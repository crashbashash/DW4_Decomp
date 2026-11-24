namespace Gap {
namespace Sg {

igMetaObject *igObjectPool::_Meta;
igMetaField *igObjectPool::k_freeIndex;
igMetaField *igObjectPool::k_capabilityIncrease;
igMetaField *igObjectPool::k_resetMode;

igMetaObject *igObjectPool::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igObjectPool::retrieveVTablePointer()
{
    igObjectPool temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igObjectPool::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igObjectPool::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igObjectPool",
        sizeof(igObjectPool),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igObjectPool::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igBoolMetaField_Create };
    static const char *names[] = { "_freeIndex", "_capabilityIncrease", "_resetMode" };
    static igMetaField **enumStorage[] = { &k_freeIndex, &k_capabilityIncrease, &k_resetMode };
    static int offsets[] = { 20, 24, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(50);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

