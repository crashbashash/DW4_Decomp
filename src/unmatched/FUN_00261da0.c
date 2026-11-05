/* 0x00261da0 — FUN_00261da0 (256 bytes). Starts a read of up to the requested number of sectors from the current position of the ADXF handle into the buffer, inside the FUN_0025f2d0/FUN_0025f2e8 lock; marks the handle finished (state 3) when nothing is left. Returns the sectors requested. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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

char FUN_0026a138(void *stream);
void FUN_0026a2a0(void *stream);
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void FUN_0026a300(void *stream, int a);
void FUN_0026aae8(void *stream, void *buffer);
int FUN_0026a9e8(void *stream, int a);
void FUN_0026aa10(void *stream, int a);
void FUN_0026a140(void *stream, int position);
void FUN_0026a1f0(void *stream, int count);

int FUN_00261da0(AdxfHandle *handle, int sectors, void *buffer) {
    int remaining;
    int count;

    if (FUN_0026a138(handle->stream) != 1) {
        FUN_0026a2a0(handle->stream);
    }
    FUN_0025f2d0();
    remaining = handle->f12 - handle->f20;
    handle->f32 = 0;
    if (sectors < remaining) {
        remaining = sectors;
    }
    handle->f24 = handle->f48 + handle->f20;
    handle->f28 = remaining;
    if (remaining == 0) {
        handle->f1 = 3;
        count = 0;
    } else {
        FUN_0026a300(handle->stream, -1);
        FUN_0026aae8(handle->stream, buffer);
        FUN_0026a9e8(handle->stream, handle->f44);
        handle->f1 = 2;
        handle->f3 = 0;
        FUN_0026aa10(handle->stream, 0);
        FUN_0026a140(handle->stream, handle->f20);
        FUN_0026a1f0(handle->stream, handle->f28);
        count = handle->f28;
    }
    FUN_0025f2e8();
    return count;
}
