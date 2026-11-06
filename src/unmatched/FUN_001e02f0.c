extern char DAT_001e0790[];
int igNode_GetMetaObject();
int igGroup_GetMetaObject();
int FUN_001e06c0();
int FUN_002fe290();
int FUN_001e07a0();

void FUN_001e02f0(int arg0, int arg1) {
    if (FUN_002fe290(arg1, igNode_GetMetaObject()) != 0) {
        if (FUN_002fe290(arg1, igGroup_GetMetaObject()) != 0) {
            FUN_001e06c0(arg0, arg1, &FUN_001e07a0);
            return;
        }
        FUN_001e06c0(arg0, arg1, (int *)DAT_001e0790);
    }
}
