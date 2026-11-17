#ifndef DW4_IGSMARTPOINTERDESTRUCT_H
#define DW4_IGSMARTPOINTERDESTRUCT_H
#include "dw4/igSmartPointer.h"

struct igStringRef;

/* The out-of-line igSmartPointer<T> destructors other units call by name: each releases the held
 * object, then frees the pointer itself when the delete flag is positive. Every T has the same body;
 * T only names the symbol. igStringRef_Destruct is the same for an interned-string reference. */
extern "C" {
igSmartPointer<igObject> *igSmartPointer_bePadManager_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_beDataBase_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_beDataObjInt_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_beModelCtrlData_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoAI_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoDataTrc_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoHitBody_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoRideOn_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_beModelCtrlMoveObjectList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_beModelCtrlNode2_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_beModelCtrlSubCom_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *GameMain_igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igAABox_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igActorList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igAnimationDatabase_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igAppearanceList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igAttrList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igAttrSet_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igBlendFunctionAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igBlendStateAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igBoolList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igCharList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igCharMetricsList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igColorAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igDependencyList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igDirectoryList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igDirectory_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igFile_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igFloatList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igGeometryList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igGeometry_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igGroup_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igGuiComponent_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igImage_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igInfoList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igIntListList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igIntList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igLightingStateAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igLongList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igMatrix44fList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igMemoryPool_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igMetaFieldList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igMetaField_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igMetaObjectList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igMetaObject_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igMovieManager_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igNamedObjectList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igNodeList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igNode_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igObjectList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igPointerList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igRegistry_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igRendererOrderedList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igSceneInfo_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igShortList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igStringObjList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igStringObj_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igStringRefListList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igStringRefList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igTextureList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igThread_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igTransform_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igVec3fList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igVertexArray_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igVisualContext_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igStringRef *igStringRef_Destruct(igStringRef *self, short deleteFlag);
}

#endif
