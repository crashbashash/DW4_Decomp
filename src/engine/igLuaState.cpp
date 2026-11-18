#include "dw4/support/reflected.h"
#include <stdlib.h>
#include "dw4/enbaya/Enbaya.h"

class DW4VC_12_1 { public: virtual void d0(); virtual int vX(int); };

extern "C" {


/* Vtable images of the derived and base classes; the array form keeps the address load absolute. */
extern int g_derivedVtable_0052d6d0[4];
extern int g_baseVtable_0052d6f0[4];
extern int g_derivedVtable_0052d710[4];
extern int g_baseVtable_0052d730[4];
/* The 4-byte allocator object Enbaya_InitMemoryManagement creates on first use. */
int g_luaAllocator;

void FUN_002809e0(igObject *self);
int FUN_002809f0(int a0, int a1);
void Enbaya_CreateDefaultAllocator(int ***arg0, int **arg1);

void *FUN_00280810(void *arg0) {
    *(int *)((char *)(arg0) + 0) = (int)(&g_baseVtable_0052d6f0[0]);
    *(int *)((char *)(arg0) + 0) = (int)(&g_derivedVtable_0052d6d0[0]);
    *(int *)((char *)(arg0) + 76) = (int)((int) ((char *)arg0 + 0x50));
    return arg0;
}

/* Deleting destructor of the 0x50-byte object built by FUN_00280810 (see FUN_00280890). Sets only the
 * base vtable, then calls operator delete when the signed low 16 bits of the delete flag are
 * positive; FUN_00280890 calls the bare-return FUN_002809e0 at the same point. operator delete never
 * returns (it ends in an endless loop). */
igObject *FUN_00280840(igObject *self, long long deleteFlags) {
    if (self != 0) {
        self->_vtable = (int)&g_baseVtable_0052d6f0[0];
        if (((long long) (deleteFlags << 0x30) >> 0x30) > 0) {
            operator delete(self);
        }
    }
    return self;
}

/* Deleting destructor of the 0x50-byte object built by FUN_00280810. Its constructor writes the
 * base vtable and then the derived one; this undoes that in reverse, then releases the storage
 * when the signed low 16 bits of the flag are positive (same flag test as FUN_00280840). FUN_002809e0
 * is a bare return, so no release actually happens in retail. */
igObject *FUN_00280890(igObject *self, long long deleteFlags) {
    if (self != 0) {
        self->_vtable = (int)&g_derivedVtable_0052d6d0[0];
        if (self != 0) {
            self->_vtable = (int)&g_baseVtable_0052d6f0[0];
        }
        if (((long long) (deleteFlags << 0x30) >> 0x30) > 0) {
            FUN_002809e0(self);
        }
    }
    return self;
}

int FUN_002808f0(int arg0) {
    int p = FUN_002809f0(0x50, arg0); if (p != 0) { p = (int)FUN_00280810((void *)p); } return p;
}

/* Returns 0x50 (the offset FUN_00280810 stores at +76 as the inline-data pointer) plus the int
 * words at +20..+72. The layout is the one FUN_00280810 constructs, not the reflected igLuaState. */
int FUN_00280920(void *self) {
    int *word = (int *)self;
    return word[18] + (word[17] + (word[16] + (word[15] + (word[14] + (word[13] + (word[12] + (word[11] + (word[10] + (word[9] + (word[8] + (word[7] + (word[5] + 0x50 + word[6]))))))))))));
}

void FUN_002809a0(void) {
}

/* Constant stub that returns 0x50 (80). It is not a field offset of the reflected igLuaState,
 * which is 0x14 bytes. */
int FUN_002809b0(void) {
    return 0x50;
}

/* IgLuaState slot 33, returns the object reference count (_refCount at +4, inherited from
 * igObject). */
int FUN_002809c0(igLuaState *self) {
    return self->_refCount;
}

/* Vtable slot 34: returns the word at +12 (_luaState, the raw lua_State reference) reinterpreted
 * as float (loaded with lwc1). */
float FUN_002809d0(igLuaState *self) {
    return *(float *)&self->_luaState;
}

void FUN_002809e0(igObject *self)
{
}

int FUN_002809f0(int a0, int a1)
{
    return a1;
}

void Enbaya_InitMemoryManagement(void **arg0) {
    if (g_luaAllocator == 0) {
        if (arg0 == 0) {
            g_luaAllocator = (int)malloc(4);
        } else {
            g_luaAllocator = ((DW4VC_12_1 *)(arg0))->vX((int)(4));
        }
        Enbaya_CreateDefaultAllocator((int ***)g_luaAllocator, (int **)arg0);
    }
}

void Enbaya_CreateDefaultAllocator(int ***arg0, int **arg1) {
    int **temp_v0;

    if (arg1 != 0) {
        *arg0 = arg1;
        return;
    }
    temp_v0 = (int **)malloc(4);
    if (temp_v0 != 0) {
        *temp_v0 = &g_baseVtable_0052d730[0];
        *temp_v0 = &g_derivedVtable_0052d710[0];
    }
    *arg0 = temp_v0;
}

/* Deleting destructor of the 4-byte, vtable-only object that Enbaya_CreateDefaultAllocator builds. Resets the
 * vtable to the base-class image (the constructor writes the base image, then the derived one),
 * then calls operator delete when the signed low 16 bits of the delete flag are positive (same flag
 * test as FUN_00280890 / FUN_00280840). operator delete never returns, so retail has no working release here. */
igObject *EnbayaAllocator_Destruct(igObject *self, long long deleteFlags) {
    if (self != 0) {
        self->_vtable = (int)&g_baseVtable_0052d730[0];
        if (((long long) (deleteFlags << 0x30) >> 0x30) > 0) {
            operator delete(self);
        }
    }
    return self;
}

/* Destructor (no delete flag) of the 4-byte, vtable-only object that Enbaya_CreateDefaultAllocator builds. Undoes
 * the constructor's two vtable writes in reverse: the derived image, then the base image (the same
 * one EnbayaAllocator_Destruct leaves behind). */
igObject *EnbayaDefaultAllocator_Destruct(igObject *self) {
    if (self != 0) {
        self->_vtable = (int)&g_derivedVtable_0052d710[0];
        if (self != 0) {
            self->_vtable = (int)&g_baseVtable_0052d730[0];
        }
    }
    return self;
}

void EnbayaDefaultAllocator_Allocate(int a0, int a1) {
    malloc(a1);
}

void EnbayaDefaultAllocator_Free(int a0, int a1) {
    free((void *)a1);
}

void EnbayaDefaultAllocator_Reallocate(int unused, int a, int b) {
    realloc((void *)a, b);
}

void EnbayaDefaultAllocator_AllocateCleared(int unused, int a, int b) {
    calloc(a, b);
}

void FUN_00280b90(int a0, int a1) {
    free((void *)a1);
}

}
