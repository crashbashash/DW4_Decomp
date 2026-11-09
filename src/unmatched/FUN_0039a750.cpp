#include "dw4/reflected.h"
/* Appends a sound sub-command to the controller's command list: the command object is created from
 * the controller's allocator, its _sndName is interned (replacing the string the constructor
 * left), _startFrame is set and the object appended; the creating reference is released on scope
 * exit. */
extern "C" {
int FUN_002eb010(...);
beModelCtrlSCSound *FUN_0034f4a0(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_0039a750(beModelCtrlSubCom *arg0, int arg1, float fparg0);
}
/* Owning stack reference to the new sound command, released on scope exit once the list holds its
 * own reference (reference count in the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void FUN_0039a750(beModelCtrlSubCom *arg0, int arg1, float fparg0) {
    int *temp_a1;
    int temp_v0;
    int var_v0;
    int key;
    int var_v0_2;
    int *temp_v1;
    beModelCtrlSCSound *s1;

    key = arg1;
    var_v0 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0 = (int)var_v0;
    } else {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    igSmartPointer<beModelCtrlSCSound> cmd(FUN_0034f4a0(var_v0));
    s1 = cmd.p;
    if (DAT_00586f20[0] == 0) {
        var_v0_2 = FUN_002eb010(0x10);
        if (var_v0_2 != 0) {
            var_v0_2 = StringPool_Construct(var_v0_2);
        }
        DAT_00586f20[0] = var_v0_2;
    }
    key = (int)StringPool_Intern(DAT_00586f20[0], key);
    temp_v1 = (int *)s1->_sndName;
    if (temp_v1 != 0) {
        temp_a1 = temp_v1 - 2;
        temp_v0 = temp_v1[-1] - 1;
        temp_v1[-1] = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    s1->_sndName = key;
    cmd.p->_startFrame = fparg0;
    ObjectList_AppendRetained(arg0->_comList, cmd.p);
}
