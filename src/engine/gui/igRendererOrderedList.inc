void FUN_0044c490(int arg0) {
    igRendererOrderedList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x58C200, arg0);
}

igMetaObject *FUN_0044c4d0(void) {
    if (g_igRendererOrderedList_metaObject[0] == 0) {
        g_igRendererOrderedList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igRendererOrderedList_metaObject[0];
}

igMetaObject *igRendererOrderedList_GetMetaObject(void)
{
    igMetaObject *g = g_igRendererOrderedList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRendererOrderedList_EnsureRegistered();
    return g_igRendererOrderedList_metaObject[0];
}

int igRendererOrderedList_GetVTable(void) {
    struct Obj_44c570 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.vt = &DAT_00541d70[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00541d70[0];
    FUN_0044c5e0((int **)&obj, 0);
    return r;
}

int **FUN_0044c5e0(int **arg0, long long arg1) {
    if (arg0 != 0) {
        *arg0 = &DAT_00541dd0[0];
        if (arg0 != 0) {
            *arg0 = &DAT_0052cc20[0];
            ObjectRef_Destruct_001c6460((int **)((char *)arg0 + 0x14), -1);
            FUN_00135430((int **)((char *)arg0 + 0x10), -1);
            FUN_00233590((int **)((char *)arg0 + 0xC), -1);
            FUN_0014aa70((int **)((char *)arg0 + 8), -1);
        }
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            thunk_FUN_002ed460__002ff810(arg0);
        }
    }
    return arg0;
}

void igRendererOrderedList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRendererOrderedList_Register);
}

void igRendererOrderedList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRendererOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        thunk_igRendererOrderedList_GetMetaObject,
        igRendererOrderedList_className,
        0x1C, /* instance size */
        igRendererOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRendererOrderedList_callbackList /* callback list */
    );
}

void thunk_igRendererOrderedList_GetMetaObject(void) {
    igRendererOrderedList_GetMetaObject();
}

