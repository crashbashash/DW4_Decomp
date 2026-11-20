igSmartPointer<igObject> igFolder_GetFullPath(igFolder *folder, int name) {
    igSmartPointer<igObject> item(((igObject *)igStringObj_Create(((int)((Gap::Core::igObject *)folder)->getMemoryPool()))));
    igStringObj_Format((igStringObj *)item.get(),"%s/%s", folder->_folderName, name);
    return item;
}

