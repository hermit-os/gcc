/* Copyright (C) 1997 Free Software Foundation, Inc.
 * This is part of the G77 manual.
 * For copying conditions, see the file g77.texi. */

/* This is the file containing the verbage for the
   intrinsics.  It consists of a data base built up
   via DEFDOC macros of the form:

   DEFDOC (IMP, SUMMARY, DESCRIPTION)

   IMP is the implementation keyword used in the intrin module.
   SUMMARY is the short summary to go in the "* Menu:" section
   of the Info document.  DESCRIPTION is the longer description
   to go in the documentation itself.

   Note that IMP is leveraged across multiple intrinsic names.

   To make for more accurate and consistent documentation,
   the translation made by intdoc.c of the text in SUMMARY
   and DESCRIPTION includes the special sequence

   @ARGNO@

   where ARGNO is a series of digits forming a number that
   is substituted by intdoc.c as follows:

   0     The initial-caps form of the intrinsic name (e.g. Float).
   1-98  The initial-caps form of the ARGNO'th argument.
   99    (SUMMARY only) a newline plus the appropriate # of spaces.

   Hope this info is enough to encourage people to feel free to
   add documentation to this file!

*/

/* ~~~~~ to do:
   ALARM
*/

#define ARCHAIC(upper,mixed) \
  "Archaic form of @code{" #upper "()} that is specific\n\
to one type for @var{@1@}.\n\
@xref{" #mixed " Intrinsic}.\n"

#define ARCHAIC_2nd(upper,mixed) \
  "Archaic form of @code{" #upper "()} that is specific\n\
to one type for @var{@2@}.\n\
@xref{" #mixed " Intrinsic}.\n"

#define ARCHAIC_2(upper,mixed) \
  "Archaic form of @code{" #upper "()} that is specific\n\
to one type for @var{@1@} and @var{@2@}.\n\
@xref{" #mixed " Intrinsic}.\n"

