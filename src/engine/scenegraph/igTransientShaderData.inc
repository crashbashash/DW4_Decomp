namespace Gap {
namespace Sg {

igMetaObject *igTransientShaderData::_Meta;
igMetaField *igTransientShaderData::k_attrPushLists;
igMetaField *igTransientShaderData::k_attrPopLists;
igMetaField *igTransientShaderData::k_dataPumps;
igMetaField *igTransientShaderData::k_childLists;

igMetaObject *igTransientShaderData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTransientShaderData::retrieveVTablePointer()
{
    igTransientShaderData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igTransientShaderData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTransientShaderData::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igAttrListList::arkRegister, igDataPumpInfo_EnsureRegistered, Gap::Sg::igNodeListList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igShaderData::arkRegisterInternal,
        Gap::Sg::igShaderData::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTransientShaderData",
        sizeof(igTransientShaderData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

igMetaObject *igShaderData::_Meta;
igMetaField *igShaderData::k_attrPushLists;
igMetaField *igShaderData::k_attrPopLists;
igMetaField *igShaderData::k_dataPumps;
igMetaField *igShaderData::k_childLists;

void igTransientShaderData::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_attrPushLists");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igObjectRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_metaObject = (int)Gap::Attrs::igAttrListList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
        metaField->_externalEnumStorage = (int)&k_attrPushLists;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_attrPopLists");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igObjectRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_metaObject = (int)Gap::Attrs::igAttrListList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
        metaField->_externalEnumStorage = (int)&k_attrPopLists;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_dataPumps");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igObjectRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_metaObject = (int)igDataPumpInfo_GetOrCreateMetaObject();
        metaField->setDefault(0);
        metaField->_persistent = 0;
        metaField->_externalEnumStorage = (int)&k_dataPumps;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_childLists");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igObjectRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_metaObject = (int)Gap::Sg::igNodeListList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
        metaField->_externalEnumStorage = (int)&k_childLists;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
}
}
}

