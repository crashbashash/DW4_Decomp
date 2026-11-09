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
typedef struct GsTexClut {
    unsigned int cbw : 6;
    unsigned int cou : 6;
    unsigned int cov : 10;
    unsigned int pad : 10;
    unsigned int pad2;
} GsTexClut;
typedef struct GsState {
    char pad0[48];
    GsTex0 tex0_1;
    GsTex0 tex0_2;
    char pad64[104];
    GsTexClut texclut;
} GsState;
typedef struct ClutImage { char pad0[56]; int address; } ClutImage;
typedef struct ClutSource {
    char pad0[12];
    ClutImage *image;
    int unused : 2;
    int storageMode : 4;
    int format : 4;
} ClutSource;
extern int DAT_00569330[4];
extern GsState *DAT_0056ad80;
extern int DAT_00491478[4];
extern long long DAT_0056ae48[4];
void FUN_001fcb00(void);

/* matching construct: a small sweep of spellings */
void FUN_001ea5d0(ClutSource *clut) {
    if (clut->image == 0) return;
    if (DAT_00569330[0] == 0) {
        DAT_0056ad80->tex0_1.cbp = clut->image->address;
        DAT_0056ad80->tex0_1.cpsm = clut->format;
        DAT_0056ad80->tex0_1.csm = clut->storageMode;
        DAT_0056ad80->tex0_1.csa = 0;
        DAT_0056ad80->tex0_1.cld = 2;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x40200040LL;
    } else {
        DAT_0056ad80->tex0_2.cbp = clut->image->address;
        DAT_0056ad80->tex0_2.cpsm = clut->format;
        DAT_0056ad80->tex0_2.csm = clut->storageMode;
        DAT_0056ad80->tex0_2.csa = 0;
        DAT_0056ad80->tex0_2.cld = 2;
        DAT_00491478[0] |= 0x40;
        DAT_0056ae48[0] |= 0x40200080LL;
        if (DAT_00569330[0] == 1) FUN_001fcb00();
    }
    DAT_0056ad80->texclut.cbw = 1;
    DAT_0056ad80->texclut.cou = 0;
    DAT_0056ad80->texclut.cov = 0;
}
