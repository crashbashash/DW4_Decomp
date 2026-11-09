struct IniValueObject { int pad0; int _refCount; union { int i; float f; unsigned char b; char *s; } value; };
struct IniValueList;
struct IniValueTarget;
extern "C" {
void *igObject_GetAllocator(void *);
IniValueObject *FUN_002b9500(void *);
int FUN_00303e50(IniValueList *);
IniValueObject *FUN_00303e60(IniValueList *, int);
int FUN_00303e80(IniValueList *, int);
void *FUN_001e4e30();
void *FUN_001e4fc0();
void *FUN_001e5c50();
int igObject_IsKindOf(void *, void *);
void FUN_0030b720(IniValueObject *, int, void *);
void FUN_0030b730(IniValueObject *, void *, float);
void FUN_0030b770(IniValueObject *, unsigned char, int);
void FUN_002d9740(IniValueTarget *, int, int, char *);
void igObject_Destroy(void *);
extern char *DAT_004c22f0[4];
extern int DAT_004e4710[2];
extern int DAT_004e4718[2];
}
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    ~igSmartPointer() {
        T *o;
        if ((o = p) != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
};
extern "C" void FUN_001cb010(void *self, IniValueTarget *target, IniValueList *list) {
    int i;
    IniValueObject *value;
    char *s;
    igSmartPointer<IniValueObject> text(FUN_002b9500(igObject_GetAllocator(self)));
    for (i = 0; i < FUN_00303e50(list); i++) {
        value = FUN_00303e60(list, i);
        if (igObject_IsKindOf(value, FUN_001e4e30()) != 0) {
            FUN_0030b720(text.p, value->value.i, DAT_004e4710);
            s = text.p->value.s;
            s = (s == 0) ? DAT_004c22f0[0] : s;
            FUN_002d9740(target, 10, FUN_00303e80(list, i), s);
        } else if (igObject_IsKindOf(value, FUN_001e4fc0()) != 0) {
            FUN_0030b730(text.p, DAT_004e4718, value->value.f);
            s = text.p->value.s;
            s = (s == 0) ? DAT_004c22f0[0] : s;
            FUN_002d9740(target, 11, FUN_00303e80(list, i), s);
        } else if (igObject_IsKindOf(value, FUN_001e5c50()) != 0) {
            FUN_0030b770(text.p, value->value.b, 0);
            s = text.p->value.s;
            s = (s == 0) ? DAT_004c22f0[0] : s;
            FUN_002d9740(target, 12, FUN_00303e80(list, i), s);
        }
    }
}
