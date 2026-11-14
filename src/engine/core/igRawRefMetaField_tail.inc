/* Prints `<indent><field> = 0x<value>`: a raw reference is a pointer, shown as its address. */
void Gap__Core__igRawRefMetaField__vfunc_41(igRawRefMetaField *self, char *object, int unusedArg, const char *indent) {
    FUN_00304430(DAT_004faef0, indent, self->_fieldName, (int)*(void **)(object + self->_offset));
    FUN_00304680();
}

int Gap__Core__igRawRefMetaField__vfunc_43(igRawRefArrayMetaField *arg0, int arg1, int arg2) {
    if (arg0->_persistent == 1) {
        return FUN_002d8d00((igDirectoryView *)arg2, *(int *)(arg1 + arg0->_offset), 0, 0);
    }
    return -1;
}

int **FUN_00305400(int **arg0, int extra1) {
    igRefMetaField_Construct((igRefMetaField *)arg0);
    *arg0 = &DAT_00532eb0[0];
    if (arg0 != 0) {
        FUN_00305440(arg0);
    }
    return arg0;
}

int **FUN_00305440(int **arg0) {
    igRefMetaField_Init((igRefMetaField *)arg0);
    *arg0 = &DAT_00532eb0[0];
    return arg0;
}

int **FUN_00305480(int **arg0, int extra1) {
    igRefMetaField_CopyConstruct((igRefMetaField *)arg0, (igRefMetaField *)extra1);
    *arg0 = &DAT_00532eb0[0];
    return arg0;
}

void Gap__Core__igRawRefMetaField__vfunc_02(void) {
    igRefMetaField_Destruct();
}

int FUN_003054d0(void) {
    return 0;
}

void FUN_003054e0(int *arg0) {
    *arg0 = 0;
}

