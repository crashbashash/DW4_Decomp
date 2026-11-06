/* The record pointer is re-read from the global for each group of copies. */
struct G { char pad0[136]; short s136, s138, s140, s142, s144, s146, s148, s150; char pad152[104]; int i256, i260, i264, i268; char pad272[40]; int i312, i316, i320, i324; char pad328[8]; int i336, i340, i344, i348, i352, i356, i360, i364, i368, i372, i376, i380; };
extern int DAT_00491478[4];
extern struct G *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
void FUN_001fc350(void) {
    struct G *g;
    g = DAT_0056ad80[0];
    g->i360 = g->i352; g->i364 = g->i356;
    g = DAT_0056ad80[0];
    g->i376 = g->i368; g->i380 = g->i372;
    g = DAT_0056ad80[0];
    g->i320 = g->i312; g->i324 = g->i316;
    g = DAT_0056ad80[0];
    g->s144 = g->s136; g->s146 = g->s138; g->s148 = g->s140; g->s150 = g->s142;
    g = DAT_0056ad80[0];
    g->i264 = g->i256; g->i268 = g->i260;
    g = DAT_0056ad80[0];
    g->i344 = g->i336; g->i348 = g->i340;
    DAT_00491478[0] |= 0x40;
    DAT_0056ae48[0] |= 0x40000 | ((long long)0xA902 << 0x20);
}
