igMetaObject *g_beNDMWTitle2Option_metaObject;
int g_beNDMWTitle2Option_nameExternalEnumStorage;
igMetaField *g_beNDMWTitle2Option_messengerMetaField;
igMetaField *g_beNDMWTitle2Option_selLangMetaField;
igMetaField *g_beNDMWTitle2Option_ctrlPosMetaField;
igMetaField *g_beNDMWTitle2Option_isOKMetaField;
igMetaField *g_beNDMWTitle2Option_comConfMetaField;
igMetaField *g_beNDMWTitle2Option_lightConfMetaField;
igMetaField *g_beNDMWTitle2Option_oldCountryMetaField;
igMetaField *g_beNDMWTitle2Option_dispComConfMetaField;
igMetaField *g_beNDMWTitle2Option_dispLightConfMetaField;
igMetaField *g_beNDMWTitle2Option_dispCountryConfMetaField;

void FUN_003b2250(int arg0) {
    FUN_003b2370();
    igMetaObject_CreateInstance(g_beNDMWTitle2Option_metaObject, arg0);
}

void *FUN_003b2290(void) {
    bool ok;
    if (g_beNDMWTitle2Option_metaObject == 0) goto make;
    ok = !!(g_beNDMWTitle2Option_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_003b2370();
done:;
    return g_beNDMWTitle2Option_metaObject;
}

int beNDMWTitle2Option_GetVTable(void) {
    union U_3b22e0 u;
    int temp_s0;
    int temp_v0;
    int *temp_a1;
    int *temp_v1;
    char *q0;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_igNamedObject_vtable[0];
    q0 = &u.b[8];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_0053dcf0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q0 != 0) {
        temp_v1 = *(int **)q0;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_003b2370(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2Option_Register);
}

static igMetaObjectCallback g_beNDMWTitle2Option_callbackList[] = { FUN_00357d10, 0 };

void *beNDMWTitle2Option_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWTitle2Option_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWTitle2Option_GetMetaObject,
        "beNDMWTitle2Option",
        0x38, /* instance size */
        beNDMWTitle2Option_GetVTable,
        beNDMWTitle2Option_InitFields,
        0, /* extra callback item */
        g_beNDMWTitle2Option_callbackList /* callback list */
    );
}

void beNDMWTitle2Option_GetMetaObject(void)
{
    FUN_003b2290();
}

static FieldFactory g_beNDMWTitle2Option_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWTitle2Option_fieldTable[] = {
    "_messenger",
    "_selLang",
    "_ctrlPos",
    "_isOK",
    "_comConf",
    "_lightConf",
    "_oldCountry",
    "_dispComConf",
    "_dispLightConf",
    "_dispCountryConf",
};
static igMetaField **g_beNDMWTitle2Option_fieldHandles[] = {
    &g_beNDMWTitle2Option_messengerMetaField,
    &g_beNDMWTitle2Option_selLangMetaField,
    &g_beNDMWTitle2Option_ctrlPosMetaField,
    &g_beNDMWTitle2Option_isOKMetaField,
    &g_beNDMWTitle2Option_comConfMetaField,
    &g_beNDMWTitle2Option_lightConfMetaField,
    &g_beNDMWTitle2Option_oldCountryMetaField,
    &g_beNDMWTitle2Option_dispComConfMetaField,
    &g_beNDMWTitle2Option_dispLightConfMetaField,
    &g_beNDMWTitle2Option_dispCountryConfMetaField,
};
static int g_beNDMWTitle2Option_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
};

void beNDMWTitle2Option_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;
    T_temp_v0_2 *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)(g_beNDMWTitle2Option_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWTitle2Option_ctorTable, 0xA);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_temp_v0_2 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "OPTION");
    temp_v0_2->f28 = (int)(&g_beNDMWTitle2Option_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if (((unsigned long long)(long long)temp_v0_2->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = FUN_00357910();
    *(char *)((char *)(temp_s0) + 60) = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWTitle2Option_fieldTable, g_beNDMWTitle2Option_fieldHandles, g_beNDMWTitle2Option_fieldOffsets, temp_s2);
}

