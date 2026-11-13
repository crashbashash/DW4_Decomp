igMetaObject *FUN_00458c50(void) {
    if (g_igStatisticsItem_metaObject[0] == 0) {
        g_igStatisticsItem_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igStatisticsItem_metaObject[0];
}

void *igStatisticsItem_GetMetaObject(void) {
    unsigned char b;
    if (((void *)g_igStatisticsItem_metaObject[0]) != 0) {
        b = (*(int *)((char *)(((void *)g_igStatisticsItem_metaObject[0])) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00458ec0();
done:
    return ((void *)g_igStatisticsItem_metaObject[0]);
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
    StringRef_Destruct_00130720(&obj.w7, -1);
    StringRef_Destruct_00130720(&obj.w6, -1);
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

void igStatisticsItem_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStatisticsItem_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igStatisticsItem_GetMetaObject,
        igStatisticsItem_className,
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

void igStatisticsItem_InitFields(void) {
    igEnumMetaField *temp_v0;
    igObjectRefMetaField *temp_s2;
    igObjectRefMetaField *temp_s2_2;
    igObjectRefMetaField *temp_s2_3;
    igObjectRefMetaField *temp_s2_4;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_igStatisticsItem_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d09f0[0], 0xC);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s1, temp_s0), 0.0f);
    FUN_002e3810(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1), -1.0f);
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
    FUN_002dc7a0(temp_v0, &DAT_004d0ab0[0]);
    temp_v0->_getMetaEnumFunction = (int)(&FUN_00149b60);
    FUN_002ea4b0(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xB), -1);
    igMetaObject_NameFields(temp_s1, &DAT_004d0a20[0], &DAT_004d0a50[0], &DAT_004d0a80[0], temp_s0);
}

