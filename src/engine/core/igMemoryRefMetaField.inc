namespace Gap {
namespace Core {

igMetaObject *igMemoryRefMetaField::_Meta;
igMemoryRefMetaField *igMemoryRefMetaField::_MetaField;
igMetaField *igMemoryRefMetaField::k_shallowCopyMethod;
igMetaField *igMemoryRefMetaField::k_memSize;
igMetaField *igMemoryRefMetaField::k_memType;
igMetaField *igMemoryRefMetaField::k_releaseOnCopy;
igMetaField *igMemoryRefMetaField::k_releaseOnReset;
igMetaField *igMemoryRefMetaField::k_resetMethod;
igMetaField *igMemoryRefMetaField::k_refCounted;
igMetaField *igMemoryRefMetaField::k_alignmentType;
igMetaField *igMemoryRefMetaField::k_memTypeRef;
igMetaField *igMemoryRefMetaField::k_poolName;
}
}

igMetaField *igMemoryRefMetaField_Create(igMemoryPoolView *pool) {
    void **instance;

    if (g_objectSystem->active != 0) {
        Gap::Core::igMemoryRefMetaField::arkRegister();
        instance = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)((int)Gap::Core::igMemoryRefMetaField::getClassMeta()), pool)));
    } else {
        instance = (void **)(((void **)igObject_AllocateRawStorage(0x50, 0, pool)));
        if (instance != 0) {
            instance = (void **)(((void **)igMemoryRefMetaField_Construct((igMemoryRefMetaField *)instance, 1)));
        }
        ((igObjectDispatchView *)(instance))->InitDefaults();
        ((igObjectDispatchView *)(instance))->userConstruct((int)(0));
    }
    return (igMetaField *)instance;
}

namespace Gap {
namespace Core {

igObject *igMemoryRefMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (igObject_AllocateRawStorageDefault(sizeof(igMemoryRefMetaField), 0), 0) igMemoryRefMetaField(*this);
}

igMetaObject *igMemoryRefMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMemoryRefMetaField::retrieveVTablePointer()
{
    igMemoryRefMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMemoryRefMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMemoryRefMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igMetaField::arkRegister, arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igRefMetaField::arkRegisterInternal,
        Gap::Core::igRefMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMemoryRefMetaField",
        sizeof(igMemoryRefMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igMemoryRefMetaField::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igStringMetaField_Create };
    static const char *names[] = { "_memSize", "_memType", "_releaseOnCopy", "_releaseOnReset", "_refCounted", "_alignmentType", "_memTypeRef", "_poolName" };
    static igMetaField **enumStorage[] = { &k_memSize, &k_memType, &k_releaseOnCopy, &k_releaseOnReset, &k_refCounted, &k_alignmentType, &k_memTypeRef, &k_poolName };
    static int offsets[] = { 56, 60, 64, 65, 66, 68, 72, 76 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 8);
    {
        igCharMetaField *metaField = (igCharMetaField *)igMetaObject_FindFieldByName(metaObject, "_shallowCopyMethod");
        int metaIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)metaObject->_metaFields, (int)metaField);
        metaField = (igCharMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->setDefault(2);
        metaField->_externalEnumStorage = (int)&k_shallowCopyMethod;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Core::igMetaField::getClassTypeLazy();
        metaField->_refCounted = 0;
        metaField->_deepCopyMethod = 1;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(1);
    }
    {
        __internalNonRefCountedObjectList *metaFields = (__internalNonRefCountedObjectList *)metaObject->_metaFields;
        int metaIndex = ObjectPointerList_FindIndex(metaFields, (int)igMetaObject_FindFieldByName(metaObject, "_resetMethod"));
        igEnumMetaField *metaField = (igEnumMetaField *)igEnumMetaField_Create(Memory_GetAllocatorBySelector((int)kIGMemoryPoolHandleMetaData));
        metaField->setBasicProperties("_resetMethod", &k_resetMethod, 36, metaObject);
        metaField->setDefault(3);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaField_GetResetTypeMetaEnum;
        metaField->_externalEnumStorage = (int)&k_resetMethod;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(-1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)Gap::Core::igMetaField::getClassTypeLazy();
        metaField->_deepCopyMethod = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igMemoryRefMetaField::arkRegisterMetaValidate()
{
    igMemoryRefMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igMemoryRefMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
        metaField = _MetaField;
        if (metaField != 0) {
            MetaRefList_AppendRetained(getMetaFieldTypes(), (::igObject *)metaField);
            {
                ::igObject *held = (::igObject *)_MetaField;
                held->release();
            }
            _MetaField->_internalIndex = (short)(getMetaFieldTypes()->_count - 1);
            _MetaField->validate();
        }
    }
}

igMemoryRefMetaField *igMemoryRefMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

