struct EventQueryResult { int w0; EventQueryResult() {} EventQueryResult(int v) { w0 = v; } bool operator!=(const EventQueryResult &o) const { return w0 != o.w0; } };
struct EventRecordInfo { int kind; char pad4[64]; int f68; int f72; int *pending; char pad80[80]; };
struct EventSlotWords { int vt; int rc; int count; int capacity; int *data; };
class EventTrackerLock { public:
    virtual void l0();
    virtual void l1();
    virtual void l2();
    virtual void l3();
    virtual void l4();
    virtual void l5();
    virtual void l6();
    virtual void l7();
    virtual void l8();
    virtual void l9();
    virtual void l10();
    virtual void l11();
    virtual void l12();
    virtual void l13();
    virtual void l14();
    virtual void l15();
    virtual void l16();
    virtual void l17();
    virtual void l18();
    virtual void l19();
    virtual void l20();
    virtual void l21();
    virtual void l22();
    virtual void l23();
    virtual void l24();
    virtual void l25();
    virtual void l26();
    virtual void l27();
    virtual void l28();
    virtual EventQueryResult Unlock();
    virtual void l30();
    virtual EventQueryResult Acquire(int wait);
};
class EventTrackerFilter { public:
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void f18();
    virtual void f19();
    virtual void f20();
    virtual void f21();
    virtual void f22();
    virtual int IsOpen();
};
class EventTrackerQueryView { public:
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
    virtual void Update(EventRecordInfo *info, int mode);
    virtual EventQueryResult Get(int id, EventRecordInfo *info);
    virtual void t26();
    virtual void t27();
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
    virtual EventQueryResult Describe(int id, char *buffer, int size, int *line, int a, int b, int *column);
    int rc; EventTrackerLock *lock; char pad12[72]; EventSlotWords *slots; char pad88[4]; EventTrackerFilter *filter;
};
struct EventTrackerScopedLock {
    EventTrackerLock *l;
    EventTrackerScopedLock(EventTrackerLock *m) { l = m; if (l != 0) { l->Acquire(1); } }
    ~EventTrackerScopedLock() { if (l != 0) { l->Unlock(); } }
};
extern "C" {
void FUN_002e2130(EventRecordInfo *);
void FUN_002e2300(EventRecordInfo *, int);
int strcmp(char *, char *);
int FUN_0012aff0(char *, char *);
extern EventQueryResult DAT_004fb418[2];
extern char DAT_004f98d0[];
void Gap__Core__igEventTracker__vfunc_37(EventTrackerQueryView *self, char *wanted);
}
void Gap__Core__igEventTracker__vfunc_37(EventTrackerQueryView *self, char *wanted) {
    EventTrackerScopedLock guard(self->lock);
    int i; int n = self->slots->count;
    EventRecordInfo info;
    char buffer[256];
    int line;
    int column;
    FUN_002e2130(&info);
    if (self->filter->IsOpen() == 0) {
        FUN_002e2300(&info, -1);
        return;
    }
    for (i = 0; i < n; i++) {
        int id = self->slots->data[i];
        if (id != -1 && self->Get(id, &info) != DAT_004fb418[0] && info.kind != 3) {
            int **pending = &info.pending;
            if (*pending == 0) {
                continue;
            }
            while (**pending != 0) {
                self->Describe(**pending, buffer, 255, &line, 0, 0, &column);
                if (strcmp(buffer, DAT_004f98d0) == 0) {
                    break;
                }
                if (FUN_0012aff0(buffer, wanted) != 0) {
                    info.kind = 3;
                    info.f68 = 0;
                    info.f72 = 0;
                    self->Update(&info, -1);
                }
                *pending = *pending + 1;
            }
        }
    }
    FUN_002e2300(&info, -1);
}
