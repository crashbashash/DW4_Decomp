igMetaObject *g_igPsx2Semaphore_metaObject;
igMetaField *g_igPsx2Semaphore_semaIDMetaField;
igMetaField *g_igPsx2Semaphore_initCountMetaField;
igMetaField *g_igPsx2Semaphore_maxCountMetaField;

igMetaObject *igPsx2Semaphore_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Semaphore_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2Semaphore_EnsureRegistered();
    return g_igPsx2Semaphore_metaObject;
}

int igPsx2Semaphore_GetVTable(void) {
    igPsx2Semaphore semaphore;
    int vtable;
    void **q;
    int *header;
    int refCount;
    void *chars;

    igObject_InitHeader((igObject *)&semaphore);
    q = (void **)&semaphore._name;
    *q = 0;
    semaphore._vtable = (int)&g_igNamedObject_vtable[0];
    semaphore._vtable = (int)&g_igPsx2Semaphore_vtable[0];
    vtable = *(int *)((char *)&semaphore + g_objectSystem->vtableProbeOffset);
    semaphore._vtable = (int)&g_igNamedObject_vtable[0];
    if (q != 0) {
        chars = *q;
        if (chars != 0) {
            header = (int *)((char *)chars - 8);
            refCount = *(int *)((char *)(chars) - 4) - 1;
            *(int *)((char *)(chars) - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
            }
        }
    }
    return vtable;
}

void igPsx2Semaphore_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2Semaphore_Register);
}

CallbackArray *igPsx2Semaphore_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igPsx2Semaphore_metaObject,
        Gap::Core::igSemaphore::arkRegisterInternal,
        Gap::Core::igSemaphore::getClassMeta,
        igPsx2Semaphore_GetMetaObjectFunction,
        "igPsx2Semaphore",
        0x18,
        igPsx2Semaphore_GetVTable,
        igPsx2Semaphore_InitFields,
        0,
        0
    );
}

static FieldFactory g_igPsx2Semaphore_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igPsx2Semaphore_fieldTable[] = {
    "_semaID",
    "_initCount",
    "_maxCount",
};
static igMetaField **g_igPsx2Semaphore_fieldDescriptors[] = {
    &g_igPsx2Semaphore_semaIDMetaField,
    &g_igPsx2Semaphore_initCountMetaField,
    &g_igPsx2Semaphore_maxCountMetaField,
};
static int g_igPsx2Semaphore_fieldOffsets[] = {
    12,
    16,
    20,
};

void igPsx2Semaphore_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)(g_igPsx2Semaphore_metaObject);
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igPsx2Semaphore_ctorTable, 3);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, first)))->setDefault(-1);
    ((Gap::Core::igUnsignedIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 1)))->setDefault(1);
    ((Gap::Core::igUnsignedIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)))->setDefault(1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igPsx2Semaphore_fieldTable, g_igPsx2Semaphore_fieldDescriptors, g_igPsx2Semaphore_fieldOffsets, first);
    g_igPsx2Semaphore_metaObject->_writeProxy = (int)(&Gap::Core::igSemaphore::getClassMetaSafe);
}

