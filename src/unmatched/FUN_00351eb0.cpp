extern "C" {
void FUN_00351ff0(void);
extern struct G *DAT_00588aa8[4];
void *FUN_00351eb0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00351eb0(void) {
    struct G *g = DAT_00588aa8[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00351ff0();
    }
    return DAT_00588aa8[0];
}
