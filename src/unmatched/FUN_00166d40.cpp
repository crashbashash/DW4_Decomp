struct L { char pad[8]; int count; int pad2; int *items; };
extern "C" {
int igObject_IsKindOf(int, int);
extern int DAT_0055f8e8[4];
extern struct L *DAT_00560758[4];
int FUN_00166d40(void);
}
int FUN_00166d40(void) {
    int r;
    int i;

    r = 0;
    if (DAT_00560758[0] != 0) {
        for (i = 0; i < DAT_00560758[0]->count; i++) {
            if (igObject_IsKindOf(DAT_00560758[0]->items[i], DAT_0055f8e8[0]) != 0) {
                r = DAT_00560758[0]->items[i];
                break;
            }
        }
    }
    return r;
}
