igMetaObject *g_beWeaponInfoRam_metaObject;

void *beWeaponInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beWeaponInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWeaponInfoRam_EnsureRegistered();
    }
    return g_beWeaponInfoRam_metaObject;
}

int beWeaponInfoRam_GetVTable(void) {
    beWeaponInfoRam obj;
    int vtable;
    igObject **dataListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    obj._vtable = (int)&g_beWeaponInfoRam_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beBaseInfoRam_vtable[0];
    igObjectRef_Release(dataListSlot);
    return vtable;
}

void *beBaseInfoRam_Destroy(beBaseInfoRam *self, long long delete_storage) {
    if (self != 0) {
        self->_vtable = (int)(&g_beBaseInfoRam_vtable[0]);
        igObjectRef_Release((igObject **)&self->_dataList);
        if ((short)delete_storage > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

igSmartPointer<igObject> *beWeaponInfoRam_igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beWeaponInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWeaponInfoRam_Register);
}

void *beWeaponInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWeaponInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beWeaponInfoRam_GetMetaObjectFunction,
        "beWeaponInfoRam",
        0x2c, /* instance size */
        beWeaponInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beWeaponInfoRam_GetMetaObjectFunction(void)
{
    beWeaponInfoRam_GetMetaObject();
}

igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void) {
    return g_beBaseInfoRam_metaObject;
}

