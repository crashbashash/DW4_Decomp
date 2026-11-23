namespace Gap {
namespace Sg {

igMetaObject *igSkeleton::_Meta;
igMetaField *igSkeleton::k_boneInfoList;
igMetaField *igSkeleton::k_invJointArray;
igMetaField *igSkeleton::k_jointCount;

igMetaObject *igSkeleton::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igSkeleton::retrieveVTablePointer()
{
    igSkeleton temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igSkeleton::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igSkeleton::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igSkeletonBoneInfoList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igAnimationHierarchy::arkRegisterInternal,
        Gap::Sg::igAnimationHierarchy::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igSkeleton",
        sizeof(igSkeleton),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

igMetaObject *igAnimationHierarchy::_Meta;
igMetaField *igAnimationHierarchy::k_boneTranslationArray;

void igSkeleton::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igMemoryRefMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_boneInfoList", "_invJointArray", "_jointCount" };
    static igMetaField **enumStorage[] = { &k_boneInfoList, &k_invJointArray, &k_jointCount };
    static int offsets[] = { 16, 20, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igSkeletonBoneInfoList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_memType = (int)Gap::Math::igMatrix44fMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

