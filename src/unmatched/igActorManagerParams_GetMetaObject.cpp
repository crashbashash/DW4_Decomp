extern "C" {
void FUN_0045e830(void);
extern struct G *DAT_0058ceb8[4];
void *igActorManagerParams_GetMetaObject(void);
}
struct G { int pad[9]; int f; };
void *igActorManagerParams_GetMetaObject(void) {
    struct G *g = DAT_0058ceb8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_0045e830();
end:
    return DAT_0058ceb8[0];
}
