namespace Gap {
namespace Bec {

igMetaObject *beSelectCtrlInfoWork::_Meta;
igMetaField *beSelectCtrlInfoWork::k_offsetPos;
igMetaField *beSelectCtrlInfoWork::k_selectMax;
igMetaField *beSelectCtrlInfoWork::k_isCancel;
igMetaField *beSelectCtrlInfoWork::k_svSeqName;
igMetaField *beSelectCtrlInfoWork::k_decideList;

beSelectCtrlInfoWork *beSelectCtrlInfoWork::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beSelectCtrlInfoWork *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beSelectCtrlInfoWork::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beSelectCtrlInfoWork::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSelectCtrlInfoWork::retrieveVTablePointer()
{
    beSelectCtrlInfoWork temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSelectCtrlInfoWork::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSelectCtrlInfoWork::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igBoolList::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSelectCtrlInfoWork",
        sizeof(beSelectCtrlInfoWork),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beSelectCtrlInfoWork::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igBoolMetaField_Create, igStringMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_offsetPos", "_selectMax", "_isCancel", "_svSeqName", "_decideList" };
    static igMetaField **enumStorage[] = { &k_offsetPos, &k_selectMax, &k_isCancel, &k_svSeqName, &k_decideList };
    static int offsets[] = { 8, 20, 24, 28, 32 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Core::igBoolList::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

igMetaEnum *g_beSelectCtrlInfoWork_msgActionMetaEnum;
static const char *g_beSelectCtrlInfoWork_msgActionNames[] = {
    "GENERATE", "ISEND", "GETSELECT", "ISSELECTNOW",
    "FO2TOP", "ISFO2TOP", "REMOVE",
};
static int g_beSelectCtrlInfoWork_msgActionValues[] = {
    0, 1, 2, 3, 4, 5, 6,
};

igMetaEnum *beSelectCtrl_GetMessageEnum(void) {
    if (g_beSelectCtrlInfoWork_msgActionMetaEnum == 0) {
        g_beSelectCtrlInfoWork_msgActionMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("MsgAction", g_beSelectCtrlInfoWork_msgActionNames, g_beSelectCtrlInfoWork_msgActionValues, 7);
    }
    return g_beSelectCtrlInfoWork_msgActionMetaEnum;
}

