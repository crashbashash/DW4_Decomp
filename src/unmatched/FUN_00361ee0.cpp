extern "C" {
void FUN_00362170(void);
extern struct G *DAT_00589678[4];
void *FUN_00361ee0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00361ee0(void) {
    struct G *g = DAT_00589678[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00362170();
    }
    return DAT_00589678[0];
}
