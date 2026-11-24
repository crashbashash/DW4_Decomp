namespace Gap {
namespace Insight {

igMetaObject *igInfoManager::_Meta;
igMetaField *igInfoManager::k_insight;

igMetaObject *igInfoManager::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igInfoManager::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igInfoManager::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igInsightCore_EnsureRegistered, 0 };

    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igInfoManager",
        sizeof(igInfoManager),
        0,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igInfoManager::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_insight" };
    static igMetaField **enumStorage[] = { &k_insight };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igInsightCore_GetOrCreateMetaObject();
        metaField->_refCounted = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

