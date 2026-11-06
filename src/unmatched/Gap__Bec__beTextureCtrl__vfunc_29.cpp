#include "dw4/reflected.h"
struct TextureCtrlWork { char header[8]; int f8; int f12; }; /* The _work object: two list handles at +8 and +12. */
struct TextureCtrlSource { char pad[12]; struct TextureCtrlSource *f12; char pad1[12]; unsigned char f28; char pad2[3]; igObjectList *f32; };
extern "C" {
struct TextureCtrlWork *FUN_00342630(int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, int);
int igObject_Destroy(igObject *);
int igObject_GetAllocator(beTextureCtrl *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beTextureCtrl__vfunc_29(beTextureCtrl *arg0, struct TextureCtrlSource *arg1);
}
void Gap__Bec__beTextureCtrl__vfunc_29(beTextureCtrl *arg0, struct TextureCtrlSource *arg1) {
    int temp_s4;
    int var_s3;
    int var_s2;
    int var_v0;
    igObject *old;

    if (arg0->_work == 0) {
        var_v0 = igObject_GetAllocator(arg0);
        if (GPR_00554c14 != 0) {
            var_v0 = (int)var_v0;
        } else {
            var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        old = (igObject *)arg0->_work;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        arg0->_work = (int)FUN_00342630(var_v0);
    }
    arg1 = arg1->f12;
    if (arg1->f28 != 0) {
        temp_s4 = arg1->f32->_count;
        var_s3 = 0;
        if (0 < temp_s4) {
            var_s2 = 0;
            do {
                ObjectList_AppendRetained(((struct TextureCtrlWork *)arg0->_work)->f8, *(int *)((char *)arg1->f32->_data + var_s2));
                var_s3 += 1;
                var_s2 += 4;
            } while (var_s3 < temp_s4);
        }
    } else {
        temp_s4 = arg1->f32->_count;
        var_s3 = 0;
        if (0 < temp_s4) {
            var_s2 = 0;
            do {
                ObjectList_AppendRetained(((struct TextureCtrlWork *)arg0->_work)->f12, *(int *)((char *)arg1->f32->_data + var_s2));
                var_s3 += 1;
                var_s2 += 4;
            } while (var_s3 < temp_s4);
        }
    }
}
