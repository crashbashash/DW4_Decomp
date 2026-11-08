typedef struct E { char pad0[44]; int name; char pad48[16]; } E;
int strcmp();
extern int DAT_00568da0[4];
extern E DAT_00562da0[];
int FUN_001eb410(int arg0) {
    int i;
    int r;

    r = -1;
    for (i = 0; DAT_00568da0[0] >= i; i++) {
        if (strcmp(DAT_00562da0[i].name, arg0) == 0) {
            r = i;
            break;
        }
    }
    return r;
}
