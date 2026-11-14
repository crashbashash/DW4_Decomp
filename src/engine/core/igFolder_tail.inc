igSmartPointer<igObject> igFolder_GetFullPath(igFolder *folder, int name) {
    igSmartPointer<igObject> item(((igObject *)igStringObj_Create(((int)igObject_GetAllocator((int)folder)))));
    igStringObj_Format((int)(item.get()), (int)(&DAT_004f9a78[0]), folder->_folderName, name);
    return item;
}

