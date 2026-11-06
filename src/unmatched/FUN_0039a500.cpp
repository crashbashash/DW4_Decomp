/* Build one timed record from the request `arg1` (start time, optional duration, two vectors and a
 * kind code classified by its ten-thousands digit) and append it, retained, to the list at
 * arg0->f8. The record is owned by a stack reference until the list has taken its own reference. */
typedef struct R { int w0; int refs; int f8; int f12; float f16; int f20; int f24; float f28; float f32; float f36; float f40; float f44; float f48; float f52; } R;
typedef struct A { char pad[8]; int f8; } A;
typedef struct S { char pad[12]; int f12; float f16; float f20; float f24; float f28; float f32; float f36; float f40; float f44; } S;
extern "C" {
int igObject_GetAllocator(A *);
int Memory_GetAllocatorBySelector(int);
void *FUN_0034f6f0(int);
int ObjectList_AppendRetained(int, R *);
int igObject_Destroy(R *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_0039a500(A *arg0, S *arg1);
}
/* Owning stack reference to the new record: constructed from the object and released on scope exit
 * (reference count in the low 23 bits of refs).  The out-of-line copy the exception table names is the
 * retail body 0x0039a6d0 (config/SLUS-20836/unit-objects.json, duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    R *p;
    ObjectRef(R *o) : p(o) {}
    ~ObjectRef() { R *o = p; if (o != 0) { --o->refs; if ((o->refs & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void FUN_0039a500(A *arg0, S *arg1) {
    int v;
    float f;
    float e;
    R *t;
    int k;

    v = igObject_GetAllocator(arg0);
    v = (GPR_00554c14 != 0) ? v : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    ObjectRef rec((R *)FUN_0034f6f0(v));
    rec.p->f16 = arg1->f16;
    e = arg1->f20;
    if (e == -1.0f) {
        f = 100000000.0f;
    } else {
        f = arg1->f16 + e;
    }
    t = rec.p;
    t->f28 = f;
    t = rec.p;
    t->f32 = arg1->f24;
    t->f36 = arg1->f28;
    t->f40 = arg1->f32;
    t = rec.p;
    t->f44 = arg1->f36;
    t->f48 = arg1->f40;
    t->f52 = arg1->f44;
    k = arg1->f12;
    switch (k / 10000) {
    case 0:
        if (k < 1000) {
            rec.p->f24 = 0;
        } else {
            rec.p->f24 = 2;
        }
        break;
    case 6:
        rec.p->f24 = 1;
        break;
    case 7:
    case 8:
        rec.p->f24 = 2;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 9:
    default:
        rec.p->f24 = 0;
        break;
    }
    rec.p->f20 = arg1->f12;
    ObjectList_AppendRetained(arg0->f8, rec.p);
}
