struct RefCountResult { int w0; RefCountResult() {} RefCountResult(const RefCountResult &o) { w0 = o.w0; } };
class RefCountLock { public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void s27();
    virtual void s28();
    virtual RefCountResult Unlock();
    virtual void s30();
    virtual RefCountResult Acquire(int wait);
};
struct RefCountOwnerList { int vt; int rc; int count; int capacity; int *data; };
struct RefCountOwnerHolder { char pad[16]; RefCountOwnerList *list; };
struct RefCountedHandle { char pad[32]; RefCountOwnerHolder *holder; char pad36[16]; int refs; char pad56[12]; RefCountLock *lock; };
struct RefCountObjectHeader { int vt; unsigned int _refCount; };
extern "C" {
void igObject_Destroy(RefCountObjectHeader *);
void List_RemoveWordAt(RefCountOwnerList *, int);
int FUN_002d91c0(RefCountedHandle *self);
}
static inline int findOwner(RefCountOwnerList *list, int owner) {
    volatile int key = owner;
    int n = list->count;
    int value = key;
    int i;
    for (i = 0; i < n; i++) {
        if (value == list->data[i]) {
            return i;
        }
    }
    return -1;
}
int FUN_002d91c0(RefCountedHandle *self) {
    int left;
    if (self->lock == 0) {
        left = self->refs - 1;
        self->refs = left;
    } else {
        self->lock->Acquire(1);
        left = self->refs - 1;
        self->refs = left;
    }
    if (left <= 0) {
        if (self->lock != 0) {
            self->lock->Unlock();
        }
        if (self->holder != 0) {
            RefCountOwnerList *list = self->holder->list;
            int index = findOwner(list, (int)self);
            RefCountObjectHeader *o = (RefCountObjectHeader *)list->data[index];
            if (o != 0) {
                o->_refCount = (int)o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
            List_RemoveWordAt(list, index);
            list->data[list->count] = 0;
        }
    } else {
        if (self->lock != 0) {
            self->lock->Unlock();
        }
    }
    return left;
}
