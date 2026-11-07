#include "dw4/reflected.h"
class igAnimationHierarchyOps {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual int getBoneCount();
    virtual int getBlendCount();
    char pad4[8];
    float *_translations;
};
struct BoneInfoRow { char pad[8]; int _count; int _capacity; igAnimationCombinerBoneInfo **_data; };
struct BoneInfoRows { char pad[16]; BoneInfoRow **_data; };
struct CombinerView {
    char pad0[12];
    igAnimationHierarchyOps *_animHierarchy;
    char pad16[32];
    BoneInfoRows *_boneInfoListList;
    char pad52[32];
    float *_boneMatrixArray;
    float *_blendMatrixArray;
};
extern "C" {
void Gap__Core__igObject__vfunc_15(CombinerView *);
int igObject_GetAllocator(CombinerView *);
void igMetaField_AllocateArray(int *, int, CombinerView *, int, int);
void igMatrix44f_SetIdentity(float *);
extern int DAT_00562300;
extern int DAT_00562308;
void Gap__Sg__igAnimationCombiner__vfunc_17(CombinerView *c);
}
void Gap__Sg__igAnimationCombiner__vfunc_17(CombinerView *c) {
    int result1;
    int result2;
    int bones;
    int i;
    Gap__Core__igObject__vfunc_15(c);
    bones = c->_animHierarchy->getBoneCount();
    for (i = 0; i < bones; i++) {
        BoneInfoRow *row = c->_boneInfoListList->_data[i];
        int j;
        for (j = 0; j < row->_count; j++) {
            igAnimationCombinerBoneInfo *info = row->_data[j];
            if (info->_transformSource != 0 && !info->_useAnimationTranslation) {
                float *t = c->_animHierarchy->_translations + i * 3;
                float y;
                float z;
                float x;
                z = t[2];
                y = t[1];
                x = t[0];
                info->_constantTranslation[0] = x;
                info->_constantTranslation[1] = y;
                info->_constantTranslation[2] = z;
            }
        }
    }
    if (c->_animHierarchy != 0) {
        int boneCount = c->_animHierarchy->getBoneCount();
        int blendCount = c->_animHierarchy->getBlendCount();
        if (boneCount != 0) {
            if (c->_boneMatrixArray == 0) {
                float *m;
                int k;
                igMetaField_AllocateArray(&result1, DAT_00562300, c, boneCount, igObject_GetAllocator(c));
                m = c->_boneMatrixArray;
                for (k = 0; k < boneCount; k++) {
                    igMatrix44f_SetIdentity(m);
                    m += 16;
                }
            }
            if (blendCount != 0 && c->_blendMatrixArray == 0) {
                float *m;
                int k;
                igMetaField_AllocateArray(&result2, DAT_00562308, c, blendCount, igObject_GetAllocator(c));
                m = c->_blendMatrixArray;
                for (k = 0; k < blendCount; k++) {
                    igMatrix44f_SetIdentity(m);
                    m += 16;
                }
            }
        }
    }
}
