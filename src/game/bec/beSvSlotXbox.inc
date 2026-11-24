namespace Gap {
namespace Bec {

igMetaObject *beSvSlotXbox::_Meta;
igMetaField *beSvSlotXbox::k_name;
igMetaField *beSvSlotXbox::k_totalBytes;
igMetaField *beSvSlotXbox::k_freeBytes;
igMetaField *beSvSlotXbox::k_useBytes;

igMetaObject *beSvSlotXbox::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSvSlotXbox::retrieveVTablePointer()
{
    beSvSlotXbox temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSvSlotXbox::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSvSlotXbox::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Bec::beSvSlotData::arkRegisterInternal,
        Gap::Bec::beSvSlotData::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSvSlotXbox",
        sizeof(beSvSlotXbox),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beSvSlotXbox::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igUnsignedLongMetaField_Create, igUnsignedLongMetaField_Create, igUnsignedLongMetaField_Create };
    static const char *names[] = { "_name", "_totalBytes", "_freeBytes", "_useBytes" };
    static igMetaField **enumStorage[] = { &k_name, &k_totalBytes, &k_freeBytes, &k_useBytes };
    static int offsets[] = { 24, 32, 40, 48 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault("");
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

