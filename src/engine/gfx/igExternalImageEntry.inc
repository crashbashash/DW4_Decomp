namespace Gap {
namespace Gfx {

igMetaObject *igExternalImageEntry::_Meta;

igMetaObject *igExternalImageEntry::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igExternalImageEntry::retrieveVTablePointer()
{
    igExternalImageEntry temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

igDirEntry *igDirEntry_Destroy(igDirEntry *self, short deleteFlag) {
    void *p;
    int *h;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&g_igDirEntry_vtable[0];
        if (self != 0) {
            self->_vtable = (int)&g_igNamedObject_vtable[0];
            if (&self->_name) {
                p = (void *)self->_name;
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

namespace Gap {
namespace Gfx {

void igExternalImageEntry::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igExternalImageEntry::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igExternalDirEntry::arkRegisterInternal,
        Gap::Core::igExternalDirEntry::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igExternalImageEntry",
        sizeof(igExternalImageEntry),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

igMetaObject *igDisableExt_GetOrCreateMetaObject(void) {
    if (g_igDisableExt_metaObject == 0) {
        g_igDisableExt_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDisableExt_metaObject;
}

