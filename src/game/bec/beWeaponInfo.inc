igMetaObject *g_beWeaponInfo_metaObject;
igMetaField *g_beWeaponInfo_nodeListMetaField;
igMetaField *g_beWeaponInfo_boneNameListMetaField;
igMetaField *g_beWeaponInfo_seqDataListMetaField;

void *beWeaponInfo_GetMetaObject(void) {
    igMetaObject *g = g_beWeaponInfo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWeaponInfo_EnsureRegistered();
    }
    return g_beWeaponInfo_metaObject;
}

int beWeaponInfo_GetVTable(void) {
    beWeaponInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beWeaponInfo_vtable[0];
    obj._nodeList = 0;
    obj._boneNameList = 0;
    obj._seqDataList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beWeaponInfo_vtable[0];
    igSmartPointer_beWeaponSeqDataList_Destruct((igSmartPointer<igObject> *)&obj._seqDataList, (short)(-1));
    igSmartPointer_igNamedObjectList_Destruct(&obj._boneNameList, -1);
    igSmartPointer_igNodeList_Destruct(&obj._nodeList, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beBaseInfoRamList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void *beBaseInfo_Destroy(beBaseInfo *self, short delete_storage) {
    if (self != 0) {
        self->_vtable = (int)&g_beBaseInfo_vtable[0];
        igObjectRef_Release((igObject **)&self->_ramList);
        igObjectRef_Release((igObject **)&self->_dataList);
        /* ~igInfo and ~igNamedObject are inlined here with their own null checks on `this` */
        if (self != 0) {
            self->_vtable = (int)&g_igInfo_vtable[0];
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

igSmartPointer<igObject> *igSmartPointer_beWeaponSeqDataList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

void beWeaponInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWeaponInfo_Register);
}

static igMetaObjectCallback g_beWeaponInfo_callbackList[] = { igNodeList_EnsureRegistered, igNamedObjectList_EnsureRegistered, beWeaponSeqDataList_EnsureRegistered, 0 };

CallbackArray *beWeaponInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWeaponInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beWeaponInfo_GetMetaObjectFunction,
        "beWeaponInfo",
        0x28, /* instance size */
        beWeaponInfo_GetVTable,
        beWeaponInfo_InitFields,
        0, /* extra callback item */
        g_beWeaponInfo_callbackList /* callback list */
    );
}

void beWeaponInfo_GetMetaObjectFunction(void)
{
    beWeaponInfo_GetMetaObject();
}

igMetaObject *beBaseInfo_GetPublishedMetaObject(void) {
    return g_beBaseInfo_metaObject;
}

static FieldFactory g_beWeaponInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beWeaponInfo_fieldTable[] = {
    "_nodeList",
    "_boneNameList",
    "_seqDataList",
};
static igMetaField **g_beWeaponInfo_fieldHandles[] = {
    &g_beWeaponInfo_nodeListMetaField,
    &g_beWeaponInfo_boneNameListMetaField,
    &g_beWeaponInfo_seqDataListMetaField,
};
static int g_beWeaponInfo_fieldOffsets[] = {
    28,
    32,
    36,
};

void beWeaponInfo_InitFields(void) {
    int base;
    void *nodeList;
    void *boneNameList;
    void *seqDataList;
    igMetaObject *meta;

    meta = g_beWeaponInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beWeaponInfo_ctorTable, 3);
    nodeList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)nodeList)->_metaObject = (int)igNodeList_GetOrCreateMetaObject();
    ((igRefMetaField *)nodeList)->_construct = 1;
    boneNameList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)boneNameList)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)boneNameList)->_construct = 1;
    seqDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)seqDataList)->_metaObject = (int)beWeaponSeqDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)seqDataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beWeaponInfo_fieldTable, g_beWeaponInfo_fieldHandles, g_beWeaponInfo_fieldOffsets, base);
}

