igMetaObject *g_beModelCtrlInfoRamData_metaObject;
int g_beModelCtrlInfoRamData_nameStorage;
igMetaField *g_beModelCtrlInfoRamData_nodeMetaField;
igMetaField *g_beModelCtrlInfoRamData_workMetaField;

void *FUN_00352ee0(void) {
    igMetaObject *g = g_beModelCtrlInfoRamData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00353040();
    }
    return g_beModelCtrlInfoRamData_metaObject;
}

int beModelCtrlInfoRamData_GetVTable(void) {
    struct Obj_352f30 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00537bb0[0];
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00537bb0[0];
    FUN_00352fc0((ObjectRefWord *)&obj.w5, -1);
    FUN_0034c1b0((void **)&obj.w4, (short)(-1));
    FUN_00344030((struct W_344030 *)&obj, (short)0);
    return t;
}

ObjectRefWord *FUN_00352fc0(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) __dl__FPv(self);
    }
    return self;
}

void FUN_00353040(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRamData_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoRamData_callbackList[] = { FUN_0034fe80, FUN_00350fb0, 0 };

void *beModelCtrlInfoRamData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoRamData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoRamData_GetMetaObject,
        "beModelCtrlInfoRamData",
        0x18, /* instance size */
        beModelCtrlInfoRamData_GetVTable,
        beModelCtrlInfoRamData_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoRamData_callbackList /* callback list */
    );
}

void beModelCtrlInfoRamData_GetMetaObject(void)
{
    FUN_00352ee0();
}

static FieldFactory g_beModelCtrlInfoRamData_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlInfoRamData_fieldTable[] = {
    "_node",
    "_work",
};
static igMetaField **g_beModelCtrlInfoRamData_fieldHandles[] = {
    &g_beModelCtrlInfoRamData_nodeMetaField,
    &g_beModelCtrlInfoRamData_workMetaField,
};
static int g_beModelCtrlInfoRamData_fieldOffsets[] = {
    16,
    20,
};

void beModelCtrlInfoRamData_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s1;
    S_ref *temp_v0_2;

    temp_s1 = (void *)(((void * *)&g_beModelCtrlInfoRamData_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beModelCtrlInfoRamData_ctorTable, 2);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (S_ref *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "ONE");
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&g_beModelCtrlInfoRamData_nameStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->f4 = temp_v0_2->f4 - 1;
    if (((unsigned long long) ((long long) temp_v0_2->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = (int)FUN_0034fd40();
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    *(int *)((char *)(temp_s0_2) + 56) = (int)FUN_00350060();
    igMetaObject_NameFields(temp_s1, g_beModelCtrlInfoRamData_fieldTable, g_beModelCtrlInfoRamData_fieldHandles, g_beModelCtrlInfoRamData_fieldOffsets, temp_s2);
}

