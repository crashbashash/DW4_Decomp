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
extern igMetaObject *g_beNDMWStatusSubSlot_metaObject[];
void *beNDMWStatusCtrlBaseEquip_Register(void);
igMetaObject *beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatusSubSlot_GetMetaObject(void);
extern const char beNDMWStatusSubSlot_className[];
int beNDMWStatusSubSlot_GetVTable(void);
void *beNDMWStatusSubSlot_Register(void);
}

void *beNDMWStatusSubSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatusSubSlot_metaObject,
        beNDMWStatusCtrlBaseEquip_Register,
        beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject,
        beNDMWStatusSubSlot_GetMetaObject,
        beNDMWStatusSubSlot_className,
        0x7c, /* instance size */
        beNDMWStatusSubSlot_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
