/* Prints `<indent><field> = 0x<value>`: a raw reference is a pointer, shown as its address. */
void igRawRefMetaField_Print(igRawRefMetaField *self, char *object, int unusedArg, const char *indent) {
    igReport_Printf(text_s_s_0x_x, indent, self->_fieldName, (int)*(void **)(object + self->_offset));
    igReport_Flush();
}

int igRawRefMetaField_Write(igRawRefArrayMetaField *self, int object, int directory) {
    if (self->_persistent == 1) {
        return igDirectory_AddRawRef((igDirectoryView *)directory, *(int *)(object + self->_offset), 0, 0);
    }
    return -1;
}

int **igRawRefMetaField_Construct(int **self, int extra1) {
    igRefMetaField_Construct((igRefMetaField *)self);
    *self = &g_igRawRefMetaField_vtable[0];
    if (self != 0) {
        igRawRefMetaField_Init(self);
    }
    return self;
}

int **igRawRefMetaField_Init(int **self) {
    igRefMetaField_Init((igRefMetaField *)self);
    *self = &g_igRawRefMetaField_vtable[0];
    return self;
}

int **igRawRefMetaField_CopyConstruct(int **self, int source) {
    igRefMetaField_CopyConstruct((igRefMetaField *)self, (igRefMetaField *)source);
    *self = &g_igRawRefMetaField_vtable[0];
    return self;
}

void igRawRefMetaField_Destruct(igRawRefMetaField *self) {
    igRefMetaField_Destruct((igRefMetaField *)self);
}

int igRefMetaField_ValueFromString(void) {
    return 0;
}

void igRefMetaField_ValueToString(int *result) {
    *result = 0;
}

