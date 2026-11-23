namespace Gap {
namespace Sg {

igMetaObject *igTraversal::_Meta;
igMetaField *igTraversal::k_nodeSelectProcEnabled;
igMetaField *igTraversal::k_nodeSelectProc;
igMetaField *igTraversal::k_timeLong;
igMetaField *igTraversal::k_userTimeState;
igMetaField *igTraversal::k_travProcs;
igTraversalFunctionList *igTraversal::travProcs;

igMetaObject *igTraversal::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTraversal::retrieveVTablePointer()
{
    igTraversal temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTraversal::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTraversal::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igTraversalFunctionList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTraversal",
        sizeof(igTraversal),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Sg::igTraversal::arkRegisterUser,
        regFunctions
    );
}

void igTraversal::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igRawRefMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igBoolMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_nodeSelectProcEnabled", "_nodeSelectProc", "_timeLong", "_userTimeState", "_travProcs" };
    static igMetaField **enumStorage[] = { &k_nodeSelectProcEnabled, &k_nodeSelectProc, &k_timeLong, &k_userTimeState, &k_travProcs };
    static int offsets[] = { 8, 12, 16, 24, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(-1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Sg::igTraversalFunctionList::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)thunk_FUN_001e0470);
}

void igTraversal::arkRegisterUser() {
    userRegister();
    igMetaObject_AddRegistrationCallback((int)((int *)registerClass));
}
}
}

void thunk_FUN_001e0470(void) {
    Gap::Sg::igTraversal::userUnregister();
}

