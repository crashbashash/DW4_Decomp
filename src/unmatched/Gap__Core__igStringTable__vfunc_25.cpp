extern "C" {
struct T { int w0; int refs; int cnt; int cap; int *data; };
struct B { char p[8]; int size; char p2[4]; char *data; };
int strlen(char *s);
int FUN_002ca8b0(int a);
void igObject_Destroy(T *t);
int List_Reserve(T *l, int n, int sz);
int List_Resize(T *l, int n, int sz);
extern int DAT_004c22f8[4];
}
class ST { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(char *s, int n); char pad[12]; B *f16; T *f20; };
extern "C" int FUN_0030cf30(ST *s);
extern "C" int igObject_GetAllocator(ST *s);
extern "C" void Gap__Core__igStringTable__vfunc_25(ST *arg0, int arg1);
void Gap__Core__igStringTable__vfunc_25(ST *arg0, int arg1) {
    T *old;
    T *l;
    int alloc;
    int n;
    int *data;
    int i;
    char *base;
    char *end;
    char *p;
    FUN_0030cf30(arg0);
    if (arg1 != 0) {
        if (arg0->f20 == 0) {
            alloc = igObject_GetAllocator(arg0);
            old = arg0->f20;
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) {
                    igObject_Destroy(old);
                }
            }
            arg0->f20 = (T *)FUN_002ca8b0(alloc);
        }
        l = arg0->f20;
        if (arg1 >= 0) {
            if (arg1 <= l->cap) {
                l->cnt = arg1;
            } else {
                List_Resize(l, arg1, 4);
            }
        }
        l = arg0->f20;
        if (arg1 >= l->cnt) {
            List_Reserve(l, arg1, 4);
        }
        l = arg0->f20;
        n = l->cnt;
        data = l->data;
        i = 0;
        while (i < n) {
            data[i] = DAT_004c22f8[0];
            i++;
        }
        base = arg0->f16->data;
        p = base;
        end = base + arg0->f16->size;
        while (p < end) {
            if (arg0->vX(p, p - base) == 0) {
                return;
            }
            p += strlen(p) + 1;
        }
    } else {
        old = arg0->f20;
        if (old != 0) {
            if (old != 0) {
                --old->refs;
                if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) {
                    igObject_Destroy(old);
                }
            }
            arg0->f20 = 0;
        }
    }
}
