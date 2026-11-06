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
extern igMetaObject *g_beNDMWStatusCtrlBit_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusCtrlBit_GetMetaObject(void);
extern const char beNDMWStatusCtrlBit_className[];
int beNDMWStatusCtrlBit_GetVTable(void);
void beNDMWStatusCtrlBit_InitFields(void);
extern char g_beNDMWStatusCtrlBit_callbackList[];
void *beNDMWStatusCtrlBit_Register(void);
}

void *beNDMWStatusCtrlBit_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusCtrlBit_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlBit_GetMetaObject,
        beNDMWStatusCtrlBit_className,
        0x58, /* instance size */
        beNDMWStatusCtrlBit_GetVTable,
        beNDMWStatusCtrlBit_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlBit_callbackList /* callback list */
    );
}
