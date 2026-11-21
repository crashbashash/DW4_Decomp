/* not-found status */

namespace Gap {
namespace Core {

igResult igMetaEnum::getEnumValue(const char *enumName, igEnum &value) const
{
    int index;
    int match;
    int count;

    if (_names) {
        count = _names->_count;
        for (index = 0; index < count; ++index) {
            {
                igStringRef retained = StringList_CopyRetained(_names, index);
                match = strcmp(retained.p, enumName) == 0;
            }
            if (match) {
                value = _values->get(index);
                return g_resultSuccess;
            }
        }
    }
    return g_resultFailure;
}

igStringRef igMetaEnum::getEnumName(igEnum enumValue) const
{
    int i;
    int n;
    igStringRefList *names = _names;

    if (names != 0) {
        n = _values->getCount();
        i = 0;
        goto test;
body:
        if (enumValue == _values->get(i)) {
            return StringList_CopyRetained(names, i);
        }
        i++;
test:
        if (i < n) goto body;
    }
    return igStringRef();
}

/* The number of names: the `_count` of the `_names` list. */

int igMetaEnum::getEnumCount() const
{
    return _names->_count;
}

igStringRef igMetaEnum::getIndexedEnumName(int index) const
{
    igStringRefList *names = _names;

    if ((names != 0) && (index >= 0) && (index < names->_count)) {
        return StringList_CopyRetained(names, index);
    }
    return igStringRef();
}

igEnum igMetaEnum::getIndexedEnumValue(int index) const
{
    igIntList *values = _values;

    if (values != 0) {
        if ((index >= 0) && (index < values->getCount())) {
            return values->get(index);
        }
    }
    return 0;
}
}
}

static inline int enumStringPool(void) {
    if ((g_stringPool) == 0) {
        int p = ((int)StringPool_Allocate(0x10));
        if (p != 0) { p = ((int)StringPool_Construct((StringPool *)p)); }
        g_stringPool = (StringPool *)p;
    }
    return (int)g_stringPool;
}

static inline void dropEnumNames(igTDataList<char *> *o) {
    IG_OBJECT_RELEASE(o);
}

static inline void dropValues(igTDataList<int> *o) {
    IG_OBJECT_RELEASE(o);
}

static inline void setValue(igTDataList<int> *l, int i, int *v) { if (l->_count != 0 && i >= 0 && i < l->_count) { l->_data[i] = *v; } }

namespace Gap {
namespace Core {

igMetaEnum *igMetaEnum::createMetaEnum(const char *name, const char **names, igEnum *values, int count) {
    MetaEnumView *metaEnum;
    int i;
    char *interned;
    const char *entry;
    char *held;
    char *old;
    ::igTDataList<char *> *nameList;
    ::igTDataList<int> *valueList;
    int pool;
    char **slot;
    metaEnum = ((MetaEnumView *)_instantiateFromPool((igMemoryPoolView *)((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))));
    interned = ((char *)StringPool_Intern((StringPool *)(enumStringPool()), (const char *)name));
    old = metaEnum->name;
    releaseString(old);
    metaEnum->name = interned;
    pool = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    dropEnumNames(metaEnum->names);
    metaEnum->names = ((::igTDataList<char *> *)igStringRefList_Create(pool));
    StringList_Resize(metaEnum->names, count);
    pool = ((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    dropValues(metaEnum->values);
    metaEnum->values = ((::igTDataList<int> *)igIntList_Create(pool));
    valueList = metaEnum->values;
    if (count >= 0) {
        if (!(count > valueList->_capacity)) {
            valueList->_count = count;
        } else {
            ((Gap::Core::igDataList *)valueList)->resizeAndSetCount(count, 4);
        }
    }
    for (i = 0; i < count; i++) {
        entry = names[i];
        if (entry == 0) {
            interned = 0;
        } else {
            interned = ((char *)StringPool_Intern((StringPool *)(enumStringPool()), (const char *)entry));
        }
        *(char **)&held = interned;
        nameList = metaEnum->names;
        if (nameList->_count != 0 && i >= 0 && i < nameList->_count) {
            slot = &nameList->_data[i];
            if (held != 0) { ((int *)held)[-1] = ((int *)held)[-1] + 1; }
            old = *slot;
            releaseString(old);
            *slot = held;
        }
        releaseString(held);
        setValue(metaEnum->values, i, &values[i]);
    }
    igObjectSystem_AppendMetaEnum((int *)(((*(int *)&g_objectSystem))), (int)metaEnum);
    metaEnum->_refCount = metaEnum->_refCount - 1;
    if (((unsigned long long)((long long)metaEnum->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy((::igObject *)metaEnum); }
    return (igMetaEnum *)metaEnum;
}
}
}

