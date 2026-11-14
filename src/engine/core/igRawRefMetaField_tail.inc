/* Prints `<indent><field> = 0x<value>`: a raw reference is a pointer, shown as its address. */
void igRawRefMetaField_Print(igRawRefMetaField *self, char *object, int unusedArg, const char *indent) {
    igReport_Printf(DAT_004faef0, indent, self->_fieldName, (int)*(void **)(object + self->_offset));
    igReport_Flush();
}

int igRawRefMetaField_Write(igRawRefArrayMetaField *arg0, int arg1, int arg2) {
    if (arg0->_persistent == 1) {
        return igDirectory_AddRawRef((igDirectoryView *)arg2, *(int *)(arg1 + arg0->_offset), 0, 0);
    }
    return -1;
}

int **igRawRefMetaField_Construct(int **arg0, int extra1) {
    igRefMetaField_Construct((igRefMetaField *)arg0);
    *arg0 = &DAT_00532eb0[0];
    if (arg0 != 0) {
        igRawRefMetaField_Init(arg0);
    }
    return arg0;
}

int **igRawRefMetaField_Init(int **arg0) {
    igRefMetaField_Init((igRefMetaField *)arg0);
    *arg0 = &DAT_00532eb0[0];
    return arg0;
}

int **igRawRefMetaField_CopyConstruct(int **arg0, int extra1) {
    igRefMetaField_CopyConstruct((igRefMetaField *)arg0, (igRefMetaField *)extra1);
    *arg0 = &DAT_00532eb0[0];
    return arg0;
}

void igRawRefMetaField_Destruct(igRawRefMetaField *self) {
    igRefMetaField_Destruct((igRefMetaField *)self);
}

int igRefMetaField_ValueFromString(void) {
    return 0;
}

void igRefMetaField_ValueToString(int *arg0) {
    *arg0 = 0;
}

