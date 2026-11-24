namespace Gap {
namespace Viewer {

igMetaObject *igActorManagerParams::_Meta;
igMetaField *igActorManagerParams::k_skelOnly;
igMetaField *igActorManagerParams::k_skelAndSkin;

igMetaObject *igActorManagerParams::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igActorManagerParams::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igActorManagerParams::retrieveVTablePointer()
{
    igActorManagerParams temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igActorManagerParams::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igActorManagerParams::arkRegisterInternal()
{
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igModel::arkRegisterInternal,
        Gap::Gui::igModel::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igActorManagerParams",
        sizeof(igActorManagerParams),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igActorManagerParams::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_skelOnly", "_skelAndSkin" };
    static igMetaField **enumStorage[] = { &k_skelOnly, &k_skelAndSkin };
    static int offsets[] = { 12, 13 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

