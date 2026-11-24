namespace Gap {
namespace Bec {

igMetaObject *beWeaponSeqData::_Meta;
igMetaField *beWeaponSeqData::k_label;

igMetaObject *beWeaponSeqData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beWeaponSeqData::retrieveVTablePointer()
{
    beWeaponSeqData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beWeaponSeqData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beWeaponSeqData::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beWeaponSeqData",
        sizeof(beWeaponSeqData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beWeaponSeqData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create };
    static const char *names[] = { "_label" };
    static igMetaField **enumStorage[] = { &k_label };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

igMetaEnum *g_beWeaponSeqData_msgActionMetaEnum;
static const char *g_beWeaponSeqData_msgActionNames[] = {
    "GENERATE", "REMOVE", "GETINFONAME",
};
static int g_beWeaponSeqData_msgActionValues[] = {
    0, 1, 2,
};

igMetaEnum *beWeaponSeqData_GetMsgActionEnum(void) {
    if (g_beWeaponSeqData_msgActionMetaEnum == 0) {
        g_beWeaponSeqData_msgActionMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("MsgAction", g_beWeaponSeqData_msgActionNames, g_beWeaponSeqData_msgActionValues, 3);
    }
    return g_beWeaponSeqData_msgActionMetaEnum;
}

