namespace Gap {
namespace Gfx {

bool igExternalImageEntry::load(Core::igResolveFunction *userFunction)
{
    igImage *image = igImage::_instantiateFromPool(getMemoryPool());
    if (!loadWork(image)) {
        image->release();
        return false;
    }
    setRef(image);
    image->release();
    return true;
}

bool igExternalImageEntry::loadWork(igImage *image)
{
    char *name;
    char *path;
    int length;
    int total;

    if (!image->load(_entryName.p)) {
        name = _entryName.p;
        length = strlen(_externalFilePath.p);
        length = length + strlen("/");
        total = strlen(name);
        total = total + length;
        path = (char *)malloc(total + 1);
        strcpy(path, _externalFilePath.p);
        strcat(path, "/");
        strcat(path, _entryName.p);
        if (!image->load(path)) {
            free(path);
            return false;
        }
        free(path);
    }
    return true;
}

void igExternalImageEntry::initDefaults()
{
    igExternalDirEntry::initDefaults();
    setDirectoryName((const char *)text_igImageDirectory);
}
}
}

