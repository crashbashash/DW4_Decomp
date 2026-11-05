extern "C" {
void FUN_003c59f0(void);
extern struct G *DAT_0058bc90[4];
void *beNDMWMcSlotList_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWMcSlotList_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bc90[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c59f0();
end:
    return DAT_0058bc90[0];
}
