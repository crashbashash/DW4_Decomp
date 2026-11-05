struct Obj { int w0; unsigned refs; };
struct Y { char pad[8]; int f8; char pad2[8]; float f20; };
struct Z { char pad[24]; float f24; unsigned char f28; char pad2[3]; Obj *f32; };
extern "C" {
Obj *FUN_0019f630(...);
int FUN_001c5790(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
void FUN_00455f50(Z *arg0, Y *arg1);
}
void FUN_00455f50(Z *arg0, Y *arg1) {
    Obj *volatile sp4C;
    int s1 = arg1->f8;
    if (arg1->f20 <= arg0->f24) {
        Obj *s0;
        Obj *old;
        arg0->f28 = 1;
        arg0->f24 = arg1->f20;
        sp4C = FUN_0019f630(igObject_GetAllocator(arg0));
        s0 = sp4C;
        if (s0 != 0) {
            s0->refs = s0->refs + 1;
        }
        old = arg0->f32;
        if (old != 0) {
            old->refs = old->refs - 1;
            if ((old->refs & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        arg0->f32 = s0;
        {
            Obj *q = sp4C;
            if (q != 0) {
                q->refs = q->refs - 1;
                q = sp4C;
                if ((q->refs & 0x7FFFFF) == 0) {
                    igObject_Destroy(q);
                }
            }
        }
        FUN_001c5790(arg0->f32, s1);
    }
}
