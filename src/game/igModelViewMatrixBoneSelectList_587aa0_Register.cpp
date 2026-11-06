struct igMetaObject;
extern "C" {
void BecLibrary_MarkRegistered(void);
void *igMetaObject_RegisterClass(
        int abstractState,
        igMetaObject **slot,
        void *(*baseRegister)(void),
        igMetaObject *(*baseMetaObject)(void),
        igMetaObject *(*getMetaObject)(void),
        const char *className,
        int instanceSize,
        int (*getVTable)(void),
        void (*initFields)(void),
        void (*callbackItem)(void),
        void *callbackList);
extern igMetaObject *g_igModelViewMatrixBoneSelectList_metaObject_00587aa0[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *igModelViewMatrixBoneSelectList_587aa0_GetMetaObject(void);
extern const char igModelViewMatrixBoneSelectList_className_2[];
int igModelViewMatrixBoneSelectList_587aa0_GetVTable(void);
extern char g_igModelViewMatrixBoneSelectList_587aa0_callbackList[];
void *igModelViewMatrixBoneSelectList_587aa0_Register(void);
}

void *igModelViewMatrixBoneSelectList_587aa0_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igModelViewMatrixBoneSelectList_metaObject_00587aa0,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igModelViewMatrixBoneSelectList_587aa0_GetMetaObject,
        igModelViewMatrixBoneSelectList_className_2,
        0x14, /* instance size */
        igModelViewMatrixBoneSelectList_587aa0_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixBoneSelectList_587aa0_callbackList /* callback list */
    );
}
