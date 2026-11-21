static const char *g_igDirEntry_refTypeNames[] = {
    "kObjectRef", "kMemoryRef", "kRawRef",
};
static int g_igDirEntry_refTypeValues[] = {
    0, 1, 2,
};

namespace Gap {
namespace Core {

igMetaEnum *igDirEntry::getRefTypeMetaEnum() {
    if (RefType_Meta == 0) {
        RefType_Meta = Gap::Core::igMetaEnum::createMetaEnum("RefType", g_igDirEntry_refTypeNames, g_igDirEntry_refTypeValues, 3);
    }
    return RefType_Meta;
}
}
}

static const char *g_igDirEntry_resolveMethodNames[] = {
    "kLocal", "kNameSpace", "kGlobal",
};
static int g_igDirEntry_resolveMethodValues[] = {
    0, 1, 2,
};

namespace Gap {
namespace Core {

igMetaEnum *igDirEntry::getResolveMethodMetaEnum() {
    if (ResolveMethod_Meta == 0) {
        ResolveMethod_Meta = Gap::Core::igMetaEnum::createMetaEnum("ResolveMethod", g_igDirEntry_resolveMethodNames, g_igDirEntry_resolveMethodValues, 3);
    }
    return ResolveMethod_Meta;
}

igDirEntry *igDirEntry::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igDirEntry *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igDirEntry::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igDirEntry::retrieveVTablePointer()
{
    igDirEntry temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igDirEntry::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igDirEntry::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igDirEntry",
        sizeof(igDirEntry),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igDirEntry::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igRawRefMetaField_Create };
    static const char *names[] = { "_index", "_resolveMethod", "_refType", "_ref" };
    static igMetaField **enumStorage[] = { &k_index, &k_resolveMethod, &k_refType, &k_ref };
    static int offsets[] = { 12, 16, 20, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Core::igDirEntry::getResolveMethodMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Core::igDirEntry::getRefTypeMetaEnum;
    }
    {
        igRawRefMetaField *metaField = (igRawRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

