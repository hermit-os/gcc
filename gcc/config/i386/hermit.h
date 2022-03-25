/* Default arguments you want when running your
 * x86_64-hermit-gcc toolchain */
#undef LIB_SPEC
#define LIB_SPEC "%{!z:-z max-page-size=0x1000 -z common-page-size=0x1000} \
		  %{pthread:-lpthread} -lc -lg -lm -lhermit"

/* The svr4 ABI for the i386 says that records and unions are returned
 * in memory.  In the 64bit compilation we will turn this flag off in
 * x86_option_override_internal, as we never do pcc_struct_return
 * scheme on this target.  */
#undef DEFAULT_PCC_STRUCT_RETURN
#define DEFAULT_PCC_STRUCT_RETURN 1

#undef TARGET_TLS_DIRECT_SEG_REFS_DEFAULT
#define TARGET_TLS_DIRECT_SEG_REFS_DEFAULT MASK_TLS_DIRECT_SEG_REFS
