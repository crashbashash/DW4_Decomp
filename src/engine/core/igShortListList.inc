void igShortListList_Create(int arg0) {
    igShortListList_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586828), (igMemoryPoolView *)arg0);
}

igMetaObject *igShortListList_GetOrCreateMetaObject(void) {
    if (g_igShortListList_metaObject[0] == 0) {
        g_igShortListList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igShortListList_metaObject[0];
}

igMetaObject *igShortListList_GetMetaObject(void)
{
    igMetaObject *g = g_igShortListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igShortListList_EnsureRegistered();
    return g_igShortListList_metaObject[0];
}

int igShortListList_GetVTable(void) {
    igShortListList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_00531d50[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igShortListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igShortListList_Register);
}

void igShortListList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igShortListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igShortListList_GetMetaObjectFunction,
        igShortListList_className,
        0x14, /* instance size */
        igShortListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igShortListList_callbackList /* callback list */
    );
}

void igShortListList_GetMetaObjectFunction(void) {
    igShortListList_GetMetaObject();
}

