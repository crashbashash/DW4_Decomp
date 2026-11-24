namespace Gap {
namespace Bec {

igMetaObject *beGeneraterItemDataOne::_Meta;
igMetaField *beGeneraterItemDataOne::k_id;
igMetaField *beGeneraterItemDataOne::k_rank;
igMetaField *beGeneraterItemDataOne::k_rate;

igMetaObject *beGeneraterItemDataOne::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beGeneraterItemDataOne::retrieveVTablePointer()
{
    beGeneraterItemDataOne temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beGeneraterItemDataOne::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beGeneraterItemDataOne::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beGeneraterItemDataOne",
        sizeof(beGeneraterItemDataOne),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beGeneraterItemDataOne::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_id", "_rank", "_rate" };
    static igMetaField **enumStorage[] = { &k_id, &k_rank, &k_rate };
    static int offsets[] = { 12, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

igMetaEnum *g_beGeneraterItemDataOne_msgActionMetaEnum;
static const char *g_beGeneraterItemDataOne_msgActionNames[] = {
    "START", "STOP", "STOPREVERS", "RESET",
    "RESTART", "PERFECTDROP", "ONFREEZE", "OFFREEZE",
};
static int g_beGeneraterItemDataOne_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
};

igMetaEnum *beGenerater_GetMsgActionEnum(void) {
    if (g_beGeneraterItemDataOne_msgActionMetaEnum == 0) {
        g_beGeneraterItemDataOne_msgActionMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("MsgAction", g_beGeneraterItemDataOne_msgActionNames, g_beGeneraterItemDataOne_msgActionValues, 8);
    }
    return g_beGeneraterItemDataOne_msgActionMetaEnum;
}

