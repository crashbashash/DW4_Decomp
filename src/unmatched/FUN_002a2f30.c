struct Info { int f0, f4, f8, f12, f16, f20, f24, f28, f32; };
extern struct Info DAT_005855b0;
extern char DAT_005855d8[];
extern int DAT_005855e0[4];
void *memset();
void FUN_002a2f30(struct Info *arg0) {
    DAT_005855b0 = *arg0;
    DAT_005855b0.f16 = (DAT_005855b0.f16 + 0x3F) & ~0x3F;
    DAT_005855b0.f32 = (DAT_005855b0.f32 + 0x3F) & ~0x3F;
    memset(DAT_005855d8, 0, 8);
    memset(DAT_005855e0, 0, 0x40);
}
