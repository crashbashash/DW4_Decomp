void ViewerLibrary_MarkRegistered(void) {
    if (g_ViewerLibrary_registered == 0) {
        g_ViewerLibrary_registered = 1;
    }
}

igMetaObject *FUN_004586a0(void) {
    if (g_igViewerStatisticsManager_metaObject[0] == 0) {
        g_igViewerStatisticsManager_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igViewerStatisticsManager_metaObject[0];
}

