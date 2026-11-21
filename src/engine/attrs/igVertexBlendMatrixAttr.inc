namespace Gap {
namespace Attrs {

igMetaObject *igVertexBlendMatrixAttr::_Meta;
igMetaField *igVertexBlendMatrixAttr::k_m;
igMetaField *igVertexBlendMatrixAttr::k_blendMatID;

igVertexBlendMatrixAttr *igVertexBlendMatrixAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVertexBlendMatrixAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVertexBlendMatrixAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igVertexBlendMatrixAttr::retrieveVTablePointer()
{
    igVertexBlendMatrixAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igVertexBlendMatrixAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVertexBlendMatrixAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVertexBlendMatrixAttr",
        sizeof(igVertexBlendMatrixAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igVertexBlendMatrixAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, igUnsignedShortMetaField_Create };
    static const char *names[] = { "_m", "_blendMatID" };
    static igMetaField **enumStorage[] = { &k_m, &k_blendMatID };
    static int offsets[] = { 12, 76 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                          igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    }
    {
        igUnsignedShortMetaField *metaField = (igUnsignedShortMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igVertexBlendMatrixAttr::synchronizeCachedUnitID;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

void igMatrix44f_FromRows(float *matrix, const igVec4f *row0, const igVec4f *row1, const igVec4f *row2,
                          const igVec4f *row3) {
    matrix[0] = row0->vec[0];
    matrix[1] = row0->vec[1];
    matrix[2] = row0->vec[2];
    matrix[3] = row0->vec[3];
    matrix[4] = row1->vec[0];
    matrix[5] = row1->vec[1];
    matrix[6] = row1->vec[2];
    matrix[7] = row1->vec[3];
    matrix[8] = row2->vec[0];
    matrix[9] = row2->vec[1];
    matrix[10] = row2->vec[2];
    matrix[11] = row2->vec[3];
    matrix[12] = row3->vec[0];
    matrix[13] = row3->vec[1];
    matrix[14] = row3->vec[2];
    matrix[15] = row3->vec[3];
}

