typedef struct R { int w0; int refs; } R;
struct Y { char pad[240]; R *obj; };
struct X { char pad[76]; struct Y *y; };
struct Msg { int a; int b; int c; };
int FUN_004578c0();
int FUN_00466b20();
int igObject_Destroy();
extern int DAT_0058cb00[4];
void FUN_004666e0(struct X *arg0, int arg1, int arg2) {
    struct Msg m;
    R **pp;
    R *p;
    if (arg2 != 0) {
        if (arg1 == 0) {
            FUN_00466b20(arg0);
        } else if (arg1 == 1) {
            pp = &arg0->y->obj;
            p = *pp;
            if (p != 0) {
                p->refs = p->refs - 1;
                if (((unsigned long long)((long long)p->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(p);
                }
            }
            *pp = 0;
            m.a = 2;
            m.b = 0;
            m.c = DAT_0058cb00[0];
            FUN_004578c0(arg0->y, &m);
        }
    }
}
