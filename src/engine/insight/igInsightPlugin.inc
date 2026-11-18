igMetaObject *g_igInsightPlugin_metaObject;

igMetaObject *igInsightPlugin_GetMetaObject(void)
{
    igMetaObject *g = g_igInsightPlugin_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igInsightPlugin_EnsureRegistered();
    return g_igInsightPlugin_metaObject;
}

void igInsightPlugin_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igInsightPlugin_Register);
}

CallbackArray *igInsightPlugin_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igInsightPlugin_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igInsightPlugin_GetMetaObjectFunction,
        "igInsightPlugin",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igInsightPlugin_GetMetaObjectFunction(void) {
    igInsightPlugin_GetMetaObject();
}

