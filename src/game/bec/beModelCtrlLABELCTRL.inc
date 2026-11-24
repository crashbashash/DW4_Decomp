namespace Gap {
namespace Bec {

igMetaObject *beModelCtrlLABELCTRL::_Meta;
igMetaField *beModelCtrlLABELCTRL::k_seqName;

igMetaObject *beModelCtrlLABELCTRL::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beModelCtrlLABELCTRL::retrieveVTablePointer()
{
    beModelCtrlLABELCTRL temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlLABELCTRL::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beModelCtrlLABELCTRL::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beModelCtrlLABELCTRL",
        sizeof(beModelCtrlLABELCTRL),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beModelCtrlLABELCTRL::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create };
    static const char *names[] = { "_seqName" };
    static igMetaField **enumStorage[] = { &k_seqName };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

