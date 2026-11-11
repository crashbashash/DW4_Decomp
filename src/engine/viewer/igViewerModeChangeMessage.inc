int FUN_0045a450(void) {
    if (DAT_0058c8f8[0] == 0) {
        DAT_0058c8f8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c8f8[0];
}

S *igViewerModeChangeMessage_GetMetaObject(void) {
    S *g = g_igViewerModeChangeMessage_metaObject[0];
    if (g != 0) {
        int b = !!(g->flags & 4);
        if (b) goto done;
    }
    FUN_0045a580();
done:
    return g_igViewerModeChangeMessage_metaObject[0];
}

int igViewerModeChangeMessage_GetVTable(void) {
    Obj_45a450 o;
    int r;
    char *p;
    int *hdr;
    int c;

    igObject_InitHeader(&o);
    o.vt = &DAT_00542160[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    o.vt = &DAT_00542160[0];
    if (&o.s != 0) {
        p = (char *)o.s;
        if (p != 0) {
            hdr = (int *)(p - 8);
            c = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader(*hdr, hdr);
            }
        }
    }
    return r;
}

void FUN_0045a580(void)
{
    igMetaObject_RunStaticInit(igViewerModeChangeMessage_Register);
}

void igViewerModeChangeMessage_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerModeChangeMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewerModeChangeMessage_GetMetaObject,
        igViewerModeChangeMessage_className,
        0x10, /* instance size */
        igViewerModeChangeMessage_GetVTable,
        &igViewerModeChangeMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewerModeChangeMessage_GetMetaObject(void) {
    igViewerModeChangeMessage_GetMetaObject();
}

void igViewerModeChangeMessage_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c8f8[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0e18[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004d0e20[0], &DAT_004d0e28[0], &DAT_004d0e30[0], temp_s1);
}

