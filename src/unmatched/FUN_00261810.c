/* Opens the named file on the ADXF handle stream (message from ADXF_Open at DAT_004edbc8 for a
 * null name), closing it again when FUN_0026a138 reports state 4; on success records the sizes
 * from FUN_0026aa00/FUN_0026aa08. Returns 0 or -1. */
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
int FUN_0026aa00(void *stream);
int FUN_0026aa08(void *stream);
void FUN_002607e8(const char *message);
extern char DAT_004edbc8[]; /* "E9081901:illigal parameter fname=null.(ADXF_Open)" */

int FUN_00261810(AdxfHandle *handle, const char *name, int directory) {
    int size;

    if (name == 0) {
        FUN_002607e8(DAT_004edbc8);
        return -1;
    }
    handle->f52 = directory;
    handle->f56 = name;
    handle->f20 = 0;
    FUN_0026a068(handle->stream, name, directory, 0, 0xfffff);
    if (FUN_0026a138(handle->stream) == 4) {
        FUN_0026a0e0(handle->stream);
        return -1;
    }
    handle->f16 = FUN_0026aa00(handle->stream);
    size = FUN_0026aa08(handle->stream);
    handle->f60 = 0;
    handle->f12 = size;
    handle->f64 = size;
    return 0;
}
