#include "dw4/reflected.h"
struct Rc { int vt; int refs; };
extern "C" {
void *FUN_0014adc0(...);
void *FUN_0014b180(...);
int FUN_0015f660(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
int Gap__Core__igPsx2VertexArray2__vfunc_23(igVertexArray2 *arg0, int arg1, int arg2, struct Info *arg3, struct Disp *arg4);
}
#define RELEASE(slot) { Rc *t = slot; if (t != 0) { t->refs = t->refs - 1; Rc *u = slot; if (((unsigned long long)(long long)u->refs & 0x7fffffULL) == 0) igObject_Destroy(u); } }
struct Disp { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207(); virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215(); virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223(); virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230(); virtual void d231(); virtual void d232(); virtual void d233(); virtual void d234(); virtual void d235(); virtual void d236(); virtual void d237(); virtual void d238(); virtual void d239(); virtual void d240(); virtual void d241(); virtual void d242(); virtual void d243(); virtual void d244(); virtual void d245(); virtual void d246(); virtual void d247(); virtual void d248(); virtual void d249(); virtual void d250(); virtual void d251(); virtual void d252(); virtual void d253(); virtual void d254(); virtual void d255(); virtual void d256(); virtual void d257(); virtual void d258(); virtual int v1044(void *, int); };
struct Impl { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v104(void *, int, void *, void *); };
struct Info { char pad[12]; unsigned int f12; };
int Gap__Core__igPsx2VertexArray2__vfunc_23(igVertexArray2 *arg0, int arg1, int arg2, Info *arg3, Disp *arg4) {
    Rc * volatile sp7C;
    Rc * volatile sp78;
    Rc * volatile sp74;
    Rc * volatile sp70;
    igVertexStream *s5;
    int s0;
    int s3 = arg1;
    if (arg0->_vertexStream == 0) {
        Rc *n;
        Rc *old;
        sp7C = (Rc *)FUN_0014adc0(igObject_GetAllocator(arg0));
        n = sp7C;
        if (n != 0) n->refs = n->refs + 1;
        old = (Rc *)arg0->_vertexStream;
        if (old != 0) {
            old->refs = old->refs - 1;
            if (((unsigned long long)(long long)old->refs & 0x7fffffULL) == 0) igObject_Destroy(old);
        }
        arg0->_vertexStream = (int)n;
        { Rc *a = sp7C; if (a != 0) { a->refs = a->refs - 1; if (((unsigned long long)(long long)a->refs & 0x7fffffULL) == 0) igObject_Destroy(a); } }
    }
    s5 = (igVertexStream *)arg0->_vertexStream;
    if (s5->_isConfigured != 0) return 1;
    sp78 = (Rc *)FUN_0014b180(igObject_GetAllocator(arg0));
    sp74 = sp78;
    { Rc *t = sp74; if (t != 0) t->refs = t->refs + 1; }
    FUN_0015f660(arg0, &sp74);
    RELEASE(sp74);
    if (arg3 != 0 && arg3->f12 > 1 && !(s3 & 0x2000)) {
        switch (s3) {
        case 4: s3 = 0x2001; break;
        case 2: s3 = 0x2000; break;
        case 5: s3 = 0x2002; break;
        }
    }
    s5->_primitive = s3;
    arg4->v1044(arg0, 0);
    sp70 = sp78;
    { Rc *t = sp70; if (t != 0) t->refs = t->refs + 1; }
    s0 = ((Impl *)s5)->v104((void *)&sp70, arg2, arg3, arg4) & 0xFF;
    RELEASE(sp70);
    { Rc *t = sp78; if (t != 0) { t->refs = t->refs - 1; if (((unsigned long long)(long long)t->refs & 0x7fffffULL) == 0) igObject_Destroy(t); } }
    return s0;
}
