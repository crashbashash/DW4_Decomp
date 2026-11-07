class ShadowRefObj { public: virtual void s0(); int refCount; };
class ShadowSetupObj : public ShadowRefObj { public: virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(int); virtual void s24(); virtual void s25(); virtual void s26(int); virtual void s27(int); virtual void s28(int); virtual void s29(); virtual void s30(int); virtual void s31(int); virtual void s32(int); virtual void s33(int); char pad8[44]; unsigned char *pixels; };
class ShadowFogObj { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(int); virtual void s24(); virtual void s25(); virtual void s26(int); virtual void s27(int); virtual void s28(int); virtual void s29(); virtual void s30(int); virtual void s31(float); virtual void s32(int); virtual void s33(int); };
struct ShadowColor { float r, g, b, a; };
extern "C" int FUN_001931b0(ShadowColor *, int);
struct ShadowColorObj { char pad0[12]; int enabled; ShadowColor color; char pad32[28]; int packed;
    void setColor(ShadowColor &c) { color = c; packed = FUN_001931b0(&c, 1); }
};
struct ShadowModeObj { char pad0[12]; int mode; };
extern "C" {
int igObject_Destroy(...);
int FUN_002f88e0(...);
ShadowSetupObj *FUN_00132b60(...);
ShadowSetupObj *FUN_0014df70(...);
void FUN_00140ad0(void *, void *, int);
extern int DAT_00587038;
extern ShadowSetupObj *DAT_005628d8;
extern ShadowSetupObj *DAT_005627e8;
extern ShadowSetupObj *DAT_005627f0;
extern ShadowSetupObj *DAT_005627f8;
extern ShadowSetupObj *DAT_00562800;
extern ShadowSetupObj *DAT_00562808;
extern ShadowSetupObj *DAT_00562810;
extern ShadowSetupObj *DAT_00562818;
extern ShadowSetupObj *DAT_00562820;
extern ShadowSetupObj *DAT_00562850;
extern ShadowSetupObj *DAT_00562858;
extern ShadowSetupObj *DAT_00562860;
extern ShadowSetupObj *DAT_00562868;
extern ShadowSetupObj *DAT_00562870;
extern ShadowSetupObj *DAT_00562878;
extern ShadowSetupObj *DAT_00562880;
extern ShadowSetupObj *DAT_005628d0;
extern ShadowColorObj *DAT_00562838;
extern ShadowColorObj *DAT_00562840;
extern ShadowModeObj *DAT_00562848;
extern ShadowFogObj *DAT_00562828;
extern ShadowSetupObj *DAT_00562830;
}
struct ShadowRef {
    ShadowSetupObj *p;
    ~ShadowRef() {
        ShadowSetupObj *object = p;
        if (object) {
            --object->refCount;
            if (((unsigned long long)(long long)object->refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
extern "C" void FUN_001d4480(void);
void FUN_001d4480(void) {
    ShadowColor black;
    ShadowColor white;
    DAT_005628d8->s23(0);
    {
        ShadowRef image;
        image.p = FUN_00132b60(FUN_002f88e0(DAT_00587038));
        DAT_005628d8->s31((int)image.p);
        ShadowRef texture;
        texture.p = FUN_0014df70(FUN_002f88e0(DAT_00587038));
        FUN_00140ad0(image.p, texture.p, 0);
        texture.p->s26(1);
        texture.p->s27(1);
        texture.p->s28(5);
        texture.p->s29();
        unsigned char *px = texture.p->pixels;
        px[0] = 255;
        px[1] = 255;
        px[2] = 255;
        image.p->s30(0);
        image.p->s31(0);
        image.p->s32(0);
        image.p->s33(0);
    }
    DAT_005627e8->s23(0);
    DAT_005627e8->s30(1);
    DAT_005627f0->s23(1);
    DAT_005627f0->s30(1);
    DAT_005627f8->s23(0);
    DAT_005627f8->s30(0);
    DAT_00562820->s30(0);
    DAT_00562850->s30(0);
    DAT_00562800->s30(0);
    DAT_00562800->s31(5);
    DAT_00562808->s30(1);
    DAT_00562808->s31(1);
    DAT_00562810->s30(1);
    DAT_00562818->s30(0);
    black.r = 0.0f; black.g = 0.0f; black.b = 0.0f; black.a = 0.0f;
    DAT_00562838->enabled = 1;
    DAT_00562848->mode = 1;
    white.r = 1.0f; white.g = 1.0f; white.b = 1.0f; white.a = 1.0f;
    DAT_00562838->setColor(white);
    DAT_00562840->setColor(black);
    DAT_00562840->enabled = 1;
    DAT_00562858->s30(1);
    DAT_00562858->s23(0);
    DAT_00562860->s30(1);
    DAT_00562860->s23(1);
    ((ShadowModeObj *)DAT_00562868)->mode = 1;
    DAT_00562868->s23(0);
    ((ShadowModeObj *)DAT_00562870)->mode = 1;
    DAT_00562870->s23(1);
    DAT_00562878->s30(1);
    DAT_00562878->s23(0);
    DAT_00562880->s30(1);
    DAT_00562880->s23(1);
    DAT_00562828->s30(4);
    DAT_00562828->s31(0.01f);
    DAT_00562830->s30(1);
    DAT_005628d0->s30(0);
}
