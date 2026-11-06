/* Sets every field of a 40-byte record to -1. */
typedef struct {
    long long f0;
    long long f8;
    int f16;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
} Rec28dbf8;

void FUN_0028dbf8(Rec28dbf8 *rec) {
    rec->f0 = -1;
    rec->f8 = -1;
    rec->f16 = -1;
    rec->f20 = -1;
    rec->f24 = -1;
    rec->f28 = -1;
    rec->f32 = -1;
    rec->f36 = -1;
}
