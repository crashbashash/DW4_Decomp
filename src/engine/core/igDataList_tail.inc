namespace Gap {
namespace Core {

int igDataList::getElementSize() const
{
    return -1;
}

void igDataList::setCapacity(int newCapacity, unsigned int itemSize)
{
    int allocResult;
    if (newCapacity == 0) {
        free(_data);
        _data = 0;
    } else {
        unsigned char *oldData = _data;
        ::igMemoryRefMetaField *field =
            (::igMemoryRefMetaField *)igMetaObject_GetFieldAt(getMeta(), k_data->_internalIndex);
        unsigned int elementCount = newCapacity * itemSize / ((igMetaField *)field->_memType)->computeSize();
        igMetaField_AllocateArray(&allocResult, field, this, elementCount, getMemoryPool());
        if (oldData != 0) {
            int oldCapacity = _capacity;
            int copyCount = (oldCapacity < newCapacity) ? oldCapacity : newCapacity;
            memcpy(_data, oldData, copyCount * itemSize);
            free(oldData);
        }
    }
    _capacity = newCapacity;
}

void igDataList::resizeAndSetCount(int newCount, unsigned int itemSize)
{
    int capacity = _capacity > 4 ? _capacity : 4;
    while (capacity < newCount) {
        capacity = capacity < 1024 ? capacity * 2 : capacity + 1024;
    }
    setCapacity(capacity, itemSize);
    _count = newCount;
}

void igDataList::insert(int pos, int numItems, const unsigned char *items, unsigned int itemSize)
{
    int oldCount;
    int newCount;
    unsigned char *at;
    unsigned char *dst;
    int tail;
    if (pos < 0 || pos > getCount()) {
        return;
    }
    if (numItems >= 0 && numItems != 0) {
        oldCount = _count;
        newCount = oldCount + numItems;
        if (newCount <= _capacity) {
            _count = newCount;
        } else {
            resizeAndSetCount(newCount, itemSize);
        }
        at = _data + pos * itemSize;
        numItems *= itemSize;
        dst = at + numItems;
        tail = oldCount - pos;
        if (tail != 0) {
            memmove(dst, at, tail * itemSize);
        }
        memcpy(at, items, numItems);
    }
}

void igDataList::append(int numitems, const unsigned char *items, unsigned int itemSize)
{
    int oldCount;
    int newCount;
    if (numitems >= 0 && numitems != 0) {
        oldCount = _count;
        newCount = oldCount + numitems;
        if (newCount <= _capacity) {
            _count = newCount;
        } else {
            resizeAndSetCount(newCount, itemSize);
        }
        memcpy(_data + oldCount * itemSize, items, numitems * itemSize);
    }
}

void igDataList::remove(int pos, unsigned int itemSize)
{
    int count = _count;
    unsigned char *at;
    if (count <= 0 || pos < 0 || pos >= count) {
        return;
    }
    if (pos != count - 1) {
        at = _data + pos * itemSize;
        memmove(at, at + itemSize, itemSize * (count - (pos + 1)));
    }
    _count = _count - 1;
}

int igDataList::sortedFind(const unsigned char *item, igCompareFunction *compare, unsigned int itemSize) const
{
    int left = 0;
    int right = _count - 1;
    int middle;
    int order;
    while (left < right) {
        middle = (left + right) >> 1;
        order = compare(_data + itemSize * middle, item);
        if (order < 0) {
            left = middle + 1;
        } else if (order > 0) {
            right = middle - 1;
        } else {
            return middle;
        }
    }
    if (_count == 0) {
        return -1;
    }
    if (compare(_data + itemSize * left, item) == 0) {
        return left;
    }
    return -1;
}

void igDataList::resizeAndSetCount4For1(int value)
{
    int index = _count;
    resizeAndSetCount(index + 1, 4);
    ((int *)_data)[index] = value;
}

void igDataList::insert4(int pos, int numItems, const unsigned char *items)
{
    int oldCount;
    int newCount;
    unsigned char *at;
    unsigned char *dst;
    int tail;
    if (pos < 0 || pos > getCount()) {
        return;
    }
    if (numItems >= 0 && numItems != 0) {
        oldCount = _count;
        newCount = oldCount + numItems;
        if (newCount <= _capacity) {
            _count = newCount;
        } else {
            resizeAndSetCount(newCount, 4);
        }
        at = _data + pos * 4;
        numItems *= 4;
        dst = at + numItems;
        tail = oldCount - pos;
        if (tail != 0) {
            memmove(dst, at, tail * 4);
        }
        memcpy(at, items, numItems);
    }
}

void igDataList::append4(int numitems, const unsigned char *items)
{
    int oldCount;
    int newCount;
    if (numitems >= 0 && numitems != 0) {
        oldCount = _count;
        newCount = oldCount + numitems;
        if (newCount <= _capacity) {
            _count = newCount;
        } else {
            resizeAndSetCount(newCount, 4);
        }
        memcpy(_data + oldCount * 4, items, numitems * 4);
    }
}

void igDataList::remove4(int pos)
{
    int count = _count;
    unsigned char *at;
    if (count <= 0 || pos < 0 || pos >= count) {
        return;
    }
    if (pos != count - 1) {
        at = _data + pos * 4;
        memmove(at, at + 4, 4 * (count - (pos + 1)));
    }
    _count = _count - 1;
}

int igDataList::sortedFind4(const unsigned char *item, igCompareFunction *compare) const
{
    int left = 0;
    int right = _count - 1;
    int middle;
    int order;
    while (left < right) {
        middle = (left + right) >> 1;
        order = compare(_data + middle * 4, item);
        if (order < 0) {
            left = middle + 1;
        } else if (order > 0) {
            right = middle - 1;
        } else {
            return middle;
        }
    }
    if (_count == 0) {
        return -1;
    }
    if (compare(_data + left * 4, item) == 0) {
        return left;
    }
    return -1;
}

int igDataList::binaryInsert4(const unsigned char *item, igCompareFunction *compare) const
{
    int left = 0;
    int right = _count - 1;
    int middle;
    int order;
    while (left < right) {
        middle = (left + right) >> 1;
        order = compare((int *)_data + middle, item);
        if (order < 0) {
            left = middle + 1;
        } else if (order > 0) {
            right = middle - 1;
        } else {
            return middle;
        }
    }
    if (_count == 0) {
        return 0;
    }
    if (compare((int *)_data + left, item) < 0) {
        left++;
    }
    return left;
}
}
}
