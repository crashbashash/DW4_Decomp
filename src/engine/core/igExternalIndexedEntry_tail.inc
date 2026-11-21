namespace Gap {
namespace Core {

void igExternalIndexedEntry::readPreRead(igIGBFile *igb)
{
    setRef((void *)((igDirectory *)(((int *)((::igObjectList *)((::igDirectory *)igb)->_externalDirectoryList)->_data)[_directoryIndex]))->getRef(_entryIndex));
    ((igDirectory *)igb)->setRef(_index, (void *)_ref);
}
}
}

