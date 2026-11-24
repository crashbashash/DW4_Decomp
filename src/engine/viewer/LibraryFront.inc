unsigned char g_ViewerLibrary_registered;

void ViewerLibrary_MarkRegistered(void) {
    if (g_ViewerLibrary_registered == 0) {
        g_ViewerLibrary_registered = 1;
    }
}

namespace Gap {
namespace Viewer {

igMetaObject *igViewerStatisticsManager::_Meta;
igMetaField *igViewerStatisticsManager::k_items;
igMetaField *igViewerStatisticsManager::k_visualContext;
igMetaField *igViewerStatisticsManager::k_guiFactory;
igMetaField *igViewerStatisticsManager::k_menu;
igMetaField *igViewerStatisticsManager::k_boxComponent;
igMetaField *igViewerStatisticsManager::k_string;
igMetaField *igViewerStatisticsManager::k_recordStatisticMaximum;
igMetaField *igViewerStatisticsManager::k_attrMetaObjects;
igMetaField *igViewerStatisticsManager::k_extraSgStatistics;
igMetaField *igViewerStatisticsManager::k_attrCount;
igMetaField *igViewerStatisticsManager::k_displayListAttrCount;
igMetaField *igViewerStatisticsManager::k_textureAttrCount;
igMetaField *igViewerStatisticsManager::k_geometryAttrCount;
igMetaField *igViewerStatisticsManager::k_geometrySetAttrCount;
igMetaField *igViewerStatisticsManager::k_mvmAttrCount;

igMetaObject *igViewerStatisticsManager::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}
}
}

