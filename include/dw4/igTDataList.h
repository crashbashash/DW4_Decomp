#ifndef DW4_IGTDATALIST_H
#define DW4_IGTDATALIST_H

extern "C" int List_Resize(void *, int, int);

template <class T> class igTDataList {
public:
    int _vtable;
    unsigned int _refCount;
    int _count;
    int _capacity;
    T *_data;
    int count() const { return _count; }
    const int &getCount() const { return _count; }
    T get(int index) const { return _data[index]; }
    void set(int index, const T *value) { _data[index] = *value; }
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
    void append(T v) {
        int n = count();
        if (n < _capacity) {
            _count = _count + 1;
        } else {
            List_Resize(this, n + 1, 4);
        }
        const T *p = &v;
        _data[n] = *p;
    }
};

#endif
