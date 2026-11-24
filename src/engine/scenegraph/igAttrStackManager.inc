namespace Gap {
namespace Sg {

igMetaObject *igAttrStackManager::_Meta;
igMetaField *igAttrStackManager::k_numAttrStacks;
igMetaField *igAttrStackManager::k_attrStacks;
igMetaField *igAttrStackManager::k_attrDefaults;
igMetaField *igAttrStackManager::k_attrIncrementalUpdateList;
igMetaField *igAttrStackManager::k_attrRootUpdateList;
igMetaField *igAttrStackManager::k_nextAttrUpdateList;
igMetaField *igAttrStackManager::k_lightAttrAddrs;
igMetaField *igAttrStackManager::k_lightAttrStackAddrs;
igMetaField *igAttrStackManager::k_updateLightAttrs;
igMetaField *igAttrStackManager::k_popProcData;
igMetaField *igAttrStackManager::k_capabilityManager;
igMetaField *igAttrStackManager::k_defaultManager;
igMetaField *igAttrStackManager::k_simpleLightMgr;
igMetaField *igAttrStackManager::k_lightDisableAttrPool;
igMetaField *igAttrStackManager::k_stackChanged;
igMetaField *igAttrStackManager::k_attrStackIndexTable;
igMetaField *igAttrStackManager::k_attrStackIndexTableSize;

igMetaObject *igAttrStackManager::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igAttrStackManager::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAttrStackManager::retrieveVTablePointer()
{
    igAttrStackManager temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igAttrStackManager::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAttrStackManager::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igAttrStackList::arkRegister, Gap::Attrs::igAttrList::arkRegister, Gap::Core::igIntList::arkRegister, Gap::Attrs::igNonRefCountedAttrList::arkRegister, Gap::Core::igIntList::arkRegister, Gap::Gfx::igCapabilityManager::arkRegister, Gap::Attrs::igAttrDefaultManager::arkRegister, Gap::Sg::igLightStateAttrPool::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAttrStackManager",
        sizeof(igAttrStackManager),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Sg::igAttrStackManager::userRegister,
        regFunctions
    );
}

void igAttrStackManager::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igRawRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igMemoryRefMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_numAttrStacks", "_attrStacks", "_attrDefaults", "_attrIncrementalUpdateList", "_attrRootUpdateList", "_nextAttrUpdateList", "_lightAttrAddrs", "_lightAttrStackAddrs", "_updateLightAttrs", "_popProcData", "_capabilityManager", "_defaultManager", "_simpleLightMgr", "_lightDisableAttrPool", "_stackChanged", "_attrStackIndexTable", "_attrStackIndexTableSize" };
    static igMetaField **enumStorage[] = { &k_numAttrStacks, &k_attrStacks, &k_attrDefaults, &k_attrIncrementalUpdateList, &k_attrRootUpdateList, &k_nextAttrUpdateList, &k_lightAttrAddrs, &k_lightAttrStackAddrs, &k_updateLightAttrs, &k_popProcData, &k_capabilityManager, &k_defaultManager, &k_simpleLightMgr, &k_lightDisableAttrPool, &k_stackChanged, &k_attrStackIndexTable, &k_attrStackIndexTableSize };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 8, 68, 72 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 17);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igAttrStackList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Attrs::igAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)Gap::Attrs::igNonRefCountedAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)Gap::Attrs::igNonRefCountedAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_metaObject = (int)Gap::Gfx::igCapabilityManager::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_metaObject = (int)Gap::Attrs::igAttrDefaultManager::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_metaObject = (int)Gap::Sg::igLightStateAttrPool::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->_memType = (int)Gap::Core::igIntMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)Gap::Sg::igAttrStackManager::_classDestructor);
}

void igAttrStackManager::userRegister() {
    igMetaObject_AddRegistrationCallback((int)&registerClass);
}

void igAttrStackManager::_classDestructor() {
    userUnregister();
}
}
}

