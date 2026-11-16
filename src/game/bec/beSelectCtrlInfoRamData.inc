igMetaObject *g_beSelectCtrlInfoRamData_metaObject;
int g_beSelectCtrlInfoRamData_nameStorage;
igMetaField *g_beSelectCtrlInfoRamData_isTateSelectMetaField;
igMetaField *g_beSelectCtrlInfoRamData_maxSelectMetaField;
igMetaField *g_beSelectCtrlInfoRamData_selectNoMetaField;
igMetaField *g_beSelectCtrlInfoRamData_workMetaField;

void *beSelectCtrlInfoRamData_GetMetaObject(void) {
    igMetaObject *g = g_beSelectCtrlInfoRamData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSelectCtrlInfoRamData_EnsureRegistered();
    }
    return g_beSelectCtrlInfoRamData_metaObject;
}

int beSelectCtrlInfoRamData_GetVTable(void) {
    Obj_345330 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &g_beSelectCtrlInfoRamData_vtable[0];
    obj.r6 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beSelectCtrlInfoRamData_vtable[0];
    obj.rel6();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel1();
    return r;
}

igSmartPointer<igObject> *FUN_00345410(igSmartPointer<igObject> *self, int delete_storage) {
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

void beSelectCtrlInfoRamData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSelectCtrlInfoRamData_Register);
}

static igMetaObjectCallback g_beSelectCtrlInfoRamData_callbackList[] = { beSelectCtrlInfoWork_EnsureRegistered, 0 };

void *beSelectCtrlInfoRamData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSelectCtrlInfoRamData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSelectCtrlInfoRamData_GetMetaObjectFunction,
        "beSelectCtrlInfoRamData",
        0x20, /* instance size */
        beSelectCtrlInfoRamData_GetVTable,
        beSelectCtrlInfoRamData_InitFields,
        0, /* extra callback item */
        g_beSelectCtrlInfoRamData_callbackList /* callback list */
    );
}

void beSelectCtrlInfoRamData_GetMetaObjectFunction(void)
{
    beSelectCtrlInfoRamData_GetMetaObject();
}

static FieldFactory g_beSelectCtrlInfoRamData_ctorTable[] = {
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSelectCtrlInfoRamData_fieldTable[] = {
    "_isTateSelect",
    "_maxSelect",
    "_selectNo",
    "_work",
};
static igMetaField **g_beSelectCtrlInfoRamData_fieldHandles[] = {
    &g_beSelectCtrlInfoRamData_isTateSelectMetaField,
    &g_beSelectCtrlInfoRamData_maxSelectMetaField,
    &g_beSelectCtrlInfoRamData_selectNoMetaField,
    &g_beSelectCtrlInfoRamData_workMetaField,
};
static int g_beSelectCtrlInfoRamData_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beSelectCtrlInfoRamData_InitFields(void) {
    int base;
    int index;
    void **found;
    void *work;
    void *meta;
    igStringMetaField *clone;

    meta = (void *)g_beSelectCtrlInfoRamData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSelectCtrlInfoRamData_ctorTable, 4);
    found = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    index = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, found);
    clone = (igStringMetaField *)(((DW4VC_84_1 *)(found))->vX((int)(1)));
    igStringMetaField_SetDefaultText(clone, "ONE");
    clone->_externalEnumStorage = (int)(&g_beSelectCtrlInfoRamData_nameStorage);
    igMetaObject_FinalizeAndReplaceField(meta, index, clone);
    clone->_refCount = (int)clone->_refCount - 1;
    if (((unsigned long long) ((long long)(int)clone->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(clone);
    }
    work = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)work)->_metaObject = (int)beSelectCtrlInfoWork_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beSelectCtrlInfoRamData_fieldTable, g_beSelectCtrlInfoRamData_fieldHandles, g_beSelectCtrlInfoRamData_fieldOffsets, base);
}

