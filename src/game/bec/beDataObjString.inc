namespace Gap {
namespace Bec {

igMetaObject *beDataObjString::_Meta;
igMetaField *beDataObjString::k_data;

beDataObjString *beDataObjString::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beDataObjString *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beDataObjString::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beDataObjString::retrieveVTablePointer()
{
    beDataObjString temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beDataObjString::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beDataObjString::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beDataObjString",
        sizeof(beDataObjString),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beDataObjString::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create };
    static const char *names[] = { "_data" };
    static igMetaField **enumStorage[] = { &k_data };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(0);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

