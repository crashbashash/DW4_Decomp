/* Handle-checked getter (CRI Sofdec 'mwPlyGetAdxtHn'): reports the error text and returns 0 when FUN_002968c0 rejects the handle, otherwise tail-calls FUN_002968e0. */
extern int FUN_002968c0(void *);
extern int FUN_002968e0(void *);
extern void FUN_0029a320(const char *);
extern const char D_004f3a18[]; /* "E1122639: mwPlyGetAdxtHn: handle is invalid." */
int FUN_002963e8(void *h)
{
    if (!FUN_002968c0(h)) {
        FUN_0029a320(D_004f3a18);
        return 0;
    }
    return FUN_002968e0(h);
}
