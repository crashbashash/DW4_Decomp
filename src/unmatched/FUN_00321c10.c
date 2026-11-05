/* 0x00321c10 — scans the {key, value} pair table from arg1 until a null value; returns the value for the first matching key,
 * or the default entry when none matches. */
extern int DAT_004f7910[4];
int *FUN_00321c10(int arg0, int *arg1) {
    int *v;
    while ((v = (int *)arg1[1]) != 0) {
        if (arg1[0] == arg0) return v;
        arg1 += 2;
    }
    return &DAT_004f7910[0];
}
