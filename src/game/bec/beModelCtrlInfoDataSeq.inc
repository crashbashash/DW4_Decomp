igMetaObject *g_beModelCtrlInfoDataSeq_metaObject;
int g_beModelCtrlInfoDataSeq_nameStorage;
igMetaField *g_beModelCtrlInfoDataSeq_dataListMetaField;

void *beModelCtrlInfoDataSeq_GetMetaObject(void) {
    bool ok;
    if (g_beModelCtrlInfoDataSeq_metaObject == 0) goto make;
    ok = !!(g_beModelCtrlInfoDataSeq_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beModelCtrlInfoDataSeq_EnsureRegistered();
done:;
    return g_beModelCtrlInfoDataSeq_metaObject;
}

int beModelCtrlInfoDataSeq_GetVTable(void) {
    union U_353600 u;
    int t;
    char *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    int *q8;
    int *q16;

    igObject_InitHeader(u.b);
    q8 = (int *)&u.b[8];
    *q8 = 0;
    u.vt = (int)&g_beModelCtrlInfoDataSeq_vtable[0];
    q16 = (int *)&u.b[16];
    *q16 = 0;
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beModelCtrlInfoDataSeq_vtable[0];
    if (q16 != 0) {
        o = (char *)*q16;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q8 != 0) {
        temp_v1 = (int *)*q8;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return t;
}

void beModelCtrlInfoDataSeq_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoDataSeq_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoDataSeq_callbackList[] = { igNamedObjectList_EnsureRegistered, 0 };

void *beModelCtrlInfoDataSeq_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoDataSeq_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoDataSeq_GetMetaObjectFunction,
        "beModelCtrlInfoDataSeq",
        0x14, /* instance size */
        beModelCtrlInfoDataSeq_GetVTable,
        beModelCtrlInfoDataSeq_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoDataSeq_callbackList /* callback list */
    );
}

void beModelCtrlInfoDataSeq_GetMetaObjectFunction(void)
{
    beModelCtrlInfoDataSeq_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoDataSeq_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlInfoDataSeq_fieldTable[] = {
    "_dataList",
};
static igMetaField **g_beModelCtrlInfoDataSeq_fieldHandles[] = {
    &g_beModelCtrlInfoDataSeq_dataListMetaField,
};
static int g_beModelCtrlInfoDataSeq_fieldOffsets[] = {
    16,
};

void beModelCtrlInfoDataSeq_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;
    S_ref *temp_v0_2;

    temp_s1 = (void *)(((void * *)&g_beModelCtrlInfoDataSeq_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beModelCtrlInfoDataSeq_ctorTable, 1);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (S_ref *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "SEQ");
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&g_beModelCtrlInfoDataSeq_nameStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->f4 = temp_v0_2->f4 - 1;
    if (((unsigned long long) ((long long) temp_v0_2->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = igNamedObjectList_GetOrCreateMetaObject();
    *(char *)((char *)(temp_s0) + 52) = 1;
    igMetaObject_NameFields(temp_s1, g_beModelCtrlInfoDataSeq_fieldTable, g_beModelCtrlInfoDataSeq_fieldHandles, g_beModelCtrlInfoDataSeq_fieldOffsets, temp_s2);
}

