class ShadowRefObj { public: virtual void s0(); int refCount; };
extern "C" {
int igObject_Destroy(...);
void FUN_00140ad0(void *, void *, int);
int FUN_00166d40(void);
void FUN_001d7b10(void *, void *);
extern ShadowRefObj *DAT_005628f0;
extern int DAT_004e4820[];
}
class ShadowStateObj : public ShadowRefObj { public: virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(int); virtual void s23(int); virtual void s24(); virtual void s25(); virtual void s26(int); virtual void s27(int); virtual void s28(int); virtual void s29(); virtual void s30(int); virtual void s31(int); virtual void s32(int); virtual void s33(int); };
class ShadowViewportObj { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(int, int, int, int, float, float); };
static inline void addRef(ShadowRefObj *o) { if (o) { o->refCount++; } }
static inline void releaseRef(ShadowRefObj *o) {
    if (o) {
        --o->refCount;
        if (((unsigned long long)(long long)o->refCount & 0x7fffffULL) == 0)
            igObject_Destroy(o);
    }
}
struct ShadowRef {
    ShadowRefObj *p;
    ShadowRef(ShadowRefObj *x) : p(x) { addRef(p); }
    ~ShadowRef() {
        ShadowRefObj *object = p;
        if (object) {
            --object->refCount;
            if (((unsigned long long)(long long)object->refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
struct ShadowTexState {
    char pad0[12]; int mode; ShadowRefObj *image; ShadowRefObj *source; ShadowRefObj *target;
    int f28; int f32; int f36; int f40; int width; int height;
    void set_image(ShadowRefObj *v) { addRef(v); releaseRef(image); image = v; }
    void set_source(ShadowRefObj *v) { addRef(v); releaseRef(source); source = v; }
    void set_target(ShadowRefObj *v) { addRef(v); releaseRef(target); target = v; }
};
struct ShadowTarget : public ShadowRefObj {
    char pad8[4]; int f12; int f16; int f20; unsigned char f24; char pad25[7]; ShadowRefObj *texture; int f36; int width; int height;
    int f48; int f52; int f56; int f60;
    void setSize(int w, int h) { width = w; height = h; }
    void set_texture(ShadowRefObj *v) { addRef(v); releaseRef(texture); texture = v; }
};
struct ShadowHolder { char pad0[12]; ShadowRefObj *target;
    void set_target(ShadowRefObj *v) { addRef(v); releaseRef(target); target = v; }
};
struct ShadowFlagObj { char pad0[82]; unsigned char enabled; };
struct ProjectiveShadowView {
    char pad0[100];
    ShadowStateObj *f100;
    ShadowStateObj *f104;
    int pad108;
    char f112[16];
    int width;
    int height;
    int format;
    char pad140[4];
    ShadowTarget *target;
    ShadowHolder *holder;
    ShadowStateObj *texture;
    ShadowStateObj *f156;
    ShadowStateObj *f160;
    ShadowStateObj *f164;
    ShadowTexState *texState;
    ShadowStateObj *image;
    ShadowViewportObj *f176;
    char pad180[4];
    ShadowStateObj *f184;
    char pad188[40];
    ShadowViewportObj *f228;
};
extern "C" void FUN_001d7120(ProjectiveShadowView *s);
void FUN_001d7120(ProjectiveShadowView *s) {
    bool missing = !(s->format != 0);
    if (missing != false) { s->format = 0; }
    s->f184->s23(1);
    ShadowRef none(0);
    s->f184->s31((int)none.p);
    s->f156->s23(0);
    s->f156->s31((int)s->texture);
    s->f160->s23(1);
    s->f160->s31((int)s->texture);
    s->f164->s23(2);
    s->f164->s31((int)s->texture);
    s->texState->mode = 3;
    { ShadowRefObj *v = s->image; s->texState->set_source(v); }
    { ShadowRefObj *v = s->texture; s->texState->set_target(v); }
    s->texState->f28 = 0;
    s->texState->f32 = 0;
    s->texState->f36 = 0;
    s->texState->f40 = 0;
    s->texState->set_image(DAT_005628f0);
    s->texState->width = s->width;
    s->texState->height = s->height;
    s->image->s26(s->width);
    s->image->s27(s->height);
    s->image->s28(DAT_004e4820[s->format]);
    s->texture->s30(0);
    s->texture->s31(0);
    s->texture->s32(0);
    s->texture->s33(0);
    FUN_00140ad0(s->texture, s->image, 0);
    ((ShadowTexState *)s->texture)->width = 3;
    if (FUN_00166d40() != 0) {
        ShadowStateObj *t = s->texture;
        t->s22(FUN_00166d40());
    }
    s->target->f24 = 1;
    s->target->f20 = -1;
    s->target->f36 = 2;
    s->target->f12 = 1;
    s->target->f16 = 0;
    { ShadowRefObj *v = s->texture; s->target->set_texture(v); }
    { int h = s->height; s->target->setSize(s->width, h); }
    s->target->f60 = 0;
    s->target->f56 = 16;
    s->target->f48 = 24;
    s->target->f52 = 8;
    { ShadowRefObj *v = s->target; s->holder->set_target(v); }
    s->f228->s30(1, 1, s->width - 2, s->height - 2, 0.0f, 1.0f);
    s->f176->s30(0, 0, s->width, s->height, 0.0f, 1.0f);
    ((ShadowFlagObj *)s->f100)->enabled = 1;
    ((ShadowFlagObj *)s->f104)->enabled = 1;
    s->f100->s23(0);
    s->f104->s23(0);
    FUN_001d7b10(s, s->f112);
}
