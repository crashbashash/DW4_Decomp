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
extern igMetaObject *g_beWeaponSeqData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beWeaponSeqData_GetMetaObject(void);
extern const char beWeaponSeqData_className[];
int beWeaponSeqData_GetVTable(void);
void beWeaponSeqData_InitFields(void);
void *beWeaponSeqData_Register(void);
}

void *beWeaponSeqData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeaponSeqData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beWeaponSeqData_GetMetaObject,
        beWeaponSeqData_className,
        0x10, /* instance size */
        beWeaponSeqData_GetVTable,
        beWeaponSeqData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
