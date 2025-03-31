#undef LIB_SPEC
#define LIB_SPEC "%{pthread:-lpthread} --whole-archive -lc --no-whole-archive -lg"
