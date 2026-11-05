extern "C" {
int Memory_FreeBuffer(...);
void *FUN_00300e50(void *, void *, int);
void memset(void *, int, int);
unsigned int Memory_GetBufferSize(void *);
}
struct List {
    char pad[8]; char *data;
    inline unsigned int Cap() {
        return data == 0 ? 0 : Memory_GetBufferSize(data) >> 2;
    }
};
extern "C" void ObjectPointerList_EnsureIndex(List *arg0, int arg1) {
    if (arg1 >= (int)arg0->Cap()) {
        unsigned int old = arg0->Cap();
        unsigned int n = old;
        if (old == 0) {
            n = 4;
        }
        while (!(arg1 < (int)n)) {
            if ((int)n < 512) n *= 2; else n += 512;
        }
        arg0->data = (char *)FUN_00300e50(arg0, arg0->data, n * 4);
        char *p = arg0->data;
        p += old * 4;
        memset(p, 0, (n - old) * 4);
    }
}
