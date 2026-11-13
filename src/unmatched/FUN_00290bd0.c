int FUN_00290ca8(void);
void FUN_00290d20(int status);
int FUN_00290d48(int arg);
void FUN_00290ec8(int count, int work);
void FUN_0028ea10(void);
void FUN_0028f090(void);
void FUN_00290d68(int addr);
void FUN_00290e40(void);
void FUN_00290ec0(int base);
void FUN_00291438(void);

extern char cri_mpv_version[];
extern char *volatile DAT_00573f10;
extern int DAT_00573f68;

int FUN_00290bd0(int count, int arg) {
    int status;
    int base;

    DAT_00573f10 = cri_mpv_version;
    status = FUN_00290ca8();
    if (status != 0) {
        if (status == (int)0xff03ff05) {
            return status;
        }
        for (;;) {
        }
    }
    FUN_00290d20(status);
    FUN_00290ec8(count, FUN_00290d48(arg));
    base = DAT_00573f68;
    FUN_0028ea10();
    FUN_0028f090();
    FUN_00290d68(base + 6112);
    FUN_00290e40();
    FUN_00290ec0(base);
    FUN_00291438();
    return 0;
}
