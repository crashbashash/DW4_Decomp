/* Points the stdout stream at the current reent block and formats the arguments to it through
 * vfprintf (newlib printf shape). */
/* ee-gcc ships no stdarg.h here: the compiler builtins stand in for it. */
typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) __builtin_va_end(ap)

typedef struct Reent Reent;

typedef struct Stream {
    char f0[84];
    Reent *data;
} Stream;

struct Reent {
    int errorNumber;
    Stream *in;
    Stream *out;
};

int vfprintf(Stream *stream, const char *format, va_list args);
extern Reent *DAT_004854a0;

int printf(const char *format, ...) {
    int result;
    va_list args;

    DAT_004854a0->out->data = DAT_004854a0;
    va_start(args, format);
    result = vfprintf(DAT_004854a0->out, format, args);
    va_end(args);
    return result;
}
