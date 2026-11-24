static const char *g_igEnbayaAnimationSource_playModeNames[] = {
    "REPEAT", "CLAMP", "BOUNCE", "LOOP",
    "OFFSET_CLAMP",
};
static int g_igEnbayaAnimationSource_playModeValues[] = {
    0, 1, 2, 3, 4,
};
igMetaEnum *g_igEnbayaAnimationSource_playModeMetaEnum;

igMetaEnum *FUN_001a21b0(void) {
    if (g_igEnbayaAnimationSource_playModeMetaEnum == 0) {
        g_igEnbayaAnimationSource_playModeMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("PLAY_MODE", g_igEnbayaAnimationSource_playModeNames, g_igEnbayaAnimationSource_playModeValues, 5);
    }
    return g_igEnbayaAnimationSource_playModeMetaEnum;
}

namespace Gap {
namespace Sg {

igMetaObject *igEnbayaAnimationSource::_Meta;
igMetaField *igEnbayaAnimationSource::k_enbayaAnimationStream;
igMetaField *igEnbayaAnimationSource::k_interpolationMethod;
igMetaField *igEnbayaAnimationSource::k_drivenChannels;
igMetaField *igEnbayaAnimationSource::k_playMode;
igMetaField *igEnbayaAnimationSource::k_lastUpdateTimef;
igMetaField *igEnbayaAnimationSource::k_lastUpdateTime;

igMetaObject *igEnbayaAnimationSource::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igEnbayaAnimationSource::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igEnbayaAnimationSource::retrieveVTablePointer()
{
    igEnbayaAnimationSource temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igEnbayaAnimationSource::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igEnbayaAnimationSource::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igEnbayaAnimationSource",
        sizeof(igEnbayaAnimationSource),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        FUN_001a24d0,
        0
    );
}

void igEnbayaAnimationSource::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igMemoryRefMetaField_Create, (FieldFactory)Gap::Core::igUnsignedCharArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igUnsignedCharMetaField::_instantiateFromPool, igEnumMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool };
    static const char *names[] = { "_enbayaAnimationStream", "_interpolationMethod", "_drivenChannels", "_playMode", "_lastUpdateTimef", "_lastUpdateTime" };
    static igMetaField **enumStorage[] = { &k_enbayaAnimationStream, &k_interpolationMethod, &k_drivenChannels, &k_playMode, &k_lastUpdateTimef, &k_lastUpdateTime };
    static int offsets[] = { 32, 8, 11, 12, 16, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 6);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igUnsignedCharArrayMetaField *metaField = (igUnsignedCharArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_num = 3;
    }
    {
        igUnsignedCharMetaField *metaField = (igUnsignedCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(3);
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())FUN_001a21b0;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(-1.0f);
        metaField->_persistent = 0;
    }
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)FUN_001a24e0);
}
}
}

void FUN_001a24d0(void) {
    FUN_001c07d0();
}

void FUN_001a24e0(void) {
    FUN_001c07e0();
}

