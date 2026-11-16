igMetaObject *g_beWeapon_metaObject;
igMetaField *g_beWeapon_attachDataListMetaField;

void beWeapon_CreateInstance(int allocator) {
    beWeapon_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x587A68, allocator);
}

igMetaObject *beWeapon_GetOrCreateMetaObject(void) {
    if (g_beWeapon_metaObject == 0) {
        g_beWeapon_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beWeapon_metaObject;
}

void *beWeapon_GetMetaObject(void) {
    igMetaObject *g = g_beWeapon_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWeapon_EnsureRegistered();
    }
    return g_beWeapon_metaObject;
}

int beWeapon_GetVTable(void) {
    beWeapon obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    obj._vtable = (int)&g_beWeapon_vtable[0];
    obj._attachDataList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beWeapon_vtable[0];
    beWeapon_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)(&obj._attachDataList), (short)(-1));
    beBaseInfoManager_Destroy((O_33f5e0 *)(&obj._vtable), (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beBaseInfoList_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
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

O_33f5e0 *beBaseInfoManager_Destroy(O_33f5e0 *arg0, short arg1) {
    int *temp_a1;
    int temp_v0;
    R_33f5e0 *temp_a0;
    int *temp_v1;

    if (arg0 != 0) {
        arg0->vt = &g_beBaseInfoManager_vtable[0];
        if (&arg0->ref != 0) {
            temp_a0 = arg0->ref;
            if (temp_a0 != 0) {
                temp_a0->refs = temp_a0->refs - 1;
                if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
        }
        if (arg0 != 0) {
            arg0->vt = &g_igInfoManager_vtable[0];
            if (arg0 != 0) {
                arg0->vt = &g_igNamedObject_vtable[0];
                if (&arg0->str != 0) {
                    temp_v1 = arg0->str;
                    if (temp_v1 != 0) {
                        temp_a1 = temp_v1 - 2;
                        temp_v0 = temp_v1[-1] - 1;
                        temp_v1[-1] = temp_v0;
                        if (temp_v0 == 0) {
                            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
                        }
                    }
                }
            }
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *beWeapon_igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void beWeapon_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWeapon_Register);
}

static igMetaObjectCallback g_beWeapon_callbackList[] = { beWeaponAttachDataList_EnsureRegistered, 0 };

void *beWeapon_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWeapon_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beWeapon_GetMetaObjectFunction,
        "beWeapon",
        0x24, /* instance size */
        beWeapon_GetVTable,
        beWeapon_InitFields,
        0, /* extra callback item */
        g_beWeapon_callbackList /* callback list */
    );
}

void beWeapon_GetMetaObjectFunction(void)
{
    beWeapon_GetMetaObject();
}

igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void) {
    return g_beBaseInfoManager_metaObject;
}

static FieldFactory g_beWeapon_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beWeapon_fieldTable[] = {
    "_attachDataList",
};
static igMetaField **g_beWeapon_fieldHandles[] = {
    &g_beWeapon_attachDataListMetaField,
};
static int g_beWeapon_fieldOffsets[] = {
    32,
};

void beWeapon_InitFields(void) {
    int base;
    void *attachDataList;
    void *meta;

    meta = (void *)g_beWeapon_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beWeapon_ctorTable, 1);
    attachDataList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)attachDataList)->_metaObject = (int)beWeaponAttachDataList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beWeapon_fieldTable, g_beWeapon_fieldHandles, g_beWeapon_fieldOffsets, base);
}

