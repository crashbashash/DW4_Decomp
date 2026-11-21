namespace Gap {
namespace Core {

void igExternalInfoEntry::readSetup(igIGBFile *igb)
{
    void **info;

    info = (void **)(((void **)((igDirectory *)(*(int *)(((::igDirectoryList *)((::igDirectory *)igb)->_externalDirectoryList)->_data + (_directoryIndex * 4))))->getInfo(_infoName.p)));
    if (info != 0) {
        ((igDirectory *)igb)->setRef(_index, (void *)((igInfoView *)(info))->GetFieldValueByName((int)_key.p));
        return;
    }
    ((igDirectory *)igb)->setRef(_index, 0);
}
}
}

/* Adds a directory entry that finds `object` again on load through `info`, under `key`; an object
 * already in the directory is not added twice. */
bool igDirectory_AddExternalInfoRef(igDirectoryView *directory, igInfoView *info, char *key, igObject *object) {
    int index = ((Gap::Core::igDirectory *)directory)->binaryFind((Gap::Core::igRefMetaField *)Gap::Core::igDirEntry::k_ref, object);
    if (index >= 0 && index < directory->_count && (igObject *)((Gap::Core::igDirectory *)directory)->getRef(index) == object) {
        return 0;
    }
    igSmartPointer<igExternalInfoEntryView> entry((igExternalInfoEntryView *)Gap::Core::igExternalInfoEntry::_instantiateFromPool(((Gap::Core::igObject *)directory)->getMemoryPool()));
    entry.get()->setDirectoryIndex(((igSmartPointer<igTDataList<igDirectoryView *> > &)directory->_externalDirectoryList)->find((igDirectoryView *)info->_directory));
    entry.get()->setInfoName(info->_name != 0 ? (char *)info->_name : (char *)emptyString);
    entry.get()->setKey(key);
    entry.get()->SetRef((int)object);
    entry.get()->_index = index;
    insertObject((igDataList *)directory, index, entry.get());
    return 1;
}
