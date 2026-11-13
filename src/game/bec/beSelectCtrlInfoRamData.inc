void *FUN_003452e0(void) {
    igMetaObject *g = g_beSelectCtrlInfoRamData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00345490();
    }
    return g_beSelectCtrlInfoRamData_metaObject[0];
}

int beSelectCtrlInfoRamData_GetVTable(void) {
    Obj_345330 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.r1 = 0;
    obj.vt = &DAT_00539070[0];
    obj.r6 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00539070[0];
    obj.rel6();
    obj.vt = &g_igNamedObject_vtable[0];
    obj.rel1();
    return r;
}

ObjectRefWord *FUN_00345410(ObjectRefWord *self,int delete_storage) {
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

void FUN_00345490(void)
{
    igMetaObject_RunStaticInit(beSelectCtrlInfoRamData_Register);
}

void *beSelectCtrlInfoRamData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSelectCtrlInfoRamData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beSelectCtrlInfoRamData_GetMetaObject,
        beSelectCtrlInfoRamData_className,
        0x20, /* instance size */
        beSelectCtrlInfoRamData_GetVTable,
        beSelectCtrlInfoRamData_InitFields,
        0, /* extra callback item */
        text_0X4 /* callback list */
    );
}

void beSelectCtrlInfoRamData_GetMetaObject(void)
{
    FUN_003452e0();
}

void beSelectCtrlInfoRamData_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s1;
    T_345550 *temp_v0_2;

    temp_s1 = (void *)(((void * *)g_beSelectCtrlInfoRamData_metaObject)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c3a70[0], 4);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00502218[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (T_345550 *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00502220[0]);
    temp_v0_2->f28 = (int)(&DAT_00587f38[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->references = temp_v0_2->references - 1;
    if (((unsigned long long)(long long)temp_v0_2->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    *(int *)((char *)(temp_s0) + 56) = (int)FUN_003456c0();
    igMetaObject_NameFields(temp_s1, &DAT_004c3a80[0], &DAT_004c3a90[0], &DAT_004c3aa0[0], temp_s2);
}

