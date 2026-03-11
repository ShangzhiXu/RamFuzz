/*
 * violation_postproc.c — MP4 violation post-processor
 *
 * After FormatFuzzer generates a structurally valid MP4, this module
 * walks the box tree, identifies fields with known valid domains
 * (from G2FUZZ ComponentEnum 04_type_values.json), and overwrites
 * selected fields with values OUTSIDE their valid domain.
 *
 * Selection strategy (simplified, no coverage feedback):
 *   - Geometric distribution for cardinality (how many fields per round)
 *   - Epsilon-greedy with frequency fairness:
 *       * With prob epsilon: random selection
 *       * Otherwise: prefer least-selected fields
 *   - Periodic decay of selection counts (windowed)
 */

#include "violation_postproc.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

/* ================================================================
 * Configuration
 * ================================================================ */

#define VIOLATION_PROB      0.5     /* prob of applying violation per call   */
#define EPSILON             0.1     /* exploration rate                      */
#define GEO_BASE            0.6     /* geometric dist base for cardinality   */
#define COLD_START          20      /* pure-random rounds at start           */
#define WINDOW_SIZE         100     /* decay window                          */
#define MAX_FOUND           256     /* max fields found per buffer           */
#define TYPE_RANGE_VIOL_P   0.3     /* prob of violating outside type range  */

/* ================================================================
 * Field type / domain type constants
 * ================================================================ */

#define FT_UINT8   1
#define FT_UINT16  2
#define FT_UINT24  3
#define FT_UINT32  4
#define FT_UINT64  5
#define FT_INT16   6
#define FT_INT32   7
#define FT_FOURCC  8   /* 4-byte FourCC string */

#define DT_DISCRETE 1  /* specific valid values             */
#define DT_RANGE    2  /* [min, max] inclusive range         */

#define MAX_DVALS  16  /* max domain values per field        */

/* ================================================================
 * Encode FourCC as int64 for domain table
 * ================================================================ */

#define FC(a,b,c,d) ((int64_t)( \
    ((uint32_t)(a)<<24)|((uint32_t)(b)<<16)|((uint32_t)(c)<<8)|(uint32_t)(d)))

/* ================================================================
 * Field definition
 * ================================================================ */

typedef struct {
    char     box_type[5];     /* e.g. "mvhd"                       */
    char     field_name[32];  /* e.g. "timescale" (for debugging)   */
    uint16_t offset;          /* absolute offset from box start     */
    uint8_t  size;            /* field size in bytes                */
    uint8_t  field_type;      /* FT_*                               */
    uint8_t  domain_type;     /* DT_*                               */
    int      dcnt;            /* number of domain values            */
    int64_t  dvals[MAX_DVALS];/* valid domain values / [min,max]    */
} field_def_t;

/* ================================================================
 * Field table — extracted from 04_type_values.json
 * ================================================================ */

