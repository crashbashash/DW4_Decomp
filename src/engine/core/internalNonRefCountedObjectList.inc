namespace Gap {
namespace Core {

__internalNonRefCountedObjectList::__internalNonRefCountedObjectList(bool boot) : igObject(boot)
{
    new (this, 0) __internalNonRefCountedObjectList;
    _data = (igObject **)getMemoryPool()->Allocate(16);
}

__internalNonRefCountedObjectList::__internalNonRefCountedObjectList()
{
    _data = 0;
    _count = 0;
}

__internalNonRefCountedObjectList::__internalNonRefCountedObjectList(const __internalNonRefCountedObjectList &other) : igObject(other)
{
    _count = other._count;
    if (other._data) {
        int size = _count * sizeof(igObject *);

        _data = (igObject **)getMemoryPool()->Allocate(size);
        memcpy(_data, other._data, size);
    } else {
        _data = 0;
    }
}

void __internalNonRefCountedObjectList::__bootstrapDestruct()
{
    if (_data != 0) {
        getMemoryPool()->Free(_data);
    }
    igObject::__bootstrapDestruct();
}
}
}



static inline unsigned int pointerListCapacity(__internalNonRefCountedObjectList *list) {
    return list->_data == 0 ? 0 : Memory_GetBufferSize((void *)list->_data) >> 2;
}

namespace Gap {
namespace Core {

void __internalNonRefCountedObjectList::setCapacity(int capacity)
{
    if (capacity >= getCapacity()) {
        unsigned int old = _data == 0 ? 0 : Memory_GetBufferSize(_data) / sizeof(igObject *);
        unsigned int size = old;

        if (old == 0) {
            size = 4;
        }
        while (!(capacity < (int)size)) {
            if ((int)size < 512) {
                size *= 2;
            } else {
                size += 512;
            }
        }
        _data = (igObject **)realloc(_data, size * sizeof(igObject *));
        char *cleared = (char *)_data;
        cleared += old * sizeof(igObject *);
        memset(cleared, 0, (size - old) * sizeof(igObject *));
    }
}

igObject *__internalNonRefCountedObjectList::search(igStringMetaField *field, const char *name) const
{
    int i;

    for (i = 0; i < _count; i++) {
        if (strcmp(*(const char **)((char *)_data[i] + field->_offset), name) == 0) {
            return _data[i];
        }
    }
    return 0;
}

int __internalNonRefCountedObjectList::find(const igObject *obj) const
{
    igObject **data = _data;
    int count = _count;
    int i;

    for (i = 0; i < count; i++) {
        if (data[i] == obj) {
            return i;
        }
    }
    return -1;
}

void __internalNonRefCountedObjectList::trimCapacity()
{
    int i = _count;

    while (i < getCapacity()) {
        _data[i] = 0;
        i++;
    }
}

void __internalNonRefCountedObjectList::insert(int index, igObject *obj)
{
    int i;
    int count = _count;

    if (count >= getCapacity()) {
        setCapacity(count);
    }
    for (i = _count; i > index; i--) {
        _data[i] = _data[i - 1];
    }
    _data[index] = obj;
    _count++;
}

void __internalNonRefCountedObjectList::setCount(int cnt)
{
    if (cnt >= getCapacity()) {
        setCapacity(cnt);
    }
    _count = cnt;
}

int __internalNonRefCountedObjectList::remove(int index)
{
    int i;

    if (index < _count) {
        for (i = index; i < _count - 1; i++) {
            _data[i] = _data[i + 1];
        }
        _count--;
        return index;
    }
    return -1;
}

int __internalNonRefCountedObjectList::append(igObject *obj)
{
    int count = _count;

    if (count >= getCapacity()) {
        setCapacity(count);
    }
    _data[_count] = obj;
    return _count++;
}

void __internalNonRefCountedObjectList::set(int index, igObject *obj)
{
    if (index >= getCapacity()) {
        setCapacity(index);
    }
    _data[index] = obj;
}
}
}

