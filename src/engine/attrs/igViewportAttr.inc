namespace Gap {
namespace Attrs {

igMetaObject *igViewportAttr::_Meta;
igMetaField *igViewportAttr::k_x;
igMetaField *igViewportAttr::k_y;
igMetaField *igViewportAttr::k_w;
igMetaField *igViewportAttr::k_h;
igMetaField *igViewportAttr::k_scissorExt;
igMetaField *igViewportAttr::k_nearZ;
igMetaField *igViewportAttr::k_farZ;

igMetaObject *igViewportAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igViewportAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewportAttr::retrieveVTablePointer()
{
    igViewportAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewportAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewportAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igScissorExt_EnsureRegistered, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewportAttr",
        sizeof(igViewportAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igViewportAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_x", "_y", "_w", "_h", "_scissorExt", "_nearZ", "_farZ" };
    static igMetaField **enumStorage[] = { &k_x, &k_y, &k_w, &k_h, &k_scissorExt, &k_nearZ, &k_farZ };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(639);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(447);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igScissorExt_GetOrCreateMetaObject();
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
        metaField->_isAlikeShallowMethod = 3;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(1.0f);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

igStringRef *igStringRef_Destruct(igStringRef *self, short deleteFlag) {
    if (self) {
        char *value = self->p;
        if (value) {
            StringTokenHeader *header = (StringTokenHeader *)value - 1;
            if (--header->refCount == 0) StringChunk_ReleaseHeader((StringChunk *)header->owner, header);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

