/* 0x0040c180 — FUN_0040c180. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beBaseInfoDataList_Create(int);

int *FUN_0040c180(int *arg0, int *arg1) {
    *arg0 = beBaseInfoDataList_Create(*arg1);
    return arg0;
}
} /* extern "C" */
