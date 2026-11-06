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
extern igMetaObject *g_beWeaponInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beWeaponInfoRam_GetMetaObject(void);
extern const char beWeaponInfoRam_className[];
int beWeaponInfoRam_GetVTable(void);
void *beWeaponInfoRam_Register(void);
}

void *beWeaponInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeaponInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beWeaponInfoRam_GetMetaObject,
        beWeaponInfoRam_className,
        0x2c, /* instance size */
        beWeaponInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
