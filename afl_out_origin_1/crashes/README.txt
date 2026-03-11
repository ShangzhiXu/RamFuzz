Command line used to find this crash:

/srv/scratch/z5500277/FormatFuzzer/AFLplusplus/afl-fuzz -d -i /srv/scratch/z5500277/G2FUZZ/mp4_output/default/gen_seeds/ -o /srv/scratch/z5500277/FormatFuzzer/afl_out_origin_1 -t 5000 -- /srv/scratch/z5500277/target/Bento4/build-afl/mp4dump @@

If you can't reproduce a bug outside of afl-fuzz, be sure to set the same
memory limit. The limit used for this fuzzing session was 50.0 MB.

Need a tool to minimize test cases before investigating the crashes or sending
them to a vendor? Check out the afl-tmin that comes with the fuzzer!

Found any cool bugs in open-source tools using afl-fuzz? If yes, please drop
an mail at <afl-users@googlegroups.com> once the issues are fixed

  https://github.com/vanhauser-thc/AFLplusplus

