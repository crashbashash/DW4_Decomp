int Gap__Core__igFloatMetaField__vfunc_25(void) {
    return 4;
}

void FUN_002e3810(void **arg0, float fparg0) {
    float sp1C;

    sp1C = fparg0;
    ((igMetaFieldView *)(arg0))->SetDefault(&sp1C);
}

int Gap__Core__igFloatMetaField__vfunc_27(void) {
    return 0x10;
}

void FUN_002e3850(igFolderView *self, const char *name) {
    igSmartPointer<igStringObj> h = self->vfunc_23(name);
    char *text = (char *)h.p->_buffer;
    text = (text == 0) ? g_stringObjEmptyText[0] : text;
    self->_folderName = text;
}

