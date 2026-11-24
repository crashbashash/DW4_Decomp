namespace Gap {
namespace Bec {

igMetaObject *beCameraDemoData::_Meta;
igMetaField *beCameraDemoData::k_cameraPath;
igMetaField *beCameraDemoData::k_endTime;
igMetaField *beCameraDemoData::k_totalSec;

igMetaObject *beCameraDemoData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beCameraDemoData::retrieveVTablePointer()
{
    beCameraDemoData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beCameraDemoData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beCameraDemoData::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igGraphPath::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beCameraDemoData",
        sizeof(beCameraDemoData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beCameraDemoData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_cameraPath", "_endTime", "_totalSec" };
    static igMetaField **enumStorage[] = { &k_cameraPath, &k_endTime, &k_totalSec };
    static int offsets[] = { 8, 16, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igGraphPath::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

