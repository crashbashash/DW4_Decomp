extern "C" {
void FUN_0045c330(void);
extern struct G *DAT_0058cb88[4];
void *igPickMode_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igPickMode_GetMetaObject(void) {
    struct G *g = DAT_0058cb88[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0045c330();
end:
    return DAT_0058cb88[0];
}
