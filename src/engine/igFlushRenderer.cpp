#include "dw4/reflected.h"

extern "C" {
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; int w[3]; char b[12]; };

void FUN_00233b80(void);
void igFlushRenderer_Register(void);
void thunk_igFlushRenderer_GetMetaObject(void);
int igObject_Destroy(...);
int igObject_InitHeader(...);
void igMetaObject_RunStaticInit(...);
int InsightLibrary_MarkRegistered(...);
int igMetaObject_RegisterClass(...);
extern igMetaObject *g_igFlushRenderer_metaObject[4];
extern int DAT_0052ca80[4];
extern int DAT_0052d060[4];
extern void *DAT_00586dc8[4];
extern char igRenderer_GetPublishedMetaObject[];
extern char igRenderer_Register[];
extern char igFlushRenderer_className[];

/* Registers the class first when the slot is empty or its igMetaObject._validity (+36) lacks the
 * ready bit (mask 4), then returns the published MetaObject. */
igMetaObject *igFlushRenderer_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igFlushRenderer_metaObject[0] != 0) {
        ready = (g_igFlushRenderer_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_00233b80();
done:
    return g_igFlushRenderer_metaObject[0];
}

int igFlushRenderer_GetVTable(void) {
    union U u;
    int temp_s0;
    S_ref *q1;


    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_0052d060[0]);
    q1 = (S_ref *)&u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_0052ca80[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052d060[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void FUN_00233b80(void)
{
    igMetaObject_RunStaticInit(igFlushRenderer_Register);
}

void igFlushRenderer_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFlushRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igFlushRenderer_GetMetaObject,
        igFlushRenderer_className,
        0xC, /* instance size */
        igFlushRenderer_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igFlushRenderer_GetMetaObject(void) {
    igFlushRenderer_GetMetaObject();
}
}
