namespace Gap {
namespace Core {

igMetaObject *igBitMask::_Meta;
igMetaField *igBitMask::k_bitCount;

igMetaObject *igBitMask::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igBitMask::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBitMask::retrieveVTablePointer()
{
    igBitMask temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBitMask::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBitMask::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igUnsignedIntList::arkRegisterInternal,
        Gap::Core::igUnsignedIntList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBitMask",
        sizeof(igBitMask),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}
}
}

namespace Gap {
namespace Core {

void igBitMask::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igUnsignedIntMetaField_Create };
    static const char *names[] = { "_bitCount" };
    static igMetaField **enumStorage[] = { &k_bitCount };
    static int offsets[] = { 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

