struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beNDMWItemWeapon_metaObject[];
void *beNDMWItemRevisionPocketBase_Register(void);
igMetaObject *beNDMWItemRevisionPocketBase_GetPublishedMetaObject(void);
igMetaObject *beNDMWItemWeapon_GetMetaObject(void);
extern const char beNDMWItemWeapon_className[];
int beNDMWItemWeapon_GetVTable(void);
void *beNDMWItemWeapon_Register(void);
}

void *beNDMWItemWeapon_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemWeapon_metaObject,
        beNDMWItemRevisionPocketBase_Register,
        beNDMWItemRevisionPocketBase_GetPublishedMetaObject,
        beNDMWItemWeapon_GetMetaObject,
        beNDMWItemWeapon_className,
        0x1c, /* instance size */
        beNDMWItemWeapon_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
