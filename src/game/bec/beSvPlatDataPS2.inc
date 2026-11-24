namespace Gap {
namespace Bec {

igMetaObject *beSvPlatDataPS2::_Meta;
igMetaField *beSvPlatDataPS2::k_connectMax;
igMetaField *beSvPlatDataPS2::k_dirName;
igMetaField *beSvPlatDataPS2::k_title;
igMetaField *beSvPlatDataPS2::k_offsLF;
igMetaField *beSvPlatDataPS2::k_transRate;
igMetaField *beSvPlatDataPS2::k_bgColor0;
igMetaField *beSvPlatDataPS2::k_bgColor1;
igMetaField *beSvPlatDataPS2::k_bgColor2;
igMetaField *beSvPlatDataPS2::k_bgColor3;
igMetaField *beSvPlatDataPS2::k_lightDir0;
igMetaField *beSvPlatDataPS2::k_lightDir1;
igMetaField *beSvPlatDataPS2::k_lightDir2;
igMetaField *beSvPlatDataPS2::k_lightColor0;
igMetaField *beSvPlatDataPS2::k_lightColor1;
igMetaField *beSvPlatDataPS2::k_lightColor2;
igMetaField *beSvPlatDataPS2::k_ambient;
igMetaField *beSvPlatDataPS2::k_fnameIcon0;
igMetaField *beSvPlatDataPS2::k_fnameIcon1;
igMetaField *beSvPlatDataPS2::k_fnameIcon2;
igMetaField *beSvPlatDataPS2::k_saveDataSize;
igMetaField *beSvPlatDataPS2::k_dataOffSet;
igMetaField *beSvPlatDataPS2::k_iconCount;
igMetaField *beSvPlatDataPS2::k_image;

igMetaObject *beSvPlatDataPS2::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSvPlatDataPS2::retrieveVTablePointer()
{
    beSvPlatDataPS2 temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSvPlatDataPS2::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSvPlatDataPS2::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igObjectList::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Bec::beSvPlatBaseData::arkRegisterInternal,
        Gap::Bec::beSvPlatBaseData::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSvPlatDataPS2",
        sizeof(beSvPlatDataPS2),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beSvPlatDataPS2::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igStringMetaField_Create, igUnsignedShortMetaField_Create, igUnsignedIntMetaField_Create, (FieldFactory)Gap::Core::igShortArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igShortArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igShortArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igShortArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatArrayMetaField::_instantiateFromPool, igStringMetaField_Create, igStringMetaField_Create, igStringMetaField_Create, igUnsignedIntMetaField_Create, (FieldFactory)Gap::Core::igIntArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_dirName", "_title", "_offsLF", "_transRate", "_bgColor0", "_bgColor1", "_bgColor2", "_bgColor3", "_lightDir0", "_lightDir1", "_lightDir2", "_lightColor0", "_lightColor1", "_lightColor2", "_ambient", "_fnameIcon0", "_fnameIcon1", "_fnameIcon2", "_saveDataSize", "_dataOffSet", "_iconCount", "_image" };
    static igMetaField **enumStorage[] = { &k_dirName, &k_title, &k_offsLF, &k_transRate, &k_bgColor0, &k_bgColor1, &k_bgColor2, &k_bgColor3, &k_lightDir0, &k_lightDir1, &k_lightDir2, &k_lightColor0, &k_lightColor1, &k_lightColor2, &k_ambient, &k_fnameIcon0, &k_fnameIcon1, &k_fnameIcon2, &k_saveDataSize, &k_dataOffSet, &k_iconCount, &k_image };
    static int offsets[] = { 24, 28, 32, 36, 40, 48, 56, 64, 72, 88, 104, 120, 136, 152, 168, 184, 188, 192, 204, 196, 208, 212 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 22);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_FindFieldByName(metaObject, "_connectMax");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igIntMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->setDefault(5);
        metaField->_externalEnumStorage = (int)&k_connectMax;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igShortArrayMetaField *metaField = (igShortArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_num = 4;
    }
    {
        igShortArrayMetaField *metaField = (igShortArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_num = 4;
    }
    {
        igShortArrayMetaField *metaField = (igShortArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_num = 4;
    }
    {
        igShortArrayMetaField *metaField = (igShortArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_num = 4;
    }
    {
        igFloatArrayMetaField *metaField = (igFloatArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_num = 4;
    }
    {
        igFloatArrayMetaField *metaField = (igFloatArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_num = 4;
    }
    {
        igFloatArrayMetaField *metaField = (igFloatArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_num = 4;
    }
    {
        igFloatArrayMetaField *metaField = (igFloatArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_num = 4;
    }
    {
        igFloatArrayMetaField *metaField = (igFloatArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_num = 4;
    }
    {
        igFloatArrayMetaField *metaField = (igFloatArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_num = 4;
    }
    {
        igFloatArrayMetaField *metaField = (igFloatArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->_num = 4;
    }
    {
        igIntArrayMetaField *metaField = (igIntArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 19);
        metaField->_num = 2;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 21);
        metaField->_metaObject = (int)Gap::Core::igObjectList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

