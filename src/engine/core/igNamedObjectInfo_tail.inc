typedef igSmartPointer<igTDataList<igNamedObject *> > igNamedObjectListRef;

/* Writes the directory entry for `object`: under its own name when the info lists it, else through
 * the base class, which looks for the object among the info's reference fields. */
void Gap__Core__igNamedObjectInfo__vfunc_23(igNamedObjectInfo *self, int file, igNamedObject *object) {
    for (int i = 0; i < ((igNamedObjectListRef &)self->_objects)->count(); i++) {
        igNamedObject *named = ((igNamedObjectListRef &)self->_objects)->get(i);
        if (named == object) {
            FUN_002e2d30(file, self, named->_name ? (int *)named->_name : emptyString, object);
            return;
        }
    }
    FUN_002ea0d0((void **)self, file, (int)object);
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

