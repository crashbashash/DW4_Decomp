namespace Gap {
namespace Attrs {

igMetaObject *igTextureFunctionAttr::_Meta;
igMetaField *igTextureFunctionAttr::k_mode;
igMetaField *igTextureFunctionAttr::k_unitID;
igMetaField *igTextureFunctionAttr::k_arg0;
igMetaField *igTextureFunctionAttr::k_arg1;
igMetaField *igTextureFunctionAttr::k_type;
igMetaField *igTextureFunctionAttr::k_call_state;
igMetaField *igTextureFunctionAttr::k_functionType;

igTextureFunctionAttr *igTextureFunctionAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTextureFunctionAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTextureFunctionAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTextureFunctionAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTextureFunctionAttr::retrieveVTablePointer()
{
    igTextureFunctionAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTextureFunctionAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTextureFunctionAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTextureFunctionAttr",
        sizeof(igTextureFunctionAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        FUN_00131f70,
        0
    );
}
}
}

int g_igTextureFunctionAttr_modeDefault = 1;

namespace Gap {
namespace Attrs {

void igTextureFunctionAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create, igIntMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, (FieldFactory)Gap::Core::igUnsignedCharMetaField::_instantiateFromPool, igEnumMetaField_Create };
    static const char *names[] = { "_mode", "_unitID", "_arg0", "_arg1", "_type", "_call_state", "_functionType" };
    static igMetaField **enumStorage[] = { &k_mode, &k_unitID, &k_arg0, &k_arg1, &k_type, &k_call_state, &k_functionType };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igTextureFunctionAttr::synchronizeCachedUnitID;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())TEXTURE_ARGUMENT_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())TEXTURE_ARGUMENT_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())TEXTURE_STAGE_TYPE_GetMetaEnum;
    }
    {
        igUnsignedCharMetaField *metaField = (igUnsignedCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(2);
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())TEXTURE_FUNCTION_TYPE_GetMetaEnum;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

void FUN_00131f70(void) {
    FUN_001412a0();
}

