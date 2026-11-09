extern "C" {
struct QuadNamed { int w0; int refs; int name; };
struct Quad { float x, y, z, w; };
QuadNamed *FUN_002b9500(int);
int fptodp(float);
int FUN_002eb010(int);
int FUN_0030b7e0(QuadNamed *, int, int, int, int, int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int igObject_Destroy(QuadNamed *);
extern int DAT_004c22f0[16];
extern int DAT_00586f20[16];
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    ~igSmartPointer() {
        T *object = p;
        if (object != 0) {
            object->refs = object->refs - 1;
            if ((object->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    T *get() const { return p; }
};
struct Tag { };
int FUN_001e6f10(int *result, Quad *quad, int kind) {
    int s3, s2, s1;
    int name;
    int res;
    int obj;
    Tag tag = Tag();
    igSmartPointer<QuadNamed> named(FUN_002b9500(0));
    s3 = fptodp(quad->x);
    s2 = fptodp(quad->y);
    s1 = fptodp(quad->z);
    FUN_0030b7e0(named.p, kind, s3, s2, s1, fptodp(quad->w));
    name = named.get()->name;
    if (name == 0) {
        name = DAT_004c22f0[0];
    }
    if (name == 0) {
        res = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            obj = FUN_002eb010(0x10);
            if (obj != 0) {
                obj = StringPool_Construct(obj);
            }
            DAT_00586f20[0] = obj;
        }
        res = StringPool_Intern(DAT_00586f20[0], name);
    }
    *result = res;
    return 0;
}
}
