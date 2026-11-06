/* /192B — beNDMWWindowCtrl_Destroy. Destructor body: republish the controller vtable and then the
 * beNDMWWindow vtable (retail RTTI of 0x0053daa0 and 0x0053dc30), release the seven reference
 * cells the original constructor initialized (reflected offsets 76..52, in that order, flag -1),
 * and when the signed low 16 bits of `flags` are positive hand the object to the deallocation
 * thunk 0x002ff810 (Memory_FreeBuffer wrapper). No extra clearing. `self` is returned unchanged.
 * Matching constructs: the explicit 64-bit return copy (`dmove v0,self`) preserves the original
 * deletion-branch delay slots, and the `nop` after the last cleanup call is the original padding. */
#include "dw4/reflected.h"
extern "C" {
extern int g_beNDMWWindowCtrl_vtable[4];
extern int g_beNDMWWindow_vtable[4];
extern void ObjectRef_Destruct_00150eb0(int *, int);
extern void ObjectRef_Destruct_001c6460(int *, int);
extern void FUN_003b2f30(int *, int);
extern void FUN_003b2fb0(int *, int);
extern void thunk_FUN_002ed460__002ff810(void *);
beNDMWWindowCtrl *beNDMWWindowCtrl_Destroy(beNDMWWindowCtrl *self, long long flags);
}

beNDMWWindowCtrl *beNDMWWindowCtrl_Destroy(beNDMWWindowCtrl *self, long long flags) {
    if (self) {
        self->_vtable = (int)g_beNDMWWindowCtrl_vtable;
        if (self) {
            self->_vtable = (int)g_beNDMWWindow_vtable;
            ObjectRef_Destruct_001c6460(&self->_modelCloseSeqNameList, -1);
            ObjectRef_Destruct_00150eb0(&self->_modelCloseRamNoList, -1);
            ObjectRef_Destruct_001c6460(&self->_modelCloseInfoNameList, -1);
            ObjectRef_Destruct_001c6460(&self->_textCloseNameList, -1);
            ObjectRef_Destruct_001c6460(&self->_textCloseTypeList, -1);
            FUN_003b2f30(&self->_mother, -1);
            FUN_003b2fb0(&self->_subWindow, -1);
            asm { nop }
        }
        if ((short)flags > 0) thunk_FUN_002ed460__002ff810(self);
    }
    asm { dmove v0,self }
    return self;
}
