namespace Gap {
namespace Bec {

igMetaObject *beParticleCtrl2InfoWork::_Meta;
igMetaField *beParticleCtrl2InfoWork::k_positionLockNode;
igMetaField *beParticleCtrl2InfoWork::k_positionLockOffset;

beParticleCtrl2InfoWork *beParticleCtrl2InfoWork::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beParticleCtrl2InfoWork *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beParticleCtrl2InfoWork::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beParticleCtrl2InfoWork::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beParticleCtrl2InfoWork::retrieveVTablePointer()
{
    beParticleCtrl2InfoWork temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beParticleCtrl2InfoWork::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beParticleCtrl2InfoWork::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { beModelCtrlNode2_EnsureRegistered, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beParticleCtrl2InfoWork",
        sizeof(beParticleCtrl2InfoWork),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beParticleCtrl2InfoWork::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool };
    static const char *names[] = { "_positionLockNode", "_positionLockOffset" };
    static igMetaField **enumStorage[] = { &k_positionLockNode, &k_positionLockOffset };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)beModelCtrlNode2_GetOrCreateMetaObject();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

