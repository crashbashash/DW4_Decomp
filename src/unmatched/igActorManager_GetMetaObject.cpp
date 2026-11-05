extern "C" {
void FUN_0045e4a0(void);
extern struct G *DAT_0058ce60[4];
void *igActorManager_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igActorManager_GetMetaObject(void) {
    struct G *g = DAT_0058ce60[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0045e4a0();
end:
    return DAT_0058ce60[0];
}
