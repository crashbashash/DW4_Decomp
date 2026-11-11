igMetaObject *igInsightPlugin_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightPlugin_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00232780();
    return g_igInsightPlugin_metaObject[0];
}

void FUN_00232780(void)
{
    igMetaObject_RunStaticInit(igInsightPlugin_Register);
}

void igInsightPlugin_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInsightPlugin_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInsightPlugin_GetMetaObject,
        igInsightPlugin_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igInsightPlugin_GetMetaObject(void) {
    igInsightPlugin_GetMetaObject();
}

