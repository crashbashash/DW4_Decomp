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
extern igMetaObject *g_beNDMWStatusSubMenu_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusSubMenu_GetMetaObject(void);
extern const char beNDMWStatusSubMenu_className[];
int beNDMWStatusSubMenu_GetVTable(void);
void beNDMWStatusSubMenu_InitFields(void);
extern char g_beNDMWStatusSubMenu_callbackList[];
void *beNDMWStatusSubMenu_Register(void);
}

void *beNDMWStatusSubMenu_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusSubMenu_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusSubMenu_GetMetaObject,
        beNDMWStatusSubMenu_className,
        0x68, /* instance size */
        beNDMWStatusSubMenu_GetVTable,
        beNDMWStatusSubMenu_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusSubMenu_callbackList /* callback list */
    );
}
