extern "C" {
void FUN_0036a360(void);
extern struct G *DAT_00589d28[4];
void *FUN_0036a280(void);
}
struct G { int pad[9]; int f; };
void *FUN_0036a280(void) {
    struct G *g = DAT_00589d28[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036a360();
    }
    return DAT_00589d28[0];
}
