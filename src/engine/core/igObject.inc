int igInfo_FindObjectReference(void **self, int directory, int target) {
    int meta;
    int i;
    int value;
    igMetaField *field;
    meta = (int)((igObjectDispatchView *)(self))->getMeta();
    for (i = 0; i < igMetaObject_GetFieldCount((igMetaObject *)meta); i++) {
        field = (igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, i);
        if (igObject_IsKindOf((void *)field, (igMetaObject *)g_igRefMetaField_metaObject[0]) != 0) {
          value = *(int *)((char *)self + field->_offset);
          if (value == target) {
            FUN_002e2d30((igDirectoryView *)directory, (igInfoView *)self, (char *)field->_fieldName, (igObject *)target);
            return 1;
        }
        }
    }
    return 0;
}

int igObject_GetFieldValueByName(void **self, int name) {
    igMetaField *field;

    if (name == 0) {
        return 0;
    }
    field = (igMetaField *)(igMetaObject_FindFieldByName((igMetaObject *)(((igObjectDispatchView *)(self))->getMeta()), (const char *)name));
    if (field == 0) {
        return 0;
    }
    return *(int *)((char *)self + field->_offset);
}

