extern "C" {
int FUN_00460e00(...);
int FUN_00460f20(...);
struct OptionPanelView;
void FUN_00460ac0(OptionPanelView *arg0);
}
class DW4VC_128 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
class DW4VC_132 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
struct OptionPanelConfig { char pad[195]; unsigned char b195, b196, b197, b198, b199, b200, b201, b202; };
struct OptionPanelView { char pad[12]; OptionPanelConfig *f12; DW4VC_128 *f16; DW4VC_128 *f20; DW4VC_128 *f24; DW4VC_128 *f28; };
enum PanelMode { kPanelOff, kPanelOn };
void FUN_00460ac0(OptionPanelView *arg0) {
    arg0->f20->vX(arg0->f12->b195);
    FUN_00460e00(arg0, arg0->f20);
    FUN_00460f20(arg0, arg0->f20, arg0->f12->b196);
    ((DW4VC_132 *)arg0->f16)->vX(arg0->f12->b197);
    FUN_00460e00(arg0, arg0->f16);
    FUN_00460f20(arg0, arg0->f16, arg0->f12->b198);
    arg0->f24->vX(arg0->f12->b201 ? kPanelOff : kPanelOn);
    FUN_00460e00(arg0, arg0->f24);
    FUN_00460f20(arg0, arg0->f24, arg0->f12->b202);
    arg0->f28->vX(arg0->f12->b199 ? kPanelOn : kPanelOff);
    FUN_00460e00(arg0, arg0->f28);
    FUN_00460f20(arg0, arg0->f28, arg0->f12->b200);
}
