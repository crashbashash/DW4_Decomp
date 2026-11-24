namespace Gap {
namespace Bec {

igMetaObject *beSvSlotData::_Meta;
igMetaField *beSvSlotData::k_isConnect;
igMetaField *beSvSlotData::k_isFormat;
igMetaField *beSvSlotData::k_freeSize;
igMetaField *beSvSlotData::k_useSize;
igMetaField *beSvSlotData::k_totalSize;

igMetaObject *beSvSlotData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void beSvSlotData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSvSlotData::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSvSlotData",
        sizeof(beSvSlotData),
        0,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beSvSlotData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_isConnect", "_isFormat", "_freeSize", "_useSize", "_totalSize" };
    static igMetaField **enumStorage[] = { &k_isConnect, &k_isFormat, &k_freeSize, &k_useSize, &k_totalSize };
    static int offsets[] = { 8, 9, 12, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

