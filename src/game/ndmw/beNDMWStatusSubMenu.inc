igMetaObject *g_beNDMWStatusSubMenu_metaObject;
igMetaField *g_beNDMWStatusSubMenu_selectDeviceMetaField;
igMetaField *g_beNDMWStatusSubMenu_deviceFolderListMetaField;
igMetaField *g_beNDMWStatusSubMenu_receiptMetaField;
igMetaField *g_beNDMWStatusSubMenu_playerNoListMetaField;
igMetaField *g_beNDMWStatusSubMenu_playerDeviceCntMetaField;

void beNDMWStatusSubMenu_Create(int allocator) {
    beNDMWStatusSubMenu_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusSubMenu_metaObject, allocator);
}

void *beNDMWStatusSubMenu_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusSubMenu_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusSubMenu_EnsureRegistered();
    }
    return g_beNDMWStatusSubMenu_metaObject;
}

int beNDMWStatusSubMenu_GetVTable(void) {
    union U_3b8fe0 u;
    int temp_s2;

    igObject_InitHeader(u.b);
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    u.w[17] = 0;
    u.w[18] = 0;
    u.w[19] = 0;
    u.w[0] = (int)(&g_beNDMWStatusSubMenu_vtable[0]);
    u.w[22] = 0;
    u.w[24] = 0;
    u.w[25] = 0;
    temp_s2 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beNDMWStatusSubMenu_vtable[0]);
    igSmartPointer_igIntList_Destruct(&u.w[25], -1);
    igSmartPointer_igIntList_Destruct(&u.w[24], -1);
    beNDMWStatusSubMenu_igSmartPointer_beNDMWWindow_Destruct((igSmartPointer<igObject> *)(&u.w[22]), -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)u.b, (long long)0);
    return temp_s2;
}

igSmartPointer<igObject> *beNDMWStatusSubMenu_igSmartPointer_beNDMWWindow_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWStatusSubMenu_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSubMenu_Register);
}

static igMetaObjectCallback g_beNDMWStatusSubMenu_callbackList[] = { beNDMWWindowCtrl_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWStatusSubMenu_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusSubMenu_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusSubMenu_GetMetaObjectFunction,
        "beNDMWStatusSubMenu",
        0x68, /* instance size */
        beNDMWStatusSubMenu_GetVTable,
        beNDMWStatusSubMenu_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusSubMenu_callbackList /* callback list */
    );
}

void beNDMWStatusSubMenu_GetMetaObjectFunction(void)
{
    beNDMWStatusSubMenu_GetMetaObject();
}

static FieldFactory g_beNDMWStatusSubMenu_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusSubMenu_fieldTable[] = {
    "_selectDevice",
    "_deviceFolderList",
    "_receipt",
    "_playerNoList",
    "_playerDeviceCnt",
};
static igMetaField **g_beNDMWStatusSubMenu_fieldHandles[] = {
    &g_beNDMWStatusSubMenu_selectDeviceMetaField,
    &g_beNDMWStatusSubMenu_deviceFolderListMetaField,
    &g_beNDMWStatusSubMenu_receiptMetaField,
    &g_beNDMWStatusSubMenu_playerNoListMetaField,
    &g_beNDMWStatusSubMenu_playerDeviceCntMetaField,
};
static int g_beNDMWStatusSubMenu_fieldOffsets[] = {
    84,
    88,
    92,
    96,
    100,
};

void beNDMWStatusSubMenu_InitFields(void) {
    int base;
    void *deviceFolderList;
    void *playerNoList;
    void *playerDeviceCnt;
    igMetaObject *meta;

    meta = g_beNDMWStatusSubMenu_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusSubMenu_ctorTable, 5);
    deviceFolderList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)deviceFolderList)->_metaObject = (int)beNDMWWindowCtrl_GetOrCreateMetaObject();
    playerNoList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)playerNoList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerNoList)->_construct = 1;
    playerDeviceCnt = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)playerDeviceCnt)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerDeviceCnt)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWStatusSubMenu_fieldTable, g_beNDMWStatusSubMenu_fieldHandles, g_beNDMWStatusSubMenu_fieldOffsets, base);
}

