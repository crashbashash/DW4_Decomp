namespace Gap {
namespace Bec {

igMetaObject *beModelCtrlInfoAI::_Meta;
igMetaField *beModelCtrlInfoAI::k_seqName;
igMetaField *beModelCtrlInfoAI::k_mapNo;
igMetaField *beModelCtrlInfoAI::k_worldPos;
igMetaField *beModelCtrlInfoAI::k_hStatus;
igMetaField *beModelCtrlInfoAI::k_hCount;

beModelCtrlInfoAI *beModelCtrlInfoAI::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beModelCtrlInfoAI *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beModelCtrlInfoAI::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beModelCtrlInfoAI::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beModelCtrlInfoAI::retrieveVTablePointer()
{
    beModelCtrlInfoAI temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlInfoAI::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beModelCtrlInfoAI::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beModelCtrlInfoAI",
        sizeof(beModelCtrlInfoAI),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beModelCtrlInfoAI::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_seqName", "_mapNo", "_worldPos", "_hStatus", "_hCount" };
    static igMetaField **enumStorage[] = { &k_seqName, &k_mapNo, &k_worldPos, &k_hStatus, &k_hCount };
    static int offsets[] = { 8, 12, 16, 28, 32 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

