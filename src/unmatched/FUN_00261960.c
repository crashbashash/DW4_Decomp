/* 0x00261960 — FUN_00261960 (128 bytes). Opens a sector range on the ADXF handle stream, closing it again when FUN_0026a138 reports state 4; on success records the length in sectors and bytes (sectors * 2048). Returns 0 or -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* ADXF file handle, 68 bytes (16 of them at DAT_00499de8); field meanings beyond the ones set here are not yet known */
typedef struct AdxfHandle {
    signed char used;
    signed char f1;
    signed char f2;
    signed char f3;
    void *stream;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int f28;
    int f32;
    char f36[8];
    int f44;
    int f48;
    int f52;
    const char *f56;
    int f60;
    int f64;
} AdxfHandle;

#define ADXF_HANDLE_COUNT 16

void FUN_0026a068(void *stream, const char *name, int b, int c, int sectors);
char FUN_0026a138(void *stream);
void FUN_0026a0e0(void *stream);

int FUN_00261960(AdxfHandle *handle, const char *name, int directory, int start, int sectors) {
    handle->f52 = directory;
    handle->f56 = name;
    handle->f48 = start;
    handle->f60 = start;
    handle->f64 = sectors;
    handle->f20 = 0;
    FUN_0026a068(handle->stream, name, directory, start, sectors);
    if (FUN_0026a138(handle->stream) == 4) {
        FUN_0026a0e0(handle->stream);
        return -1;
    }
    handle->f12 = sectors;
    handle->f16 = sectors << 11;
    return 0;
}
