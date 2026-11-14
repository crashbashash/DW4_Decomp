int igFloatMetaField_GetSize(void) {
    return 4;
}

void igFloatMetaField_SetDefault(void **arg0, float fparg0) {
    float sp1C;

    sp1C = fparg0;
    ((igMetaFieldView *)(arg0))->SetDefault(&sp1C);
}

int igFloatMetaField_GetAlignment(void) {
    return 0x10;
}

void igFolder_SetFolderName(igFolderView *self, const char *name) {
    igSmartPointer<igStringObj> h = self->vfunc_23(name);
    char *text = (char *)h.p->_buffer;
    text = (text == 0) ? g_stringObjEmptyText[0] : text;
    self->_folderName = text;
}

