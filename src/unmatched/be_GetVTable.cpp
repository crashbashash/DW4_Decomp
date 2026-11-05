extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int StringChunk_ReleaseHeader(...);
extern int DAT_00539f10[4];
extern int DAT_00524950[4];
extern void * DAT_00586dc8[4];
}
struct Obj {
    int *vt; int w0[1]; char *s; int w3; T *ref; char tail[12];
    inline void releaseRef() {
        T **self = &ref;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
    inline void releaseStr() {
        char **self = &s;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
};
extern "C" int igObject_InitHeader(Obj *);
extern "C" int be_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.s = 0;
    obj.vt = &DAT_00539f10[0];
    obj.ref = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00539f10[0];
    obj.releaseRef();
    obj.vt = &DAT_00524950[0];
    obj.releaseStr();
    return r;
}
