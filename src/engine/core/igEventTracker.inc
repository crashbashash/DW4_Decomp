igMetaObject *g_igEventTracker_metaObject;
igMetaField *g_igEventTracker_flagsMetaField;
igMetaField *g_igEventTracker_eventTypeFilterFlagsMetaField;
igMetaField *g_igEventTracker_memoryFieldFilterFlagsMetaField;
igMetaField *g_igEventTracker_markerTypeFilterFlagsMetaField;
igMetaField *g_igEventTracker_notificationTypeFilterFlagsMetaField;
igMetaField *g_igEventTracker_notificationCodeFilterFlagsMetaField;
igMetaField *g_igEventTracker_capacityMetaField;
igMetaField *g_igEventTracker_countMetaField;
igMetaField *g_igEventTracker_detachAllocationsCounterMetaField;
igMetaField *g_igEventTracker_namesMetaField;
igMetaField *g_igEventTracker_groupsMetaField;
igMetaField *g_igEventTracker_classNamesMetaField;
igMetaField *g_igEventTracker_memberNamesMetaField;
igMetaField *g_igEventTracker_annotationsMetaField;
igMetaField *g_igEventTracker_sourceFileNamesMetaField;
igMetaField *g_igEventTracker_callStacksMetaField;
igMetaField *g_igEventTracker_locationsMetaField;
igMetaField *g_igEventTracker_eventRecordsMetaField;
igMetaField *g_igEventTracker_hashIndexMetaField;
igMetaField *g_igEventTracker_codeReferenceAddressMetaField;
igMetaField *g_igEventTracker_callStackTracerMetaField;
igMetaField *g_igEventTracker_eventFormatOffsetsMetaField;
igMetaField *g_igEventTracker_defaultMemoryEventFormatMetaField;
igMetaField *g_igEventTracker_eventTypeNameOffsetsMetaField;
igMetaField *g_igEventTracker_markerTypeNameOffsetsMetaField;
igMetaField *g_igEventTracker_notificationTypeNameOffsetsMetaField;
igMetaField *g_igEventTracker_notificationCodeNameOffsetsMetaField;
igMetaField *g_igEventTracker_formatBufferMetaField;
igMetaField *g_igEventTracker_eventTagMetaField;
igMetaField *g_igEventTracker_eventTagOffsetMetaField;
igMetaField *g_igEventTracker_eventClassNameMetaField;
igMetaField *g_igEventTracker_eventClassNameOffsetMetaField;
igMetaField *g_igEventTracker_lockMetaField;

void * igEventTracker_Create(int allocator) {
    igEventTracker_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igEventTracker_metaObject, (igMemoryPoolView *)allocator));
}

igMetaObject *igEventTracker_GetOrCreateMetaObject(void) {
    if (g_igEventTracker_metaObject == 0) {
        g_igEventTracker_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igEventTracker_metaObject;
}

igMetaObject *igEventTracker_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igEventTracker_metaObject != 0) {
        ready = (g_igEventTracker_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igEventTracker_EnsureRegistered();
done:
    return g_igEventTracker_metaObject;
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
    t = *(int *)((char *)&tracker + g_objectSystem->vtableProbeOffset);
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
    igMetaObject_RunStaticInit(igEventTracker_Register);
}

static igMetaObjectCallback g_igEventTracker_callbackList[] = { igStringTable_EnsureRegistered, igCallStackTable_EnsureRegistered, igLocationTable_EnsureRegistered, igCharListNoClean_EnsureRegistered, igIntListNoClean_EnsureRegistered, igCallStackTracer_EnsureRegistered, igSemaphore_EnsureRegistered, 0 };

CallbackArray *igEventTracker_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igEventTracker_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igEventTracker_GetMetaObjectFunction,
        "igEventTracker",
        0x2530,
        igEventTracker_GetVTable,
        igEventTracker_InitFields,
        0,
        g_igEventTracker_callbackList
    );
}

void igEventTracker_GetMetaObjectFunction(void) {
    igEventTracker_GetMetaObject();
}

