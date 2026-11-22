namespace Gap {
namespace Core {

bool igInfo::attemptResolve(igDirectory *parentDir, void *ref) {
    igMetaObject *meta = getMeta();
    int i;
    void *value;
    igMetaField *field;
    for (i = 0; i < igMetaObject_GetFieldCount(meta); i++) {
        field = (igMetaField *)igMetaObject_GetFieldAt(meta, i);
        if (field->isOfType(igRefMetaField::getClassMeta())) {
            value = *(void **)((char *)this + field->_offset);
            if (value == ref) {
                igDirectory_AddExternalInfoRef(parentDir, this, field->_fieldName.p, (igObject *)ref);
                return true;
            }
        }
    }
    return false;
}

void *igInfo::resolve(const char *key) {
    igMetaField *field;

    if (key == 0) {
        return 0;
    }
    field = (igMetaField *)igMetaObject_FindFieldByName(getMeta(), key);
    if (field == 0) {
        return 0;
    }
    return *(void **)((char *)this + field->_offset);
}
}
}

