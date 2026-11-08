extern int DAT_00483550;
extern int DAT_004850c0;
extern int DAT_004d2840;
int FUN_0010bf40(int usec);
int FUN_0010d108(void *p);
int FUN_0010e4a0(void *p);
int FUN_00116d20(int mode) {
    if (mode == 0) {
        if (DAT_00483550 > 0) FUN_0010d108(&DAT_004d2840);
        while (FUN_0010e4a0(&DAT_004850c0)) FUN_0010bf40(4000);
        return 0;
    }
    return FUN_0010e4a0(&DAT_004850c0);
}
