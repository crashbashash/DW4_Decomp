int FUN_002ea0d0(void **arg0, int arg1, int arg2) {
    int meta;
    int i;
    int w;
    igMetaField *f;
    meta = (int)((igObjectDispatchView *)(arg0))->getMeta();
    for (i = 0; i < igMetaObject_GetFieldCount((igMetaObject *)meta); i++) {
        f = (igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, i);
        if (igObject_IsKindOf((void *)f, (igMetaObject *)g_igRefMetaField_metaObject[0]) != 0) {
          w = *(int *)((char *)arg0 + f->_offset);
          if (w == arg2) {
            FUN_002e2d30(arg1, arg0, f->_fieldName, arg2);
            return 1;
        }
        }
    }
    return 0;
}

int igObject_GetFieldValueByName(void **arg0, int arg1) {
    void *temp_v0;

    if (arg1 == 0) {
        return 0;
    }
    temp_v0 = (void *)(igMetaObject_FindFieldByName((igMetaObject *)(((igObjectDispatchView *)(arg0))->getMeta()), (const char *)arg1));
    if (temp_v0 == 0) {
        return 0;
    }
    return *(int *)((char *)arg0 + *(int *)((char *)(temp_v0) + 8));
}

