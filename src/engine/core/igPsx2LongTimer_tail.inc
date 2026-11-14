igMetaObject *igPsx2LongTimer_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2LongTimer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2LongTimer_EnsureRegistered();
    return g_igPsx2LongTimer_metaObject[0];
}

int igPsx2LongTimer_GetVTable(void) {
    igPsx2LongTimer timer;

    igObject_InitHeader((igObject *)&timer);
    timer._vtable = (int)&DAT_0052da90[0];
    return *(int *)((char *)&timer + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igPsx2LongTimer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2LongTimer_Register);
}

void igPsx2LongTimer_Register(void) {
    CoreLibrary_MarkRegistered();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2LongTimer_metaObject),
        igLongTimer_Register,
        igLongTimer_GetPublishedMetaObject,
        igPsx2LongTimer_GetMetaObjectFunction,
        igPsx2LongTimer_className,
        0x28, /* instance size */
        igPsx2LongTimer_GetVTable,
        0,
        igPsx2LongTimer_StaticInitCallback,                                /* static-initializer callback item (appended on fresh configuration) */
        0                                            /* 0-terminated dependency-callback list */
    );
}

int igLongTimer_GetPublishedMetaObject(void) {
    return ((int *)g_igLongTimer_metaObject)[0];
}

void igPsx2LongTimer_StaticInitCallback(void) {
    igPsx2LongTimer_StaticInit();
}

