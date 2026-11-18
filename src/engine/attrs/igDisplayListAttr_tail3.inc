igMetaObject *igDisplayListAttr_GetMeta(void) {
    return g_igDisplayListAttr_metaObject;
}

void igDisplayListAttr_Reset(void *arg0) {
    *(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 8) = 0;
}

