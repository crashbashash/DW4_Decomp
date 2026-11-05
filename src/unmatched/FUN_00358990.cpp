extern "C" {
int beMessengerDelay_EnsureRegistered();
struct G { char pad[36]; int f; };
extern G *DAT_00588ff0[4];
G *FUN_00358990(void);
}
G *FUN_00358990(void) {
    G *g = DAT_00588ff0[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        beMessengerDelay_EnsureRegistered();
    return DAT_00588ff0[0];
}
