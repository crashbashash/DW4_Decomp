namespace Gap {
namespace Bec {

igMetaObject *beNumVerData::_Meta;
igMetaField *beNumVerData::k_disp;
igMetaField *beNumVerData::k_verDataList;

igMetaObject *beNumVerData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beNumVerData::retrieveVTablePointer()
{
    beNumVerData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beNumVerData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beNumVerData::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Bec::beNumVerInsideDataList::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beNumVerData",
        sizeof(beNumVerData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beNumVerData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_disp", "_verDataList" };
    static igMetaField **enumStorage[] = { &k_disp, &k_verDataList };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Bec::beNumVerInsideDataList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

