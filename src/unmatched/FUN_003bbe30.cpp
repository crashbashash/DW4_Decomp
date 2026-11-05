extern "C" {
int FUN_003bbf60();
struct G { char pad[36]; int f; };
extern G *DAT_0058b060[4];
G *FUN_003bbe30(void);
}
G *FUN_003bbe30(void) {
    G *g = DAT_0058b060[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003bbf60();
    return DAT_0058b060[0];
}
