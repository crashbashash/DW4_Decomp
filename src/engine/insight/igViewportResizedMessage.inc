namespace Gap {
namespace Insight {

igMetaObject *igViewportResizedMessage::_Meta;
igMetaField *igViewportResizedMessage::k_origin;
igMetaField *igViewportResizedMessage::k_size;

igViewportResizedMessage *igViewportResizedMessage::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igViewportResizedMessage *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igViewportResizedMessage::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewportResizedMessage::retrieveVTablePointer()
{
    igViewportResizedMessage temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewportResizedMessage::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewportResizedMessage::arkRegisterInternal()
{
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Insight::igMessage::arkRegisterInternal,
        Gap::Insight::igMessage::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewportResizedMessage",
        sizeof(igViewportResizedMessage),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igViewportResizedMessage::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool };
    static const char *names[] = { "_origin", "_size" };
    static igMetaField **enumStorage[] = { &k_origin, &k_size };
    static int offsets[] = { 8, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

