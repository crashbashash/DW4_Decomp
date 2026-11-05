extern "C" {
void FUN_00341790(void);
extern struct G *DAT_00587c48[4];
void *FUN_00341700(void);
}
struct G { int pad[9]; int f; };
void *FUN_00341700(void) {
    struct G *g = DAT_00587c48[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00341790();
end:
    return DAT_00587c48[0];
}
