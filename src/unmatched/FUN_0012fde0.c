/* 0x0012fde0 — FUN_0012fde0 (84 bytes). Formats a va_list into a caller buffer through a string stream with unbounded space and terminates it (newlib vsprintf shape; name is a hypothesis). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* ee-gcc ships no stdarg.h here: the compiler builtins stand in for it. */
typedef __builtin_va_list va_list;

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

int FUN_0012fde0(char *buffer, const char *format, va_list args) {
    int result;
    Stream stream;

    stream.flags = STREAM_WRITE | STREAM_STRING;
    stream.buffer.base = stream.position = (unsigned char *)buffer;
    stream.buffer.size = stream.writeSpace = INT_MAX;
    stream.data = DAT_004854a0;
    result = vfprintf(&stream, format, args);
    *stream.position = 0;
    return result;
}
