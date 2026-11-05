struct R { int w0; int references; };
struct A1 { char pad8[8]; int f8; char pad12[8]; float f20; };
struct A0 { char pad[104]; float f104; unsigned char f108; char p109[3]; struct R *f112; };
struct R *FUN_0019f630();
int FUN_001c5790();
int igObject_Destroy();
void FUN_00466a10(struct A0 *arg0, struct A1 *arg1) {
    struct R *volatile sp4C;
    volatile char sp48[4];
    int s1;
    struct R *o;
    struct R *s0;
    s1 = arg1->f8;
    if (arg1->f20 <= arg0->f104) {
        arg0->f108 = 1;
        arg0->f104 = arg1->f20;
        sp48[0] = 0;
        sp4C = FUN_0019f630(0);
        s0 = sp4C;
        if (s0 != 0) {
            s0->references = s0->references + 1;
        }
        o = arg0->f112;
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
        arg0->f112 = s0;
        o = sp4C;
        if (o != 0) {
            o->references = o->references - 1;
            o = sp4C;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
        FUN_001c5790(arg0->f112, s1);
    }
}
