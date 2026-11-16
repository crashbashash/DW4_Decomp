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
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beWeaponInfo_vtable[0];
    igSmartPointer_beWeaponSeqDataList_Destruct((igSmartPointer<igObject> *)&obj._seqDataList, (short)(-1));
    igSmartPointer_igNamedObjectList_Destruct(&obj._boneNameList, -1);
    igSmartPointer_igNodeList_Destruct(&obj._nodeList, -1);
    beBaseInfo_Destroy((struct S_33ec80 *)&obj, (short)0);
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
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

void *beBaseInfo_Destroy(struct S_33ec80 *arg0, short arg1) {
    struct R_33ec80 *p;
    int *h;
    int *a1;
    int rc;

    if (arg0 != 0) {
        arg0->f0 = &g_beBaseInfo_vtable[0];
        if (&arg0->f24) {
            p = arg0->f24;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (&arg0->f20) {
            p = arg0->f20;
            if (p != 0) {
                p->rc = p->rc - 1;
                if ((p->rc & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
        }
        if (arg0 != 0) {
            arg0->f0 = &g_igInfo_vtable[0];
            if (arg0 != 0) {
                arg0->f0 = &g_igNamedObject_vtable[0];
                if (&arg0->f8) {
                    h = arg0->f8;
                    if (h != 0) {
                        a1 = h - 2;
                        rc = h[-1] - 1;
                        h[-1] = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*a1, a1);
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

igSmartPointer<igObject> *igSmartPointer_beWeaponSeqDataList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
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

void beWeaponInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWeaponInfo_Register);
}

static igMetaObjectCallback g_beWeaponInfo_callbackList[] = { igNodeList_EnsureRegistered, igNamedObjectList_EnsureRegistered, beWeaponSeqDataList_EnsureRegistered, 0 };

void *beWeaponInfo_Register(void) {
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
    void *meta;

    meta = (void *)g_beWeaponInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beWeaponInfo_ctorTable, 3);
    nodeList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)nodeList)->_metaObject = igNodeList_GetOrCreateMetaObject();
    ((igRefMetaField *)nodeList)->_construct = 1;
    boneNameList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)boneNameList)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)boneNameList)->_construct = 1;
    seqDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)seqDataList)->_metaObject = (int)beWeaponSeqDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)seqDataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beWeaponInfo_fieldTable, g_beWeaponInfo_fieldHandles, g_beWeaponInfo_fieldOffsets, base);
}

