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
    int find(T v, int start = 0) const {
        int i;
        int n = _count;
        for (i = start; i < n; i++) {
            const T *p = &v;
            if (*p == _data[i]) return i;
        }
        return -1;
    }
};

#endif
