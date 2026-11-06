/* Reset a name table: call the virtual hook (slot 76) for every index below the count that is not
 * in the exclusion list (bool inline, direct returns), then when requested release the interned
 * name, free the buffers and the table. Loop test written -1 < i. Alternate compiler -O3. */
extern "C" {
int FUN_002eb010(int);
void Memory_FreeBuffer(void *);
void Memory_FreeBufferAliasB(void *);
void StringChunk_ReleaseHeader(void *, int);
int StringPool_Construct(int);
char *StringPool_Intern(int, char *);
extern void *DAT_00560858[4];
extern int DAT_00586f20[4];
}
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((char *)(s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader((void *)h_[0], (int)h_); }
#define POOL() if (!DAT_00586f20[0]) { int p_ = FUN_002eb010(16); if (p_) p_ = StringPool_Construct(p_); DAT_00586f20[0] = p_; }
struct T {
    unsigned short count; unsigned short pad0; unsigned short n; unsigned short pad1; char *str; unsigned short *arr; void *buf;
    bool Wanted(int idx) {
        int j;
        if (idx < count && idx >= 0) {
            for (j = 0; j < n; j++) {
                if (idx == arr[j]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

};
struct Obj {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void f76(int);
    char pad[1332]; struct T *t; int pad2; void *f1344;
};
extern "C" void FUN_00170510(Obj *o, int arg1) {
    int s0;
    T *t;
    char *s1;
    s0 = o->t->count - 1;
    while (-1 < s0) {
        if (o->t->Wanted(s0)) {
            o->f76(s0);
        }
        s0--;
    }
    if (arg1 == 0) {
        t = o->t;
        if (t != 0) {
            POOL();
            s1 = StringPool_Intern(DAT_00586f20[0], 0);
            STR_RELEASE(t->str);
            t->str = s1;
            Memory_FreeBuffer(t->buf);
            Memory_FreeBuffer(t->arr);
            if (&t->str != 0) {
                STR_RELEASE(t->str);
            }
            Memory_FreeBufferAliasB(t);
        }
        o->t = 0;
        Memory_FreeBuffer(DAT_00560858[0]);
        if (o->f1344 != 0) {
            Memory_FreeBufferAliasB(o->f1344);
        }
    }
}
