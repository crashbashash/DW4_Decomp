igMetaObject *FUN_0045e6f0(void) {
    if (g_igActorManagerParams_metaObject[0] == 0) {
        g_igActorManagerParams_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igActorManagerParams_metaObject[0];
}

void *igActorManagerParams_GetMetaObject(void) {
    igMetaObject *g = g_igActorManagerParams_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045e830();
    }
    return g_igActorManagerParams_metaObject[0];
}

int igActorManagerParams_GetVTable(void) {
    union U_45e790 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00540e30[0];
    u.vt = (int)&DAT_00541fe0[0];
    s0 = *(int *)&u.b[*(int *)((char *)(((void *)g_objectSystem[0])) + 916)];
    u.vt = (int)&DAT_00540e30[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            v1[1] = v1[1] - 1;
            if ((v1[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(v1);
            }
        }
    }
    return s0;
}

void FUN_0045e830(void)
{
    igMetaObject_RunStaticInit(igActorManagerParams_Register);
}

void igActorManagerParams_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igActorManagerParams_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igActorManagerParams_GetMetaObject,
        igActorManagerParams_className,
        0x10, /* instance size */
        igActorManagerParams_GetVTable,
        &igActorManagerParams_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igActorManagerParams_GetMetaObject(void) {
    igActorManagerParams_GetMetaObject();
}

void igActorManagerParams_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igActorManagerParams_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d1aa8[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004d1ab0[0], &DAT_004d1ab8[0], &DAT_004d1ac0[0], temp_s1);
}

igMetaObject *Gap__Viewer__igActorManagerParams__vfunc_22(void) {
    return g_igActorManagerParams_metaObject[0];
}

