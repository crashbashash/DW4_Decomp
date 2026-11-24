namespace Gap {
namespace Bec {

igMetaObject *beSeInfoData::_Meta;
igMetaField *beSeInfoData::k_actionList;

igMetaObject *beSeInfoData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSeInfoData::retrieveVTablePointer()
{
    beSeInfoData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSeInfoData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSeInfoData::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Bec::beSeDataList::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Bec::beBaseInfoData::arkRegisterInternal,
        Gap::Bec::beBaseInfoData::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSeInfoData",
        sizeof(beSeInfoData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beSeInfoData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_actionList" };
    static igMetaField **enumStorage[] = { &k_actionList };
    static int offsets[] = { 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Bec::beSeDataList::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

