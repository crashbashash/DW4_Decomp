namespace Gap {
namespace Bec {

igMetaObject *beBaseInfoDataList::_Meta;
}
}

beBaseInfoDataList *beBaseInfoDataList_Create(int allocator) {
    Gap::Bec::beBaseInfoDataList::arkRegister();
    return (beBaseInfoDataList *)igMetaObject_CreateInstance(Gap::Bec::beBaseInfoDataList::getClassMeta(), (igMemoryPoolView *)allocator);
}

namespace Gap {
namespace Bec {

igMetaObject *beBaseInfoDataList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beBaseInfoDataList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beBaseInfoDataList::retrieveVTablePointer()
{
    beBaseInfoDataList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beBaseInfoDataList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beBaseInfoDataList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Bec::beBaseInfoData::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beBaseInfoDataList",
        sizeof(beBaseInfoDataList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

