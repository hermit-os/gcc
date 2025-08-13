/* Useful if you wish to make target-specific gcc changes. */
#undef TARGET_HERMIT
#define TARGET_HERMIT 1

#undef  CPP_SPEC
#define CPP_SPEC "%(cpp_cpu) %{pthread:-D_REENTRANT}"

/* Switch into a generic section.  */
#define TARGET_ASM_NAMED_SECTION  default_elf_asm_named_section

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
#define STARTFILE_SPEC "crt0%O%s crti%O%s %{static:crtbeginT%O%s;shared|static-pie|" PIE_SPEC ":crtbeginS%O%s;:crtbegin%O%s}"

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC "%{shared|static-pie|" PIE_SPEC ":crtendS%O%s;:crtend%O%s} crtn%O%s"
