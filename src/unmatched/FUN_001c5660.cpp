class V;
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void vX(int); char pad4[16]; int f20; };
struct Item { char pad[12]; V *f12; };
struct Lst { char pad[8]; unsigned int cnt; int pad2; Item **items; };
struct Z { char pad[32]; Lst *f32; };
extern "C" {
void FUN_001c5660(Z *arg0, int arg1, int arg2);
}

void FUN_001c5660(Z *arg0, int arg1, int arg2) {
    unsigned int cnt;
    unsigned int i;
    Item *it;
    V *o;
    int cur;
    int a1;
    i = 0;
    cnt = arg0->f32->cnt;
    for (; i < cnt; i++) {
        it = arg0->f32->items[i];
        if (it != 0) {
            o = it->f12;
            if (o != 0) {
                cur = o->f20;
                if (arg2 != 0) {
                    a1 = cur | arg1;
                } else {
                    a1 = cur & ~(cur & ~arg1);
                }
                o->vX(a1);
            }
        }
    }
}
