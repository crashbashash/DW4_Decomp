typedef struct GsTex0 {
    unsigned long long tbp0 : 14;
    unsigned long long tbw : 6;
    unsigned long long psm : 6;
    unsigned long long tw : 4;
    unsigned long long th : 4;
    unsigned long long tcc : 1;
    unsigned long long tfx : 2;
    unsigned long long cbp : 14;
    unsigned long long cpsm : 4;
    unsigned long long csm : 1;
    unsigned long long csa : 5;
    unsigned long long cld : 3;
} GsTex0;
typedef struct GsSyncState {
    char pad0[48];
    GsTex0 tex0_1;
    GsTex0 tex0_2;
    char pad64[152];
    signed char textureFunction;
} GsSyncState;
typedef struct Texture {
    char pad0[16];
    GsTex0 tex0;
    char pad24[20];
    void *clut;
    char pad48[4];
    int bufferMode;
    int address;
    char pad60[13];
    signed char function;
} Texture;
extern int DAT_00569330;
extern GsSyncState *DAT_0056ad80;
extern int DAT_00491478;
extern long long DAT_0056ae48;
extern long long DAT_0056c068;
extern short DAT_00568e12[4];
extern short DAT_00568e1c[4];
void FUN_001ea5d0(void *clut);
void FUN_001fcb00(void);

void FUN_002084e0(Texture *texture) {
    if (texture == 0) return;
    if (texture->clut != 0) {
        FUN_001ea5d0(texture->clut);
        return;
    }
    DAT_0056c068++;
    DAT_0056ad80->textureFunction = texture->function;
    if (texture->bufferMode != 0) {
        if (texture->bufferMode == 1) {
            texture->address = DAT_00568e12[0] ? 0 : DAT_00568e1c[0];
        }
        if (texture->bufferMode == 2) {
            texture->address = DAT_00568e12[0] ? DAT_00568e1c[0] : 0;
        }
        if (texture->bufferMode == 3) {
            texture->address = DAT_00568e1c[0] * 2;
        }
        texture->address = texture->address << 5;
    }
    if (DAT_00569330 == 0) {
        DAT_0056ad80->tex0_1.tbp0 = texture->address;
        DAT_0056ad80->tex0_1.tbw = texture->tex0.tbw;
        DAT_0056ad80->tex0_1.psm = texture->tex0.psm;
        DAT_0056ad80->tex0_1.tw = texture->tex0.tw;
        DAT_0056ad80->tex0_1.th = texture->tex0.th;
        DAT_00491478 |= 0x40;
        DAT_0056ae48 |= 0x48000040LL;
    } else {
        DAT_0056ad80->tex0_2.tbp0 = texture->address;
        DAT_0056ad80->tex0_2.tbw = texture->tex0.tbw;
        DAT_0056ad80->tex0_2.psm = texture->tex0.psm;
        DAT_0056ad80->tex0_2.tw = texture->tex0.tw;
        DAT_0056ad80->tex0_2.th = texture->tex0.th;
        DAT_00491478 |= 0x40;
        DAT_0056ae48 |= 0x48000080LL;
        if (DAT_00569330 == 1 && texture->bufferMode == 0) FUN_001fcb00();
    }
}
