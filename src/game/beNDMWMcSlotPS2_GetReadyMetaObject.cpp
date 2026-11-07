struct S { char pad[36]; unsigned flags; };
extern "C" {
int FUN_003c5fb0();
extern S *DAT_0058bcc0[4];
S *beNDMWMcSlotPS2_GetReadyMetaObject(void);
}
S *beNDMWMcSlotPS2_GetReadyMetaObject(void) {
    S *g = DAT_0058bcc0[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_003c5fb0();
done:
    return DAT_0058bcc0[0];
}
