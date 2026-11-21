igMetaObject *g_igExternalImageEntry_metaObject;

igMetaObject *igExternalImageEntry_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igExternalImageEntry_metaObject != 0) {
        ready = (g_igExternalImageEntry_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igExternalImageEntry_EnsureRegistered();
done:
    return g_igExternalImageEntry_metaObject;
}

int igExternalImageEntry_GetVTable(void) {
    struct W_14f470 o;
    int r;
    igObject_InitHeader((igObject *)&o);
    o.f[1] = 0;
    o.f[6] = 0;
    o.f[7] = 0;
    o.f[9] = 0;
    o.vt = g_igExternalImageEntry_vtable;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = g_igExternalImageEntry_vtable;
    FUN_0014f580((W_14f580 *)&o, 0);
    return r;
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

W_14f580 *FUN_0014f580(W_14f580 *t, short flag)
{
    if (t != 0) {
        t->vt = g_igExternalDirEntry_vtable;
        t->s40.~Str();
        t->s32.~Str();
        t->s28.~Str();
        if (t != 0) {
            t->vt = g_igDirEntry_vtable;
            if (t != 0) {
                t->vt = g_igNamedObject_vtable;
                t->s8.~Str();
            }
        }
        if (flag > 0) {
            Memory_FreeBufferAliasC(t);
        }
    }
    return t;
}

void igExternalImageEntry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igExternalImageEntry_Register);
}

CallbackArray *igExternalImageEntry_Register(void) {
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igExternalImageEntry_metaObject,
        Gap::Core::igExternalDirEntry::arkRegisterInternal,
        igExternalDirEntry_GetPublishedMetaObject,
        thunk_igExternalImageEntry_GetMetaObject_0014f750,
        "igExternalImageEntry",
        0x2C, /* instance size */
        igExternalImageEntry_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igExternalImageEntry_GetMetaObjectFunction(void) {
    igExternalImageEntry_GetMetaObject();
}

int FUN_0014f760(void) {
    return (int)Gap::Core::igExternalDirEntry::getClassMeta();
}

igMetaObject *igDisableExt_GetOrCreateMetaObject(void) {
    if (g_igDisableExt_metaObject == 0) {
        g_igDisableExt_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDisableExt_metaObject;
}

