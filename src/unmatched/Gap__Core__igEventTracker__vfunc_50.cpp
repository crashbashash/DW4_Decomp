struct EventLookupResult { int w0; bool operator==(const EventLookupResult &o) const { return w0 == o.w0; } };
struct EventSlotList { int vt; int rc; int count; int capacity; int *data; };
struct EventByteStream { int vt; int rc; int count; int capacity; char *data; };
class EventTrackerSlots { public:
    virtual void t0();
    virtual void t1();
    virtual void t2();
    virtual void t3();
    virtual void t4();
    virtual void t5();
    virtual void t6();
    virtual void t7();
    virtual void t8();
    virtual void t9();
    virtual void t10();
    virtual void t11();
    virtual void t12();
    virtual void t13();
    virtual void t14();
    virtual void t15();
    virtual void t16();
    virtual void t17();
    virtual void t18();
    virtual void t19();
    virtual void t20();
    virtual void t21();
    virtual void t22();
    virtual void t23();
    virtual void t24();
    virtual void t25();
    virtual void t26();
    virtual EventLookupResult Lookup(int offset, int *out);
    virtual void t28();
    virtual void t29();
    virtual void t30();
    virtual void t31();
    virtual void t32();
    virtual void t33();
    virtual void t34();
    virtual void t35();
    virtual void t36();
    virtual void t37();
    virtual void t38();
    virtual void t39();
    virtual void t40();
    virtual void t41();
    virtual void t42();
    virtual void t43();
    virtual void t44();
    virtual void t45();
    virtual void t46();
    virtual void Bind(int value, int offset);
    char pad[76]; EventByteStream *bytes; EventSlotList *slots;
};
extern "C" {
void FUN_002dcc40(EventTrackerSlots *);
void List_Reserve(EventSlotList *, int, int);
void List_Resize(EventSlotList *, int, int);
extern int DAT_004c2120[4];
extern EventLookupResult DAT_004fb410[2];
void Gap__Core__igEventTracker__vfunc_50(EventTrackerSlots *self, int n);
}
static inline void setCount(EventSlotList *l, int n) {
    if (n >= 0) {
        if (n <= l->capacity) {
            l->count = n;
        } else {
            List_Resize(l, n, 4);
        }
    }
}
void Gap__Core__igEventTracker__vfunc_50(EventTrackerSlots *self, int n) {
    char *base;
    int value;
    char *end;
    char *p;
    int len;
    int offset;
    FUN_002dcc40(self);
    if (n >= self->slots->count) {
        List_Reserve(self->slots, n, 4);
    }
    setCount(self->slots, n);
    {
        int count = self->slots->count;
        int *data = self->slots->data;
        int i;
        for (i = 0; i < count; i++) {
            data[i] = DAT_004c2120[0];
        }
    }
    base = self->bytes->data;
    p = base;
    end = base + self->bytes->count;
    while (p < end) {
        offset = p - base;
        len = p[1];
        p += 2;
        if (self->Lookup(offset, &value) == DAT_004fb410[0]) {
            self->Bind(value, offset);
        }
        p += len;
    }
}
