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
extern igMetaObject *g_beWeaponSeqDataList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *beWeaponSeqDataList_GetMetaObject(void);
extern const char beWeaponSeqDataList_className[];
int beWeaponSeqDataList_GetVTable(void);
extern char g_beWeaponSeqDataList_callbackList[];
void *beWeaponSeqDataList_Register(void);
}

void *beWeaponSeqDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeaponSeqDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beWeaponSeqDataList_GetMetaObject,
        beWeaponSeqDataList_className,
        0x14, /* instance size */
        beWeaponSeqDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beWeaponSeqDataList_callbackList /* callback list */
    );
}
