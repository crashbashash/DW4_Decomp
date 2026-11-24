namespace Gap {
namespace Sg {

igModelViewMatrixBoneSelect *igModelViewMatrixBoneSelect::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igModelViewMatrixBoneSelect *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igModelViewMatrixBoneSelect::_Meta;
igMetaField *igModelViewMatrixBoneSelect::k_matrixIndex;

igMetaObject *igModelViewMatrixBoneSelect::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igModelViewMatrixBoneSelect::retrieveVTablePointer()
{
    igModelViewMatrixBoneSelect temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igModelViewMatrixBoneSelect::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igModelViewMatrixBoneSelect::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igModelViewMatrixBoneSelect",
        sizeof(igModelViewMatrixBoneSelect),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igModelViewMatrixBoneSelect::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_matrixIndex" };
    static igMetaField **enumStorage[] = { &k_matrixIndex };
    static int offsets[] = { 32 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

