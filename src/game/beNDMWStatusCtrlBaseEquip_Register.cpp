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
extern igMetaObject *g_beNDMWStatusCtrlBaseEquip_metaObject[];
void *beNDMWWindowCtrl_Register(void);
igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusCtrlBaseEquip_GetMetaObject(void);
extern const char beNDMWStatusCtrlBaseEquip_className[];
void beNDMWStatusCtrlBaseEquip_InitFields(void);
extern char pA6_2[];
void *beNDMWStatusCtrlBaseEquip_Register(void);
}

void *beNDMWStatusCtrlBaseEquip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beNDMWStatusCtrlBaseEquip_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlBaseEquip_GetMetaObject,
        beNDMWStatusCtrlBaseEquip_className,
        0x7c, /* instance size */
        0,
        beNDMWStatusCtrlBaseEquip_InitFields,
        0, /* extra callback item */
        pA6_2 /* callback list */
    );
}
