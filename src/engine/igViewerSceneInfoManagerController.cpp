#include "dw4/reflected.h"

struct G { int pad[9]; int f; };
struct Obj { int *vt; char pad[28]; };

extern "C" {
int Memory_GetAllocatorBySelector(...);
int igMetaObject_Create(...);
int igObject_InitHeader(struct Obj *);
void igMetaObject_RunStaticInit(...);
int igMetaObject_RegisterClass(...);
int ViewerLibrary_MarkRegistered(...);
int FUN_00459380(...);
int FUN_0045aaf0(...);
int igMetaObject_CreateFields(...);
void *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);

void FUN_0045a9a0(void);
void igViewerSceneInfoManagerController_Register(void);
void thunk_igViewerSceneInfoManagerController_GetMetaObject(void);
void igViewerSceneInfoManagerController_InitFields(void);

extern struct G *g_igViewerSceneInfoManagerController_metaObject[4];
extern int DAT_0058c928[4];
extern int DAT_00587040[4];
extern int DAT_00542540[4];
extern void * DAT_00586dc8[4];
extern int DAT_004d0e68[4];
extern int DAT_004d0e70[4];
extern int DAT_004d0e78[4];
extern int DAT_004d0e80[4];
extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char g_igViewerSceneInfoManagerController_callbackList[];
extern char igViewerSceneInfoManagerController_className[];

int FUN_0045a8c0(void) {
    if (DAT_0058c928[0] == 0) {
        DAT_0058c928[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c928[0];
}

void *igViewerSceneInfoManagerController_GetMetaObject(void) {
    struct G *g = g_igViewerSceneInfoManagerController_metaObject[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0045a9a0();
    }
    return g_igViewerSceneInfoManagerController_metaObject[0];
}

int igViewerSceneInfoManagerController_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542540[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0045a9a0(void)
{
    igMetaObject_RunStaticInit(igViewerSceneInfoManagerController_Register);
}

void igViewerSceneInfoManagerController_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerSceneInfoManagerController_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igViewerSceneInfoManagerController_GetMetaObject,
        igViewerSceneInfoManagerController_className,
        0x14, /* instance size */
        igViewerSceneInfoManagerController_GetVTable,
        &igViewerSceneInfoManagerController_InitFields,
        0, /* extra callback item */
        g_igViewerSceneInfoManagerController_callbackList /* callback list */
    );
}

void thunk_igViewerSceneInfoManagerController_GetMetaObject(void) {
    igViewerSceneInfoManagerController_GetMetaObject();
}

void igViewerSceneInfoManagerController_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c928[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0e68[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00459380();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0045aaf0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004d0e70[0], &DAT_004d0e78[0], &DAT_004d0e80[0], temp_s2);
}

}