static const field_def_t FTABLE[] = {

    /* ---- ftyp (plain box) ---- */
    {"ftyp","major_brand",   8, 4, FT_FOURCC, DT_DISCRETE, 12,
     {FC('i','s','o','m'), FC('i','s','o','2'), FC('m','p','4','1'),
      FC('m','p','4','2'), FC('a','v','c','1'), FC('h','v','c','1'),
      FC('h','e','v','1'), FC('a','v','0','1'), FC('d','a','s','h'),
      FC('q','t',' ',' '), FC('M','4','V',' '), FC('M','4','A',' ')}},
    {"ftyp","minor_version", 12, 4, FT_UINT32, DT_DISCRETE, 4,
     {0, 1, 512, 131072}},

    /* ---- mvhd (fullbox) ---- */
    {"mvhd","version",       8,  1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},
    {"mvhd","flags",         9,  3, FT_UINT24, DT_DISCRETE, 1, {0}},
    {"mvhd","timescale",    20,  4, FT_UINT32, DT_RANGE,    2, {1, 1000000}},
    {"mvhd","rate",         28,  4, FT_UINT32, DT_DISCRETE, 1, {0x00010000}},
    {"mvhd","volume",       32,  2, FT_UINT16, DT_DISCRETE, 1, {0x0100}},
    {"mvhd","next_track_ID",104, 4, FT_UINT32, DT_RANGE,    2, {1, 100}},

    /* ---- tkhd (fullbox) ---- */
    {"tkhd","version",       8,  1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},
    {"tkhd","flags",         9,  3, FT_UINT24, DT_DISCRETE, 3, {1, 3, 7}},
    {"tkhd","track_ID",     20,  4, FT_UINT32, DT_RANGE,    2, {1, 100}},
    {"tkhd","layer",        40,  2, FT_INT16,  DT_DISCRETE, 1, {0}},
    {"tkhd","alternate_grp",42,  2, FT_UINT16, DT_DISCRETE, 1, {0}},
    {"tkhd","volume",       44,  2, FT_UINT16, DT_DISCRETE, 2, {0, 0x0100}},
    {"tkhd","width",        84,  4, FT_UINT32, DT_RANGE,    2, {0, 0x1E000000}},
    {"tkhd","height",       88,  4, FT_UINT32, DT_RANGE,    2, {0, 0x10E00000}},

    /* ---- mdhd (fullbox) ---- */
    {"mdhd","version",       8,  1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},
    {"mdhd","timescale",    20,  4, FT_UINT32, DT_RANGE,    2, {1, 1000000}},
    {"mdhd","language",     28,  2, FT_UINT16, DT_RANGE,    2, {0, 0x7FFF}},

    /* ---- hdlr (fullbox) ---- */
    {"hdlr","version",       8,  1, FT_UINT8,  DT_DISCRETE, 1, {0}},
    {"hdlr","handler_type", 16,  4, FT_FOURCC, DT_DISCRETE, 7,
     {FC('v','i','d','e'), FC('s','o','u','n'), FC('h','i','n','t'),
      FC('m','e','t','a'), FC('t','e','x','t'), FC('s','u','b','t'),
      FC('s','b','t','l')}},

    /* ---- smhd (fullbox) ---- */
    {"smhd","balance",      12,  2, FT_INT16,  DT_DISCRETE, 1, {0}},

    /* ---- vmhd (fullbox) ---- */
    {"vmhd","version",       8,  1, FT_UINT8,  DT_DISCRETE, 1, {0}},
    {"vmhd","flags",         9,  3, FT_UINT24, DT_DISCRETE, 1, {1}},
    {"vmhd","graphicsmode", 12,  2, FT_UINT16, DT_DISCRETE, 1, {0}},

    /* ---- stts (fullbox) ---- */
    {"stts","entry_count",  12,  4, FT_UINT32, DT_RANGE,    2, {0, 100000}},

    /* ---- ctts (fullbox) ---- */
    {"ctts","version",       8,  1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},
    {"ctts","entry_count",  12,  4, FT_UINT32, DT_RANGE,    2, {0, 100000}},

    /* ---- stsc (fullbox) ---- */
    {"stsc","entry_count",  12,  4, FT_UINT32, DT_RANGE,    2, {0, 100000}},

    /* ---- stsz (fullbox) ---- */
    {"stsz","sample_size",  12,  4, FT_UINT32, DT_RANGE,    2, {0, 1048576}},
    {"stsz","sample_count", 16,  4, FT_UINT32, DT_RANGE,    2, {0, 100000}},

    /* ---- stco (fullbox) ---- */
    {"stco","entry_count",  12,  4, FT_UINT32, DT_RANGE,    2, {0, 100000}},

    /* ---- co64 (fullbox) ---- */
    {"co64","entry_count",  12,  4, FT_UINT32, DT_RANGE,    2, {0, 100000}},

    /* ---- stss (fullbox) ---- */
    {"stss","entry_count",  12,  4, FT_UINT32, DT_RANGE,    2, {0, 100000}},

    /* ---- stsd (fullbox) ---- */
    {"stsd","entry_count",  12,  4, FT_UINT32, DT_RANGE,    2, {1, 100}},

    /* ---- elst (fullbox) ---- */
    {"elst","version",       8,  1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},
    {"elst","entry_count",  12,  4, FT_UINT32, DT_RANGE,    2, {1, 100}},

    /* ---- dref (fullbox) ---- */
    {"dref","entry_count",  12,  4, FT_UINT32, DT_RANGE,    2, {1, 10}},

    /* ---- mfhd (fullbox) ---- */
    {"mfhd","seq_number",   12,  4, FT_UINT32, DT_RANGE,    2, {1, 10000}},

    /* ---- tfhd (fullbox) ---- */
    {"tfhd","track_ID",     12,  4, FT_UINT32, DT_RANGE,    2, {1, 100}},

    /* ---- tfdt (fullbox) ---- */
    {"tfdt","version",       8,  1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},

    /* ---- trun (fullbox) ---- */
    {"trun","sample_count", 12,  4, FT_UINT32, DT_RANGE,    2, {0, 100000}},

    /* ---- sidx (fullbox) ---- */
    {"sidx","version",       8,  1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},
    {"sidx","timescale",    16,  4, FT_UINT32, DT_RANGE,    2, {1, 1000000}},

    /* ---- emsg (fullbox) ---- */
    {"emsg","version",       8,  1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},

    /* ---- pssh (fullbox) ---- */
    {"pssh","version",       8,  1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},

    /* ---- tenc (fullbox) ---- */
    {"tenc","isProtected",  14,  1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},
    {"tenc","IV_Size",      15,  1, FT_UINT8,  DT_DISCRETE, 3, {0, 8, 16}},

    /* ---- sbgp (fullbox) ---- */
    {"sbgp","entry_count",  16,  4, FT_UINT32, DT_RANGE,    2, {0, 100000}},

    /* ---- sgpd (fullbox) ---- */
    {"sgpd","version",       8,  1, FT_UINT8,  DT_DISCRETE, 2, {1, 2}},

    /* ---- avcC (plain box) ---- */
    {"avcC","configVersion",  8, 1, FT_UINT8,  DT_DISCRETE, 1, {1}},
    {"avcC","AVCProfile",     9, 1, FT_UINT8,  DT_DISCRETE, 7,
     {66, 77, 88, 100, 110, 122, 244}},
    {"avcC","AVCLevel",      11, 1, FT_UINT8,  DT_RANGE,    2, {10, 62}},

    /* ---- hvcC (plain box) ---- */
    {"hvcC","configVersion",  8, 1, FT_UINT8,  DT_DISCRETE, 1, {1}},

    /* ---- av1C (plain box) ---- */
    {"av1C","marker_ver",     8, 1, FT_UINT8,  DT_DISCRETE, 1, {0x81}},

    /* ---- colr (plain box) ---- */
    {"colr","colour_type",    8, 4, FT_FOURCC, DT_DISCRETE, 3,
     {FC('n','c','l','x'), FC('r','I','C','C'), FC('p','r','o','f')}},

    /* ---- pasp (plain box) ---- */
    {"pasp","hSpacing",       8, 4, FT_UINT32, DT_RANGE,    2, {1, 65535}},
    {"pasp","vSpacing",      12, 4, FT_UINT32, DT_RANGE,    2, {1, 65535}},

    /* ---- btrt (plain box) ---- */
    {"btrt","bufferSizeDB",   8, 4, FT_UINT32, DT_RANGE,    2, {0, 10000000}},
    {"btrt","maxBitrate",    12, 4, FT_UINT32, DT_RANGE,    2, {0, 1000000000}},
    {"btrt","avgBitrate",    16, 4, FT_UINT32, DT_RANGE,    2, {0, 1000000000}},

    /* ---- trex (fullbox) ---- */
    {"trex","track_ID",      12, 4, FT_UINT32, DT_RANGE,    2, {1, 100}},
    {"trex","def_samp_desc", 16, 4, FT_UINT32, DT_RANGE,    2, {1, 100}},

    /* ---- pdin (fullbox) ---- */
    {"pdin","version",        8, 1, FT_UINT8,  DT_DISCRETE, 1, {0}},

    /* ---- iods (fullbox) ---- */
    {"iods","version",        8, 1, FT_UINT8,  DT_DISCRETE, 1, {0}},

    /* ---- ssix (fullbox) ---- */
    {"ssix","subseg_count",  12, 4, FT_UINT32, DT_RANGE,    2, {0, 10000}},

    /* ---- saiz (fullbox) ---- */
    {"saiz","def_info_size", 12, 1, FT_UINT8,  DT_RANGE,    2, {0, 128}},

    /* ---- saio (fullbox) ---- */
    {"saio","entry_count",   12, 4, FT_UINT32, DT_RANGE,    2, {0, 10000}},

    /* ---- mehd (fullbox) ---- */
    {"mehd","version",        8, 1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},

    /* ---- prft (fullbox) ---- */
    {"prft","version",        8, 1, FT_UINT8,  DT_DISCRETE, 2, {0, 1}},
};

