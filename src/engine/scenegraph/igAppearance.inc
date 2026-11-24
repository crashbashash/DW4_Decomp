namespace Gap {
namespace Sg {

igMetaObject *igAppearance::_Meta;
igMetaField *igAppearance::k_skin;
igMetaField *igAppearance::k_attachedSkins;
igMetaField *igAppearance::k_attachedGraphs;
igMetaField *igAppearance::k_segmentOverrideNameList;
igMetaField *igAppearance::k_segmentOverrideGraphList;

igMetaObject *igAppearance::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igAppearance::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAppearance::retrieveVTablePointer()
{
    igAppearance temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igAppearance::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAppearance::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igSkin::arkRegister, Gap::Sg::igSkinList::arkRegister, Gap::Sg::igModelViewMatrixBoneSelectList::arkRegister, igStringObjList_EnsureRegistered, Gap::Sg::igNodeList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAppearance",
        sizeof(igAppearance),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igAppearance::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_skin", "_attachedSkins", "_attachedGraphs", "_segmentOverrideNameList", "_segmentOverrideGraphList" };
    static igMetaField **enumStorage[] = { &k_skin, &k_attachedSkins, &k_attachedGraphs, &k_segmentOverrideNameList, &k_segmentOverrideGraphList };
    static int offsets[] = { 12, 16, 20, 24, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igSkin::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igSkinList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Sg::igModelViewMatrixBoneSelectList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Sg::igNodeList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

