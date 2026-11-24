namespace Gap {
namespace Bec {

igMetaObject *beSvPs2McImage128k::_Meta;
igMetaField *beSvPs2McImage128k::k_dataSize;
igMetaField *beSvPs2McImage128k::k_data;

igMetaObject *beSvPs2McImage128k::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSvPs2McImage128k::retrieveVTablePointer()
{
    beSvPs2McImage128k temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSvPs2McImage128k::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSvPs2McImage128k::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSvPs2McImage128k",
        sizeof(beSvPs2McImage128k),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beSvPs2McImage128k::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igMemoryRefMetaField_Create };
    static const char *names[] = { "_dataSize", "_data" };
    static igMetaField **enumStorage[] = { &k_dataSize, &k_data };
    static int offsets[] = { 12, 8 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

