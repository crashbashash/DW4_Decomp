#ifndef DW4_IGSMARTPOINTERDESTRUCT_H
#define DW4_IGSMARTPOINTERDESTRUCT_H
#include "dw4/igSmartPointer.h"

/* The out-of-line igSmartPointer<T> destructors other units call by name: each releases the held
 * object, then frees the pointer itself when the delete flag is positive. Every T has the same body;
 * T only names the symbol. */
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
}

#endif
