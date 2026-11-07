struct igResult { int w0; bool operator==(const igResult &o) const { return w0 == o.w0; } };
extern "C" {
extern igResult DAT_004fb410;
int Memory_FreeBuffer(...);
}
class Iter { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual igResult vNext(int *, int); };
struct Args { igResult (*fn)(int); Iter *it; };
extern "C" int FUN_00304e60(Args *args) {
    int key;
    Iter *it;
    igResult (*fn)(int);

    it = args->it;
    fn = args->fn;
    Memory_FreeBuffer();
    for (it->vNext(&key, 1); fn(key) == DAT_004fb410; it->vNext(&key, 1)) {
    }
    return 0;
}
