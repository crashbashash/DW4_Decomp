namespace Gap {
namespace Gfx {

igMetaObject *igClut::_Meta;
igMetaField *igClut::k_fmt;
igMetaField *igClut::k_numEntries;
igMetaField *igClut::k_stride;
igMetaField *igClut::k_pData;
igMetaField *igClut::k_clutSize;
igMetaField *igClut::k_clutDirty;
igMetaField *igClut::k_isAlphaScaled;

igClut *igClut::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igClut *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igClut::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igClut::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igClut::retrieveVTablePointer()
{
    igClut temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igClut::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igClut::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igClut",
        sizeof(igClut),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}
}
}

static int g_igClut_fmtDefault = -1;

namespace Gap {
namespace Gfx {

void igClut::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create, igUnsignedIntMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_fmt", "_numEntries", "_stride", "_pData", "_clutSize", "_clutDirty", "_isAlphaScaled" };
    static igMetaField **enumStorage[] = { &k_fmt, &k_numEntries, &k_stride, &k_pData, &k_clutSize, &k_clutDirty, &k_isAlphaScaled };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 29 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(-1);
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(-1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(1);
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())Gap::Gfx::igPsx2Clut::getClassMetaSafe;
}
}
}

