/* ADXF_Stop (name from the error strings at DAT_004edd68/DAT_004edd90): stops a running read,
 * records the sectors actually read, detaches the reader and returns the handle to state 1,
 * bracketed by FUN_00260c20 trace calls. Returns the current position, or -3/-1 on a bad handle. */
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
void FUN_0026a2a0(void *stream);
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
int FUN_0026a160(void *stream);
void FUN_00261c18(AdxfHandle *handle);
extern char DAT_004edd68[]; /* "E9040822:'adxf' is NULL.(ADXF_Stop)" */
extern char DAT_004edd90[]; /* "E9040823:'adxf->stm' is NULL.(ADXF_Stop)" */

int FUN_00262118(AdxfHandle *handle) {
    FUN_00260c20(5, 0, handle, -1, -1);
    if (handle == 0) {
        FUN_002607e8(DAT_004edd68);
        return -3;
    }
    if (handle->f1 != 1) {
        if (handle->f1 == 3) {
            handle->f1 = 1;
        } else {
            if (handle->stream == 0) {
                FUN_002607e8(DAT_004edd90);
                return -1;
            }
            FUN_0026a2a0(handle->stream);
            FUN_0025f2d0();
            handle->f32 = FUN_0026a160(handle->stream) - handle->f20;
            FUN_00261c18(handle);
            handle->f1 = 1;
            FUN_0025f2e8();
            FUN_00260c20(5, 1, handle, -1, -1);
        }
    }
    return handle->f20;
}
