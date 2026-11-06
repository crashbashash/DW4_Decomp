extern char DAT_001cf980[];
int igTransform_GetMetaObject();
int igNode_GetMetaObject();
int igGroup_GetMetaObject();
int igGeometry_GetMetaObject();
int FUN_001e02f0();
int FUN_001e06c0();
int FUN_002fe290();
int FUN_001cf990();
int FUN_001cfaa0();
int FUN_001cfc70();

void FUN_001ce790(int arg0, int arg1) {
    FUN_001e02f0();
    if (FUN_002fe290(arg1, igNode_GetMetaObject()) != 0) {
        if (FUN_002fe290(arg1, igGeometry_GetMetaObject()) != 0) {
            FUN_001e06c0(arg0, arg1, &FUN_001cfc70);
            return;
        }
        if (FUN_002fe290(arg1, igTransform_GetMetaObject()) != 0) {
            FUN_001e06c0(arg0, arg1, &FUN_001cfaa0);
            return;
        }
        if (FUN_002fe290(arg1, igGroup_GetMetaObject()) != 0) {
            FUN_001e06c0(arg0, arg1, &FUN_001cf990);
            return;
        }
        FUN_001e06c0(arg0, arg1, (int *)DAT_001cf980);
    }
}
