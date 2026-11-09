struct R { int w0; R() {} R(const R &o) { w0 = o.w0; } bool operator==(const R &o) const { return w0 == o.w0; } };
extern "C" int igObject_Destroy(...);
struct T {
    int w0;
    int refs;
    void release() {
        refs = refs - 1;
        if ((refs & 0x7FFFFF) == 0) {
            igObject_Destroy(this);
        }
    }
};
struct C { char p0[80]; int f80; int f84; char p88[12]; int f100; char p104[64]; unsigned char f168; char p169[23]; int f192; char p196[20]; int f216; char p220[40]; int f260; int f264; char p268[12]; int f280; };
extern "C" {
int FUN_002e3a10(...);
R FUN_002e7030(C *);
int FUN_002fff90(T*, int*, C*, int, unsigned char);
int FUN_00300250(T*, int*, C*, int, unsigned char);
int igObject_IsKindOf(...);
int igObject_RegisterInstance(...);
extern R DAT_004fb418[2];
extern int DAT_00586710[4];
}
class MF {
public:
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
  virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
  virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
  virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
  virtual int vX(int *, int);
};
extern "C" {
void *igIntMetaField_GetDefaultDescriptor(...);
void *igMetaObject_CreateInstanceWithPool(...);
}
static inline T *castToKind(T *object) {
    if (object != 0 && igObject_IsKindOf(object, DAT_00586710[0]) != 0) {
        return object;
    }
    return 0;
}
struct TRef {
    T *p;
    TRef(T *object) : p(object) {
        if (p != 0) {
            p->refs = p->refs + 1;
        }
    }
    ~TRef() {
        T *object = p;
        if (object != 0) {
            object->refs = object->refs - 1;
            if ((object->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    T *operator->() const { return p; }
};
extern "C" int igIGBFile_ReadObject(T **out, C *file) {
    int metaIndex;
    int *record;
    int end = file->f264 + file->f80;
    int position = file->f80;
    int t0;
    if (position > file->f260 - 9 || (t0 = file->f216 * 4 + (file->f80 + FUN_002e3a10(file, end)), file->f260 < t0)) {
        if (FUN_002e7030(file) == DAT_004fb418[0]) {
            *out = 0;
            T *null = *out;
            if (null != 0) {
                null->refs = null->refs + 1;
            }
            return;
        }
    }
    record = (int *)((char *)file->f264 + file->f80);
    metaIndex = *record;
    if (file->f168 != 0) {
        ((MF *)igIntMetaField_GetDefaultDescriptor())->vX(&metaIndex, 1);
    }
    TRef object(castToKind((T *)igMetaObject_CreateInstanceWithPool(*(int *)(*(int *)((char *)file->f192 + 16) + metaIndex * 4), file->f280)));
    object->release();
    igObject_RegisterInstance(object.p, 0);
    int read;
    if (file->f100 < 4) {
        read = FUN_002fff90(object.p, record, file, file->f192, file->f168);
    } else {
        read = FUN_00300250(object.p, record, file, file->f192, file->f168);
    }
    file->f80 = file->f80 + read;
    file->f84 = file->f84 + read;
    file->f80 = file->f80 + file->f216 * 4;
    file->f84 = file->f84 + file->f216 * 4;
    *out = object.p;
    T *retained = *out;
    if (retained != 0) {
        retained->refs = retained->refs + 1;
    }
    return 0;
}
