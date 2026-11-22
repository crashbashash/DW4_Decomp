namespace Gap {
namespace Core {

igStringObjRef igFolder::getPathToFile(const char *fileName) const
{
    igStringObjRef item((igStringObj *)igStringObj_Create((int)getMemoryPool()));
    igStringObj_Format(item.get(), "%s/%s", _folderName.p, fileName);
    return item;
}
}
}

