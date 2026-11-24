namespace Gap {
namespace Bec {

igMetaObject *beHitLandResultData::_Meta;
igMetaField *beHitLandResultData::k_infoName;
igMetaField *beHitLandResultData::k_ramNo;

beHitLandResultData *beHitLandResultData::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beHitLandResultData *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beHitLandResultData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beHitLandResultData::retrieveVTablePointer()
{
    beHitLandResultData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beHitLandResultData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beHitLandResultData::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beHitLandResultData",
        sizeof(beHitLandResultData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beHitLandResultData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_infoName", "_ramNo" };
    static igMetaField **enumStorage[] = { &k_infoName, &k_ramNo };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault("");
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

