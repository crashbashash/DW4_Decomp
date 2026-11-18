igMetaObject *g_beSvPlatDataPC_metaObject;

void *beSvPlatDataPC_GetMetaObject(void) {
    bool ok;
    if (g_beSvPlatDataPC_metaObject == 0) goto make;
    ok = !!(g_beSvPlatDataPC_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beSvPlatDataPC_EnsureRegistered();
done:;
    return g_beSvPlatDataPC_metaObject;
}

int beSvPlatDataPC_GetVTable(void) {
    beSvPlatDataPC obj;
    int vtable;
    igObject **slotListSlot;

    igObject_InitHeader(&obj);
    slotListSlot = (igObject **)&obj._slotList;
    *slotListSlot = 0;
    obj._vtable = (int)&g_beSvPlatBaseData_vtable[0];
    obj._vtable = (int)&g_beSvPlatDataPC_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSvPlatBaseData_vtable[0];
    igObjectRef_Release(slotListSlot);
    return vtable;
}

beSvPlatBaseData *beSvPlatBaseData_Destroy(beSvPlatBaseData *self, short delete_storage) {
    if (self != 0) {
        self->_vtable = (int)&g_beSvPlatBaseData_vtable[0];
        igObjectRef_Release((igObject **)&self->_slotList);
        if (delete_storage > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

void beSvPlatDataPC_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataPC_Register);
}

CallbackArray *beSvPlatDataPC_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPlatDataPC_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataPC_GetMetaObjectFunction,
        "beSvPlatDataPC",
        0x18, /* instance size */
        beSvPlatDataPC_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvPlatDataPC_GetMetaObjectFunction(void)
{
    beSvPlatDataPC_GetMetaObject();
}

igMetaObject *beSvPlatBaseData_GetPublishedMetaObject(void) {
    return g_beSvPlatBaseData_metaObject;
}

