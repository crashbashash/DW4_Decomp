namespace Gap {
namespace Sg {

igBlendListRecord *igBlendListRecord::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igBlendListRecord *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igBlendListRecord::_Meta;
igMetaField *igBlendListRecord::k_attr;
igMetaField *igBlendListRecord::k_fwdPtr;

igMetaObject *igBlendListRecord::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBlendListRecord::retrieveVTablePointer()
{
    igBlendListRecord temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBlendListRecord::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBlendListRecord::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igBlendMatrixPaletteAttr::arkRegister, Gap::Attrs::igAttr::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBlendListRecord",
        sizeof(igBlendListRecord),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igBlendListRecord::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_attr", "_fwdPtr" };
    static igMetaField **enumStorage[] = { &k_attr, &k_fwdPtr };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igBlendMatrixPaletteAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Attrs::igAttr::getClassTypeLazy();
        metaField->_refCounted = 0;
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

