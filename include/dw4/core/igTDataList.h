/* reflected.h comes first, outside the guard: it reads this header itself, just before the first converted class
 * deriving from the kit's template, so the template follows its parent igDataList there whichever header a
 * unit names first. */
#include "dw4/support/reflected.h"
#ifndef DW4_IGTDATALIST_H
#define DW4_IGTDATALIST_H

namespace Gap {
namespace Core {

/* The kit's typed list (alchemy-kit_202309 igCore/igTDataList.h): igDataList's storage read as an array of T,
 * with the item size its services take. */
template <class T> class igTDataList : public igDataList {
private:
    typedef igDataList Parent;
    inline T *getArrayInternal() const { return (T *)_data; }
public:
    inline void setCapacityToCount() {
        if (_capacity > _count) {
            Parent::setCapacity(_count, sizeof(T));
        }
    }
    inline void setCount(int newCount) {
        if (!(newCount >= 0)) {
            return;
        }
        if (newCount <= _capacity) {
            _count = newCount;
            return;
        }
        Parent::resizeAndSetCount(newCount, sizeof(T));
    }
    inline const T *getArray() const { return (const T *)_data; }
    inline T &get(int index) const { return getArrayInternal()[index]; }
    inline void set(int index, const T &value) {
        if (!(_count != 0)) {
            return;
        }
        if (!((index >= 0) && (index < _count))) {
            return;
        }
        getArrayInternal()[index] = value;
    }
    inline int find(const T &value, int startIndex) const {
        const int count = _count;
        for (int i = startIndex; i < count; i++) {
            if (value == getArray()[i]) {
                return i;
            }
        }
        return -1;
    }
    inline virtual void trimCapacity() { setCapacityToCount(); }
    inline virtual int getElementSize() const { return sizeof(T); }
};
}
}

/* A typed igDataList: the igObject header, then the count, capacity and element array. */
template <class T> class igTDataList : public igObject {
public:
    int _count;
    int _capacity;
    T *_data;
    int count() const { return _count; }
    int capacity() const { return _capacity; }
    const int &getCount() const { return _count; }
    T get(int index) const { return _data[index]; }
    T &operator[](int index) { return _data[index]; }
    void set(int index, const T *value) { _data[index] = *value; }
    /* the kit's setCount (alchemy-kit_202309 igCore/igTDataList.h), without its negative-count assert */
    void setCount(int newCount) {
        if (newCount <= _capacity) {
            _count = newCount;
            return;
        }
        ((Gap::Core::igDataList *)this)->resizeAndSetCount(newCount, sizeof(T));
    }
    int find(T v, int start = 0) const {
        int i;
        int n = _count;
        for (i = start; i < n; i++) {
            const T *p = &v;
            if (*p == _data[i]) return i;
        }
        return -1;
    }
    int sortedFind(const T *item) const {
        /* matching construct: declaration-order search — the order of these locals */
        int lo;
        int hi;
        T key;
        int n;
        int mid;
        const T *p;
        T e;
        T value;
        value = *item;
        p = &value;
        lo = 0;
        n = _count;
        key = *p;
        hi = n - 1;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            e = _data[mid];
            if (e < key) {
                lo = mid + 1;
            } else if (key < e) {
                hi = mid - 1;
            } else {
                return mid;
            }
        }
        if (n == 0) {
            return -1;
        }
        e = _data[lo];
        if (value < e || e < value) {
            return -1;
        }
        return lo;
    }
    /* sortedFind for a key passed by reference: the key is copied into a local whose address is
     * taken, so a by-value argument stays in its own stack slot, read before the loop and again
     * after it (Gap::igItemInterface::vfunc_29). */
    int sortedIndex(const T &item) const {
        T value;
        int lo;
        int hi;
        T key;
        int n;
        int mid;
        const T *p;
        T e;
        value = item;
        p = &value;
        lo = 0;
        n = _count;
        key = *p;
        hi = n - 1;
        while (lo < hi) {
            mid = (lo + hi) >> 1;
            e = _data[mid];
            if (e < key) {
                lo = mid + 1;
            } else if (key < e) {
                hi = mid - 1;
            } else {
                return mid;
            }
        }
        if (n == 0) {
            return -1;
        }
        e = _data[lo];
        if (value < e || e < value) {
            return -1;
        }
        return lo;
    }
    void append(T v) {
        int n = count();
        if (n < _capacity) {
            _count = _count + 1;
        } else {
            ((Gap::Core::igDataList *)this)->resizeAndSetCount(n + 1, sizeof(T));
        }
        const T *p = &v;
        _data[n] = *p;
    }
};

#endif
