extern "C" {
void FUN_0045d9f0(void);
extern struct G *DAT_0058cda0[4];
void *igNormalsRenderer_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igNormalsRenderer_GetMetaObject(void) {
    struct G *g = DAT_0058cda0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045d9f0();
    }
    return DAT_0058cda0[0];
}
