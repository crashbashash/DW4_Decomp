extern "C" {
void beMessengerGroup_EnsureRegistered(void);
extern struct G *DAT_00588fc8[4];
void *FUN_00358520(void);
}
struct G { int pad[9]; int f; };
void *FUN_00358520(void) {
    struct G *g = DAT_00588fc8[0];
    bool t;
    if (g) {
        if (t = g->f & 4) goto end;
        asm { nop }
    }
    beMessengerGroup_EnsureRegistered();
end:
    return DAT_00588fc8[0];
}
