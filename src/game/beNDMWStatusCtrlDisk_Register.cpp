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
extern igMetaObject *g_beNDMWStatusCtrlDisk_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusCtrlDisk_GetMetaObject(void);
extern const char beNDMWStatusCtrlDisk_className[];
int beNDMWStatusCtrlDisk_GetVTable(void);
void beNDMWStatusCtrlDisk_InitFields(void);
extern char g_beNDMWStatusCtrlDisk_callbackList[];
void *beNDMWStatusCtrlDisk_Register(void);
}

void *beNDMWStatusCtrlDisk_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlDisk_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlDisk_GetMetaObject,
        beNDMWStatusCtrlDisk_className,
        0x6c, /* instance size */
        beNDMWStatusCtrlDisk_GetVTable,
        beNDMWStatusCtrlDisk_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlDisk_callbackList /* callback list */
    );
}
