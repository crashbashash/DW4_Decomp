# Typed game layer: scope, metric and reference targets

Struct recovery for the game layer. The matched C of the `Gap::Bec` game classes is typed through the generated
`include/dw4/reflected.h`; every edit is verified codegen-identical with `tools/verify.py` (the dispatcher with
`tools/dispatcher/full_verify.py`).

## Scope and metric

`tools/typed_scope.py` measures the game layer: functions named `Gap__Bec__*` or `be<Upper>*`, minus
registration boilerplate (`*_GetMetaObject`, `*_Register`, `*_InitFields`, `*_GetVTable`, `*_GetMetaEnum`), plus the
combat helpers in `config/typed-scope-extra.tsv`; the function list is `config/typed-scope.tsv`. Each member access falls
in one bucket: **typed** (member of a reflected class, ancestors merged), **local** (file-private struct), **synthetic**
(automatch `struct G`), **raw** (`*(T *)(base + N)`). Run `make typed-scope` (per class) or `make typed-check` (global
count gate). `make reflected-check` compiles the generated header with the host compiler and verifies every field offset.

`tools/typed_coverage.py` understands `Gap__Bec__X__vfunc_N` receivers, comma-separated parameters, inherited fields
(reflection lists only a class's own fields; the header merges ancestors) and `((Class *)p->_ref)->_field`; a count
that misses those forms understates the code.

The scope measures **9,356 / 10,570 typed (88.51 %) over 1,160 functions**; `config/typed-scope-baseline.json` and
`config/typed-scope.tsv` record that source set, and the 80 % scope target is satisfied. The figure includes the
316-file typing pass ([typed coverage](typed-coverage.md#the-316-file-typing-pass))
and the [title update recovery](title-menu-controller.md) (one function, 304 recovered accesses). The wider global gain
of the 316-file pass primarily concerns engine code and registration functions excluded here. Receiver hypotheses are explicitly unconfirmed. Source recovery
continues from the remaining byte-focused module work, not from extending the blanket typing pass.

## The `igObject` header

The classes share the two-word `igObject` header: a vtable word at +0 and a reference-count word at +4.
Reflection lists no field for `igObject`, so `config/SLUS-20836/authoritative-fields.tsv` records them with their
evidence (the identifier `_refCount` is a name hypothesis). `scripts/gen_type_headers.py` merges
that overlay, so every class struct in `reflected.h` starts `int _vtable; unsigned int _refCount;` instead of
`char _pad0[8]`, and `tools/typed_coverage.py` counts accesses through them. `scripts/retype_igobject_shims.py` replaces
the file-private header structs with the reflected one (62 files) and leaves 4 C++ files as they were, because their
destructor classes make the rewrite change codegen. The retail code reads the count as a signed int in some functions and
as unsigned (`lwu` where the value is widened to 64 bits) in others, so the field is unsigned and signed sites read it
through `(int)`.

`igObject_InitHeader` (`0x2fef20`, `src/engine/core/igObject_tail2.inc`) writes the vtable reference at +0, then sets the
23-bit count to 1, clears the flag bit and zeroes the top byte (retail result: vtable `0x52f0f0`, header word 1).

## Rules the edits follow

* References stay four-byte `int` and are only named.
* No new `sizeof(void *) == 4` assumptions; constructs that exist only to steer the matching compiler carry a
  `/* matching construct: <why> */` comment so they can be told from game logic.
* Reflected classes come only from `#include "dw4/reflected.h"`; helper structs for non-reflected records are named for
  what they are.
* A pointer-typed local declared first is the safe spelling for a followed reference: casting an `int` field at every use
  can change register allocation.
* A class identity that rests on an offset fingerprint or a documented convention is a **hypothesis**, not a recovered fact.

## Reference-field targets

Each row says which class a reference field (`igObjectRefMetaField`) points at.
Evidence is the class's `_InitFields` metaobject getter (handle resolved through `data/reflection.json`) unless noted.

| class.field | target class | evidence |
| --- | --- | --- |
| `ParticleTimer._attributes` | `igObjectList` | by shape (count +8, data +16) |
| `be._stringRefList` | `igStringRefList` | DAT_0058a1d8 is the Game this (docs/engine/game-state.md); Gap__Bec__be__vfunc_26 clears it as a string list |
| `beAction2._system` | `beSystem` | slot-96 draw on field +48 = beSystem._random (beNDMWGameRam._system -> beSystem); applied in beAction2WAITCHEC |
| `beAction2Data._comList` | `igObjectList` | shaped list: docs/engine/action2-jointset.md |
| `beAction2InfoRam._parentInfo` | `beAction2Info` | reflection field pairing (ram/info), _switch read at +28 |
| `beAction2InfoRam._work` | `beAction2InfoWork` | docs/engine/action2-jointset.md work offsets match _motionSt0/_jointSt0/_fadeSt0/_waitSt0/_flashSt0/_isFreeze |
| `beAction2InfoWork._comData` | `beAction2Data` | docs/engine/action2-timing.md ("+0xc beAction2Data") and action2-jointset.md |
| `beActionStarterInfo._modelList` | `igDataList` | of model records (+8 name, +12 data list; record class unidentified) |
| `beActionStarterInfoRam._parentInfo` | `beActionStarterInfo` (hypothesis) | (hypothesis): BaseInfoRam._parentInfo; accessed +8 _name and +28 _modelList match beActionStarterInfo |
| `beBaseInfoManager._insight` | `igInsightCore` | docs/engine/system-clock.md (+20 _window, +80 _worldTime) |
| `beBaseInfoManager._system` | `beSystem` | ; _messenger -> beMessenger; _infoList -> beBaseInfoList (FUN_0036aaf0): beBaseInfoManager_InitFields metaObjects |
| `beBaseInfoRam._dataList` | `beBaseInfoDataList` | beBaseInfoRam_InitFields field 8 getter FUN_0036aec0 reads class handle 0x589e00; beBaseInfoDataList_Create allocates that class |
| `beBaseInfoRam._parentInfo` | `beBaseInfo` | beBaseInfoRam_InitFields field 1 getter FUN_0036ac80 reads handle 0x589de8 |
| `beBaseInfoRam._parentManager` | `beBaseInfoManager` | InitFields field 2 getter FUN_0036a8d0 reads handle 0x589db8 |
| `beCri._hdSEs` | `igObjectList` (hypothesis) | (retained list: ObjectList_AppendRetained/RemoveFirstRetained); elements beCriHandle (hypothesis) |
| `beCriHandle._audio` | `beCriAudio` (hypothesis) | (hypothesis, name only; not applied) |
| `beDBManager._messenger` | `beMessenger` | same call (Gap__Bec__beDBManager__vfunc_29) |
| `beDataObjBoolList._data` | `igBoolList` | field metaobject getter FUN_002cb110 loads handle 0x5868a8 |
| `beDataObjIntList._data` | `igIntList` | beDataObjIntList_InitFields uses igIntList_GetOrCreateMetaObject |
| `beDataObjObjectList._data` | `igObjectList` | beDataObjObjectList_InitFields uses igObjectList_GetOrCreateMetaObject |
| `beDataObjStringList._data` | `igStringRefList` | field metaobject getter FUN_002b9120 loads handle 0x5858d8 |
| `beDemoManager._lua` | `beLua` | handle 0x589208 in beDemoManager vfunc_23 |
| `beDemoManager._messenger` | `beMessenger` | handle 0x588f38 in beDemoManager vfunc_23 |
| `beFileListInfoManager._messenger` | `beMessenger` | class handle DAT_00588f38 (data/reflection.json) passed to FUN_00236f80 (vfunc_23) |
| `beFileListInfoManager._sceneInfoManager` | `igViewerSceneInfoManager` | class handle DAT_0058c790 |
| `beFileListInfoManager._system` | `beSystem` | class handle DAT_00587d08 |
| `beFont._root` | `igAttrSet` | (FUN_001a5d70); _fonts -> beFontImageList (FUN_00361750); _gaPairList -> beFontGeomAttrPairList (FUN_00362360); _lineFeedList -> igIntList; _alignList -> igFloa |
| `beFontImage._charMetricsList` | `igCharMetricsList` (hypothesis) | (name match, hypothesis; applied) |
| `beGenerater._luaManager` | `beLua` | created with class handle DAT_00589208 = beLua (data/reflection.json) |
| `beGenerater._messenger` | `beMessenger` | first argument of beMessenger_RegisterReceiver |
| `beHitLandDeliv._messenger` | `beMessenger` | first argument of beMessenger_RegisterReceiverFromInfo (a beMessenger_* method) |
| `beHitLandModelOrder._hitdataList` | `beHitLandResultDataList` | InitFields field 8 getter FUN_0035e270 reads handle 0x5893e0 |
| `beHitLandModelOrder._rayList` | `igRayList` | beHitLandModelOrder_InitFields field 6 metaobject getter FUN_001880b0 reads class handle 0x560fb8 (igRayList) |
| `beLua._infoList` | `igInfoList` | igInfoManager list by name; beLua._luaState -> beLuaState: field/class name pairing, refcounted object released in vfunc_26 |
| `beLua._system` | `beSystem` | set from FUN_00236f80(_insight, class handle 0x587d08); handle 0x587d08 is beSystem in data/reflection.json |
| `beMatCtrl._wkMatOnList` | `igDataList` (hypothesis) | of unsigned words (indexed by _wkChkMat; hypothesis for exact class) |
| `beMessenger._argData` | `beMessengerArgData` | _objectList(+40)/_longList(+28) match the ClearObjects/AppendLong names; beMessengerArgData_Clear callee |
| `beMessenger._workStack` | `beMessengerWorkList` | (elements beMessengerWork): field offsets in beMessenger_DispatchSelected |
| `beMessengerArgData._boolList` | `igBoolList` | (FUN_002cb110); _intList -> igIntList; _floatList -> igFloatList (FUN_002c9780); _longList -> igLongList (FUN_002ca680); _vec3fList -> igVec3fList (FUN_0018a0a0 |
| `beMessengerArgData._floatList` | `igFloatList` | field name plus element size 4 |
| `beMessengerArgData._intList` | `igIntList` | field name plus element size 4 |
| `beMessengerArgData._longList` | `igLongList` | field name plus element size 8 |
| `beMessengerArgData._matrix44fList` | `igMatrix44fList` | field name plus element size 64 |
| `beMessengerArgData._objectList` | `igObjectList` | elements released through igObject_Destroy in beMessengerArgData_Clear |
| `beMessengerArgData._stringList` | `igStringList` | (no reflected struct; typed as igDataList): field name, interned strings released per element |
| `beMessengerArgData._vec3fList` | `igVec3fList` | field name plus element size 12 |
| `beMessengerDelay._argData` | `beMessengerArgData` | argument of beMessengerArgData_Clear |
| `beMessengerWork._findRamNoList` | `igIntList` | ; beMessengerWork._findRamList -> igObjectList of beBaseInfoRam: beMessenger_DispatchSelected |
| `beMovie._insight` | `object` | whose class handles are looked up by FUN_00236f80 (insight getter): DAT_00588518 bePadManager, DAT_00589208 beLua |
| `beMovie._messenger` | `beMessenger` | beMessenger_RegisterReceiver callee |
| `beNDMWGameRam._commonDataList` | `beDataObjList` | (FUN_00364090); _playerDataListList -> beDataObjListList (FUN_00363ec0); _dBShinka.._dBEneatk -> beDataBase (FUN_003658e0) |
| `beNDMWGameRam._dBShinka` | `beDataBase` | first argument of beDataBase_GetRecordString in beNDMWGameRam_SelectSpecies, object obtained via beMessenger_GetObject |
| `beNDMWGameRam._infoList` | `beBaseInfoList` | beBaseInfoManager._infoList, list class by name; used with ObjectList_AppendRetained |
| `beNDMWGameRam._messenger` | `beMessenger` | passed as the first argument of beMessenger_RegisterReceiverFromInfo (config/SLUS-20836/names) |
| `beNDMWGameRam._playerDataListList` | `igIntList` | of player data handles: indexed by player in beNDMWGameRam_SelectSpecies and beNDMWGameRam_StoreSpecies (SaveBase.c) |
| `beNDMWGameRam._system` | `beSystem` | beBaseInfoManager_InitFields sets the _system field metaobject via FUN_00342ce0 which loads handle 0x587d08 (beSystem) |
| `beNDMWGameRamInfo._ramList` | `beBaseInfoRamList` | name pairing; receives the new ram |
| `beNDMWGameRamInfoRam._parentInfo` | `beNDMWGameRamInfo` | ; _parentManager -> beNDMWGameRam: stored from the created info and arg0 in beNDMWGameRam_CreateInfo |
| `beNDMWLoadCtrl2CommonIntf._flagWork` | `beNDMWLoadSavePlWorkList` | InitFields field 6 getter FUN_003c5520 reads handle 0x58bc10 (beNDMWLoadSavePlWorkList) |
| `beNDMWLoadCtrl2CommonIntf._gameUseData` | `beNDMWDegiDataList` | beNDMWLoadCtrl2CommonIntf_InitFields field 5 metaobject getter FUN_003c66a0 reads class handle 0x58bd20 (beNDMWDegiDataList) |
| `beNDMWLoadCtrl2CommonIntf._inforam` | `beBaseInfoRam` | InitFields field 2 getter FUN_0036a230 reads handle 0x589d28 |
| `beNDMWLoadCtrl2CommonIntf._insight` | `igInsightCore` | InitFields field 3 getter FUN_00232840 reads handle 0x56db60 |
| `beNDMWLoadCtrl2CommonIntf._messenger` | `beMessenger` | InitFields field 0 getter FUN_00357910 reads handle 0x588f38 |
| `beNDMWLoadCtrl2CommonIntf._slotSaveData` | `beNDMWLoadSlotPlayerList` | InitFields field 4 getter FUN_003c61d0 reads handle 0x58bcf8 |
| `beNDMWLoadCtrl2CommonIntf._system` | `beSystem` | InitFields field 1 getter FUN_00342ce0 reads handle 0x587d08 |
| `beNDMWLoadIntf2._messenger` | `beMessenger` | first argument of beMessenger_RegisterReceiver* |
| `beNDMWLoadIntf2._padManager` | `bePadManager` | set from FUN_00236f80(insight, class handle 0x588518 = bePadManager) |
| `beNDMWLoadSlotPlayer._accessPlList` | `igIntList` | InitFields field 2 igIntList_GetOrCreateMetaObject |
| `beNDMWLoadSlotPlayer._saveDataList` | `beNDMWDegiDataList` | beNDMWLoadSlotPlayer_InitFields field 1 metaobject getter FUN_003c66a0 reads class handle 0x58bd20 (beNDMWDegiDataList) |
| `beNDMWLogo._padManager` | `bePadManager` | set from lookup with handle 0x588518 |
| `beNDMWLogo._system_` | `beSystem` | set from lookup with handle 0x587d08 = beSystem (data/reflection.json) |
| `beNDMWMdlItem._lockRamList` | `igDataList` (hypothesis) | derived list (element-release loop; hypothesis) |
| `beNDMWMdlItem._messenger` | `beMessenger` | beMessenger_* callees take it; class handle DAT_00588f38 is beMessenger |
| `beNDMWMdlMapBase._messenger` | `beMessenger` | beMessenger_SendGroup/GetMatrix callees |
| `beNDMWMdlPEBaseInfoWork._dispPosNoList` | `igIntList` | InitFields field 2 igIntList_GetOrCreateMetaObject |
| `beNDMWMdlPEBaseInfoWork._dispRamNoList` | `igIntList` | beNDMWMdlPEBaseInfoWork_InitFields field 1 metaobject igIntList_GetOrCreateMetaObject |
| `beNDMWMdlPEBaseInfoWork._downDataList` | `igIntList` | InitFields field 7 igIntList_GetOrCreateMetaObject |
| `beNDMWMdlPEBaseInfoWork._isFirstList` | `igBoolList` | InitFields field 4 metaobject getter FUN_002cb110 reads class handle 0x5868a8 (igBoolList) |
| `beNDMWMdlPEBaseInfoWork._messenger` | `beMessenger` | InitFields field 9 metaobject getter FUN_00357910 reads class handle 0x588f38 (beMessenger) |
| `beNDMWMdlPEBaseInfoWork._timerList` | `igIntList` | InitFields field 3 igIntList_GetOrCreateMetaObject |
| `beNDMWMdlPEBaseInfoWork._upDataList` | `igIntList` | InitFields field 8 igIntList_GetOrCreateMetaObject |
| `beNDMWMdlPlayer._gameRam` | `beNDMWGameRam` | class handle DAT_0058c0a0 (vfunc_23) |
| `beNDMWMdlPlayer._messenger` | `beMessenger` | beMessenger_* callees (vfunc_41/43) |
| `beNDMWMdlPlayer._padManager` | `bePadManager` | class handle DAT_00588518 (vfunc_23) |
| `beNDMWMdlPlayer._viewerSIManager` | `igViewerSceneInfoManager` | class handle DAT_0058c790 (vfunc_23) |
| `beNDMWMdlPlayer2._padManager` | `bePadManager` | argument of bePadManager_GetPadForPlayer; same handle 0x588518 in the matched vfunc_23 |
| `beNDMWPanelObjectWaza._messenger` | `beMessenger` | arguments of beMessenger_* callees in Gap__Bec__beNDMWPanelObjectWaza__vfunc_22 |
| `beNDMWSaveCtrl._messenger` | `beMessenger` | same call (vfunc_29) |
| `beNDMWSaveCtrl._padManager` | `bePadManager` | handle 0x588518 in vfunc_32 |
| `beNDMWSaveIntf._padManager` | `bePadManager` | FUN_00236f80(_insight, class handle 0x588518); the handle is bePadManager |
| `beNDMWShopCtrlXdataChip._itemBaseList` | `beNDMWItemBaseList` | (FUN_003c9130) |
| `beNDMWStageCtl._messenger` | `beMessenger` | beMessenger_RegisterReceiver callee |
| `beNDMWStatus._windowPro` | `beNDMWWindow` | (FUN_003b1dd0) |
| `beNDMWStatusCtrlBaseEquip._apuPocket` | `beNDMWItemBaseList` | InitFields metaobject getter FUN_003c9130 (handle 0x58bf88) |
| `beNDMWStatusCtrlBaseEquip._deviceFolder` | `beNDMWItemBaseList` | InitFields metaobject getter FUN_003c9130 (handle 0x58bf88) |
| `beNDMWStatusCtrlBaseEquip._mainSlot` | `beNDMWItemBaseList` | InitFields metaobject getter FUN_003c9130 (handle 0x58bf88) |
| `beNDMWStatusCtrlBaseEquip._playerList` | `beDataObjList` | InitFields field 3 getter FUN_00364090 reads handle 0x589840 |
| `beNDMWStatusCtrlBaseEquip._powerSocket` | `beNDMWItemBaseList` | InitFields field 4 getter FUN_003c9130 reads handle 0x58bf88 |
| `beNDMWStatusCtrlBaseEquip._subSlot` | `beNDMWItemBaseList` | beNDMWStatusCtrlBaseEquip_InitFields field 6 metaobject getter FUN_003c9130 reads class handle 0x58bf88 (beNDMWItemBaseList) |
| `beNDMWStatusCtrlBaseEquip._wpuPocket` | `beNDMWItemBaseList` | InitFields metaobject getter FUN_003c9130 (handle 0x58bf88) |
| `beNDMWStatusCtrlD0._decideList` | `igBoolList` | InitFields field 7 getter FUN_002cb110 (handle 0x5868a8) |
| `beNDMWStatusCtrlD0._kindList` | `igIntList` | beNDMWStatusCtrlD0_InitFields _metaObject = igIntList_GetOrCreateMetaObject |
| `beNDMWStatusCtrlFlag._impItems` | `igIntList` | beNDMWStatusCtrlFlag_InitFields _metaObject = igIntList_GetOrCreateMetaObject |
| `beNDMWStatusMainSlot._messenger` | `beMessenger` | beMessenger_* callees in vfunc_26 |
| `beNDMWStatusMainSlot._subWindow` | `beNDMWWindowList` | (child windows, retained list): docs/engine/window-tree-and-shop-root.md; used with ObjectList_AppendRetained of a beNDMWStatusCtrlD0 |
| `beNDMWTitle2._messenger` | `beMessenger` | passed to beMessenger_ResolveEnumValue |
| `beNDMWWindow._insight` | `igInsightCore` | beNDMWWindow_InitFields field 0 getter FUN_00232840 (handle 0x56db60) |
| `beNDMWWindow._messenger` | `beMessenger` | beNDMWWindow_InitFields field 1 getter FUN_00357910 (handle 0x588f38) |
| `beNDMWWindow._modelCloseInfoNameList` | `igStringRefList` | InitFields field 15 getter FUN_002b9120 |
| `beNDMWWindow._modelCloseRamNoList` | `igIntList` | InitFields field 16 igIntList_GetOrCreateMetaObject |
| `beNDMWWindow._modelCloseSeqNameList` | `igStringRefList` | InitFields field 17 getter FUN_002b9120 |
| `beNDMWWindow._mother` | `beNDMWWindow` | metaObject FUN_003b1dd0 (handle beNDMWWindow) |
| `beNDMWWindow._padManager` | `bePadManager` | handle 0x588518 passed to FUN_00236f80 in beNDMWWindow_BindContext |
| `beNDMWWindow._subWindow` | `beNDMWWindowList` | beNDMWWindow_InitFields field 11 metaObject FUN_003b1be0 returns handle 0x58a9a8 (beNDMWWindowList) |
| `beNDMWWindow._textCloseNameList` | `igStringRefList` | beNDMWWindow_InitFields field 14 getter FUN_002b9120 |
| `beNDMWWindow._textCloseTypeList` | `igStringRefList` | beNDMWWindow_InitFields field 13 metaobject getter FUN_002b9120 reads class handle 0x5858d8 (igStringRefList) |
| `beNDMWWindowSelect._decideList` | `igBoolList` | beNDMWWindowSelect_InitFields field 5 getter FUN_002cb110 (handle 0x5868a8) |
| `beNDMWWindowSelect._messenger` | `beMessenger` | passed as the first argument of every beMessenger_* call (recovered signatures) |
| `beNDMWWindowSelect._mother` | `beNDMWWindow` (hypothesis) | (hypothesis): docs/engine/shop-selectors.md 'Mother56 receives the selected return value in its word48', beNDMWWindow._retCode is +48 |
| `beNumVerData._verDataList` | `beNumVerDataList` | name pairing, class derives igObjectList, destructor releases the elements |
| `beNumberCtrl._messenger` | `beMessenger` | passed to beMessenger_AppendInt/GetInt/GetIntCount/ResolveEnumValue |
| `beNumberCtrlInfoRam._work` | `beNumberCtrlInfoWork` | FUN_0034d2b0 allocates from handle 0x588630 (beNumberCtrlInfoWork); FUN_0034d2f0, a metaobject getter reading 0x588630, is the metaobject of field 5 in beNumber |
| `bePadManager._padList` | `bePadDataList` | (rows bePadData): docs/engine/selectctrl.md pad record array |
| `beParticleCtrl2._infoList` | `igObjectList` (hypothesis) | of beParticleCtrl2Info; beParticleCtrl2Info._ramList -> igObjectList of beParticleCtrl2InfoRam; beParticleCtrl2InfoRam._particleTimer -> ParticleTimer; hypothes |
| `beParticleCtrl2._messenger` | `beMessenger` | beMessenger_RegisterReceiver callee |
| `bePoint01._messenger` | `beMessenger` | beMessenger_ResolveEnumValue/GetInt/AppendInt callees |
| `beSeCtl._sndMng` | `beSound` | (FUN_003442f0) |
| `beSeInfo._dataList` | `beBaseInfoDataList` | (rows beSeInfoData): docs/engine/sound-format.md; list layout identical to beSeDataList |
| `beSeInfoData._actionList` | `beSeDataList` | (rows beSeData): docs/engine/sound-format.md 'walks every matching beSeData action' |
| `beSelectCtrl._messenger` | `beMessenger` | beMessenger_* callees; docs/engine/selectctrl.md (RegisterReceiverFromInfo with _messenger) |
| `beSelectCtrlInfoRamData._work` | `beSelectCtrlInfoWork` | docs/engine/selectctrl.md state-object table |
| `beShadow01._svInfoList` | `igDataList` (hypothesis) | derived list (List_Reserve; hypothesis for exact class) |
| `beShadow01Info._projShadowShader` | `igProjectiveShadowShader` | eight offsets/widths match uniquely in beShadow01 vfunc_25 |
| `beSound._cri` | `beCri` | beSound_InitFields field 0 metaobject getter FUN_003678a0 reads handle 0x589ad8 (beCri) |
| `beSound._playSEs` | `bePlaySEList` | beSound_InitFields field 2 getter FUN_00344630 reads handle 0x587ec8 |
| `beStaticInfoCtl._messenger` | `beMessenger` | set from FUN_00236f80(insight, class handle 0x588f38 = beMessenger) |
| `beSvDeliver._formatList` | `igIntList` | beSvDeliver_InitFields igIntList_GetOrCreateMetaObject (fields 12-15) |
| `beSvDeliver._freeFileList` | `igIntList` | beSvDeliver_InitFields igIntList_GetOrCreateMetaObject (fields 12-15) |
| `beSvDeliver._freeSizeList` | `igIntList` | beSvDeliver_InitFields igIntList_GetOrCreateMetaObject (fields 12-15) |
| `beSvDeliver._gameData` | `beSaveDataDeliver` | beSvDeliver_InitFields field 16 getter FUN_0034aeb0 reads handle 0x5883b0 |
| `beSvDeliver._platformData` | `beSvPlatBaseData` | beSvDeliver_InitFields field 17 metaobject getter FUN_0034a210 reads class handle 0x588308 (beSvPlatBaseData) |
| `beSvDeliver._totalSizeList` | `igIntList` | beSvDeliver_InitFields igIntList_GetOrCreateMetaObject (fields 12-15) |
| `beSvFileMakeApi._earlyGamedata` | `beSvPlatBaseData` | InitFields field 0 getter FUN_0034a210 reads handle 0x588308 |
| `beSvFileMakeApi._saveWork` | `beSaveMemoryObj` | beSvFileMakeApi_InitFields field 1 metaobject getter FUN_0034ac90 reads class handle 0x5883a0 (beSaveMemoryObj) |
| `beSvReadMediaApi._gameData` | `beSaveDataDeliver` | beSvReadMediaApi_InitFields field 1 getter FUN_0034aeb0 reads class handle 0x5883b0 (beSaveDataDeliver) |
| `beSvReadMediaApi._loadWorkList` | `igObjectList` | beSvReadMediaApi_InitFields field 4 igObjectList_GetOrCreateMetaObject |
| `beSvReadMediaApi._outputGamedata` | `beSvPlatBaseData` | field 0 getter FUN_0034a210 reads 0x588308 |
| `beTextureCtrl._work` | `beTextureCtrlWork` (hypothesis) | (hypothesis: offsets +8/+12 only; not applied) |
| `beTimer._luaManager` | `beLua` | handle 0x589208 |
| `beTimer._padManager` | `bePadManager` | handle 0x588518 |
| `beTimer._system` | `beSystem` | handle 0x587d08 passed to FUN_00236f80 in beTimer vfunc_23 |
| `beWeapon._messenger` | `beMessenger` | beMessenger_RegisterReceiverFromInfo argument in Gap__Bec__beWeapon__vfunc_29 |
| `igAttrSet._attributes` | `igAttrList` | igAttrSet_InitFields field 0 metaobject getter FUN_0013af00 reads class handle 0x55f460 (igAttrList) |
| `igBitmapFont._charMetricsList` | `igCharMetricsList` | (FUN_00452790); _textureBind -> igTextureBindAttr (FUN_00132850) |
| `igInfoManager._insight` | `igInsightCore` | metaObject FUN_00232840 |

## Notes not resolved to a single field

* DEVICEFOLDER igObjectList elements -> beNDMWItemBase (subclasses beNDMWItemWeapon/BlueArmor/YellowArmor/AbilityChip): creators beNDMWItemWeapon_Create, beNDMWItemBlueArmor_Create, beNDMWItemYellowArmor_Create and beNDMWItemAbilityChip_Create and initialisers beNDMWItemWeapon_Set, beNDMWItemBlueArmor_Set, beNDMWItemYellowArmor_Set and beNDMWItemAbilityChip_Set
* DISKFOLDER igObjectList elements -> beNDMWItemDisk: beNDMWGameRam_ResetPlayer creates and initialises them with beNDMWItemDisk_Set(beNDMWItemDisk *)
* beActionStarter._messenger, beLightCtrl._messenger, beNDMWMdlMapBase._messenger, beSeCtl._messenger -> beMessenger: first argument of beMessenger_RegisterReceiver/FromInfo in their vfunc_29/37
* beBaseInfoRam._dataList (context +40) -> container of RamData records searched by name (e.g. beSelectCtrlInfoRamData): hypothesis, from selectctrl.md and the shared igProperty_FindByName(DAT_00585be0) key
* window object built by FUN_003baf10 in beNDMWStatusSubSlot vfunc_29 is a beNDMWWindow subclass: callees beNDMWWindow_BindContext/RunMessageScript; fields _textCloseTypeList/_textCloseNameList at +60/+64
* beNDMWStatusPowerSocket._messenger / beActionStarter._messenger / beCameraCtrl._messenger / beMeterCtrl._messenger / beSwitchCtrl._messenger / beNDMWMdlPlayer2._messenger / beNumberCtrl._messenger -> beMessenger: passed 
* beNDMWWindow._textCloseTypeList/_textCloseNameList/_modelCloseInfoNameList/_modelCloseSeqNameList -> igStringRefList: metaObject FUN_002b9120 (handle 0x5858d8)
* beMatCtrl._wkMatOnList/_wkMatOldOnList -> igIntList; _lua (+36) -> beLua (FUN_0035b770): beMatCtrl_InitFields
* beNDMWStatusPowerSocket._mother, beNDMWStatusMainSlot._mother, beNDMWWindow._mother -> beNDMWWindow: docs/engine/window-tree-and-shop-root.md (retained parent window)
* beNDMWWindow._modelCloseInfoNameList / _modelCloseSeqNameList -> igStringList-style string lists; _modelCloseRamNoList -> int list (igDataList layout used): PresentModel appends a string/int/string; element class not cla
* ParticleArray._pointSpriteInterface / _internalVertexArray: target classes unidentified (not claimed)
* beNDMWMdlPlayer2/beBaseInfoRam._dataList -> unidentified property-list object (igProperty_FindByName target): not claimed
* beNDMWMdlItem property folder list (Fold.f12) -> igObjectList: ObjectList_AppendRetained callee, docs/engine/object-lists.md
* beCri._hdBGM, beCri._hdENV -> beCriHandle (hypothesis: appended to the same handle list)
* beMovie list items (arg1 info list) -> beMovieInfoData: class-handle cast DAT_00588760
* beNDMWPanelWazaInfoWork._textSetList, ._textColorList -> igDataList-derived lists (List_Reserve/List_Resize/StringList_Resize callees); subclasses unidentified
* beNDMWAfsSetup._infoList, beCri._infoList, beStaticInfoCtl._staticInfoList, beMatCtrl._wkMatOnList -> igDataList-layout lists (layout only; subclasses unidentified)
* beMessengerArgData._boolList igBoolList 0x5868a8 -> : beMessengerArgData_InitFields sets the field's _metaObject from the getter reading class handle  (reflection class )
* beMessengerArgData._intList igIntList 0x586880 -> : beMessengerArgData_InitFields sets the field's _metaObject from the getter reading class handle  (reflection class )
* beMessengerArgData._floatList igFloatList 0x586808 -> : beMessengerArgData_InitFields sets the field's _metaObject from the getter reading class handle  (reflection class )
* beMessengerArgData._longList igLongList 0x586868 -> : beMessengerArgData_InitFields sets the field's _metaObject from the getter reading class handle  (reflection class )
* beMessengerArgData._vec3fList igVec3fList 0x5610b8 -> : beMessengerArgData_InitFields sets the field's _metaObject from the getter reading class handle  (reflection class )
* beMessengerArgData._matrix44fList igMatrix44fList 0x561078 -> : beMessengerArgData_InitFields sets the field's _metaObject from the getter reading class handle  (reflection class )
* beMessengerArgData._objectList igObjectList 0x585b60 -> : beMessengerArgData_InitFields sets the field's _metaObject from the getter reading class handle  (reflection class )
* beMessengerArgData._stringList igStringRefList 0x5858d8 -> : beMessengerArgData_InitFields sets the field's _metaObject from the getter reading class handle  (reflection class )
* beMessenger._groupList/_delayStack/_pushPopStack -> igObjectList subclasses (count/data shape in beMessenger_ResetMemory); specific list classes unrecorded
* beTargetObj._playerPosList/_enemyPosList -> igVec3fList, _playerRamNoList -> igIntList: List_Reserve element sizes 12/4/12; hypothesis
* beNDMWPanelObjectStat._listFolder/_listColor -> igDataList-shaped lists; class unrecorded
* beBkColor/beMessenger/etc ._messenger -> beMessenger: the value is passed as first argument of every beMessenger_* function
* beHitLandModel._order/_hitTraversal/_probe -> released and cleared in vfunc_32; _hitTraversal presumably beHitLandModelTraversal (class not proven, no entry)

## Header coverage

`scripts/check_scope_headers.py` (run by `make reflected-check`) verifies that every class named in `config/typed-scope.tsv` has its authoritative struct in `include/dw4/reflected.h`: **460 of 460** in-scope classes (`FUN` and `bePlayer` are not classes).

The generator emits a struct for each class in `config/typed-scope.tsv` even when it has no field of its own (`beCountry`,
`beFile`, `beUnicode` hold the `igObject` header). The two remaining name groups in the scope list are not classes: `FUN`
(unnamed combat helpers) and `bePlayer` (the helper `bePlayer_GetStruct`, no reflected class).

## Open questions

All of these are unproven.

* **Property record classes.** The class of each property record is taken from the template type of its property key. All 146
  sites in `beNDMWGameRam_OnMessage` resolve to a single key and all int-typed keys share one class, but a variable aliasing two
  keys would be mistyped.
* **Handler `arg1`.** The `arg1` of handler vfuncs is `beBaseInfoRam` or a subclass. The best evidence is `beSelectCtrl::vfunc_33`
  (eight offsets and widths: 8, 12, 20, 24, 28, 32, 36, 40) and `beNDMWTitle2::vfunc_34` (+24..+36 and +40), plus the shared
  `igProperty_FindByName(arg1+40, DAT_00585be0)` lookup, the `vfunc_31` `(this, ram)` convention and
  `beMessenger_RegisterReceiverFromInfo` (+8 `_ramNo`, +12 `_parentInfo`, parent +8 `_name`). Many other sites rest on one or two
  offsets and the shared signature, and concrete model-info subclasses have no reflected struct. Unrelated classes share these
  offsets and RTTI does not confirm it. Not applied in `beNDMWPanelWaza::vfunc_29` or `beNDMWMdlPlayer2::vfunc_36` (two offsets).
* **`beNDMWMdlPlayer2::vfunc_38` work record.** Its byte +236 and int +240 fit `beNDMWMdlPlayer2InfoWork._isPowerOn`/`_timerCount`
  on two offsets only. Not applied.
* **List element classes**, from the list name and offsets: `beActionStarter` elements are `beActionStarterData2` (fingerprint);
  `beTimerDataList` elements are `beTimerData` (+8 `_startTime`, +16 `_resetCondition`, +20 `_callLuaFile`, +24 `_downTimer`);
  `beNDMWItemBaseList` elements are `beNDMWItemBase` (+16 `_isEquip`).
* **`beAction2._switch` target.** Not identified. `beAction2FADESET_Start` reads it as a local view, `Action2SwitchBits`, with a
  bit-word list at +32.
* **Save API `arg1`.** It is `beSvDeliver`, by the fingerprint +16 `_targetConnect`, +24 `_result`, +44 `_isEndOperat` (one-byte
  bool), +64 `_platformData`, and the API semantics. Among game classes the fingerprint is unique; `beSvFileFindApi` `vfunc_21`
  stores +64 into `DAT_0058a600`, which `vfunc_22` uses as `beSvPlatBaseData`. Applied in `beSvFileFindApi` `vfunc_21`/`23`,
  `beSvFileMakeApi` `vfunc_23` and `beSvUseCheckApi` `vfunc_21`/`23`. Not applied in `beSvReadMediaApi`, `beSvEndApi`,
  `beSvStartApi`, `beSvWriteMediaApi` and `beSvFormatApi` `vfunc_23` or `beSvGetFreeSizeApi` and `beSvFormatApi` `vfunc_21`, which
  show too few offsets or also fit `igAdxFile` and `igMediaFile`.
