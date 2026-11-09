#include "dw4/igSmartPointer.h"
extern "C" {
void FUN_00236be0(int, beCri *);
int FUN_00306360(int, const char *, int);
igStringObj *FUN_002b9500(void *);
int FUN_00306770(int, int, const char *, igSmartPointer<igStringObj> *, const char *, int);
void FUN_0030b3c0(igStringObj *, const char *);
void FUN_003327c0(const char *);
void FUN_00332810(int);
void FUN_00332c50(int);
void FUN_0037b950(void);
void *Memory_GetAllocatorBySelector(int);
void *igObject_GetAllocator(void *);
int strcmp(const char *, const char *);
struct IniRoot { char pad[56]; int ini; };
struct ErrorHooks { char pad[60]; void (*onError)(void); };
extern IniRoot *DAT_00586dc8[4];
extern ErrorHooks *DAT_005863b0[4];
extern void (*DAT_0058a350[4])(void);
extern int DAT_005873c8[4];
extern int DAT_00587110[4];
extern char *DAT_004c22f0[4];
extern char DAT_0050e400[];                 /* "BECRUNTIME" */
extern char DAT_0050e410[];                 /* "AdxModulePath" */
extern char DAT_0050e420[];                 /* "" */
extern char DAT_0050e428[];                 /* "9.31s281" */
extern char DAT_0050e438[];                 /* "9.18" */
extern char DAT_0050e440[];                 /* "C:/cri/ps2/iop/modules" */
extern char DAT_0050e460[];                 /* "C:/usr/local/cri/mwlib/iop/drv" */
extern unsigned char GPR_00554c14;
extern unsigned char GPR_00554de4;
void Gap__Bec__beCri__vfunc_21(beCri *self);
}

void Gap__Bec__beCri__vfunc_21(beCri *self) {
    int section;
    int ini;
    FUN_00236be0(self->_insight, self);
    ini = DAT_00586dc8[0]->ini;
    if (ini == 0) return;
    section = FUN_00306360(ini, DAT_0050e400, 0);
    if (section == -1) return;
    void *alloc = igObject_GetAllocator(self);
    alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    igSmartPointer<igStringObj> path(FUN_002b9500(alloc));
    if (FUN_00306770(ini, section, DAT_0050e410, &path, DAT_0050e420, 0) == 0) {
        if (strcmp(DAT_0050e428, DAT_0050e438) == 0)
            FUN_0030b3c0(path, DAT_0050e440);
        else
            FUN_0030b3c0(path, DAT_0050e460);
    }
    char *text = (char *)path->_buffer;
    FUN_003327c0(text == 0 ? DAT_004c22f0[0] : text);
    GPR_00554de4 = 1;
    FUN_00332810(0);
    DAT_005873c8[0] = 2;
    FUN_00332c50(1);
    ErrorHooks *hooks = DAT_005863b0[0];
    DAT_0058a350[0] = hooks->onError;
    hooks->onError = FUN_0037b950;
}
