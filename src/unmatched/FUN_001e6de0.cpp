extern "C" {
typedef struct FormattedObject { int w0; int refs; int f8; } FormattedObject;
typedef struct Vector3f { float x, y, z; } Vector3f;
FormattedObject *FUN_002b9500(int);
int fptodp(float);
int FUN_002eb010(int);
int FUN_0030b7e0(FormattedObject *, int, int, int, int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int igObject_Destroy(FormattedObject *);
extern int DAT_004c22f0[16];
extern int DAT_00586f20[16];
}
struct AdoptReference { };
struct FormattedRef {
    FormattedObject *p;
    FormattedRef(FormattedObject *object, AdoptReference) : p(object) {}
    ~FormattedRef() {
        FormattedObject *object = p;
        if (object != 0) {
            object->refs = object->refs - 1;
            if ((object->refs & 0x7FFFFF) == 0) igObject_Destroy(object);
        }
    }
};
struct InternedText {
    int text;
    InternedText(int name) {
        int interned;
        if (name == 0) {
            name = DAT_004c22f0[0];
        }
        if (name == 0) {
            interned = 0;
        } else {
            if (DAT_00586f20[0] == 0) {
                int pool = FUN_002eb010(0x10);
                if (pool != 0) {
                    pool = StringPool_Construct(pool);
                }
                DAT_00586f20[0] = pool;
            }
            interned = StringPool_Intern(DAT_00586f20[0], name);
        }
        text = interned;
    }
};
extern "C" InternedText FUN_001e6de0(Vector3f *value, int format) {
    FormattedRef formatted(FUN_002b9500(0), AdoptReference());
    int x = fptodp(value->x);
    int y = fptodp(value->y);
    FUN_0030b7e0(formatted.p, format, x, y, fptodp(value->z));
    return InternedText(formatted.p->f8);
}
