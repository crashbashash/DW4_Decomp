extern "C" {
void FUN_00334c70(void);
extern struct G *DAT_00587658[4];
void *FUN_00334b40(void);
}
struct G { int pad[9]; int f; };
void *FUN_00334b40(void) {
    struct G *g = DAT_00587658[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00334c70();
    }
    return DAT_00587658[0];
}
