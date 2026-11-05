/* 0x00262208 — FUN_00262208 (196 bytes). ADXF_StopNw (name from the error strings at DAT_004eddc0/DAT_004edde8): requests a non-waiting stop of the stream with FUN_0026a238 and flags it in f3, bracketed by FUN_00260c20 trace calls. Returns the current position, or -3/-1 on a bad handle. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct AdxfReader AdxfReader;

typedef struct AdxfReaderMethods {
    void (*f0)(AdxfReader *reader);
    void (*f4)(AdxfReader *reader);
    void (*f8)(AdxfReader *reader);
    void (*f12)(AdxfReader *reader);
} AdxfReaderMethods;

struct AdxfReader {
    const AdxfReaderMethods *methods;
};

/* ADXF file handle, 68 bytes (16 of them at DAT_00499de8); field meanings beyond the ones set here are not yet known */
typedef struct AdxfHandle {
    signed char used;
    signed char f1;
    signed char f2;
    signed char f3;
    void *stream;
    struct AdxfReader *reader;
    int f12;
    int f16;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
    int f40;
    int f44;
    int f48;
    int f52;
    const char *f56;
    int f60;
    int f64;
} AdxfHandle;

#define ADXF_HANDLE_COUNT 16

void FUN_00260c20(int a, int b, void *handle, int c, int d);
void FUN_002607e8(const char *message);
void FUN_0026a238(void *stream);
extern char DAT_004eddc0[]; /* "E2092301:'adxf' is NULL.(ADXF_StopNw)" */
extern char DAT_004edde8[]; /* "E2092302:'adxf->stm' is NULL.(ADXF_StopNw)" */

int FUN_00262208(AdxfHandle *handle) {
    FUN_00260c20(7, 0, handle, -1, -1);
    if (handle == 0) {
        FUN_002607e8(DAT_004eddc0);
        return -3;
    }
    if (handle->f1 != 1) {
        if (handle->f1 == 3) {
            handle->f1 = 1;
        } else {
            if (handle->stream == 0) {
                FUN_002607e8(DAT_004edde8);
                return -1;
            }
            FUN_0026a238(handle->stream);
            handle->f3 = 1;
            FUN_00260c20(7, 1, handle, -1, -1);
        }
    }
    return handle->f20;
}
