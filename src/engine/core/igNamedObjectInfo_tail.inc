typedef igSmartPointer<igTDataList<igNamedObject *> > igNamedObjectListRef;

/* Writes the directory entry for `object`: under its own name when the info lists it, else through
 * the base class, which looks for the object among the info's reference fields. */
void Gap__Core__igNamedObjectInfo__vfunc_23(igNamedObjectInfo *self, int file, igNamedObject *object) {
    for (int i = 0; i < ((igNamedObjectListRef &)self->_objects)->count(); i++) {
        igNamedObject *named = ((igNamedObjectListRef &)self->_objects)->get(i);
        if (named == object) {
            FUN_002e2d30((igDirectoryView *)file, (igInfoView *)self, named->_name ? (char *)named->_name : (char *)emptyString, (igObject *)object);
            return;
        }
    }
    FUN_002ea0d0((void **)self, file, (int)object);
}

/* The listed object of the given name, else the base class's lookup among the reference fields. */
igNamedObject *Gap__Core__igNamedObjectInfo__vfunc_24(igNamedObjectInfo *self, const char *name) {
    int i;
    if (name == 0) {
        return 0;
    }
    for (i = 0; i < ((igNamedObjectListRef &)self->_objects)->count(); i++) {
        igNamedObject *named = ((igNamedObjectListRef &)self->_objects)->get(i);
        if (strcmp(named->_name != 0 ? (int *)named->_name : emptyString, name) == 0) {
            return ((igNamedObjectListRef &)self->_objects)->get(i);
        }
    }
    return (igNamedObject *)igObject_GetFieldValueByName((void **)self, (int)name);
}

int FUN_002feeb0(igTDataList<int> *list, igMetaField *field, int value) {
    int i;
    int v;
    if (field == 0) {
        return 0;
    }
    for (i = 0; i < list->_count; i++) {
        v = list->_data[i];
        if (v != 0 && value == *(int *)(v + field->_offset)) {
            return v;
        }
    }
    return 0;
}

