namespace Gap {
namespace Attrs {

igMetaObject *igTextureMatrixAttr::_Meta;
igMetaField *igTextureMatrixAttr::k_m;
igMetaField *igTextureMatrixAttr::k_unitID;
igMetaField *igTextureMatrixAttr::k_outputElementCount;
igMetaField *igTextureMatrixAttr::k_isProjective;

igTextureMatrixAttr *igTextureMatrixAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTextureMatrixAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTextureMatrixAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTextureMatrixAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTextureMatrixAttr::retrieveVTablePointer()
{
    igTextureMatrixAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTextureMatrixAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTextureMatrixAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTextureMatrixAttr",
        sizeof(igTextureMatrixAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igTextureMatrixAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, igIntMetaField_Create, igShortMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_m", "_unitID", "_outputElementCount", "_isProjective" };
    static igMetaField **enumStorage[] = { &k_m, &k_unitID, &k_outputElementCount, &k_isProjective };
    static int offsets[] = { 12, 76, 80, 82 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                          igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igTextureMatrixAttr::synchronizeCachedUnitID;
    }
    {
        igShortMetaField *metaField = (igShortMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

igSmartPointer<igObject> *igSmartPointer_igTextureList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igInfo *igInfo_Destroy(igInfo *self, short deleteFlag) {
    char *p;
    int *h;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&g_igInfo_vtable[0];
        if (self != 0) {
            self->_vtable = (int)&g_igNamedObject_vtable[0];
            if (&self->_name) {
                p = (char *)self->_name;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
                    }
                }
            }
        }
        if (deleteFlag > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

igNamedObject *igNamedObject_Destroy(igNamedObject *self, short deleteFlag) {
    char *p;
    int *h;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&g_igNamedObject_vtable[0];
        if (&self->_name) {
            p = (char *)self->_name;
            if (p != 0) {
                h = (int *)((char *)(p) - 8);
                rc = *(int *)((char *)(p) - 4) - 1;
                *(int *)((char *)(p) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
                }
            }
        }
        if (deleteFlag > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

int FUN_00131c50(void) {
    return (int)g_igInfo_metaObject;
}

