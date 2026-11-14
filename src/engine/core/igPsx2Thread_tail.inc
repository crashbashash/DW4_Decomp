igMetaObject *igPsx2Thread_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Thread_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cf540();
    return g_igPsx2Thread_metaObject[0];
}

int igPsx2Thread_GetVTable(void) {
    igPsx2Thread thread;
    int t;
    char *o;
    int *a1;
    int v0;
    S_ref *p0, *p1;
    igObject_InitHeader((igObject *)&thread);
    p0 = (S_ref *)&thread._name;
    *(int *)p0 = 0;
    thread._vtable = (int)&DAT_0052d7c0[0];
    p1 = (S_ref *)&thread._threadDoneSema;
    *(int *)p1 = 0;
    t = *(int *)((char *)&thread + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    thread._vtable = (int)&DAT_0052d7c0[0];
    if (p1 != 0) {
        p1 = *(S_ref **)p1;
        if (p1 != 0) {
            p1->f4 = (int)((int) (p1->f4 - 1));
            if (((unsigned long long) ((long long) p1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(p1);
            }
        }
    }
    thread._vtable = (int)&g_igNamedObject_vtable[0];
    if (p0 != 0) {
        o = *(char **)p0;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
            }
        }
    }
    return t;
}

void FUN_002cf540(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2Thread_Register);
}

void igPsx2Thread_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2Thread_metaObject),
        igThread_Register,
        igThread_GetPublishedMetaObject,
        thunk_igPsx2Thread_GetMetaObject,
        igPsx2Thread_className,
        0x40, /* instance size */
        igPsx2Thread_GetVTable,
        &igPsx2Thread_InitFields,
        0, /* extra callback item */
        g_igPsx2Thread_callbackList /* callback list */
    );
}

igMetaObject *FUN_002cf5d0(void) {
    return g_igThread_metaObject[0];
}

void igPsx2Thread_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igPsx2Thread_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igPsx2Thread_ctorTable[0], 6);
    FUN_002ea4b0((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2))), -1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_002ba690();
    *(char *)((char *)(temp_s1) + 52) = 1;
    FUN_002d3890((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 3))), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igPsx2Thread_fieldTable[0], (igMetaField ***)&DAT_004c1cc0[0], &DAT_004c1ce0[0], temp_s2);
    *(int *)((char *)(g_igPsx2Thread_metaObject[0]) + 64) = (int)(&thunk_igThread_GetMetaObject);
}