DEFDOC (ABS, "Absolute value.", "\
Returns the absolute value of @var{@1@}.

If @var{@1@} is type @code{COMPLEX}, the absolute
value is computed as:

@example
SQRT(REALPART(@var{@1@})**2, IMAGPART(@var{@1@})**2)
@end example

@noindent
Otherwise, it is computed by negating the @var{@1@} if
it is negative, or returning @var{@1@}.

@xref{Sign Intrinsic}, for how to explicitly
compute the positive or negative form of the absolute
value of an expression.
")

DEFDOC (CABS, "Absolute value (archaic).", ARCHAIC (ABS, Abs))

DEFDOC (DABS, "Absolute value (archaic).", ARCHAIC (ABS, Abs))

DEFDOC (IABS, "Absolute value (archaic).", ARCHAIC (ABS, Abs))

DEFDOC (CDABS, "Absolute value (archaic).", ARCHAIC (ABS, Abs))

DEFDOC (ACHAR, "ASCII character from code.", "\
Returns the ASCII character corresponding to the
code specified by @var{@1@}.

@xref{IAChar Intrinsic}, for the inverse of this function.

@xref{Char Intrinsic}, for the function corresponding
to the system's native character set.
")

DEFDOC (IACHAR, "ASCII code for character.", "\
Returns the code for the ASCII character in the
first character position of @var{@1@}.

@xref{AChar Intrinsic}, for the inverse of this function.

@xref{IChar Intrinsic}, for the function corresponding
to the system's native character set.
")

DEFDOC (CHAR, "Character from code.", "\
Returns the character corresponding to the
code specified by @var{@1@}, using the system's
native character set.

Because the system's native character set is used,
the correspondence between character and their codes
is not necessarily the same between GNU Fortran
implementations.

Note that no intrinsic exists to convert a numerical
value to a printable character string.
For example, there is no intrinsic that, given
an @code{INTEGER} or @code{REAL} argument with the
value @samp{154}, returns the @code{CHARACTER}
result @samp{'154'}.

Instead, you can use internal-file I/O to do this kind
of conversion.
For example:

@smallexample
INTEGER VALUE
CHARACTER*10 STRING
VALUE = 154
WRITE (STRING, '(I10)'), VALUE
PRINT *, STRING
END
@end smallexample

The above program, when run, prints:

@smallexample
        154
@end smallexample

@xref{IChar Intrinsic}, for the inverse of the @code{@0@} function.

@xref{AChar Intrinsic}, for the function corresponding
to the ASCII character set.
")

DEFDOC (ICHAR, "Code for character.", "\
Returns the code for the character in the
first character position of @var{@1@}.

Because the system's native character set is used,
the correspondence between character and their codes
is not necessarily the same between GNU Fortran
implementations.

Note that no intrinsic exists to convert a printable
character string to a numerical value.
For example, there is no intrinsic that, given
the @code{CHARACTER} value @samp{'154'}, returns an
@code{INTEGER} or @code{REAL} value with the value @samp{154}.

Instead, you can use internal-file I/O to do this kind
of conversion.
For example:

@smallexample
INTEGER VALUE
CHARACTER*10 STRING
STRING = '154'
READ (STRING, '(I10)'), VALUE
PRINT *, VALUE
END
@end smallexample

The above program, when run, prints:

@smallexample
 154
@end smallexample

@xref{Char Intrinsic}, for the inverse of the @code{@0@} function.

@xref{IAChar Intrinsic}, for the function corresponding
to the ASCII character set.
")

DEFDOC (ACOS, "Arc cosine.", "\
Returns the arc-cosine (inverse cosine) of @var{@1@}
in radians.

@xref{Cos Intrinsic}, for the inverse of this function.
")

DEFDOC (DACOS, "Arc cosine (archaic).", ARCHAIC (ACOS, ACos))

DEFDOC (AIMAG, "Convert/extract imaginary part of complex.", "\
Returns the (possibly converted) imaginary part of @var{@1@}.

Use of @code{@0@()} with an argument of a type
other than @code{COMPLEX(KIND=1)} is restricted to the following case:

@example
REAL(AIMAG(@1@))
@end example

@noindent
This expression converts the imaginary part of @1@ to
@code{REAL(KIND=1)}.

@xref{REAL() and AIMAG() of Complex}, for more information.
")

DEFDOC (DIMAG, "Convert/extract imaginary part of complex (archaic).", ARCHAIC (AIMAG, AImag))

DEFDOC (AINT, "Truncate to whole number.", "\
Returns @var{@1@} with the fractional portion of its
magnitude truncated and its sign preserved.
(Also called ``truncation towards zero''.)

@xref{ANInt Intrinsic}, for how to round to nearest
whole number.

@xref{Int Intrinsic}, for how to truncate and then convert
number to @code{INTEGER}.
")

DEFDOC (DINT, "Truncate to whole number (archaic).", ARCHAIC (AINT, AInt))

DEFDOC (INT, "Convert to @code{INTEGER} value truncated@99@to whole number.", "\
Returns @var{@1@} with the fractional portion of its
magnitude truncated and its sign preserved, converted
to type @code{INTEGER(KIND=1)}.

If @var{@1@} is type @code{COMPLEX}, its real part is
truncated and converted, and its imaginary part is disregarded.

@xref{NInt Intrinsic}, for how to convert, rounded to nearest
whole number.

@xref{AInt Intrinsic}, for how to truncate to whole number
without converting.
")

DEFDOC (IDINT, "Convert to @code{INTEGER} value truncated@99@to whole number (archaic).", ARCHAIC (INT, Int))

DEFDOC (ANINT, "Round to nearest whole number.", "\
Returns @var{@1@} with the fractional portion of its
magnitude eliminated by rounding to the nearest whole
number and with its sign preserved.

A fractional portion exactly equal to
@samp{.5} is rounded to the whole number that
is larger in magnitude.
(Also called ``Fortran round''.)

@xref{AInt Intrinsic}, for how to truncate to
whole number.

@xref{NInt Intrinsic}, for how to round and then convert
number to @code{INTEGER}.
")

DEFDOC (DNINT, "Round to nearest whole number (archaic).", ARCHAIC (ANINT, ANInt))

DEFDOC (NINT, "Convert to @code{INTEGER} value rounded@99@to nearest whole number.", "\
Returns @var{@1@} with the fractional portion of its
magnitude eliminated by rounding to the nearest whole
number and with its sign preserved, converted
to type @code{INTEGER(KIND=1)}.

If @var{@1@} is type @code{COMPLEX}, its real part is
rounded and converted.

A fractional portion exactly equal to
@samp{.5} is rounded to the whole number that
is larger in magnitude.
(Also called ``Fortran round''.)

@xref{Int Intrinsic}, for how to convert, truncate to
whole number.

@xref{ANInt Intrinsic}, for how to round to nearest whole number
without converting.
")

DEFDOC (IDNINT, "Convert to @code{INTEGER} value rounded@99@to nearest whole number (archaic).", ARCHAIC (NINT, NInt))

DEFDOC (LOG, "Natural logarithm.", "\
Returns the natural logarithm of @var{@1@}, which must
be greater than zero or, if type @code{COMPLEX}, must not
be zero.

@xref{Exp Intrinsic}, for the inverse of this function.

@xref{Log10 Intrinsic}, for the base-10 logarithm function.
")

DEFDOC (ALOG, "Natural logarithm (archaic).", ARCHAIC (LOG, Log))

DEFDOC (CLOG, "Natural logarithm (archaic).", ARCHAIC (LOG, Log))

DEFDOC (DLOG, "Natural logarithm (archaic).", ARCHAIC (LOG, Log))

DEFDOC (CDLOG, "Natural logarithm (archaic).", ARCHAIC (LOG, Log))

DEFDOC (LOG10, "Natural logarithm.", "\
Returns the natural logarithm of @var{@1@}, which must
be greater than zero or, if type @code{COMPLEX}, must not
be zero.

The inverse of this function is @samp{10. ** LOG10(@var{@1@})}.

@xref{Log Intrinsic}, for the natural logarithm function.
")

DEFDOC (ALOG10, "Natural logarithm (archaic).", ARCHAIC (LOG10, Log10))

DEFDOC (DLOG10, "Natural logarithm (archaic).", ARCHAIC (LOG10, Log10))

DEFDOC (MAX, "Maximum value.", "\
Returns the argument with the largest value.

@xref{Min Intrinsic}, for the opposite function.
")

DEFDOC (AMAX0, "Maximum value (archaic).", "\
Archaic form of @code{MAX()} that is specific
to one type for @var{@1@} and a different return type.
@xref{Max Intrinsic}.
")

DEFDOC (AMAX1, "Maximum value (archaic).", ARCHAIC (MAX, Max))

DEFDOC (DMAX1, "Maximum value (archaic).", ARCHAIC (MAX, Max))

DEFDOC (MAX0, "Maximum value (archaic).", ARCHAIC (MAX, Max))

DEFDOC (MAX1, "Maximum value (archaic).", "\
Archaic form of @code{MAX()} that is specific
to one type for @var{@1@} and a different return type.
@xref{Max Intrinsic}.
")

DEFDOC (MIN, "Minimum value.", "\
Returns the argument with the smallest value.

@xref{Max Intrinsic}, for the opposite function.
")

DEFDOC (AMIN0, "Minimum value (archaic).", "\
Archaic form of @code{MIN()} that is specific
to one type for @var{@1@} and a different return type.
@xref{Min Intrinsic}.
")

DEFDOC (AMIN1, "Minimum value (archaic).", ARCHAIC (MIN, Min))

DEFDOC (DMIN1, "Minimum value (archaic).", ARCHAIC (MIN, Min))

DEFDOC (MIN0, "Minimum value (archaic).", ARCHAIC (MIN, Min))

DEFDOC (MIN1, "Minimum value (archaic).", "\
Archaic form of @code{MIN()} that is specific
to one type for @var{@1@} and a different return type.
@xref{Min Intrinsic}.
")

DEFDOC (MOD, "Remainder.", "\
Returns remainder calculated as:

@smallexample
@var{@1@} - (INT(@var{@1@} / @var{@2@}) * @var{@2@})
@end smallexample

@var{@2@} must not be zero.
")

DEFDOC (AMOD, "Remainder (archaic).", ARCHAIC (MOD, Mod))

DEFDOC (DMOD, "Remainder (archaic).", ARCHAIC (MOD, Mod))

DEFDOC (AND, "Boolean AND.", "\
Returns value resulting from boolean AND of
pair of bits in each of @var{@1@} and @var{@2@}.
")

DEFDOC (IAND, "Boolean AND.", "\
Returns value resulting from boolean AND of
pair of bits in each of @var{@1@} and @var{@2@}.
")

DEFDOC (OR, "Boolean OR.", "\
Returns value resulting from boolean OR of
pair of bits in each of @var{@1@} and @var{@2@}.
")

DEFDOC (IOR, "Boolean OR.", "\
Returns value resulting from boolean OR of
pair of bits in each of @var{@1@} and @var{@2@}.
")

DEFDOC (XOR, "Boolean XOR.", "\
Returns value resulting from boolean exclusive-OR of
pair of bits in each of @var{@1@} and @var{@2@}.
")

DEFDOC (IEOR, "Boolean XOR.", "\
Returns value resulting from boolean exclusive-OR of
pair of bits in each of @var{@1@} and @var{@2@}.
")

DEFDOC (NOT, "Boolean NOT.", "\
Returns value resulting from boolean NOT of each bit
in @var{@1@}.
")

DEFDOC (ASIN, "Arc sine.", "\
Returns the arc-sine (inverse sine) of @var{@1@}
in radians.

@xref{Sin Intrinsic}, for the inverse of this function.
")

DEFDOC (DASIN, "Arc sine (archaic).", ARCHAIC (ASIN, ASin))

DEFDOC (ATAN, "Arc tangent.", "\
Returns the arc-tangent (inverse tangent) of @var{@1@}
in radians.

@xref{Tan Intrinsic}, for the inverse of this function.
")

DEFDOC (DATAN, "Arc tangent (archaic).", ARCHAIC (ATAN, ATan))

DEFDOC (ATAN2, "Arc tangent.", "\
Returns the arc-tangent (inverse tangent) of the complex
number (@var{@1@}, @var{@2@}) in radians.

@xref{Tan Intrinsic}, for the inverse of this function.
")

DEFDOC (DATAN2, "Arc tangent (archaic).", ARCHAIC_2 (ATAN2, ATan2))

DEFDOC (BIT_SIZE, "Number of bits in argument's type.", "\
Returns the number of bits (integer precision plus sign bit)
represented by the type for @var{@1@}.

@xref{BTest Intrinsic}, for how to test the value of a
bit in a variable or array.

@xref{IBSet Intrinsic}, for how to set a bit in a variable to 1.

@xref{IBClr Intrinsic}, for how to set a bit in a variable to 0.

")

DEFDOC (BTEST, "Test bit.", "\
Returns @code{.TRUE.} if bit @var{@2@} in @var{@1@} is
1, @code{.FALSE.} otherwise.

(Bit 0 is the low-order (rightmost) bit, adding the value 
@ifinfo
2**0,
@end ifinfo
@iftex
@tex
$2^0$,
@end tex
@end iftex
or 1,
to the number if set to 1;
bit 1 is the next-higher-order bit, adding 
@ifinfo
2**1,
@end ifinfo
@iftex
@tex
$2^1$,
@end tex
@end iftex
or 2;
bit 2 adds 
@ifinfo
2**2,
@end ifinfo
@iftex
@tex
$2^2$,
@end tex
@end iftex
or 4; and so on.)

@xref{Bit_Size Intrinsic}, for how to obtain the number of bits
in a type.
The leftmost bit of @var{@1@} is @samp{BIT_SIZE(@var{@1@}-1}.
")

DEFDOC (CMPLX, "Construct @code{COMPLEX(KIND=1)} value.", "\
If @var{@1@} is not type @code{COMPLEX},
constructs a value of type @code{COMPLEX(KIND=1)} from the
real and imaginary values specified by @var{@1@} and
@var{@2@}, respectively.
If @var{@2@} is omitted, @samp{0.} is assumed.

If @var{@1@} is type @code{COMPLEX},
converts it to type @code{COMPLEX(KIND=1)}.

@xref{Complex Intrinsic}, for information on easily constructing
a @code{COMPLEX} value of arbitrary precision from @code{REAL}
arguments.
")

DEFDOC (DCMPLX, "Construct @code{COMPLEX(KIND=2)} value.", "\
If @var{@1@} is not type @code{COMPLEX},
constructs a value of type @code{COMPLEX(KIND=2)} from the
real and imaginary values specified by @var{@1@} and
@var{@2@}, respectively.
If @var{@2@} is omitted, @samp{0D0} is assumed.

If @var{@1@} is type @code{COMPLEX},
converts it to type @code{COMPLEX(KIND=2)}.

Although this intrinsic is not standard Fortran,
it is a popular extension offered by many compilers
that support @code{DOUBLE COMPLEX}, since it offers
the easiest way to convert to @code{DOUBLE COMPLEX}
without using Fortran 90 features (such as the @samp{KIND=}
argument to the @code{CMPLX()} intrinsic).

(@samp{CMPLX(0D0, 0D0)} returns a single-precision
@code{COMPLEX} result, as required by standard FORTRAN 77.
That's why so many compilers provide @code{DCMPLX()}, since
@samp{DCMPLX(0D0, 0D0)} returns a @code{DOUBLE COMPLEX}
result.
Still, @code{DCMPLX()} converts even @code{REAL*16} arguments
to their @code{REAL*8} equivalents in most dialects of
Fortran, so neither it nor @code{CMPLX()} allow easy
construction of arbitrary-precision values without
potentially forcing a conversion involving extending or
reducing precision.
GNU Fortran provides such an intrinsic, called @code{COMPLEX()}.)

@xref{Complex Intrinsic}, for information on easily constructing
a @code{COMPLEX} value of arbitrary precision from @code{REAL}
arguments.
")

DEFDOC (CONJG, "Complex conjugate.", "\
Returns the complex conjugate:

@example
COMPLEX(REALPART(@var{@1@}), -IMAGPART(@var{@1@}))
@end example
")

DEFDOC (DCONJG, "Complex conjugate (archaic).", ARCHAIC (CONJG, ATan2))

DEFDOC (COS, "Cosine.", "\
Returns the cosine of @var{@1@}, an angle measured
in radians.

@xref{ACos Intrinsic}, for the inverse of this function.
")

DEFDOC (CCOS, "Cosine (archaic).", ARCHAIC (COS, Cos))

DEFDOC (DCOS, "Cosine (archaic).", ARCHAIC (COS, Cos))

DEFDOC (CDCOS, "Cosine (archaic).", ARCHAIC (COS, Cos))

DEFDOC (COSH, "Hyperbolic cosine.", "\
Returns the hyperbolic cosine of @var{@1@}.
")

DEFDOC (DCOSH, "Hyperbolic cosine (archaic).", ARCHAIC (COSH, CosH))

DEFDOC (SQRT, "Square root.", "\
Returns the square root of @var{@1@}, which must
not be negative.

To calculate and represent the square root of a negative
number, complex arithmetic must be used.
For example, @samp{SQRT(COMPLEX(@var{@1@}))}.

The inverse of this function is @samp{SQRT(@var{@1@}) * SQRT(@var{@1@})}.
")

DEFDOC (CSQRT, "Square root (archaic).", ARCHAIC (SQRT, SqRt))

DEFDOC (DSQRT, "Square root (archaic).", ARCHAIC (SQRT, SqRt))

DEFDOC (CDSQRT, "Square root (archaic).", ARCHAIC (SQRT, SqRt))

DEFDOC (DBLE, "Convert to double precision.", "\
Returns @var{@1@} converted to double precision
(@code{REAL(KIND=2)}).
If @var{@1@} is @code{COMPLEX}, the real part of
@var{@1@} is used for the conversion
and the imaginary part disregarded.

@xref{Sngl Intrinsic}, for the function that converts
to single precision.

@xref{Int Intrinsic}, for the function that converts
to @code{INTEGER}.

@xref{Complex Intrinsic}, for the function that converts
to @code{COMPLEX}.
")

DEFDOC (DIM, "Difference magnitude (non-negative subtract).", "\
Returns @samp{@var{@1@}-@var{@2@}} if @var{@1@} is greater than
@var{@2@}; otherwise returns zero.
")

DEFDOC (DDIM, "Difference magnitude (archaic).", ARCHAIC_2 (DIM, DiM))
DEFDOC (IDIM, "Difference magnitude (archaic).", ARCHAIC_2 (IDIM, IDiM))

DEFDOC (DPROD, "Double-precision product.", "\
Returns @samp{DBLE(@var{@1@})*DBLE(@var{@2@})}.
")

DEFDOC (EXP, "Exponential.", "\
Returns @samp{@var{e}**@var{@1@}}, where
@var{e} is approximately 2.7182818.

@xref{Log Intrinsic}, for the inverse of this function.
")

DEFDOC (CEXP, "Exponential (archaic).", ARCHAIC (EXP, Exp))

DEFDOC (DEXP, "Exponential (archaic).", ARCHAIC (EXP, Exp))

DEFDOC (CDEXP, "Exponential (archaic).", ARCHAIC (EXP, Exp))

DEFDOC (FLOAT, "Conversion (archaic).", ARCHAIC (REAL, Real))
DEFDOC (DFLOAT, "Conversion (archaic).", ARCHAIC (REAL, Real))

DEFDOC (IFIX, "Conversion (archaic).", ARCHAIC (INT, Int))

DEFDOC (LONG, "Conversion to @code{INTEGER(KIND=1)} (archaic).", "\
Archaic form of @code{INT()} that is specific
to one type for @var{@1@}.
@xref{Int Intrinsic}.

The precise meaning of this intrinsic might change
in a future version of the GNU Fortran language,
as more is learned about how it is used.
")

DEFDOC (SHORT, "Convert to @code{INTEGER(KIND=6)} value@99@truncated to whole number.", "\
Returns @var{@1@} with the fractional portion of its
magnitude truncated and its sign preserved, converted
to type @code{INTEGER(KIND=6)}.

If @var{@1@} is type @code{COMPLEX}, its real part
is truncated and converted, and its imaginary part is disgregarded.

@xref{Int Intrinsic}.

The precise meaning of this intrinsic might change
in a future version of the GNU Fortran language,
as more is learned about how it is used.
")

DEFDOC (INT2, "Convert to @code{INTEGER(KIND=6)} value@99@truncated to whole number.", "\
Returns @var{@1@} with the fractional portion of its
magnitude truncated and its sign preserved, converted
to type @code{INTEGER(KIND=6)}.

If @var{@1@} is type @code{COMPLEX}, its real part
is truncated and converted, and its imaginary part is disgregarded.

@xref{Int Intrinsic}.

The precise meaning of this intrinsic might change
in a future version of the GNU Fortran language,
as more is learned about how it is used.
")

DEFDOC (INT8, "Convert to @code{INTEGER(KIND=2)} value@99@truncated to whole number.", "\
Returns @var{@1@} with the fractional portion of its
magnitude truncated and its sign preserved, converted
to type @code{INTEGER(KIND=2)}.

If @var{@1@} is type @code{COMPLEX}, its real part
is truncated and converted, and its imaginary part is disgregarded.

@xref{Int Intrinsic}.

The precise meaning of this intrinsic might change
in a future version of the GNU Fortran language,
as more is learned about how it is used.
")

DEFDOC (LEN, "Length of character entity.", "\
Returns the length of @var{@1@}.

If @var{@1@} is an array, the length of an element
of @var{@1@} is returned.

Note that @var{@1@} need not be defined when this
intrinsic is invoked, since only the length, not
the content, of @var{@1@} is needed.

@xref{Bit_Size Intrinsic}, for the function that determines
the size of its argument in bits.
")

DEFDOC (TAN, "Tangent.", "\
Returns the tangent of @var{@1@}, an angle measured
in radians.

@xref{ATan Intrinsic}, for the inverse of this function.
")

DEFDOC (DTAN, "Tangent (archaic).", ARCHAIC (TAN, Tan))

DEFDOC (TANH, "Hyperbolic tangent.", "\
Returns the hyperbolic tangent of @var{@1@}.
")

DEFDOC (DTANH, "Hyperbolic tangent (archaic).", ARCHAIC (TANH, TanH))

DEFDOC (SNGL, "Convert (archaic).", ARCHAIC (REAL, Real))

DEFDOC (SIN, "Sine.", "\
Returns the sine of @var{@1@}, an angle measured
in radians.

@xref{ASin Intrinsic}, for the inverse of this function.
")

DEFDOC (CSIN, "Sine (archaic).", ARCHAIC (SIN, Sin))

DEFDOC (DSIN, "Sine (archaic).", ARCHAIC (SIN, Sin))

DEFDOC (CDSIN, "Sine (archaic).", ARCHAIC (SIN, Sin))

DEFDOC (SINH, "Hyperbolic sine.", "\
Returns the hyperbolic sine of @var{@1@}.
")

DEFDOC (DSINH, "Hyperbolic sine (archaic).", ARCHAIC (SINH, SinH))

DEFDOC (LSHIFT, "Left-shift bits.", "\
Returns @var{@1@} shifted to the left
@var{@2@} bits.

Although similar to the expression
@samp{@var{@1@}*(2**@var{@2@})}, there
are important differences.
For example, the sign of the result is
not necessarily the same as the sign of
@var{@1@}.

Currently this intrinsic is defined assuming
the underlying representation of @var{@1@}
is as a two's-complement integer.
It is unclear at this point whether that
definition will apply when a different
representation is involved.

@xref{LShift Intrinsic}, for the inverse of this function.

@xref{IShft Intrinsic}, for information
on a more widely available left-shifting
intrinsic that is also more precisely defined.
")

DEFDOC (RSHIFT, "Right-shift bits.", "\
Returns @var{@1@} shifted to the right
@var{@2@} bits.

Although similar to the expression
@samp{@var{@1@}/(2**@var{@2@})}, there
are important differences.
For example, the sign of the result is
undefined.

Currently this intrinsic is defined assuming
the underlying representation of @var{@1@}
is as a two's-complement integer.
It is unclear at this point whether that
definition will apply when a different
representation is involved.

@xref{RShift Intrinsic}, for the inverse of this function.

@xref{IShft Intrinsic}, for information
on a more widely available right-shifting
intrinsic that is also more precisely defined.
")

DEFDOC (LGE, "Lexically greater than or equal.", "\
Returns @samp{.TRUE.} if @samp{@var{@1@}.GE.@var{@2@}},
@samp{.FALSE.} otherwise.
@var{@1@} and @var{@2@} are interpreted as containing
ASCII character codes.
If either value contains a character not in the ASCII
character set, the result is processor dependent.

If the @var{@1@} and @var{@2@} are not the same length,
the shorter is compared as if spaces were appended to
it to form a value that has the same length as the longer.

The lexical comparison intrinsics @code{LGe}, @code{LGt},
@code{LLe}, and @code{LLt} differ from the corresponding
intrinsic operators @code{.GE.}, @code{.GT.},
@code{.LE.}, @code{.LT.}.
Because the ASCII collating sequence is assumed,
the following expressions always return @samp{.TRUE.}:

@smallexample
LGE ('0', ' ')
LGE ('A', '0')
LGE ('a', 'A')
@end smallexample

The following related expressions do @emph{not} always
return @samp{.TRUE.}, as they are not necessarily evaluated
assuming the arguments use ASCII encoding:

@smallexample
'0' .GE. ' '
'A' .GE. '0'
'a' .GE. 'A'
@end smallexample

The same difference exists
between @code{LGt} and @code{.GT.};
between @code{LLe} and @code{.LE.}; and
between @code{LLt} and @code{.LT.}.
")

DEFDOC (LGT, "Lexically greater than.", "\
Returns @samp{.TRUE.} if @samp{@var{@1@}.GT.@var{@2@}},
@samp{.FALSE.} otherwise.
@var{@1@} and @var{@2@} are interpreted as containing
ASCII character codes.
If either value contains a character not in the ASCII
character set, the result is processor dependent.

If the @var{@1@} and @var{@2@} are not the same length,
the shorter is compared as if spaces were appended to
it to form a value that has the same length as the longer.

@xref{LGe Intrinsic}, for information on the distinction
between the @code{@0@} intrinsic and the @code{.GT.}
operator.
")

DEFDOC (LLE, "Lexically less than or equal.", "\
Returns @samp{.TRUE.} if @samp{@var{@1@}.LE.@var{@2@}},
@samp{.FALSE.} otherwise.
@var{@1@} and @var{@2@} are interpreted as containing
ASCII character codes.
If either value contains a character not in the ASCII
character set, the result is processor dependent.

If the @var{@1@} and @var{@2@} are not the same length,
the shorter is compared as if spaces were appended to
it to form a value that has the same length as the longer.

@xref{LGe Intrinsic}, for information on the distinction
between the @code{@0@} intrinsic and the @code{.LE.}
operator.
")

DEFDOC (LLT, "Lexically less than.", "\
Returns @samp{.TRUE.} if @samp{@var{@1@}.LT.@var{@2@}},
@samp{.FALSE.} otherwise.
@var{@1@} and @var{@2@} are interpreted as containing
ASCII character codes.
If either value contains a character not in the ASCII
character set, the result is processor dependent.

If the @var{@1@} and @var{@2@} are not the same length,
the shorter is compared as if spaces were appended to
it to form a value that has the same length as the longer.

@xref{LGe Intrinsic}, for information on the distinction
between the @code{@0@} intrinsic and the @code{.LT.}
operator.
")

DEFDOC (SIGN, "Apply sign to magnitude.", "\
Returns @samp{ABS(@var{@1@})*@var{s}}, where
@var{s} is +1 if @samp{@var{@2@}.GE.0},
-1 otherwise.

@xref{Abs Intrinsic}, for the function that returns
the magnitude of a value.
")

DEFDOC (DSIGN, "Apply sign to magnitude (archaic).", ARCHAIC_2 (SIGN, Sign))
DEFDOC (ISIGN, "Apply sign to magnitude (archaic).", ARCHAIC_2 (ISIGN, ISign))

DEFDOC (REAL, "Convert value to type @code{REAL(KIND=1)}.", "\
Converts @var{@1@} to @code{REAL(KIND=1)}.

Use of @code{@0@()} with a @code{COMPLEX} argument
(other than @code{COMPLEX(KIND=1)}) is restricted to the following case:

@example
REAL(REAL(@1@))
@end example

@noindent
This expression converts the real part of @1@ to
@code{REAL(KIND=1)}.

@xref{RealPart Intrinsic}, for information on a GNU Fortran
intrinsic that extracts the real part of an arbitrary
@code{COMPLEX} value.

@xref{REAL() and AIMAG() of Complex}, for more information.
")

DEFDOC (DREAL, "Convert value to type @code{REAL(KIND=2)}.", "\
Converts @var{@1@} to @code{REAL(KIND=2)}.

If @var{@1@} is type @code{COMPLEX}, its real part
is converted (if necessary) to @code{REAL(KIND=2)},
and its imaginary part is disregarded.

Although this intrinsic is not standard Fortran,
it is a popular extension offered by many compilers
that support @code{DOUBLE COMPLEX}, since it offers
the easiest way to extract the real part of a @code{DOUBLE COMPLEX}
value without using the Fortran 90 @code{REAL()} intrinsic
in a way that produces a return value inconsistent with
the way many FORTRAN 77 compilers handle @code{REAL()} of
a @code{DOUBLE COMPLEX} value.

@xref{RealPart Intrinsic}, for information on a GNU Fortran
intrinsic that avoids these areas of confusion.

@xref{REAL() and AIMAG() of Complex}, for more information on
this issue.
")

DEFDOC (IMAGPART, "Extract imaginary part of complex.", "\
The imaginary part of @var{@1@} is returned, without conversion.

@emph{Note:} The way to do this in standard Fortran 90
is @samp{AIMAG(@var{@1@})}.
However, when, for example, @var{@1@} is @code{DOUBLE COMPLEX},
@samp{AIMAG(@var{@1@})} means something different for some compilers
that are not true Fortran 90 compilers but offer some
extensions standardized by Fortran 90 (such as the
@code{DOUBLE COMPLEX} type, also known as @code{COMPLEX(KIND=2)}).

The advantage of @code{@0@()} is that, while not necessarily
more or less portable than @code{AIMAG()}, it is more likely to
cause a compiler that doesn't support it to produce a diagnostic
than generate incorrect code.

@xref{REAL() and AIMAG() of Complex}, for more information.
")

DEFDOC (COMPLEX, "Build complex value from real and@99@imaginary parts.", "\
Returns a @code{COMPLEX} value that has @samp{@1@} and @samp{@2@} as its
real and imaginary parts, respectively.

If @var{@1@} and @var{@2@} are the same type, and that type is not
@code{INTEGER}, no data conversion is performed, and the type of
the resulting value has the same kind value as the types
of @var{@1@} and @var{@2@}.

If @var{@1@} and @var{@2@} are not the same type, the usual type-promotion
rules are applied to both, converting either or both to the
appropriate @code{REAL} type.
The type of the resulting value has the same kind value as the
type to which both @var{@1@} and @var{@2@} were converted, in this case.

If @var{@1@} and @var{@2@} are both @code{INTEGER}, they are both converted
to @code{REAL(KIND=1)}, and the result of the @code{@0@()}
invocation is type @code{COMPLEX(KIND=1)}.

@emph{Note:} The way to do this in standard Fortran 90
is too hairy to describe here, but it is important to
note that @samp{CMPLX(D1,D2)} returns a @code{COMPLEX(KIND=1)}
result even if @samp{D1} and @samp{D2} are type @code{REAL(KIND=2)}.
Hence the availability of @code{COMPLEX()} in GNU Fortran.
")

DEFDOC (LOC, "Address of entity in core.", "\
The @code{LOC()} intrinsic works the
same way as the @code{%LOC()} construct.
@xref{%LOC(),,The @code{%LOC()} Construct}, for
more information.
")

DEFDOC (REALPART, "Extract real part of complex.", "\
The real part of @var{@1@} is returned, without conversion.

@emph{Note:} The way to do this in standard Fortran 90
is @samp{REAL(@var{@1@})}.
However, when, for example, @var{@1@} is @code{COMPLEX(KIND=2)},
@samp{REAL(@var{@1@})} means something different for some compilers
that are not true Fortran 90 compilers but offer some
extensions standardized by Fortran 90 (such as the
@code{DOUBLE COMPLEX} type, also known as @code{COMPLEX(KIND=2)}).

The advantage of @code{@0@()} is that, while not necessarily
more or less portable than @code{REAL()}, it is more likely to
cause a compiler that doesn't support it to produce a diagnostic
than generate incorrect code.

@xref{REAL() and AIMAG() of Complex}, for more information.
")

DEFDOC (GETARG, "Obtain command-line argument.", "\
Sets @var{@2@} to the @var{@1@}-th command-line argument (or to all
blanks if there are fewer than @var{@2@} command-line arguments);
@code{CALL @0@(0, @var{value})} sets @var{value} to the name of the
program (on systems that support this feature).

@xref{IArgC Intrinsic}, for information on how to get the number
of arguments.
")

DEFDOC (ABORT, "Abort the program.", "\
Prints a message and potentially causes a core dump via @code{abort(3)}.
")

DEFDOC (EXIT, "Terminate the program.", "\
Exit the program with status @var{@1@} after closing open Fortran
I/O units and otherwise behaving as @code{exit(2)}.
If @var{@1@} is omitted the canonical `success' value
will be returned to the system.
")

DEFDOC (IARGC, "Obtain count of command-line arguments.", "\
Returns the number of command-line arguments.

This count does not include the specification of the program
name itself.
")

DEFDOC (CTIME_func, "Convert time to Day Mon dd hh:mm:ss yyyy.", "\
Converts @var{@1@}, a system time value, such as returned by
@code{TIME8()}, to a string of the form @samp{Sat Aug 19 18:13:14 1995},
and returns that string as the function value.

@xref{Time8 Intrinsic}.
")

DEFDOC (CTIME_subr, "Convert time to Day Mon dd hh:mm:ss yyyy.", "\
Converts @var{@2@}, a system time value, such as returned by
@code{TIME8()}, to a string of the form @samp{Sat Aug 19 18:13:14 1995},
and returns that string in @var{@1@}.

@xref{Time8 Intrinsic}.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine.
")

DEFDOC (DATE, "Get current date as dd-Mon-yy.", "\
Returns @var{@1@} in the form @samp{@var{dd}-@var{mmm}-@var{yy}},
representing the numeric day of the month @var{dd}, a three-character
abbreviation of the month name @var{mmm} and the last two digits of
the year @var{yy}, e.g.@ @samp{25-Nov-96}.

This intrinsic is not recommended, due to the year 2000 approaching.
@xref{CTime Intrinsic (subroutine)}, for information on obtaining more digits
for the current (or any) date.
")

DEFDOC (DTIME_func, "Get elapsed time since last time.", "\
Initially, return the number of seconds of runtime
since the start of the process's execution
as the function value,
and the user and system components of this in @samp{@var{@1@}(1)}
and @samp{@var{@1@}(2)} respectively.
The functions' value is equal to @samp{@var{@1@}(1) + @var{@1@}(2)}.

Subsequent invocations of @samp{@0@()} return values accumulated since the
previous invocation.

Due to the side effects performed by this intrinsic, the function
form is not recommended.
")

DEFDOC (DTIME_subr, "Get elapsed time since last time.", "\
Initially, return the number of seconds of runtime
since the start of the process's execution
in @var{@1@},
and the user and system components of this in @samp{@var{@2@}(1)}
and @samp{@var{@2@}(2)} respectively.
The value of @var{@1@} is equal to @samp{@var{@2@}(1) + @var{@2@}(2)}.

Subsequent invocations of @samp{@0@()} set values based on accumulations
since the previous invocation.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine.
")

DEFDOC (ETIME_func, "Get elapsed time for process.", "\
Return the number of seconds of runtime
since the start of the process's execution
as the function value,
and the user and system components of this in @samp{@var{@1@}(1)}
and @samp{@var{@1@}(2)} respectively.
The functions' value is equal to @samp{@var{@1@}(1) + @var{@1@}(2)}.
")

DEFDOC (ETIME_subr, "Get elapsed time for process.", "\
Return the number of seconds of runtime
since the start of the process's execution
in @var{@1@},
and the user and system components of this in @samp{@var{@2@}(1)}
and @samp{@var{@2@}(2)} respectively.
The value of @var{@1@} is equal to @samp{@var{@2@}(1) + @var{@2@}(2)}.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine.
")

DEFDOC (FDATE_func, "Get current time as Day Mon dd hh:mm:ss yyyy.", "\
Returns the current date (using the same format as @code{CTIME()}).

Equivalent to:

@example
CTIME(TIME8())
@end example

@xref{CTime Intrinsic (function)}.
")

DEFDOC (FDATE_subr, "Get current time as Day Mon dd hh:mm:ss yyyy.", "\
Returns the current date (using the same format as @code{CTIME()})
in @var{@1@}.

Equivalent to:

@example
CALL CTIME(@var{@1@}, TIME8())
@end example

@xref{CTime Intrinsic (subroutine)}.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine.
")

DEFDOC (GMTIME, "Convert time to GMT time info.", "\
Given a system time value @var{@1@}, fills @var{@2@} with values
extracted from it appropriate to the GMT time zone using
@code{gmtime(3)}.

The array elements are as follows:

@enumerate
@item
Seconds after the minute, range 0--59 or 0--61 to allow for leap
seconds

@item
Minutes after the hour, range 0--59

@item
Hours past midnight, range 0--23

@item
Day of month, range 0--31

@item
Number of months since January, range 0--12

@item
Years since 1900

@item
Number of days since Sunday, range 0--6

@item
Days since January 1

@item
Daylight savings indicator: positive if daylight savings is in effect,
zero if not, and negative if the information isn't available.
@end enumerate
")

DEFDOC (LTIME, "Convert time to local time info.", "\
Given a system time value @var{@1@}, fills @var{@2@} with values
extracted from it appropriate to the GMT time zone using
@code{localtime(3)}.

The array elements are as follows:

@enumerate
@item
Seconds after the minute, range 0--59 or 0--61 to allow for leap
seconds

@item
Minutes after the hour, range 0--59

@item
Hours past midnight, range 0--23

@item
Day of month, range 0--31

@item
Number of months since January, range 0--12

@item
Years since 1900

@item
Number of days since Sunday, range 0--6

@item
Days since January 1

@item
Daylight savings indicator: positive if daylight savings is in effect,
zero if not, and negative if the information isn't available.
@end enumerate
")

DEFDOC (IDATE_unix, "Get local time info.", "\
Fills @var{@1@} with the numerical values at the current local time
of day, month (in the range 1--12), and year in elements 1, 2, and 3,
respectively.
The year has four significant digits.
")

DEFDOC (IDATE_vxt, "Get local time info (VAX/VMS).", "\
Returns the numerical values of the current local time.
The month (in the range 1--12) is returned in @var{@1@},
the day (in the range 1--7) in @var{@2@},
and the year in @var{@3@} (in the range 0--99).

This intrinsic is not recommended, due to the year 2000 approaching.
")

DEFDOC (ITIME, "Get local time of day.", "\
Returns the current local time hour, minutes, and seconds in elements
1, 2, and 3 of @var{@1@}, respectively.
")

DEFDOC (MCLOCK, "Get number of clock ticks for process.", "\
Returns the number of clock ticks since the start of the process.
Supported on systems with @code{clock(3)} (q.v.).

This intrinsic is not fully portable, such as to systems
with 32-bit @code{INTEGER} types but supporting times
wider than 32 bits.
@xref{MClock8 Intrinsic}, for information on a
similar intrinsic that might be portable to more
GNU Fortran implementations, though to fewer
Fortran compilers.

If the system does not support @code{clock(3)},
-1 is returned.
")

DEFDOC (MCLOCK8, "Get number of clock ticks for process.", "\
Returns the number of clock ticks since the start of the process.
Supported on systems with @code{clock(3)} (q.v.).

No Fortran implementations other than GNU Fortran are
known to support this intrinsic at the time of this
writing.
@xref{MClock Intrinsic}, for information on a
similar intrinsic that might be portable to more Fortran
compilers, though to fewer GNU Fortran implementations.

If the system does not support @code{clock(3)},
-1 is returned.
")

DEFDOC (SECNDS, "Get local time offset since midnight.", "\
Returns the local time in seconds since midnight minus the value
@var{@1@}.
")

DEFDOC (SECOND_func, "Get CPU time for process in seconds.", "\
Returns the process's runtime in seconds---the same value as the
UNIX function @code{etime} returns.

This routine is known from Cray Fortran.
")

DEFDOC (SECOND_subr, "Get CPU time for process@99@in seconds.", "\
Returns the process's runtime in seconds in @var{@1@}---the same value
as the UNIX function @code{etime} returns.

This routine is known from Cray Fortran.  @xref{Cpu_Time Intrinsic}
for a standard equivalent.
")

DEFDOC (SYSTEM_CLOCK, "Get current system clock value.", "\
Returns in @var{@1@} the current value of the system clock; this is
the value returned by the UNIX function @code{times(2)}
in this implementation, but
isn't in general.
@var{@2@} is the number of clock ticks per second and
@var{@3@} is the maximum value this can take, which isn't very useful
in this implementation since it's just the maximum C @code{unsigned
int} value.
")

DEFDOC (CPU_TIME, "Get current CPU time.", "\
Returns in @var{@1@} the current value of the system time.
This implementation of the Fortran 95 intrinsic is just an alias for
@code{second} @xref{Second Intrinsic (subroutine)}.
")

DEFDOC (TIME8, "Get current time as time value.", "\
Returns the current time encoded as a long integer
(in the manner of the UNIX function @code{time(3)}).
This value is suitable for passing to @code{CTIME},
@code{GMTIME}, and @code{LTIME}.

No Fortran implementations other than GNU Fortran are
known to support this intrinsic at the time of this
writing.
@xref{Time Intrinsic (UNIX)}, for information on a
similar intrinsic that might be portable to more Fortran
compilers, though to fewer GNU Fortran implementations.
")

DEFDOC (TIME_unix, "Get current time as time value.", "\
Returns the current time encoded as an integer
(in the manner of the UNIX function @code{time(3)}).
This value is suitable for passing to @code{CTIME},
@code{GMTIME}, and @code{LTIME}.

This intrinsic is not fully portable, such as to systems
with 32-bit @code{INTEGER} types but supporting times
wider than 32 bits.
@xref{Time8 Intrinsic}, for information on a
similar intrinsic that might be portable to more
GNU Fortran implementations, though to fewer
Fortran compilers.
")

#define BES(num,n,val) "\
Calculates the Bessel function of the " #num " kind of \
order " #n " of @var{@" #val "@}.\n\
See @code{bessel(3m)}, on whose implementation the \
function depends.\
"

DEFDOC (BESJ0, "Bessel function.", BES (first, 0, 1))
DEFDOC (BESJ1, "Bessel function.", BES (first, 1, 1))
DEFDOC (BESJN, "Bessel function.", BES (first, @var{N}, 2))
DEFDOC (BESY0, "Bessel function.", BES (second, 0, 1))
DEFDOC (BESY1, "Bessel function.", BES (second, 1, 1))
DEFDOC (BESYN, "Bessel function.", BES (second, @var{N}, 2))
DEFDOC (DBESJ0, "Bessel function (archaic).", ARCHAIC (BESJ0, BesJ0))
DEFDOC (DBESJ1, "Bessel function (archaic).", ARCHAIC (BESJ1, BesJ1))
DEFDOC (DBESJN, "Bessel function (archaic).", ARCHAIC_2nd (BESJN, BesJN))
DEFDOC (DBESY0, "Bessel function (archaic).", ARCHAIC (BESY0, BesY0))
DEFDOC (DBESY1, "Bessel function (archaic).", ARCHAIC (BESY1, BesY1))
DEFDOC (DBESYN, "Bessel function (archaic).", ARCHAIC_2nd (BESYN, BesYN))

DEFDOC (ERF, "Error function.", "\
Returns the error function of @var{@1@}.
See @code{erf(3m)}, which provides the implementation.
")

DEFDOC (ERFC, "Complementary error function.", "\
Returns the complementary error function of @var{@1@}:
@samp{ERFC(R) = 1 - ERF(R)} (except that the result may be more
accurate than explicitly evaluating that formulae would give).
See @code{erfc(3m)}, which provides the implementation.
")

DEFDOC (DERF, "Error function (archaic).", ARCHAIC (ERF, ErF))
DEFDOC (DERFC, "Complementary error function (archaic).", ARCHAIC (ERFC, ErFC))

DEFDOC (IRAND, "Random number.", "\
Returns a uniform quasi-random number up to a system-dependent limit.
If @var{@1@} is 0, the next number in sequence is returned; if
@var{@1@} is 1, the generator is restarted by calling the UNIX function
@samp{srand(0)}; if @var{@1@} has any other value,
it is used as a new seed with @code{srand()}.

@xref{SRand Intrinsic}.

@emph{Note:} As typically implemented (by the routine of the same
name in the C library), this random number generator is a very poor
one, though the BSD and GNU libraries provide a much better
implementation than the `traditional' one.
On a different system you almost certainly want to use something better.
")

DEFDOC (RAND, "Random number.", "\
Returns a uniform quasi-random number between 0 and 1.
If @var{@1@} is 0, the next number in sequence is returned; if
@var{@1@} is 1, the generator is restarted by calling @samp{srand(0)};
if @var{@1@} has any other value, it is used as a new seed with
@code{srand}.

@xref{SRand Intrinsic}.

@emph{Note:} As typically implemented (by the routine of the same
name in the C library), this random number generator is a very poor
one, though the BSD and GNU libraries provide a much better
implementation than the `traditional' one.
On a different system you
almost certainly want to use something better.
")

DEFDOC (SRAND, "Random seed.", "\
Reinitialises the generator with the seed in @var{@1@}.
@xref{IRand Intrinsic}.
@xref{Rand Intrinsic}.
")

DEFDOC (ACCESS, "Check file accessibility.", "\
Checks file @var{@1@} for accessibility in the mode specified by @var{@2@} and
returns 0 if the file is accessible in that mode, otherwise an error
code if the file is inaccessible or @var{@2@} is invalid.
See @code{access(2)}.
A null character (@samp{CHAR(0)}) marks the end of
the name in @var{@1@}---otherwise,
trailing blanks in @var{@1@} are ignored.
@var{@2@} may be a concatenation of any of the following characters:

@table @samp
@item r
Read permission

@item w
Write permission

@item x
Execute permission

@item @kbd{SPC}
Existence
@end table
")

DEFDOC (CHDIR_subr, "Change directory.", "\
Sets the current working directory to be @var{@1@}.
If the @var{@2@} argument is supplied, it contains 0
on success or a non-zero error code otherwise upon return.
See @code{chdir(3)}.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@2@} argument.
")

DEFDOC (CHDIR_func, "Change directory.", "\
Sets the current working directory to be @var{@1@}.
Returns 0 on success or a non-zero error code.
See @code{chdir(3)}.

Due to the side effects performed by this intrinsic, the function
form is not recommended.
")

DEFDOC (CHMOD_func, "Change file modes.", "\
Changes the access mode of file @var{@1@} according to the
specification @var{@2@}, which is given in the format of
@code{chmod(1)}.
A null character (@samp{CHAR(0)}) marks the end of
the name in @var{@1@}---otherwise,
trailing blanks in @var{@1@} are ignored.
Currently, @var{@1@} must not contain the single quote
character.

Returns 0 on success or a non-zero error code otherwise.

Note that this currently works
by actually invoking @code{/bin/chmod} (or the @code{chmod} found when
the library was configured) and so may fail in some circumstances and
will, anyway, be slow.

Due to the side effects performed by this intrinsic, the function
form is not recommended.
")

DEFDOC (CHMOD_subr, "Change file modes.", "\
Changes the access mode of file @var{@1@} according to the
specification @var{@2@}, which is given in the format of
@code{chmod(1)}.
A null character (@samp{CHAR(0)}) marks the end of
the name in @var{@1@}---otherwise,
trailing blanks in @var{@1@} are ignored.
Currently, @var{@1@} must not contain the single quote
character.

If the @var{@3@} argument is supplied, it contains
0 on success or a non-zero error code upon return.

Note that this currently works
by actually invoking @code{/bin/chmod} (or the @code{chmod} found when
the library was configured) and so may fail in some circumstances and
will, anyway, be slow.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@3@} argument.
")

DEFDOC (GETCWD_func, "Get current working directory.", "\
Places the current working directory in @var{@1@}.
Returns 0 on
success, otherwise a non-zero error code
(@code{ENOSYS} if the system does not provide @code{getcwd(3)}
or @code{getwd(3)}).
")

DEFDOC (GETCWD_subr, "Get current working directory.", "\
Places the current working directory in @var{@1@}.
If the @var{@2@} argument is supplied, it contains 0
success or a non-zero error code upon return
(@code{ENOSYS} if the system does not provide @code{getcwd(3)}
or @code{getwd(3)}).

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@2@} argument.
")

DEFDOC (FSTAT_func, "Get file information.", "\
Obtains data about the file open on Fortran I/O unit @var{@1@} and
places them in the array @var{@2@}.
The values in this array are
extracted from the @code{stat} structure as returned by
@code{fstat(2)} q.v., as follows:

@enumerate
@item
File mode

@item
Inode number

@item
ID of device containing directory entry for file

@item
Device id (if relevant)

@item
Number of links

@item
Owner's uid

@item
Owner's gid

@item
File size (bytes)

@item
Last access time

@item
Last modification time

@item
Last file status change time

@item
Preferred I/O block size

@item
Number of blocks allocated
@end enumerate

Not all these elements are relevant on all systems.
If an element is not relevant, it is returned as 0.

Returns 0 on success or a non-zero error code.
")

DEFDOC (FSTAT_subr, "Get file information.", "\
Obtains data about the file open on Fortran I/O unit @var{@1@} and
places them in the array @var{@2@}.
The values in this array are
extracted from the @code{stat} structure as returned by
@code{fstat(2)} q.v., as follows:

@enumerate
@item
File mode

@item
Inode number

@item
ID of device containing directory entry for file

@item
Device id (if relevant)

@item
Number of links

@item
Owner's uid

@item
Owner's gid

@item
File size (bytes)

@item
Last access time

@item
Last modification time

@item
Last file status change time

@item
Preferred I/O block size

@item
Number of blocks allocated
@end enumerate

Not all these elements are relevant on all systems.
If an element is not relevant, it is returned as 0.

If the @var{@3@} argument is supplied, it contains
0 on success or a non-zero error code upon return.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@3@} argument.
")

DEFDOC (LSTAT_func, "Get file information.", "\
Obtains data about the given file @var{@1@} and places them in the array
@var{@2@}.
A null character (@samp{CHAR(0)}) marks the end of
the name in @var{@1@}---otherwise,
trailing blanks in @var{@1@} are ignored.
If @var{@1@} is a symbolic link it returns data on the
link itself, so the routine is available only on systems that support
symbolic links.
The values in this array are extracted from the
@code{stat} structure as returned by @code{fstat(2)} q.v., as follows:

@enumerate
@item
File mode

@item
Inode number

@item
ID of device containing directory entry for file

@item
Device id (if relevant)

@item
Number of links

@item
Owner's uid

@item
Owner's gid

@item
File size (bytes)

@item
Last access time

@item
Last modification time

@item
Last file status change time

@item
Preferred I/O block size

@item
Number of blocks allocated
@end enumerate

Not all these elements are relevant on all systems.
If an element is not relevant, it is returned as 0.

Returns 0 on success or a non-zero error code
(@code{ENOSYS} if the system does not provide @code{lstat(2)}).
")

DEFDOC (LSTAT_subr, "Get file information.", "\
Obtains data about the given file @var{@1@} and places them in the array
@var{@2@}.
A null character (@samp{CHAR(0)}) marks the end of
the name in @var{@1@}---otherwise,
trailing blanks in @var{@1@} are ignored.
If @var{@1@} is a symbolic link it returns data on the
link itself, so the routine is available only on systems that support
symbolic links.
The values in this array are extracted from the
@code{stat} structure as returned by @code{fstat(2)} q.v., as follows:

@enumerate
@item
File mode

@item
Inode number

@item
ID of device containing directory entry for file

@item
Device id (if relevant)

@item
Number of links

@item
Owner's uid

@item
Owner's gid

@item
File size (bytes)

@item
Last access time

@item
Last modification time

@item
Last file status change time

@item
Preferred I/O block size

@item
Number of blocks allocated
@end enumerate

Not all these elements are relevant on all systems.
If an element is not relevant, it is returned as 0.

If the @var{@3@} argument is supplied, it contains
0 on success or a non-zero error code upon return
(@code{ENOSYS} if the system does not provide @code{lstat(2)}).

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@3@} argument.
")

DEFDOC (STAT_func, "Get file information.", "\
Obtains data about the given file @var{@1@} and places them in the array
@var{@2@}.
A null character (@samp{CHAR(0)}) marks the end of
the name in @var{@1@}---otherwise,
trailing blanks in @var{@1@} are ignored.
The values in this array are extracted from the
@code{stat} structure as returned by @code{fstat(2)} q.v., as follows:

@enumerate
@item
File mode

@item
Inode number

@item
ID of device containing directory entry for file

@item
Device id (if relevant)

@item
Number of links

@item
Owner's uid

@item
Owner's gid

@item
File size (bytes)

@item
Last access time

@item
Last modification time

@item
Last file status change time

@item
Preferred I/O block size

@item
Number of blocks allocated
@end enumerate

Not all these elements are relevant on all systems.
If an element is not relevant, it is returned as 0.

Returns 0 on success or a non-zero error code.
")

DEFDOC (STAT_subr, "Get file information.", "\
Obtains data about the given file @var{@1@} and places them in the array
@var{@2@}.
A null character (@samp{CHAR(0)}) marks the end of
the name in @var{@1@}---otherwise,
trailing blanks in @var{@1@} are ignored.
The values in this array are extracted from the
@code{stat} structure as returned by @code{fstat(2)} q.v., as follows:

@enumerate
@item
File mode

@item
Inode number

@item
ID of device containing directory entry for file

@item
Device id (if relevant)

@item
Number of links

@item
Owner's uid

@item
Owner's gid

@item
File size (bytes)

@item
Last access time

@item
Last modification time

@item
Last file status change time

@item
Preferred I/O block size

@item
Number of blocks allocated
@end enumerate

Not all these elements are relevant on all systems.
If an element is not relevant, it is returned as 0.

If the @var{@3@} argument is supplied, it contains
0 on success or a non-zero error code upon return.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@3@} argument.
")

DEFDOC (LINK_subr, "Make hard link in file system.", "\
Makes a (hard) link from file @var{@1@} to @var{@2@}.
A null character (@samp{CHAR(0)}) marks the end of
the names in @var{@1@} and @var{@2@}---otherwise,
trailing blanks in @var{@1@} and @var{@2@} are ignored.
If the @var{@3@} argument is supplied, it contains
0 on success or a non-zero error code upon return.
See @code{link(2)}.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@3@} argument.
")

DEFDOC (LINK_func, "Make hard link in file system.", "\
Makes a (hard) link from file @var{@1@} to @var{@2@}.
A null character (@samp{CHAR(0)}) marks the end of
the names in @var{@1@} and @var{@2@}---otherwise,
trailing blanks in @var{@1@} and @var{@2@} are ignored.
Returns 0 on success or a non-zero error code.
See @code{link(2)}.

Due to the side effects performed by this intrinsic, the function
form is not recommended.
")

DEFDOC (SYMLNK_subr, "Make symbolic link in file system.", "\
Makes a symbolic link from file @var{@1@} to @var{@2@}.
A null character (@samp{CHAR(0)}) marks the end of
the names in @var{@1@} and @var{@2@}---otherwise,
trailing blanks in @var{@1@} and @var{@2@} are ignored.
If the @var{@3@} argument is supplied, it contains
0 on success or a non-zero error code upon return
(@code{ENOSYS} if the system does not provide @code{symlink(2)}).

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@3@} argument.
")

DEFDOC (SYMLNK_func, "Make symbolic link in file system.", "\
Makes a symbolic link from file @var{@1@} to @var{@2@}.
A null character (@samp{CHAR(0)}) marks the end of
the names in @var{@1@} and @var{@2@}---otherwise,
trailing blanks in @var{@1@} and @var{@2@} are ignored.
Returns 0 on success or a non-zero error code
(@code{ENOSYS} if the system does not provide @code{symlink(2)}).

Due to the side effects performed by this intrinsic, the function
form is not recommended.
")

DEFDOC (RENAME_subr, "Rename file.", "\
Renames the file @var{@1@} to @var{@2@}.
A null character (@samp{CHAR(0)}) marks the end of
the names in @var{@1@} and @var{@2@}---otherwise,
trailing blanks in @var{@1@} and @var{@2@} are ignored.
See @code{rename(2)}.
If the @var{@3@} argument is supplied, it contains
0 on success or a non-zero error code upon return.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@3@} argument.
")

DEFDOC (RENAME_func, "Rename file.", "\
Renames the file @var{@1@} to @var{@2@}.
A null character (@samp{CHAR(0)}) marks the end of
the names in @var{@1@} and @var{@2@}---otherwise,
trailing blanks in @var{@1@} and @var{@2@} are ignored.
See @code{rename(2)}.
Returns 0 on success or a non-zero error code.

Due to the side effects performed by this intrinsic, the function
form is not recommended.
")

DEFDOC (UMASK_subr, "Set file creation permissions mask.", "\
Sets the file creation mask to @var{@1@} and returns the old value in
argument @var{@2@} if it is supplied.
See @code{umask(2)}.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine.
")

DEFDOC (UMASK_func, "Set file creation permissions mask.", "\
Sets the file creation mask to @var{@1@} and returns the old value.
See @code{umask(2)}.

Due to the side effects performed by this intrinsic, the function
form is not recommended.
")

DEFDOC (UNLINK_subr, "Unlink file.", "\
Unlink the file @var{@1@}.
A null character (@samp{CHAR(0)}) marks the end of
the name in @var{@1@}---otherwise,
trailing blanks in @var{@1@} are ignored.
If the @var{@2@} argument is supplied, it contains
0 on success or a non-zero error code upon return.
See @code{unlink(2)}.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@2@} argument.
")

DEFDOC (UNLINK_func, "Unlink file.", "\
Unlink the file @var{@1@}.
A null character (@samp{CHAR(0)}) marks the end of
the name in @var{@1@}---otherwise,
trailing blanks in @var{@1@} are ignored.
Returns 0 on success or a non-zero error code.
See @code{unlink(2)}.

Due to the side effects performed by this intrinsic, the function
form is not recommended.
")

DEFDOC (GERROR, "Get error message for last error.", "\
Returns the system error message corresponding to the last system
error (C @code{errno}).
")

DEFDOC (IERRNO, "Get error number for last error.", "\
Returns the last system error number (corresponding to the C
@code{errno}).
")

DEFDOC (PERROR, "Print error message for last error.", "\
Prints (on the C @code{stderr} stream) a newline-terminated error
message corresponding to the last system error.
This is prefixed by @var{@1@}, a colon and a space.
See @code{perror(3)}.
")
 
DEFDOC (GETGID, "Get process group id.", "\
Returns the group id for the current process.
")
 
DEFDOC (GETUID, "Get process user id.", "\
Returns the user id for the current process.
")
 
DEFDOC (GETPID, "Get process id.", "\
Returns the process id for the current process.
")

DEFDOC (GETENV, "Get environment variable.", "\
Sets @var{@2@} to the value of environment variable given by the
value of @var{@1@} (@code{$name} in shell terms) or to blanks if
@code{$name} has not been set.
A null character (@samp{CHAR(0)}) marks the end of
the name in @var{@1@}---otherwise,
trailing blanks in @var{@1@} are ignored.
")

DEFDOC (GETLOG, "Get login name.", "\
Returns the login name for the process in @var{@1@}.
")

DEFDOC (HOSTNM_func, "Get host name.", "\
Fills @var{@1@} with the system's host name returned by
@code{gethostname(2)}, returning 0 on success or a non-zero error code
(@code{ENOSYS} if the system does not provide @code{gethostname(2)}).

This intrinsic is not available on all systems.
")

DEFDOC (HOSTNM_subr, "Get host name.", "\
Fills @var{@1@} with the system's host name returned by
@code{gethostname(2)}.
If the @var{@2@} argument is supplied, it contains
0 on success or a non-zero error code upon return
(@code{ENOSYS} if the system does not provide @code{gethostname(2)}).

This intrinsic is not available on all systems.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@2@} argument.
")

/* Fixme: stream I/O */

DEFDOC (FLUSH, "Flush buffered output.", "\
Flushes Fortran unit(s) currently open for output.
Without the optional argument, all such units are flushed,
otherwise just the unit specified by @var{@1@}.

Some non-GNU implementations of Fortran provide this intrinsic
as a library procedure that might or might not support the
(optional) @var{@1@} argument.
")

DEFDOC (FNUM, "Get file descriptor from Fortran unit number.", "\
Returns the Unix file descriptor number corresponding to the open
Fortran I/O unit @var{@1@}.
This could be passed to an interface to C I/O routines.
")

#define IOWARN "
Stream I/O should not be mixed with normal record-oriented (formatted or
unformatted) I/O on the same unit; the results are unpredictable.
"

DEFDOC (FGET_func, "Read a character from unit 5 stream-wise.", "\
Reads a single character into @var{@1@} in stream mode from unit 5
(by-passing normal formatted input) using @code{getc(3)}.
Returns 0 on
success, @minus{}1 on end-of-file, and the error code from
@code{ferror(3)} otherwise.
" IOWARN)

DEFDOC (FGET_subr, "Read a character from unit 5 stream-wise.", "\
Reads a single character into @var{@1@} in stream mode from unit 5
(by-passing normal formatted output) using @code{getc(3)}.
Returns in
@var{@2@} 0 on success, @minus{}1 on end-of-file, and the error code
from @code{ferror(3)} otherwise.
" IOWARN)

DEFDOC (FGETC_func, "Read a character stream-wise.", "\
Reads a single character into @var{@2@} in stream mode from unit @var{@1@}
(by-passing normal formatted output) using @code{getc(3)}.
Returns 0 on
success, @minus{}1 on end-of-file, and the error code from
@code{ferror(3)} otherwise.
" IOWARN)

DEFDOC (FGETC_subr, "Read a character stream-wise.", "\
Reads a single character into @var{@2@} in stream mode from unit @var{@1@}
(by-passing normal formatted output) using @code{getc(3)}.
Returns in
@var{@3@} 0 on success, @minus{}1 on end-of-file, and the error code from
@code{ferror(3)} otherwise.
" IOWARN)

DEFDOC (FPUT_func, "Write a character to unit 6 stream-wise.", "\
Writes the single character @var{@1@} in stream mode to unit 6
(by-passing normal formatted output) using @code{getc(3)}.
Returns 0 on
success, the error code from @code{ferror(3)} otherwise.
" IOWARN)

DEFDOC (FPUT_subr, "Write a character to unit 6 stream-wise.", "\
Writes the single character @var{@1@} in stream mode to unit 6
(by-passing normal formatted output) using @code{putc(3)}.
Returns in
@var{@2@} 0 on success, the error code from @code{ferror(3)} otherwise.
" IOWARN)

DEFDOC (FPUTC_func, "Write a character stream-wise.", "\
Writes the single character @var{@2@} in stream mode to unit @var{@1@}
(by-passing normal formatted output) using @code{putc(3)}.
Returns 0 on
success, the error code from @code{ferror(3)} otherwise.
" IOWARN)

DEFDOC (FPUTC_subr, "Write a character stream-wise.", "\
Writes the single character @var{@1@} in stream mode to unit 6
(by-passing normal formatted output) using @code{putc(3)}.
Returns in
@var{@2@} 0 on success, the error code from @code{ferror(3)} otherwise.
" IOWARN)

DEFDOC (FSEEK, "Position file (low-level).", "\
Attempts to move Fortran unit @var{@1@} to the specified
@var{Offset}: absolute offset if @var{@2@}=0; relative to the
current offset if @var{@2@}=1; relative to the end of the file if
@var{@2@}=2.
It branches to label @var{@3@} if @var{@1@} is
not open or if the call otherwise fails.
")

DEFDOC (FTELL_func, "Get file position (low-level).", "\
Returns the current offset of Fortran unit @var{@1@}
(or @minus{}1 if @var{@1@} is not open).
")

DEFDOC (FTELL_subr, "Get file position (low-level).", "\
Sets @var{@2@} to the current offset of Fortran unit @var{@1@}
(or to @minus{}1 if @var{@1@} is not open).

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine.
")

DEFDOC (ISATTY, "Is unit connected to a terminal?", "\
Returns @code{.TRUE.} if and only if the Fortran I/O unit
specified by @var{@1@} is connected
to a terminal device.
See @code{isatty(3)}.
")

DEFDOC (TTYNAM_func, "Get name of terminal device for unit.", "\
Returns the name of the terminal device open on logical unit
@var{@1@} or a blank string if @var{@1@} is not connected to a
terminal.
")

DEFDOC (TTYNAM_subr, "Get name of terminal device for unit.", "\
Sets @var{@1@} to the name of the terminal device open on logical unit
@var{@2@} or a blank string if @var{@2@} is not connected to a
terminal.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine.
")

DEFDOC (SIGNAL_subr, "Muck with signal handling.", "\
If @var{@2@} is a an @code{EXTERNAL} routine, arranges for it to be
invoked with a single integer argument (of system-dependent length)
when signal @var{@1@} occurs.
If @var{@1@} is an integer, it can be
used to turn off handling of signal @var{@2@} or revert to its default
action.
See @code{signal(2)}.

Note that @var{@2@} will be called using C conventions, so its value in
Fortran terms is obtained by applying @code{%LOC()} (or @var{LOC()}) to it.

The value returned by @code{signal(2)} is written to @var{@3@}, if
that argument is supplied.
Otherwise the return value is ignored.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@3@} argument.
")

DEFDOC (SIGNAL_func, "Muck with signal handling.", "\
If @var{@2@} is a an @code{EXTERNAL} routine, arranges for it to be
invoked with a single integer argument (of system-dependent length)
when signal @var{@1@} occurs.
If @var{@1@} is an integer, it can be
used to turn off handling of signal @var{@2@} or revert to its default
action.
See @code{signal(2)}.

Note that @var{@2@} will be called using C conventions, so its value in
Fortran terms is obtained by applying @code{%LOC()} (or @var{LOC()}) to it.

The value returned by @code{signal(2)} is returned.

Due to the side effects performed by this intrinsic, the function
form is not recommended.
")

DEFDOC (KILL_func, "Signal a process.", "\
Sends the signal specified by @var{@2@} to the process @var{@1@}.
Returns 0 on success or a non-zero error code.
See @code{kill(2)}.

Due to the side effects performed by this intrinsic, the function
form is not recommended.
")

DEFDOC (KILL_subr, "Signal a process.", "\
Sends the signal specified by @var{@2@} to the process @var{@1@}.
If the @var{@3@} argument is supplied, it contains
0 on success or a non-zero error code upon return.
See @code{kill(2)}.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@3@} argument.
")

DEFDOC (LNBLNK, "Get last non-blank character in string.", "\
Returns the index of the last non-blank character in @var{@1@}.
@code{LNBLNK} and @code{LEN_TRIM} are equivalent.
")

DEFDOC (SLEEP, "Sleep for a specified time.", "\
Causes the process to pause for @var{@1@} seconds.
See @code{sleep(2)}.
")

DEFDOC (SYSTEM_subr, "Invoke shell (system) command.", "\
Passes the command @var{@1@} to a shell (see @code{system(3)}).
If argument @var{@2@} is present, it contains the value returned by
@code{system(3)}, presumably 0 if the shell command succeeded.
Note that which shell is used to invoke the command is system-dependent
and environment-dependent.

Some non-GNU implementations of Fortran provide this intrinsic as
only a function, not as a subroutine, or do not support the
(optional) @var{@2@} argument.
")

DEFDOC (SYSTEM_func, "Invoke shell (system) command.", "\
Passes the command @var{@1@} to a shell (see @code{system(3)}).
Returns the value returned by
@code{system(3)}, presumably 0 if the shell command succeeded.
Note that which shell is used to invoke the command is system-dependent
and environment-dependent.

Due to the side effects performed by this intrinsic, the function
form is not recommended.
However, the function form can be valid in cases where the
actual side effects performed by the call are unimportant to
the application.

For example, on a UNIX system, @samp{SAME = SYSTEM('cmp a b')}
does not perform any side effects likely to be important to the
program, so the programmer would not care if the actual system
call (and invocation of @code{cmp}) was optimized away in a situation
where the return value could be determined otherwise, or was not
actually needed (@samp{SAME} not actually referenced after the
sample assignment statement).
")

DEFDOC (TIME_vxt, "Get the time as a character value.", "\
Returns in @var{@1@} a character representation of the current time as
obtained from @code{ctime(3)}.

@xref{Fdate Intrinsic (subroutine)} for an equivalent routine.
")

DEFDOC (IBCLR, "Clear a bit.", "\
Returns the value of @var{@1@} with bit @var{@2@} cleared (set to
zero).
@xref{BTest Intrinsic} for information on bit positions.
")

DEFDOC (IBSET, "Set a bit.", "\
Returns the value of @var{@1@} with bit @var{@2@} set (to one).
@xref{BTest Intrinsic} for information on bit positions.
")

DEFDOC (IBITS, "Extract a bit subfield of a variable.", "\
Extracts a subfield of length @var{@3@} from @var{@1@}, starting from
bit position @var{@2@} and extending left for @var{@3@} bits.
The result is right-justified and the remaining bits are zeroed.
The value
of @samp{@var{@2@}+@var{@3@}} must be less than or equal to the value
@samp{BIT_SIZE(@var{@1@})}.
@xref{Bit_Size Intrinsic}.
")

DEFDOC (ISHFT, "Logical bit shift.", "\
All bits representing @var{@1@} are shifted @var{@2@} places.
@samp{@var{@2@}.GT.0} indicates a left shift, @samp{@var{@2@}.EQ.0}
indicates no shift and @samp{@var{@2@}.LT.0} indicates a right shift.
If the absolute value of the shift count is greater than
@samp{BIT_SIZE(@var{@1@})}, the result is undefined.
Bits shifted out from the left end or the right end, as the case may be,
are lost.
Zeros are shifted in from the opposite end.

@xref{IShftC Intrinsic} for the circular-shift equivalent.
")

DEFDOC (ISHFTC, "Circular bit shift.", "\
The rightmost @var{@3@} bits of the argument @var{@1@}
are shifted circularly @var{@2@}
places, i.e.@ the bits shifted out of one end are shifted into 
the opposite end.
No bits are lost.
The unshifted bits of the result are the same as
the unshifted bits of @var{@1@}.
The  absolute value of the argument @var{@2@}
must be less than or equal to @var{@3@}.  
The value of @var{@3@} must be greater than or equal to one and less than 
or equal to @samp{BIT_SIZE(@var{@1@})}.

@xref{IShft Intrinsic} for the logical shift equivalent.
")

DEFDOC (MVBITS, "Moving a bit field.", "\
Moves @var{@3@} bits from positions @var{@2@} through
@samp{@var{@2@}+@var{@3@}-1} of @var{@1@} to positions @var{@5@} through
@samp{@var{@2@}+@var{@3@}-1} of @var{@4@}.  The portion of argument
@var{@4@} not affected by the movement of bits is unchanged.  Arguments
@var{@1@} and @var{@4@} are permitted to be the same numeric storage
unit.  The values of @samp{@var{@2@}+@var{@3@}} and
@samp{@var{@5@}+@var{@3@}} must be less than or equal to
@samp{BIT_SIZE(@var{@1@})}.
")

DEFDOC (INDEX, "Locate a CHARACTER substring.", "\
Returns the position of the start of the first occurrence of string
@var{@2@} as a substring in @var{@1@}, counting from one.
If @var{@2@} doesn't occur in @var{@1@}, zero is returned.
")

