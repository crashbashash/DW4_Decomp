/* Sets every field of a 16-byte record to -1. */
typedef struct {
    long long f0;
    int f8;
    int f12;
} Rec28dbb8;

void FUN_0028dbb8(Rec28dbb8 *rec) {
    rec->f0 = -1;
    rec->f8 = -1;
    rec->f12 = -1;
}
