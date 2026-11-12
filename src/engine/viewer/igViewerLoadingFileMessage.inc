void FUN_0045a680(int arg0) {
    FUN_0045a7a0();
    igMetaObject_CreateInstance(*(int *)0x58C910, arg0);
}

igMetaObject *igViewerLoadingFileMessage_GetMetaObject(void) {
    igMetaObject *g = g_igViewerLoadingFileMessage_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_0045a7a0();
    return g_igViewerLoadingFileMessage_metaObject[0];
}

int igViewerLoadingFileMessage_GetVTable(void) {
    struct Obj_45a680 obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542100[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
    obj.vt = &DAT_00542100[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void FUN_0045a7a0(void)
{
    igMetaObject_RunStaticInit(igViewerLoadingFileMessage_Register);
}

void igViewerLoadingFileMessage_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerLoadingFileMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewerLoadingFileMessage_GetMetaObject,
        igViewerLoadingFileMessage_className,
        0x10, /* instance size */
        igViewerLoadingFileMessage_GetVTable,
        &igViewerLoadingFileMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewerLoadingFileMessage_GetMetaObject(void) {
    igViewerLoadingFileMessage_GetMetaObject();
}

void igViewerLoadingFileMessage_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igViewerLoadingFileMessage_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0e38[0], 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), &DAT_0051eef0[0]);
    igMetaObject_NameFields(temp_s0, &DAT_004d0e40[0], &DAT_004d0e48[0], &DAT_004d0e50[0], temp_s1);
}

