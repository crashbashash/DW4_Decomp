struct FieldLinkInfo;
class FieldLinkObject { public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12();
    virtual void Prepare();
    virtual void s14(); virtual void s15();
    virtual void Touch();
    virtual void SetPool(int pool);
    virtual void s18(); virtual void s19();
    virtual FieldLinkInfo *GetMeta();
    virtual void Assign(void *value);
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
    virtual void SetContext(int mode);
    virtual void s28();
    virtual int Classify(void *pool);
};
struct FieldLinkInfo { char pad[64]; int (*poolFor)(); };
struct FieldLinkRecord : FieldLinkObject { unsigned int rc; int pad8; int index; int user; int extra; };
struct FieldLinkSet { int vt; int rc; int count; char pad12[44]; char reset; char pad57[7]; unsigned char mode; unsigned char tracks; unsigned char namedPools; };
extern "C" {
int FUN_002d86b0(FieldLinkSet *, int, FieldLinkObject *);
FieldLinkObject *FUN_002d7d60(FieldLinkSet *, int);
int igObject_IsKindOf(void *, int);
void *igObject_GetAllocator(void *);
FieldLinkRecord *FUN_002bd8f0(void *);
void List_InsertWords(FieldLinkSet *, int, int, void *);
void igNamedObject_SetName(FieldLinkRecord *, char *);
char *igMetaObject_GetPoolName(FieldLinkInfo *);
void *Memory_GetAllocatorByName(char *);
FieldLinkObject *Memory_GetCurrentContextAlias(void);
void FUN_00301590(FieldLinkRecord *, FieldLinkInfo *);
void igObject_Destroy(FieldLinkRecord *);
extern int DAT_00586730;
extern int DAT_00586140;
int FUN_002d87b0(FieldLinkSet *self, FieldLinkObject *obj, char *name, int user);
}
template <class T> struct RetainedWord {
    T *p;
    RetainedWord(T *object) : p(object) {
        if (p != 0) {
            p->rc = p->rc + 1;
        }
    }
};
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    ~igSmartPointer() {
        T *o;
        if ((o = p) != 0) {
            o->rc = o->rc - 1;
            if ((o->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    T *get() const { return p; }
};
int FUN_002d87b0(FieldLinkSet *self, FieldLinkObject *obj, char *name, int user) {
    int index = 0;
    FieldLinkInfo *info;
    void *pool;
    int mode;
    if (obj == 0) {
        return -1;
    }
    if (self->count > 0) {
        index = FUN_002d86b0(self, DAT_00586730, obj);
        if (self->count > index && FUN_002d7d60(self, index) == obj) {
            return -1;
        }
    }
    if (obj != 0) {
        obj->Touch();
        if (igObject_IsKindOf(self, DAT_00586140) != 0) {
            if (self->mode == 1) {
                obj->Prepare();
            }
            {
                FieldLinkInfo *m = obj->GetMeta();
                int (*fn)() = m->poolFor;
                if (fn != 0) {
                    self->reset = 0;
                    obj->SetPool(fn());
                }
            }
        }
    }
    igSmartPointer<FieldLinkRecord> record(FUN_002bd8f0(igObject_GetAllocator(self)));
    record.get()->index = index;
    RetainedWord<FieldLinkRecord> inserted(record.get());
    List_InsertWords(self, index, 1, &inserted);
    if (name != 0) {
        igNamedObject_SetName(record.get(), name);
    }
    record.get()->user = user;
    record.get()->extra = 0;
    record.get()->Assign(obj);
    if (self->tracks != 0) {
        info = obj->GetMeta();
        pool = 0;
        if (self->namedPools != 0 && info != 0 && igMetaObject_GetPoolName(info) != 0) {
            pool = Memory_GetAllocatorByName(igMetaObject_GetPoolName(info));
        }
        if (pool == 0) {
            pool = igObject_GetAllocator(obj);
        }
        if (pool != 0) {
            mode = Memory_GetCurrentContextAlias()->Classify(pool);
            if (mode == 1 || mode == 2) {
                mode = -1;
            }
            record.get()->SetContext(mode);
        }
    }
    if (obj != 0) {
        FUN_00301590(record.get(), obj->GetMeta());
    }
    return index;
}
