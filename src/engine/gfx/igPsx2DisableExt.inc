igMetaObject *g_igPsx2DisableExt_metaObject;
igMetaField *g_igPsx2DisableExt_contextMetaField;

void FUN_0014f8a0(void) {
    *(int *)((char *)(g_igDisableExt_metaObject) + 60) = (int)(&thunk_igPsx2DisableExt_GetMetaObject);
}

void thunk_igPsx2DisableExt_GetMetaObject(void) {
    igPsx2DisableExt_GetMetaObject();
}