#define FTABLE_SIZE ((int)(sizeof(FTABLE) / sizeof(FTABLE[0])))

/* ================================================================
 * Container box check
 * ================================================================ */

static const char* CONTAINERS[] = {
    "moov","trak","mdia","minf","stbl","dinf","edts","udta",
    "mvex","moof","traf","mfra","sinf","schi","ilst","iprp",
    "ipco","ipro","meco","mere","grpl","strd","skip","free",
    "wide", NULL
};

static int is_container(const char t[4]) {
    for (int i = 0; CONTAINERS[i]; i++)
        if (memcmp(t, CONTAINERS[i], 4) == 0) return 1;
    return 0;
}

/* ================================================================
 * Found field during box walk
 * ================================================================ */

typedef struct {
    uint32_t buf_offset;   /* absolute offset in buffer */
    int      ftable_idx;   /* index into FTABLE         */
} found_t;

/* ================================================================
 * Per-field selection state (persists across calls)
 * ================================================================ */

static int sel_count[MAX_DVALS * 8];  /* oversized; indexed by ftable_idx */
static int global_step = 0;
static int initialized = 0;

/* ================================================================
 * Type range helpers
 * ================================================================ */

static void type_range(uint8_t ft, int64_t *lo, int64_t *hi) {
    switch (ft) {
        case FT_UINT8:  *lo = 0; *hi = 255; break;
        case FT_UINT16: *lo = 0; *hi = 65535; break;
        case FT_UINT24: *lo = 0; *hi = 16777215; break;
        case FT_UINT32: *lo = 0; *hi = 4294967295LL; break;
        case FT_UINT64: *lo = 0; *hi = (int64_t)0x7FFFFFFFFFFFFFFFLL; break;
        case FT_INT16:  *lo = -32768; *hi = 32767; break;
        case FT_INT32:  *lo = -2147483648LL; *hi = 2147483647LL; break;
        case FT_FOURCC: *lo = 0; *hi = 4294967295LL; break;
        default:        *lo = 0; *hi = 255; break;
    }
}

