igMetaObject *g_beNDMWLoadIntf2MakeChr_metaObject;
int g_beNDMWLoadIntf2MakeChr_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2MakeChr_chaSelDegiMetaField;
igMetaField *g_beNDMWLoadIntf2MakeChr_degiNameMetaField;
igMetaField *g_beNDMWLoadIntf2MakeChr_nameCurMetaField;
igMetaField *g_beNDMWLoadIntf2MakeChr_mojiSelPointMetaField;

void beNDMWLoadIntf2MakeChr_Create(int arg0) {
    FUN_003c41e0();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2MakeChr_metaObject, arg0);
}

igMetaObject *beNDMWLoadIntf2MakeChr_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadIntf2MakeChr_metaObject != 0) {
        ready = (g_beNDMWLoadIntf2MakeChr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_003c41e0();
done:
    return g_beNDMWLoadIntf2MakeChr_metaObject;
}

int beNDMWLoadIntf2MakeChr_GetVTable(void) {
    union U_3c4150 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0053cf30[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return s0;
}

void FUN_003c41e0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2MakeChr_Register);
}

void *beNDMWLoadIntf2MakeChr_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2MakeChr_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2MakeChr_GetMetaObject,
        "beNDMWLoadIntf2MakeChr",
        0x3c, /* instance size */
        beNDMWLoadIntf2MakeChr_GetVTable,
        beNDMWLoadIntf2MakeChr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLoadIntf2MakeChr_GetMetaObject(void)
{
    beNDMWLoadIntf2MakeChr_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2MakeChr_ctorTable[] = {
    igIntMetaField_Create,
    igCharArrayMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2MakeChr_fieldTable[] = {
    "_chaSelDegi",
    "_degiName",
    "_nameCur",
    "_mojiSelPoint",
};
static igMetaField **g_beNDMWLoadIntf2MakeChr_fieldHandles[] = {
    &g_beNDMWLoadIntf2MakeChr_chaSelDegiMetaField,
    &g_beNDMWLoadIntf2MakeChr_degiNameMetaField,
    &g_beNDMWLoadIntf2MakeChr_nameCurMetaField,
    &g_beNDMWLoadIntf2MakeChr_mojiSelPointMetaField,
};
static int g_beNDMWLoadIntf2MakeChr_fieldOffsets[] = {
    48,
    16,
    52,
    56,
};

void beNDMWLoadIntf2MakeChr_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igMetaObject *temp_s1;
    igStringMetaField *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (igMetaObject *)(g_beNDMWLoadIntf2MakeChr_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2MakeChr_ctorTable, 4);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "MAKECHR");
    temp_v0_2->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2MakeChr_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)((int) ((int)temp_v0_2->_refCount - 1));
    if (((unsigned long long) ((long long)(int)temp_v0_2->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igCharArrayMetaField *temp_s0 = (igCharArrayMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1);
    temp_s0->_num = 0x20;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2MakeChr_fieldTable, g_beNDMWLoadIntf2MakeChr_fieldHandles, g_beNDMWLoadIntf2MakeChr_fieldOffsets, temp_s2);
}

