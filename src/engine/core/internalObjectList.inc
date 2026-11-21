namespace Gap {
namespace Core {

__internalObjectList::__internalObjectList(bool boot) : __internalNonRefCountedObjectList(boot)
{
}

__internalObjectList::__internalObjectList()
{
}

__internalObjectList::__internalObjectList(const __internalObjectList &other) : __internalNonRefCountedObjectList(other)
{
}

void __internalObjectList::__bootstrapDestruct()
{
    setCount(0);
    __internalNonRefCountedObjectList::__bootstrapDestruct();
}

void __internalObjectList::insert(int index, igObject *obj)
{
    igObject::ref(obj);
    __internalNonRefCountedObjectList::insert(index, obj);
}

void __internalObjectList::setCount(int cnt)
{
    int i = _count;

    if (cnt < i) {
        i--;
        while (i >= cnt) {
            igObject::release(_data[i]);
            i--;
        }
    }
    __internalNonRefCountedObjectList::setCount(cnt);
}

int __internalObjectList::append(igObject *obj)
{
    igObject::ref(obj);
    return __internalNonRefCountedObjectList::append(obj);
}

void __internalObjectList::set(int index, igObject *obj)
{
    igObject::ref(obj);
    igObject::release(_data[index]);
    __internalNonRefCountedObjectList::set(index, obj);
}
}
}

