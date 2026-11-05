/* 0x001e8850 - 308 bytes. Set the three colour bytes from 0..1 floats (inline float to unsigned conversion) and flag the dirty bits; alternate -O3. */
struct Col { char pad[224]; unsigned char r; unsigned char g; unsigned char b; };
extern int DAT_00491478[4];
extern struct Col *DAT_0056ad80[4];
extern long long DAT_0056ae48[4];
void FUN_001e8850(float r, float g, float b) {
    DAT_0056ad80[0]->r = (unsigned int)(255.0f * r);
    DAT_0056ad80[0]->g = (unsigned int)(255.0f * g);
    DAT_0056ad80[0]->b = (unsigned int)(255.0f * b);
    DAT_00491478[0] |= 0x40;
    DAT_0056ae48[0] |= 0x10000000;
}
