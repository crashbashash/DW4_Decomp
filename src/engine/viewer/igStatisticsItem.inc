igMetaObject *g_igStatisticsItem_metaObject;
igMetaField *g_igStatisticsItem_valueMetaField;
igMetaField *g_igStatisticsItem_maximumValueMetaField;
igMetaField *g_igStatisticsItem_useMultiplierMetaField;
igMetaField *g_igStatisticsItem_textMetaField;
igMetaField *g_igStatisticsItem_numberFormatMetaField;
igMetaField *g_igStatisticsItem_visibleMetaField;
igMetaField *g_igStatisticsItem_displayComponentMetaField;
igMetaField *g_igStatisticsItem_aspectMetaField;
igMetaField *g_igStatisticsItem_textElementMetaField;
igMetaField *g_igStatisticsItem_managerMetaField;
igMetaField *g_igStatisticsItem_statIdMetaField;
igMetaField *g_igStatisticsItem_otherIdMetaField;

igMetaObject *FUN_00458c50(void) {
    if (g_igStatisticsItem_metaObject == 0) {
        g_igStatisticsItem_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igStatisticsItem_metaObject;
}

void *igStatisticsItem_GetMetaObject(void) {
    unsigned char b;
    if (((void *)g_igStatisticsItem_metaObject) != 0) {
        b = (*(int *)((char *)(((void *)g_igStatisticsItem_metaObject)) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00458ec0();
done:
    return ((void *)g_igStatisticsItem_metaObject);
}

int igStatisticsItem_GetVTable(void) {
    struct Obj_458cf0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542620[0];
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
    obj.vt = &DAT_00542620[0];
    FUN_00458e40((ObjectRefWord *)&obj.w11, -1);
    FUN_00458dc0((void **)&obj.w10, -1);
    FUN_003cafa0(&obj.w9, -1);
    igStringRef_Destruct(&obj.w7, -1);
    igStringRef_Destruct(&obj.w6, -1);
    return t;
}

void **FUN_00458dc0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

ObjectRefWord *FUN_00458e40(ObjectRefWord *self,int delete_storage) {
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

void FUN_00458ec0(void)
{
    igMetaObject_RunStaticInit(igStatisticsItem_Register);
}

static igMetaObjectCallback g_igStatisticsItem_callbackList[] = { igGuiComponent_EnsureRegistered, igDefaultAspect_EnsureRegistered, igTextElement_EnsureRegistered, FUN_004588e0, 0 };

void igStatisticsItem_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igStatisticsItem_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igStatisticsItem_GetMetaObject,
        "igStatisticsItem",
        0x3C, /* instance size */
        igStatisticsItem_GetVTable,
        &igStatisticsItem_InitFields,
        0, /* extra callback item */
        g_igStatisticsItem_callbackList /* callback list */
    );
}

void thunk_igStatisticsItem_GetMetaObject(void) {
    igStatisticsItem_GetMetaObject();
}

static FieldFactory g_igStatisticsItem_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igEnumMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_igStatisticsItem_fieldTable[] = {
    "_value",
    "_maximumValue",
    "_useMultiplier",
    "_text",
    "_numberFormat",
    "_visible",
    "_displayComponent",
    "_aspect",
    "_textElement",
    "_manager",
    "_statId",
    "_otherId",
};
static igMetaField **g_igStatisticsItem_fieldHandles[] = {
    &g_igStatisticsItem_valueMetaField,
    &g_igStatisticsItem_maximumValueMetaField,
    &g_igStatisticsItem_useMultiplierMetaField,
    &g_igStatisticsItem_textMetaField,
    &g_igStatisticsItem_numberFormatMetaField,
    &g_igStatisticsItem_visibleMetaField,
    &g_igStatisticsItem_displayComponentMetaField,
    &g_igStatisticsItem_aspectMetaField,
    &g_igStatisticsItem_textElementMetaField,
    &g_igStatisticsItem_managerMetaField,
    &g_igStatisticsItem_statIdMetaField,
    &g_igStatisticsItem_otherIdMetaField,
};
static int g_igStatisticsItem_fieldOffsets[] = {
    12,
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
    56,
};


void igStatisticsItem_InitFields(void) {
    igEnumMetaField *temp_v0;
    igObjectRefMetaField *temp_s2;
    igObjectRefMetaField *temp_s2_2;
    igObjectRefMetaField *temp_s2_3;
    igObjectRefMetaField *temp_s2_4;
    void *temp_s1;
    int temp_s0;

    temp_s1 = g_igStatisticsItem_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_igStatisticsItem_ctorTable, 0xC);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s1, temp_s0), 0.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1), -1.0f);
    temp_s2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    temp_s2->_metaObject = FUN_0044ff40();
    temp_s2_2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    temp_s2_2->_metaObject = FUN_004516e0();
    temp_s2_3 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    temp_s2_3->_metaObject = FUN_0044bce0();
    temp_s2_3->_construct = 1;
    temp_s2_4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    temp_s2_4->_metaObject = (int)FUN_004586a0();
    temp_s2_4->_refCounted = 0;
    temp_v0 = (igEnumMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xA));
    igEnumMetaField_SetDefaultValue(temp_v0, -1);
    temp_v0->_getMetaEnumFunction = (int)(&FUN_00149b60);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB), -1);
    igMetaObject_NameFields(temp_s1, g_igStatisticsItem_fieldTable, g_igStatisticsItem_fieldHandles, g_igStatisticsItem_fieldOffsets, temp_s0);
}

