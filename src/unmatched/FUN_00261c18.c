/* Detaches the reader object from an ADXF handle that is not busy (f2 clear), first calling
 * FUN_00260a40 on f36/f40 when DAT_0049a628 is 1, then calls the reader method at slot 12. */
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

void FUN_00260a40(int a, int b);
extern int DAT_0049a628;

void FUN_00261c18(AdxfHandle *handle) {
    AdxfReader *reader;

    if (handle->reader != 0 && handle->f2 == 0) {
        if (DAT_0049a628 == 1) {
            FUN_00260a40(handle->f36, handle->f40);
        }
        reader = handle->reader;
        handle->reader = 0;
        reader->methods->f12(reader);
    }
}
