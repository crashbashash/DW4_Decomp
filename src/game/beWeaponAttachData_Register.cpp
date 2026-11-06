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
extern igMetaObject *g_beWeaponAttachData_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beWeaponAttachData_GetMetaObject(void);
extern const char beWeaponAttachData_className[];
int beWeaponAttachData_GetVTable(void);
void beWeaponAttachData_InitFields(void);
extern char g_beWeaponAttachData_callbackList[];
void *beWeaponAttachData_Register(void);
}

void *beWeaponAttachData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeaponAttachData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beWeaponAttachData_GetMetaObject,
        beWeaponAttachData_className,
        0x10, /* instance size */
        beWeaponAttachData_GetVTable,
        beWeaponAttachData_InitFields,
        0, /* extra callback item */
        g_beWeaponAttachData_callbackList /* callback list */
    );
}
