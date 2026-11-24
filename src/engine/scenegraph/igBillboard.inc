namespace Gap {
namespace Sg {

igMetaObject *igBillboard::_Meta;
igMetaField *igBillboard::k_mode;
igMetaField *igBillboard::k_axis;
igMetaField *igBillboard::k_origin;
igMetaField *igBillboard::k_mvm;

igMetaObject *igBillboard::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBillboard::retrieveVTablePointer()
{
    igBillboard temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBillboard::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBillboard::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igModelViewMatrixAttr::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igGroup::arkRegisterInternal,
        Gap::Sg::igGroup::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBillboard",
        sizeof(igBillboard),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igBillboard::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_mode", "_axis", "_origin", "_mvm" };
    static igMetaField **enumStorage[] = { &k_mode, &k_axis, &k_origin, &k_mvm };
    static int offsets[] = { 32, 36, 48, 60 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 1.0f));
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Attrs::igModelViewMatrixAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

