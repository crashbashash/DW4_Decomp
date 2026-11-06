/* adxf_CreateAdxFs (name from the error strings at DAT_004edb58/DAT_004edb90): takes a free ADXF
 * handle, opens its stream with FUN_00269f50 and initialises it; reports through FUN_002607e8 and
 * returns 0 on failure. */
/* ADXF file handle, 68 bytes (16 of them at DAT_00499de8); field meanings beyond the ones set here are not yet known */
typedef struct AdxfHandle {
    signed char used;
    signed char f1;
    signed char f2;
    signed char f3;
    void *stream;
    int f8;
    char f12[12];
    int f24;
    int f28;
    int f32;
    char f36[8];
    int f44;
    char f48[20];
} AdxfHandle;

#define ADXF_HANDLE_COUNT 16

AdxfHandle *FUN_00261720(void);
void *FUN_00269f50(int a, int size);
void FUN_002607e8(const char *message);
extern char DAT_004edb58[]; /* "E04041201:not enough ADXF handle (adxf_CreateAdxFs)" */
extern char DAT_004edb90[]; /* "E02111001:can't create stm handle (adxf_CreateAdxFs)" */

AdxfHandle *FUN_00261778(void) {
    AdxfHandle *handle;
    void *stream;

    handle = FUN_00261720();
    if (handle == 0) {
        FUN_002607e8(DAT_004edb58);
        return 0;
    }
    stream = FUN_00269f50(0, 256);
    handle->stream = stream;
    if (stream == 0) {
        FUN_002607e8(DAT_004edb90);
        return 0;
    }
    handle->f1 = 1;
    handle->f24 = 0;
    handle->f28 = 0;
    handle->f32 = 0;
    handle->f2 = 0;
    handle->f8 = 0;
    handle->f3 = 0;
    handle->f44 = 512;
    handle->used = 1;
    return handle;
}
