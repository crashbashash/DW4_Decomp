unsigned char g_ViewerLibrary_registered;

void ViewerLibrary_MarkRegistered(void) {
    if (g_ViewerLibrary_registered == 0) {
        g_ViewerLibrary_registered = 1;
    }
}

igMetaObject *g_igViewerStatisticsManager_metaObject;
igMetaField *g_igViewerStatisticsManager_itemsMetaField;
igMetaField *g_igViewerStatisticsManager_visualContextMetaField;
igMetaField *g_igViewerStatisticsManager_guiFactoryMetaField;
igMetaField *g_igViewerStatisticsManager_menuMetaField;
igMetaField *g_igViewerStatisticsManager_boxComponentMetaField;
igMetaField *g_igViewerStatisticsManager_stringMetaField;
igMetaField *g_igViewerStatisticsManager_recordStatisticMaximumMetaField;
igMetaField *g_igViewerStatisticsManager_attrMetaObjectsMetaField;
igMetaField *g_igViewerStatisticsManager_extraSgStatisticsMetaField;
igMetaField *g_igViewerStatisticsManager_attrCountMetaField;
igMetaField *g_igViewerStatisticsManager_displayListAttrCountMetaField;
igMetaField *g_igViewerStatisticsManager_textureAttrCountMetaField;
igMetaField *g_igViewerStatisticsManager_geometryAttrCountMetaField;
igMetaField *g_igViewerStatisticsManager_geometrySetAttrCountMetaField;
igMetaField *g_igViewerStatisticsManager_mvmAttrCountMetaField;

igMetaObject *FUN_004586a0(void) {
    if (g_igViewerStatisticsManager_metaObject == 0) {
        g_igViewerStatisticsManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igViewerStatisticsManager_metaObject;
}

