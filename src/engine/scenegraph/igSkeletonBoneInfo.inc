namespace Gap {
namespace Sg {

igMetaObject *igSkeletonBoneInfo::_Meta;
igMetaField *igSkeletonBoneInfo::k_parentIdx;
igMetaField *igSkeletonBoneInfo::k_bmIdx;
igMetaField *igSkeletonBoneInfo::k_flags;

igMetaObject *igSkeletonBoneInfo::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igSkeletonBoneInfo::retrieveVTablePointer()
{
    igSkeletonBoneInfo temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igSkeletonBoneInfo::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igSkeletonBoneInfo::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igSkeletonBoneInfo",
        sizeof(igSkeletonBoneInfo),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igSkeletonBoneInfo::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_parentIdx", "_bmIdx", "_flags" };
    static igMetaField **enumStorage[] = { &k_parentIdx, &k_bmIdx, &k_flags };
    static int offsets[] = { 12, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

