namespace Gap {
namespace Bec {

igMetaObject *beFileChkObj::_Meta;
igMetaField *beFileChkObj::k_fd;

beFileChkObj *beFileChkObj::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beFileChkObj *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beFileChkObj::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beFileChkObj::retrieveVTablePointer()
{
    beFileChkObj temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beFileChkObj::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beFileChkObj::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igFile::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beFileChkObj",
        sizeof(beFileChkObj),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beFileChkObj::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_fd" };
    static igMetaField **enumStorage[] = { &k_fd };
    static int offsets[] = { 8 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igFile::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