/* ================================================================
 * Random helpers
 * ================================================================ */

static double randf(void) {
    return (double)rand() / ((double)RAND_MAX + 1.0);
}

static int64_t rand_range(int64_t lo, int64_t hi) {
    if (lo >= hi) return lo;
    uint64_t span = (uint64_t)(hi - lo + 1);
    return lo + (int64_t)((uint64_t)rand() % span);
}

/* ================================================================
 * Violation value generation
 * ================================================================ */

static int64_t gen_violation_numeric(const field_def_t *f) {
    int64_t t_lo, t_hi;
    type_range(f->field_type, &t_lo, &t_hi);

    /* With some probability, go completely outside the type range */
    if (randf() < TYPE_RANGE_VIOL_P) {
        int64_t delta = (int64_t)(rand() % 65536) + 1;
        if (rand() & 1)
            return t_lo - delta;  /* underflow */
        else
            return t_hi + delta;  /* overflow */
    }

    if (f->domain_type == DT_RANGE && f->dcnt >= 2) {
        int64_t d_lo = f->dvals[0], d_hi = f->dvals[1];

        /* Violation = [t_lo, d_lo-1] ∪ [d_hi+1, t_hi] */
        int64_t below_size = (d_lo > t_lo) ? (d_lo - t_lo) : 0;
        int64_t above_size = (t_hi > d_hi) ? (t_hi - d_hi) : 0;
        int64_t total = below_size + above_size;

        if (total > 0) {
            int64_t pick = rand_range(0, total - 1);
            if (pick < below_size)
                return t_lo + pick;
            else
                return d_hi + 1 + (pick - below_size);
        }
        /* Fallback: boundary */
        if (d_lo > t_lo) return d_lo - 1;
        if (d_hi < t_hi) return d_hi + 1;
        return t_lo;

    } else if (f->domain_type == DT_DISCRETE && f->dcnt > 0) {
        /* Generate value NOT in discrete set */
        for (int tries = 0; tries < 100; tries++) {
            int64_t v = rand_range(t_lo, t_hi);
            int found = 0;
            for (int j = 0; j < f->dcnt; j++) {
                if (v == f->dvals[j]) { found = 1; break; }
            }
            if (!found) return v;
        }
        /* Fallback: boundary of first discrete value */
        return (f->dvals[0] > t_lo) ? f->dvals[0] - 1 : f->dvals[0] + 1;
    }

    return rand_range(t_lo, t_hi);
}

