namespace Gap {
namespace Bec {

igMetaObject *beDataObjBool::_Meta;
igMetaField *beDataObjBool::k_data;

beDataObjBool *beDataObjBool::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beDataObjBool *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beDataObjBool::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beDataObjBool::retrieveVTablePointer()
{
    beDataObjBool temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beDataObjBool::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beDataObjBool::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beDataObjBool",
        sizeof(beDataObjBool),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beDataObjBool::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create };
    static const char *names[] = { "_data" };
    static igMetaField **enumStorage[] = { &k_data };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

