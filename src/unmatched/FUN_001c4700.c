int igPlanarShadowShader_GetMetaObject();
int igNode_GetMetaObject();
int FUN_001b68c0();
int FUN_001e06c0();
int FUN_002fe290();
extern int DAT_001c5130[4];
int FUN_001c5030();

void FUN_001c4700(int arg0, int arg1) {
    FUN_001b68c0();
    if (FUN_002fe290(arg1, igNode_GetMetaObject()) != 0) {
        FUN_001e06c0(arg0, arg1, &FUN_001c5030);
    }
    if (FUN_002fe290(arg1, igPlanarShadowShader_GetMetaObject()) != 0) {
        FUN_001e06c0(arg0, arg1, &DAT_001c5130[0]);
    }
}
