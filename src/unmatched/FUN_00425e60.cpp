/* 0x00425e60 - FUN_00425e60. Messenger string-table walk; 116-byte pointer table struct copy; alternate compiler -O3,p. Verified byte-identical by tools/verify.py. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct Tbl { const char *s[29]; } Tbl;
extern Tbl DAT_004cf7a0;
extern char DAT_0051ac10[], DAT_0051ac30[], DAT_0051acc8[], DAT_0051ace0[], DAT_0051af10[], DAT_0051af20[], DAT_0051af30[], DAT_0051af38[], DAT_0051af40[];
void FUN_00425430(int *);
void beNDMWWindow_PresentModelAtOrigin(int *, char *, int, char *, char *);
void beMessenger_SelectGroup(int, char *);
void beMessenger_AppendString(int, const char *);
void beMessenger_DispatchSelected(int, char *);
void FUN_00425e60(int *arg0) {
    Tbl sp30;
    const char **p;
    FUN_00425430(arg0);
    beNDMWWindow_PresentModelAtOrigin(arg0, DAT_0051af10, arg0[5], DAT_0051af20, DAT_0051ac10);
    sp30 = DAT_004cf7a0;
    p = sp30.s;
    if (*p != 0) {
        do {
            beMessenger_SelectGroup(arg0[3], DAT_0051af30);
            beMessenger_AppendString(arg0[3], DAT_0051ac30);
            beMessenger_AppendString(arg0[3], *p);
            beMessenger_AppendString(arg0[3], DAT_0051af38);
            beMessenger_DispatchSelected(arg0[3], DAT_0051af40);
            p++;
        } while (*p != 0);
    }
    beMessenger_SelectGroup(arg0[3], DAT_0051af30);
    beMessenger_AppendString(arg0[3], DAT_0051acc8);
    beMessenger_AppendString(arg0[3], DAT_0051ace0);
    beMessenger_AppendString(arg0[3], DAT_0051af38);
    beMessenger_DispatchSelected(arg0[3], DAT_0051af40);
}
} /* extern "C" */
