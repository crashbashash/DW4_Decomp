struct G { char pad[36]; int f; };
struct Obj { int *vt; char pad[8]; char *m; };

extern "C" {
int igMetaObject_CreateInstance(int, int);
int igObject_InitHeader(struct Obj *);
int StringChunk_ReleaseHeader(...);
void igMetaObject_RunStaticInit(...);
int igMetaObject_RegisterClass(...);
int ViewerLibrary_MarkRegistered(...);
int igStringMetaField_SetDefaultText(int, int *);
int igMetaObject_CreateFields(void *, int *, int);
int igMetaObject_GetFieldAt(void *, int);
int igMetaObject_GetFieldCount(void *);
int igMetaObject_NameFields(void *, int *, int *, int *, int);

void FUN_0045a7a0(void);
void igViewerLoadingFileMessage_Register(void);
void thunk_igViewerLoadingFileMessage_GetMetaObject(void);
void igViewerLoadingFileMessage_InitFields(void);

extern struct G *g_igViewerLoadingFileMessage_metaObject[4];
extern int DAT_0058c910[4];
extern int DAT_00542100[4];
extern void * DAT_00586dc8[4];
extern int DAT_004d0e38[4];
extern int DAT_004d0e40[4];
extern int DAT_004d0e48[4];
extern int DAT_004d0e50[4];
extern int DAT_0051eef0[4];
extern char igMessage_GetPublishedMetaObject[];
extern char igMessage_Register[];
extern char igViewerLoadingFileMessage_className[];

void FUN_0045a680(int arg0) {
    FUN_0045a7a0();
    igMetaObject_CreateInstance(*(int *)0x58C910, arg0);
}

struct G *igViewerLoadingFileMessage_GetMetaObject(void) {
    struct G *g = g_igViewerLoadingFileMessage_metaObject[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0045a7a0();
    return g_igViewerLoadingFileMessage_metaObject[0];
}

int igViewerLoadingFileMessage_GetVTable(void) {
    struct Obj obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542100[0];
    obj.m = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00542100[0];
    if (&obj.m != 0) {
        o = obj.m;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void FUN_0045a7a0(void)
{
    igMetaObject_RunStaticInit(igViewerLoadingFileMessage_Register);
}

void igViewerLoadingFileMessage_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewerLoadingFileMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewerLoadingFileMessage_GetMetaObject,
        igViewerLoadingFileMessage_className,
        0x10, /* instance size */
        igViewerLoadingFileMessage_GetVTable,
        &igViewerLoadingFileMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igViewerLoadingFileMessage_GetMetaObject(void) {
    igViewerLoadingFileMessage_GetMetaObject();
}

void igViewerLoadingFileMessage_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c910[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004d0e38[0], 2);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), &DAT_0051eef0[0]);
    igMetaObject_NameFields(temp_s0, &DAT_004d0e40[0], &DAT_004d0e48[0], &DAT_004d0e50[0], temp_s1);
}

}