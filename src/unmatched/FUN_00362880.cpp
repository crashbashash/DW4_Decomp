extern "C" {
void FUN_003629b0(void);
extern struct G *DAT_005896f8[4];
void *FUN_00362880(void);
}
struct G { int pad[9]; int f; };
void *FUN_00362880(void) {
    struct G *g = DAT_005896f8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_003629b0();
end:
    return DAT_005896f8[0];
}
