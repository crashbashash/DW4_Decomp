namespace Gap {
namespace Core {

unsigned short igFloatMetaField::computeSize() {
    return 4;
}

void igFloatMetaField::setDefault(float def)
{
    setDefaultMemory(&def);
}

int igFloatMetaField::computeRequiredAlignment() {
    return 0x10;
}
}
}

void igFolder_SetFolderName(igFolderView *self, const char *name) {
    igSmartPointer<igStringObj> h = self->GetFullPath(name);
    char *text = (char *)h.p->_buffer;
    text = (text == 0) ? g_stringObjEmptyText : text;
    self->_folderName = text;
}

