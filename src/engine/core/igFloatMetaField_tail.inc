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

void igFolder::appendRelativePath(const char *subdir)
{
    igStringObjRef path = getPathToFile(subdir);
    char *text = (char *)path.p->_buffer;
    text = (text == 0) ? g_stringObjEmptyText : text;
    _folderName = text;
}
}
}

