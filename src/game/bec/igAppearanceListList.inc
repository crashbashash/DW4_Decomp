namespace Gap {
namespace Bec {

igMetaObject *igAppearanceListList::_Meta;

igMetaObject *igAppearanceListList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igAppearanceListList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAppearanceListList::retrieveVTablePointer()
{
    igAppearanceListList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAppearanceListList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAppearanceListList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAppearanceList::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAppearanceListList",
        sizeof(igAppearanceListList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

igMetaObject *g_igModelViewMatrixBoneSelectListBec_metaObject;

igMetaObject *igModelViewMatrixBoneSelectListBec_GetOrCreateMetaObject(void) {
    if (g_igModelViewMatrixBoneSelectListBec_metaObject == 0) {
        g_igModelViewMatrixBoneSelectListBec_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igModelViewMatrixBoneSelectListBec_metaObject;
}

