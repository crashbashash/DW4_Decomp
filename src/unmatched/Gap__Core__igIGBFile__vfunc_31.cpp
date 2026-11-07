extern "C" {
void igObject_Destroy(void *);
int igObject_IsKindOf(void *, int);
}
class igResult;
extern int DAT_00586140[4];
extern igResult DAT_004fb410;
extern igResult DAT_004fb418;
class igResult { public: int v; igResult(const igResult &o) : v(o.v) {}
    bool operator==(const igResult &o) const { return v == o.v; }
    inline bool isFailed(int &f) const; };
inline bool igResult::isFailed(int &f) const { f = DAT_004fb418.v; return *this == DAT_004fb418; }
class IgbInfoBase { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual igResult check(); };
class IgbInfoObject : public IgbInfoBase { public: int rc; };
struct IgbInfoList { int vt; int rc; int count; int cap; IgbInfoObject **data; };
class Ref { public: IgbInfoObject *p; Ref(IgbInfoObject *o) : p(o) { if (p != 0) { p->rc = p->rc + 1; } }
 ~Ref() { IgbInfoObject *object = p; if (object) { --object->rc; if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
static inline IgbInfoObject *castInfo(IgbInfoObject *o) { if (o != 0 && igObject_IsKindOf(o, DAT_00586140[0]) != 0) { return o; } return 0; }
class IgbFileInfoView { public: virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual igResult finish(); char pad[20]; IgbInfoList *list; };
extern "C" igResult Gap__Core__igIGBFile__vfunc_31(IgbFileInfoView *self) {
    igResult result = DAT_004fb410;
    int i;
    int fail;
    for (i = 0; i < self->list->count; i++) {
        Ref o(castInfo(self->list->data[i]));
        if (o.p != 0) {
            if (o.p->check().isFailed(fail)) {
                result.v = fail;
            }
        }
    }
    if (self->finish().isFailed(fail)) {
        result.v = fail;
    }
    return result;
}
