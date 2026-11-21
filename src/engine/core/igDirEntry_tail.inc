namespace Gap {
namespace Core {

void igDirEntry::refEntry(void *ref) {

}

void igDirEntry::releaseEntry(void *ref) {

}

igDirEntry *igDirEntry::share(igIGBFile *igb) {
    return this;
}

int igDirEntry::refNeedsEntryForPostFileReadCleanup() {
    return 0;
}

void igDirEntry::setMemoryPoolHandle(int handle) {

}

int igDirEntry::getMemoryPoolHandle() {
    return -1;
}

void igDirEntry::writeMemorySpecial(igIGBFile *igb) {

}

void igDirEntry::writeWrite(igIGBFile *igb) {

}

void igDirEntry::writeMakeProxy(igIGBFile *igb) {

}

void igDirEntry::writeComputeBufferSize(igIGBFile *igb) {

}

void igDirEntry::readMemorySpecial(igIGBFile *igb) {

}

void igDirEntry::readFinishConstruction(bool doMakeConcrete) {

}

void igDirEntry::readPostRead(igIGBFile *igb) {

}

void igDirEntry::readReadVersion3(igIGBFile *igb) {

}

void igDirEntry::readRead(igIGBFile *igb) {

}

void igDirEntry::readPreRead(igIGBFile *igb) {

}

void igDirEntry::readSetup(igIGBFile *igb) {

}

void igDirEntry::initDefaults() {
    igObject_InitDefaults((::igObject *)this);
    setName(0);
}

void igDirEntry::setRef(void *refParam) {
    _ref = (int)refParam;
}

void igDirEntry::refRef(void *refParam) {

}

void igDirEntry::releaseRef(void *refParam) {

}
}
}

