struct igBitMaskWords { char pad8[8]; int _count; int _capacity; unsigned int *_data; unsigned int _bitCount;
    inline void setCount(int n);
    inline void setWord(int i, const unsigned int &v);
    inline unsigned int getWord(unsigned int i) { return _data[i]; }
};
extern unsigned int DAT_0048d8d0;
extern "C" {
void List_Resize(igBitMaskWords *, int, int);
void FUN_001b1e50(void *arg, unsigned int bits);
}
inline void igBitMaskWords::setCount(int n) {
    if (n >= 0) {
        if (!(n > _capacity)) {
            _count = n;
        } else {
            List_Resize(this, n, 4);
        }
    }
}
inline void igBitMaskWords::setWord(int i, const unsigned int &v) {
    int n = _count;
    if (n != 0 && i >= 0 && i < n) {
        _data[i] = v;
    }
}
void FUN_001b1e50(void *arg, unsigned int bits) {
    igBitMaskWords *m;
    unsigned int old;
    int partial;
    int i;
    int n;
    m = (igBitMaskWords *)arg;
    old = m->_bitCount;
    if (bits <= old) {
        m->_bitCount = bits;
        m->setCount((bits + 31) >> 5);
    } else {
        i = m->_count;
        partial = old & 31;
        m->_bitCount = bits;
        m->setCount((bits + 31) >> 5);
        if (partial != 0) {
            unsigned int mask = ((1 << partial) - 1) & m->getWord(i - 1);
            m->setWord(i - 1, mask);
        }
        n = m->_count;
        for (; i < n; i++) {
            m->setWord(i, DAT_0048d8d0);
        }
    }
}
