namespace Gap {
namespace Bec {

igMetaObject *beSvPlatDataGC::_Meta;
igMetaField *beSvPlatDataGC::k_connectMax;
igMetaField *beSvPlatDataGC::k_fileName;
igMetaField *beSvPlatDataGC::k_imageSize;
igMetaField *beSvPlatDataGC::k_dataOffSet;
igMetaField *beSvPlatDataGC::k_bannerType;
igMetaField *beSvPlatDataGC::k_iconType;
igMetaField *beSvPlatDataGC::k_iconKaz;
igMetaField *beSvPlatDataGC::k_iconSpeed;
igMetaField *beSvPlatDataGC::k_iconLoopType;
igMetaField *beSvPlatDataGC::k_banTplSize;
igMetaField *beSvPlatDataGC::k_banTplData;
igMetaField *beSvPlatDataGC::k_iconTplSize;
igMetaField *beSvPlatDataGC::k_iconTplData;
igMetaField *beSvPlatDataGC::k_comment;

igMetaObject *beSvPlatDataGC::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSvPlatDataGC::retrieveVTablePointer()
{
    beSvPlatDataGC temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSvPlatDataGC::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSvPlatDataGC::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Bec::beSvPlatBaseData::arkRegisterInternal,
        Gap::Bec::beSvPlatBaseData::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSvPlatDataGC",
        sizeof(beSvPlatDataGC),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beSvPlatDataGC::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igMemoryRefMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igMemoryRefMetaField_Create, (FieldFactory)Gap::Core::igCharArrayMetaField::_instantiateFromPool };
    static const char *names[] = { "_fileName", "_imageSize", "_dataOffSet", "_bannerType", "_iconType", "_iconKaz", "_iconSpeed", "_iconLoopType", "_banTplSize", "_banTplData", "_iconTplSize", "_iconTplData", "_comment" };
    static igMetaField **enumStorage[] = { &k_fileName, &k_imageSize, &k_dataOffSet, &k_bannerType, &k_iconType, &k_iconKaz, &k_iconSpeed, &k_iconLoopType, &k_banTplSize, &k_banTplData, &k_iconTplSize, &k_iconTplData, &k_comment };
    static int offsets[] = { 104, 108, 24, 112, 116, 120, 124, 128, 132, 32, 136, 36, 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 13);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_FindFieldByName(metaObject, "_connectMax");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igIntMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->setDefault(2);
        metaField->_externalEnumStorage = (int)&k_connectMax;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igIntArrayMetaField *metaField = (igIntArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_num = 2;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igCharArrayMetaField *metaField = (igCharArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_num = 64;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

