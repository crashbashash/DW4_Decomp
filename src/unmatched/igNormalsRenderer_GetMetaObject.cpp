extern "C" {
void FUN_0045d9f0(void);
extern struct G *DAT_0058cda0[4];
void *igNormalsRenderer_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igNormalsRenderer_GetMetaObject(void) {
    struct G *g = DAT_0058cda0[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0045d9f0();
end:
    return DAT_0058cda0[0];
}
