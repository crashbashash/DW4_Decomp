typedef struct L { char pad[8]; int f8; char pad2[4]; int *f10; } L;
typedef struct O { char pad[12]; L *fc; } O;
int igObject_IsKindOf();
extern int DAT_0055ef80[4];
extern void *DAT_0055f170[4];
extern int DAT_0055f208[4];
int FUN_00462100(O *arg0) {
    int i;
    int n;
    int off;

    if (arg0 == 0) {
        return 0;
    }
    if (igObject_IsKindOf(arg0, DAT_0055f170[0]) != 0) {
        return 1;
    }
    if (igObject_IsKindOf(arg0, DAT_0055ef80[0]) != 0) {
        return 1;
    }
    if (igObject_IsKindOf(arg0, DAT_0055f208[0]) != 0) {
        n = arg0->fc->f8;
        i = 0;
        if (0 < n) {
            off = 0;
            do {
                if (!!FUN_00462100(*(O **)((char *)arg0->fc->f10 + off))) {
                    return 1;
                }
                i += 1;
                off += 4;
            } while (i < n);
        }
    }
    return 0;
}
