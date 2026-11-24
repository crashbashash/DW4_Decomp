namespace Gap {
namespace Sg {

igMetaObject *igBlendMatrixSelect::_Meta;
igMetaField *igBlendMatrixSelect::k_blendMatrixIndices;
igMetaField *igBlendMatrixSelect::k_skeletonTransform;
igMetaField *igBlendMatrixSelect::k_skeletonInverseTransform;

igMetaObject *igBlendMatrixSelect::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBlendMatrixSelect::retrieveVTablePointer()
{
    igBlendMatrixSelect temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBlendMatrixSelect::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBlendMatrixSelect::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igIntList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igAttrSet::arkRegisterInternal,
        Gap::Sg::igAttrSet::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBlendMatrixSelect",
        sizeof(igBlendMatrixSelect),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igBlendMatrixSelect::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool };
    static const char *names[] = { "_blendMatrixIndices", "_skeletonTransform", "_skeletonInverseTransform" };
    static igMetaField **enumStorage[] = { &k_blendMatrixIndices, &k_skeletonTransform, &k_skeletonInverseTransform };
    static int offsets[] = { 40, 44, 108 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

