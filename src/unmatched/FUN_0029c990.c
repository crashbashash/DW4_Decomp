/* Records FUN_0026bd20(source) in DAT_004be8b8, then passes the source's 64-bit size pair and the
 * FUN_002b5a10/FUN_002b5b80 pair to FUN_002b0608 and returns the low words of its two results. */
int FUN_0026bd20();
int FUN_0026bf90();
void FUN_002b0608();
long FUN_002b5a10();
long FUN_002b5b80();
extern int DAT_004be8b8;

struct Pair64 {
    long a;
    long b;
};

void FUN_0029c990(int target, int source, int *out0, int *out1) {
    struct Pair64 size;
    struct Pair64 extra;
    struct Pair64 result;
    int width;
    int height;

    DAT_004be8b8 = FUN_0026bd20(source);
    FUN_0026bf90(source, &width, &height);
    size.b = height;
    size.a = width;
    extra.a = FUN_002b5a10();
    extra.b = FUN_002b5b80();
    FUN_002b0608(target, &size, &extra, &result);
    *out0 = result.a;
    *out1 = result.b;
}
