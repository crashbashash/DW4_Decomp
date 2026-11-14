void * igEventTracker_Create(int allocator) {
    igEventTracker_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586480), (igMemoryPoolView *)allocator));
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
    tracker._vtable = (int)&g_igEventTracker_vtable[0];
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
    tracker._vtable = (int)&g_igEventTracker_vtable[0];
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
        0,
        g_igEventTracker_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igEventTracker_GetMetaObjectFunction,
        igEventTracker_className,
        0x2530,
        igEventTracker_GetVTable,
        igEventTracker_InitFields,
        0,
        (igMetaObjectCallback *)g_igEventTracker_callbackList
    );
}

void igEventTracker_GetMetaObjectFunction(void) {
    igEventTracker_GetMetaObject();
}

void igEventTracker_InitFields(void) {
    igMetaObject *meta;
    int base;
    igMetaField *names;
    igMetaField *hashIndex;
    igMetaField *callStackTracer;
    igMetaField *lock;
    igMetaField *groups;
    igMetaField *classNames;
    igMetaField *memberNames;
    igMetaField *annotations;
    igMetaField *sourceFileNames;
    igMetaField *callStacks;
    igMetaField *locations;
    igMetaField *eventRecords;
    igMetaField *defaultMemoryEventFormat;
    igMetaField *formatBuffer;
    igMetaField *eventTag;
    igMetaField *eventTagOffset;
    igMetaField *eventClassName;
    igMetaField *eventClassNameOffset;

    meta = g_igEventTracker_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igEventTracker_ctorTable[0], 0x21);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1))), -1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2))), -1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3))), -1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4))), -1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5))), -1);
    ((igMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8)))->_persistent = 0;
    names = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9));
    ((igObjectRefMetaField *)names)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)names)->_construct = 1;
    groups = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xA));
    ((igObjectRefMetaField *)groups)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)groups)->_construct = 1;
    classNames = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xB));
    ((igObjectRefMetaField *)classNames)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)classNames)->_construct = 1;
    memberNames = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xC));
    ((igObjectRefMetaField *)memberNames)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)memberNames)->_construct = 1;
    annotations = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xD));
    ((igObjectRefMetaField *)annotations)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)annotations)->_construct = 1;
    sourceFileNames = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xE));
    ((igObjectRefMetaField *)sourceFileNames)->_metaObject = (int)igStringTable_GetOrCreateMetaObject();
    ((igRefMetaField *)sourceFileNames)->_construct = 1;
    callStacks = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xF));
    ((igObjectRefMetaField *)callStacks)->_metaObject = (int)igCallStackTable_GetOrCreateMetaObject();
    ((igRefMetaField *)callStacks)->_construct = 1;
    locations = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x10));
    ((igObjectRefMetaField *)locations)->_metaObject = (int)igLocationTable_GetOrCreateMetaObject();
    ((igRefMetaField *)locations)->_construct = 1;
    eventRecords = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x11));
    ((igObjectRefMetaField *)eventRecords)->_metaObject = (int)igCharListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)eventRecords)->_construct = 1;
    hashIndex = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x12));
    ((igObjectRefMetaField *)hashIndex)->_metaObject = (int)igIntListNoClean_GetOrCreateMetaObject();
    ((igRefMetaField *)hashIndex)->_construct = 1;
    callStackTracer = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x14));
    ((igObjectRefMetaField *)callStackTracer)->_metaObject = (int)igCallStackTracer_GetOrCreateMetaObject();
    ((igRefMetaField *)callStackTracer)->_construct = 1;
    callStackTracer->_persistent = 0;
    { igIntArrayMetaField *q = (igIntArrayMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x15)); q->_num = 0x20; }
    defaultMemoryEventFormat = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x16));
    igStringMetaField_SetDefaultText((int *)defaultMemoryEventFormat, 0);
    ((igStringMetaField *)defaultMemoryEventFormat)->_refCounted = 0;
    defaultMemoryEventFormat->_persistent = 0;
    { igIntArrayMetaField *q = (igIntArrayMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x17)); q->_num = 0x20; }
    { igIntArrayMetaField *q = (igIntArrayMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x18)); q->_num = 0x20; }
    { igIntArrayMetaField *q = (igIntArrayMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x19)); q->_num = 0x10; }
    { igIntArrayMetaField *q = (igIntArrayMetaField *)((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1A)); q->_num = 0x40; }
    formatBuffer = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1B));
    ((igCharArrayMetaField *)formatBuffer)->_num = 0x2004;
    formatBuffer->_persistent = 0;
    eventTag = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1C));
    ((igCharArrayMetaField *)eventTag)->_num = 0x100;
    eventTag->_persistent = 0;
    eventTagOffset = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1D));
    igIntMetaField_SetDefault((void **)eventTagOffset, -1);
    eventTagOffset->_persistent = 0;
    eventClassName = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1E));
    ((igCharArrayMetaField *)eventClassName)->_num = 0x100;
    eventClassName->_persistent = 0;
    eventClassNameOffset = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1F));
    igIntMetaField_SetDefault((void **)eventClassNameOffset, -1);
    eventClassNameOffset->_persistent = 0;
    lock = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x20));
    ((igObjectRefMetaField *)lock)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    lock->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igEventTracker_fieldTable[0], (igMetaField ***)&g_igEventTracker_fieldDescriptors[0], &g_igEventTracker_fieldOffsets[0], base);
}

