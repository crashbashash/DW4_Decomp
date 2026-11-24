#ifndef DW4_NDMW_LIBRARY_H
#define DW4_NDMW_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/support/ClassRegistration.h"
#include "dw4/game/ndmw/beLoadIntf2ComMdlData.h"
#include "dw4/game/ndmw/beNDMWAfsSetup.h"
#include "dw4/game/ndmw/beNDMWAfsSetupInfo.h"
#include "dw4/game/ndmw/beNDMWAfsStageLoad.h"
#include "dw4/game/ndmw/beNDMWDegiData.h"
#include "dw4/game/ndmw/beNDMWGameRam.h"
#include "dw4/game/ndmw/beNDMWGameRamInfo.h"
#include "dw4/game/ndmw/beNDMWGameRamInfoRam.h"
#include "dw4/game/ndmw/beNDMWItemAbilityChip.h"
#include "dw4/game/ndmw/beNDMWItemBaseList.h"
#include "dw4/game/ndmw/beNDMWItemBlueArmor.h"
#include "dw4/game/ndmw/beNDMWItemDisk.h"
#include "dw4/game/ndmw/beNDMWItemImportant.h"
#include "dw4/game/ndmw/beNDMWItemInstant.h"
#include "dw4/game/ndmw/beNDMWItemWaza.h"
#include "dw4/game/ndmw/beNDMWItemWeapon.h"
#include "dw4/game/ndmw/beNDMWItemYellowArmor.h"
#include "dw4/game/ndmw/beNDMWListCtrl.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2CommonIntf.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2CtrlData.h"
#include "dw4/game/ndmw/beNDMWLoadCtrl2Info.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2ComMdlCtrl.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2CtrlData.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2DataSelIntf.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2DegiState.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2DegiStateCtrl.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2Diffselect.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2Info.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2MakeChr.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2MesWin.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2NameSel.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2SelSlot.h"
#include "dw4/game/ndmw/beNDMWLoadIntf2TextOrder.h"
#include "dw4/game/ndmw/beNDMWLoadSavePlWork.h"
#include "dw4/game/ndmw/beNDMWLoadSlotPlayer.h"
#include "dw4/game/ndmw/beNDMWLogo.h"
#include "dw4/game/ndmw/beNDMWLogoCtrlData.h"
#include "dw4/game/ndmw/beNDMWLogoInfo.h"
#include "dw4/game/ndmw/beNDMWMcSlotGC.h"
#include "dw4/game/ndmw/beNDMWMcSlotPS2.h"
#include "dw4/game/ndmw/beNDMWMcSlotXbox.h"
#include "dw4/game/ndmw/beNDMWMcUtilCtrl.h"
#include "dw4/game/ndmw/beNDMWMdlEBullet.h"
#include "dw4/game/ndmw/beNDMWMdlEffect.h"
#include "dw4/game/ndmw/beNDMWMdlEnemy.h"
#include "dw4/game/ndmw/beNDMWMdlEnemyInfoWork.h"
#include "dw4/game/ndmw/beNDMWMdlItem.h"
#include "dw4/game/ndmw/beNDMWMdlItemInfoWork.h"
#include "dw4/game/ndmw/beNDMWMdlMapBase.h"
#include "dw4/game/ndmw/beNDMWMdlMapCursor.h"
#include "dw4/game/ndmw/beNDMWMdlObject.h"
#include "dw4/game/ndmw/beNDMWMdlPBullet.h"
#include "dw4/game/ndmw/beNDMWMdlPEBase.h"
#include "dw4/game/ndmw/beNDMWMdlPEBaseInfoWork.h"
#include "dw4/game/ndmw/beNDMWMdlPlayer.h"
#include "dw4/game/ndmw/beNDMWMdlPlayer2.h"
#include "dw4/game/ndmw/beNDMWMdlPlayer2InfoWork.h"
#include "dw4/game/ndmw/beNDMWMdlPlayerInfoWork.h"
#include "dw4/game/ndmw/beNDMWPanelObject.h"
#include "dw4/game/ndmw/beNDMWPanelObjectItem.h"
#include "dw4/game/ndmw/beNDMWPanelObjectStat.h"
#include "dw4/game/ndmw/beNDMWPanelObjectWaza.h"
#include "dw4/game/ndmw/beNDMWPanelWaza.h"
#include "dw4/game/ndmw/beNDMWPanelWazaInfo.h"
#include "dw4/game/ndmw/beNDMWPanelWazaInfoWork.h"
#include "dw4/game/ndmw/beNDMWSaveCtrl.h"
#include "dw4/game/ndmw/beNDMWSaveCtrlCtrlData.h"
#include "dw4/game/ndmw/beNDMWSaveCtrlInfo.h"
#include "dw4/game/ndmw/beNDMWSaveIntf.h"
#include "dw4/game/ndmw/beNDMWSaveIntfCtrlData.h"
#include "dw4/game/ndmw/beNDMWSaveIntfInfo.h"
#include "dw4/game/ndmw/beNDMWShinkaObject.h"
#include "dw4/game/ndmw/beNDMWShopCtrl00.h"
#include "dw4/game/ndmw/beNDMWShopCtrl10.h"
#include "dw4/game/ndmw/beNDMWShopCtrl30.h"
#include "dw4/game/ndmw/beNDMWShopCtrl40.h"
#include "dw4/game/ndmw/beNDMWShopCtrl50.h"
#include "dw4/game/ndmw/beNDMWShopCtrlA0.h"
#include "dw4/game/ndmw/beNDMWShopCtrlA1.h"
#include "dw4/game/ndmw/beNDMWShopCtrlA2.h"
#include "dw4/game/ndmw/beNDMWShopCtrlDeviceSell.h"
#include "dw4/game/ndmw/beNDMWShopCtrlDigilabo.h"
#include "dw4/game/ndmw/beNDMWShopCtrlDiskSell.h"
#include "dw4/game/ndmw/beNDMWShopCtrlEditBit.h"
#include "dw4/game/ndmw/beNDMWShopCtrlEvolve.h"
#include "dw4/game/ndmw/beNDMWShopCtrlSales.h"
#include "dw4/game/ndmw/beNDMWShopCtrlSell.h"
#include "dw4/game/ndmw/beNDMWShopCtrlXdataChip.h"
#include "dw4/game/ndmw/beNDMWShopDevice.h"
#include "dw4/game/ndmw/beNDMWShopJunk.h"
#include "dw4/game/ndmw/beNDMWShopSelect00.h"
#include "dw4/game/ndmw/beNDMWShopSelect01.h"
#include "dw4/game/ndmw/beNDMWShopSelect02.h"
#include "dw4/game/ndmw/beNDMWShopSelect03.h"
#include "dw4/game/ndmw/beNDMWShopSelect11.h"
#include "dw4/game/ndmw/beNDMWShopSelect34.h"
#include "dw4/game/ndmw/beNDMWShopSelect52.h"
#include "dw4/game/ndmw/beNDMWShopSelectA0.h"
#include "dw4/game/ndmw/beNDMWShopSelectB0.h"
#include "dw4/game/ndmw/beNDMWShopTitle00.h"
#include "dw4/game/ndmw/beNDMWShopTitle01.h"
#include "dw4/game/ndmw/beNDMWShopTitle03.h"
#include "dw4/game/ndmw/beNDMWStageCtl.h"
#include "dw4/game/ndmw/beNDMWStageCtlInfo.h"
#include "dw4/game/ndmw/beNDMWStatus.h"
#include "dw4/game/ndmw/beNDMWStatusCtrl00.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlBaseEquip.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlBit.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlD0.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlDisk.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlEquip.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlFlag.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlFolder.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlSendBit.h"
#include "dw4/game/ndmw/beNDMWStatusCtrlSkill.h"
#include "dw4/game/ndmw/beNDMWStatusInfo.h"
#include "dw4/game/ndmw/beNDMWStatusInfoWork.h"
#include "dw4/game/ndmw/beNDMWStatusMainSlot.h"
#include "dw4/game/ndmw/beNDMWStatusPowerSocket.h"
#include "dw4/game/ndmw/beNDMWStatusSelect00.h"
#include "dw4/game/ndmw/beNDMWStatusSelect01.h"
#include "dw4/game/ndmw/beNDMWStatusSelectE0.h"
#include "dw4/game/ndmw/beNDMWStatusSelectE1.h"
#include "dw4/game/ndmw/beNDMWStatusSubMenu.h"
#include "dw4/game/ndmw/beNDMWStatusSubSlot.h"
#include "dw4/game/ndmw/beNDMWStatusTitle00.h"
#include "dw4/game/ndmw/beNDMWStatusTitle01.h"
#include "dw4/game/ndmw/beNDMWStatusTitle02.h"
#include "dw4/game/ndmw/beNDMWStatusTitle03.h"
#include "dw4/game/ndmw/beNDMWStatusTitle04.h"
#include "dw4/game/ndmw/beNDMWTitle2.h"
#include "dw4/game/ndmw/beNDMWTitle2CtrlData.h"
#include "dw4/game/ndmw/beNDMWTitle2Info.h"
#include "dw4/game/ndmw/beNDMWTitle2Option.h"
#include "dw4/game/ndmw/beNDMWWindowCtrl.h"
#include "dw4/game/ndmw/beNDMWWindowList.h"
#include "dw4/game/ndmw/beNDMWWindowSelect.h"
#include "dw4/game/ndmw/beNDMWWindowTitle.h"
#include "dw4/game/ndmw/libNdmwRuntimePlugin.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/beBaseInfo.h"
#include "dw4/game/beBaseInfoData.h"
#include "dw4/game/beBaseInfoManager.h"
#include "dw4/game/beBaseInfoRam.h"
#include "dw4/game/beDBManager.h"
#include "dw4/game/beDataBase.h"
#include "dw4/game/beDataObjList.h"
#include "dw4/game/beDataObjListList.h"
#include "dw4/game/beLua.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beModelCtrl.h"
#include "dw4/game/beModelCtrlInfoWork.h"
#include "dw4/game/bePadManager.h"
#include "dw4/game/beSaveDataDeliver.h"
#include "dw4/game/beSystem.h"
#include "dw4/audio/igAdxAfsFileList.h"
#include "dw4/core/igBoolList.h"
#include "dw4/gui/igBoxComponent.h"
#include "dw4/core/igDataLists.h"
#include "dw4/gui/igGuiComponent.h"
#include "dw4/core/igInfo.h"
#include "dw4/core/igInfoList.h"
#include "dw4/insight/igInfoManager.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/insight/igInsightPlugin.h"
#include "dw4/core/igIntList.h"
#include "dw4/core/igMemory.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igMetaObject.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igObjectList.h"
#include "dw4/core/igObjectSystem.h"
#include "dw4/core/igStringRefList.h"
#include "dw4/viewer/igViewerSceneInfoManager.h"
#include "dw4/core/igObjectDispatchView.h"
#include "dw4/core/igTDataList.h"
/* kept local: the metafield types' Create functions have no include/dw4 home; typed as FieldFactory. */
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igCharArrayMetaField.h"
#include "dw4/core/igFloatMetaField.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igLongMetaField.h"
#include "dw4/core/igMemoryRefMetaField.h"
#include "dw4/core/igMetaEnum.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igStringMetaField.h"
#include "dw4/core/igUnsignedShortArrayMetaField.h"
#include "dw4/maths/igVec3fMetaField.h"
#include "dw4/core/igIntListList.h"
#include "dw4/core/igCharMetaField.h"

static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }

