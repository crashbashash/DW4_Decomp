igMetaObject *igPsx2Folder_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Folder_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002d0110();
    return g_igPsx2Folder_metaObject[0];
}

int igPsx2Folder_GetVTable(void) {
    union U_2d0080 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;
    igObject_InitHeader((ObjectHeader *)u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_0052fee0[0];
    u.vt = (int)&DAT_0052db90[0];
    s0 = *(int *)&u.b[*(int *)((char *)(((void * *)DAT_00586dc8)[0]) + 916)];
    u.vt = (int)&DAT_0052fee0[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*a1), (int)a1);
            }
        }
    }
    return s0;
}

void FUN_002d0110(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2Folder_Register);
}

void igPsx2Folder_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2Folder_metaObject),
        igFolder_Register,
        igFolder_GetPublishedMetaObject,
        thunk_igPsx2Folder_GetMetaObject,
        igPsx2Folder_className,
        0xC, /* instance size */
        igPsx2Folder_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

int FUN_002d0190(void) {
    return DAT_00586368[0];
}

