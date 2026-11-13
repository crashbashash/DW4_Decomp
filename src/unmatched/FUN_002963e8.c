extern int FUN_002968c0(void *);
extern int FUN_002968e0(void *);
extern void mwsfd_Error(const char *);
extern const char D_004f3a18[];
int FUN_002963e8(void *h)
{
    if (!FUN_002968c0(h)) {
        mwsfd_Error(D_004f3a18);
        return 0;
    }
    return FUN_002968e0(h);
}
