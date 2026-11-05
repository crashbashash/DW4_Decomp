extern "C" {
void FUN_0045d000(void);
extern struct G *DAT_0058ccf8[4];
void *igViewMode_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igViewMode_GetMetaObject(void) {
    struct G *g = DAT_0058ccf8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0045d000();
end:
    return DAT_0058ccf8[0];
}
