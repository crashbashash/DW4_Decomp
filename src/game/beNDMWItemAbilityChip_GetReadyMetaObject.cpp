extern "C" {
void FUN_003c88c0(void);
extern struct G *DAT_0058bf48[4];
void *beNDMWItemAbilityChip_GetReadyMetaObject(void);
}
struct G { int pad[9]; int f; };
void *beNDMWItemAbilityChip_GetReadyMetaObject(void) {
    struct G *g = DAT_0058bf48[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003c88c0();
end:
    return DAT_0058bf48[0];
}
