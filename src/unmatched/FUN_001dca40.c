/* The count is read const so it is loaded before f24. */
typedef struct Obj Obj;
struct Obj { int w0; int references; };
typedef struct List List;
struct List { int pad0[2]; int count; int pad1; Obj **data; int f20; int f24; };
int ObjectList_ResizeRetained();
int igObject_Destroy();
int igObject_GetAllocator();
void FUN_001dca40(List *arg0, Obj *(*arg1)(int)) {
    int n;
    int alloc;
    int i;
    int c;
    Obj *o;
    Obj *old;
    int off;
    c = *(const int *)&arg0->count;
    n = arg0->f24 + c;
    ObjectList_ResizeRetained(arg0, n);
    alloc = igObject_GetAllocator(arg0);
    i = arg0->f20;
    for (; i < n; i++) {
        o = arg1(alloc);
        if (o != 0) {
            o->references = o->references + 1;
        }
        off = i * 4;
        old = *(Obj **)((char *)arg0->data + off);
        if (old != 0) {
            old->references = old->references - 1;
            if (((unsigned long long)((long long)old->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(old);
            }
        }
        if (arg0->count != 0 && i >= 0 && i < arg0->count) {
            *(Obj **)((char *)arg0->data + off) = o;
        }
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
}
