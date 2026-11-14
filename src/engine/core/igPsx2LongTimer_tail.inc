igMetaObject *igPsx2LongTimer_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2LongTimer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cfd70();
    return g_igPsx2LongTimer_metaObject[0];
}

int igPsx2LongTimer_GetVTable(void) {
    igPsx2LongTimer timer;

    igObject_InitHeader((igObject *)&timer);
    timer._vtable = (int)&DAT_0052da90[0];
    return *(int *)((char *)&timer + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002cfd70(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2LongTimer_Register);
}

void igPsx2LongTimer_Register(void) {
    FUN_002b5d50();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2LongTimer_metaObject),
        igLongTimer_Register,
        igLongTimer_GetPublishedMetaObject,
        thunk_igPsx2LongTimer_GetMetaObject,
        igPsx2LongTimer_className,
        0x28, /* instance size */
        igPsx2LongTimer_GetVTable,
        0,
        FUN_002cfe00,                                /* static-initializer callback item (appended on fresh configuration) */
        0                                            /* 0-terminated dependency-callback list */
    );
}

int FUN_002cfdf0(void) {
    return ((int *)g_igLongTimer_metaObject)[0];
}

void FUN_002cfe00(void) {
    FUN_0032daf0();
}

