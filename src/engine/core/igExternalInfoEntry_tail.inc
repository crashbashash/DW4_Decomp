namespace Gap {
namespace Core {

void igExternalInfoEntry::readSetup(igIGBFile *igb)
{
    igInfo *info;

    info = ((igDirectory *)(*(int *)(((::igDirectoryList *)((::igDirectory *)igb)->_externalDirectoryList)->_data + (_directoryIndex * 4))))->getInfo(_infoName.p);
    if (info != 0) {
        ((igDirectory *)igb)->setRef(_index, info->resolve(_key.p));
        return;
    }
    ((igDirectory *)igb)->setRef(_index, 0);
}
}
}

/* Adds a directory entry that finds `object` again on load through `info`, under `key`; an object
 * already in the directory is not added twice. */
bool igDirectory_AddExternalInfoRef(Gap::Core::igDirectory *directory, Gap::Core::igInfo *info, const char *key, Gap::Core::igObject *object) {
    int index = directory->binaryFind((Gap::Core::igRefMetaField *)Gap::Core::igDirEntry::k_ref, object);
    if (index >= 0 && index < directory->_count && (Gap::Core::igObject *)directory->getRef(index) == object) {
        return 0;
    }
    igSmartPointer<igExternalInfoEntryView> entry((igExternalInfoEntryView *)Gap::Core::igExternalInfoEntry::_instantiateFromPool(directory->getMemoryPool()));
    entry.get()->setDirectoryIndex(directory->_externalDirectoryList->find(info->_directory, 0));
    entry.get()->setInfoName(info->_name.p != 0 ? (char *)info->_name.p : (char *)emptyString);
    entry.get()->setKey((char *)key);
    entry.get()->SetRef((int)object);
    entry.get()->_index = index;
    insertObject((igDataList *)directory, index, entry.get());
    return 1;
}
