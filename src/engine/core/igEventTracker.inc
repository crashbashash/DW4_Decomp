void * FUN_002c5780(int arg0) {
    FUN_002c59e0();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x586480), (MemoryPool *)arg0));
}

igMetaObject *FUN_002c57c0(void) {
    if (g_igEventTracker_metaObject[0] == 0) {
        g_igEventTracker_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igEventTracker_metaObject[0];
}

igMetaObject *igEventTracker_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igEventTracker_metaObject[0] != 0) {
        ready = (g_igEventTracker_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_002c59e0();
done:
    return g_igEventTracker_metaObject[0];
}

int igEventTracker_GetVTable(void) {
    struct Obj_2c5860 obj;
    int t;
    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_00530420[0];
    obj.w2 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.w20 = 0;
    obj.w21 = 0;
    obj.w23 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    obj.vt = &DAT_00530420[0];
    FUN_002ba7f0((ObjectRefWord *)&obj.w23, -1);
    FUN_002b86c0((void **)&obj.w21, -1);
    FUN_002b8f10((R_2b8f10 **)&obj.w20, -1);
    FUN_002ba870((void **)&obj.w19, -1);
    FUN_002ba8f0((void **)&obj.w18, -1);
    FUN_002b8740((ObjectRefWord *)&obj.w17, -1);
    FUN_002b8740((ObjectRefWord *)&obj.w16, -1);
    FUN_002b8740((ObjectRefWord *)&obj.w15, -1);
    FUN_002b8740((ObjectRefWord *)&obj.w14, -1);
    FUN_002b8740((ObjectRefWord *)&obj.w13, -1);
    FUN_002b8740((ObjectRefWord *)&obj.w12, -1);
    FUN_002ba970((Ref **)&obj.w2, -1);
    return t;
}

void FUN_002c59e0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igEventTracker_Register);
}

void igEventTracker_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igEventTracker_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEventTracker_GetMetaObject,
        igEventTracker_className,
        0x2530, /* instance size */
        igEventTracker_GetVTable,
        &igEventTracker_InitFields,
        0, /* extra callback item */
        g_igEventTracker_callbackList /* callback list */
    );
}

void thunk_igEventTracker_GetMetaObject(void) {
    igEventTracker_GetMetaObject();
}

void igEventTracker_InitFields(void) {
    igMetaObject *temp_s0;
    int temp_s1;
    igMetaField *temp_s2;
    igMetaField *temp_s2_10;
    igMetaField *temp_s2_11;
    igMetaField *temp_s2_12;
    igMetaField *temp_s2_2;
    igMetaField *temp_s2_3;
    igMetaField *temp_s2_4;
    igMetaField *temp_s2_5;
    igMetaField *temp_s2_6;
    igMetaField *temp_s2_7;
    igMetaField *temp_s2_8;
    igMetaField *temp_s2_9;
    igMetaField *temp_v0;
    igMetaField *temp_v0_2;
    igMetaField *temp_v0_3;
    igMetaField *temp_v0_4;
    igMetaField *temp_v0_5;
    igMetaField *temp_v0_6;

    temp_s0 = g_igEventTracker_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igEventTracker_ctorTable[0], 0x21);
    FUN_0030e9b0((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1))), -1);
    FUN_0030e9b0((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2))), -1);
    FUN_0030e9b0((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3))), -1);
    FUN_0030e9b0((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4))), -1);
    FUN_0030e9b0((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5))), -1);
    ((igMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)))->_persistent = 0;
    temp_s2 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_002b8d90();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_002b8d90();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_002b8d90();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_002b8d90();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xD));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)FUN_002b8d90();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xE));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_002b8d90();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xF));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)FUN_002cc7e0();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x10));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)FUN_002c1fa0();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x11));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)FUN_002cace0();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x12));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = (int)FUN_002ca8f0();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x14));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = (int)FUN_002cc630();
    ((igRefMetaField *)temp_s2_11)->_construct = 1;
    temp_s2_11->_persistent = 0;
    { igIntArrayMetaField *q = (igIntArrayMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x15)); q->_num = 0x20; }
    temp_v0 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x16));
    igStringMetaField_SetDefaultText((int *)temp_v0, 0);
    ((igStringMetaField *)temp_v0)->_refCounted = 0;
    temp_v0->_persistent = 0;
    { igIntArrayMetaField *q = (igIntArrayMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x17)); q->_num = 0x20; }
    { igIntArrayMetaField *q = (igIntArrayMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x18)); q->_num = 0x20; }
    { igIntArrayMetaField *q = (igIntArrayMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x19)); q->_num = 0x10; }
    { igIntArrayMetaField *q = (igIntArrayMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1A)); q->_num = 0x40; }
    temp_v0_2 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1B));
    ((igCharArrayMetaField *)temp_v0_2)->_num = 0x2004;
    temp_v0_2->_persistent = 0;
    temp_v0_3 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1C));
    ((igCharArrayMetaField *)temp_v0_3)->_num = 0x100;
    temp_v0_3->_persistent = 0;
    temp_v0_4 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1D));
    FUN_002ea4b0((void **)temp_v0_4, -1);
    temp_v0_4->_persistent = 0;
    temp_v0_5 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1E));
    ((igCharArrayMetaField *)temp_v0_5)->_num = 0x100;
    temp_v0_5->_persistent = 0;
    temp_v0_6 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1F));
    FUN_002ea4b0((void **)temp_v0_6, -1);
    temp_v0_6->_persistent = 0;
    temp_s2_12 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x20));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = (int)FUN_002ba690();
    temp_s2_12->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igEventTracker_fieldTable[0], (igMetaField ***)&DAT_004c0e50[0], &DAT_004c0ee0[0], temp_s1);
}

