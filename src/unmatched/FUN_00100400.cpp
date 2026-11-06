/* Array constructor with a partial-array guard object whose inline destructor runs at scope exit. */
typedef void (*Fn)(void *, int);
struct PAD {
    void *ptr; unsigned size; unsigned n; Fn dtor; unsigned i;
    PAD(void *p, unsigned s, unsigned nn, Fn d) {
        ptr = p;
        size = s;
        n = nn;
        dtor = d;
        i = n;
    }
    ~PAD() {
        char *p;
        unsigned k = i;
        if (k < n && dtor != 0) {
            p = (char *)ptr + size * k;
            if (k != 0) {
                do {
                    p -= size;
                    dtor(p, -1);
                    i--;
                } while (i != 0);
            }
        }
    }
};
extern "C" void FUN_00100400(void *ptr, Fn ctor, Fn dtor, unsigned size, unsigned n);
void FUN_00100400(void *ptr, Fn ctor, Fn dtor, unsigned size, unsigned n) {
    char *p;
    PAD pad(ptr, size, n, dtor);
    p = (char *)ptr;
    pad.i = 0;
    if (pad.i < n) {
        do {
            ctor(p, 1);
            pad.i++;
            p += size;
        } while (pad.i < n);
    }
}
