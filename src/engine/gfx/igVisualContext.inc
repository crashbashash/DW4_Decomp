namespace Gap {
namespace Gfx {

igMetaObject *igVisualContext::_Meta;
igMetaField *igVisualContext::k_contextIndex;
igMetaField *igVisualContext::k_timer;
igMetaField *igVisualContext::k_showFrameRate;
igMetaField *igVisualContext::k_commandLineFrameRate;
igMetaField *igVisualContext::k_primitiveCount;
igMetaField *igVisualContext::k_frameStartTime;
igMetaField *igVisualContext::k_blendMatricesCount;
igMetaField *igVisualContext::k_blendIndex;
igMetaField *igVisualContext::k_inverseTranspose;
igMetaField *igVisualContext::k_blendMatrices;
igMetaField *igVisualContext::k_inverseTransposeCount;
igMetaField *igVisualContext::k_renderingTime;
igMetaField *igVisualContext::k_scissorType;
igMetaField *igVisualContext::k_viewMatrixHint;
igMetaField *igVisualContext::k_viewMatrixInverse;
igMetaField *igVisualContext::k_viewMatrixDirty;
igMetaField *igVisualContext::k_vertexArray2;
igMetaField *igVisualContext::k_customStates;
igMetaField *igVisualContext::k_customFields;
igMetaField *igVisualContext::k_ditherState;
igMetaField *igVisualContext::k_driverDataMemoryPool;
igMetaField *igVisualContext::k_vertexMemoryPool;
igMetaField *igVisualContext::k_internalMemoryPool;
igMetaField *igVisualContext::k_temporaryMemoryPool;
igMetaField *igVisualContext::k_imageMemoryPool;
igMetaField *igVisualContext::k_textureMemoryPool;
igMetaField *igVisualContext::k_statisticsMemoryPool;
igMetaField *igVisualContext::k_listMemoryPool;

igVisualContext *igVisualContext::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVisualContext *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVisualContext::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igVisualContext::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igVisualContext::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVisualContext::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igTimer::arkRegister, Gap::Gfx::igVertexArray2::arkRegister, igCustomStateCollectionList_EnsureRegistered, igCustomStateFieldList_EnsureRegistered, igMemoryPool_EnsureRegistered, 0 };

    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igContext::arkRegisterInternal,
        Gap::Core::igContext::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVisualContext",
        sizeof(igVisualContext),
        0,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igVisualContext::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igIntMetaField_Create, igUnsignedIntMetaField_Create, igMemoryRefMetaField_Create, igRawRefMetaField_Create, igUnsignedIntMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igEnumMetaField_Create, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, igBoolMetaField_Create, (FieldFactory)Gap::Core::igObjectRefArrayMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_contextIndex", "_timer", "_showFrameRate", "_commandLineFrameRate", "_primitiveCount", "_frameStartTime", "_blendMatricesCount", "_blendIndex", "_inverseTranspose", "_blendMatrices", "_inverseTransposeCount", "_renderingTime", "_scissorType", "_viewMatrixHint", "_viewMatrixInverse", "_viewMatrixDirty", "_vertexArray2", "_customStates", "_customFields", "_ditherState", "_driverDataMemoryPool", "_vertexMemoryPool", "_internalMemoryPool", "_temporaryMemoryPool", "_imageMemoryPool", "_textureMemoryPool", "_statisticsMemoryPool", "_listMemoryPool" };
    static igMetaField **enumStorage[] = { &k_contextIndex, &k_timer, &k_showFrameRate, &k_commandLineFrameRate, &k_primitiveCount, &k_frameStartTime, &k_blendMatricesCount, &k_blendIndex, &k_inverseTranspose, &k_blendMatrices, &k_inverseTransposeCount, &k_renderingTime, &k_scissorType, &k_viewMatrixHint, &k_viewMatrixInverse, &k_viewMatrixDirty, &k_vertexArray2, &k_customStates, &k_customFields, &k_ditherState, &k_driverDataMemoryPool, &k_vertexMemoryPool, &k_internalMemoryPool, &k_temporaryMemoryPool, &k_imageMemoryPool, &k_textureMemoryPool, &k_statisticsMemoryPool, &k_listMemoryPool };
    static int offsets[] = { 20, 56, 60, 61, 64, 68, 72, 76, 80, 84, 88, 96, 104, 108, 172, 236, 240, 304, 308, 312, 24, 28, 32, 36, 40, 44, 48, 52 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 28);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Core::igTimer::getClassTypeLazy();
        metaField->_resetMethod = 3;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_persistent = 0;
    }
    {
        igUnsignedIntMetaField *metaField = (igUnsignedIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_persistent = 0;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
        metaField->_persistent = 0;
    }
    {
        igRawRefMetaField *metaField = (igRawRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_persistent = 0;
    }
    {
        igUnsignedIntMetaField *metaField = (igUnsignedIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_persistent = 0;
    }
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->setDefault(0);
        metaField->_persistent = 0;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_SCISSOR_TYPE_GetMetaEnum;
    }
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_persistent = 0;
    }
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->setDefault(1);
        metaField->_persistent = 0;
    }
    {
        igObjectRefArrayMetaField *metaField = (igObjectRefArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 16);
        metaField->_metaObject = (int)Gap::Gfx::igVertexArray2::getClassTypeLazy();
        metaField->_num = 16;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 17);
        metaField->_metaObject = (int)igCustomStateCollectionList_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 18);
        metaField->_metaObject = (int)igCustomStateFieldList_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 19);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 20);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 21);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 22);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 23);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 24);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 25);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 26);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 27);
        metaField->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
        metaField->_resetMethod = 3;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())Gap::Gfx::igPsx2VisualContext::getClassMetaSafe;
}

igMemoryPool *igVisualContext::_defaultDriverDataMemoryPool;
igMemoryPool *igVisualContext::_defaultVertexMemoryPool;
igMemoryPool *igVisualContext::_defaultInternalMemoryPool;
igMemoryPool *igVisualContext::_defaultTemporaryMemoryPool;
igMemoryPool *igVisualContext::_defaultImageMemoryPool;
igMemoryPool *igVisualContext::_defaultTextureMemoryPool;
igMemoryPool *igVisualContext::_defaultStatisticsMemoryPool;
igMemoryPool *igVisualContext::_defaultListMemoryPool;
}
}

