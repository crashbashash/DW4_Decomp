namespace Gap {
namespace Gfx {

igMetaObject *igPsx2VertexArray1_1::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igPsx2VertexArray1_1::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPsx2VertexArray1_1::retrieveVTablePointer()
{
    igPsx2VertexArray1_1 temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPsx2VertexArray1_1::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPsx2VertexArray1_1::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igPointerList::arkRegister, igPsx2LongList_EnsureRegistered, 0 };

    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gfx::igVertexArray1_1::arkRegisterInternal,
        Gap::Gfx::igVertexArray1_1::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPsx2VertexArray1_1",
        sizeof(igPsx2VertexArray1_1),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igPsx2VertexArray1_1::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntArrayMetaField::_instantiateFromPool, igIntMetaField_Create };
    static const char *names[] = { "_pBlendedVertsList", "_pBlendedNormsList", "_pWaitSeqList", "_lastArrayUsed", "_lSequence", "_textureCoordCompiled", "_multipassCompiled" };
    static igMetaField **enumStorage[] = { &k_pBlendedVertsList, &k_pBlendedNormsList, &k_pWaitSeqList, &k_lastArrayUsed, &k_lSequence, &k_textureCoordCompiled, &k_multipassCompiled };
    static int offsets[] = { 48, 52, 56, 60, 64, 72, 136 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igPointerList::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Core::igPointerList::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = igPsx2LongList_GetOrCreateMetaObject();
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_persistent = 0;
    }
    {
        igIntArrayMetaField *metaField = (igIntArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_num = 16;
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_writeProxy = (void (*)())Gap::Gfx::igVertexArray1_1::getClassMetaSafe;
}
}
}

int igPsx2LongList_Create(int arg0) {
    igPsx2LongList_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igPsx2LongList_metaObject, (igMemoryPoolView *)arg0);
}

int igPsx2LongList_GetOrCreateMetaObject(void) {
    if (g_igPsx2LongList_metaObject == 0) {
        g_igPsx2LongList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return (int)g_igPsx2LongList_metaObject;
}

