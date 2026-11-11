void * FUN_002ba650(int arg0) {
    FUN_002ba730();
    return (void *)(igMetaObject_CreateInstance((CreateMeta *)(*(int *)0x585970), (MemoryPool *)arg0));
}

int FUN_002ba690(void) {
    if (DAT_00585970[0] == 0) {
        DAT_00585970[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00585970[0];
}

igMetaObject *igSemaphore_GetMetaObject(void)
{
    igMetaObject *g = g_igSemaphore_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002ba730();
    return g_igSemaphore_metaObject[0];
}

void FUN_002ba730(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igSemaphore_Register);
}

void igSemaphore_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igSemaphore_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igSemaphore_GetMetaObject,
        igSemaphore_className,
        0xC, /* instance size */
        0,
        &igSemaphore_InitFields_002ba7c0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igSemaphore_GetMetaObject(void) {
    igSemaphore_GetMetaObject();
}

void FUN_002ba7c0(void) {
    *(int *)((char *)(((void * *)DAT_00585970)[0]) + 60) = (int)(&thunk_igPsx2Semaphore_GetMetaObject);
}

