namespace Gap {
namespace Gfx {

igMetaObject *igVertexStream::_Meta;
igMetaField *igVertexStream::k_stream;
igMetaField *igVertexStream::k_isConfigured;
igMetaField *igVertexStream::k_vertexDataList;
igMetaField *igVertexStream::k_accessMode;
igMetaField *igVertexStream::k_primitive;
igMetaField *igVertexStream::k_streamMode;
}
}

static const char *g_igVertexStream_vertexStreamCompileModeNames[] = {
    "IG_VERTEX_STREAM_COMPILE_ALL", "IG_VERTEX_STREAM_COMPILE_COMPACT_MAX", "IG_VERTEX_STREAM_COMPILE_EVERYTHING",
};
static int g_igVertexStream_vertexStreamCompileModeValues[] = {
    0, 1, 2,
};
namespace Gap {
namespace Gfx {

igMetaEnum *igVertexStream::IG_VERTEX_STREAM_COMPILE_MODE_Meta;

igMetaEnum *igVertexStream::getIG_VERTEX_STREAM_COMPILE_MODEMetaEnum() {
    if (IG_VERTEX_STREAM_COMPILE_MODE_Meta == 0) {
        IG_VERTEX_STREAM_COMPILE_MODE_Meta = igMetaEnum::createMetaEnum("IG_VERTEX_STREAM_COMPILE_MODE", g_igVertexStream_vertexStreamCompileModeNames, g_igVertexStream_vertexStreamCompileModeValues, 3);
    }
    return IG_VERTEX_STREAM_COMPILE_MODE_Meta;
}
}
}

static const char *g_igVertexStream_vertexAccessModeNames[] = {
    "IG_VERTEX_ACCESS_READ_WRITE", "IG_VERTEX_ACCESS_READ", "IG_VERTEX_ACCESS_WRITE", "IG_VERTEX_ACCESS_WRITE_ONCE",
};
static int g_igVertexStream_vertexAccessModeValues[] = {
    0, 1, 2, 3,
};
namespace Gap {
namespace Gfx {

igMetaEnum *igVertexStream::IG_VERTEX_ACCESS_MODE_Meta;

igMetaEnum *igVertexStream::getIG_VERTEX_ACCESS_MODEMetaEnum() {
    if (IG_VERTEX_ACCESS_MODE_Meta == 0) {
        IG_VERTEX_ACCESS_MODE_Meta = igMetaEnum::createMetaEnum("IG_VERTEX_ACCESS_MODE", g_igVertexStream_vertexAccessModeNames, g_igVertexStream_vertexAccessModeValues, 4);
    }
    return IG_VERTEX_ACCESS_MODE_Meta;
}

igVertexStream *igVertexStream::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVertexStream *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVertexStream::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igVertexStream::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igVertexStream::retrieveVTablePointer()
{
    igVertexStream temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igVertexStream::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVertexStream::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igVertexDataList_EnsureRegistered, 0 };

    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVertexStream",
        sizeof(igVertexStream),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igVertexStream::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igRawRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create };
    static const char *names[] = { "_stream", "_isConfigured", "_vertexDataList", "_accessMode", "_primitive", "_streamMode" };
    static igMetaField **enumStorage[] = { &k_stream, &k_isConfigured, &k_vertexDataList, &k_accessMode, &k_primitive, &k_streamMode };
    static int offsets[] = { 12, 16, 20, 24, 28, 32 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 6);
    {
        igRawRefMetaField *metaField = (igRawRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igVertexDataList_GetOrCreateMetaObject();
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Gfx::igVertexStream::getIG_VERTEX_ACCESS_MODEMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_DRAW_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Gfx::igVertexStream::getIG_VERTEX_STREAM_COMPILE_MODEMetaEnum;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())Gap::Gfx::igPsx2VertexStream::getClassMetaSafe;
}
}
}

