/* 0x0012d5c8 — vfprintf (116 bytes). Binds the stream to the current reent block and runs the one-time stdio setup if needed, then formats through FUN_0012d640 (newlib vfprintf with CHECK_INIT). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef __builtin_va_list va_list;

typedef struct Reent {
    char f0[56];
    int stdioInitialised;
} Reent;

typedef struct Stream {
    char f0[84];
    Reent *data;
} Stream;

void FUN_00125138(Reent *reent);
int FUN_0012d640(Reent *reent, Stream *stream, const char *format, va_list args);
extern Reent *DAT_004854a0;

int vfprintf(Stream *stream, const char *format, va_list args) {
    /* newlib's CHECK_INIT macro */
    do {
        if (stream->data == 0) {
            stream->data = DAT_004854a0;
        }
        if (!stream->data->stdioInitialised) {
            FUN_00125138(stream->data);
        }
    } while (0);
    return FUN_0012d640(stream->data, stream, format, args);
}