static uint32_t gen_violation_fourcc(const field_def_t *f) {
    /* Generate a random FourCC not in the enum list */
    for (int tries = 0; tries < 100; tries++) {
        char c[4];
        for (int j = 0; j < 4; j++)
            c[j] = (char)(0x20 + (rand() % 95));  /* printable ASCII */
        uint32_t v = ((uint32_t)(unsigned char)c[0] << 24) |
                     ((uint32_t)(unsigned char)c[1] << 16) |
                     ((uint32_t)(unsigned char)c[2] << 8)  |
                     ((uint32_t)(unsigned char)c[3]);
        int found = 0;
        for (int j = 0; j < f->dcnt; j++) {
            if ((int64_t)v == f->dvals[j]) { found = 1; break; }
        }
        if (!found) return v;
    }
    return 0xDEADBEEF;
}

/* ================================================================
 * Write value into buffer
 * ================================================================ */

static void write_val(uint8_t *buf, uint32_t off, uint8_t sz, int64_t val) {
    /* Big-endian write, truncated to sz bytes */
    uint64_t uval = (uint64_t)val;
    for (int i = sz - 1; i >= 0; i--) {
        buf[off + i] = (uint8_t)(uval & 0xFF);
        uval >>= 8;
    }
}

/* ================================================================
 * MP4 box walker — find fields in buffer
 * ================================================================ */

static int walk_boxes(uint8_t *buf, uint32_t buf_size,
                      uint32_t start, uint32_t end,
                      found_t *found, int max_found) {
    int nfound = 0;
    uint32_t pos = start;

    while (pos + 8 <= end && nfound < max_found) {
        uint32_t box_size = ((uint32_t)buf[pos] << 24) |
                            ((uint32_t)buf[pos+1] << 16) |
                            ((uint32_t)buf[pos+2] << 8) |
                            (uint32_t)buf[pos+3];
        char type[5] = {0};
        memcpy(type, buf + pos + 4, 4);

        if (box_size < 8 || pos + box_size > end)
            break;

        /* Check if this box type has fields in FTABLE */
        for (int i = 0; i < FTABLE_SIZE; i++) {
            if (memcmp(FTABLE[i].box_type, type, 4) != 0)
                continue;
            /* Verify field fits within box */
            if (FTABLE[i].offset + FTABLE[i].size <= box_size) {
                found[nfound].buf_offset = pos + FTABLE[i].offset;
                found[nfound].ftable_idx = i;
                nfound++;
                if (nfound >= max_found) break;
            }
        }

        /* Recurse into containers */
        if (is_container(type)) {
            nfound += walk_boxes(buf, buf_size, pos + 8, pos + box_size,
                                 found + nfound, max_found - nfound);
        } else if (memcmp(type, "meta", 4) == 0) {
            /* meta is fullbox container: skip version(1) + flags(3) */
            if (box_size > 12) {
                nfound += walk_boxes(buf, buf_size, pos + 12, pos + box_size,
                                     found + nfound, max_found - nfound);
            }
        }

        pos += box_size;
    }

    return nfound;
}

