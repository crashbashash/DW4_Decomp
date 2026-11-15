igMetaObject *g_beSvPlatDataXbox_metaObject;
int g_beSvPlatDataXbox_connectMaxStorage;
igMetaField *g_beSvPlatDataXbox_imageSizeMetaField;
igMetaField *g_beSvPlatDataXbox_imageMetaField;
igMetaField *g_beSvPlatDataXbox_saveDataSizeMetaField;
igMetaField *g_beSvPlatDataXbox_dataOffSetMetaField;

void *FUN_003472b0(void) {
    igMetaObject *g = g_beSvPlatDataXbox_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003473f0();
    }
    return g_beSvPlatDataXbox_metaObject;
}

int beSvPlatDataXbox_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q0;
    S_ref *q1;

    igObject_InitHeader(u.b);
    q1 = (S_ref *)&u.b[12];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00538c80[0];
    q0 = (S_ref *)&u.b[36];
    *(int *)q0 = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00538c80[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    u.vt = (int)&DAT_00538d40[0];
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void FUN_003473f0(void)
{
    igMetaObject_RunStaticInit(beSvPlatDataXbox_Register);
}

static igMetaObjectCallback g_beSvPlatDataXbox_callbackList[] = { FUN_003476e0, 0 };

void *beSvPlatDataXbox_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvPlatDataXbox_metaObject,
        beSvPlatBaseData_Register,
        beSvPlatBaseData_GetPublishedMetaObject,
        beSvPlatDataXbox_GetMetaObject,
        "beSvPlatDataXbox",
        0x2c, /* instance size */
        beSvPlatDataXbox_GetVTable,
        beSvPlatDataXbox_InitFields,
        0, /* extra callback item */
        g_beSvPlatDataXbox_callbackList /* callback list */
    );
}

void beSvPlatDataXbox_GetMetaObject(void)
{
    FUN_003472b0();
}

static FieldFactory g_beSvPlatDataXbox_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igIntArrayMetaField_Create,
};
static const char *g_beSvPlatDataXbox_fieldTable[] = {
    "_imageSize",
    "_image",
    "_saveDataSize",
    "_dataOffSet",
};
static igMetaField **g_beSvPlatDataXbox_fieldHandles[] = {
    &g_beSvPlatDataXbox_imageSizeMetaField,
    &g_beSvPlatDataXbox_imageMetaField,
    &g_beSvPlatDataXbox_saveDataSizeMetaField,
    &g_beSvPlatDataXbox_dataOffSetMetaField,
};
static int g_beSvPlatDataXbox_fieldOffsets[] = {
    32,
    36,
    40,
    24,
};

void beSvPlatDataXbox_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    F_3474b0 *temp_s0;
    G_3474b0 *tg;
    void *temp_s1;
    T_3474b0 *temp_v0_2;

    temp_s1 = (void *)(((void * *)&g_beSvPlatDataXbox_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beSvPlatDataXbox_ctorTable, 4);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_connectMax"));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_3474b0 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igIntMetaField_SetDefault(temp_v0_2, 9);
    temp_v0_2->f1c = &g_beSvPlatDataXbox_connectMaxStorage;
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->refs = temp_v0_2->refs - 1;
    if (((unsigned long long) ((long long) temp_v0_2->refs << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (F_3474b0 *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    temp_s0->f56 = (int)FUN_00347600();
    temp_s0->b52 = 1;
    tg = (G_3474b0 *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3);
    tg->w52 = 2;
    igMetaObject_NameFields(temp_s1, g_beSvPlatDataXbox_fieldTable, g_beSvPlatDataXbox_fieldHandles, g_beSvPlatDataXbox_fieldOffsets, temp_s2);
}