static FieldFactory g_igEventTracker_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntArrayMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igIntArrayMetaField_Create,
    (FieldFactory)igIntArrayMetaField_Create,
    (FieldFactory)igIntArrayMetaField_Create,
    (FieldFactory)igIntArrayMetaField_Create,
    (FieldFactory)igCharArrayMetaField_Create,
    (FieldFactory)igCharArrayMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igCharArrayMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igEventTracker_fieldTable[] = {
    "_flags",
    "_eventTypeFilterFlags",
    "_memoryFieldFilterFlags",
    "_markerTypeFilterFlags",
    "_notificationTypeFilterFlags",
    "_notificationCodeFilterFlags",
    "_capacity",
    "_count",
    "_detachAllocationsCounter",
    "_names",
    "_groups",
    "_classNames",
    "_memberNames",
    "_annotations",
    "_sourceFileNames",
    "_callStacks",
    "_locations",
    "_eventRecords",
    "_hashIndex",
    "_codeReferenceAddress",
    "_callStackTracer",
    "_eventFormatOffsets",
    "_defaultMemoryEventFormat",
    "_eventTypeNameOffsets",
    "_markerTypeNameOffsets",
    "_notificationTypeNameOffsets",
    "_notificationCodeNameOffsets",
    "_formatBuffer",
    "_eventTag",
    "_eventTagOffset",
    "_eventClassName",
    "_eventClassNameOffset",
    "_lock",
};
static igMetaField **g_igEventTracker_fieldDescriptors[] = {
    &g_igEventTracker_flagsMetaField,
    &g_igEventTracker_eventTypeFilterFlagsMetaField,
    &g_igEventTracker_memoryFieldFilterFlagsMetaField,
    &g_igEventTracker_markerTypeFilterFlagsMetaField,
    &g_igEventTracker_notificationTypeFilterFlagsMetaField,
    &g_igEventTracker_notificationCodeFilterFlagsMetaField,
    &g_igEventTracker_capacityMetaField,
    &g_igEventTracker_countMetaField,
    &g_igEventTracker_detachAllocationsCounterMetaField,
    &g_igEventTracker_namesMetaField,
    &g_igEventTracker_groupsMetaField,
    &g_igEventTracker_classNamesMetaField,
    &g_igEventTracker_memberNamesMetaField,
    &g_igEventTracker_annotationsMetaField,
    &g_igEventTracker_sourceFileNamesMetaField,
    &g_igEventTracker_callStacksMetaField,
    &g_igEventTracker_locationsMetaField,
    &g_igEventTracker_eventRecordsMetaField,
    &g_igEventTracker_hashIndexMetaField,
    &g_igEventTracker_codeReferenceAddressMetaField,
    &g_igEventTracker_callStackTracerMetaField,
    &g_igEventTracker_eventFormatOffsetsMetaField,
    &g_igEventTracker_defaultMemoryEventFormatMetaField,
    &g_igEventTracker_eventTypeNameOffsetsMetaField,
    &g_igEventTracker_markerTypeNameOffsetsMetaField,
    &g_igEventTracker_notificationTypeNameOffsetsMetaField,
    &g_igEventTracker_notificationCodeNameOffsetsMetaField,
    &g_igEventTracker_formatBufferMetaField,
    &g_igEventTracker_eventTagMetaField,
    &g_igEventTracker_eventTagOffsetMetaField,
    &g_igEventTracker_eventClassNameMetaField,
    &g_igEventTracker_eventClassNameOffsetMetaField,
    &g_igEventTracker_lockMetaField,
};
static int g_igEventTracker_fieldOffsets[] = {
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
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
    92,
    96,
    224,
    228,
    356,
    484,
    548,
    804,
    9000,
    9256,
    9260,
    9516,
    8,
};

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

    meta = g_igEventTracker_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igEventTracker_ctorTable, 0x21);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1), -1);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2), -1);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3), -1);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4), -1);
    igUnsignedIntMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5), -1);
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
    igStringMetaField_SetDefaultText((igMetaField *)defaultMemoryEventFormat, 0);
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
    igIntMetaField_SetDefault((igMetaField *)eventTagOffset, -1);
    eventTagOffset->_persistent = 0;
    eventClassName = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1E));
    ((igCharArrayMetaField *)eventClassName)->_num = 0x100;
    eventClassName->_persistent = 0;
    eventClassNameOffset = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x1F));
    igIntMetaField_SetDefault((igMetaField *)eventClassNameOffset, -1);
    eventClassNameOffset->_persistent = 0;
    lock = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x20));
    ((igObjectRefMetaField *)lock)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    lock->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igEventTracker_fieldTable, g_igEventTracker_fieldDescriptors, g_igEventTracker_fieldOffsets, base);
}

