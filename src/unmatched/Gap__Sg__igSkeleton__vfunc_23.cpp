extern "C" {
void FUN_00190470(void *, void *, void *);
void FUN_001904f0(void *, void *, void *);
void FUN_001906d0(void *, void *);
void Matrix44_Copy(void *, void *);
void Matrix44_GetTranslation(void *, void *);
void Matrix44_SetTranslation(void *, void *);
}
struct SkeletonMatrix { float m[16]; };
struct SkeletonBoneInfoView { int _vtable; unsigned int _refCount; int _name; int _parentIdx; int _bmIdx; };
struct SkeletonBoneListView { int _vtable; unsigned int _refCount; int _count; int _capacity; SkeletonBoneInfoView **_data; };
class SkeletonSlots {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual int getBoneCount();
    virtual void s23();
    virtual int getTime();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
    virtual void update(int t);
};
struct SkeletonSourceView : SkeletonSlots { char pad[28]; SkeletonMatrix _matrix; };
struct SkeletonOverrideView { int _vtable; unsigned int _refCount; int _bone; SkeletonSourceView *_source; int _mode; };
struct SkeletonOverrideListView { int _vtable; unsigned int _refCount; int _count; int _capacity; SkeletonOverrideView **_data; };
struct SkeletonView : SkeletonSlots { unsigned int _refCount; int _name; int _boneTranslationArray; SkeletonBoneListView *_boneInfoList; SkeletonMatrix *_invJointArray; };
extern "C" void Gap__Sg__igSkeleton__vfunc_23(SkeletonView *o, SkeletonSlots *clock, int unused, SkeletonMatrix *local, SkeletonMatrix *global, SkeletonMatrix *out, SkeletonOverrideListView *overrides) {
    SkeletonMatrix *inv;
    int count;
    int n;
    int i;
    int j;
    float translation[3];
    SkeletonMatrix m;
    count = o->getBoneCount();
    inv = o->_invJointArray;
    if (overrides == 0 || (n = overrides->_count) == 0) {
        for (i = 1; i < count; i++) {
            SkeletonBoneInfoView *info = o->_boneInfoList->_data[i];
            SkeletonMatrix *g;
            int parent = info->_parentIdx;
            if (parent == 0) {
                g = &global[i];
                Matrix44_Copy(g, &local[i]);
            } else {
                g = &global[i];
                FUN_00190470(g, &local[i], &global[parent]);
            }
            if (info->_bmIdx != -1) {
                FUN_00190470(&out[info->_bmIdx], inv, g);
                inv++;
            }
        }
        return;
    }
    for (i = 1; i < count; i++) {
        int off;
        SkeletonBoneInfoView *info;
        SkeletonMatrix *g;
        info = o->_boneInfoList->_data[i];
        off = i << 6;
        Matrix44_Copy(&m, (SkeletonMatrix *)((char *)local + off));
        for (j = 0; j < n; j++) {
            SkeletonOverrideView *ov = overrides->_data[j];
            if (i == ov->_bone) {
                SkeletonMatrix *src;
                SkeletonSourceView *source = ov->_source;
                source->update(clock->getTime());
                src = &ov->_source->_matrix;
                if (ov->_mode == 2) { Matrix44_Copy(&m, src); }
                if (ov->_mode == 3) {
                    Matrix44_GetTranslation(&m, translation);
                    Matrix44_Copy(&m, src);
                    Matrix44_SetTranslation(&m, translation);
                } else if (ov->_mode == 0) {
                    FUN_001906d0(&m, src);
                } else if (ov->_mode == 1) {
                    FUN_001904f0(&m, &m, src);
                }
            }
        }
        if (info->_parentIdx != 0) {
            g = (SkeletonMatrix *)((char *)global + off);
            FUN_001904f0(g, &m, &global[info->_parentIdx]);
        } else {
            g = (SkeletonMatrix *)((char *)global + off);
            Matrix44_Copy(g, &m);
        }
        if (info->_bmIdx != -1) {
            FUN_001904f0(&out[info->_bmIdx], inv, g);
            inv++;
        }
    }
}
