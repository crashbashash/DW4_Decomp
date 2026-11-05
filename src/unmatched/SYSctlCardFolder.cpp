extern "C" {
typedef struct CardFolderFlags { int pad0; int pad1; int count; int pad3; unsigned char *flags; } CardFolderFlags;
typedef struct CardRecord { int pad0; int pad1; int pad2; CardFolderFlags *folder; } CardRecord;
int bePlayer_GetStruct(int);
CardRecord *igProperty_GetRecordArray(int, void *);
int igStrCmp(int, void *);
extern int DAT_0050da28[4];
extern int DAT_0050da38[4];
extern int DAT_0050da40[4];
extern int DAT_0050da48[4];
extern unsigned char GPR_005549bc;
extern unsigned char GPR_005549c0;
int SYSctlCardFolder(int name, int idx);
}

int SYSctlCardFolder(int name, int idx) {
    CardFolderFlags *f = igProperty_GetRecordArray(bePlayer_GetStruct(1), DAT_0050da28)->folder;
    if (igStrCmp(name, DAT_0050da38) == 0) {
        int n = f->count;
        int total = 0;
        int i;
        for (i = 0; i < n; i++) {
            if (f->flags[i] == 1) total += 1;
        }
        return total;
    }
    if (igStrCmp(name, DAT_0050da40) == 0) {
        unsigned char *q = f->flags + idx;
        if (*q != 0) return 0;
        if (f->count != 0 && idx >= 0 && idx < f->count) *q = GPR_005549bc;
        return 1;
    }
    if (igStrCmp(name, DAT_0050da48) == 0) {
        unsigned char *q = f->flags + idx;
        if (*q == 0) return 0;
        if (f->count != 0 && idx >= 0 && idx < f->count) *q = GPR_005549c0;
        return 1;
    }
    return 0;
}
