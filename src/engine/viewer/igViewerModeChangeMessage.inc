namespace Gap {
namespace Viewer {

igMetaObject *igViewerModeChangeMessage::_Meta;
igMetaField *igViewerModeChangeMessage::k_state;
igMetaField *igViewerModeChangeMessage::k_mode;

igMetaObject *igViewerModeChangeMessage::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igViewerModeChangeMessage::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewerModeChangeMessage::retrieveVTablePointer()
{
    igViewerModeChangeMessage temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewerModeChangeMessage::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewerModeChangeMessage::arkRegisterInternal()
{
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Insight::igMessage::arkRegisterInternal,
        Gap::Insight::igMessage::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewerModeChangeMessage",
        sizeof(igViewerModeChangeMessage),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igViewerModeChangeMessage::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igStringMetaField_Create };
    static const char *names[] = { "_state", "_mode" };
    static igMetaField **enumStorage[] = { &k_state, &k_mode };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

