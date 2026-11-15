igSmartPointer<igObject> igFolder_GetFullPath(igFolder *folder, int name) {
    igSmartPointer<igObject> item(((igObject *)igStringObj_Create(((int)igObject_GetAllocator((int)folder)))));
    igStringObj_Format((igStringObj *)item.get(),"%s/%s", folder->_folderName, name);
    return item;
}

