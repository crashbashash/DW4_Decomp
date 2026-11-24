namespace Gap {
namespace Sg {

igMetaObject *igLod::_Meta;
igMetaField *igLod::k_rangeList;
igMetaField *igLod::k_lastRange;
igMetaField *igLod::k_lastIndex;
igMetaField *igLod::k_lastLower;
igMetaField *igLod::k_lastUpper;
igMetaField *igLod::k_center;
igMetaField *igLod::k_hysteresisList;

igMetaObject *igLod::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igLod::retrieveVTablePointer()
{
    igLod temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igLod::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igLod::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igFloatList::arkRegister, Gap::Sg::igNode::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igLod",
        sizeof(igLod),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igLod::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_rangeList", "_lastRange", "_lastIndex", "_lastLower", "_lastUpper", "_center", "_hysteresisList" };
    static igMetaField **enumStorage[] = { &k_rangeList, &k_lastRange, &k_lastIndex, &k_lastLower, &k_lastUpper, &k_center, &k_hysteresisList };
    static int offsets[] = { 32, 36, 40, 44, 48, 52, 64 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igFloatList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_deepCopyMethod = 0;
        metaField->_shallowCopyMethod = 2;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igNode::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(0.0f);
        metaField->_persistent = 0;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(0.0f);
        metaField->_persistent = 0;
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)Gap::Core::igFloatList::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

