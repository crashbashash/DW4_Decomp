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
extern igMetaObject *g_beWeapon_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beWeapon_GetMetaObject(void);
extern const char beWeapon_className[];
int beWeapon_GetVTable(void);
void beWeapon_InitFields(void);
extern char g_beWeapon_callbackList[];
void *beWeapon_Register(void);
}

void *beWeapon_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeapon_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beWeapon_GetMetaObject,
        beWeapon_className,
        0x24, /* instance size */
        beWeapon_GetVTable,
        beWeapon_InitFields,
        0, /* extra callback item */
        g_beWeapon_callbackList /* callback list */
    );
}
