namespace Gap {
namespace Bec {

igMetaObject *beModelCtrlMOVERL::_Meta;
igMetaField *beModelCtrlMOVERL::k_modelName;
igMetaField *beModelCtrlMOVERL::k_boneName;

igMetaObject *beModelCtrlMOVERL::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beModelCtrlMOVERL::retrieveVTablePointer()
{
    beModelCtrlMOVERL temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlMOVERL::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beModelCtrlMOVERL::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beModelCtrlMOVERL",
        sizeof(beModelCtrlMOVERL),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beModelCtrlMOVERL::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igStringMetaField_Create };
    static const char *names[] = { "_modelName", "_boneName" };
    static igMetaField **enumStorage[] = { &k_modelName, &k_boneName };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

