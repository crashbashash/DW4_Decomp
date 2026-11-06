/* ADXF_GetFsizeSct (name from the error string at DAT_004ede90): returns the file size in sectors,
 * first asking the stream to resolve it with FUN_0026abb0 when the cached size is still the
 * 0x7FFFF800 placeholder (-5 when the stream then reports state 4). */
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

void FUN_002607e8(const char *message);
void FUN_0026abb0(void *stream);
char FUN_0026a138(void *stream);
int FUN_0026aa00(void *stream);
extern char DAT_004ede90[]; /* "E9040828:'adxf' is NULL.(ADXF_GetFsizeSct)" */

int FUN_00262580(AdxfHandle *handle) {
    if (handle == 0) {
        FUN_002607e8(DAT_004ede90);
        return -3;
    }
    if (handle->f16 > 0x7ffff7ff) {
        FUN_0026abb0(handle->stream);
        if (FUN_0026a138(handle->stream) == 4) {
            return -5;
        }
    }
    handle->f16 = FUN_0026aa00(handle->stream);
    return handle->f16;
}
