class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void *v104(void *); virtual void d25(); virtual void v112(int); };
struct Rc { int vt; int rc; };
struct Q { char pad8[8]; V *f8; char pad12[60]; V *f72; char pad76[4]; V *f80; char pad84[4]; Rc *f88; };
extern "C" {
int FUN_004601e0(...);
int FUN_00460260(...);
int FUN_004602c0(...);
int FUN_00460330(...);
int FUN_004608a0(...);
int FUN_00460ac0(...);
int igObject_Destroy(...);
extern int DAT_0051faa8[4];
void FUN_0045f690(Q *arg0);
}
void FUN_0045f690(Q *arg0) {
    Rc *temp_v0 = (Rc *)arg0->f8->v104(&DAT_0051faa8[0]);
    if (temp_v0 != 0) {
        temp_v0->rc = temp_v0->rc + 1;
        asm { nop }
    }
    Rc *temp_a0_2 = arg0->f88;
    if (temp_a0_2 != 0) {
        temp_a0_2->rc = temp_a0_2->rc - 1;
        if (((unsigned long long)((long long)temp_a0_2->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0_2);
            asm { nop }
        }
    }
    arg0->f88 = temp_v0;
    arg0->f72->v112((int)arg0->f8);
    arg0->f80->v112((int)arg0->f8);
    FUN_004601e0(arg0);
    FUN_00460260(arg0);
    FUN_004602c0(arg0);
    FUN_004608a0(arg0);
    FUN_00460ac0(arg0);
    FUN_00460330(arg0);
}
