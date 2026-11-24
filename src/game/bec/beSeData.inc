namespace Gap {
namespace Bec {

igMetaObject *beSeData::_Meta;
igMetaField *beSeData::k_sound;
igMetaField *beSeData::k_delay;

igMetaObject *beSeData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSeData::retrieveVTablePointer()
{
    beSeData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSeData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSeData::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSeData",
        sizeof(beSeData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beSeData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igShortMetaField_Create };
    static const char *names[] = { "_sound", "_delay" };
    static igMetaField **enumStorage[] = { &k_sound, &k_delay };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

