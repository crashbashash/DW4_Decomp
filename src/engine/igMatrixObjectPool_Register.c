/* 0x00199dc0 igMatrixObjectPool_Register: registers class igMatrixObjectPool with the object system, derived from igObjectPool.
 * The igMetaObject_RegisterClass arguments are laid out per
 * docs/engine/reflection-metadata.md section 1; names from data/reflection.json. */
extern char igObjectPool_Register[];
extern char igObjectPool_GetPublishedMetaObject_00197aa0[];
extern char igMatrixObjectPool_GetVTable[];
extern char thunk_igMatrixObjectPool_GetMetaObject[];
extern char g_igMatrixObjectPool_callbackList_0048b720[];
extern char s_igMatrixObjectPool_className_004e1d20[];
extern char g_igMatrixObjectPool_metaObject_00561590[];
int GpFlag_SetOnce_00194380();
int igMetaObject_RegisterClass();

void igMatrixObjectPool_Register(void) {
    GpFlag_SetOnce_00194380();
    igMetaObject_RegisterClass(
        0,                                            /* abstract state (0: the vtable getter runs, 1: abstract class) */
        g_igMatrixObjectPool_metaObject_00561590,     /* published MetaObject slot */
        igObjectPool_Register,                        /* base class registrar */
        igObjectPool_GetPublishedMetaObject_00197aa0, /* base class MetaObject accessor */
        thunk_igMatrixObjectPool_GetMetaObject,       /* own MetaObject accessor (stored at +0x54) */
        s_igMatrixObjectPool_className_004e1d20,      /* class name */
        0x20,                                         /* instance size */
        igMatrixObjectPool_GetVTable,                 /* vtable getter */
        0,                                            /* field adder */
        0,                                            /* extra callback item */
        g_igMatrixObjectPool_callbackList_0048b720    /* callback list */
    );
}
