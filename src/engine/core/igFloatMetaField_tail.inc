int igFloatMetaField_GetSize(void) {
    return 4;
}

void igFloatMetaField_SetDefault(igMetaField *self, float value) {
    float defaultValue;

    defaultValue = value;
    ((igMetaFieldView *)(self))->SetDefault(&defaultValue);
}

int igFloatMetaField_GetAlignment(void) {
    return 0x10;
}

void igFolder_SetFolderName(igFolderView *self, const char *name) {
    igSmartPointer<igStringObj> h = self->GetFullPath(name);
    char *text = (char *)h.p->_buffer;
    text = (text == 0) ? g_stringObjEmptyText : text;
    self->_folderName = text;
}

