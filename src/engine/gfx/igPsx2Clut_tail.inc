namespace Gap {
namespace Gfx {

igMetaObject *igPsx2Clut::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPsx2Clut::retrieveVTablePointer()
{
    igPsx2Clut temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPsx2Clut::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPsx2Clut::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gfx::igClut::arkRegisterInternal,
        Gap::Gfx::igClut::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPsx2Clut",
        sizeof(igPsx2Clut),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igPsx2Clut::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_id", "_refCount" };
    static igMetaField **enumStorage[] = { &k_id, &k_refCount };
    static int offsets[] = { 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_writeProxy = (void (*)())Gap::Gfx::igClut::getClassMetaSafe;
}
}
}

