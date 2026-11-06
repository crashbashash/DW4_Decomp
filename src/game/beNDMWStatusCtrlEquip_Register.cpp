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
extern igMetaObject *g_beNDMWStatusCtrlEquip_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusCtrlEquip_GetMetaObject(void);
extern const char beNDMWStatusCtrlEquip_className[];
int beNDMWStatusCtrlEquip_GetVTable(void);
void beNDMWStatusCtrlEquip_InitFields(void);
void *beNDMWStatusCtrlEquip_Register(void);
}

void *beNDMWStatusCtrlEquip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlEquip_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlEquip_GetMetaObject,
        beNDMWStatusCtrlEquip_className,
        0x58, /* instance size */
        beNDMWStatusCtrlEquip_GetVTable,
        beNDMWStatusCtrlEquip_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
