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
extern igMetaObject *g_beWeaponInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beWeaponInfo_GetMetaObject(void);
extern const char beWeaponInfo_className[];
int beWeaponInfo_GetVTable(void);
void beWeaponInfo_InitFields(void);
extern char g_beWeaponInfo_callbackList[];
void *beWeaponInfo_Register(void);
}

void *beWeaponInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeaponInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beWeaponInfo_GetMetaObject,
        beWeaponInfo_className,
        0x28, /* instance size */
        beWeaponInfo_GetVTable,
        beWeaponInfo_InitFields,
        0, /* extra callback item */
        g_beWeaponInfo_callbackList /* callback list */
    );
}
