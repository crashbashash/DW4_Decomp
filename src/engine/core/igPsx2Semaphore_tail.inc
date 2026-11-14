igMetaObject *igPsx2Semaphore_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Semaphore_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2Semaphore_EnsureRegistered();
    return g_igPsx2Semaphore_metaObject[0];
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
    vtable = *(int *)((char *)&semaphore + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    semaphore._vtable = (int)&g_igNamedObject_vtable[0];
    if (q != 0) {
        chars = *q;
        if (chars != 0) {
            header = (int *)((char *)chars - 8);
            refCount = *(int *)((char *)(chars) - 4) - 1;
            *(int *)((char *)(chars) - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    return vtable;
}

void igPsx2Semaphore_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2Semaphore_Register);
}

void igPsx2Semaphore_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igPsx2Semaphore_metaObject,
        (igMetaObjectRegisterFunction)igSemaphore_Register,
        igSemaphore_GetPublishedMetaObject,
        igPsx2Semaphore_GetMetaObjectFunction,
        igPsx2Semaphore_className,
        0x18,
        igPsx2Semaphore_GetVTable,
        igPsx2Semaphore_InitFields,
        0,
        0
    );
}

igMetaObject *igSemaphore_GetPublishedMetaObject(void) {
    return g_igSemaphore_metaObject[0];
}

void igPsx2Semaphore_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)(g_igPsx2Semaphore_metaObject[0]);
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igPsx2Semaphore_ctorTable[0], 3);
    igIntMetaField_SetDefault((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, first)), -1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 1)), 1);
    igUnsignedIntMetaField_SetDefaultValue((void **)(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igPsx2Semaphore_fieldTable[0], (igMetaField ***)&g_igPsx2Semaphore_fieldDescriptors[0], &g_igPsx2Semaphore_fieldOffsets[0], first);
    g_igPsx2Semaphore_metaObject[0]->_writeProxy = (int)(&igSemaphore_GetMetaObjectFunction);
}

