igMetaObject *g_beWeapon_metaObject;
igMetaField *g_beWeapon_attachDataListMetaField;

beWeapon *beWeapon_CreateInstance(int allocator) {
    beWeapon_EnsureRegistered();
    return (beWeapon *)igMetaObject_CreateInstance(g_beWeapon_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beWeapon_GetOrCreateMetaObject(void) {
    if (g_beWeapon_metaObject == 0) {
        g_beWeapon_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beWeapon_vtable[0];
    beBaseInfoManager_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)(&obj._attachDataList), (short)(-1));
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, (short)0);
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

beBaseInfoManager *beBaseInfoManager_Destroy(beBaseInfoManager *self, short delete_storage) {
    if (self != 0) {
        self->_vtable = (int)&g_beBaseInfoManager_vtable[0];
        igObjectRef_Release((igObject **)&self->_infoList);
        /* ~igInfoManager and ~igNamedObject are inlined here with their own null checks on `this` */
        if (self != 0) {
            self->_vtable = (int)&g_igInfoManager_vtable[0];
            if (self != 0) {
                self->_vtable = (int)&g_igNamedObject_vtable[0];
                igStringRef_Release((char **)&self->_name);
            }
        }
        if (delete_storage > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

igSmartPointer<igObject> *beBaseInfoManager_igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

CallbackArray *beWeapon_Register(void) {
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
    igMetaObject *meta;

    meta = g_beWeapon_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beWeapon_ctorTable, 1);
    attachDataList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)attachDataList)->_metaObject = (int)beWeaponAttachDataList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beWeapon_fieldTable, g_beWeapon_fieldHandles, g_beWeapon_fieldOffsets, base);
}

