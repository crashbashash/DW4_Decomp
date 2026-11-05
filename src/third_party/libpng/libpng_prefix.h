/* libpng_prefix.h -- build configuration of the game's libpng 1.0.8.
 * Passed to the compiler with -prefix, so upstream's files stay unedited. -prefix is read before
 * any -D, which is why the configuration macros are here and not on the command line. */
#define PNG_SETJMP_NOT_SUPPORTED
#define PNG_USER_MEM_SUPPORTED
#define PNG_NO_READ_iCCP
#define PNG_NO_WRITE_iCCP
#define PNG_NO_PROGRESSIVE_READ

/* Every libpng source file defines this before png.h; pngconf.h needs it to pull in stdlib and math. */
#define PNG_INTERNAL

/* zlib keeps the compiler's 64-bit long; libpng was built with a 32-bit one. */
#include "zlib.h"
#define long int

/* pngconf.h defines read interlacing unconditionally; retail has none. Its include guard makes
 * png.h's own #include a no-op. */
#include "pngconf.h"
#undef PNG_READ_INTERLACING_SUPPORTED
