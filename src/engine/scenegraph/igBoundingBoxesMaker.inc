namespace Gap {
namespace Sg {

igBoundingBoxesMaker *igBoundingBoxesMaker::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igBoundingBoxesMaker *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igBoundingBoxesMaker::_Meta;
igMetaField *igBoundingBoxesMaker::k_time;
igMetaField *igBoundingBoxesMaker::k_useWholeAnimation;
igMetaField *igBoundingBoxesMaker::k_setBoundingBoxes;
igMetaField *igBoundingBoxesMaker::k_skinnedBox;
igMetaField *igBoundingBoxesMaker::k_bboxList;
igMetaField *igBoundingBoxesMaker::k_preserveActorBoxes;
igMetaField *igBoundingBoxesMaker::k_exclusionList;
igMetaField *igBoundingBoxesMaker::k_metaObjectList;

igMetaObject *igBoundingBoxesMaker::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBoundingBoxesMaker::retrieveVTablePointer()
{
    igBoundingBoxesMaker temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBoundingBoxesMaker::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBoundingBoxesMaker::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igAABox_EnsureRegistered, igObjectStringMap_EnsureRegistered, igStringObj_EnsureRegistered, igMetaObjectList_EnsureRegistered, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBoundingBoxesMaker",
        sizeof(igBoundingBoxesMaker),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igBoundingBoxesMaker::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_time", "_useWholeAnimation", "_setBoundingBoxes", "_skinnedBox", "_bboxList", "_preserveActorBoxes", "_exclusionList", "_metaObjectList" };
    static igMetaField **enumStorage[] = { &k_time, &k_useWholeAnimation, &k_setBoundingBoxes, &k_skinnedBox, &k_bboxList, &k_preserveActorBoxes, &k_exclusionList, &k_metaObjectList };
    static int offsets[] = { 8, 16, 17, 20, 24, 28, 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 8);
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(1);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igAABox_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igObjectStringMap_GetOrCreateMetaObject();
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

