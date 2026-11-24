namespace Gap {
namespace Sg {

igMetaObject *igAnimationDatabase::_Meta;
igMetaField *igAnimationDatabase::k_skeletonList;
igMetaField *igAnimationDatabase::k_animationList;
igMetaField *igAnimationDatabase::k_skinList;
igMetaField *igAnimationDatabase::k_appearanceList;
igMetaField *igAnimationDatabase::k_combinerList;

igMetaObject *igAnimationDatabase::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igAnimationDatabase::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igAnimationDatabase::retrieveVTablePointer()
{
    igAnimationDatabase temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igAnimationDatabase::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationDatabase::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igSkeletonList::arkRegister, Gap::Sg::igAnimationList::arkRegister, Gap::Sg::igSkinList::arkRegister, Gap::Sg::igAppearanceList::arkRegister, igAnimationCombinerList_EnsureRegistered, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igInfo::arkRegisterInternal,
        Gap::Core::igInfo::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationDatabase",
        sizeof(igAnimationDatabase),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igAnimationDatabase::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_skeletonList", "_animationList", "_skinList", "_appearanceList", "_combinerList" };
    static igMetaField **enumStorage[] = { &k_skeletonList, &k_animationList, &k_skinList, &k_appearanceList, &k_combinerList };
    static int offsets[] = { 20, 24, 28, 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igSkeletonList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Sg::igAnimationList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Sg::igSkinList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Sg::igAppearanceList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igAnimationCombinerList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

