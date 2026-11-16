igMetaField *igMetaField_FindByName(int self, char *qualifiedName) {
    igMetaField *found; char *separator; char *fieldName; int n; int i; int j; int fieldCount; igMetaObject *meta; __internalObjectList *list; char *className; igMetaField *field;
    found = 0;
    if (strncmp(qualifiedName, g_metaFieldNamePrefix, strlen(g_metaFieldNamePrefix)) == 0) {
        qualifiedName = qualifiedName + strlen(g_metaFieldNamePrefix);
        separator = strstr(qualifiedName, g_metaFieldScopeSeparator);
        if (separator != 0) {
            fieldName = separator + strlen(g_metaFieldScopeSeparator);
            i = 0;
            list = (__internalObjectList *)g_objectSystem->metaRegistry;
            n = list->_count;
            goto test;
body:
            meta = 0;
            if (i < list->_count) { meta = ((igMetaObject **)list->_data)[i]; }
            className = (char *)meta->_name;
            if (strncmp(className, qualifiedName, strlen(className)) == 0) {
                fieldCount = igMetaObject_GetFieldCount((igMetaObject *)meta);
                j = 0;
                goto t2;
b2:
                field = ((igMetaField *)igMetaObject_GetFieldAt(meta, j));
                if (strcmp((char *)field->_fieldName, fieldName) == 0) {
                    found = field;
                    goto next;
                }
                j++;
t2:
                if (j < fieldCount) goto b2;
            }
next:
            i++;
test:
            if (i < n) goto body;
        }
    }
    return found;
}

