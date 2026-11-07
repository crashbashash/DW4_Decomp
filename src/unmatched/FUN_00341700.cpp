extern "C" {
void FUN_00341790(void);
extern struct G *DAT_00587c48[4];
void *FUN_00341700(void);
}
struct G { int pad[9]; int f; };
void *FUN_00341700(void) {
    struct G *g = DAT_00587c48[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00341790();
    }
    return DAT_00587c48[0];
}
