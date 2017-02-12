/* Useful if you wish to make target-specific gcc changes. */
#undef TARGET_HERMIT
#define TARGET_HERMIT 1

/* Default arguments you want when running your
 * i686-hermit-gcc/x86_64-hermit-gcc toolchain */
#undef LIB_SPEC
#define LIB_SPEC "%{!z:-z max-page-size=0x1000 -z common-page-size=0x1000} \
		  %{pthread:-lpthread} -lc -lg -lm -lhermit"

#undef  CPP_SPEC
#define CPP_SPEC "%(cpp_cpu) %{pthread:-D_REENTRANT}"

/* Don't automatically add extern "C" { } around header files. */
#undef  NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C 1

/* Switch into a generic section.  */
#define TARGET_ASM_NAMED_SECTION  default_elf_asm_named_section

#undef TARGET_TLS_DIRECT_SEG_REFS_DEFAULT
#define TARGET_TLS_DIRECT_SEG_REFS_DEFAULT MASK_TLS_DIRECT_SEG_REFS

/* Additional predefined macros. */
#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()      \
  do {                                \
    builtin_define ("__hermit__");      \
    builtin_define ("__unix__");      \
    builtin_assert ("system=hermit");   \
    builtin_assert ("system=unix");   \
    builtin_assert ("system=posix");   \
  } while(0);

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC "crt0.o%s crti.o%s crtbegin.o%s"

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s crtn.o%s"
