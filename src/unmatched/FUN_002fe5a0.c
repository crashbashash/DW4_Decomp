int FUN_002fe300();
int igMetaObject_CountTree();
int igMetaObject_FinalizeFieldLayout();
void FUN_002fe5a0(int arg0) {
    int temp_s1;
    int var_s0;
    temp_s1 = igMetaObject_CountTree();
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        igMetaObject_FinalizeFieldLayout(FUN_002fe300(arg0, var_s0));
    }
}