extern "C" void NdmwLibrary_MarkRegistered(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWStageCtl_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWTitle2_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWLoadIntf2_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWGameRam_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWStatus_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPlayer_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPBullet_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEBullet_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlObject_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEffect_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlMapCursor_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlMapBase_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEffect_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlItem_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlObject_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEBullet_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEnemy_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPBullet_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPlayer2_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPlayer_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWStatus_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWGameRam_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWSaveIntf_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWSaveCtrl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWLoadIntf2_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWLoadCtrl2_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWTitle2_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWLogo_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWPanelWaza_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWStageCtl_Construct(igSmartPointer<igObject> *self);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWAfsSetup_Construct(igSmartPointer<igObject> *self);
extern "C" void libNdmwRuntimePlugin_EnsureRegistered(void);
extern "C" int libNdmwRuntimePlugin_GetVTable(void);
extern "C" CallbackArray *libNdmwRuntimePlugin_Register(void);
extern "C" void libNdmwRuntimePlugin_GetMetaObjectFunction(void);
extern "C" void libNdmwRuntimePlugin_InitFields(void);
/* igInsightPlugin, constructed out of line; its vtable pointer is where igObject keeps _vtable. */
struct InsightPluginView { virtual void firstSlot(); unsigned int refCount; InsightPluginView(); };
/* The object references of libNdmwRuntimePlugin, one class per referenced type. */
struct AfsSetupField { int *p; AfsSetupField() throw(); ~AfsSetupField(); };
struct StageCtlField { int *p; StageCtlField() throw(); ~StageCtlField(); };
struct PanelWazaField { int *p; PanelWazaField() throw(); ~PanelWazaField(); };
struct LogoField { int *p; LogoField() throw(); ~LogoField(); };
struct Title2Field { int *p; Title2Field() throw(); ~Title2Field(); };
struct LoadCtrl2Field { int *p; LoadCtrl2Field() throw(); ~LoadCtrl2Field(); };
struct LoadIntf2Field { int *p; LoadIntf2Field() throw(); ~LoadIntf2Field(); };
struct SaveCtrlField { int *p; SaveCtrlField() throw(); ~SaveCtrlField(); };
struct SaveIntfField { int *p; SaveIntfField() throw(); ~SaveIntfField(); };
struct GameRamField { int *p; GameRamField() throw(); ~GameRamField(); };
struct StatusField { int *p; StatusField() throw(); ~StatusField(); };
struct MdlPlayerField { int *p; MdlPlayerField() throw(); ~MdlPlayerField(); };
struct MdlPlayer2Field { int *p; MdlPlayer2Field() throw(); ~MdlPlayer2Field(); };
struct MdlPBulletField { int *p; MdlPBulletField() throw(); ~MdlPBulletField(); };
struct MdlEnemyField { int *p; MdlEnemyField() throw(); ~MdlEnemyField(); };
struct MdlEBulletField { int *p; MdlEBulletField() throw(); ~MdlEBulletField(); };
struct MdlObjectField { int *p; MdlObjectField() throw(); ~MdlObjectField(); };
struct MdlItemField { int *p; MdlItemField() throw(); ~MdlItemField(); };
struct MdlEffectField { int *p; MdlEffectField() throw(); ~MdlEffectField(); };
struct MdlMapBaseField { int *p; MdlMapBaseField() throw(); ~MdlMapBaseField(); };
struct MdlMapCursorField { int *p; MdlMapCursorField() throw(); ~MdlMapCursorField(); };
/* libNdmwRuntimePlugin with the constructors and destructors of its references called out of line. */
struct NdmwRuntimePluginView : InsightPluginView {
    AfsSetupField            afsSetup;           /* +8   _afsSetup */
    StageCtlField            stageCtl;           /* +12  _stageCtl */
    PanelWazaField           panelWaza;          /* +16  _panelWaza */
    LogoField                logo;               /* +20  _logo */
    Title2Field              title2;             /* +24  _title2 */
    LoadCtrl2Field           loadCtrl2;          /* +28  _loadCtrl2 */
    LoadIntf2Field           loadIntf2;          /* +32  _loadIntf2 */
    SaveCtrlField            saveCtrl;           /* +36  _saveCtrl */
    SaveIntfField            saveIntf;           /* +40  _saveIntf */
    GameRamField             gameRam;            /* +44  _gameRam */
    StatusField              status;             /* +48  _status */
    MdlPlayerField           mdlPlayer;          /* +52  _mdlPlayer */
    MdlPlayer2Field          mdlPlayer2;         /* +56  _mdlPlayer2 */
    MdlPBulletField          mdlPBullet;         /* +60  _mdlPBullet */
    MdlEnemyField            mdlEnemy;           /* +64  _mdlEnemy */
    MdlEBulletField          mdlEBullet;         /* +68  _mdlEBullet */
    MdlObjectField           mdlObject;          /* +72  _mdlObject */
    MdlItemField             mdlItem;            /* +76  _mdlItem */
    MdlEffectField           mdlEffect;          /* +80  _mdlEffect */
    MdlMapBaseField          mdlMapBase;         /* +84  _mdlMapBase */
    MdlMapCursorField        mdlMapCursor;       /* +88  _mdlMapCursor */
    virtual void firstSlot();
};
extern "C" igMetaObject *beNDMWWindowList_GetOrCreateMetaObject(void);
extern "C" int beNDMWWindowList_GetVTable(void);
extern "C" void beNDMWWindowList_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWWindowList_Register(void);
extern "C" void beNDMWWindowList_GetMetaObjectFunction(void);
/* kept local: no include/dw4 home; the definition still returns a placeholder view. */
extern "C" igMetaObject *beNDMWWindow_GetOrCreateMetaObject(void);
extern "C" void *beNDMWWindow_GetMetaObject(void);
extern "C" void beNDMWWindow_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWWindow_Register(void);
extern "C" void beNDMWWindow_GetMetaObjectFunction(void);
/* kept local: no include/dw4 home declares it. */
extern "C" void beNDMWWindow_InitFields(void);
extern "C" void *beNDMWTitle2Info_GetMetaObject(void);
extern "C" int beNDMWTitle2Info_GetVTable(void);
extern "C" void beNDMWTitle2Info_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWTitle2Info_Register(void);
extern "C" void beNDMWTitle2Info_GetMetaObjectFunction(void);
extern "C" void *beNDMWTitle2Option_GetMetaObject(void);
extern "C" int beNDMWTitle2Option_GetVTable(void);
extern "C" void beNDMWTitle2Option_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWTitle2Option_Register(void);
extern "C" void beNDMWTitle2Option_GetMetaObjectFunction(void);
/* kept local: no include/dw4 home declares it. */
extern "C" void beNDMWTitle2Option_InitFields(void);
extern "C" void *beNDMWTitle2CtrlData_GetMetaObject(void);
extern "C" int beNDMWTitle2CtrlData_GetVTable(void);
extern "C" void beNDMWTitle2CtrlData_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWTitle2CtrlData_Register(void);
extern "C" void beNDMWTitle2CtrlData_GetMetaObjectFunction(void);
extern "C" void beNDMWTitle2CtrlData_InitFields(void);
extern "C" igMetaObject *beNDMWTitle2_GetOrCreateMetaObject(void);
extern "C" void *beNDMWTitle2_GetMetaObject(void);
extern "C" int beNDMWTitle2_GetVTable(void);
extern "C" void beNDMWTitle2_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWTitle2_Register(void);
extern "C" void beNDMWTitle2_GetMetaObjectFunction(void);
extern "C" void beNDMWTitle2_InitFields(void);
extern "C" void *beNDMWShopTitle03_GetMetaObject(void);
extern "C" int beNDMWShopTitle03_GetVTable(void);
extern "C" igSmartPointer<igObject> *beNDMWWindow_igSmartPointer_beNDMWWindow_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWWindowList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" beNDMWWindowTitle *beNDMWWindowTitle_Destroy(beNDMWWindowTitle *self, short flags);
extern "C" void beNDMWShopTitle03_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopTitle03_Register(void);
extern "C" void beNDMWShopTitle03_GetMetaObjectFunction(void);
extern "C" igMetaObject *beNDMWWindowTitle_GetPublishedMetaObject(void);
extern "C" void *beNDMWShopTitle01_GetMetaObject(void);
extern "C" int beNDMWShopTitle01_GetVTable(void);
extern "C" void beNDMWShopTitle01_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopTitle01_Register(void);
extern "C" void beNDMWShopTitle01_GetMetaObjectFunction(void);
extern "C" void *beNDMWShopTitle00_GetMetaObject(void);
extern "C" int beNDMWShopTitle00_GetVTable(void);
extern "C" void beNDMWShopTitle00_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopTitle00_Register(void);
extern "C" void beNDMWShopTitle00_GetMetaObjectFunction(void);
extern "C" void *beNDMWStatusTitle04_GetMetaObject(void);
extern "C" int beNDMWStatusTitle04_GetVTable(void);
extern "C" void beNDMWStatusTitle04_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusTitle04_Register(void);
extern "C" void beNDMWStatusTitle04_GetMetaObjectFunction(void);
extern "C" igMetaObject *beNDMWStatusTitle03_GetOrCreateMetaObject(void);
extern "C" void *beNDMWStatusTitle03_GetMetaObject(void);
extern "C" int beNDMWStatusTitle03_GetVTable(void);
extern "C" void beNDMWStatusTitle03_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusTitle03_Register(void);
extern "C" void beNDMWStatusTitle03_GetMetaObjectFunction(void);
extern "C" int beNDMWStatusTitle02_GetVTable(void);
extern "C" void beNDMWStatusTitle02_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusTitle02_Register(void);
extern "C" void beNDMWStatusTitle02_GetMetaObjectFunction(void);
extern "C" int beNDMWStatusTitle01_GetVTable(void);
extern "C" void beNDMWStatusTitle01_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusTitle01_Register(void);
extern "C" void beNDMWStatusTitle01_GetMetaObjectFunction(void);
extern "C" int beNDMWStatusTitle00_GetVTable(void);
extern "C" void beNDMWStatusTitle00_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusTitle00_Register(void);
extern "C" void beNDMWStatusTitle00_GetMetaObjectFunction(void);
extern "C" void beNDMWWindowTitle_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWWindowTitle_Register(void);
extern "C" void beNDMWWindowTitle_GetMetaObjectFunction(void);
extern "C" igMetaObject *beNDMWWindow_GetPublishedMetaObject(void);
extern "C" void *beNDMWShopSelectB0_GetMetaObject(void);
extern "C" int beNDMWShopSelectB0_GetVTable(void);
extern "C" void beNDMWShopSelectB0_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopSelectB0_Register(void);
extern "C" void beNDMWShopSelectB0_GetMetaObjectFunction(void);
extern "C" igMetaObject *beNDMWWindowSelect_GetPublishedMetaObject(void);
extern "C" void *beNDMWShopSelectA0_GetMetaObject(void);
extern "C" int beNDMWShopSelectA0_GetVTable(void);
extern "C" void beNDMWShopSelectA0_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopSelectA0_Register(void);
extern "C" void beNDMWShopSelectA0_GetMetaObjectFunction(void);
extern "C" void *beNDMWShopSelect52_GetMetaObject(void);
extern "C" int beNDMWShopSelect52_GetVTable(void);
extern "C" void beNDMWShopSelect52_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopSelect52_Register(void);
extern "C" void beNDMWShopSelect52_GetMetaObjectFunction(void);
extern "C" void *beNDMWShopSelect34_GetMetaObject(void);
extern "C" int beNDMWShopSelect34_GetVTable(void);
extern "C" void beNDMWShopSelect34_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopSelect34_Register(void);
extern "C" void beNDMWShopSelect34_GetMetaObjectFunction(void);
extern "C" void *beNDMWShopSelect11_GetMetaObject(void);
extern "C" int beNDMWShopSelect11_GetVTable(void);
extern "C" void beNDMWShopSelect11_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopSelect11_Register(void);
extern "C" void beNDMWShopSelect11_GetMetaObjectFunction(void);
extern "C" void *beNDMWShopSelect03_GetMetaObject(void);
extern "C" int beNDMWShopSelect03_GetVTable(void);
extern "C" void beNDMWShopSelect03_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopSelect03_Register(void);
extern "C" void beNDMWShopSelect03_GetMetaObjectFunction(void);
extern "C" void *beNDMWShopSelect02_GetMetaObject(void);
extern "C" int beNDMWShopSelect02_GetVTable(void);
extern "C" void beNDMWShopSelect02_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopSelect02_Register(void);
extern "C" void beNDMWShopSelect02_GetMetaObjectFunction(void);
extern "C" void beNDMWShopSelect02_InitFields(void);
extern "C" void *beNDMWShopSelect01_GetMetaObject(void);
extern "C" int beNDMWShopSelect01_GetVTable(void);
extern "C" void beNDMWShopSelect01_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopSelect01_Register(void);
extern "C" void beNDMWShopSelect01_GetMetaObjectFunction(void);
extern "C" void *beNDMWShopSelect00_GetMetaObject(void);
extern "C" int beNDMWShopSelect00_GetVTable(void);
extern "C" void beNDMWShopSelect00_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopSelect00_Register(void);
extern "C" void beNDMWShopSelect00_GetMetaObjectFunction(void);
extern "C" void beNDMWShopSelect00_InitFields(void);
extern "C" void *beNDMWStatusSelectE1_GetMetaObject(void);
extern "C" int beNDMWStatusSelectE1_GetVTable(void);
extern "C" void beNDMWStatusSelectE1_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusSelectE1_Register(void);
extern "C" void beNDMWStatusSelectE1_GetMetaObjectFunction(void);
extern "C" int beNDMWStatusSelectE0_GetVTable(void);
extern "C" void beNDMWStatusSelectE0_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusSelectE0_Register(void);
extern "C" void beNDMWStatusSelectE0_GetMetaObjectFunction(void);
extern "C" int beNDMWStatusSelect01_GetVTable(void);
extern "C" void beNDMWStatusSelect01_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusSelect01_Register(void);
extern "C" void beNDMWStatusSelect01_GetMetaObjectFunction(void);
extern "C" int beNDMWStatusSelect00_GetVTable(void);
extern "C" void beNDMWStatusSelect00_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusSelect00_Register(void);
extern "C" void beNDMWStatusSelect00_GetMetaObjectFunction(void);
extern "C" void beNDMWWindowSelect_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWWindowSelect_Register(void);
extern "C" void beNDMWWindowSelect_GetMetaObjectFunction(void);
extern "C" void beNDMWWindowSelect_InitFields(void);
extern "C" void *beNDMWStatusInfo_GetMetaObject(void);
extern "C" int beNDMWStatusInfo_GetVTable(void);
extern "C" void beNDMWStatusInfo_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusInfo_Register(void);
extern "C" void beNDMWStatusInfo_GetMetaObjectFunction(void);
extern "C" void *beNDMWStatusInfoRam_GetMetaObject(void);
extern "C" int beNDMWStatusInfoRam_GetVTable(void);
extern "C" void beNDMWStatusInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusInfoRam_Register(void);
extern "C" void beNDMWStatusInfoRam_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusInfoRam_InitFields(void);
extern "C" igMetaObject *beNDMWStatusInfoWork_GetOrCreateMetaObject(void);
extern "C" void *beNDMWStatusInfoWork_GetMetaObject(void);
extern "C" int beNDMWStatusInfoWork_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWItemBaseList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" void beNDMWStatusInfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusInfoWork_Register(void);
extern "C" void beNDMWStatusInfoWork_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusInfoWork_InitFields(void);
extern "C" void *beNDMWShopJunk_GetMetaObject(void);
extern "C" int beNDMWShopJunk_GetVTable(void);
extern "C" void beNDMWShopJunk_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopJunk_Register(void);
extern "C" void beNDMWShopJunk_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrl00_EnsureRegistered();
extern "C" void beNDMWShopJunk_InitFields(void);
extern "C" void *beNDMWShopDevice_GetMetaObject(void);
extern "C" int beNDMWShopDevice_GetVTable(void);
extern "C" beNDMWListCtrl *beNDMWListCtrl_Destroy(beNDMWListCtrl *self, short flags);
extern "C" void beNDMWShopDevice_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopDevice_Register(void);
extern "C" void beNDMWShopDevice_GetMetaObjectFunction(void);
extern "C" igMetaObject *beNDMWListCtrl_GetPublishedMetaObject(void);
extern "C" void beNDMWShopDevice_InitFields(void);
extern "C" void *beNDMWShopCtrlXdataChip_GetMetaObject(void);
extern "C" int beNDMWShopCtrlXdataChip_GetVTable(void);
extern "C" void beNDMWShopCtrlXdataChip_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrlXdataChip_Register(void);
extern "C" void beNDMWShopCtrlXdataChip_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrlXdataChip_InitFields(void);
extern "C" void *beNDMWShopCtrlSales_GetMetaObject(void);
extern "C" int beNDMWShopCtrlSales_GetVTable(void);
extern "C" void beNDMWShopCtrlSales_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrlSales_Register(void);
extern "C" void beNDMWShopCtrlSales_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrlSales_InitFields(void);
extern "C" void *beNDMWShopCtrlDiskSell_GetMetaObject(void);
extern "C" int beNDMWShopCtrlDiskSell_GetVTable(void);
extern "C" void beNDMWShopCtrlDiskSell_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrlDiskSell_Register(void);
extern "C" void beNDMWShopCtrlDiskSell_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrlDiskSell_InitFields(void);
extern "C" void *beNDMWShopCtrlDeviceSell_GetMetaObject(void);
extern "C" int beNDMWShopCtrlDeviceSell_GetVTable(void);
extern "C" void beNDMWShopCtrlDeviceSell_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrlDeviceSell_Register(void);
extern "C" void beNDMWShopCtrlDeviceSell_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrlDeviceSell_InitFields(void);
extern "C" void *beNDMWShopCtrlSell_GetMetaObject(void);
extern "C" int beNDMWShopCtrlSell_GetVTable(void);
extern "C" void beNDMWShopCtrlSell_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrlSell_Register(void);
extern "C" void beNDMWShopCtrlSell_GetMetaObjectFunction(void);
extern "C" int beNDMWShopCtrlEditBit_GetVTable(void);
extern "C" void beNDMWShopCtrlEditBit_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrlEditBit_Register(void);
extern "C" void beNDMWShopCtrlEditBit_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrlEditBit_InitFields(void);
extern "C" int beNDMWShopCtrlDigilabo_GetVTable(void);
extern "C" void beNDMWShopCtrlDigilabo_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrlDigilabo_Register(void);
extern "C" void beNDMWShopCtrlDigilabo_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrlDigilabo_InitFields(void);
extern "C" int beNDMWShopCtrlA2_GetVTable(void);
extern "C" void beNDMWShopCtrlA2_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrlA2_Register(void);
extern "C" void beNDMWShopCtrlA2_GetMetaObjectFunction(void);
extern "C" int beNDMWShopCtrlA1_GetVTable(void);
extern "C" void beNDMWShopCtrlA1_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrlA1_Register(void);
extern "C" void beNDMWShopCtrlA1_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrlA1_InitFields(void);
extern "C" void *beNDMWShopCtrlA0_GetMetaObject(void);
extern "C" int beNDMWShopCtrlA0_GetVTable(void);
extern "C" void beNDMWShopCtrlA0_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrlA0_Register(void);
extern "C" void beNDMWShopCtrlA0_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrlA0_InitFields(void);
extern "C" void *beNDMWShopCtrl50_GetMetaObject(void);
extern "C" int beNDMWShopCtrl50_GetVTable(void);
extern "C" void beNDMWShopCtrl50_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrl50_Register(void);
extern "C" void beNDMWShopCtrl50_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrl50_InitFields(void);
extern "C" void *beNDMWShopCtrl40_GetMetaObject(void);
extern "C" int beNDMWShopCtrl40_GetVTable(void);
extern "C" void beNDMWShopCtrl40_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrl40_Register(void);
extern "C" void beNDMWShopCtrl40_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrl40_InitFields(void);
extern "C" void *beNDMWShopCtrl30_GetMetaObject(void);
extern "C" int beNDMWShopCtrl30_GetVTable(void);
extern "C" void beNDMWShopCtrl30_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrl30_Register(void);
extern "C" void beNDMWShopCtrl30_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrl30_InitFields(void);
extern "C" void *beNDMWShopCtrlEvolve_GetMetaObject(void);
extern "C" int beNDMWShopCtrlEvolve_GetVTable(void);
extern "C" void beNDMWShopCtrlEvolve_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrlEvolve_Register(void);
extern "C" void beNDMWShopCtrlEvolve_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrlEvolve_InitFields(void);
extern "C" void *beNDMWShopCtrl10_GetMetaObject(void);
extern "C" int beNDMWShopCtrl10_GetVTable(void);
extern "C" void beNDMWShopCtrl10_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShopCtrl10_Register(void);
extern "C" void beNDMWShopCtrl10_GetMetaObjectFunction(void);
extern "C" void beNDMWShopCtrl10_InitFields(void);
extern "C" int beNDMWShopCtrl00_GetVTable(void);
extern "C" CallbackArray *beNDMWShopCtrl00_Register(void);
extern "C" void *beNDMWStatusSubMenu_GetMetaObject(void);
extern "C" int beNDMWStatusSubMenu_GetVTable(void);
extern "C" igSmartPointer<igObject> *beNDMWStatusSubMenu_igSmartPointer_beNDMWWindow_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" void beNDMWStatusSubMenu_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusSubMenu_Register(void);
extern "C" void beNDMWStatusSubMenu_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusSubMenu_InitFields(void);
extern "C" void *beNDMWStatusCtrlSkill_GetMetaObject(void);
extern "C" int beNDMWStatusCtrlSkill_GetVTable(void);
extern "C" void beNDMWStatusCtrlSkill_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusCtrlSkill_Register(void);
extern "C" void beNDMWStatusCtrlSkill_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusCtrlSkill_InitFields(void);
extern "C" void *beNDMWStatusCtrlSendBit_GetMetaObject(void);
extern "C" int beNDMWStatusCtrlSendBit_GetVTable(void);
extern "C" void beNDMWStatusCtrlSendBit_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusCtrlSendBit_Register(void);
extern "C" void beNDMWStatusCtrlSendBit_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusCtrlSendBit_InitFields(void);
extern "C" void *beNDMWStatusCtrlBit_GetMetaObject(void);
extern "C" int beNDMWStatusCtrlBit_GetVTable(void);
extern "C" void beNDMWStatusCtrlBit_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusCtrlBit_Register(void);
extern "C" void beNDMWStatusCtrlBit_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusCtrlBit_InitFields(void);
extern "C" int beNDMWStatusCtrlDisk_GetVTable(void);
extern "C" void beNDMWStatusCtrlDisk_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusCtrlDisk_Register(void);
extern "C" void beNDMWStatusCtrlDisk_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusCtrlDisk_InitFields(void);
extern "C" int beNDMWStatusCtrlFlag_GetVTable(void);
extern "C" void beNDMWStatusCtrlFlag_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusCtrlFlag_Register(void);
extern "C" void beNDMWStatusCtrlFlag_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusCtrlFlag_InitFields(void);
extern "C" int beNDMWStatusCtrlFolder_GetVTable(void);
extern "C" void beNDMWStatusCtrlFolder_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusCtrlFolder_Register(void);
extern "C" void beNDMWStatusCtrlFolder_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusCtrlFolder_InitFields(void);
extern "C" int beNDMWStatusSubSlot_GetVTable(void);
extern "C" igSmartPointer<igObject> *beNDMWStatusSubSlot_igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" void beNDMWStatusSubSlot_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusSubSlot_Register(void);
extern "C" void beNDMWStatusSubSlot_GetMetaObjectFunction(void);
extern "C" igMetaObject *beNDMWStatusCtrlBaseEquip_GetPublishedMetaObject(void);
extern "C" void *beNDMWStatusMainSlot_GetMetaObject(void);
extern "C" int beNDMWStatusMainSlot_GetVTable(void);
extern "C" void beNDMWStatusMainSlot_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusMainSlot_Register(void);
extern "C" void beNDMWStatusMainSlot_GetMetaObjectFunction(void);
extern "C" void *beNDMWStatusPowerSocket_GetMetaObject(void);
extern "C" int beNDMWStatusPowerSocket_GetVTable(void);
extern "C" void beNDMWStatusPowerSocket_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusPowerSocket_Register(void);
extern "C" void beNDMWStatusPowerSocket_GetMetaObjectFunction(void);
extern "C" void *beNDMWStatusCtrlBaseEquip_GetMetaObject(void);
extern "C" void beNDMWStatusCtrlBaseEquip_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusCtrlBaseEquip_Register(void);
extern "C" void beNDMWStatusCtrlBaseEquip_GetMetaObjectFunction(void);
/* kept local: no include/dw4 home declares it. */
extern "C" void beNDMWStatusCtrlBaseEquip_InitFields(void);
extern "C" void *beNDMWStatusCtrlEquip_GetMetaObject(void);
extern "C" int beNDMWStatusCtrlEquip_GetVTable(void);
extern "C" void beNDMWStatusCtrlEquip_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusCtrlEquip_Register(void);
extern "C" void beNDMWStatusCtrlEquip_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusCtrlEquip_InitFields(void);
extern "C" void *beNDMWStatusCtrlD0_GetMetaObject(void);
extern "C" int beNDMWStatusCtrlD0_GetVTable(void);
extern "C" void beNDMWStatusCtrlD0_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusCtrlD0_Register(void);
extern "C" void beNDMWStatusCtrlD0_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusCtrlD0_InitFields(void);
extern "C" void *beNDMWStatusCtrl00_GetMetaObject(void);
extern "C" int beNDMWStatusCtrl00_GetVTable(void);
extern "C" void beNDMWStatusCtrl00_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatusCtrl00_Register(void);
extern "C" void beNDMWStatusCtrl00_GetMetaObjectFunction(void);
extern "C" void beNDMWStatusCtrl00_InitFields(void);
extern "C" void *beNDMWListCtrl_GetMetaObject(void);
extern "C" void beNDMWListCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWListCtrl_Register(void);
extern "C" void beNDMWListCtrl_GetMetaObjectFunction(void);
extern "C" void beNDMWListCtrl_InitFields(void);
extern "C" igMetaObject *beNDMWWindowCtrl_GetOrCreateMetaObject(void);
extern "C" void *beNDMWWindowCtrl_GetMetaObject(void);
extern "C" void beNDMWWindowCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWWindowCtrl_Register(void);
extern "C" void beNDMWWindowCtrl_GetMetaObjectFunction(void);
extern "C" void beNDMWWindowCtrl_InitFields(void);
extern "C" igMetaObject *beNDMWStatus_GetOrCreateMetaObject(void);
extern "C" void *beNDMWStatus_GetMetaObject(void);
extern "C" int beNDMWStatus_GetVTable(void);
extern "C" void beNDMWStatus_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStatus_Register(void);
extern "C" void beNDMWStatus_GetMetaObjectFunction(void);
extern "C" void beNDMWStatus_InitFields(void);
extern "C" void *beNDMWStageCtlInfoRam_GetMetaObject(void);
extern "C" int beNDMWStageCtlInfoRam_GetVTable(void);
extern "C" void beNDMWStageCtlInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStageCtlInfoRam_Register(void);
extern "C" void beNDMWStageCtlInfoRam_GetMetaObjectFunction(void);
extern "C" int beNDMWStageCtlInfo_GetVTable(void);
extern "C" void beNDMWStageCtlInfo_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStageCtlInfo_Register(void);
extern "C" void beNDMWStageCtlInfo_GetMetaObjectFunction(void);
extern "C" igMetaObject *beNDMWStageCtl_GetOrCreateMetaObject(void);
extern "C" int beNDMWStageCtl_GetVTable(void);
extern "C" void beNDMWStageCtl_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWStageCtl_Register(void);
extern "C" void beNDMWStageCtl_GetMetaObjectFunction(void);
extern "C" void beNDMWStageCtl_InitFields(void);
extern "C" int beNDMWSaveIntfInfo_GetVTable(void);
extern "C" void beNDMWSaveIntfInfo_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWSaveIntfInfo_Register(void);
extern "C" void beNDMWSaveIntfInfo_GetMetaObjectFunction(void);
extern "C" int beNDMWSaveIntfComMdlCtrl_GetVTable(void);
extern "C" void beNDMWSaveIntfComMdlCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWSaveIntfComMdlCtrl_Register(void);
extern "C" void beNDMWSaveIntfComMdlCtrl_GetMetaObjectFunction(void);
extern "C" void beNDMWSaveIntfComMdlCtrl_InitFields(void);
extern "C" igMetaObject *beSaveIntfComMdlDataList_GetOrCreateMetaObject(void);
extern "C" void *beSaveIntfComMdlDataList_GetMetaObject(void);
extern "C" int beSaveIntfComMdlDataList_GetVTable(void);
extern "C" void beSaveIntfComMdlDataList_EnsureRegistered(void);
extern "C" CallbackArray *beSaveIntfComMdlDataList_Register(void);
extern "C" void beSaveIntfComMdlDataList_GetMetaObjectFunction(void);
extern "C" void *beSaveIntfComMdlData_GetMetaObject(void);
extern "C" int beSaveIntfComMdlData_GetVTable(void);
extern "C" void beSaveIntfComMdlData_EnsureRegistered(void);
extern "C" CallbackArray *beSaveIntfComMdlData_Register(void);
extern "C" void beSaveIntfComMdlData_GetMetaObjectFunction(void);
extern "C" void beSaveIntfComMdlData_InitFields(void);
extern "C" void *beNDMWSaveIntfCtrlData_GetMetaObject(void);
extern "C" int beNDMWSaveIntfCtrlData_GetVTable(void);
extern "C" void beNDMWSaveIntfCtrlData_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWSaveIntfCtrlData_Register(void);
extern "C" void beNDMWSaveIntfCtrlData_GetMetaObjectFunction(void);
extern "C" void beNDMWSaveIntfCtrlData_InitFields(void);
extern "C" igMetaObject *beNDMWSaveIntf_GetOrCreateMetaObject(void);
extern "C" void *beNDMWSaveIntf_GetMetaObject(void);
extern "C" int beNDMWSaveIntf_GetVTable(void);
extern "C" void beNDMWSaveIntf_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWSaveIntf_Register(void);
extern "C" void beNDMWSaveIntf_GetMetaObjectFunction(void);
extern "C" void beNDMWSaveIntf_InitFields(void);
extern "C" void *beNDMWSaveCtrlInfo_GetMetaObject(void);
extern "C" int beNDMWSaveCtrlInfo_GetVTable(void);
extern "C" void beNDMWSaveCtrlInfo_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWSaveCtrlInfo_Register(void);
extern "C" void beNDMWSaveCtrlInfo_GetMetaObjectFunction(void);
extern "C" void *beNDMWSaveCtrlCtrlData_GetMetaObject(void);
extern "C" int beNDMWSaveCtrlCtrlData_GetVTable(void);
extern "C" void beNDMWSaveCtrlCtrlData_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWSaveCtrlCtrlData_Register(void);
extern "C" void beNDMWSaveCtrlCtrlData_GetMetaObjectFunction(void);
extern "C" void beNDMWSaveCtrlCtrlData_InitFields(void);
extern "C" igMetaObject *beNDMWSaveCtrl_GetOrCreateMetaObject(void);
extern "C" void *beNDMWSaveCtrl_ResolveMetaObject(void);
extern "C" int beNDMWSaveCtrl_GetVTable(void);
extern "C" void beNDMWSaveCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWSaveCtrl_Register(void);
extern "C" void beNDMWSaveCtrl_GetMetaObject(void);
extern "C" void beNDMWSaveCtrl_InitFields(void);
extern "C" void *beNDMWPanelWazaInfo_ResolveMetaObject(void);
extern "C" int beNDMWPanelWazaInfo_GetVTable(void);
extern "C" void beNDMWPanelWazaInfo_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWPanelWazaInfo_Register(void);
extern "C" void beNDMWPanelWazaInfo_GetMetaObject(void);
extern "C" void *beNDMWPanelWazaInfoRam_ResolveMetaObject(void);
extern "C" int beNDMWPanelWazaInfoRam_GetVTable(void);
extern "C" void beNDMWPanelWazaInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWPanelWazaInfoRam_Register(void);
extern "C" void beNDMWPanelWazaInfoRam_GetMetaObject(void);
extern "C" void beNDMWPanelWazaInfoRam_InitFields(void);
extern "C" igMetaObject *beNDMWPanelWazaInfoWork_GetOrCreateMetaObject(void);
extern "C" int beNDMWPanelWazaInfoWork_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWPanelObjectItem_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWPanelObjectStat_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" void beNDMWPanelWazaInfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWPanelWazaInfoWork_Register(void);
extern "C" void beNDMWPanelWazaInfoWork_GetMetaObject(void);
extern "C" void beNDMWPanelWazaInfoWork_InitFields(void);
extern "C" igMetaObject *beNDMWPanelObjectStat_GetOrCreateMetaObject(void);
extern "C" int beNDMWPanelObjectStat_GetVTable(void);
extern "C" void beNDMWPanelObjectStat_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWPanelObjectStat_Register(void);
extern "C" void beNDMWPanelObjectStat_GetMetaObject(void);
extern "C" igMetaObject *beNDMWPanelObject_GetPublishedMetaObject(void);
extern "C" void beNDMWPanelObjectStat_InitFields(void);
extern "C" igMetaObject *beNDMWPanelObjectItem_GetOrCreateMetaObject(void);
extern "C" int beNDMWPanelObjectItem_GetVTable(void);
extern "C" void beNDMWPanelObjectItem_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWPanelObjectItem_Register(void);
extern "C" void beNDMWPanelObjectItem_GetMetaObject(void);
extern "C" void beNDMWPanelObjectItem_InitFields(void);
extern "C" igMetaObject *beNDMWPanelObjectWaza_GetOrCreateMetaObject(void);
extern "C" int beNDMWPanelObjectWaza_GetVTable(void);
extern "C" void beNDMWPanelObjectWaza_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWPanelObjectWaza_Register(void);
extern "C" void beNDMWPanelObjectWaza_GetMetaObject(void);
extern "C" void beNDMWPanelObjectWaza_InitFields(void);
extern "C" void beNDMWPanelObject_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWPanelObject_Register(void);
extern "C" void beNDMWPanelObject_GetMetaObject(void);
extern "C" void beNDMWPanelObject_InitFields(void);
extern "C" igMetaObject *beNDMWPanelWaza_GetOrCreateMetaObject(void);
extern "C" void *beNDMWPanelWaza_ResolveMetaObject(void);
extern "C" int beNDMWPanelWaza_GetVTable(void);
extern "C" void beNDMWPanelWaza_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWPanelWaza_Register(void);
extern "C" void beNDMWPanelWaza_GetMetaObject(void);
extern "C" void beNDMWPanelWaza_InitFields(void);
extern "C" igMetaObject *beNDMWMdlPlayer2_GetOrCreateMetaObject(void);
extern "C" void *beNDMWMdlPlayer2_ResolveMetaObject(void);
extern "C" int beNDMWMdlPlayer2_GetVTable(void);
extern "C" void beNDMWMdlPlayer2_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlPlayer2_Register(void);
extern "C" void beNDMWMdlPlayer2_GetMetaObject(void);
extern "C" igMetaObject *beModelCtrl_GetPublishedMetaObject(void);
extern "C" void beNDMWMdlPlayer2_InitFields(void);
extern "C" void *beNDMWMdlPlayer2InfoWork_ResolveMetaObject(void);
extern "C" int beNDMWMdlPlayer2InfoWork_GetVTable(void);
extern "C" void beNDMWMdlPlayer2InfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlPlayer2InfoWork_Register(void);
extern "C" void beNDMWMdlPlayer2InfoWork_GetMetaObject(void);
extern "C" igMetaObject *beModelCtrlInfoWork_GetPublishedMetaObject(void);
extern "C" void beNDMWMdlPlayer2InfoWork_InitFields(void);
extern "C" igMetaObject *beNDMWMdlPlayer_GetOrCreateMetaObject(void);
extern "C" void *beNDMWMdlPlayer_ResolveMetaObject(void);
extern "C" int beNDMWMdlPlayer_GetVTable(void);
extern "C" void beNDMWMdlPlayer_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlPlayer_Register(void);
extern "C" void beNDMWMdlPlayer_GetMetaObject(void);
extern "C" igMetaObject *beNDMWMdlPEBase_GetPublishedMetaObject(void);
extern "C" void beNDMWMdlPlayer_InitFields(void);
extern "C" igMetaObject *beNDMWMdlPlayerInfoWork_GetOrCreateMetaObject(void);
extern "C" int beNDMWMdlPlayerInfoWork_GetVTable(void);
extern "C" void beNDMWMdlPlayerInfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlPlayerInfoWork_Register(void);
extern "C" void beNDMWMdlPlayerInfoWork_GetMetaObject(void);
extern "C" igMetaObject *beNDMWMdlPEBaseInfoWork_GetPublishedMetaObject(void);
extern "C" void beNDMWMdlPlayerInfoWork_InitFields(void);
extern "C" void *beNDMWMdlPEBase_ResolveMetaObject(void);
extern "C" void beNDMWMdlPEBase_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlPEBase_Register(void);
extern "C" void beNDMWMdlPEBase_GetMetaObject(void);
extern "C" void *beNDMWMdlPEBaseInfoWork_ResolveMetaObject(void);
extern "C" int beNDMWMdlPEBaseInfoWork_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_igBoolList_Construct(igSmartPointer<igObject> *self);
extern "C" void beNDMWMdlPEBaseInfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlPEBaseInfoWork_Register(void);
extern "C" void beNDMWMdlPEBaseInfoWork_GetMetaObject(void);
extern "C" void beNDMWMdlPEBaseInfoWork_InitFields(void);
extern "C" igMetaObject *beNDMWMdlPBullet_GetOrCreateMetaObject(void);
extern "C" void *beNDMWMdlPBullet_GetReadyMetaObject(void);
extern "C" int beNDMWMdlPBullet_GetVTable(void);
extern "C" void beNDMWMdlPBullet_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlPBullet_Register(void);
extern "C" void beNDMWMdlPBullet_GetMetaObject(void);
extern "C" igMetaObject *beNDMWMdlObject_GetOrCreateMetaObject(void);
extern "C" void *beNDMWMdlObject_GetReadyMetaObject(void);
extern "C" int beNDMWMdlObject_GetVTable(void);
extern "C" void beNDMWMdlObject_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlObject_Register(void);
extern "C" void beNDMWMdlObject_GetMetaObject(void);
extern "C" igMetaObject *beNDMWMdlMapCursor_GetOrCreateMetaObject(void);
extern "C" void *beNDMWMdlMapCursor_GetReadyMetaObject(void);
extern "C" int beNDMWMdlMapCursor_GetVTable(void);
extern "C" void beNDMWMdlMapCursor_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlMapCursor_Register(void);
extern "C" void beNDMWMdlMapCursor_GetMetaObject(void);
extern "C" igMetaObject *beNDMWMdlMapBase_GetOrCreateMetaObject(void);
extern "C" int beNDMWMdlMapBase_GetVTable(void);
extern "C" void beNDMWMdlMapBase_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlMapBase_Register(void);
extern "C" void beNDMWMdlMapBase_GetMetaObject(void);
extern "C" igMetaObject *beNDMWMdlItem_GetOrCreateMetaObject(void);
extern "C" int beNDMWMdlItem_GetVTable(void);
extern "C" void beNDMWMdlItem_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlItem_Register(void);
extern "C" void beNDMWMdlItem_GetMetaObject(void);
extern "C" void beNDMWMdlItem_InitFields(void);
extern "C" int beNDMWMdlItemInfoWork_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWItemBase_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWItemBase_Construct(igSmartPointer<igObject> *self);
extern "C" void beNDMWMdlItemInfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlItemInfoWork_Register(void);
extern "C" void beNDMWMdlItemInfoWork_GetMetaObject(void);
extern "C" void beNDMWMdlItemInfoWork_InitFields(void);
extern "C" igMetaObject *beNDMWMdlEnemy_GetOrCreateMetaObject(void);
extern "C" int beNDMWMdlEnemy_GetVTable(void);
extern "C" void beNDMWMdlEnemy_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlEnemy_Register(void);
extern "C" void beNDMWMdlEnemy_GetMetaObject(void);
extern "C" void *beNDMWMdlEnemyInfoWork_GetReadyMetaObject(void);
extern "C" int beNDMWMdlEnemyInfoWork_GetVTable(void);
extern "C" void beNDMWMdlEnemyInfoWork_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlEnemyInfoWork_Register(void);
extern "C" void beNDMWMdlEnemyInfoWork_GetMetaObject(void);
extern "C" igMetaObject *beNDMWMdlEffect_GetOrCreateMetaObject(void);
extern "C" void *beNDMWMdlEffect_GetReadyMetaObject(void);
extern "C" int beNDMWMdlEffect_GetVTable(void);
extern "C" void beNDMWMdlEffect_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlEffect_Register(void);
extern "C" void beNDMWMdlEffect_GetMetaObject(void);
extern "C" igMetaObject *beNDMWMdlEBullet_GetOrCreateMetaObject(void);
extern "C" void *beNDMWMdlEBullet_GetReadyMetaObject(void);
extern "C" int beNDMWMdlEBullet_GetVTable(void);
extern "C" void beNDMWMdlEBullet_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMdlEBullet_Register(void);
extern "C" void beNDMWMdlEBullet_GetMetaObject(void);
extern "C" void *beNDMWLogoInfo_GetReadyMetaObject(void);
extern "C" int beNDMWLogoInfo_GetVTable(void);
extern "C" void beNDMWLogoInfo_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLogoInfo_Register(void);
extern "C" void beNDMWLogoInfo_GetMetaObject(void);
extern "C" void *beNDMWLogoCtrlData_GetReadyMetaObject(void);
extern "C" int beNDMWLogoCtrlData_GetVTable(void);
extern "C" void beNDMWLogoCtrlData_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLogoCtrlData_Register(void);
extern "C" void beNDMWLogoCtrlData_GetMetaObject(void);
extern "C" void beNDMWLogoCtrlData_InitFields(void);
extern "C" igMetaObject *beNDMWLogo_GetOrCreateMetaObject(void);
extern "C" void *beNDMWLogo_GetReadyMetaObject(void);
extern "C" int beNDMWLogo_GetVTable(void);
extern "C" void beNDMWLogo_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLogo_Register(void);
extern "C" void beNDMWLogo_GetMetaObject(void);
extern "C" void beNDMWLogo_InitFields(void);
extern "C" void *beNDMWLoadIntf2Info_GetReadyMetaObject(void);
extern "C" int beNDMWLoadIntf2Info_GetVTable(void);
extern "C" void beNDMWLoadIntf2Info_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2Info_Register(void);
extern "C" void beNDMWLoadIntf2Info_GetMetaObject(void);
extern "C" void *beNDMWLoadIntf2NameSel_GetReadyMetaObject(void);
extern "C" int beNDMWLoadIntf2NameSel_GetVTable(void);
extern "C" void beNDMWLoadIntf2NameSel_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2NameSel_Register(void);
extern "C" void beNDMWLoadIntf2NameSel_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2NameSel_InitFields(void);
extern "C" int beNDMWLoadIntf2ChrDataSel_GetVTable(void);
extern "C" void beNDMWLoadIntf2ChrDataSel_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2ChrDataSel_Register(void);
extern "C" void beNDMWLoadIntf2ChrDataSel_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2ChrDataSel_InitFields(void);
extern "C" int beNDMWLoadIntf2SelSlot_GetVTable(void);
extern "C" void beNDMWLoadIntf2SelSlot_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2SelSlot_Register(void);
extern "C" void beNDMWLoadIntf2SelSlot_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2SelSlot_InitFields(void);
extern "C" int beNDMWLoadIntf2Diffselect_GetVTable(void);
extern "C" void beNDMWLoadIntf2Diffselect_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2Diffselect_Register(void);
extern "C" void beNDMWLoadIntf2Diffselect_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2Diffselect_InitFields(void);
extern "C" int beNDMWLoadIntf2DataSelIntf_GetVTable(void);
extern "C" void beNDMWLoadIntf2DataSelIntf_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2DataSelIntf_Register(void);
extern "C" void beNDMWLoadIntf2DataSelIntf_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2DataSelIntf_InitFields(void);
extern "C" igMetaObject *beNDMWLoadIntf2DegiStateCtrl_GetOrCreateMetaObject(void);
extern "C" int beNDMWLoadIntf2DegiStateCtrl_GetVTable(void);
extern "C" void beNDMWLoadIntf2DegiStateCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2DegiStateCtrl_Register(void);
extern "C" void beNDMWLoadIntf2DegiStateCtrl_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2DegiStateCtrl_InitFields(void);
extern "C" igMetaObject *beNDMWLoadIntf2DegiStateList_GetOrCreateMetaObject(void);
extern "C" int beNDMWLoadIntf2DegiStateList_GetVTable(void);
extern "C" void beNDMWLoadIntf2DegiStateList_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2DegiStateList_Register(void);
extern "C" void beNDMWLoadIntf2DegiStateList_GetMetaObject(void);
extern "C" void *beNDMWLoadIntf2DegiState_ResolveMetaObject(void);
extern "C" int beNDMWLoadIntf2DegiState_GetVTable(void);
extern "C" void beNDMWLoadIntf2DegiState_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2DegiState_Register(void);
extern "C" void beNDMWLoadIntf2DegiState_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2DegiState_InitFields(void);
extern "C" int beNDMWLoadIntf2MakeChr_GetVTable(void);
extern "C" void beNDMWLoadIntf2MakeChr_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2MakeChr_Register(void);
extern "C" void beNDMWLoadIntf2MakeChr_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2MakeChr_InitFields(void);
extern "C" void *beNDMWLoadIntf2CtrlData_ResolveMetaObject(void);
extern "C" int beNDMWLoadIntf2CtrlData_GetVTable(void);
extern "C" void beNDMWLoadIntf2CtrlData_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2CtrlData_Register(void);
extern "C" void beNDMWLoadIntf2CtrlData_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2CtrlData_InitFields(void);
extern "C" igMetaObject *beNDMWLoadIntf2_GetOrCreateMetaObject(void);
extern "C" void *beNDMWLoadIntf2_ResolveMetaObject(void);
extern "C" int beNDMWLoadIntf2_GetVTable(void);
extern "C" void beNDMWLoadIntf2_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2_Register(void);
extern "C" void beNDMWLoadIntf2_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2_InitFields(void);
extern "C" int beNDMWLoadCtrl2Info_GetVTable(void);
extern "C" void beNDMWLoadCtrl2Info_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadCtrl2Info_Register(void);
extern "C" void beNDMWLoadCtrl2Info_GetMetaObject(void);
extern "C" void beNDMWLoadCtrl2Info_InitFields(void);
extern "C" igMetaObject *beNDMWLoadCtrl2CommonIntf_GetOrCreateMetaObject(void);
extern "C" int beNDMWLoadCtrl2CommonIntf_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWDegiDataList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWLoadSavePlWorkList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" void beNDMWLoadCtrl2CommonIntf_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadCtrl2CommonIntf_Register(void);
extern "C" void beNDMWLoadCtrl2CommonIntf_GetMetaObject(void);
extern "C" void beNDMWLoadCtrl2CommonIntf_InitFields(void);
extern "C" igMetaObject *beNDMWMcUtilCtrl_GetOrCreateMetaObject(void);
extern "C" void *beNDMWMcUtilCtrl_ResolveMetaObject(void);
extern "C" int beNDMWMcUtilCtrl_GetVTable(void);
extern "C" void beNDMWMcUtilCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMcUtilCtrl_Register(void);
extern "C" void beNDMWMcUtilCtrl_GetMetaObject(void);
extern "C" void beNDMWMcUtilCtrl_InitFields(void);
extern "C" igMetaObject *beNDMWLoadSavePlWorkList_GetOrCreateMetaObject(void);
extern "C" void *beNDMWLoadSavePlWorkList_ResolveMetaObject(void);
extern "C" int beNDMWLoadSavePlWorkList_GetVTable(void);
extern "C" void beNDMWLoadSavePlWorkList_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadSavePlWorkList_Register(void);
extern "C" void beNDMWLoadSavePlWorkList_GetMetaObject(void);
extern "C" void *beNDMWLoadSavePlWork_ResolveMetaObject(void);
extern "C" int beNDMWLoadSavePlWork_GetVTable(void);
extern "C" void beNDMWLoadSavePlWork_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadSavePlWork_Register(void);
extern "C" void beNDMWLoadSavePlWork_GetMetaObject(void);
extern "C" void beNDMWLoadSavePlWork_InitFields(void);
extern "C" igMetaObject *beNDMWMcSlotList_GetOrCreateMetaObject(void);
extern "C" void *beNDMWMcSlotList_GetReadyMetaObject(void);
extern "C" int beNDMWMcSlotList_GetVTable(void);
extern "C" void beNDMWMcSlotList_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMcSlotList_Register(void);
extern "C" void beNDMWMcSlotList_GetMetaObject(void);
extern "C" int beNDMWMcSlotXbox_GetVTable(void);
extern "C" void beNDMWMcSlotXbox_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMcSlotXbox_Register(void);
extern "C" void beNDMWMcSlotXbox_GetMetaObject(void);
extern "C" igMetaObject *beNDMWMcSlot_GetPublishedMetaObject(void);
extern "C" void beNDMWMcSlotXbox_InitFields(void);
extern "C" int beNDMWMcSlotGC_GetVTable(void);
extern "C" void beNDMWMcSlotGC_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMcSlotGC_Register(void);
extern "C" void beNDMWMcSlotGC_GetMetaObject(void);
extern "C" void beNDMWMcSlotGC_InitFields(void);
extern "C" int beNDMWMcSlotPS2_GetVTable(void);
extern "C" void beNDMWMcSlotPS2_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMcSlotPS2_Register(void);
extern "C" void beNDMWMcSlotPS2_GetMetaObject(void);
extern "C" void *beNDMWMcSlot_GetReadyMetaObject(void);
extern "C" void beNDMWMcSlot_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWMcSlot_Register(void);
extern "C" void beNDMWMcSlot_GetMetaObject(void);
extern "C" void beNDMWMcSlot_InitFields(void);
extern "C" igMetaObject *beNDMWLoadSlotPlayerList_GetOrCreateMetaObject(void);
extern "C" void *beNDMWLoadSlotPlayerList_GetReadyMetaObject(void);
extern "C" int beNDMWLoadSlotPlayerList_GetVTable(void);
extern "C" void beNDMWLoadSlotPlayerList_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadSlotPlayerList_Register(void);
extern "C" void beNDMWLoadSlotPlayerList_GetMetaObject(void);
extern "C" igMetaObject *beNDMWLoadSlotPlayer_GetOrCreateMetaObject(void);
extern "C" void *beNDMWLoadSlotPlayer_GetReadyMetaObject(void);
extern "C" int beNDMWLoadSlotPlayer_GetVTable(void);
extern "C" void beNDMWLoadSlotPlayer_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadSlotPlayer_Register(void);
extern "C" void beNDMWLoadSlotPlayer_GetMetaObject(void);
extern "C" void beNDMWLoadSlotPlayer_InitFields(void);
extern "C" igMetaObject *beNDMWDegiDataList_GetOrCreateMetaObject(void);
extern "C" void *beNDMWDegiDataList_GetReadyMetaObject(void);
extern "C" int beNDMWDegiDataList_GetVTable(void);
extern "C" void beNDMWDegiDataList_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWDegiDataList_Register(void);
extern "C" void beNDMWDegiDataList_GetMetaObject(void);
extern "C" void *beNDMWDegiData_GetReadyMetaObject(void);
extern "C" int beNDMWDegiData_GetVTable(void);
extern "C" void beNDMWDegiData_RunStaticInit(void);
extern "C" CallbackArray *beNDMWDegiData_Register(void);
extern "C" void beNDMWDegiData_GetMetaObject(void);
extern "C" void beNDMWDegiData_InitFields(void);
extern "C" igMetaObject *beNDMWLoadIntf2MesWin_GetOrCreateMetaObject(void);
extern "C" void *beNDMWLoadIntf2MesWin_GetReadyMetaObject(void);
extern "C" int beNDMWLoadIntf2MesWin_GetVTable(void);
extern "C" void beNDMWLoadIntf2MesWin_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2MesWin_Register(void);
extern "C" void beNDMWLoadIntf2MesWin_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2MesWin_InitFields(void);
extern "C" igMetaObject *beNDMWLoadIntf2ComMdlCtrl_GetOrCreateMetaObject(void);
extern "C" void *beNDMWLoadIntf2ComMdlCtrl_GetReadyMetaObject(void);
extern "C" int beNDMWLoadIntf2ComMdlCtrl_GetVTable(void);
extern "C" void beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2ComMdlCtrl_Register(void);
extern "C" void beNDMWLoadIntf2ComMdlCtrl_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2ComMdlCtrl_InitFields(void);
extern "C" igMetaObject *beLoadIntf2ComMdlDataList_GetOrCreateMetaObject(void);
extern "C" void *beLoadIntf2ComMdlDataList_GetReadyMetaObject(void);
extern "C" int beLoadIntf2ComMdlDataList_GetVTable(void);
extern "C" void beLoadIntf2ComMdlDataList_EnsureRegistered(void);
extern "C" CallbackArray *beLoadIntf2ComMdlDataList_Register(void);
extern "C" void beLoadIntf2ComMdlDataList_GetMetaObject(void);
extern "C" void *beLoadIntf2ComMdlData_GetReadyMetaObject(void);
extern "C" int beLoadIntf2ComMdlData_GetVTable(void);
extern "C" void beLoadIntf2ComMdlData_EnsureRegistered(void);
extern "C" CallbackArray *beLoadIntf2ComMdlData_Register(void);
extern "C" void beLoadIntf2ComMdlData_GetMetaObject(void);
extern "C" void beLoadIntf2ComMdlData_InitFields(void);
extern "C" igMetaObject *beNDMWLoadIntf2TextOrder_GetOrCreateMetaObject(void);
extern "C" void *beNDMWLoadIntf2TextOrder_GetReadyMetaObject(void);
extern "C" int beNDMWLoadIntf2TextOrder_GetVTable(void);
extern "C" void beNDMWLoadIntf2TextOrder_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadIntf2TextOrder_Register(void);
extern "C" void beNDMWLoadIntf2TextOrder_GetMetaObject(void);
extern "C" void beNDMWLoadIntf2TextOrder_InitFields(void);
extern "C" void *beNDMWLoadCtrl2CtrlData_GetReadyMetaObject(void);
extern "C" int beNDMWLoadCtrl2CtrlData_GetVTable(void);
extern "C" void beNDMWLoadCtrl2CtrlData_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadCtrl2CtrlData_Register(void);
extern "C" void beNDMWLoadCtrl2CtrlData_GetMetaObject(void);
extern "C" void beNDMWLoadCtrl2CtrlData_InitFields(void);
extern "C" igMetaObject *beNDMWLoadCtrl2_GetOrCreateMetaObject(void);
extern "C" int beNDMWLoadCtrl2_GetVTable(void);
extern "C" void beNDMWLoadCtrl2_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWLoadCtrl2_Register(void);
extern "C" void beNDMWLoadCtrl2_GetMetaObject(void);
extern "C" void beNDMWLoadCtrl2_InitFields(void);
extern "C" int beNDMWItemWaza_GetVTable(void);
extern "C" void beNDMWItemWaza_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemWaza_Register(void);
extern "C" void beNDMWItemWaza_GetMetaObject(void);
extern "C" igMetaObject *beNDMWItemBase_GetPublishedMetaObject(void);
extern "C" void beNDMWItemWaza_InitFields(void);
extern "C" int beNDMWItemImportant_GetVTable(void);
extern "C" void beNDMWItemImportant_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemImportant_Register(void);
extern "C" void beNDMWItemImportant_GetMetaObject(void);
extern "C" int beNDMWItemInstant_GetVTable(void);
extern "C" void beNDMWItemInstant_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemInstant_Register(void);
extern "C" void beNDMWItemInstant_GetMetaObject(void);
extern "C" void beNDMWItemInstant_InitFields(void);
extern "C" igMetaObject *beNDMWItemDisk_GetOrCreateMetaObject(void);
extern "C" void *beNDMWItemDisk_GetReadyMetaObject(void);
extern "C" int beNDMWItemDisk_GetVTable(void);
extern "C" void beNDMWItemDisk_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemDisk_Register(void);
extern "C" void beNDMWItemDisk_GetMetaObject(void);
extern "C" void beNDMWItemDisk_InitFields(void);
extern "C" void *beNDMWItemAbilityChip_GetReadyMetaObject(void);
extern "C" int beNDMWItemAbilityChip_GetVTable(void);
extern "C" void beNDMWItemAbilityChip_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemAbilityChip_Register(void);
extern "C" void beNDMWItemAbilityChip_GetMetaObject(void);
extern "C" void *beNDMWItemYellowArmor_GetReadyMetaObject(void);
extern "C" int beNDMWItemYellowArmor_GetVTable(void);
extern "C" void beNDMWItemYellowArmor_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemYellowArmor_Register(void);
extern "C" void beNDMWItemYellowArmor_GetMetaObject(void);
extern "C" igMetaObject *beNDMWItemRevisionBase_GetPublishedMetaObject(void);
extern "C" void *beNDMWItemBlueArmor_GetReadyMetaObject(void);
extern "C" int beNDMWItemBlueArmor_GetVTable(void);
extern "C" void beNDMWItemBlueArmor_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemBlueArmor_Register(void);
extern "C" void beNDMWItemBlueArmor_GetMetaObject(void);
extern "C" igMetaObject *beNDMWItemRevisionPocketBase_GetPublishedMetaObject(void);
extern "C" void *beNDMWItemWeapon_GetReadyMetaObject(void);
extern "C" int beNDMWItemWeapon_GetVTable(void);
extern "C" void beNDMWItemWeapon_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemWeapon_Register(void);
extern "C" void beNDMWItemWeapon_GetMetaObject(void);
extern "C" void *beNDMWItemRevisionPocketBase_GetReadyMetaObject(void);
extern "C" void beNDMWItemRevisionPocketBase_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemRevisionPocketBase_Register(void);
extern "C" void beNDMWItemRevisionPocketBase_GetMetaObject(void);
extern "C" void beNDMWItemRevisionPocketBase_InitFields(void);
extern "C" void *beNDMWItemRevisionBase_GetReadyMetaObject(void);
extern "C" void beNDMWItemRevisionBase_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemRevisionBase_Register(void);
extern "C" void beNDMWItemRevisionBase_GetMetaObject(void);
extern "C" void beNDMWItemRevisionBase_InitFields(void);
extern "C" igMetaObject *beNDMWItemBaseList_GetOrCreateMetaObject(void);
extern "C" void *beNDMWItemBaseList_GetReadyMetaObject(void);
extern "C" int beNDMWItemBaseList_GetVTable(void);
extern "C" void beNDMWItemBaseList_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemBaseList_Register(void);
extern "C" void beNDMWItemBaseList_GetMetaObject(void);
extern "C" igMetaObject *beNDMWItemBase_GetOrCreateMetaObject(void);
extern "C" void *beNDMWItemBase_ResolveMetaObject(void);
extern "C" void beNDMWItemBase_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWItemBase_Register(void);
extern "C" void beNDMWItemBase_GetMetaObject(void);
extern "C" void beNDMWItemBase_InitFields(void);
extern "C" igMetaObject *beNDMWShinkaCtrl_GetOrCreateMetaObject(void);
extern "C" void *beNDMWShinkaCtrl_ResolveMetaObject(void);
extern "C" int beNDMWShinkaCtrl_GetVTable(void);
extern "C" void beNDMWShinkaCtrl_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShinkaCtrl_Register(void);
extern "C" void beNDMWShinkaCtrl_GetMetaObject(void);
extern "C" void beNDMWShinkaCtrl_InitFields(void);
extern "C" igMetaObject *beNDMWShinkaObjectList_GetOrCreateMetaObject(void);
extern "C" int beNDMWShinkaObjectList_GetVTable(void);
extern "C" void beNDMWShinkaObjectList_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShinkaObjectList_Register(void);
extern "C" void beNDMWShinkaObjectList_GetMetaObject(void);
extern "C" int beNDMWShinkaObject_GetVTable(void);
extern "C" void beNDMWShinkaObject_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWShinkaObject_Register(void);
extern "C" void beNDMWShinkaObject_GetMetaObject(void);
extern "C" void beNDMWShinkaObject_InitFields(void);
extern "C" igMetaObject *beNDMWGameRam_GetOrCreateMetaObject(void);
extern "C" int beNDMWGameRam_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beDataObjListList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" void beNDMWGameRam_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWGameRam_Register(void);
extern "C" void beNDMWGameRam_GetMetaObject(void);
extern "C" void beNDMWGameRam_InitFields(void);
extern "C" int beNDMWGameRamInfoRam_GetVTable(void);
extern "C" void beNDMWGameRamInfoRam_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWGameRamInfoRam_Register(void);
extern "C" void beNDMWGameRamInfoRam_GetMetaObject(void);
extern "C" void *beNDMWGameRamInfo_ResolveMetaObject(void);
extern "C" int beNDMWGameRamInfo_GetVTable(void);
extern "C" void beNDMWGameRamInfo_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWGameRamInfo_Register(void);
extern "C" void beNDMWGameRamInfo_GetMetaObject(void);
extern "C" void *beNDMWAfsSetupInfo_ResolveMetaObject(void);
extern "C" int igSmartPointer_igAdxAfsFileList_Destruct(void *, int);
extern "C" int beNDMWAfsSetupInfo_GetVTable(void);
extern "C" void beNDMWAfsSetupInfo_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWAfsSetupInfo_Register(void);
extern "C" void beNDMWAfsSetupInfo_GetMetaObject(void);
extern "C" void beNDMWAfsSetupInfo_InitFields(void);
extern "C" igMetaObject *beNDMWAfsSetupDataList_GetOrCreateMetaObject(void);
extern "C" void *beNDMWAfsSetupDataList_ResolveMetaObject(void);
extern "C" int beNDMWAfsSetupDataList_GetVTable(void);
extern "C" void beNDMWAfsSetupDataList_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWAfsSetupDataList_Register(void);
extern "C" void beNDMWAfsSetupDataList_GetMetaObject(void);
extern "C" void *beNDMWAfsSetupData_ResolveMetaObject(void);
extern "C" int beNDMWAfsSetupData_GetVTable(void);
extern "C" void beNDMWAfsSetupData_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWAfsSetupData_Register(void);
extern "C" void beNDMWAfsSetupData_GetMetaObject(void);
extern "C" void beNDMWAfsSetupData_InitFields(void);
extern "C" int beNDMWAfsStageLoad_GetVTable(void);
extern "C" void beNDMWAfsStageLoad_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWAfsStageLoad_Register(void);
extern "C" void beNDMWAfsStageLoad_GetMetaObject(void);
extern "C" void beNDMWAfsStageLoad_InitFields(void);
extern "C" igMetaObject *beNDMWAfsSetup_GetOrCreateMetaObject(void);
extern "C" void *beNDMWAfsSetup_ResolveMetaObject(void);
extern "C" int beNDMWAfsSetup_GetVTable(void);
extern "C" void beNDMWAfsSetup_EnsureRegistered(void);
extern "C" CallbackArray *beNDMWAfsSetup_Register(void);
extern "C" void beNDMWAfsSetup_GetMetaObject(void);
extern "C" void beNDMWAfsSetup_InitFields(void);
extern "C" igMetaObject *beNDMWAfsSetupData_GetMeta(void);
extern "C" igMetaObject *beNDMWAfsSetupDataList_GetMeta(void);
extern "C" igMetaObject *beNDMWAfsSetupDataList_GetElementMeta(void);
extern "C" igMetaObject *beNDMWAfsSetupInfo_GetMeta(void);
extern "C" igMetaObject *beNDMWGameRamInfo_GetMeta(void);
extern "C" igMetaObject *beNDMWGameRamInfoRam_GetMeta(void);
extern "C" igMetaObject *beNDMWShinkaObject_GetMeta(void);
extern "C" igMetaObject *beNDMWShinkaObjectList_GetMeta(void);
extern "C" igMetaObject *beNDMWShinkaObjectList_GetElementMeta(void);
extern "C" igMetaObject *beNDMWShinkaCtrl_GetMeta(void);
extern "C" igMetaObject *beNDMWItemBaseList_GetMeta(void);
extern "C" igMetaObject *beNDMWItemBaseList_GetElementMeta(void);
extern "C" int beNDMWItemBase_Use(void);
extern "C" int beNDMWItemBase_Pack(void);
extern "C" void beNDMWItemBase_Unpack(void);
extern "C" igMetaObject *beNDMWLoadCtrl2CtrlData_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2TextOrder_GetMeta(void);
extern "C" igMetaObject *beLoadIntf2ComMdlData_GetMeta(void);
extern "C" igMetaObject *beLoadIntf2ComMdlDataList_GetMeta(void);
extern "C" igMetaObject *beLoadIntf2ComMdlDataList_GetElementMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2ComMdlCtrl_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2MesWin_GetMeta(void);
extern "C" igMetaObject *beNDMWDegiData_GetMeta(void);
extern "C" igMetaObject *beNDMWDegiDataList_GetMeta(void);
extern "C" igMetaObject *beNDMWDegiDataList_GetElementMeta(void);
extern "C" igMetaObject *beNDMWLoadSlotPlayer_GetMeta(void);
extern "C" void beNDMWLoadSlotPlayer_userConstruct(beNDMWLoadSlotPlayer *self);
extern "C" igMetaObject *beNDMWLoadSlotPlayerList_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadSlotPlayerList_GetElementMeta(void);
extern "C" igMetaObject *beNDMWMcSlotPS2_GetMeta(void);
extern "C" igMetaObject *beNDMWMcSlotGC_GetMeta(void);
extern "C" igMetaObject *beNDMWMcSlotXbox_GetMeta(void);
extern "C" igMetaObject *beNDMWMcSlotList_GetMeta(void);
extern "C" igMetaObject *beNDMWMcSlotList_GetElementMeta(void);
extern "C" igMetaObject *beNDMWLoadSavePlWork_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadSavePlWorkList_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadSavePlWorkList_GetElementMeta(void);
extern "C" igMetaObject *beNDMWMcUtilCtrl_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadCtrl2CommonIntf_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadCtrl2Info_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2CtrlData_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2MakeChr_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2DegiState_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2DegiStateList_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2DegiStateList_GetElementMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2DegiStateCtrl_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2DataSelIntf_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2Diffselect_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2SelSlot_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2ChrDataSel_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2NameSel_GetMeta(void);
extern "C" igMetaObject *beNDMWLoadIntf2Info_GetMeta(void);
extern "C" igMetaObject *beNDMWLogoCtrlData_GetMeta(void);
extern "C" igMetaObject *beNDMWLogoInfo_GetMeta(void);
extern "C" igMetaObject *beNDMWMdlEnemyInfoWork_GetMeta(void);
extern "C" igMetaObject *beNDMWMdlItemInfoWork_GetMeta(void);
extern "C" igMetaObject *beNDMWMdlPlayerInfoWork_GetMeta(void);
extern "C" igMetaObject *beNDMWMdlPlayer2InfoWork_GetMeta(void);
extern "C" igMetaObject *beNDMWPanelObject_GetMeta(void);
extern "C" igMetaObject *beNDMWPanelWazaInfoWork_GetMeta(void);
extern "C" int *beNDMWPanelWazaInfoWork_igStringRef_ConstructFromText(int *ref, int text);
extern "C" igMetaObject *beNDMWPanelWazaInfoRam_GetMeta(void);
extern "C" igMetaObject *beNDMWPanelWazaInfo_GetMeta(void);
extern "C" igMetaObject *beNDMWSaveCtrlCtrlData_GetMeta(void);
extern "C" igMetaObject *beNDMWSaveCtrlInfo_GetMeta(void);
extern "C" igMetaObject *beNDMWSaveIntfCtrlData_GetMeta(void);
extern "C" igMetaObject *beSaveIntfComMdlData_GetMeta(void);
extern "C" igMetaObject *beSaveIntfComMdlDataList_GetMeta(void);
extern "C" igMetaObject *beSaveIntfComMdlDataList_GetElementMeta(void);
extern "C" igMetaObject *beNDMWSaveIntfComMdlCtrl_GetMeta(void);
extern "C" igMetaObject *beNDMWSaveIntfInfo_GetMeta(void);
extern "C" igMetaObject *beNDMWStageCtlInfo_GetMeta(void);
extern "C" igMetaObject *beNDMWStageCtlInfoRam_GetMeta(void);
extern "C" igMetaObject *beNDMWWindowCtrl_GetMeta(void);
extern "C" igMetaObject *beNDMWStatusInfoWork_GetMeta(void);
extern "C" igMetaObject *beNDMWStatusInfoRam_GetMeta(void);
extern "C" igMetaObject *beNDMWStatusInfo_GetMeta(void);
extern "C" igMetaObject *beNDMWWindow_GetMeta(void);
extern "C" igMetaObject *beNDMWTitle2CtrlData_GetMeta(void);
extern "C" igMetaObject *beNDMWTitle2Option_GetMeta(void);
extern "C" igMetaObject *beNDMWTitle2Info_GetMeta(void);
extern "C" igMetaObject *beNDMWWindowList_GetMeta(void);
extern "C" igMetaObject *beNDMWWindowList_GetElementMeta(void);
extern "C" igMetaObject *libNdmwRuntimePlugin_GetMetaObject(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWAfsSetup_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWPanelWaza_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWLogo_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWLoadCtrl2_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWSaveCtrl_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWSaveIntf_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPlayer2_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlEnemy_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlItem_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlMapBase_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlMapCursor_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igMetaObject *g_beNDMWWindowList_metaObject;
extern "C" igMetaObject *beNDMWWindowList_GetMetaObject(void);
extern "C" int g_beNDMWWindowList_vtable[4];
extern "C" igMetaObject *g_beNDMWWindow_metaObject;
extern "C" int g_beNDMWTitle2Info_vtable[4];
extern "C" igMetaObject *g_beNDMWTitle2Option_metaObject;
extern "C" int g_beNDMWTitle2Option_vtable[4];
extern "C" igMetaObject *g_beNDMWTitle2CtrlData_metaObject;
extern "C" int g_beNDMWTitle2CtrlData_vtable[4];
extern "C" int g_beNDMWTitle2_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMcUtilCtrl_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" int g_beNDMWShopTitle03_vtable[4];
extern "C" int g_beNDMWWindow_vtable[4];
extern "C" void *beNDMWWindow_Destroy(beNDMWWindowCtrl *self, short flags);
extern "C" int g_beNDMWWindowTitle_vtable[4];
extern "C" int g_beNDMWShopTitle01_vtable[4];
extern "C" int g_beNDMWShopTitle00_vtable[4];
extern "C" int g_beNDMWStatusTitle04_vtable[4];
extern "C" int g_beNDMWStatusTitle03_vtable[4];
extern "C" igMetaObject *beNDMWStatusTitle02_GetMetaObject(void);
extern "C" int g_beNDMWStatusTitle02_vtable[4];
extern "C" igMetaObject *beNDMWStatusTitle01_GetMetaObject(void);
extern "C" int g_beNDMWStatusTitle01_vtable[4];
extern "C" igMetaObject *beNDMWStatusTitle00_GetMetaObject(void);
extern "C" int g_beNDMWStatusTitle00_vtable[4];
extern "C" igMetaObject *beNDMWWindowTitle_GetMetaObject(void);
extern "C" int g_beNDMWShopSelectB0_vtable[4];
extern "C" int g_beNDMWWindowSelect_vtable[4];
extern "C" void *beNDMWWindowSelect_Destroy(beNDMWWindowSelect *self, short flags);
extern "C" int g_beNDMWShopSelectA0_vtable[4];
extern "C" int g_beNDMWShopSelect52_vtable[4];
extern "C" int g_beNDMWShopSelect34_vtable[4];
extern "C" int g_beNDMWShopSelect11_vtable[4];
extern "C" int g_beNDMWShopSelect03_vtable[4];
extern "C" int g_beNDMWShopSelect02_vtable[4];
extern "C" int g_beNDMWShopSelect01_vtable[4];
extern "C" int g_beNDMWShopSelect00_vtable[4];
extern "C" int g_beNDMWStatusSelectE1_vtable[4];
extern "C" igMetaObject *beNDMWStatusSelectE0_GetMetaObject(void);
extern "C" int g_beNDMWStatusSelectE0_vtable[4];
extern "C" igMetaObject *beNDMWStatusSelect01_GetMetaObject(void);
extern "C" int g_beNDMWStatusSelect01_vtable[4];
extern "C" igMetaObject *beNDMWStatusSelect00_GetMetaObject(void);
extern "C" int g_beNDMWStatusSelect00_vtable[4];
extern "C" igMetaObject *beNDMWWindowSelect_GetMetaObject(void);
extern "C" int g_beNDMWStatusInfo_vtable[4];
extern "C" igMetaObject *g_beNDMWStatusInfoRam_metaObject;
extern "C" int g_beBaseInfoRam_vtable[4];
extern "C" int g_beNDMWStatusInfoRam_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWStatusInfoWork_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igMetaObject *g_beNDMWStatusInfoWork_metaObject;
extern "C" int g_beNDMWStatusInfoWork_vtable[4];
extern "C" int g_beNDMWShopJunk_vtable[4];
extern "C" int g_beNDMWWindowCtrl_vtable[4];
extern "C" int g_beNDMWWindow_vtable[4];
extern "C" beNDMWWindowCtrl *beNDMWWindowCtrl_Destroy(beNDMWWindowCtrl *self, long long flags);
/* beNDMWShopCtrl00 factory and metadata forwards plus the published parent-class accessor. The
 * shop controller is created by the shared igMetaObject machinery: the metadata handle is
 * registered lazily and the instance comes from igMetaObject_CreateInstance, not a C++
 * constructor. */

extern "C" igMetaObject *g_beNDMWWindowCtrl_metaObject;
extern "C" igMetaObject *beNDMWWindowCtrl_GetPublishedMetaObject();
extern "C" igMetaObject *beNDMWShopCtrl00_ResolveMetaObject();
extern "C" igMetaObject *beNDMWShopCtrl00_GetMetaObject();
extern "C" int g_beNDMWShopDevice_vtable[4];
extern "C" int g_beNDMWWindowCtrl_vtable[4];
extern "C" int g_beNDMWListCtrl_vtable[4];
extern "C" int g_beNDMWShopCtrlXdataChip_vtable[4];
extern "C" int g_beNDMWShopCtrlSales_vtable[4];
extern "C" int g_beNDMWShopCtrlDiskSell_vtable[4];
extern "C" int g_beNDMWShopCtrlDeviceSell_vtable[4];
extern "C" int g_beNDMWShopCtrlSell_vtable[4];
extern "C" igMetaObject *beNDMWShopCtrlEditBit_GetMetaObject(void);
extern "C" int g_beNDMWShopCtrlEditBit_vtable[4];
extern "C" igMetaObject *beNDMWShopCtrlDigilabo_GetMetaObject(void);
extern "C" int g_beNDMWShopCtrlDigilabo_vtable[4];
extern "C" igMetaObject *beNDMWShopCtrlA2_GetMetaObject(void);
extern "C" int g_beNDMWShopCtrlA2_vtable[4];
extern "C" igMetaObject *beNDMWShopCtrlA1_GetMetaObject(void);
extern "C" int g_beNDMWShopCtrlA1_vtable[4];
extern "C" int g_beNDMWShopCtrlA0_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWStatusTitle03_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" int g_beNDMWShopCtrl50_vtable[4];
extern "C" int g_beNDMWShopCtrl40_vtable[4];
extern "C" int g_beNDMWShopCtrl30_vtable[4];
extern "C" int g_beNDMWShopCtrlEvolve_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWShinkaCtrl_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" int g_beNDMWShopCtrl10_vtable[4];
extern "C" int g_beNDMWShopCtrl00_vtable[4];
extern "C" int g_beNDMWStatusSubMenu_vtable[4];
extern "C" int g_beNDMWStatusCtrlSkill_vtable[4];
extern "C" int g_beNDMWStatusCtrlSendBit_vtable[4];
extern "C" int g_beNDMWStatusCtrlBit_vtable[4];
extern "C" igMetaObject *beNDMWStatusCtrlDisk_GetMetaObject(void);
extern "C" int g_beNDMWStatusCtrlDisk_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWItemDisk_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igMetaObject *beNDMWStatusCtrlFlag_GetMetaObject(void);
extern "C" int g_beNDMWStatusCtrlFlag_vtable[4];
extern "C" igMetaObject *beNDMWStatusCtrlFolder_GetMetaObject(void);
extern "C" int g_beNDMWStatusCtrlFolder_vtable[4];
extern "C" igMetaObject *beNDMWStatusSubSlot_GetMetaObject(void);
extern "C" int g_beNDMWStatusSubSlot_vtable[4];
extern "C" int g_beNDMWStatusCtrlBaseEquip_vtable[4];
extern "C" void *beNDMWStatusCtrlBaseEquip_Destroy(beNDMWStatusCtrlBaseEquip *self, short flags);
extern "C" int g_beNDMWStatusCtrlBaseEquip_vtable[4];
extern "C" void *beNDMWStatusCtrlBaseEquip_Construct(beNDMWStatusCtrlBaseEquip *self);
extern "C" int g_beNDMWStatusMainSlot_vtable[4];
extern "C" int g_beNDMWStatusPowerSocket_vtable[4];
extern "C" int g_beNDMWStatusCtrlEquip_vtable[4];
extern "C" int g_beNDMWStatusCtrlD0_vtable[4];
extern "C" int g_beNDMWStatusCtrl00_vtable[4];
extern "C" int g_beNDMWStatus_vtable[4];
extern "C" igMetaObject *g_beNDMWStageCtlInfoRam_metaObject;
extern "C" int g_beNDMWStageCtlInfoRam_vtable[4];
extern "C" igMetaObject *beNDMWStageCtlInfo_GetMetaObject(void);
extern "C" int g_beNDMWStageCtlInfo_vtable[4];
extern "C" igMetaObject *beNDMWStageCtl_GetMetaObject(void);
extern "C" int g_beNDMWStageCtl_vtable[4];
extern "C" int g_beBaseInfoManager_vtable[4];
extern "C" igMetaObject *beNDMWSaveIntfInfo_GetMetaObject(void);
extern "C" int g_beNDMWSaveIntfInfo_vtable[4];
extern "C" igMetaObject *g_beNDMWSaveIntfComMdlCtrl_metaObject;
extern "C" igMetaObject *beNDMWSaveIntfComMdlCtrl_GetMetaObject(void);
extern "C" int g_beNDMWSaveIntfComMdlCtrl_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beSaveIntfComMdlDataList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igMetaObject *g_beSaveIntfComMdlDataList_metaObject;
extern "C" int g_beSaveIntfComMdlDataList_vtable[4];
extern "C" igMetaObject *g_beSaveIntfComMdlData_metaObject;
extern "C" int g_beSaveIntfComMdlData_vtable[4];
extern "C" igMetaObject *g_beNDMWSaveIntfCtrlData_metaObject;
extern "C" int g_beNDMWSaveIntfCtrlData_vtable[4];
extern "C" int g_beNDMWSaveIntf_vtable[4];
extern "C" int g_beNDMWSaveCtrlInfo_vtable[4];
extern "C" igMetaObject *g_beNDMWSaveCtrlCtrlData_metaObject;
extern "C" int g_beNDMWSaveCtrlCtrlData_vtable[4];
extern "C" int g_beNDMWSaveCtrl_vtable[4];
extern "C" int g_beNDMWPanelWazaInfo_vtable[4];
extern "C" igMetaObject *g_beNDMWPanelWazaInfoRam_metaObject;
typedef struct WazaInfoRamRefHeader { char pad4[4]; int f4; } WazaInfoRamRefHeader;
extern "C" int g_beNDMWPanelWazaInfoRam_vtable[4];
extern "C" igSmartPointer<igObject> *beNDMWPanelWazaInfoRam_igSmartPointer_igObject_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igMetaObject *g_beNDMWPanelWazaInfoWork_metaObject;
extern "C" igMetaObject *beNDMWPanelWazaInfoWork_ResolveMetaObject(void);
extern "C" int g_beNDMWPanelWazaInfoWork_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWPanelObjectWaza_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWMdlPlayerInfoWork_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igMetaObject *beNDMWPanelObjectStat_ResolveMetaObject(void);
extern "C" int g_beNDMWPanelObjectStat_vtable[4];
extern "C" int g_beNDMWPanelObject_vtable[4];
extern "C" beNDMWPanelObject *beNDMWPanelObject_Destroy(beNDMWPanelObject *self, short flags);
extern "C" igMetaObject *g_beNDMWPanelObject_metaObject;
extern "C" igMetaObject *beNDMWPanelObjectItem_ResolveMetaObject(void);
extern "C" int g_beNDMWPanelObjectItem_vtable[4];
extern "C" igMetaObject *beNDMWPanelObjectWaza_ResolveMetaObject(void);
extern "C" int g_beNDMWPanelObjectWaza_vtable[4];
extern "C" igMetaObject *beNDMWPanelObject_ResolveMetaObject(void);
extern "C" int g_beNDMWPanelWaza_vtable[4];
extern "C" int g_beNDMWMdlPlayer2_vtable[4];
extern "C" int g_beModelCtrl_vtable[4];
extern "C" beModelCtrl *beModelCtrl_Destroy(beModelCtrl *self, short flags);
extern "C" igMetaObject *g_beNDMWMdlPlayer2InfoWork_metaObject;
extern "C" int g_beNDMWMdlPlayer2InfoWork_vtable[4];
extern "C" int g_beModelCtrlInfoWork_vtable[4];
extern "C" void *beModelCtrlInfoWork_Construct(beModelCtrlInfoWork *self);
extern "C" int g_beNDMWMdlPlayer_vtable[4];
extern "C" int g_beNDMWMdlPEBase_vtable[4];
extern "C" beNDMWMdlPEBase *beNDMWMdlPEBase_Destroy(beNDMWMdlPEBase *self, short flags);
extern "C" igMetaObject *g_beNDMWMdlPlayerInfoWork_metaObject;
extern "C" igMetaObject *beNDMWMdlPlayerInfoWork_ResolveMetaObject(void);
extern "C" int g_beNDMWMdlPlayerInfoWork_vtable[4];
/* An igObjectRefMetaField member. */
struct ObjectRefField { int *p; ObjectRefField() throw(); ~ObjectRefField(); };
/* An igStringMetaField member. */
struct StringRef { int *p; StringRef() throw(); ~StringRef(); };
/* igObject, constructed by igObject_InitHeader. */
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
/* The members of beModelCtrlInfoWork whose constructors and destructors are called out of line, one
 * class per member type. */
struct HpField { int *p; HpField() throw(); ~HpField(); };
struct ComDataField { int *p; ComDataField() throw(); ~ComDataField(); };
struct LabelListField { int *p; LabelListField() throw(); ~LabelListField(); };
struct MoveDataListField { int *p; MoveDataListField() throw(); ~MoveDataListField(); };
struct AIField { int *p; AIField() throw(); ~AIField(); };
struct PosLockNodeField { int *p; PosLockNodeField() throw(); ~PosLockNodeField(); };
struct PosLockTrcField { int *p; PosLockTrcField() throw(); ~PosLockTrcField(); };
struct MoveObjectListField { int *p; MoveObjectListField() throw(); ~MoveObjectListField(); };
struct RideOnDataField { int *p; RideOnDataField() throw(); ~RideOnDataField(); };
struct DebugHitBoxNodeField { int *p; DebugHitBoxNodeField() throw(); ~DebugHitBoxNodeField(); };
struct HitBodyField { int *p; HitBodyField() throw(); ~HitBodyField(); };
struct SubCommandField { int *p; SubCommandField() throw(); ~SubCommandField(); };
struct BaseAABoxField { int *p; BaseAABoxField() throw(); ~BaseAABoxField(); };
/* An igVec3fMetaField member. */
struct Vec3Field { float v[3]; Vec3Field() throw(); };
/* Stores the beModelCtrlInfoWork vtable before the first member constructor runs. */
struct ModelCtrlInfoWorkVtable { ModelCtrlInfoWorkVtable(int **slot) { *slot = g_beModelCtrlInfoWork_vtable; } };
/* matching construct: hand-written view of beModelCtrlInfoWork (see beNDMWMdlPlayerInfoWork_GetVTable) */
struct ModelCtrlInfoWorkView : igObjectView, ModelCtrlInfoWorkVtable {
    HpField mHp;                                    /* +8   _mHp */
    HpField hp;                                     /* +12  _hp */
    int recNo;                                      /* +16  _recNo */
    StringRef seqCodeName;                          /* +20  _seqCodeName */
    ComDataField comData;                           /* +24  _comData */
    int comIndex;                                   /* +28  _comIndex */
    int comLabelCount;                              /* +32  _comLabelCount */
    LabelListField labelSeqList;                    /* +36  _labelSeqList */
    LabelListField labelNameList;                   /* +40  _labelNameList */
    ObjectRefField labelOffsetList;                 /* +44  _labelOffsetList */
    StringRef luaBHit;                              /* +48  _luaBHit */
    StringRef luaWHit;                              /* +52  _luaWHit */
    StringRef luaFHit;                              /* +56  _luaFHit */
    int ctrlSt0;                                    /* +60  _ctrlSt0 */
    int ctrlSt1;                                    /* +64  _ctrlSt1 */
    unsigned char isOnCtrl;                         /* +68  _isOnCtrl */
    unsigned char isOnFreeze;                       /* +69  _isOnFreeze */
    MoveDataListField pdMoveDataList;               /* +72  _pdMoveDataList */
    StringRef wCheckName;                           /* +76  _wCheckName */
    AIField aI;                                     /* +80  _aI */
    float aIHOffsetY;                               /* +84  _aIHOffsetY */
    StringRef targetMode;                           /* +88  _targetMode */
    StringRef targetKind;                           /* +92  _targetKind */
    StringRef targetSpc1;                           /* +96  _targetSpc1 */
    Vec3Field targetPos;                            /* +100 _targetPos */
    unsigned char keyInput;                         /* +112 _keyInput */
    StringRef keyEventName;                         /* +116 _keyEventName */
    unsigned char isHitCheck;                       /* +120 _isHitCheck */
    float mutekiCount;                              /* +124 _mutekiCount */
    Vec3Field targetDirection;                      /* +128 _targetDirection */
    Vec3Field directionLimiter;                     /* +140 _directionLimiter */
    Vec3Field direction;                            /* +152 _direction */
    float svLODHighRange;                           /* +164 _svLODHighRange */
    unsigned char isPosLock;                        /* +168 _isPosLock */
    PosLockNodeField posLockNode;                   /* +172 _posLockNode */
    PosLockTrcField posLockTrc;                     /* +176 _posLockTrc */
    StringRef posLockModelName;                     /* +180 _posLockModelName */
    StringRef posLockBoneName;                      /* +184 _posLockBoneName */
    Vec3Field posLockOffset;                        /* +188 _posLockOffset */
    MoveObjectListField moveObjectList;             /* +200 _moveObjectList */
    RideOnDataField rideOnData;                     /* +204 _rideOnData */
    DebugHitBoxNodeField debugHitBoxNode;           /* +208 _debugHitBoxNode */
    HitBodyField hitBody;                           /* +212 _hitBody */
    unsigned char isWallCheck;                      /* +216 _isWallCheck */
    unsigned char isFloorCheck;                     /* +217 _isFloorCheck */
    unsigned char isFallCheck;                      /* +218 _isFallCheck */
    StringRef hitParentName;                        /* +220 _hitParentName */
    int hitParentRamNo;                             /* +224 _hitParentRamNo */
    SubCommandField subCommand;                     /* +228 _subCommand */
    BaseAABoxField baseAABox;                       /* +232 _baseAABox */
    ModelCtrlInfoWorkView() : ModelCtrlInfoWorkVtable(&vtable) { }
    ~ModelCtrlInfoWorkView() { vtable = g_beModelCtrlInfoWork_vtable; }
};
/* The beNDMWMdlPEBaseInfoWork base. */
struct PEBaseInfoWorkView : ModelCtrlInfoWorkView {
    char basePad[240 - 236];                        /* the registered base ends at +236 */
    int dispRamNoList;                              /* +240 _dispRamNoList */
    int dispPosNoList;                              /* +244 _dispPosNoList */
    int timerList;                                  /* +248 _timerList */
    int isFirstList;                                /* +252 _isFirstList */
    int poisonDamage;                               /* +256 _poisonDamage */
    int poisonEndurance;                            /* +260 _poisonEndurance */
    int downDataList;                               /* +264 _downDataList */
    int upDataList;                                 /* +268 _upDataList */
    char ownFields[0x114 - 0x110];
    PEBaseInfoWorkView();
    ~PEBaseInfoWorkView();
};
/* Stores the derived vtable before the first member constructor runs. */
struct VtableInstall { VtableInstall(int **slot) { *slot = g_beNDMWMdlPlayerInfoWork_vtable; } };
/* matching construct: hand-written view of beNDMWMdlPlayerInfoWork (the second empty base places the
 * vtable store; a real virtual class would need __vt__ data that the build cannot bind) */
struct PlayerInfoWorkView : PEBaseInfoWorkView, VtableInstall {
    ObjectRefField turnAtkTimer;            /* +276 _turnAtkTimer */
    char ownFields[0x130 - 0x118];
    PlayerInfoWorkView() : VtableInstall(&vtable) { }
    ~PlayerInfoWorkView() { vtable = g_beNDMWMdlPlayerInfoWork_vtable; }
};
extern "C" int g_beModelCtrlInfoWork_vtable[4];
extern "C" int g_beNDMWMdlPEBaseInfoWork_vtable[4];
extern "C" beNDMWMdlPEBaseInfoWork *beNDMWMdlPEBaseInfoWork_Destroy(beNDMWMdlPEBaseInfoWork *self, short flags);
/* A 12-byte list member. */
struct PEBaseListField { int *p[3]; PEBaseListField() throw(); ~PEBaseListField(); };
/* The beModelCtrlInfoWork base. */
struct InfoBase { int *vtable; char baseFields[0xf0 - 4]; InfoBase(); ~InfoBase(); };
/* Stores the derived vtable before the first member constructor runs. */
struct VtableInstall_3c0640 { VtableInstall_3c0640(int **slot) { *slot = g_beNDMWMdlPEBaseInfoWork_vtable; } };
/* matching construct: hand-written view of beNDMWMdlPEBaseInfoWork (see beNDMWMdlPlayerInfoWork_GetVTable) */
struct PEBaseInfoWorkObj : InfoBase, VtableInstall_3c0640 {
    ObjectRefField ref0;                    /* +240 */
    ObjectRefField ref1;                    /* +244 */
    ObjectRefField ref2;                    /* +248 */
    PEBaseListField list;                   /* +252 */
    ObjectRefField ref3;                    /* +264 */
    ObjectRefField ref4;                    /* +268 */
    char ownFields[0x114 - 0x110];
    PEBaseInfoWorkObj() : VtableInstall_3c0640(&vtable) { }
    ~PEBaseInfoWorkObj() { vtable = g_beNDMWMdlPEBaseInfoWork_vtable; }
};
extern "C" int g_beNDMWMdlPBullet_vtable[4];
extern "C" int g_beNDMWMdlObject_vtable[4];
extern "C" int g_beNDMWMdlMapCursor_vtable[4];
extern "C" igMetaObject *beNDMWMdlMapBase_GetReadyMetaObject(void);
extern "C" int g_beNDMWMdlMapBase_vtable[4];
extern "C" igMetaObject *beNDMWMdlItem_GetReadyMetaObject(void);
extern "C" int g_beNDMWMdlItem_vtable[4];
extern "C" igMetaObject *g_beNDMWMdlItemInfoWork_metaObject;
extern "C" igMetaObject *beNDMWMdlItemInfoWork_GetReadyMetaObject(void);
extern "C" int g_beNDMWMdlItemInfoWork_vtable[4];
/* _itemObject (igObjectRefMetaField). */
struct ItemObjectField { int *p; ItemObjectField() throw(); ~ItemObjectField(); };
/* Stores the derived vtable before the first member constructor runs. */
struct VtableInstall_3c1480 { VtableInstall_3c1480(int **slot) { *slot = g_beNDMWMdlItemInfoWork_vtable; } };
/* matching construct: hand-written view of beNDMWMdlItemInfoWork (see beNDMWMdlPlayerInfoWork_GetVTable) */
struct ItemInfoWork : InfoBase, VtableInstall_3c1480 {
    ItemObjectField itemObject;             /* +240 _itemObject */
    char gap[0x104 - 0xf4];
    StringRef fontType;                     /* +260 _fontType */
    char ownFields[0x110 - 0x108];
    ItemInfoWork() : VtableInstall_3c1480(&vtable) { }
    ~ItemInfoWork() { vtable = g_beNDMWMdlItemInfoWork_vtable; }
};
extern "C" igMetaObject *beNDMWMdlEnemy_GetReadyMetaObject(void);
extern "C" int g_beNDMWMdlEnemy_vtable[4];
extern "C" igMetaObject *g_beNDMWMdlEnemyInfoWork_metaObject;
extern "C" int beNDMWMdlPEBaseInfoWork_Construct(beNDMWMdlPEBaseInfoWork *);
extern "C" int g_beNDMWMdlEnemyInfoWork_vtable[4];
extern "C" int g_beNDMWMdlEffect_vtable[4];
extern "C" int g_beNDMWMdlEBullet_vtable[4];
extern "C" int g_beNDMWLogoInfo_vtable[4];
extern "C" igMetaObject *g_beNDMWLogoCtrlData_metaObject;
extern "C" int g_beNDMWLogoCtrlData_vtable[4];
extern "C" int g_beNDMWLogo_vtable[4];
extern "C" int g_beNDMWLoadIntf2Info_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2NameSel_metaObject;
extern "C" int g_beNDMWLoadIntf2NameSel_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2ChrDataSel_metaObject;
extern "C" igMetaObject *beNDMWLoadIntf2ChrDataSel_ResolveMetaObject(void);
extern "C" int g_beNDMWLoadIntf2ChrDataSel_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2SelSlot_metaObject;
extern "C" igMetaObject *beNDMWLoadIntf2SelSlot_ResolveMetaObject(void);
extern "C" int g_beNDMWLoadIntf2SelSlot_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2Diffselect_metaObject;
extern "C" igMetaObject *beNDMWLoadIntf2Diffselect_ResolveMetaObject(void);
extern "C" int g_beNDMWLoadIntf2Diffselect_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2DataSelIntf_metaObject;
extern "C" igMetaObject *beNDMWLoadIntf2DataSelIntf_ResolveMetaObject(void);
extern "C" int g_beNDMWLoadIntf2DataSelIntf_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2DegiStateCtrl_metaObject;
extern "C" igMetaObject *beNDMWLoadIntf2DegiStateCtrl_ResolveMetaObject(void);
extern "C" int g_beNDMWLoadIntf2DegiStateCtrl_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2DegiStateList_metaObject;
extern "C" igMetaObject *beNDMWLoadIntf2DegiStateList_ResolveMetaObject(void);
extern "C" int g_beNDMWLoadIntf2DegiStateList_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2DegiState_metaObject;
extern "C" int g_beNDMWLoadIntf2DegiState_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2MakeChr_metaObject;
extern "C" igMetaObject *beNDMWLoadIntf2MakeChr_ResolveMetaObject(void);
extern "C" int g_beNDMWLoadIntf2MakeChr_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2CtrlData_metaObject;
extern "C" int g_beNDMWLoadIntf2CtrlData_vtable[4];
extern "C" int g_beNDMWLoadIntf2_vtable[4];
extern "C" igMetaObject *beNDMWLoadCtrl2Info_ResolveMetaObject(void);
extern "C" int g_beNDMWLoadCtrl2Info_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadCtrl2CommonIntf_metaObject;
extern "C" igMetaObject *beNDMWLoadCtrl2CommonIntf_ResolveMetaObject(void);
extern "C" int g_beNDMWLoadCtrl2CommonIntf_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWLoadSlotPlayerList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igMetaObject *g_beNDMWMcUtilCtrl_metaObject;
extern "C" int g_beNDMWMcUtilCtrl_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadSavePlWorkList_metaObject;
extern "C" int g_beNDMWLoadSavePlWorkList_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadSavePlWork_metaObject;
extern "C" int g_beNDMWLoadSavePlWork_vtable[4];
extern "C" igMetaObject *g_beNDMWMcSlotList_metaObject;
extern "C" int g_beNDMWMcSlotList_vtable[4];
extern "C" igMetaObject *g_beNDMWMcSlotXbox_metaObject;
extern "C" igMetaObject *beNDMWMcSlotXbox_GetReadyMetaObject(void);
extern "C" int g_beNDMWMcSlotXbox_vtable[4];
extern "C" igMetaObject *g_beNDMWMcSlotGC_metaObject;
extern "C" igMetaObject *beNDMWMcSlotGC_GetReadyMetaObject(void);
/* Stack object, vtable slot read through the object plus a runtime offset. */
extern "C" int g_beNDMWMcSlotGC_vtable[4];
extern "C" igMetaObject *g_beNDMWMcSlotPS2_metaObject;
extern "C" igMetaObject *beNDMWMcSlotPS2_GetReadyMetaObject(void);
extern "C" int g_beNDMWMcSlotPS2_vtable[4];
extern "C" igMetaObject *g_beNDMWMcSlot_metaObject;
extern "C" igMetaObject *g_beNDMWLoadSlotPlayerList_metaObject;
extern "C" int g_beNDMWLoadSlotPlayerList_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadSlotPlayer_metaObject;
extern "C" int g_beNDMWLoadSlotPlayer_vtable[4];
extern "C" igMetaObject *g_beNDMWDegiDataList_metaObject;
extern "C" int g_beNDMWDegiDataList_vtable[4];
extern "C" igMetaObject *g_beNDMWDegiData_metaObject;
extern "C" int g_beNDMWDegiData_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2MesWin_metaObject;
extern "C" int g_beNDMWLoadIntf2MesWin_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2ComMdlCtrl_metaObject;
extern "C" int g_beNDMWLoadIntf2ComMdlCtrl_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beLoadIntf2ComMdlDataList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igMetaObject *g_beLoadIntf2ComMdlDataList_metaObject;
extern "C" int g_beLoadIntf2ComMdlDataList_vtable[4];
extern "C" igMetaObject *g_beLoadIntf2ComMdlData_metaObject;
extern "C" int g_beLoadIntf2ComMdlData_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadIntf2TextOrder_metaObject;
extern "C" int g_beNDMWLoadIntf2TextOrder_vtable[4];
extern "C" igMetaObject *g_beNDMWLoadCtrl2CtrlData_metaObject;
extern "C" int g_beNDMWLoadCtrl2CtrlData_vtable[4];
extern "C" igMetaObject *beNDMWLoadCtrl2_GetReadyMetaObject(void);
extern "C" int g_beNDMWLoadCtrl2_vtable[4];
extern "C" igMetaObject *beNDMWItemWaza_GetReadyMetaObject(void);
extern "C" int g_beNDMWItemWaza_vtable[4];
extern "C" igMetaObject *beNDMWItemImportant_GetReadyMetaObject(void);
extern "C" int g_beNDMWItemImportant_vtable[4];
extern "C" igMetaObject *beNDMWItemInstant_GetReadyMetaObject(void);
extern "C" int g_beNDMWItemInstant_vtable[4];
extern "C" int g_beNDMWItemDisk_vtable[4];
extern "C" int g_beNDMWItemAbilityChip_vtable[4];
extern "C" int g_beNDMWItemYellowArmor_vtable[4];
extern "C" int g_beNDMWItemBlueArmor_vtable[4];
extern "C" int g_beNDMWItemWeapon_vtable[4];
extern "C" igMetaObject *g_beNDMWItemRevisionPocketBase_metaObject;
extern "C" igMetaObject *g_beNDMWItemRevisionBase_metaObject;
extern "C" igMetaObject *g_beNDMWItemBaseList_metaObject;
extern "C" int g_beNDMWItemBaseList_vtable[4];
extern "C" igMetaObject *g_beNDMWItemBase_metaObject;
extern "C" igMetaObject *g_beNDMWShinkaCtrl_metaObject;
extern "C" int g_beNDMWShinkaCtrl_vtable[4];
extern "C" igMetaObject *g_beNDMWShinkaObjectList_metaObject;
extern "C" igMetaObject *beNDMWShinkaObjectList_ResolveMetaObject(void);
extern "C" int g_beNDMWShinkaObjectList_vtable[4];
extern "C" igMetaObject *g_beNDMWShinkaObject_metaObject;
extern "C" igMetaObject *beNDMWShinkaObject_ResolveMetaObject(void);
extern "C" int g_beNDMWShinkaObject_vtable[4];
/* Cached FightCom metadata enum: 22 command names built once and cached. */

extern "C" igMetaObject *beNDMWGameRam_ResolveMetaObject(void);
extern "C" int g_beNDMWGameRam_vtable[4];
extern "C" igMetaObject *g_beNDMWGameRamInfoRam_metaObject;
extern "C" igMetaObject *beNDMWGameRamInfoRam_ResolveMetaObject(void);
extern "C" int g_beNDMWGameRamInfoRam_vtable[4];
extern "C" igMetaObject *g_beNDMWGameRamInfo_metaObject;
extern "C" int g_beNDMWGameRamInfo_vtable[4];
/* kept local: no include/dw4 home; the definition still takes a placeholder view. */
extern "C" int g_beNDMWAfsSetupInfo_vtable[4];
extern "C" igSmartPointer<igObject> *igSmartPointer_beNDMWAfsSetupDataList_Destruct(igSmartPointer<igObject> *self,int delete_storage);
extern "C" igMetaObject *g_beNDMWAfsSetupDataList_metaObject;
/* Stack object, vtable slot read through the object plus a runtime offset. */
extern "C" int g_beNDMWAfsSetupDataList_vtable[4];
extern "C" igMetaObject *g_beNDMWAfsSetupData_metaObject;
extern "C" int g_beNDMWAfsSetupData_vtable[4];
extern "C" igMetaObject *beNDMWAfsStageLoad_ResolveMetaObject(void);
extern "C" int g_beNDMWAfsStageLoad_vtable[4];
extern "C" int g_beNDMWAfsSetup_vtable[4];
extern "C" void beNDMWDegiData_userConstruct(beNDMWDegiData *self, int flag);
extern "C" void beNDMWDegiData_userDestruct(beNDMWDegiData *self);
extern "C" void beNDMWLoadSlotPlayer_userDestruct(beNDMWLoadSlotPlayer *self);
extern "C" void beNDMWMcUtilCtrl_userConstruct(beNDMWMcUtilCtrl *self);
extern "C" void beNDMWMcUtilCtrl_userDestruct(beNDMWMcUtilCtrl *self);
extern "C" void beNDMWLoadCtrl2CommonIntf_userDestruct(beNDMWLoadCtrl2CommonIntf *self);
/* kept local: no include/dw4 home declares it. */
/* Owning stack reference to a pooled string token it is handed (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit, inline. */
class HeldStringRef {
public:
    char *p;
    HeldStringRef(char *s) : p(s) {}
    ~HeldStringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h); } }
};
extern "C" void beNDMWPanelWazaInfoWork_userConstruct(beNDMWPanelWazaInfoWork *self);
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]). The constructor interns the text and the destructor releases the token on scope exit;
 * both are out of line. */
class InternedStringRef {
public:
    char *p;
    InternedStringRef(const char *text);
    ~InternedStringRef();
};
extern "C" void beNDMWPanelWazaInfoWork_TrimCapacity(beNDMWPanelWazaInfoWork *self);
extern "C" void beNDMWPanelObjectStat_TrimCapacity(beNDMWPanelObjectStat *self);
extern "C" void beNDMWPanelObjectItem_TrimCapacity(beNDMWPanelObjectItem *self);
extern "C" void beNDMWPanelObjectWaza_TrimCapacity(beNDMWPanelObjectWaza *self);
extern "C" int GAMERAM_3[4];
extern "C" int GETCOMMON_2[4];
extern "C" int CAMERAMODE_2[4];
extern "C" int LIGHTMODE_2[4];

#endif
