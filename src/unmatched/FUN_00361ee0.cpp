extern "C" {
void FUN_00362170(void);
extern struct G *DAT_00589678[4];
void *FUN_00361ee0(void);
}
struct G { int pad[9]; int f; };
void *FUN_00361ee0(void) {
    struct G *g = DAT_00589678[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00362170();
end:
    return DAT_00589678[0];
}
