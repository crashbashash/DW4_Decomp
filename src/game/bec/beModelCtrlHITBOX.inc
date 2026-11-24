namespace Gap {
namespace Bec {

igMetaObject *beModelCtrlHITBOX::_Meta;
igMetaField *beModelCtrlHITBOX::k_kind;
igMetaField *beModelCtrlHITBOX::k_start;
igMetaField *beModelCtrlHITBOX::k_length;
igMetaField *beModelCtrlHITBOX::k_offset;
igMetaField *beModelCtrlHITBOX::k_boxSize;
}
}

beModelCtrlHITBOX *beModelCtrlHITBOX_Create(int allocator) {
    Gap::Bec::beModelCtrlHITBOX::arkRegister();
    return (beModelCtrlHITBOX *)igMetaObject_CreateInstance(Gap::Bec::beModelCtrlHITBOX::getClassMeta(), (igMemoryPoolView *)allocator);
}

namespace Gap {
namespace Bec {

igMetaObject *beModelCtrlHITBOX::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beModelCtrlHITBOX::retrieveVTablePointer()
{
    beModelCtrlHITBOX temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlHITBOX::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beModelCtrlHITBOX::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beModelCtrlHITBOX",
        sizeof(beModelCtrlHITBOX),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beModelCtrlHITBOX::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool };
    static const char *names[] = { "_kind", "_start", "_length", "_offset", "_boxSize" };
    static igMetaField **enumStorage[] = { &k_kind, &k_start, &k_length, &k_offset, &k_boxSize };
    static int offsets[] = { 12, 16, 20, 24, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

