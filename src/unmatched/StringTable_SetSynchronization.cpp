extern "C" {
void **FUN_002ba650(...);
int FUN_002f8a20(...);
int Memory_GetAllocatorBySelector(...);
int igObject_Destroy(...);
extern int DAT_00587038[4];
extern void * DAT_005871c8[4];
extern unsigned char GPR_00554c14;
void StringTable_SetSynchronization(int arg0);
}
struct S { int v; S() {} };
class V92 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual S vX(); };
struct T { int word0; int references; };
void StringTable_SetSynchronization(int arg0) {
    int var_v0;
    V92 *o;
    T *p;
    if (arg0 != 0) {
        if (DAT_005871c8[0] == 0) {
            var_v0 = FUN_002f8a20();
var_v0 = GPR_00554c14 != 0 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587038[0]);
            o = (V92 *)FUN_002ba650(var_v0);
            o->vX();
            DAT_005871c8[0] = o;
        }
    } else {
        p = (T *)DAT_005871c8[0];
        if (p != 0) {
            DAT_005871c8[0] = 0;
            p->references = p->references - 1;
            if (((unsigned long long)(long long)p->references & 0x7fffffULL) == 0) {
                igObject_Destroy(p);
            }
        }
    }
}
