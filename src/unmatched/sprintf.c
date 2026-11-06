/* Formats into a caller buffer through a string stream with unbounded space and terminates it
 * (newlib sprintf shape). */
/* ee-gcc ships no stdarg.h here: the compiler builtins stand in for it. */
typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) __builtin_va_end(ap)

typedef struct StreamBuffer {
    unsigned char *base;
    int size;
} StreamBuffer;

/* newlib FILE layout as the stores below use it */
typedef struct Stream {
    unsigned char *position;
    int readSpace;
    int writeSpace;
    short flags;
    short file;
    StreamBuffer buffer;
    char f24[60];
    void *data;
} Stream;

#define STREAM_WRITE 0x0008  /* __SWR */
#define STREAM_STRING 0x0200 /* __SSTR */
#define INT_MAX 0x7fffffff

int vfprintf(Stream *stream, const char *format, va_list args);
extern void *DAT_004854a0; /* current reent block */

int sprintf(char *buffer, const char *format, ...) {
    int result;
    va_list args;
    Stream stream;

    stream.flags = STREAM_WRITE | STREAM_STRING;
    stream.buffer.base = stream.position = (unsigned char *)buffer;
    stream.buffer.size = stream.writeSpace = INT_MAX;
    stream.data = DAT_004854a0;
    va_start(args, format);
    result = vfprintf(&stream, format, args);
    va_end(args);
    *stream.position = 0;
    return result;
}
