igMetaObject *g_beNDMWLoadIntf2DegiStateCtrl_metaObject;
int g_beNDMWLoadIntf2DegiStateCtrl_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2DegiStateCtrl_statDataListMetaField;

void beNDMWLoadIntf2DegiStateCtrl_Create(int allocator) {
    beNDMWLoadIntf2DegiStateCtrl_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2DegiStateCtrl_metaObject, allocator);
}

igMetaObject *beNDMWLoadIntf2DegiStateCtrl_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadIntf2DegiStateCtrl_metaObject == 0) {
        g_beNDMWLoadIntf2DegiStateCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadIntf2DegiStateCtrl_metaObject;
}

igMetaObject *beNDMWLoadIntf2DegiStateCtrl_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2DegiStateCtrl_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWLoadIntf2DegiStateCtrl_EnsureRegistered();
done:
    return g_beNDMWLoadIntf2DegiStateCtrl_metaObject;
}

int beNDMWLoadIntf2DegiStateCtrl_GetVTable(void) {
    union U_3c39e0 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p38;
    char *p40;

    igObject_InitHeader(u.b);
    p38 = &u.b[8];
    *(int *)p38 = 0;
    u.vt = (int)&g_beNDMWLoadIntf2DegiStateCtrl_vtable[0];
    p40 = &u.b[16];
    *(int *)p40 = 0;
    r = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWLoadIntf2DegiStateCtrl_vtable[0];
    if (p40 != 0) {
        v1 = *(int **)p40;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (p38 != 0) {
        v1 = *(int **)p38;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return r;
}

void beNDMWLoadIntf2DegiStateCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DegiStateCtrl_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2DegiStateCtrl_callbackList[] = { beNDMWLoadIntf2DegiStateList_EnsureRegistered, 0 };

void *beNDMWLoadIntf2DegiStateCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2DegiStateCtrl_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2DegiStateCtrl_GetMetaObject,
        "beNDMWLoadIntf2DegiStateCtrl",
        0x14, /* instance size */
        beNDMWLoadIntf2DegiStateCtrl_GetVTable,
        beNDMWLoadIntf2DegiStateCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DegiStateCtrl_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2DegiStateCtrl_GetMetaObject(void)
{
    beNDMWLoadIntf2DegiStateCtrl_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2DegiStateCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWLoadIntf2DegiStateCtrl_fieldTable[] = {
    "_statDataList",
};
static igMetaField **g_beNDMWLoadIntf2DegiStateCtrl_fieldHandles[] = {
    &g_beNDMWLoadIntf2DegiStateCtrl_statDataListMetaField,
};
static int g_beNDMWLoadIntf2DegiStateCtrl_fieldOffsets[] = {
    16,
};

void beNDMWLoadIntf2DegiStateCtrl_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    igObjectRefMetaField *statDataList;
    igMetaObject *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (igMetaObject *)(g_beNDMWLoadIntf2DegiStateCtrl_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2DegiStateCtrl_ctorTable, 1);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex(meta->_metaFields, inheritedName);
    nameField = (igStringMetaField *)(((DW4VC_84_1 *)(inheritedName))->vX((int)(1)));
    igStringMetaField_SetDefaultText(nameField, "DEGISTATECTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2DegiStateCtrl_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    statDataList = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base));
    statDataList->_metaObject = (int)beNDMWLoadIntf2DegiStateList_GetOrCreateMetaObject();
    statDataList->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2DegiStateCtrl_fieldTable, g_beNDMWLoadIntf2DegiStateCtrl_fieldHandles, g_beNDMWLoadIntf2DegiStateCtrl_fieldOffsets, base);
}

