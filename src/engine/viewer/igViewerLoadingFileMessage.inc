namespace Gap {
namespace Viewer {

igMetaObject *igViewerLoadingFileMessage::_Meta;
igMetaField *igViewerLoadingFileMessage::k_current;
igMetaField *igViewerLoadingFileMessage::k_filename;

igViewerLoadingFileMessage *igViewerLoadingFileMessage::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igViewerLoadingFileMessage *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igViewerLoadingFileMessage::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewerLoadingFileMessage::retrieveVTablePointer()
{
    igViewerLoadingFileMessage temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewerLoadingFileMessage::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewerLoadingFileMessage::arkRegisterInternal()
{
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Insight::igMessage::arkRegisterInternal,
        Gap::Insight::igMessage::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewerLoadingFileMessage",
        sizeof(igViewerLoadingFileMessage),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igViewerLoadingFileMessage::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igStringMetaField_Create };
    static const char *names[] = { "_current", "_filename" };
    static igMetaField **enumStorage[] = { &k_current, &k_filename };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault("");
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

