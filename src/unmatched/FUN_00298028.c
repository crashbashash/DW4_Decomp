/* Handle-checked setter: when FUN_002968c0 accepts the handle the value is forwarded through two helpers, otherwise the error text at D_004f42c8
 * ("E306091: MWSFSFX_SetOutBufSize: handle is invalid.", CRI Sofdec) is reported through FUN_0029a320. */
extern int FUN_002968c0(void *);
extern void *FUN_00297810(void *);
extern void FUN_0029a320(const char *);
extern void FUN_002b3bf8(void *, int, int);
extern void FUN_002b3c20(void *, int);
extern const char D_004f42c8[];
void FUN_00298028(void *h, int a, int b, int c)
{
    void *w;
    if (!FUN_002968c0(h)) {
        FUN_0029a320(D_004f42c8);
        return;
    }
    w = FUN_00297810(h);
    FUN_002b3bf8(w, a, b);
    FUN_002b3c20(w, c);
}
