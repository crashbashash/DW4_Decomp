extern char igObject_GetMetaObject_ParentAccessor[];
extern char igBoundingSphereMaker_GetVTable[];
extern char thunk_igBoundingSphereMaker_GetMetaObject[];
extern char igObject_Register[];
extern char g_igBoundingSphereMaker_callbackList[];
extern char igBoundingSphereMaker_className[];
extern char g_igBoundingSphereMaker_metaObject[];
int CollisionLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBoundingSphereMaker_InitFields();

void igBoundingSphereMaker_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoundingSphereMaker_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBoundingSphereMaker_GetMetaObject,
        igBoundingSphereMaker_className,
        0xC, /* instance size */
        igBoundingSphereMaker_GetVTable,
        &igBoundingSphereMaker_InitFields,
        0, /* extra callback item */
        g_igBoundingSphereMaker_callbackList /* callback list */
    );
}
