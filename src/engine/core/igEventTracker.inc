void * igEventTracker_Create(int arg0) {
    igEventTracker_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586480), (igMemoryPoolView *)arg0));
}

igMetaObject *igEventTracker_GetOrCreateMetaObject(void) {
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
    igEventTracker_EnsureRegistered();
done:
    return g_igEventTracker_metaObject[0];
}

int igEventTracker_GetVTable(void) {
    igEventTracker tracker;
    int t;
    igObject_InitHeader((igObject *)&tracker);
    tracker._vtable = (int)&DAT_00530420[0];
    tracker._lock = 0;
    tracker._names = 0;
    tracker._groups = 0;
    tracker._classNames = 0;
    tracker._memberNames = 0;
    tracker._annotations = 0;
    tracker._sourceFileNames = 0;
    tracker._callStacks = 0;
    tracker._locations = 0;
    tracker._eventRecords = 0;
    tracker._hashIndex = 0;
    tracker._callStackTracer = 0;
    t = *(int *)((char *)&tracker + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    tracker._vtable = (int)&DAT_00530420[0];
    igSmartPointer_igCallStackTracer_Destruct((igSmartPointer<igObject> *)&tracker._callStackTracer, -1);
    igSmartPointer_igIntListNoClean_Destruct((void **)&tracker._hashIndex, -1);
    igSmartPointer_igCharListNoClean_Destruct((igObject **)&tracker._eventRecords, -1);
    igSmartPointer_igLocationTable_Destruct((void **)&tracker._locations, -1);
    igSmartPointer_igCallStackTable_Destruct((void **)&tracker._callStacks, -1);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&tracker._sourceFileNames, -1);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&tracker._annotations, -1);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&tracker._memberNames, -1);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&tracker._classNames, -1);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&tracker._groups, -1);
    igSmartPointer_igStringTable_Destruct((igSmartPointer<igObject> *)&tracker._names, -1);
    igSmartPointer_igSemaphore_Destruct((igObject **)&tracker._lock, -1);
    return t;
}

void igEventTracker_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igEventTracker_Register);
}

void igEventTracker_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igEventTracker_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igEventTracker_GetMetaObjectFunction,
        igEventTracker_className,
        0x2530, /* instance size */
        igEventTracker_GetVTable,
        &igEventTracker_InitFields,
        0, /* extra callback item */
        g_igEventTracker_callbackList /* callback list */
    );
}

void igEventTracker_GetMetaObjectFunction(void) {
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
    igUnsignedIntMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1))), -1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2))), -1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3))), -1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4))), -1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5))), -1);
    ((igMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)))->_persistent = 0;
    temp_s2 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xC));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xD));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xE));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xF));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)igCallStackTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_7)->_construct = 1;
    temp_s2_8 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x10));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = (int)igLocationTable_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_8)->_construct = 1;
    temp_s2_9 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x11));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = (int)igCharListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_9)->_construct = 1;
    temp_s2_10 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x12));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = (int)igIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_10)->_construct = 1;
    temp_s2_11 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x14));
    ((igObjectRefMetaField *)temp_s2_11)->_metaObject = (int)igCallStackTracer_GetOrCreateMetaObject();
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
    igIntMetaField_SetDefault((void **)temp_v0_4, -1);
    temp_v0_4->_persistent = 0;
    temp_v0_5 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1E));
    ((igCharArrayMetaField *)temp_v0_5)->_num = 0x100;
    temp_v0_5->_persistent = 0;
    temp_v0_6 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x1F));
    igIntMetaField_SetDefault((void **)temp_v0_6, -1);
    temp_v0_6->_persistent = 0;
    temp_s2_12 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0x20));
    ((igObjectRefMetaField *)temp_s2_12)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    temp_s2_12->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igEventTracker_fieldTable[0], (igMetaField ***)&DAT_004c0e50[0], &DAT_004c0ee0[0], temp_s1);
}

