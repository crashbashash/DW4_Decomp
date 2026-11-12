FieldNameView *igMetaField_FindByName(int arg0, char *arg1) {
    FieldNameView *found; char *q; char *s8; int n; int i; int j; int fc; MetaObjectNameView *o; MetaObjectListView *list; char *nm; FieldNameView *f;
    found = 0;
    if (strncmp(arg1, DAT_004c22b8[0], strlen(DAT_004c22b8[0])) == 0) {
        arg1 = arg1 + strlen(DAT_004c22b8[0]);
        q = strstr(arg1, DAT_004c22c0[0]);
        if (q != 0) {
            s8 = q + strlen(DAT_004c22c0[0]);
            i = 0;
            list = ((MetaObjectRegistryView * *)g_objectSystem)[0]->f24;
            n = list->n;
            goto test;
body:
            o = 0;
            if (i < list->n) { o = list->data[i]; }
            nm = o->f28;
            if (strncmp(nm, arg1, strlen(nm)) == 0) {
                fc = igMetaObject_GetFieldCount((igMetaObject *)o);
                j = 0;
                goto t2;
b2:
                f = ((FieldNameView *)igMetaObject_GetFieldAt((igMetaObject *)o, j));
                if (strcmp(f->f12, s8) == 0) {
                    found = f;
                    goto next;
                }
                j++;
t2:
                if (j < fc) goto b2;
            }
next:
            i++;
test:
            if (i < n) goto body;
        }
    }
    return found;
}