/* ================================================================
 * Simplified energy scheduling: epsilon-greedy + frequency fairness
 * ================================================================ */

static int sample_cardinality(int n) {
    if (n <= 0) return 0;
    double u = randf();
    if (GEO_BASE <= 0.0 || GEO_BASE >= 1.0) return 1;
    int k = (int)ceil(log(1.0 - u) / log(GEO_BASE));
    if (k < 1) k = 1;
    if (k > n) k = n;
    return k;
}

/* Select indices from found[] array using epsilon-greedy + frequency */
static int select_fields(found_t *found, int nfound,
                         int *selected, int max_sel) {
    if (nfound <= 0) return 0;

    int k = sample_cardinality(nfound);
    if (k > max_sel) k = max_sel;

    global_step++;

    if (global_step <= COLD_START || randf() < EPSILON) {
        /* Exploration: random selection without replacement */
        /* Fisher-Yates partial shuffle */
        int *perm = (int*)malloc(nfound * sizeof(int));
        for (int i = 0; i < nfound; i++) perm[i] = i;
        for (int i = 0; i < k && i < nfound; i++) {
            int j = i + (rand() % (nfound - i));
            int tmp = perm[i]; perm[i] = perm[j]; perm[j] = tmp;
            selected[i] = perm[i];
        }
        free(perm);
    } else {
        /* Exploitation: pick least-selected fields */
        /* Simple approach: sort found by sel_count, pick first k */
        int *order = (int*)malloc(nfound * sizeof(int));
        for (int i = 0; i < nfound; i++) order[i] = i;
        /* Insertion sort by sel_count (small n, fast enough) */
        for (int i = 1; i < nfound; i++) {
            int key = order[i];
            int key_sc = sel_count[found[key].ftable_idx];
            int j = i - 1;
            while (j >= 0 && sel_count[found[order[j]].ftable_idx] > key_sc) {
                order[j+1] = order[j];
                j--;
            }
            order[j+1] = key;
        }
        for (int i = 0; i < k; i++)
            selected[i] = order[i];
        free(order);
    }

    /* Update selection counts */
    for (int i = 0; i < k; i++)
        sel_count[found[selected[i]].ftable_idx]++;

    /* Periodic decay */
    if (global_step % WINDOW_SIZE == 0) {
        for (int i = 0; i < FTABLE_SIZE; i++)
            sel_count[i] = sel_count[i] / 2;
    }

    return k;
}

/* ================================================================
 * Public API
 * ================================================================ */

void violation_init(void) {
    if (initialized) return;
    srand((unsigned)time(NULL) ^ (unsigned)getpid());
    memset(sel_count, 0, sizeof(sel_count));
    global_step = 0;
    initialized = 1;
}

int violate_mp4_buffer(uint8_t *buf, uint32_t size) {
    if (!initialized) violation_init();
    if (!buf || size < 8) return 0;

    /* Probabilistic: skip some rounds to let original mutations through */
    if (randf() >= VIOLATION_PROB) return 0;

    /* Walk box tree, collect fields */
    found_t found[MAX_FOUND];
    int nfound = walk_boxes(buf, size, 0, size, found, MAX_FOUND);
    if (nfound == 0) return 0;

    /* Select fields to violate */
    int selected[16];
    int k = select_fields(found, nfound, selected, 16);

    /* Generate and apply violations */
    int applied = 0;
    for (int i = 0; i < k; i++) {
        found_t *f = &found[selected[i]];
        const field_def_t *fd = &FTABLE[f->ftable_idx];

        /* Bounds check */
        if (f->buf_offset + fd->size > size) continue;

        if (fd->field_type == FT_FOURCC) {
            uint32_t v = gen_violation_fourcc(fd);
            write_val(buf, f->buf_offset, 4, (int64_t)v);
        } else {
            int64_t v = gen_violation_numeric(fd);
            write_val(buf, f->buf_offset, fd->size, v);
        }
        applied++;
    }

    return applied;
}
