/* src/engine/metadata-field-values.c — igMetaField / igMetaObject field-setup primitives One
 * translation unit: 4 functions, in retail address order. Folded from the per-function units by
 * tools/merge_units.py; the matching build splits a function back out with tools/units.py, so
 * `make check` still verifies one function at a time. Interned strings (the field name) are
 * reference counted in place: the count sits at (string - 4) and the owning StringChunk header at
 * (string - 8); dropping the last reference hands the header back with StringChunk_ReleaseHeader. */
#include "dw4/reflected.h"
void MetaRefList_AppendRetained(void *, void *);
int StringPool_Construct();
void *StringPool_Intern();
int FUN_002eb010();
void igMetaField_EnsureDefaultStorage(igMetaField *);
int StringChunk_ReleaseHeader();
void igMetaField_SetFieldName(igMetaField *, void **);
/* The shared string pool, created on first use. */
extern int g_stringPool[4];
int memcpy(int, int, unsigned short);

/* 0x002fc2c0 */
void igMetaField_Configure(igMetaField *self, int fieldName, int externalEnumStorage, int offset, int parentMetaObject) {
    void *internedName;
    int *chunkHeader;
    int refCount;
    int pool;
    void *name;

    /* A null name stays null; otherwise it is interned in the shared pool. */
    if (fieldName == 0) {
        name = 0;
    } else {
        if (g_stringPool[0] == 0) {
            /* Lazily build the pool: FUN_002eb010 allocates 0x10 bytes. */
            pool = FUN_002eb010(0x10);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            g_stringPool[0] = pool;
        }
        name = StringPool_Intern(g_stringPool[0], fieldName);
    }
    internedName = name;
    igMetaField_SetFieldName(self, &internedName);
    /* Drop the local reference now that the field holds its own. */
    if (internedName != 0) {
        chunkHeader = (int *)((char *)internedName - 8);
        refCount = *(int *)((char *)internedName - 4) - 1;
        *(int *)((char *)internedName - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader(*chunkHeader, chunkHeader);
        }
    }
    self->_externalEnumStorage = externalEnumStorage;
    self->_offset = offset;
    self->_parentMetaObject = parentMetaObject;
    igMetaField_EnsureDefaultStorage(self);
}

/* 0x002fc440 */
void igMetaField_SetDefault(igMetaField *self, int defaultValue) {
    igMetaField_EnsureDefaultStorage(self);
    if (defaultValue != 0) {
        /* memcpy is memcpy(dst, src, size): copy _size bytes into _default. */
        memcpy(self->_default, defaultValue, (int)self->_size);
    }
}

/* 0x002fc490 */
void igMetaField_SetFieldName(igMetaField *self, void **newName) {
    int *chunkHeader;
    int refCount;
    void *incoming;
    void *previous;

    /* Retain the new name before releasing the old one. */
    incoming = *newName;
    if (incoming != 0) {
        *(int *)((char *)incoming - 4) += 1;
    }
    previous = (void *)self->_fieldName;
    if (previous != 0) {
        chunkHeader = (int *)((char *)previous - 8);
        refCount = *(int *)((char *)previous - 4) - 1;
        *(int *)((char *)previous - 4) = refCount;
        if (refCount == 0) {
            StringChunk_ReleaseHeader(*chunkHeader, chunkHeader);
        }
    }
    self->_fieldName = (int)*newName;
}

/* 0x002fde50 — adds a field to the metaobject's field list, retaining it. */
void igMetaObject_AppendField(igMetaObject *meta, igMetaField *field)
{
    MetaRefList_AppendRetained((void *)meta->_metaFields, field);
}
