namespace Gap {
namespace Bec {

igMetaObject *beUnicodeObj::_Meta;
igMetaField *beUnicodeObj::k_buffer;

beUnicodeObj *beUnicodeObj::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beUnicodeObj *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beUnicodeObj::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beUnicodeObj::retrieveVTablePointer()
{
    beUnicodeObj temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beUnicodeObj::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beUnicodeObj::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beUnicodeObj",
        sizeof(beUnicodeObj),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beUnicodeObj::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igMemoryRefMetaField_Create };
    static const char *names[] = { "_buffer" };
    static igMetaField **enumStorage[] = { &k_buffer };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_memType = (int)Gap::Core::igUnsignedShortMetaField::getMetaField();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

