igMetaObject *FUN_0044e430(void) {
    if (g_igMouseCursor_metaObject[0] == 0) {
        g_igMouseCursor_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igMouseCursor_metaObject[0];
}

igMetaObject *igMouseCursor_GetMetaObject(void)
{
    igMetaObject *g = g_igMouseCursor_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMouseCursor_RunStaticInit();
    return g_igMouseCursor_metaObject[0];
}

int igMouseCursor_GetVTable(void) {
    struct Obj_44e4d0 obj;
    char *o;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541b10[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00541b10[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void igMouseCursor_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igMouseCursor_Register);
}

void igMouseCursor_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMouseCursor_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMouseCursor_GetMetaObject,
        igMouseCursor_className,
        0x14, /* instance size */
        igMouseCursor_GetVTable,
        &igMouseCursor_InitFields,
        0, /* extra callback item */
        g_igMouseCursor_callbackList /* callback list */
    );
}

void thunk_igMouseCursor_GetMetaObject(void) {
    igMouseCursor_GetMetaObject();
}

void igMouseCursor_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;
    void *temp_a0;
    int buf[2];

    temp_s0 = (void *)g_igMouseCursor_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0238[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    *(int *)((char *)(temp_s1) + 56) = (int)FUN_004505b0();
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    buf[0] = 0;
    buf[1] = 0;
    FUN_0018e2f0(temp_a0, buf);
    igMetaObject_NameFields(temp_s0, &DAT_004d0240[0], &DAT_004d0248[0], &DAT_004d0250[0], temp_s2);
}

