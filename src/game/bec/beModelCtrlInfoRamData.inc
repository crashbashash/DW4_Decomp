void *FUN_00352ee0(void) {
    struct G *g = DAT_00588bb0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00353040();
    }
    return DAT_00588bb0[0];
}

int beModelCtrlInfoRamData_GetVTable(void) {
    struct Obj_352f30 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00537bb0[0];
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
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
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void FUN_00353040(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoRamData_Register);
}

void *beModelCtrlInfoRamData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoRamData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beModelCtrlInfoRamData_GetMetaObject,
        beModelCtrlInfoRamData_className,
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

void beModelCtrlInfoRamData_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s1;
    S_ref *temp_v0_2;

    temp_s1 = (void *)(((void * *)DAT_00588bb0)[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004c5480[0], 2);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, &DAT_00502218[0]));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (S_ref *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, &DAT_00502220[0]);
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&DAT_00588bb8[0]);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->f4 = temp_v0_2->f4 - 1;
    if (((unsigned long long) ((long long) temp_v0_2->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    *(int *)((char *)(temp_s0) + 56) = FUN_0034fd40();
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    *(int *)((char *)(temp_s0_2) + 56) = FUN_00350060();
    igMetaObject_NameFields(temp_s1, &DAT_004c5488[0], &DAT_004c5490[0], &DAT_004c5498[0], temp_s2);
}

