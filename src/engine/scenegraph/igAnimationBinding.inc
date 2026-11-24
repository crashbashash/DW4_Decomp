namespace Gap {
namespace Sg {

igAnimationBinding *igAnimationBinding::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igAnimationBinding *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igAnimationBinding::_Meta;
igMetaField *igAnimationBinding::k_hierarchy;
igMetaField *igAnimationBinding::k_boneTrackIdxArray;
igMetaField *igAnimationBinding::k_bindCount;
igMetaField *igAnimationBinding::k_chainSwapList;
igMetaField *igAnimationBinding::k_reflectTrack;

igMetaObject *igAnimationBinding::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimationBinding::retrieveVTablePointer()
{
    igAnimationBinding temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAnimationBinding::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationBinding::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAnimationHierarchy::arkRegister, Gap::Core::igIntList::arkRegister, igBitMask_EnsureRegistered, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationBinding",
        sizeof(igAnimationBinding),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igAnimationBinding::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igMemoryRefMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_hierarchy", "_boneTrackIdxArray", "_bindCount", "_chainSwapList", "_reflectTrack" };
    static igMetaField **enumStorage[] = { &k_hierarchy, &k_boneTrackIdxArray, &k_bindCount, &k_chainSwapList, &k_reflectTrack };
    static int offsets[] = { 8, 12, 16, 20, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igAnimationHierarchy::getClassTypeLazy();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_memType = (int)Gap::Core::igIntMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igBitMask_GetOrCreateMetaObject();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

