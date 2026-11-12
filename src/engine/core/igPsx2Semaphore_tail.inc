igMetaObject *igPsx2Semaphore_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Semaphore_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cf7a0();
    return g_igPsx2Semaphore_metaObject[0];
}

int igPsx2Semaphore_GetVTable(void) {
    struct Obj_2cf710 o;
    int temp_s0;
    void **q;
    int *temp_a1;
    int temp_v0;
    void *temp_v1;

    igObject_InitHeader((struct ObjectHeader *)&o);
    q = &o.s;
    *q = 0;
    o.vt = &g_igNamedObject_vtable[0];
    o.vt = &DAT_0052d970[0];
    temp_s0 = *(int *)((char *)&o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    o.vt = &g_igNamedObject_vtable[0];
    if (q != 0) {
        temp_v1 = *q;
        if (temp_v1 != 0) {
            temp_a1 = (int *)((char *)temp_v1 - 8);
            temp_v0 = *(int *)((char *)(temp_v1) - 4) - 1;
            *(int *)((char *)(temp_v1) - 4) = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_002cf7a0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2Semaphore_Register);
}

void igPsx2Semaphore_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2Semaphore_metaObject),
        igSemaphore_Register,
        igSemaphore_GetPublishedMetaObject,
        thunk_igPsx2Semaphore_GetMetaObject,
        igPsx2Semaphore_className,
        0x18, /* instance size */
        igPsx2Semaphore_GetVTable,
        &igPsx2Semaphore_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

igMetaObject *FUN_002cf820(void) {
    return g_igSemaphore_metaObject[0];
}

void igPsx2Semaphore_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igPsx2Semaphore_metaObject[0]);
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&DAT_004c1cf8[0], 3);
    FUN_002ea4b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)), -1);
    FUN_0030e9b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)), 1);
    FUN_0030e9b0((void **)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&DAT_004c1d08[0], (igMetaField ***)&DAT_004c1d18[0], &DAT_004c1d28[0], temp_s1);
    *(int *)((char *)(g_igPsx2Semaphore_metaObject[0]) + 64) = (int)(&thunk_igSemaphore_GetMetaObject);
}

