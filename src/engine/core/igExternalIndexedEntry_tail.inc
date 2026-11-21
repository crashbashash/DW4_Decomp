namespace Gap {
namespace Core {

void igExternalIndexedEntry::readPreRead(igIGBFile *igb)
{
    setRef((void *)igDirectory_GetObject((void *)((int *)((::igObjectList *)((::igDirectory *)igb)->_externalDirectoryList)->_data)[_directoryIndex], _entryIndex));
    igDirectory_SetEntryRef((igDirectoryView *)igb, _index, _ref);
}
}
}

