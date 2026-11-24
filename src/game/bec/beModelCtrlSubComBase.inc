namespace Gap {
namespace Bec {

igMetaObject *beModelCtrlSubComBase::_Meta;
igMetaField *beModelCtrlSubComBase::k_isOneSet;
igMetaField *beModelCtrlSubComBase::k_runFrame;
igMetaField *beModelCtrlSubComBase::k_startFrame;

igMetaObject *beModelCtrlSubComBase::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void beModelCtrlSubComBase::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beModelCtrlSubComBase::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beModelCtrlSubComBase",
        sizeof(beModelCtrlSubComBase),
        0,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beModelCtrlSubComBase::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_isOneSet", "_runFrame", "_startFrame" };
    static igMetaField **enumStorage[] = { &k_isOneSet, &k_runFrame, &k_startFrame };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(0.0f);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

