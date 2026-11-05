extern "C" {
void FUN_00359310(void);
extern struct G *DAT_00589090[4];
void *FUN_00359230(void);
}
struct G { int pad[9]; int f; };
void *FUN_00359230(void) {
    struct G *g = DAT_00589090[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    FUN_00359310();
end:
    return DAT_00589090[0];
}
