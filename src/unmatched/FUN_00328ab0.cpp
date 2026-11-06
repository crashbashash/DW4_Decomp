/* Resizes a ring buffer of ints (capacity at +24, count +28, head +32, data +36): allocates,
 * copies the two segments, frees the old data, then asks the object (virtual slot 28) for the new
 * count. C++ for the t9 virtual call (26 dummy slots), the allocator and the free keep arg0 in a0,
 * the head offset is a separate local; default compiler, exceptions off. */
extern "C" {
int memmove(int, int, int);
int FUN_00300f50(void *, int);
int igObject_AllocateStorage(void *, int);
void FUN_00328ab0(struct Q *arg0, int arg1);
}
struct Q {
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
    virtual unsigned getCount();
    int pad[5]; int cap; unsigned cnt; unsigned head; int buf; };
extern "C" void FUN_00328ab0(Q *arg0, int arg1) {
    int s0;
    int s3;
    int off;
    unsigned a2;
    unsigned v0;
    if (arg1 != arg0->cap) {
        s0 = igObject_AllocateStorage(arg0, arg1 * 4);
        a2 = arg0->head;
        v0 = arg0->cnt;
        if (a2 < v0) {
            memmove(s0, arg0->buf + a2 * 4, (v0 - a2) * 4);
        } else {
            s3 = (arg0->cap - a2) * 4;
            off = a2 * 4;
            memmove(s0, arg0->buf + off, s3);
            memmove(s0 + s3, arg0->buf, arg0->cnt * 4);
        }
        FUN_00300f50(arg0, arg0->buf);
        arg0->buf = s0;
        arg0->cnt = arg0->getCount();
        arg0->head = 0;
        arg0->cap = arg1;
    }
}
