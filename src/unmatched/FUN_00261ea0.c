/* ADXF_ReadSj32: validates the handle, sector count and buffer, then starts a read with
 * FUN_00261da0 unless one is already running (state 2) and flags the handle busy. Returns the
 * sectors requested, 0, or -3 on a bad argument. */
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

/* ADXF file handle, 68 bytes (16 of them at DAT_00499de8). */
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

int FUN_00261da0(AdxfHandle *handle, int sectors, void *buffer);
void FUN_002607e8(const char *message);
extern char DAT_004edc00[]; /* "E9040811:'adxf' is NULL.(ADXF_ReadSj32)" */
extern char DAT_004edc28[]; /* "E9040812:'nsct'is negative.(ADXF_ReadSj32)" */
extern char DAT_004edc58[]; /* "E9040813:'sj'is NULL.(ADXF_ReadSj32)" */

int FUN_00261ea0(AdxfHandle *handle, int sectors, void *buffer) {
    int count;

    if (handle == 0) {
        FUN_002607e8(DAT_004edc00);
        return -3;
    }
    if (sectors < 0) {
        FUN_002607e8(DAT_004edc28);
        return -3;
    }
    if (buffer == 0) {
        FUN_002607e8(DAT_004edc58);
        return -3;
    }
    if (handle->f1 == 2) {
        return 0;
    }
    count = FUN_00261da0(handle, sectors, buffer);
    handle->f2 = 1;
    return count;
}
