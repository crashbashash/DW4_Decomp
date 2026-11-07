extern "C" {
void FUN_00349e90(void);
extern struct G *DAT_00588280[4];
void *FUN_00349db0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00349db0(void) {
    struct G *g = DAT_00588280[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00349e90();
    }
    return DAT_00588280[0];
}
