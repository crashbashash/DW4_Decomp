static inline void sortRetain(Gap::Core::igObject *o) { if (o != 0) { o->ref(); } }

static inline void sortRelease(Gap::Core::igObject *o) {
    if (o != 0) {
        o->release();
    }
}

static inline void sortSetAt(Gap::Core::igObjectList *l, int i, Gap::Core::igObject *v, int off) {
    int n = l->_count;
    if (n != 0 && i >= 0 && i < n) {
        *(Gap::Core::igObject **)((char *)l->_data + off) = v;
    }
}

static inline void setPrev(Gap::Core::igObjectList *l, int i, Gap::Core::igObject *v, int off) {
    int n = l->_count;
    if (n != 0 && i >= 0 && i < n) {
        ((Gap::Core::igObject **)((char *)l->_data + off))[-1] = v;
    }
}

namespace Gap {
namespace Core {

void igObjectList::setAll(igObject *object)
{
    int n;
    int i;
    int j;
    int cnt;
    igObject **data;
    int k;
    igObject *t;

    n = _count;
    if (object != 0) {
        for (i = 0; i < n; i++) {
            object->ref();
        }
    }
    for (j = 0; j < n; j++) {
        t = get(j);
        igObject::release(t);
    }
    cnt = _count;
    data = (igObject **)_data;
    for (k = 0; k < cnt; k++) {
        data[k] = object;
    }
}

void igObjectList::clearAll()
{
    int n;
    int i;
    igObject *o;

    n = _count;
    for (i = 0; i < n; i++) {
        o = get(i);
        igObject::release(o);
    }
    if (_count != 0) {
        memset(_data, 0, _count * sizeof(igObject *));
    }
}

void igObjectList::append(igObject *object)
{
    int count;

    igObject::ref(object);
    count = _count;
    if (count < _capacity) {
        _count = count + 1;
        get(count) = object;
        return;
    }
    resizeAndSetCount4For1((int)object);
}

void igObjectList::concatenate(const igObjectList *list)
{
    igObject *const *data = list->getArray();
    int count = list->_count;
    int i;
    igObject *object;

    for (i = 0; i < count; i++) {
        object = data[i];
        igObject::ref(object);
    }
    append4(list->_count, list->_data);
}

void igObjectList::setCount(int newCount)
{
    int n;
    int j;
    int k;
    igObject *t;

    n = _count;
    if (newCount <= n) {
        for (j = newCount; j < n; j++) {
            t = get(j);
            igObject::release(t);
        }
        for (k = newCount; k < n; k++) {
            get(k) = 0;
        }
        _count = newCount;
        return;
    }
    if (newCount >= 0) {
        if (newCount <= _capacity) {
            _count = newCount;
        } else {
            resizeAndSetCount(newCount, sizeof(igObject *));
        }
    }
    memset(_data + n * sizeof(igObject *), 0, (newCount - n) * sizeof(igObject *));
}

igResult igObjectList::removeByValue(const igObject *obj, int startIndex)
{
    int i = find(obj, startIndex);

    if (i >= 0) {
        igObject *o = get(i);
        unsigned int k = i;
        igObject::release(o);
        remove4(k);
        get(_count) = 0;
        return g_resultSuccess;
    }
    return g_resultFailure;
}

int igObjectList::removeAllByValue(const igObject *obj, int startIndex)
{
    int removed = 0;
    int i = find(obj, startIndex);

    while (i >= 0) {
        igObject *element = get(i);
        igObject::release(element);
        remove4(i);
        get(_count) = 0;
        removed++;
        i = find(obj, i);
    }
    return removed;
}

int igObjectList::appendUnique(igObject *obj)
{
    int index = find(obj, 0);

    if (index == -1) {
        index = getCount();
        append(obj);
    }
    return index;
}

igObject *igObjectList::search(igStringMetaField *field, const char *name) const
{
    const char *text;
    int i;
    int count;
    igObject *item;

    if ((field == 0) || (name == 0)) {
        return 0;
    }
    count = _count;
    for (i = 0; i < count; i++) {
        item = get(i);
        text = *(const char **)((char *)item + field->_offset);
        if ((text != 0) && (strcmp(text, name) == 0)) {
            return item;
        }
    }
    return 0;
}

igObject *igObjectList::search(igObjectRefMetaField *field, const igObject *obj) const
{
    igObject *item;
    int i;
    int n;

    n = _count;
    if (field == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        item = get(i);
        if (item != 0) {
            if (*(const igObject **)((char *)item + field->_offset) == obj) {
                return item;
            }
        }
    }
    return 0;
}

igObject *igObjectList::sortedSearch(const igRefMetaField *field, const void *val) const
{
    int index;
    igObject *item;

    if (field == 0) {
        return 0;
    }
    index = fastBinaryFind(field, val);
    if (index >= _count) {
        return 0;
    }
    item = get(index);
    if (*(const void **)((char *)item + field->_offset) != val) {
        return 0;
    }
    return item;
}

int igObjectList::fastBinaryFind(const igRefMetaField *field, const void *val) const
{
    int n;
    int lo;
    int hi;
    int mid;
    const void *key;
    igObject *item;

    if (field == 0) {
        return -1;
    }
    n = _count;
    if (n <= 0) {
        return 0;
    }
    hi = n - 1;
    lo = 0;
    while (lo < hi) {
        mid = (lo + hi) >> 1;
        item = get(mid);
        key = *(const void **)((char *)item + field->_offset);
        if (key < val) {
            lo = mid + 1;
        } else if (val < key) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    item = get(lo);
    if (*(const void **)((char *)item + field->_offset) < val) {
        return lo + 1;
    }
    return lo;
}

void igObjectList::bubbleSort(igRefMetaField *field)
{
    int i;
    int n;
    igObject *a;
    igObject *b;
    int off;
    int swapped;
    const void *prev;
    const void *cur;
    igObject **p;

    if (field == 0) {
        return;
    }
    n = _count;
    swapped = 1;
    if (n < 2) {
        return;
    }
    while (swapped > 0) {
        swapped = 0;
        prev = *(const void **)((char *)get(0) + field->_offset);
        for (i = 1; i < n; i++) {
            off = i * 4;
            p = (igObject **)(_data + off);
            b = p[0];
            cur = *(const void **)((char *)b + field->_offset);
            if (cur < prev) {
                a = p[-1];
                sortRetain(a);
                sortRelease(*(igObject **)(_data + off));
                sortSetAt(this, i, a, off);
                sortRetain(b);
                sortRelease(*(igObject **)(_data + off - 4));
                setPrev(this, i - 1, b, off);
                swapped = 1;
            }
            prev = cur;
        }
    }
}
}
}
