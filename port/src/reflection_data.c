/* Generated file; do not hand-edit. The port's reflection schema. Field `tid` is the igBinary
 * descriptor type id (0xff = a type not named); `offset` is the absolute byte offset the engine's
 * field initialiser registers. */
#include "dw4/object.h"

static const dw4_metafield mo_f0[] = {
    { "_xImageCount", 16, 0x5c },
    { "_yImageCount", 16, 0x60 },
    { "_loopTime", 2, 0x64 },
    { "_continuousTime", 2, 0x65 },
    { "_startOffset", 16, 0x68 },
    { "_hasTextureCoordinates", 2, 0x6c },
    { "_vertexArray1", 0, 0x70 },
    { "_vertexArray2", 0, 0x74 },
    { "_whichVertexArray", 2, 0x78 },
    { "_setConstant1", 2, 0x79 },
    { "_setConstant2", 2, 0x7a },
};
static const dw4_metafield mo_f1[] = {
    { "_points", 255, 0x40 },
    { "_numControls", 255, 0x340 },
    { "_lifetime", 16, 0x3c0 },
    { "_count", 1, 0x3c4 },
    { "_texture", 0, 0x3c8 },
    { "_alphaType", 6, 0x3cc },
    { "_alphaFunction", 6, 0x3d0 },
    { "_sizeLock", 2, 0x3d4 },
    { "_sizeWorld", 2, 0x3d5 },
    { "_timeType", 6, 0x3d8 },
    { "_particleScene", 2, 0x3dc },
    { "_shape", 6, 0x3e0 },
    { "_maximize", 2, 0x3e4 },
    { "_xImageCount", 1, 0x3e8 },
    { "_yImageCount", 1, 0x3ec },
    { "_resizeCurves", 2, 0x3f0 },
    { "_startOffset", 16, 0x3f4 },
    { "_geometry", 0, 0x3f8 },
};
static const dw4_metafield mo_f2[] = {
    { "_timeRunning", 2, 0x2c },
    { "_timeBias", 12, 0x30 },
    { "_time", 12, 0x38 },
};
static const dw4_metafield mo_f3[] = {
    { "_data", 7, 0x8 },
    { "_count", 1, 0xc },
};
static const dw4_metafield mo_f5[] = {
    { "_stringRefList", 0, 0x10 },
};
static const dw4_metafield mo_f7[] = {
    { "_comList", 0, 0xc },
};
static const dw4_metafield mo_f9[] = {
    { "_fadeTime", 16, 0xc },
    { "_fadeValue", 16, 0x10 },
};
static const dw4_metafield mo_f11[] = {
    { "_switch", 0, 0x1c },
    { "_animationDatabase", 0, 0x20 },
    { "_dataList", 0, 0x24 },
};
static const dw4_metafield mo_f13[] = {
    { "_node", 0, 0x2c },
    { "_appearanceList", 0, 0x30 },
    { "_actorList", 0, 0x34 },
    { "_work", 0, 0x38 },
};
static const dw4_metafield mo_f14[] = {
    { "_comData", 0, 0x8 },
    { "_comIndex", 1, 0xc },
    { "_isNoHokan", 2, 0x10 },
    { "_isMotion", 2, 0x11 },
    { "_motionSt0", 1, 0x14 },
    { "_motionIsEnd", 2, 0x18 },
    { "_jointSt0", 1, 0x1c },
    { "_jointStartTimeL", 12, 0x20 },
    { "_jointEndTimeL", 12, 0x28 },
    { "_jointIsEnd", 2, 0x30 },
    { "_fadeSt0", 1, 0x34 },
    { "_fadeLimitValue", 16, 0x38 },
    { "_fadeAddValue", 16, 0x3c },
    { "_fadeValue", 16, 0x40 },
    { "_waitSt0", 1, 0x44 },
    { "_flashSt0", 1, 0x48 },
    { "_isFreeze", 2, 0x4c },
    { "_colorAttr", 0, 0x50 },
    { "_blendStateAttr", 0, 0x54 },
    { "_textureStateAttr", 0, 0x58 },
    { "_lightingStateAttr", 0, 0x5c },
};
static const dw4_metafield mo_f15[] = {
    { "_startTime", 16, 0xc },
    { "_endTime", 16, 0x10 },
    { "_loopMode", 4, 0x14 },
};
static const dw4_metafield mo_f16[] = {
    { "_hokanMode", 4, 0xc },
    { "_hokanTime", 16, 0x10 },
    { "_loopMode", 4, 0x14 },
};
static const dw4_metafield mo_f17[] = {
    { "_waitTime", 16, 0xc },
};
static const dw4_metafield mo_f19[] = {
    { "_message", 4, 0xc },
    { "_delay", 1, 0x10 },
    { "_offset", 36, 0x14 },
    { "_isSeqDead", 2, 0x20 },
    { "_isPositionLock", 2, 0x21 },
};
static const dw4_metafield mo_f20[] = {
    { "_rotation", 36, 0x24 },
};
static const dw4_metafield mo_f22[] = {
    { "_modelList", 0, 0x1c },
};
static const dw4_metafield mo_f24[] = {
    { "_dataList", 0, 0xc },
};
static const dw4_metafield mo_f26[] = {
    { "_dataList", 0, 0x14 },
    { "_ramList", 0, 0x18 },
};
static const dw4_metafield mo_f27[] = {
    { "_version", 1, 0xc },
};
static const dw4_metafield mo_f30[] = {
    { "_system", 0, 0x10 },
    { "_messenger", 0, 0x14 },
    { "_infoList", 0, 0x18 },
    { "_isUpdateRun", 2, 0x1c },
};
static const dw4_metafield mo_f32[] = {
    { "_ramNo", 1, 0x8 },
    { "_parentInfo", 0, 0xc },
    { "_parentManager", 0, 0x10 },
    { "_isRun", 2, 0x14 },
    { "_st0", 1, 0x18 },
    { "_st1", 1, 0x1c },
    { "_st2", 1, 0x20 },
    { "_st3", 1, 0x24 },
    { "_dataList", 0, 0x28 },
};
static const dw4_metafield mo_f34[] = {
    { "_timeScale", 16, 0x10 },
    { "_timeBias", 12, 0x18 },
    { "_endTime", 12, 0x20 },
    { "_svWorldTime", 12, 0x28 },
    { "_svBeforTime", 12, 0x30 },
    { "_keikaFrame", 16, 0x38 },
};
static const dw4_metafield mo_f35[] = {
    { "_dataBuffer", 7, 0x10 },
    { "_dataSize", 1, 0x14 },
};
static const dw4_metafield mo_f36[] = {
    { "_isClear", 2, 0x20 },
};
static const dw4_metafield mo_f37[] = {
    { "_rgba", 38, 0x1c },
};
static const dw4_metafield mo_f38[] = {
    { "_switch", 0, 0x8 },
    { "_geometryList", 0, 0xc },
    { "_transformList", 0, 0x10 },
    { "_eyePosList", 0, 0x14 },
    { "_intPosList", 0, 0x18 },
};
static const dw4_metafield mo_f39[] = {
    { "_viewerMang", 0, 0x20 },
    { "_viewerPara", 0, 0x24 },
    { "_cameraMode", 0, 0x28 },
    { "_avgPos", 36, 0x2c },
    { "_savePos", 36, 0x38 },
    { "_isPosChange", 2, 0x44 },
    { "_cameraNowFrame", 16, 0x48 },
    { "_cameraNow", 1, 0x4c },
    { "_cameraOld", 1, 0x50 },
    { "_eyeMatrix", 40, 0x54 },
    { "_intMatrix", 40, 0x94 },
    { "_debugZoom", 16, 0xd4 },
    { "_isFirst", 2, 0xd8 },
};
static const dw4_metafield mo_f40[] = {
    { "_data", 0, 0x1c },
};
static const dw4_metafield mo_f41[] = {
    { "_isFirst", 2, 0x10 },
    { "_svEyePos", 36, 0x14 },
    { "_svIntPos", 36, 0x20 },
    { "_moveCode", 4, 0x2c },
    { "_value", 16, 0x30 },
    { "_oneTime", 16, 0x34 },
    { "_endTime", 16, 0x38 },
    { "_movePoint", 1, 0x3c },
};
static const dw4_metafield mo_f42[] = {
    { "_cameraPath", 0, 0x8 },
    { "_endTime", 12, 0x10 },
    { "_totalSec", 16, 0x18 },
};
static const dw4_metafield mo_f43[] = {
    { "_cameraPath", 0, 0x4c },
    { "_camera", 0, 0x50 },
    { "_insight", 0, 0x54 },
    { "_svWorldTimeL", 12, 0x58 },
    { "_nowTimeL", 12, 0x60 },
    { "_timeLength", 12, 0x68 },
    { "_isEnd", 2, 0x70 },
    { "_isFreeze", 2, 0x71 },
};
static const dw4_metafield mo_f44[] = {
    { "_oldPos", 36, 0x20 },
};
static const dw4_metafield mo_f46[] = {
    { "_transform", 0, 0x2c },
};
static const dw4_metafield mo_f47[] = {
    { "_srcNode", 0, 0x6c },
};
static const dw4_metafield mo_f48[] = {
    { "_srcTransform", 0, 0x6c },
};
static const dw4_metafield mo_f50[] = {
    { "_system", 0, 0x10 },
    { "_execDvdErr", 1, 0x14 },
    { "_request", 12, 0x18 },
    { "_hdBGM", 0, 0x20 },
    { "_hdENV", 0, 0x24 },
    { "_hdSEs", 0, 0x28 },
    { "_infoList", 0, 0x2c },
    { "_lsBinObjs", 0, 0x30 },
    { "_baseVolume", 1, 0x34 },
    { "_sndfVolume", 1, 0x38 },
    { "_pauseOnetime", 2, 0x3c },
    { "_dataType", 1, 0x40 },
};
static const dw4_metafield mo_f52[] = {
    { "_adxt", 0, 0x8 },
    { "_sndf", 0, 0xc },
    { "_audioType", 1, 0x10 },
    { "_errVolume", 1, 0x14 },
};
static const dw4_metafield mo_f53[] = {
    { "_target", 4, 0x14 },
    { "_reverb", 1, 0x18 },
    { "_delay", 1, 0x1c },
    { "_xbFxParam", 0, 0x20 },
};
static const dw4_metafield mo_f54[] = {
    { "_lRoom", 1, 0x8 },
    { "_lRoomHF", 1, 0xc },
    { "_flRoomRolloffFactor", 16, 0x10 },
    { "_flDecayTime", 16, 0x14 },
    { "_flDecayHFRatio", 16, 0x18 },
    { "_lReflections", 1, 0x1c },
    { "_flReflectionsDelay", 16, 0x20 },
    { "_lReverb", 1, 0x24 },
    { "_flReverbDelay", 16, 0x28 },
    { "_flDiffusion", 16, 0x2c },
    { "_flDensity", 16, 0x30 },
    { "_flHFReference", 16, 0x34 },
};
static const dw4_metafield mo_f55[] = {
    { "_audio", 0, 0xc },
    { "_volume", 0, 0x10 },
    { "_playID", 12, 0x18 },
    { "_type", 17, 0x20 },
    { "_priority", 17, 0x22 },
};
static const dw4_metafield mo_f57[] = {
    { "_portNo", 1, 0x18 },
    { "_tblSize", 1, 0x1c },
    { "_pcmSize", 1, 0x20 },
    { "_isTransfer", 2, 0x24 },
};
static const dw4_metafield mo_f58[] = {
    { "_req", 1, 0x8 },
    { "_seq", 12, 0x10 },
    { "_isPlaying", 2, 0x18 },
};
static const dw4_metafield mo_f59[] = {
    { "_isExec", 1, 0x8 },
    { "_max", 1, 0xc },
    { "_current", 16, 0x10 },
    { "_sta", 16, 0x14 },
    { "_end", 16, 0x18 },
    { "_unit", 16, 0x1c },
};
static const dw4_metafield mo_f61[] = {
    { "_dataBase", 0, 0x1c },
};
static const dw4_metafield mo_f62[] = {
    { "_charOffsetList", 0, 0x8 },
    { "_charData", 0, 0xc },
    { "_shortOffsetList", 0, 0x10 },
    { "_shortData", 0, 0x14 },
    { "_intOffsetList", 0, 0x18 },
    { "_intData", 0, 0x1c },
    { "_floatOffsetList", 0, 0x20 },
    { "_floatData", 0, 0x24 },
    { "_boolOffsetList", 0, 0x28 },
    { "_boolData", 0, 0x2c },
    { "_stringOffsetList", 0, 0x30 },
    { "_stringData", 0, 0x34 },
};
static const dw4_metafield mo_f64[] = {
    { "_data", 2, 0xc },
};
static const dw4_metafield mo_f65[] = {
    { "_data", 0, 0xc },
};
static const dw4_metafield mo_f66[] = {
    { "_data", 0, 0xc },
};
static const dw4_metafield mo_f67[] = {
    { "_data", 1, 0xc },
};
static const dw4_metafield mo_f68[] = {
    { "_data", 0, 0xc },
};
static const dw4_metafield mo_f71[] = {
    { "_data", 0, 0xc },
};
static const dw4_metafield mo_f72[] = {
    { "_data", 4, 0xc },
};
static const dw4_metafield mo_f73[] = {
    { "_data", 0, 0xc },
};
static const dw4_metafield mo_f74[] = {
    { "_kind", 1, 0x8 },
    { "_sendTime", 12, 0x10 },
    { "_groupName", 4, 0x18 },
    { "_infoName", 4, 0x1c },
    { "_ramNo", 1, 0x20 },
    { "_message", 4, 0x24 },
    { "_mesParam", 4, 0x28 },
};
static const dw4_metafield mo_f76[] = {
    { "_messenger", 0, 0x10 },
    { "_lua", 0, 0x14 },
    { "_buildData", 0, 0x18 },
    { "_activeDataList", 0, 0x1c },
    { "_turningOK", 2, 0x20 },
    { "_disableRemoveAll", 2, 0x21 },
    { "_calledRemoveAll", 2, 0x22 },
};
static const dw4_metafield mo_f77[] = {
    { "_advancec", 1, 0x8 },
    { "_keepMesList", 0, 0xc },
};
static const dw4_metafield mo_f80[] = {
    { "_fd", 0, 0x8 },
};
static const dw4_metafield mo_f81[] = {
    { "_section", 4, 0x14 },
    { "_fnames", 0, 0x18 },
};
static const dw4_metafield mo_f82[] = {
    { "_system", 0, 0x10 },
    { "_messenger", 0, 0x14 },
    { "_sceneInfoManager", 0, 0x18 },
    { "_isReadOnetime", 2, 0x1c },
    { "_onetimeCount", 1, 0x20 },
    { "_fnames", 0, 0x24 },
    { "_infoList", 0, 0x28 },
    { "_dirList", 0, 0x2c },
    { "_readInfoList", 0, 0x30 },
    { "_importantInfoList", 0, 0x34 },
    { "_loaded", 1, 0x38 },
    { "_proc", 1, 0x3c },
};
static const dw4_metafield mo_f83[] = {
    { "_root", 0, 0x20 },
    { "_fonts", 0, 0x24 },
    { "_fontIdx", 1, 0x28 },
    { "_gaPairList", 0, 0x2c },
    { "_lineFeedList", 0, 0x30 },
    { "_alignList", 0, 0x34 },
    { "_convertData", 0, 0x38 },
    { "_condition00", 4, 0x3c },
    { "_condition01", 4, 0x40 },
    { "_history", 1, 0x44 },
};
static const dw4_metafield mo_f84[] = {
    { "_category", 4, 0x8 },
    { "_panel", 4, 0xc },
    { "_geomAttrs", 0, 0x10 },
};
static const dw4_metafield mo_f88[] = {
    { "_unicodeList", 0, 0x1c },
};
static const dw4_metafield mo_f89[] = {
    { "_attrSet", 0, 0x10 },
    { "_cbitNo", 1, 0x14 },
    { "_tbitNo", 1, 0x18 },
    { "_width", 16, 0x1c },
    { "_height", 16, 0x20 },
    { "_align", 1, 0x24 },
    { "_kind", 4, 0x28 },
};
static const dw4_metafield mo_f90[] = {
    { "_luaManager", 0, 0x20 },
    { "_isPerfectDrop", 2, 0x24 },
};
static const dw4_metafield mo_f91[] = {
    { "_pos", 36, 0xc },
    { "_genePosIsGlobal", 2, 0x18 },
    { "_genePosList", 0, 0x1c },
    { "_geneRotYRadianList", 0, 0x20 },
    { "_geneEnemyId", 1, 0x24 },
    { "_geneEnemySeq", 4, 0x28 },
    { "_startModeStr", 4, 0x2c },
    { "_startData", 16, 0x30 },
    { "_fillModeStr", 4, 0x34 },
    { "_fillData", 16, 0x38 },
    { "_callLua", 4, 0x3c },
    { "_playerDataList", 0, 0x40 },
};
static const dw4_metafield mo_f93[] = {
    { "_dataList", 0, 0x1c },
};
static const dw4_metafield mo_f94[] = {
    { "_work", 0, 0x2c },
};
static const dw4_metafield mo_f95[] = {
    { "_isSystemFreeze", 2, 0x8 },
    { "_isFreeze", 2, 0x9 },
    { "_playerCount", 1, 0xc },
    { "_nokoriKazu", 1, 0x10 },
    { "_enemyRamList", 0, 0x14 },
    { "_genePoint", 1, 0x18 },
    { "_geneEnemyName", 4, 0x1c },
    { "_geneEnemyRecNo", 1, 0x20 },
    { "_geneEnemyMHp", 1, 0x24 },
};
static const dw4_metafield mo_f96[] = {
    { "_dataList", 0, 0xc },
};
static const dw4_metafield mo_f98[] = {
    { "_id", 1, 0xc },
    { "_rank", 1, 0x10 },
    { "_rate", 1, 0x14 },
};
static const dw4_metafield mo_f100[] = {
    { "_geneCount", 1, 0x8 },
    { "_geneMaxCount", 1, 0xc },
    { "_itemDataList", 0, 0x10 },
    { "_itemLastDataList", 0, 0x14 },
};
static const dw4_metafield mo_f106[] = {
    { "_transform", 0, 0x2c },
    { "_checkFlag", 1, 0x30 },
    { "_halfWidth", 16, 0x34 },
    { "_upRange", 16, 0x38 },
    { "_downRange", 16, 0x3c },
    { "_pos", 36, 0x40 },
    { "_oldPos", 36, 0x4c },
    { "_landPos", 36, 0x58 },
    { "_landPosOK", 2, 0x64 },
};
static const dw4_metafield mo_f107[] = {
    { "_order", 0, 0x20 },
    { "_hitTraversal", 0, 0x24 },
    { "_probe", 0, 0x28 },
    { "_isHitWall", 2, 0x2c },
    { "_mat90", 40, 0x30 },
};
static const dw4_metafield mo_f108[] = {
    { "_switchgraph", 0, 0x20 },
    { "_checkSwitch", 0, 0x24 },
    { "_nameList", 0, 0x1c },
    { "_kind", 1, 0x28 },
};
static const dw4_metafield mo_f110[] = {
    { "_infoName", 4, 0x20 },
    { "_ramNo", 1, 0x24 },
    { "_kind", 1, 0x28 },
    { "_raymax", 36, 0x8 },
    { "_raymin", 36, 0x14 },
    { "_rayCount", 1, 0x2c },
    { "_rayList", 0, 0x30 },
    { "_hitdataCount", 1, 0x34 },
    { "_hitdataList", 0, 0x38 },
};
static const dw4_metafield mo_f111[] = {
    { "_order", 0, 0x40 },
};
static const dw4_metafield mo_f112[] = {
    { "_infoName", 4, 0x8 },
    { "_ramNo", 1, 0xc },
};
static const dw4_metafield mo_f114[] = {
    { "_keyboard", 0, 0x8 },
};
static const dw4_metafield mo_f115[] = {
    { "_range", 16, 0x20 },
    { "_maxAlpha", 16, 0x24 },
    { "_addAlpha", 16, 0x28 },
    { "_oldTime", 12, 0x30 },
    { "_status", 1, 0x38 },
    { "_color", 38, 0x3c },
    { "_overrideAttrList", 0, 0x4c },
    { "_blendStateAttr", 0, 0x50 },
    { "_blendFunctionAttr", 0, 0x54 },
    { "_colorAttr", 0, 0x58 },
};
static const dw4_metafield mo_f116[] = {
    { "_isOrdered", 2, 0x20 },
    { "_layerSwt", 0, 0x24 },
};
static const dw4_metafield mo_f119[] = {
    { "_groups", 0, 0x1c },
};
static const dw4_metafield mo_f122[] = {
    { "_lightSetList", 0, 0x1c },
};
static const dw4_metafield mo_f123[] = {
    { "_ramNo", 1, 0x8 },
    { "_openSQ", 4, 0xc },
    { "_infoName", 4, 0x10 },
};
static const dw4_metafield mo_f125[] = {
    { "_lockTime", 12, 0x70 },
    { "_playLimitTime", 12, 0x78 },
};
static const dw4_metafield mo_f126[] = {
    { "_system", 0, 0x10 },
    { "_infoList", 0, 0x14 },
    { "_luaState", 0, 0x18 },
    { "_luaGlue", 0, 0x1c },
};
static const dw4_metafield mo_f127[] = {
    { "_dataObject", 0, 0xc },
};
static const dw4_metafield mo_f129[] = {
    { "_dataSize", 1, 0x8 },
    { "_data", 7, 0xc },
};
static const dw4_metafield mo_f131[] = {
    { "_dataList", 0, 0x1c },
};
static const dw4_metafield mo_f132[] = {
    { "_lp", 5, 0x14 },
};
static const dw4_metafield mo_f133[] = {
    { "_wkChkMat", 1, 0x28 },
    { "_wkChkPl", 1, 0x2c },
    { "_wkChgFlagNO", 1, 0x30 },
    { "_wkChgFlag", 2, 0x34 },
    { "_wkPlExist", 255, 0x20 },
    { "_wkMatOnList", 0, 0x38 },
    { "_wkMatOldOnList", 0, 0x3c },
    { "_isLuaCallDisp", 2, 0x40 },
    { "_lua", 0, 0x24 },
};
static const dw4_metafield mo_f134[] = {
    { "_chkBox", 0, 0xc },
};
static const dw4_metafield mo_f136[] = {
    { "_switchgraph", 0, 0x1c },
    { "_dataList", 0, 0x20 },
    { "_search", 0, 0x24 },
};
static const dw4_metafield mo_f137[] = {
    { "_work", 0, 0x2c },
};
static const dw4_metafield mo_f138[] = {
    { "_runFlagList", 0, 0x8 },
    { "_matOnPlLists", 0, 0xc },
};
static const dw4_metafield mo_f139[] = {
    { "_minX", 16, 0x8 },
    { "_maxX", 16, 0xc },
    { "_matNO", 1, 0x10 },
    { "_parent", 0, 0x14 },
    { "_memberList", 0, 0x18 },
};
static const dw4_metafield mo_f141[] = {
    { "_messenger", 0, 0x10 },
    { "_padManager", 0, 0x14 },
    { "_isDisp", 2, 0x18 },
    { "_colorIndex", 1, 0x1c },
    { "_updateCount", 1, 0x20 },
};
static const dw4_metafield mo_f142[] = {
    { "_argData", 0, 0x10 },
    { "_groupList", 0, 0x14 },
    { "_workStack", 0, 0x18 },
    { "_delayStack", 0, 0x1c },
    { "_pushPopStack", 0, 0x20 },
    { "_pushPopCount", 1, 0x24 },
    { "_freezeTime", 12, 0x28 },
    { "_isMemoryAssign", 2, 0x30 },
};
static const dw4_metafield mo_f143[] = {
    { "_isRunCheck", 2, 0x8 },
    { "_debugString", 4, 0xc },
    { "_boolList", 0, 0x10 },
    { "_intList", 0, 0x14 },
    { "_floatList", 0, 0x18 },
    { "_longList", 0, 0x1c },
    { "_vec3fList", 0, 0x20 },
    { "_matrix44fList", 0, 0x24 },
    { "_objectList", 0, 0x28 },
    { "_stringList", 0, 0x2c },
};
static const dw4_metafield mo_f145[] = {
    { "_isUse", 2, 0x8 },
    { "_sendTime", 12, 0x10 },
    { "_groupName", 4, 0x18 },
    { "_infoName", 4, 0x1c },
    { "_ramNo", 1, 0x20 },
    { "_message", 4, 0x24 },
    { "_argData", 0, 0x28 },
};
static const dw4_metafield mo_f147[] = {
    { "_infoNameList", 0, 0xc },
    { "_ramNoList", 0, 0x10 },
    { "_ramList", 0, 0x14 },
};
static const dw4_metafield mo_f149[] = {
    { "_groupName", 4, 0x8 },
    { "_infoName", 4, 0xc },
    { "_ramNo", 1, 0x10 },
    { "_message", 4, 0x14 },
    { "_findRamNoList", 0, 0x18 },
    { "_findRamList", 0, 0x1c },
};
static const dw4_metafield mo_f152[] = {
    { "_oneDataList", 0, 0x1c },
};
static const dw4_metafield mo_f154[] = {
    { "_isMeter", 2, 0x20 },
    { "_timeList", 0, 0x24 },
    { "_numberOffset", 36, 0x28 },
};
static const dw4_metafield mo_f155[] = {
    { "_node", 0, 0xc },
    { "_maxValueF", 16, 0x10 },
    { "_ratioTimeValueF", 16, 0x14 },
    { "_addMaxValueF", 16, 0x18 },
    { "_nowValueF", 16, 0x1c },
    { "_dspValueF", 16, 0x20 },
    { "_nonZeroTimeL", 12, 0x28 },
    { "_nonMaxTimeL", 12, 0x30 },
    { "_ketaKazu", 1, 0x38 },
    { "_isChange", 2, 0x3c },
    { "_isZeroSupp", 2, 0x3d },
    { "_isNotchMode", 2, 0x3e },
    { "_hp", 0, 0x40 },
    { "_mHp", 0, 0x44 },
};
static const dw4_metafield mo_f156[] = {
    { "_luaManager", 0, 0x20 },
    { "_targetObj", 0, 0x24 },
    { "_isDebugHitBox", 2, 0x28 },
};
static const dw4_metafield mo_f158[] = {
    { "_dirRadian", 16, 0xc },
    { "_time", 16, 0x10 },
    { "_limit", 1, 0x14 },
};
static const dw4_metafield mo_f161[] = {
    { "_x1Square", 16, 0xc },
    { "_x2Square", 16, 0x10 },
    { "_x3Square", 16, 0x14 },
    { "_rotLimiter", 16, 0x18 },
    { "_zoneA", 0, 0x1c },
    { "_zoneB", 0, 0x20 },
    { "_zoneC", 0, 0x24 },
    { "_zoneD", 0, 0x28 },
    { "_targetType", 4, 0x2c },
    { "_targetMode", 4, 0x30 },
};
static const dw4_metafield mo_f164[] = {
    { "_comList", 0, 0xc },
};
static const dw4_metafield mo_f166[] = {
    { "_kind", 1, 0xc },
    { "_start", 16, 0x10 },
    { "_length", 16, 0x14 },
    { "_offset", 36, 0x18 },
    { "_boxSize", 36, 0x24 },
};
static const dw4_metafield mo_f167[] = {
    { "_kindString", 4, 0x1c },
};
static const dw4_metafield mo_f168[] = {
    { "_seqName", 4, 0x8 },
    { "_mapNo", 1, 0xc },
    { "_worldPos", 36, 0x10 },
    { "_hStatus", 1, 0x1c },
    { "_hCount", 1, 0x20 },
};
static const dw4_metafield mo_f169[] = {
    { "_isXHoming", 2, 0x10 },
    { "_isYHoming", 2, 0x11 },
    { "_firstFrame", 16, 0x14 },
    { "_secondFrame", 16, 0x18 },
    { "_areaSquare", 16, 0x1c },
    { "_limitRotX", 16, 0x20 },
    { "_limitRotY", 16, 0x24 },
    { "_limitCount", 1, 0x28 },
};
static const dw4_metafield mo_f170[] = {
    { "_aIMapList", 0, 0x10 },
};
static const dw4_metafield mo_f171[] = {
    { "_isHitPlayerBullet", 2, 0x10 },
    { "_isHitEnemyBullet", 2, 0x11 },
    { "_hitBulletAABoxList", 0, 0x14 },
    { "_isHitPlayerTalk", 2, 0x18 },
};
static const dw4_metafield mo_f172[] = {
    { "_dataList", 0, 0x10 },
};
static const dw4_metafield mo_f173[] = {
    { "_recorderNode", 0, 0x10 },
};
static const dw4_metafield mo_f174[] = {
    { "_isFirst", 2, 0x8 },
    { "_calcTime", 12, 0x10 },
    { "_count", 1, 0x18 },
    { "_orgAABoxList", 0, 0x1c },
    { "_AABoxMinList", 0, 0x20 },
    { "_AABoxMaxList", 0, 0x24 },
    { "_AABoxList", 0, 0x28 },
};
static const dw4_metafield mo_f176[] = {
    { "_node", 0, 0x10 },
    { "_work", 0, 0x14 },
};
static const dw4_metafield mo_f177[] = {
    { "_modelName", 4, 0x8 },
    { "_modelRamNo", 1, 0xc },
    { "_modelNode", 0, 0x10 },
    { "_oldMatrix", 40, 0x14 },
};
static const dw4_metafield mo_f178[] = {
    { "_vector", 36, 0x54 },
};
static const dw4_metafield mo_f179[] = {
    { "_worldPosition", 36, 0x54 },
    { "_minSpeed", 16, 0x60 },
    { "_maxSpeed", 16, 0x64 },
    { "_minKyori", 16, 0x68 },
    { "_maxKyori", 16, 0x6c },
};
static const dw4_metafield mo_f180[] = {
    { "_oldPlayerPos", 36, 0x54 },
    { "_vector", 36, 0x60 },
    { "_scalar", 16, 0x6c },
    { "_limitter", 16, 0x70 },
    { "_isFirst", 1, 0x74 },
};
static const dw4_metafield mo_f181[] = {
    { "_mHp", 0, 0x8 },
    { "_hp", 0, 0xc },
    { "_recNo", 1, 0x10 },
    { "_seqCodeName", 4, 0x14 },
    { "_comData", 0, 0x18 },
    { "_comIndex", 1, 0x1c },
    { "_comLabelCount", 1, 0x20 },
    { "_labelSeqList", 0, 0x24 },
    { "_labelNameList", 0, 0x28 },
    { "_labelOffsetList", 0, 0x2c },
    { "_luaBHit", 4, 0x30 },
    { "_luaWHit", 4, 0x34 },
    { "_luaFHit", 4, 0x38 },
    { "_ctrlSt0", 1, 0x3c },
    { "_ctrlSt1", 1, 0x40 },
    { "_isOnCtrl", 2, 0x44 },
    { "_isOnFreeze", 2, 0x45 },
    { "_pdMoveDataList", 0, 0x48 },
    { "_wCheckName", 4, 0x4c },
    { "_aI", 0, 0x50 },
    { "_aIHOffsetY", 16, 0x54 },
    { "_targetMode", 4, 0x58 },
    { "_targetKind", 4, 0x5c },
    { "_targetSpc1", 4, 0x60 },
    { "_targetPos", 36, 0x64 },
    { "_keyInput", 2, 0x70 },
    { "_keyEventName", 4, 0x74 },
    { "_isHitCheck", 2, 0x78 },
    { "_mutekiCount", 16, 0x7c },
    { "_targetDirection", 36, 0x80 },
    { "_directionLimiter", 36, 0x8c },
    { "_direction", 36, 0x98 },
    { "_svLODHighRange", 16, 0xa4 },
    { "_isPosLock", 2, 0xa8 },
    { "_posLockNode", 0, 0xac },
    { "_posLockTrc", 0, 0xb0 },
    { "_posLockModelName", 4, 0xb4 },
    { "_posLockBoneName", 4, 0xb8 },
    { "_posLockOffset", 36, 0xbc },
    { "_moveObjectList", 0, 0xc8 },
    { "_rideOnData", 0, 0xcc },
    { "_debugHitBoxNode", 0, 0xd0 },
    { "_hitBody", 0, 0xd4 },
    { "_isWallCheck", 2, 0xd8 },
    { "_isFloorCheck", 2, 0xd9 },
    { "_isFallCheck", 2, 0xda },
    { "_hitParentName", 4, 0xdc },
    { "_hitParentRamNo", 1, 0xe0 },
    { "_subCommand", 0, 0xe4 },
    { "_baseAABox", 0, 0xe8 },
};
static const dw4_metafield mo_f184[] = {
    { "_seqName", 4, 0xc },
};
static const dw4_metafield mo_f185[] = {
    { "_modeName", 4, 0xc },
};
static const dw4_metafield mo_f186[] = {
    { "_value", 16, 0xc },
    { "_frame", 16, 0x10 },
};
static const dw4_metafield mo_f187[] = {
    { "_value", 16, 0xc },
    { "_frame", 16, 0x10 },
    { "_playTime", 16, 0x14 },
    { "_isSeqStop", 2, 0x18 },
    { "_stopValue", 16, 0x1c },
    { "_stopFrame", 16, 0x20 },
};
static const dw4_metafield mo_f188[] = {
    { "_modelName", 4, 0xc },
    { "_boneName", 4, 0x10 },
};
static const dw4_metafield mo_f190[] = {
    { "_frame", 16, 0xc },
};
static const dw4_metafield mo_f191[] = {
    { "_isRun", 2, 0x8 },
    { "_endTime", 16, 0xc },
    { "_mode", 1, 0x10 },
    { "_value", 16, 0x14 },
    { "_acc", 16, 0x18 },
    { "_speed", 16, 0x1c },
    { "_isSeqStop", 2, 0x20 },
    { "_stopValue", 16, 0x24 },
    { "_stopFrame", 16, 0x28 },
};
static const dw4_metafield mo_f193[] = {
    { "_time", 12, 0x70 },
    { "_timeScale", 16, 0x78 },
    { "_timeBias", 12, 0x80 },
    { "_overrideAttrList", 0, 0x88 },
};
static const dw4_metafield mo_f194[] = {
    { "_value", 16, 0xc },
    { "_frame", 16, 0x10 },
};
static const dw4_metafield mo_f195[] = {
    { "_geneRamNo", 1, 0x14 },
    { "_modelName", 4, 0x18 },
    { "_seqName", 4, 0x1c },
    { "_offset", 36, 0x20 },
    { "_rotation", 36, 0x2c },
    { "_isSeqDead", 2, 0x38 },
    { "_isPositionLock", 2, 0x39 },
};
static const dw4_metafield mo_f196[] = {
    { "_kind", 1, 0x14 },
    { "_bulletMode", 1, 0x18 },
    { "_endFrame", 16, 0x1c },
    { "_offset", 36, 0x20 },
    { "_boxSize", 36, 0x2c },
    { "_isPositionLock", 2, 0x38 },
};
static const dw4_metafield mo_f197[] = {
    { "_sndName", 4, 0x14 },
    { "_sndHandle", 12, 0x18 },
};
static const dw4_metafield mo_f198[] = {
    { "_comList", 0, 0x8 },
};
static const dw4_metafield mo_f199[] = {
    { "_isOneSet", 2, 0x8 },
    { "_runFrame", 16, 0xc },
    { "_startFrame", 16, 0x10 },
};
static const dw4_metafield mo_f201[] = {
    { "_movie", 0, 0x20 },
    { "_playingName", 4, 0x24 },
};
static const dw4_metafield mo_f203[] = {
    { "_parentLayer", 4, 0x10 },
    { "_callLuaName", 4, 0x14 },
    { "_sceneInfo", 0, 0x18 },
};
static const dw4_metafield mo_f204[] = {
    { "_infoList", 0, 0x10 },
    { "_customMenu", 0, 0x14 },
    { "_subMenu", 0, 0x18 },
    { "_subMenuHolder", 0, 0x1c },
};
static const dw4_metafield mo_f205[] = {
    { "_fileCount", 1, 0xc },
};
static const dw4_metafield mo_f207[] = {
    { "_insideFiles", 0, 0x14 },
    { "_dataList", 0, 0x18 },
};
static const dw4_metafield mo_f208[] = {
    { "_insight", 0, 0x8 },
    { "_stage", 0, 0xc },
};
static const dw4_metafield mo_f209[] = {
    { "_insight", 0, 0x20 },
    { "_isUse", 2, 0x28 },
    { "_id", 1, 0x2c },
    { "_dmkind", 4, 0x30 },
    { "_dmName", 4, 0x34 },
    { "_dmNameUni", 255, 0x8 },
    { "_lv", 1, 0x38 },
    { "_hp", 1, 0x3c },
    { "_maxHp", 1, 0x40 },
    { "_mp", 1, 0x44 },
    { "_maxMp", 1, 0x48 },
    { "_dataSize", 1, 0x24 },
    { "_data", 7, 0x1c },
};
static const dw4_metafield mo_f211[] = {
    { "_dBShinka", 0, 0x20 },
    { "_dBPcTech", 0, 0x24 },
    { "_dBWeapon", 0, 0x28 },
    { "_dBArmor1", 0, 0x2c },
    { "_dBArmor2", 0, 0x30 },
    { "_dBAbChip", 0, 0x34 },
    { "_dBEnemy", 0, 0x38 },
    { "_dBEneatk", 0, 0x3c },
    { "_commonDataList", 0, 0x40 },
    { "_playerDataListList", 0, 0x44 },
    { "_isDispFightData", 2, 0x48 },
};
static const dw4_metafield mo_f215[] = {
    { "_kindNo", 1, 0x8 },
    { "_recNo", 1, 0xc },
    { "_isEquip", 2, 0x10 },
};
static const dw4_metafield mo_f218[] = {
    { "_kazu", 1, 0x14 },
};
static const dw4_metafield mo_f220[] = {
    { "_value", 1, 0x14 },
};
static const dw4_metafield mo_f221[] = {
    { "_revision", 1, 0x14 },
};
static const dw4_metafield mo_f222[] = {
    { "_pocket", 1, 0x18 },
};
static const dw4_metafield mo_f223[] = {
    { "_baseNo", 1, 0x14 },
};
static const dw4_metafield mo_f226[] = {
    { "_nowPage", 1, 0x54 },
    { "_maxPage", 1, 0x58 },
    { "_cursor", 1, 0x5c },
};
static const dw4_metafield mo_f227[] = {
    { "_padManager", 0, 0x20 },
    { "_cameraMode", 1, 0x24 },
    { "_lightMode", 1, 0x28 },
};
static const dw4_metafield mo_f228[] = {
    { "_messenger", 0, 0x10 },
    { "_system", 0, 0x14 },
    { "_inforam", 0, 0x18 },
    { "_insight", 0, 0x1c },
    { "_slotSaveData", 0, 0x20 },
    { "_gameUseData", 0, 0x24 },
    { "_flagWork", 0, 0x28 },
    { "_nextStat", 1, 0x2c },
    { "_intfStat", 1, 0x30 },
    { "_mcUtilCtrl", 0, 0x34 },
    { "_kindHard", 1, 0x38 },
    { "_difficultMode", 1, 0x3c },
    { "_isTitle", 2, 0x40 },
    { "_utilUsePlNo", 1, 0x44 },
};
static const dw4_metafield mo_f229[] = {
    { "_isTitle", 2, 0x10 },
    { "_st0", 1, 0x14 },
    { "_st1", 1, 0x18 },
    { "_st2", 1, 0x1c },
    { "_st3", 1, 0x20 },
};
static const dw4_metafield mo_f230[] = {
    { "_nameSelList", 0, 0x1c },
};
static const dw4_metafield mo_f231[] = {
    { "_padManager", 0, 0x24 },
    { "_system", 0, 0x20 },
    { "_kindHard", 1, 0x28 },
    { "_difficultMax", 1, 0x2c },
};
static const dw4_metafield mo_f232[] = {
    { "_messenger", 0, 0x10 },
    { "_padManager", 0, 0x14 },
    { "_comMdlCtrl", 0, 0x18 },
    { "_commonIntf", 0, 0x1c },
    { "_kindHard", 1, 0x20 },
    { "_oldPadData", 1, 0x24 },
    { "_selMax", 1, 0x28 },
    { "_ramNo", 1, 0x2c },
    { "_isCansel", 2, 0x30 },
    { "_isEnd", 2, 0x31 },
    { "_selPoint", 1, 0x34 },
    { "_mcSelPoint", 1, 0x38 },
    { "_st0", 1, 0x3c },
    { "_st1", 1, 0x40 },
    { "_st2", 1, 0x44 },
    { "_st3", 1, 0x48 },
};
static const dw4_metafield mo_f233[] = {
    { "_messenger", 0, 0x10 },
    { "_openDataList", 0, 0x14 },
    { "_closeDataList", 0, 0x18 },
    { "_pos", 36, 0x1c },
};
static const dw4_metafield mo_f234[] = {
    { "_isRun", 2, 0x10 },
    { "_isRdy", 2, 0x11 },
    { "_isEntry", 2, 0x12 },
    { "_isCtrl", 2, 0x13 },
    { "_isCansel", 2, 0x14 },
    { "_isMesWin", 2, 0x15 },
    { "_isSystem", 2, 0x16 },
    { "_isNoSelMdl", 2, 0x17 },
    { "_newLoadSel", 1, 0x18 },
    { "_isNewMake", 2, 0x1c },
    { "_isRdyCancel", 2, 0x1d },
    { "_oldPadData", 1, 0x20 },
    { "_st0", 1, 0x24 },
    { "_st1", 1, 0x28 },
    { "_st2", 1, 0x2c },
    { "_st3", 1, 0x30 },
};
static const dw4_metafield mo_f235[] = {
    { "_mcSelPoint", 1, 0x10 },
    { "_svDataSelPoint", 1, 0x14 },
    { "_padManager", 0, 0x18 },
    { "_comMdlCtrl", 0, 0x1c },
    { "_textOrder", 0, 0x20 },
    { "_commonIntf", 0, 0x24 },
    { "_mesWin", 0, 0x28 },
    { "_statDisp", 0, 0x2c },
    { "_isSaveArea", 2, 0x30 },
    { "_isUpStatWin", 2, 0x31 },
    { "_isDownStatWin", 2, 0x32 },
    { "_isSlotWin", 2, 0x33 },
    { "_isSelCur", 2, 0x34 },
    { "_kind", 1, 0x38 },
    { "_plNo", 1, 0x3c },
    { "_mesKind", 1, 0x40 },
    { "_result", 1, 0x44 },
    { "_isEnd", 2, 0x48 },
    { "_isCancel", 2, 0x49 },
    { "_st0", 1, 0x4c },
    { "_st1", 1, 0x50 },
    { "_st2", 1, 0x54 },
    { "_st3", 1, 0x58 },
};
static const dw4_metafield mo_f236[] = {
    { "_comMdlCtrl", 0, 0xc },
    { "_textOrder", 0, 0x10 },
    { "_commonIntf", 0, 0x14 },
    { "_messenger", 0, 0x8 },
    { "_plNo", 1, 0x18 },
    { "_dispPos", 1, 0x1c },
    { "_isEnd", 2, 0x20 },
    { "_isAnmEnd", 2, 0x21 },
    { "_closeKind", 1, 0x24 },
    { "_kind", 1, 0x28 },
    { "_dataNo", 1, 0x2c },
    { "_isUseData", 2, 0x30 },
    { "_st0", 1, 0x34 },
    { "_st1", 1, 0x38 },
    { "_st2", 1, 0x3c },
    { "_st3", 1, 0x40 },
};
static const dw4_metafield mo_f237[] = {
    { "_statDataList", 0, 0x10 },
};
static const dw4_metafield mo_f239[] = {
    { "_selectPoint", 1, 0x10 },
    { "_maxSel", 1, 0x14 },
    { "_plNo", 1, 0x18 },
    { "_result", 1, 0x1c },
    { "_kind", 1, 0x20 },
    { "_isEnd", 2, 0x24 },
    { "_isCancel", 2, 0x25 },
    { "_padManager", 0, 0x28 },
    { "_comMdlCtrl", 0, 0x2c },
    { "_textOrder", 0, 0x30 },
    { "_commonIntf", 0, 0x34 },
    { "_mesWin", 0, 0x38 },
    { "_st0", 1, 0x3c },
    { "_st1", 1, 0x40 },
    { "_st2", 1, 0x44 },
    { "_st3", 1, 0x48 },
};
static const dw4_metafield mo_f241[] = {
    { "_chaSelDegi", 1, 0x30 },
    { "_degiName", 255, 0x10 },
    { "_nameCur", 1, 0x34 },
    { "_mojiSelPoint", 1, 0x38 },
};
static const dw4_metafield mo_f242[] = {
    { "_messenger", 0, 0x10 },
    { "_padManager", 0, 0x14 },
    { "_textOrder", 0, 0x18 },
    { "_isWinOpen", 2, 0x1c },
    { "_isWinClose", 2, 0x1d },
    { "_isSelect", 2, 0x1e },
    { "_isSystemMes", 2, 0x1f },
    { "_isMesErase", 2, 0x20 },
    { "_isMesCom", 2, 0x21 },
    { "_isCtrl", 2, 0x22 },
    { "_isDisp", 2, 0x23 },
    { "_kindCtrl", 1, 0x24 },
    { "_statCtrl", 1, 0x28 },
    { "_ramNo", 1, 0x2c },
    { "_curPoint", 1, 0x30 },
    { "_mesNo", 1, 0x34 },
    { "_sysMesNo", 1, 0x38 },
    { "_sysStat", 1, 0x3c },
};
static const dw4_metafield mo_f243[] = {
    { "_messenger", 0, 0x10 },
    { "_padManager", 0, 0x14 },
    { "_comMdlCtrl", 0, 0x18 },
    { "_textOrder", 0, 0x1c },
    { "_ramNo", 1, 0x20 },
    { "_selDataNo", 1, 0x24 },
    { "_langID", 1, 0x28 },
    { "_tateMax", 1, 0x2c },
    { "_tateMin", 1, 0x30 },
    { "_tatePoint", 1, 0x34 },
    { "_yokoPoint", 1, 0x38 },
    { "_yokoCurPos", 1, 0x3c },
    { "_oldPadData", 1, 0x40 },
    { "_nameMojiMax", 1, 0x44 },
    { "_nameCurPos", 1, 0x48 },
    { "_isEnd", 2, 0x4c },
    { "_isMakeName", 2, 0x4d },
    { "_isQuestion", 2, 0x4e },
    { "_isAnswer", 2, 0x4f },
    { "_isNameOK", 2, 0x50 },
    { "_isSideCur", 2, 0x51 },
    { "_st0", 1, 0x54 },
    { "_st1", 1, 0x58 },
    { "_st2", 1, 0x5c },
    { "_st3", 1, 0x60 },
};
static const dw4_metafield mo_f244[] = {
    { "_messenger", 0, 0x10 },
    { "_padManager", 0, 0x14 },
    { "_comMdlCtrl", 0, 0x18 },
    { "_textOrder", 0, 0x1c },
    { "_commonIntf", 0, 0x20 },
    { "_kindHard", 1, 0x24 },
    { "_oldPadData", 1, 0x28 },
    { "_selMax", 1, 0x2c },
    { "_ramNo", 1, 0x30 },
    { "_isOpen", 2, 0x34 },
    { "_isSelect", 2, 0x35 },
    { "_isCansel", 2, 0x36 },
    { "_isReOpenReq", 2, 0x37 },
    { "_isEnd", 2, 0x38 },
    { "_selPoint", 1, 0x3c },
    { "_mcSelPoint", 1, 0x40 },
    { "_mode", 1, 0x44 },
    { "_mcStat", 1, 0x48 },
    { "_st0", 1, 0x4c },
    { "_st1", 1, 0x50 },
    { "_st2", 1, 0x54 },
    { "_st3", 1, 0x58 },
};
static const dw4_metafield mo_f245[] = {
    { "_messenger", 0, 0x10 },
    { "_lua", 0, 0x14 },
};
static const dw4_metafield mo_f246[] = {
    { "_isEntry", 2, 0xc },
    { "_isRdy", 2, 0xd },
    { "_isClose", 2, 0xe },
    { "_isCtrl", 2, 0xf },
    { "_isCutConnect", 2, 0x10 },
    { "_utilReturn", 1, 0x14 },
    { "_utilNext", 1, 0x18 },
    { "_isHaveSaveData", 2, 0x1c },
    { "_haveSaveData", 0, 0x20 },
    { "_sysStat0", 1, 0x24 },
    { "_sysStat1", 1, 0x28 },
    { "_sysStat2", 1, 0x2c },
    { "_sysStat3", 1, 0x30 },
    { "_sysCount0", 1, 0x8 },
};
static const dw4_metafield mo_f248[] = {
    { "_connectNO", 1, 0x8 },
    { "_saveDataList", 0, 0xc },
    { "_accessPlList", 0, 0x10 },
};
static const dw4_metafield mo_f250[] = {
    { "_padManager", 0, 0x24 },
    { "_system", 0, 0x20 },
    { "_mcUtilCtrl", 0, 0x28 },
    { "_connect", 1, 0x2c },
    { "_reCheck", 2, 0x30 },
    { "_retryCount", 1, 0x34 },
    { "_isUseSave", 2, 0x38 },
    { "_isMtap", 2, 0x39 },
    { "_select", 1, 0x3c },
    { "_errTarget", 1, 0x40 },
    { "_errType", 1, 0x44 },
};
static const dw4_metafield mo_f251[] = {
    { "_st0", 1, 0x10 },
    { "_st1", 1, 0x14 },
    { "_st2", 1, 0x18 },
    { "_st3", 1, 0x1c },
};
static const dw4_metafield mo_f253[] = {
    { "_isConnect", 2, 0x8 },
    { "_isFile", 2, 0x9 },
    { "_totalSize", 1, 0xc },
    { "_freeSize", 1, 0x10 },
    { "_isFormat", 2, 0x14 },
};
static const dw4_metafield mo_f254[] = {
    { "_fileKaz", 1, 0x18 },
    { "_detail", 1, 0x1c },
};
static const dw4_metafield mo_f257[] = {
    { "_mName", 4, 0x18 },
};
static const dw4_metafield mo_f258[] = {
    { "_messenger", 0, 0x8 },
    { "_isUseUtil", 2, 0xc },
    { "_isRdy", 2, 0xd },
    { "_isRun", 2, 0xe },
    { "_isMtap", 2, 0xf },
    { "_isFormatRun", 2, 0x10 },
    { "_tgCon", 1, 0x14 },
    { "_usePlNo", 1, 0x18 },
    { "_kind", 1, 0x1c },
    { "_result", 1, 0x20 },
    { "_isResult", 2, 0x24 },
    { "_svData", 0, 0x28 },
    { "_slot", 0, 0x2c },
    { "_st0", 1, 0x30 },
    { "_st1", 1, 0x34 },
    { "_st2", 1, 0x38 },
    { "_st3", 1, 0x3c },
};
static const dw4_metafield mo_f263[] = {
    { "_viewerSIManager", 0, 0x2c },
    { "_lockRamList", 0, 0x30 },
};
static const dw4_metafield mo_f264[] = {
    { "_dbId", 1, 0xec },
    { "_itemObject", 0, 0xf0 },
    { "_kind", 1, 0xf4 },
    { "_isNamed", 2, 0xf8 },
    { "_dispPlayerRamNo", 1, 0xfc },
    { "_isDispName", 2, 0x100 },
    { "_fontType", 4, 0x104 },
    { "_isColorLight", 2, 0x108 },
};
static const dw4_metafield mo_f270[] = {
    { "_isPlayer", 2, 0xec },
    { "_dispRamNoList", 0, 0xf0 },
    { "_dispPosNoList", 0, 0xf4 },
    { "_timerList", 0, 0xf8 },
    { "_isFirstList", 0, 0xfc },
    { "_poisonDamage", 1, 0x100 },
    { "_poisonEndurance", 1, 0x104 },
    { "_downDataList", 0, 0x108 },
    { "_upDataList", 0, 0x10c },
    { "_messenger", 0, 0x110 },
};
static const dw4_metafield mo_f271[] = {
    { "_viewerSIManager", 0, 0x2c },
    { "_padManager", 0, 0x30 },
    { "_gameRam", 0, 0x34 },
};
static const dw4_metafield mo_f272[] = {
    { "_padManager", 0, 0x2c },
};
static const dw4_metafield mo_f273[] = {
    { "_isPowerOn", 2, 0xec },
    { "_timerCount", 1, 0xf0 },
    { "_bit", 1, 0xf4 },
    { "_exp", 1, 0xf8 },
};
static const dw4_metafield mo_f274[] = {
    { "_turnAtkTimer", 0, 0x114 },
    { "_bodyAtkSt0", 1, 0x118 },
    { "_bodyAtkPad", 1, 0x11c },
    { "_bodyAtkTimer", 16, 0x120 },
    { "_isPanel", 2, 0x124 },
    { "_isMainLobby", 2, 0x125 },
    { "_wCheckSt", 1, 0x128 },
    { "_wCheckMode", 1, 0x12c },
};
static const dw4_metafield mo_f275[] = {
    { "_manager", 0, 0x8 },
    { "_messenger", 0, 0xc },
    { "_page", 1, 0x10 },
    { "_playerNo", 1, 0x14 },
    { "_cursor", 1, 0x18 },
    { "_offset", 1, 0x1c },
    { "_lineMode", 1, 0x20 },
    { "_playerDataList", 0, 0x24 },
    { "_isNoGateDisk", 2, 0x28 },
    { "_isNoHealing", 2, 0x29 },
    { "_isNoParaUp", 2, 0x2a },
    { "_isNoCureling", 2, 0x2b },
    { "_textSetList", 0, 0x2c },
    { "_textColorList", 0, 0x30 },
    { "_listKazu", 1, 0x34 },
    { "_isEmg", 2, 0x38 },
};
static const dw4_metafield mo_f276[] = {
    { "_listFolder", 0, 0x3c },
    { "_listColor", 0, 0x40 },
};
static const dw4_metafield mo_f277[] = {
    { "_listFolder", 0, 0x3c },
    { "_listColor", 0, 0x40 },
    { "_playerWork", 0, 0x44 },
};
static const dw4_metafield mo_f278[] = {
    { "_listFolder", 0, 0x3c },
    { "_listColor", 0, 0x40 },
};
static const dw4_metafield mo_f279[] = {
    { "_padManager", 0, 0x20 },
};
static const dw4_metafield mo_f281[] = {
    { "_work", 0, 0x2c },
};
static const dw4_metafield mo_f282[] = {
    { "_page", 1, 0x8 },
    { "_isWindowGenerate", 2, 0xc },
    { "_isCursorGenerate", 2, 0xd },
    { "_panelWaza", 0, 0x10 },
    { "_panelItem", 0, 0x14 },
    { "_panelStat", 0, 0x18 },
    { "_retIsFire", 2, 0x1c },
    { "_retWazaLabel", 4, 0x20 },
    { "_playerWork", 0, 0x24 },
    { "_textSetList", 0, 0x28 },
    { "_textColorList", 0, 0x2c },
};
static const dw4_metafield mo_f283[] = {
    { "_padManager", 0, 0x20 },
};
static const dw4_metafield mo_f284[] = {
    { "_order", 1, 0x10 },
    { "_tgPlayer", 1, 0x14 },
    { "_isSelect", 2, 0x18 },
    { "_st0", 1, 0x1c },
    { "_st1", 1, 0x20 },
    { "_st2", 1, 0x24 },
    { "_st3", 1, 0x28 },
};
static const dw4_metafield mo_f286[] = {
    { "_padManager", 0, 0x24 },
    { "_system", 0, 0x20 },
    { "_kindHard", 1, 0x28 },
};
static const dw4_metafield mo_f287[] = {
    { "_messenger", 0, 0x10 },
    { "_openDataList", 0, 0x14 },
    { "_closeDataList", 0, 0x18 },
    { "_pos", 36, 0x1c },
};
static const dw4_metafield mo_f288[] = {
    { "_isRun", 2, 0x10 },
    { "_isRdy", 2, 0x11 },
    { "_isEntry", 2, 0x12 },
    { "_isCtrl", 2, 0x13 },
    { "_isCansel", 2, 0x14 },
    { "_isMesWin", 2, 0x15 },
    { "_isSystem", 2, 0x16 },
    { "_isOneSave", 2, 0x17 },
    { "_newLoadSel", 1, 0x18 },
    { "_isCharMake", 2, 0x1c },
    { "_oldPadData", 1, 0x20 },
    { "_st0", 1, 0x24 },
    { "_st1", 1, 0x28 },
    { "_st2", 1, 0x2c },
    { "_st3", 1, 0x30 },
};
static const dw4_metafield mo_f290[] = {
    { "_messenger", 0, 0x8 },
    { "_gameRam", 0, 0xc },
    { "_playerNo", 1, 0x10 },
    { "_playerParameter", 0, 0x14 },
    { "_dBShinka", 0, 0x18 },
    { "_list", 0, 0x1c },
};
static const dw4_metafield mo_f291[] = {
    { "_id", 1, 0x8 },
    { "_name", 4, 0xc },
    { "_level", 1, 0x10 },
    { "_hpMax", 1, 0x14 },
    { "_mpMax", 1, 0x18 },
    { "_tsuyosa", 1, 0x1c },
    { "_mamori", 1, 0x20 },
    { "_kashikosa", 1, 0x24 },
    { "_seishin", 1, 0x28 },
    { "_subayasa", 1, 0x2c },
    { "_blunt", 1, 0x30 },
    { "_slash", 1, 0x34 },
    { "_stab", 1, 0x38 },
    { "_bash", 1, 0x3c },
    { "_shot", 1, 0x40 },
    { "_crush", 1, 0x44 },
    { "_blast", 1, 0x48 },
    { "_heal", 1, 0x4c },
    { "_force", 1, 0x50 },
};
static const dw4_metafield mo_f294[] = {
    { "_xdataMenu", 1, 0x54 },
    { "_parameter", 1, 0x58 },
};
static const dw4_metafield mo_f295[] = {
    { "_bankMenu", 1, 0x54 },
};
static const dw4_metafield mo_f296[] = {
    { "_selectCursor", 1, 0x54 },
};
static const dw4_metafield mo_f297[] = {
    { "_cursor", 1, 0x54 },
    { "_conItemNo", 1, 0x58 },
    { "_diskCnt", 1, 0x5c },
    { "_kazu", 1, 0x60 },
    { "_tanka", 1, 0x64 },
};
static const dw4_metafield mo_f298[] = {
    { "_account", 0, 0x54 },
    { "_playerNoList", 0, 0x58 },
};
static const dw4_metafield mo_f299[] = {
    { "_cardInfoList", 0, 0x54 },
    { "_cardRamNoList", 0, 0x58 },
};
static const dw4_metafield mo_f301[] = {
    { "_decideList", 0, 0x60 },
};
static const dw4_metafield mo_f302[] = {
    { "_playerNoList", 0, 0x54 },
    { "_digimonNoList", 0, 0x58 },
    { "_wpuNoListList", 0, 0x5c },
    { "_isDigimonChange", 2, 0x60 },
    { "_isWeaponChange", 2, 0x61 },
    { "_topMenu", 1, 0x64 },
    { "_isDemoRun", 2, 0x68 },
};
static const dw4_metafield mo_f303[] = {
    { "_diskIdList", 0, 0x54 },
    { "_cursor", 1, 0x58 },
    { "_maxSell", 1, 0x5c },
    { "_kazu", 1, 0x60 },
    { "_tanka", 1, 0x64 },
};
static const dw4_metafield mo_f304[] = {
    { "_editBit", 1, 0x54 },
    { "_editMax", 1, 0x58 },
};
static const dw4_metafield mo_f305[] = {
    { "_shinkaCtrl", 0, 0x60 },
};
static const dw4_metafield mo_f306[] = {
    { "_salesItemList", 0, 0x60 },
    { "_decideList", 0, 0x64 },
};
static const dw4_metafield mo_f308[] = {
    { "_itemBaseList", 0, 0x60 },
};
static const dw4_metafield mo_f309[] = {
    { "_salesList", 0, 0x60 },
};
static const dw4_metafield mo_f310[] = {
    { "_junkMenu", 1, 0x54 },
    { "_totalGift", 1, 0x58 },
    { "_junkItemList", 0, 0x5c },
};
static const dw4_metafield mo_f311[] = {
    { "_panelName", 4, 0x70 },
};
static const dw4_metafield mo_f313[] = {
    { "_playerNoList", 0, 0x70 },
};
static const dw4_metafield mo_f323[] = {
    { "_resetTrgTime", 12, 0x20 },
};
static const dw4_metafield mo_f326[] = {
    { "_windowPro", 0, 0x20 },
    { "_whoGenerate", 1, 0x24 },
    { "_subWndNo", 1, 0x28 },
};
static const dw4_metafield mo_f327[] = {
    { "_statusMenu", 1, 0x54 },
};
static const dw4_metafield mo_f328[] = {
    { "_kindListPos", 1, 0x54 },
    { "_kindListMax", 1, 0x58 },
    { "_pocketPos", 1, 0x5c },
    { "_playerList", 0, 0x60 },
    { "_powerSocket", 0, 0x64 },
    { "_mainSlot", 0, 0x68 },
    { "_subSlot", 0, 0x6c },
    { "_wpuPocket", 0, 0x70 },
    { "_apuPocket", 0, 0x74 },
    { "_deviceFolder", 0, 0x78 },
};
static const dw4_metafield mo_f329[] = {
    { "_playerNoList", 0, 0x54 },
};
static const dw4_metafield mo_f330[] = {
    { "_isBankFolder", 2, 0x60 },
    { "_kindList", 0, 0x64 },
    { "_isAbType", 1, 0x68 },
    { "_isEquipDisable", 2, 0x6c },
    { "_isUnknownEnable", 2, 0x6d },
    { "_isUnknownDisable", 2, 0x6e },
    { "_isAutoClose", 2, 0x6f },
    { "_decideList", 0, 0x70 },
};
static const dw4_metafield mo_f331[] = {
    { "_cursor", 1, 0x54 },
    { "_playerNoList", 0, 0x58 },
    { "_receipt", 1, 0x5c },
    { "_diskList", 0, 0x60 },
    { "_sendDisk", 0, 0x64 },
    { "_sendMax", 1, 0x68 },
};
static const dw4_metafield mo_f332[] = {
    { "_equipMenu", 1, 0x54 },
};
static const dw4_metafield mo_f333[] = {
    { "_impItems", 0, 0x54 },
};
static const dw4_metafield mo_f334[] = {
    { "_folderMenu", 1, 0x54 },
};
static const dw4_metafield mo_f335[] = {
    { "_editBit", 1, 0x54 },
    { "_editMax", 1, 0x58 },
    { "_playerNoList", 0, 0x5c },
    { "_receipt", 1, 0x60 },
};
static const dw4_metafield mo_f336[] = {
    { "_skillMenu", 1, 0x60 },
    { "_shinkaCtrl", 0, 0x64 },
    { "_skillList", 0, 0x68 },
};
static const dw4_metafield mo_f338[] = {
    { "_work", 0, 0x2c },
};
static const dw4_metafield mo_f339[] = {
    { "_parameter", 0, 0x8 },
    { "_preview", 0, 0xc },
    { "_weaponSalesList", 0, 0x10 },
    { "_armorSalesList", 0, 0x14 },
    { "_chipSalesList", 0, 0x18 },
    { "_junkSalesList", 0, 0x1c },
    { "_junkGift", 1, 0x20 },
};
static const dw4_metafield mo_f346[] = {
    { "_selectDevice", 1, 0x54 },
    { "_deviceFolderList", 0, 0x58 },
    { "_receipt", 1, 0x5c },
    { "_playerNoList", 0, 0x60 },
    { "_playerDeviceCnt", 0, 0x64 },
};
static const dw4_metafield mo_f353[] = {
    { "_padManager", 0, 0x20 },
    { "_mcUtilCtrl", 0, 0x24 },
    { "_isMakeFileOK", 2, 0x28 },
    { "_select", 1, 0x2c },
};
static const dw4_metafield mo_f354[] = {
    { "_isRun", 2, 0x10 },
    { "_logoCount", 1, 0x14 },
    { "_gameMenuCnt", 1, 0x18 },
    { "_gameMenuNext", 1, 0x1c },
    { "_st0", 1, 0x20 },
    { "_st1", 1, 0x24 },
    { "_st2", 1, 0x28 },
    { "_st3", 1, 0x2c },
};
static const dw4_metafield mo_f356[] = {
    { "_messenger", 0, 0x10 },
    { "_selLang", 1, 0x14 },
    { "_ctrlPos", 1, 0x18 },
    { "_isOK", 2, 0x1c },
    { "_comConf", 1, 0x20 },
    { "_lightConf", 1, 0x24 },
    { "_oldCountry", 1, 0x28 },
    { "_dispComConf", 1, 0x2c },
    { "_dispLightConf", 1, 0x30 },
    { "_dispCountryConf", 1, 0x34 },
};
static const dw4_metafield mo_f357[] = {
    { "_insight", 0, 0x8 },
    { "_messenger", 0, 0xc },
    { "_padManager", 0, 0x10 },
    { "_playerNo", 1, 0x14 },
    { "_isRun", 2, 0x18 },
    { "_st0", 1, 0x1c },
    { "_st1", 1, 0x20 },
    { "_st2", 1, 0x24 },
    { "_st3", 1, 0x28 },
    { "_entCode", 1, 0x2c },
    { "_retCode", 1, 0x30 },
    { "_subWindow", 0, 0x34 },
    { "_mother", 0, 0x38 },
    { "_textCloseTypeList", 0, 0x3c },
    { "_textCloseNameList", 0, 0x40 },
    { "_modelCloseInfoNameList", 0, 0x44 },
    { "_modelCloseRamNoList", 0, 0x48 },
    { "_modelCloseSeqNameList", 0, 0x4c },
};
static const dw4_metafield mo_f358[] = {
    { "_nowProcKazu", 1, 0x50 },
};
static const dw4_metafield mo_f360[] = {
    { "_infoName", 4, 0x50 },
    { "_selectMax", 1, 0x54 },
    { "_offsetPos", 36, 0x58 },
    { "_startPoint", 1, 0x64 },
    { "_isNoCancel", 2, 0x68 },
    { "_decideList", 0, 0x6c },
};
static const dw4_metafield mo_f362[] = {
    { "_startTime", 12, 0x20 },
    { "_loop1Time", 12, 0x28 },
    { "_loop2Time", 12, 0x30 },
    { "_stopTime", 12, 0x38 },
    { "_isFirstTime", 2, 0x40 },
    { "_time", 12, 0x48 },
    { "_timeScale", 16, 0x50 },
    { "_timeBias", 12, 0x58 },
    { "_beforeTime", 12, 0x60 },
    { "_playTime", 12, 0x68 },
};
static const dw4_metafield mo_f363[] = {
    { "_disp", 1, 0x8 },
    { "_verDataList", 0, 0xc },
};
static const dw4_metafield mo_f365[] = {
    { "_index", 1, 0x8 },
    { "_kind", 1, 0xc },
};
static const dw4_metafield mo_f370[] = {
    { "_geometry", 0, 0x2c },
    { "_offsetNext", 16, 0x30 },
    { "_maxValue", 1, 0x34 },
    { "_mode", 1, 0x38 },
    { "_numList", 0, 0x3c },
    { "_work", 0, 0x40 },
};
static const dw4_metafield mo_f371[] = {
    { "_dispNum", 1, 0x8 },
    { "_realNum", 1, 0xc },
    { "_changeNum", 1, 0x10 },
};
static const dw4_metafield mo_f372[] = {
    { "_buildNo", 1, 0x14 },
    { "_isAsm", 2, 0x18 },
    { "_libOpt", 4, 0x1c },
    { "_libAsm", 4, 0x20 },
};
static const dw4_metafield mo_f373[] = {
    { "_isConnect", 2, 0x8 },
    { "_LStick", 37, 0xc },
    { "_RStick", 37, 0x14 },
    { "_lTrg", 1, 0x1c },
    { "_lRpt", 1, 0x20 },
    { "_lStk", 1, 0x24 },
    { "_lLast", 1, 0x28 },
    { "_lTime", 1, 0x2c },
    { "_rTrg", 1, 0x30 },
    { "_rRpt", 1, 0x34 },
    { "_rStk", 1, 0x38 },
    { "_rLast", 1, 0x3c },
    { "_rTime", 1, 0x40 },
    { "_button", 1, 0x44 },
    { "_trigger", 1, 0x48 },
    { "_repeat", 1, 0x4c },
    { "_last", 1, 0x50 },
    { "_rptime", 1, 0x54 },
    { "_enaLen", 16, 0x58 },
    { "_adAngle", 16, 0x5c },
    { "_1sttime", 1, 0x60 },
    { "_2ndtime", 1, 0x64 },
};
static const dw4_metafield mo_f375[] = {
    { "_system", 0, 0x10 },
    { "_padList", 0, 0x14 },
    { "_kbReceiver", 0, 0x18 },
    { "_is1pAllDevice", 2, 0x1c },
    { "_isPadDisable", 2, 0x1d },
};
static const dw4_metafield mo_f377[] = {
    { "_mainSwitch", 0, 0x1c },
    { "_subSwitch", 0, 0x20 },
    { "_endTimeFloat", 16, 0x24 },
    { "_endTimeLong", 12, 0x28 },
};
static const dw4_metafield mo_f378[] = {
    { "_transform", 0, 0x2c },
    { "_particleTimer", 0, 0x30 },
    { "_work", 0, 0x34 },
};
static const dw4_metafield mo_f379[] = {
    { "_positionLockNode", 0, 0x8 },
    { "_positionLockOffset", 36, 0xc },
};
static const dw4_metafield mo_f380[] = {
    { "_id", 1, 0x8 },
    { "_time", 12, 0x10 },
};
static const dw4_metafield mo_f382[] = {
    { "_pointNo", 1, 0x20 },
};
static const dw4_metafield mo_f383[] = {
    { "_switch", 0, 0x1c },
    { "_dataList", 0, 0x20 },
};
static const dw4_metafield mo_f384[] = {
    { "_isResetTime", 2, 0x20 },
    { "_isResetRotAndScale", 2, 0x21 },
};
static const dw4_metafield mo_f385[] = {
    { "_orderType", 1, 0xc },
    { "_isConAllChk", 2, 0x10 },
    { "_connect", 1, 0x14 },
    { "_result", 1, 0x18 },
    { "_isEnd", 2, 0x1c },
    { "_dummyCount", 1, 0x8 },
    { "_st0", 1, 0x20 },
    { "_st1", 1, 0x24 },
    { "_st2", 1, 0x28 },
    { "_st3", 1, 0x2c },
    { "_imageWork", 0, 0x30 },
    { "_mountWork", 0, 0x34 },
    { "_iconWork", 0, 0x38 },
};
static const dw4_metafield mo_f386[] = {
    { "_size", 1, 0xc },
    { "_data", 7, 0x8 },
};
static const dw4_metafield mo_f387[] = {
    { "_ramNo", 1, 0x8 },
    { "_openSQ", 4, 0xc },
    { "_infoName", 4, 0x10 },
};
static const dw4_metafield mo_f389[] = {
    { "_mem", 7, 0x8 },
};
static const dw4_metafield mo_f390[] = {
    { "_api", 0, 0x20 },
    { "_connectCheck", 0, 0x24 },
};
static const dw4_metafield mo_f392[] = {
    { "_isRdy", 2, 0x2c },
    { "_deliver", 0, 0x30 },
};
static const dw4_metafield mo_f393[] = {
    { "_sndMng", 0, 0x20 },
};
static const dw4_metafield mo_f394[] = {
    { "_sound", 4, 0xc },
    { "_delay", 17, 0x10 },
};
static const dw4_metafield mo_f397[] = {
    { "_actionList", 0, 0x10 },
};
static const dw4_metafield mo_f398[] = {
    { "_padManager", 0, 0x20 },
    { "_isEnableCtrl", 2, 0x24 },
};
static const dw4_metafield mo_f400[] = {
    { "_isTateSelect", 2, 0x10 },
    { "_maxSelect", 1, 0x14 },
    { "_selectNo", 1, 0x18 },
    { "_work", 0, 0x1c },
};
static const dw4_metafield mo_f401[] = {
    { "_offsetPos", 36, 0x8 },
    { "_selectMax", 1, 0x14 },
    { "_isCancel", 2, 0x18 },
    { "_svSeqName", 4, 0x1c },
    { "_decideList", 0, 0x20 },
};
static const dw4_metafield mo_f402[] = {
    { "_svInfoList", 0, 0x20 },
    { "_savePos", 36, 0x24 },
};
static const dw4_metafield mo_f403[] = {
    { "_receiverNode", 0, 0x1c },
    { "_casterNode", 0, 0x20 },
    { "_projShadowShader", 0, 0x24 },
};
static const dw4_metafield mo_f405[] = {
    { "_cri", 0, 0x20 },
    { "_currentBGM", 4, 0x24 },
    { "_playSEs", 0, 0x28 },
};
static const dw4_metafield mo_f406[] = {
    { "_type", 17, 0x10 },
    { "_fnameIdx", 17, 0x12 },
    { "_memoryIdx", 1, 0x14 },
    { "_channel", 17, 0x18 },
    { "_volume", 17, 0x1a },
    { "_priority", 17, 0x1c },
};
static const dw4_metafield mo_f407[] = {
    { "_fnameList", 0, 0x1c },
    { "_dataType", 4, 0x20 },
    { "_baseVolume", 17, 0x24 },
    { "_sndfVolume", 17, 0x26 },
};
static const dw4_metafield mo_f409[] = {
    { "_staticInfoList", 0, 0x20 },
};
static const dw4_metafield mo_f411[] = {
    { "_actConnect", 0, 0xc },
    { "_targetConnect", 1, 0x10 },
    { "_saveVer", 1, 0x14 },
    { "_result", 1, 0x18 },
    { "_operate", 1, 0x1c },
    { "_memCapa", 1, 0x20 },
    { "_fileCapa", 1, 0x24 },
    { "_useMtap", 3, 0x28 },
    { "_chgUseMtap", 3, 0x29 },
    { "_isMemCapaOK", 2, 0x2a },
    { "_isfileCapaOK", 2, 0x2b },
    { "_isEndOperat", 2, 0x2c },
    { "_freeSizeList", 0, 0x30 },
    { "_freeFileList", 0, 0x34 },
    { "_formatList", 0, 0x38 },
    { "_totalSizeList", 0, 0x3c },
    { "_gameData", 0, 0x8 },
    { "_platformData", 0, 0x40 },
};
static const dw4_metafield mo_f414[] = {
    { "_earlyGamedata", 0, 0x40 },
    { "_saveWork", 0, 0x44 },
};
static const dw4_metafield mo_f416[] = {
    { "_memNeed", 1, 0x40 },
    { "_memCapa", 1, 0x44 },
    { "_fileCapa", 1, 0x48 },
};
static const dw4_metafield mo_f417[] = {
    { "_connectMax", 1, 0x8 },
    { "_slotList", 0, 0xc },
    { "_dataSize", 9, 0x10 },
    { "_memNeed", 9, 0x14 },
};
static const dw4_metafield mo_f418[] = {
    { "_fileName", 4, 0x68 },
    { "_imageSize", 1, 0x6c },
    { "_dataOffSet", 255, 0x18 },
    { "_bannerType", 1, 0x70 },
    { "_iconType", 1, 0x74 },
    { "_iconKaz", 1, 0x78 },
    { "_iconSpeed", 1, 0x7c },
    { "_iconLoopType", 1, 0x80 },
    { "_banTplSize", 1, 0x84 },
    { "_banTplData", 7, 0x20 },
    { "_iconTplSize", 1, 0x88 },
    { "_iconTplData", 7, 0x24 },
    { "_comment", 255, 0x28 },
};
static const dw4_metafield mo_f420[] = {
    { "_dirName", 4, 0x18 },
    { "_title", 4, 0x1c },
    { "_offsLF", 10, 0x20 },
    { "_transRate", 9, 0x24 },
    { "_bgColor0", 255, 0x28 },
    { "_bgColor1", 255, 0x30 },
    { "_bgColor2", 255, 0x38 },
    { "_bgColor3", 255, 0x40 },
    { "_lightDir0", 255, 0x48 },
    { "_lightDir1", 255, 0x58 },
    { "_lightDir2", 255, 0x68 },
    { "_lightColor0", 255, 0x78 },
    { "_lightColor1", 255, 0x88 },
    { "_lightColor2", 255, 0x98 },
    { "_ambient", 255, 0xa8 },
    { "_fnameIcon0", 4, 0xb8 },
    { "_fnameIcon1", 4, 0xbc },
    { "_fnameIcon2", 4, 0xc0 },
    { "_saveDataSize", 9, 0xcc },
    { "_dataOffSet", 255, 0xc4 },
    { "_iconCount", 1, 0xd0 },
    { "_image", 0, 0xd4 },
};
static const dw4_metafield mo_f421[] = {
    { "_imageSize", 1, 0x20 },
    { "_image", 0, 0x24 },
    { "_saveDataSize", 9, 0x28 },
    { "_dataOffSet", 255, 0x18 },
};
static const dw4_metafield mo_f422[] = {
    { "_dataSize", 1, 0xc },
    { "_data", 7, 0x8 },
};
static const dw4_metafield mo_f423[] = {
    { "_outputGamedata", 0, 0x44 },
    { "_gameData", 0, 0x40 },
    { "_oneSvDataSize", 1, 0x48 },
    { "_lodeData", 0, 0x4c },
    { "_loadWorkList", 0, 0x50 },
};
static const dw4_metafield mo_f424[] = {
    { "_isConnect", 2, 0x8 },
    { "_isFormat", 2, 0x9 },
    { "_freeSize", 1, 0xc },
    { "_useSize", 1, 0x10 },
    { "_totalSize", 1, 0x14 },
};
static const dw4_metafield mo_f428[] = {
    { "_name", 4, 0x18 },
    { "_totalBytes", 13, 0x20 },
    { "_freeBytes", 13, 0x28 },
    { "_useBytes", 13, 0x30 },
};
static const dw4_metafield mo_f431[] = {
    { "_nowGamedata", 0, 0x40 },
    { "_saveWork", 0, 0x44 },
};
static const dw4_metafield mo_f433[] = {
    { "_switchNode", 0, 0x1c },
};
static const dw4_metafield mo_f434[] = {
    { "_isShutDown", 2, 0x10 },
    { "_svWorldTimeL", 12, 0x18 },
    { "_frameTimeL", 12, 0x20 },
    { "_frameTimeF", 16, 0x28 },
    { "_isActive", 2, 0x2c },
    { "_isFirstTime", 2, 0x2d },
    { "_isFrameSkip", 2, 0x2e },
    { "_random", 0, 0x30 },
    { "_readFileList", 0, 0x34 },
    { "_stageName", 4, 0x38 },
    { "_nextStage", 4, 0x3c },
    { "_isStageLoop", 2, 0x40 },
    { "_bootDirectory", 0, 0x44 },
    { "_globalStrObj", 0, 0x48 },
    { "_discErrInfos", 0, 0x4c },
    { "_viewerScene", 0, 0x50 },
    { "_dvdStat", 1, 0x54 },
    { "_execDvdErr", 1, 0x58 },
    { "_isDvdErr", 2, 0x5c },
    { "_isNowFreeze", 2, 0x5d },
    { "_isNowPadEnable", 2, 0x5e },
    { "_isResetEnable", 2, 0x5f },
    { "_isResetNow", 2, 0x60 },
    { "_isResetLast", 2, 0x61 },
    { "_isResetRelease", 2, 0x62 },
    { "_isSResetEnable", 2, 0x63 },
};
static const dw4_metafield mo_f435[] = {
    { "_playerPosList", 0, 0x10 },
    { "_playerRamNoList", 0, 0x14 },
    { "_enemyPosList", 0, 0x18 },
};
static const dw4_metafield mo_f436[] = {
    { "_isFirstTime", 2, 0x20 },
    { "_work", 0, 0x24 },
};
static const dw4_metafield mo_f437[] = {
    { "_attrSet", 0, 0xc },
};
static const dw4_metafield mo_f438[] = {
    { "_tex", 0, 0xc },
};
static const dw4_metafield mo_f439[] = {
    { "_isTexture", 2, 0x1c },
    { "_dataList", 0, 0x20 },
};
static const dw4_metafield mo_f441[] = {
    { "_textureList", 0, 0x8 },
    { "_attributeList", 0, 0xc },
};
static const dw4_metafield mo_f442[] = {
    { "_system", 0, 0x10 },
    { "_padManager", 0, 0x14 },
    { "_luaManager", 0, 0x18 },
    { "_dataList", 0, 0x1c },
    { "_oldWorldTime", 12, 0x20 },
};
static const dw4_metafield mo_f443[] = {
    { "_startTime", 12, 0x8 },
    { "_resetCondition", 4, 0x10 },
    { "_callLuaFile", 4, 0x14 },
    { "_downTimer", 12, 0x18 },
};
static const dw4_metafield mo_f445[] = {
    { "_syncTransformList", 0, 0x6c },
};
static const dw4_metafield mo_f447[] = {
    { "_buffer", 7, 0xc },
};
static const dw4_metafield mo_f449[] = {
    { "_baseTime", 12, 0x8 },
    { "_elapseTime", 12, 0x10 },
    { "_maxTime", 12, 0x18 },
    { "_targetData", 1, 0x20 },
    { "_dataList", 0, 0x24 },
};
static const dw4_metafield mo_f450[] = {
    { "_time", 12, 0x8 },
    { "_power", 16, 0x10 },
    { "_posList", 0, 0x14 },
};
static const dw4_metafield mo_f454[] = {
    { "_dampeningCoefficient", 16, 0x2c },
    { "_A", 16, 0x30 },
    { "_B", 16, 0x34 },
    { "_waveSpeed", 16, 0x38 },
    { "_shallmin", 16, 0x3c },
    { "_shallmax", 16, 0x40 },
    { "_shalldamp", 16, 0x44 },
    { "_deepmin", 16, 0x48 },
    { "_deepmax", 16, 0x4c },
    { "_deepdamp", 16, 0x50 },
    { "_vertexArray", 0, 0x54 },
    { "_dampeningGrid", 0, 0x58 },
    { "_dplist2VertexNO", 0, 0x5c },
    { "_mapWidth", 9, 0x60 },
    { "_mapHeight", 9, 0x64 },
    { "_pos", 36, 0x68 },
    { "_areaMax", 36, 0x74 },
    { "_areaMin", 36, 0x80 },
    { "_xsize", 16, 0x8c },
    { "_zsize", 16, 0x90 },
    { "_cellSize", 16, 0x94 },
    { "_gridLists", 0, 0x98 },
    { "_maxY", 16, 0x9c },
    { "_minY", 16, 0xa0 },
    { "_defaultY", 16, 0xa4 },
    { "_updateTime", 12, 0xa8 },
    { "_waterMove", 0, 0xb0 },
};
static const dw4_metafield mo_f455[] = {
    { "_attachDataList", 0, 0x20 },
};
static const dw4_metafield mo_f456[] = {
    { "_boneSelectList", 0, 0x8 },
    { "_appearanceListList", 0, 0xc },
};
static const dw4_metafield mo_f458[] = {
    { "_nodeList", 0, 0x1c },
    { "_boneNameList", 0, 0x20 },
    { "_seqDataList", 0, 0x24 },
};
static const dw4_metafield mo_f460[] = {
    { "_label", 4, 0xc },
};
static const dw4_metafield mo_f462[] = {
    { "_dataSize", 1, 0xc },
    { "_data", 7, 0x8 },
};
static const dw4_metafield mo_f463[] = {
    { "_min", 36, 0x8 },
    { "_max", 36, 0x14 },
};
static const dw4_metafield mo_f466[] = {
    { "_oldComponentUnderMouse", 0, 0xc },
    { "_oldFocusedComponent", 0, 0x10 },
    { "_oldPushedComponent", 0, 0x14 },
};
static const dw4_metafield mo_f467[] = {
    { "_animationSystem", 0, 0x20 },
    { "_boneMatrixCacheArray", 7, 0x24 },
    { "_blendMatrixCacheArray", 7, 0x28 },
    { "_appearance", 0, 0x2c },
    { "_animationDatabase", 0, 0x30 },
    { "_modifierList", 0, 0x34 },
    { "_transform", 40, 0x38 },
    { "_forceActorCacheUse", 2, 0x78 },
    { "_actorCacheUsed", 2, 0x79 },
    { "_mvmWhenTraversed", 40, 0x7c },
    { "_inverseViewWhenTraversed", 40, 0xbc },
    { "_update", 2, 0xfc },
    { "_render", 2, 0xfd },
};
static const dw4_metafield mo_f468[] = {
    { "_actor", 0, 0x14 },
    { "_actorList", 0, 0x18 },
    { "_animationDatabase", 0, 0x1c },
    { "_combinerList", 0, 0x20 },
    { "_appearanceList", 0, 0x24 },
};
static const dw4_metafield mo_f470[] = {
    { "_skelOnlys", 0, 0x10 },
    { "_skelAndSkins", 0, 0x14 },
    { "_actors", 0, 0x18 },
    { "_params", 0, 0x1c },
    { "_travFuncs", 0, 0x20 },
    { "_actorMetas", 0, 0x24 },
    { "_viewport", 0, 0x28 },
    { "_skelViewport", 0, 0x2c },
    { "_vsim", 0, 0x30 },
    { "_references", 0, 0x34 },
};
static const dw4_metafield mo_f471[] = {
    { "_skelOnly", 2, 0xc },
    { "_skelAndSkin", 2, 0xd },
};
static const dw4_metafield mo_f473[] = {
    { "_ptNumber", 17, 0x10 },
    { "_fileNumber", 17, 0x12 },
};
static const dw4_metafield mo_f475[] = {
    { "_pWorkArea", 5, 0x8 },
    { "_iWorkSize", 1, 0xc },
    { "_iMaxHandles", 1, 0x10 },
    { "_iMaxChannels", 1, 0x14 },
    { "_iType", 1, 0x18 },
    { "_iMaxStreams", 1, 0x1c },
    { "_iMaxFrequency", 1, 0x20 },
    { "_bIsInitialized", 2, 0x24 },
    { "_filename", 4, 0x28 },
};
static const dw4_metafield mo_f476[] = {
    { "_bIsOpen", 2, 0x2c },
    { "_pBuffer", 5, 0x30 },
    { "_pBufferPtr", 5, 0x34 },
    { "_pTmpBuffer", 5, 0x38 },
    { "_bUseAsync", 2, 0x3c },
    { "_bUseAlchemyAsync", 2, 0x3d },
    { "_bUseBuffer", 2, 0x3e },
    { "_bBufferFilled", 2, 0x3f },
    { "_iBufferSize", 1, 0x40 },
    { "_iBufferPos", 1, 0x44 },
    { "_iSeekPosition", 1, 0x48 },
    { "_iFileSize", 1, 0x4c },
    { "_iSectorSize", 1, 0x50 },
    { "_lSleepTime", 13, 0x58 },
};
static const dw4_metafield mo_f477[] = {
    { "_poolIndex", 1, 0x78 },
    { "_allocedBytes", 13, 0x80 },
    { "_nAllocs", 1, 0x88 },
    { "_nFrees", 1, 0x8c },
    { "_maxSize", 13, 0x90 },
    { "_eventTracker", 0, 0x98 },
    { "_allocedBytesHigh", 13, 0xa0 },
    { "_netAllocsHigh", 1, 0xa8 },
    { "_isActive", 2, 0x70 },
    { "_isReassignable", 2, 0x71 },
    { "_allocationLock", 0, 0x74 },
    { "_elementSize", 9, 0xac },
    { "_alignment", 10, 0xb0 },
    { "_aliasedMemoryPool", 0, 0xb4 },
};
static const dw4_metafield mo_f478[] = {
    { "_func", 6, 0xc },
    { "_refValue", 16, 0x10 },
};
static const dw4_metafield mo_f479[] = {
    { "_enabled", 2, 0xc },
};
static const dw4_metafield mo_f480[] = {
    { "_priority", 1, 0xc },
    { "_bindingList", 0, 0x10 },
    { "_trackList", 0, 0x14 },
    { "_transitionList", 0, 0x18 },
    { "_keyFrameTimeOffset", 12, 0x20 },
    { "_startTime", 12, 0x28 },
    { "_duration", 12, 0x30 },
    { "_useAnimationTransBoolArray", 0, 0x38 },
};
static const dw4_metafield mo_f481[] = {
    { "_hierarchy", 0, 0x8 },
    { "_boneTrackIdxArray", 7, 0xc },
    { "_bindCount", 1, 0x10 },
    { "_chainSwapList", 0, 0x14 },
    { "_reflectTrack", 0, 0x18 },
};
static const dw4_metafield mo_f483[] = {
    { "_boneInfoListList", 0, 0x30 },
    { "_boneInfoListBase", 0, 0x34 },
    { "_animationStateList", 0, 0x38 },
    { "_resultQuaternionArray", 7, 0x3c },
    { "_animationCacheMatrixArray", 7, 0x40 },
    { "_cacheTime", 12, 0x48 },
    { "_cacheValid", 2, 0x50 },
    { "_hierarchyUpdated", 2, 0x51 },
    { "_boneMatrixArray", 7, 0x54 },
    { "_blendMatrixArray", 7, 0x58 },
    { "_animationStateTime", 12, 0x10 },
    { "_lastCleanStatesTime", 12, 0x18 },
    { "_cleanStatesTimeThreshold", 12, 0x20 },
    { "_cleanStatesTransitionMargin", 12, 0x28 },
};
static const dw4_metafield mo_f484[] = {
    { "_animationState", 0, 0xc },
    { "_transformSource", 0, 0x10 },
    { "_constantQuaternion", 38, 0x14 },
    { "_constantTranslation", 36, 0x24 },
    { "_priority", 1, 0x30 },
    { "_useAnimationTranslation", 2, 0x34 },
    { "_lastKeyframe", 1, 0x8 },
    { "_reflect", 1, 0x38 },
};
static const dw4_metafield mo_f489[] = {
    { "_skeletonList", 0, 0x14 },
    { "_animationList", 0, 0x18 },
    { "_skinList", 0, 0x1c },
    { "_appearanceList", 0, 0x20 },
    { "_combinerList", 0, 0x24 },
};
static const dw4_metafield mo_f490[] = {
    { "_boneTranslationArray", 7, 0xc },
};
static const dw4_metafield mo_f492[] = {
    { "_boneIndex", 1, 0x8 },
    { "_transform", 0, 0xc },
    { "_type", 6, 0x10 },
};
static const dw4_metafield mo_f495[] = {
    { "_animation", 0, 0x8 },
    { "_combineMode", 6, 0xc },
    { "_transitionMode", 6, 0x10 },
    { "_status", 6, 0x14 },
    { "_baseState", 0, 0x18 },
    { "_new", 2, 0x1c },
    { "_currentBlendRatio", 16, 0x20 },
    { "_localTime", 12, 0x28 },
    { "_baseTransitionTime", 12, 0x30 },
    { "_timeScale", 16, 0x38 },
    { "_timeBias", 12, 0x40 },
    { "_blendStartTime", 12, 0x48 },
    { "_blendStartRatio", 16, 0x50 },
    { "_blendRatioRange", 16, 0x54 },
    { "_blendDuration", 12, 0x58 },
    { "_animationStartTime", 12, 0x60 },
    { "_cachedCycleTime", 12, 0x68 },
    { "_cachedCycleNumber", 13, 0x70 },
    { "_cycleMatchTargetState", 0, 0x78 },
    { "_isCycleMatchTarget", 2, 0x7c },
    { "_cycleMatchDisable", 2, 0x7d },
    { "_manualCycleMatch", 2, 0x7e },
    { "_cycleMatchBaseDuration", 12, 0x80 },
    { "_cycleMatchDurationRange", 12, 0x88 },
    { "_cycleMatchTargetDuration", 12, 0x90 },
    { "_timeRequested", 12, 0x98 },
};
static const dw4_metafield mo_f498[] = {
    { "_animHierarchy", 0, 0xc },
};
static const dw4_metafield mo_f499[] = {
    { "_source", 0, 0xc },
    { "_constantQuaternion", 38, 0x10 },
    { "_constantTranslation", 36, 0x20 },
};
static const dw4_metafield mo_f501[] = {
    { "_baseAnimation", 0, 0x8 },
    { "_transitionPointList", 0, 0xc },
    { "_params", 0, 0x10 },
};
static const dw4_metafield mo_f503[] = {
    { "_startRatio", 16, 0x8 },
    { "_endRatio", 16, 0xc },
    { "_duration", 12, 0x10 },
    { "_targetStartTime", 12, 0x18 },
};
static const dw4_metafield mo_f504[] = {
    { "_transitionTime", 12, 0x8 },
    { "_transitionParams", 0, 0x10 },
};
static const dw4_metafield mo_f506[] = {
    { "_skin", 0, 0xc },
    { "_attachedSkins", 0, 0x10 },
    { "_attachedGraphs", 0, 0x14 },
    { "_segmentOverrideNameList", 0, 0x18 },
    { "_segmentOverrideGraphList", 0, 0x1c },
};
static const dw4_metafield mo_f509[] = {
    { "_arenaState", 5, 0x70 },
    { "_rawMemory", 5, 0x7c },
    { "_isAlchemyMemory", 2, 0x80 },
    { "_systemAllocated", 13, 0x88 },
    { "_elementSize", 9, 0x90 },
    { "_maxSize", 13, 0x98 },
    { "_size", 13, 0xa0 },
    { "_preSize", 9, 0xa8 },
    { "_alignment", 10, 0xac },
    { "_eventTracker", 0, 0xb0 },
    { "_isActive", 2, 0x74 },
    { "_allocationLock", 0, 0x78 },
    { "_poolIndex", 1, 0xb4 },
    { "_heapIntegrityCheckLevel", 6, 0xb8 },
    { "_messageLevel", 6, 0xbc },
    { "_poolOptionFlags", 1, 0xc0 },
    { "_poolPreSized", 1, 0xc4 },
    { "_smallestChunkSize", 9, 0xc8 },
};
static const dw4_metafield mo_f510[] = {
    { "_cachedUnitID", 17, 0xa },
    { "_cachedAttrIndex", 17, 0x8 },
};
static const dw4_metafield mo_f514[] = {
    { "_metaList", 0, 0x8 },
    { "_nonSharableMetaList", 0, 0xc },
    { "_attributeList", 0, 0x10 },
};
static const dw4_metafield mo_f515[] = {
    { "_attributes", 0, 0x20 },
    { "_trigger", 2, 0x24 },
};
static const dw4_metafield mo_f516[] = {
    { "_default", 0, 0x14 },
    { "_cachedOverride", 1, 0x18 },
    { "_popProc", 5, 0x1c },
    { "_hasChangedFromLastIncrementalFlush", 2, 0x20 },
    { "_lastIncrementalFlushedAttr", 0, 0x24 },
    { "_hasChangedFromRoot", 2, 0x28 },
    { "_lastFlushedAttr", 0, 0x2c },
    { "_cachedRenderPackage", 0, 0x30 },
};
static const dw4_metafield mo_f518[] = {
    { "_numAttrStacks", 1, 0xc },
    { "_attrStacks", 0, 0x10 },
    { "_attrDefaults", 0, 0x14 },
    { "_attrIncrementalUpdateList", 0, 0x18 },
    { "_attrRootUpdateList", 0, 0x1c },
    { "_nextAttrUpdateList", 0, 0x20 },
    { "_lightAttrAddrs", 0, 0x24 },
    { "_lightAttrStackAddrs", 0, 0x28 },
    { "_updateLightAttrs", 0, 0x2c },
    { "_popProcData", 5, 0x30 },
    { "_capabilityManager", 0, 0x34 },
    { "_defaultManager", 0, 0x38 },
    { "_simpleLightMgr", 2, 0x3c },
    { "_lightDisableAttrPool", 0, 0x40 },
    { "_stackChanged", 2, 0x8 },
    { "_attrStackIndexTable", 7, 0x44 },
    { "_attrStackIndexTableSize", 1, 0x48 },
};
static const dw4_metafield mo_f519[] = {
    { "_immediateMode", 2, 0x8 },
};
static const dw4_metafield mo_f521[] = {
    { "_colors", 255, 0x8 },
    { "_disabledColor", 38, 0x48 },
};
static const dw4_metafield mo_f522[] = {
    { "_mode", 1, 0x20 },
    { "_axis", 36, 0x24 },
    { "_origin", 36, 0x30 },
    { "_mvm", 0, 0x3c },
};
static const dw4_metafield mo_f523[] = {
    { "_bitCount", 9, 0x14 },
};
static const dw4_metafield mo_f524[] = {
    { "_charMetricsList", 0, 0x1c },
    { "_textureBind", 0, 0x20 },
};
static const dw4_metafield mo_f525[] = {
    { "_equation", 6, 0x14 },
};
static const dw4_metafield mo_f526[] = {
    { "_src", 6, 0xc },
    { "_dst", 6, 0x10 },
    { "_eq", 6, 0x14 },
    { "_blendEquationExt", 0, 0x18 },
    { "_blendConstant", 8, 0x1c },
    { "_blendStage", 17, 0x1e },
    { "_blendConstantFloat", 16, 0x20 },
    { "_blendA", 6, 0x24 },
    { "_blendB", 6, 0x28 },
    { "_blendC", 6, 0x2c },
    { "_blendD", 6, 0x30 },
};
static const dw4_metafield mo_f527[] = {
    { "_attr", 0, 0x8 },
    { "_fwdPtr", 0, 0xc },
};
static const dw4_metafield mo_f528[] = {
    { "_matrixCache", 7, 0xc },
    { "_currentMatrixCount", 9, 0x10 },
    { "_matrixCacheCapacity", 9, 0x14 },
};
static const dw4_metafield mo_f530[] = {
    { "_matrixCache", 7, 0xc },
    { "_matrixIndices", 7, 0x10 },
    { "_currentMatrixCount", 9, 0x14 },
    { "_capacity", 9, 0x18 },
};
static const dw4_metafield mo_f532[] = {
    { "_blendMatrixIndices", 0, 0x28 },
    { "_skeletonTransform", 40, 0x2c },
    { "_skeletonInverseTransform", 40, 0x6c },
};
static const dw4_metafield mo_f533[] = {
    { "_enabled", 2, 0xc },
};
static const dw4_metafield mo_f534[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f537[] = {
    { "_value", 2, 0x8 },
};
static const dw4_metafield mo_f538[] = {
    { "_parameters", 0, 0xc },
    { "_displayList", 0, 0x10 },
    { "_attrList", 0, 0x14 },
    { "_modelViewAttr", 0, 0x18 },
    { "_box", 0, 0x1c },
    { "_border", 0, 0x20 },
    { "_path", 0, 0x24 },
    { "_draw", 2, 0x28 },
};
static const dw4_metafield mo_f539[] = {
    { "_time", 12, 0x8 },
    { "_useWholeAnimation", 2, 0x10 },
    { "_setBoundingBoxes", 2, 0x11 },
    { "_skinnedBox", 0, 0x14 },
    { "_bboxList", 0, 0x18 },
    { "_preserveActorBoxes", 2, 0x1c },
    { "_exclusionList", 0, 0x20 },
    { "_metaObjectList", 0, 0x24 },
};
static const dw4_metafield mo_f540[] = {
    { "_sphere", 0, 0x8 },
};
static const dw4_metafield mo_f542[] = {
    { "_capacity", 1, 0x8 },
    { "_hashCapacity", 1, 0xc },
    { "_callStacks", 0, 0x10 },
    { "_hashIndex", 0, 0x14 },
};
static const dw4_metafield mo_f544[] = {
    { "_cameraType", 6, 0x1c },
    { "_horizontalFieldOfView", 16, 0x2c },
    { "_nearPlane", 16, 0x30 },
    { "_farPlane", 16, 0x34 },
    { "_deadfield1", 2, 0x20 },
    { "_deadfield2", 16, 0x24 },
    { "_deadfield3", 16, 0x28 },
};
static const dw4_metafield mo_f545[] = {
    { "_cameraPath", 0, 0x4c },
    { "_camera", 0, 0x50 },
};
static const dw4_metafield mo_f547[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f553[] = {
    { "_clearMode", 9, 0xc },
    { "_color", 38, 0x10 },
    { "_accum", 38, 0x20 },
    { "_depth", 31, 0x30 },
    { "_stencil", 9, 0x38 },
    { "_colorPacked", 9, 0x3c },
    { "_depthF", 16, 0x40 },
};
static const dw4_metafield mo_f554[] = {
    { "_buffersToClear", 9, 0xc },
};
static const dw4_metafield mo_f555[] = {
    { "_enabled", 2, 0xc },
};
static const dw4_metafield mo_f556[] = {
    { "_fmt", 6, 0x8 },
    { "_numEntries", 9, 0xc },
    { "_stride", 1, 0x10 },
    { "_pData", 7, 0x14 },
    { "_clutSize", 1, 0x18 },
    { "_clutDirty", 2, 0x1c },
    { "_isAlphaScaled", 2, 0x1d },
};
static const dw4_metafield mo_f557[] = {
    { "_objects", 0, 0x8 },
    { "_grid", 0, 0xc },
    { "_box", 0, 0x10 },
    { "_staticCount", 1, 0x14 },
    { "_priority", 1, 0x18 },
    { "_active", 2, 0x1c },
};
static const dw4_metafield mo_f559[] = {
    { "_cells", 0, 0x8 },
    { "_activeCells", 0, 0xc },
    { "_processedCells", 0, 0x24 },
    { "_checkedGroups", 0, 0x28 },
    { "_dynamicCollisions", 0, 0x2c },
    { "_staticCollisions", 0, 0x30 },
    { "_lostGroups", 0, 0x34 },
    { "_sizeX", 1, 0x10 },
    { "_sizeY", 1, 0x14 },
    { "_sizeZ", 1, 0x18 },
    { "_maxRadius", 16, 0x1c },
    { "_bound", 0, 0x38 },
    { "_deltas", 36, 0x3c },
    { "_rate", 1, 0x48 },
    { "_maxPriority", 1, 0x20 },
};
static const dw4_metafield mo_f560[] = {
    { "_grid", 0, 0x8 },
    { "_staticGroupType", 0, 0xc },
};
static const dw4_metafield mo_f561[] = {
    { "_transform", 0, 0x20 },
    { "_position", 36, 0x24 },
    { "_lastPosition", 36, 0x30 },
    { "_collisionPosition", 36, 0x3c },
    { "_direction", 36, 0x48 },
    { "_radius", 16, 0x54 },
    { "_time", 16, 0x58 },
    { "_collisionCells", 1, 0x5c },
};
static const dw4_metafield mo_f563[] = {
    { "_grid", 0, 0x14 },
};
static const dw4_metafield mo_f564[] = {
    { "_color", 38, 0xc },
    { "_colorPacked", 9, 0x1c },
};
static const dw4_metafield mo_f566[] = {
    { "_red", 2, 0xc },
    { "_green", 2, 0xd },
    { "_blue", 2, 0xe },
    { "_alpha", 2, 0xf },
    { "_unused", 9, 0x10 },
};
static const dw4_metafield mo_f567[] = {
    { "_attrStack", 0, 0x34 },
    { "_transformStack", 0, 0x38 },
    { "_vc", 0, 0x3c },
    { "_capabilityManager", 0, 0x20 },
    { "_defaultManager", 0, 0x24 },
    { "_flushedAttrs", 0, 0x40 },
    { "_sorter", 0, 0x44 },
    { "_matrixPool", 0, 0x48 },
    { "_timePool", 0, 0x4c },
    { "_blendMatrixPool", 0, 0x50 },
    { "_texMatPool", 0, 0x54 },
    { "_vertexBlendMatListPool", 0, 0x58 },
    { "_matrixObjectPool", 0, 0x5c },
    { "_projectionMatrixPool", 0, 0x60 },
    { "_viewMat", 40, 0x64 },
    { "_viewMatInv", 40, 0xa4 },
    { "_modeMask", 1, 0xe4 },
    { "_matrixOptimization", 0, 0xe8 },
    { "_normalizeNormalsEnable", 0, 0xec },
    { "_timeStack", 0, 0xf0 },
    { "_matrixObjectList", 0, 0xf4 },
    { "_timeLongBuf", 12, 0x28 },
    { "_timeBuffered", 2, 0x30 },
    { "_boneMatrixPaletteList", 0, 0xf8 },
    { "_blendMatrixPaletteList", 0, 0xfc },
    { "_blendMatrixPaletteLengths", 0, 0x100 },
    { "_segmentOverrideNames", 0, 0x104 },
    { "_segmentOverrideStacks", 0, 0x108 },
    { "_blendMatricesAttrPool", 0, 0x10c },
    { "_projMat", 40, 0x110 },
    { "_defaultTimeAttr", 0, 0x150 },
    { "_jointChainCount", 1, 0x154 },
    { "_jointMvmBase", 40, 0x158 },
    { "_jointMvmInverseBase", 40, 0x198 },
    { "_jointGraphRootTraversed", 2, 0x31 },
};
static const dw4_metafield mo_f568[] = {
    { "_mvmList", 0, 0x1d8 },
    { "_xformInfoList", 0, 0x1dc },
    { "_moList", 0, 0x1e0 },
    { "_containsShader", 2, 0x1e4 },
    { "_bound", 0, 0x1e8 },
    { "_transformList", 0, 0x1ec },
    { "_isSkin", 2, 0x1f0 },
    { "_environmentShader2List", 0, 0x1f4 },
    { "_bmpaList", 0, 0x1f8 },
    { "_jointChainCount", 1, 0x1fc },
    { "_jointBaseMvmIndex", 1, 0x200 },
    { "_currentBoneIndex", 1, 0x204 },
};
static const dw4_metafield mo_f569[] = {
    { "_parentIdx", 1, 0x8 },
    { "_source", 0, 0xc },
    { "_moIdx", 1, 0x10 },
    { "_invJoint", 5, 0x14 },
    { "_name", 0, 0x18 },
    { "_isNode", 2, 0x1c },
    { "_isJointChainStart", 2, 0x1d },
    { "_boneIndex", 1, 0x20 },
};
static const dw4_metafield mo_f571[] = {
    { "_count", 1, 0x8 },
    { "_capacity", 1, 0xc },
    { "_data", 7, 0x10 },
};
static const dw4_metafield mo_f572[] = {
    { "_fieldList", 0, 0x34 },
};
static const dw4_metafield mo_f573[] = {
    { "_compressedTranslationList", 0, 0x8 },
    { "_compressedQuaternionList", 0, 0xc },
    { "_compressedTimeList", 0, 0x10 },
    { "_translationBase", 16, 0x14 },
    { "_translationRangeOverMaxUShort", 16, 0x18 },
    { "_quaternionBase", 16, 0x1c },
    { "_quaternionRangeOverMaxUShort", 16, 0x20 },
    { "_animationDuration", 13, 0x28 },
    { "_playMode", 6, 0x30 },
    { "_lastTime", 1, 0x34 },
    { "_channels", 8, 0x38 },
    { "_interpolationMethod", 255, 0x39 },
};
static const dw4_metafield mo_f574[] = {
    { "_compressedTranslationList", 0, 0x8 },
    { "_compressedQuatList", 0, 0xc },
    { "_compressedScaleList", 0, 0x10 },
    { "_compressedTimeList", 0, 0x14 },
    { "_translationBase", 16, 0x18 },
    { "_translationRange", 16, 0x1c },
    { "_quatBase", 16, 0x20 },
    { "_quatRange", 16, 0x24 },
    { "_scaleBase", 16, 0x28 },
    { "_scaleRange", 16, 0x2c },
};
static const dw4_metafield mo_f578[] = {
    { "_pExtList", 0, 0x8 },
    { "_iNumExts", 1, 0xc },
    { "_pExtInstances", 0, 0x10 },
};
static const dw4_metafield mo_f580[] = {
    { "_pMeta", 0, 0x8 },
    { "_pName", 4, 0xc },
    { "_pVendorName", 7, 0x10 },
};
static const dw4_metafield mo_f584[] = {
    { "_buttonMap", 7, 0x8 },
    { "_isMapped", 2, 0xc },
};
static const dw4_metafield mo_f586[] = {
    { "_controllers", 0, 0x8 },
};
static const dw4_metafield mo_f587[] = {
    { "_copyType", 6, 0xc },
    { "_pRDAttr", 0, 0x10 },
    { "_pImage", 0, 0x14 },
    { "_pTextureAttr", 0, 0x18 },
    { "_sourceX", 1, 0x1c },
    { "_sourceY", 1, 0x20 },
    { "_destinationX", 1, 0x24 },
    { "_destinationY", 1, 0x28 },
    { "_sizeW", 1, 0x2c },
    { "_sizeH", 1, 0x30 },
};
static const dw4_metafield mo_f588[] = {
    { "_gridType", 0, 0x3c },
    { "_staticGroupType", 0, 0x40 },
    { "_sizeX", 1, 0x28 },
    { "_sizeY", 1, 0x2c },
    { "_sizeZ", 1, 0x30 },
    { "_fileName", 4, 0x34 },
    { "_grid", 0, 0x38 },
};
static const dw4_metafield mo_f589[] = {
    { "_initialized", 2, 0xc },
    { "_visualContext", 0, 0x10 },
    { "_audioContext", 0, 0x14 },
};
static const dw4_metafield mo_f590[] = {
    { "_mwply", 11, 0x8 },
    { "_cprmbuf", 5, 0xc },
    { "_adxt", 11, 0x10 },
    { "_adxwork", 5, 0x14 },
    { "_macroFunction", 11, 0x18 },
};
static const dw4_metafield mo_f591[] = {
    { "_enabled", 2, 0xc },
    { "_mode", 6, 0x10 },
};
static const dw4_metafield mo_f593[] = {
    { "_name", 4, 0x14 },
    { "_flags", 9, 0x18 },
};
static const dw4_metafield mo_f595[] = {
    { "_stateCollectionHandle", 9, 0xc },
    { "_stateField", 0, 0x10 },
};
static const dw4_metafield mo_f597[] = {
    { "_count", 1, 0x8 },
    { "_capacity", 1, 0xc },
    { "_data", 7, 0x10 },
};
static const dw4_metafield mo_f598[] = {
    { "_destObj", 0, 0x8 },
    { "_destMeta", 0, 0xc },
    { "_destMetaClassName", 4, 0x10 },
    { "_destMetaFieldName", 4, 0x14 },
    { "_dpi", 0, 0x18 },
};
static const dw4_metafield mo_f599[] = {
    { "_dataPumpList", 0, 0x14 },
};
static const dw4_metafield mo_f602[] = {
    { "_dataPumpList", 0, 0x8 },
};
static const dw4_metafield mo_f603[] = {
    { "_decalOffset", 9, 0x14 },
};
static const dw4_metafield mo_f604[] = {
    { "_elementList", 0, 0x28 },
};
static const dw4_metafield mo_f605[] = {
    { "_geometryElement", 0, 0x8 },
    { "_colorChanger", 0, 0xc },
    { "_transform", 0, 0x10 },
    { "_fitMode", 6, 0x14 },
    { "_hMargin", 16, 0x18 },
    { "_vMargin", 16, 0x1c },
};
static const dw4_metafield mo_f607[] = {
    { "_mouseMotionFunction", 5, 0xc },
    { "_mouseButtonDownFunction", 5, 0x10 },
    { "_mouseButtonUpFunction", 5, 0x14 },
    { "_windowMoveFunction", 5, 0x18 },
    { "_windowResizeFunction", 5, 0x1c },
    { "_windowCloseFunction", 5, 0x20 },
    { "_controllerJoystickMotionFunction", 5, 0x24 },
    { "_controllerButtonDownFunction", 5, 0x28 },
    { "_controllerButtonUpFunction", 5, 0x2c },
    { "_controllerButtonPressureFunction", 5, 0x30 },
    { "_controllerConnectionFunction", 5, 0x34 },
    { "_controllerDisconnectionFunction", 5, 0x38 },
    { "_controllerSliderFunction", 5, 0x3c },
    { "_controllerPointOfViewFunction", 5, 0x40 },
    { "_keyDownFunction", 5, 0x44 },
    { "_keyUpFunction", 5, 0x48 },
};
static const dw4_metafield mo_f610[] = {
    { "_objectList", 0, 0x8 },
    { "_dependencies", 0, 0xc },
    { "_order", 0, 0x10 },
    { "_checkPoints", 0, 0x14 },
    { "_hasCircularDependencies", 2, 0x18 },
};
static const dw4_metafield mo_f611[] = {
    { "_enabled", 2, 0xc },
};
static const dw4_metafield mo_f612[] = {
    { "_enabled", 2, 0xc },
};
static const dw4_metafield mo_f613[] = {
    { "_index", 1, 0xc },
    { "_resolveMethod", 6, 0x10 },
    { "_refType", 6, 0x14 },
    { "_ref", 5, 0x18 },
};
static const dw4_metafield mo_f614[] = {
    { "_name", 4, 0x14 },
    { "_externalDirectoryList", 0, 0x18 },
    { "_infoList", 0, 0x1c },
    { "_managingResource", 0, 0x20 },
    { "_loadPendingState", 2, 0x30 },
    { "_validState", 2, 0x31 },
    { "_compatibleState", 2, 0x32 },
    { "_loadedRefCount", 1, 0x34 },
    { "_metaFieldPerObjectIndices", 0, 0x3c },
    { "_concreteState", 2, 0x38 },
    { "_sharingState", 2, 0x24 },
    { "_trackUniqueEntries", 2, 0x25 },
    { "_uniqueEntryList", 0, 0x28 },
    { "_refList", 0, 0x2c },
    { "_autoWriteFilePreProcessState", 2, 0x40 },
    { "_useMemoryPoolAssignmentsState", 2, 0x41 },
    { "_forceWriteMemoryPoolInfoFromMetaState", 2, 0x42 },
    { "_loadingSemaphore", 0, 0x44 },
};
static const dw4_metafield mo_f617[] = {
    { "_contents", 0, 0xc },
};
static const dw4_metafield mo_f618[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f621[] = {
    { "_currentProperties", 0, 0x8 },
    { "_subPropertyNames", 0, 0xc },
    { "_subPropertyValues", 0, 0x10 },
    { "_overrideSource", 0, 0x14 },
    { "_overrideSourceSection", 1, 0x18 },
    { "_overrideMode", 6, 0x1c },
    { "_databaseFile", 0, 0x20 },
    { "_databaseFileName", 0, 0x24 },
    { "_rawDatabase", 0, 0x28 },
    { "_currentLine", 1, 0x2c },
    { "_verbose", 2, 0x30 },
    { "_dbIndex", 5, 0x34 },
};
static const dw4_metafield mo_f622[] = {
    { "_header", 11, 0x10 },
    { "_sectionHeaderStringTableSize", 1, 0x44 },
    { "_sectionHeaderStringTable", 11, 0x48 },
    { "_sectionHeaderCount", 1, 0x4c },
    { "_sectionHeaders", 11, 0x50 },
    { "_symbolStringTableSize", 1, 0x54 },
    { "_symbolStringTable", 11, 0x58 },
    { "_symbolCount", 1, 0x5c },
    { "_symbols", 11, 0x60 },
};
static const dw4_metafield mo_f624[] = {
    { "_enbayaAnimationStream", 7, 0x20 },
    { "_interpolationMethod", 255, 0x8 },
    { "_drivenChannels", 8, 0xb },
    { "_playMode", 6, 0xc },
    { "_lastUpdateTimef", 16, 0x10 },
    { "_lastUpdateTime", 12, 0x18 },
};
static const dw4_metafield mo_f625[] = {
    { "_context", 5, 0xa0 },
    { "_fastCacheDecodingState", 2, 0xa4 },
};
static const dw4_metafield mo_f626[] = {
    { "_poolList", 0, 0x8 },
    { "_boneCountList", 0, 0xc },
    { "_freeIndexList", 0, 0x10 },
};
static const dw4_metafield mo_f627[] = {
    { "_trackId", 1, 0x8 },
    { "_enbayaAnimationSource", 0, 0xc },
};
static const dw4_metafield mo_f628[] = {
    { "_num", 1, 0x38 },
};
static const dw4_metafield mo_f629[] = {
    { "_getMetaEnumFunction", 5, 0x34 },
};
static const dw4_metafield mo_f630[] = {
    { "_envMapTexture", 0, 0x20 },
    { "_diffuseTextureBind", 0, 0x24 },
    { "_diffuseTextureCoordIndex", 1, 0x28 },
    { "_reflectionAmount", 16, 0x2c },
    { "_isTransparent", 2, 0x30 },
    { "_glossMapTexture", 0, 0x34 },
    { "_glossTextureCoordIndex", 1, 0x38 },
    { "_configured", 2, 0x3c },
    { "_attrPushLists", 0, 0x40 },
    { "_attrPopLists", 0, 0x44 },
    { "_useRenderPackage", 2, 0x48 },
    { "_discardUnusedImages", 2, 0x49 },
    { "_envMapTextureBind", 0, 0x4c },
    { "_envMapCoordSource", 0, 0x50 },
    { "_envMapTextureFunc", 0, 0x54 },
    { "_diffuseCoordSource", 0, 0x58 },
    { "_diffuseTextureFunc", 0, 0x5c },
    { "_diffuseBlendState", 0, 0x60 },
    { "_glossMapTextureBind", 0, 0x64 },
    { "_glossMapCoordSource", 0, 0x68 },
    { "_glossMapTextureFunc", 0, 0x6c },
};
static const dw4_metafield mo_f633[] = {
    { "_receivers", 0, 0xc },
    { "_controllerManager", 0, 0x10 },
};
static const dw4_metafield mo_f638[] = {
    { "_flags", 1, 0xc },
    { "_eventTypeFilterFlags", 9, 0x10 },
    { "_memoryFieldFilterFlags", 9, 0x14 },
    { "_markerTypeFilterFlags", 9, 0x18 },
    { "_notificationTypeFilterFlags", 9, 0x1c },
    { "_notificationCodeFilterFlags", 9, 0x20 },
    { "_capacity", 1, 0x24 },
    { "_count", 1, 0x28 },
    { "_detachAllocationsCounter", 1, 0x2c },
    { "_names", 0, 0x30 },
    { "_groups", 0, 0x34 },
    { "_classNames", 0, 0x38 },
    { "_memberNames", 0, 0x3c },
    { "_annotations", 0, 0x40 },
    { "_sourceFileNames", 0, 0x44 },
    { "_callStacks", 0, 0x48 },
    { "_locations", 0, 0x4c },
    { "_eventRecords", 0, 0x50 },
    { "_hashIndex", 0, 0x54 },
    { "_codeReferenceAddress", 9, 0x58 },
    { "_callStackTracer", 0, 0x5c },
    { "_eventFormatOffsets", 255, 0x60 },
    { "_defaultMemoryEventFormat", 4, 0xe0 },
    { "_eventTypeNameOffsets", 255, 0xe4 },
    { "_markerTypeNameOffsets", 255, 0x164 },
    { "_notificationTypeNameOffsets", 255, 0x1e4 },
    { "_notificationCodeNameOffsets", 255, 0x224 },
    { "_formatBuffer", 255, 0x324 },
    { "_eventTag", 255, 0x2328 },
    { "_eventTagOffset", 1, 0x2428 },
    { "_eventClassName", 255, 0x242c },
    { "_eventClassNameOffset", 1, 0x252c },
    { "_lock", 0, 0x8 },
};
static const dw4_metafield mo_f642[] = {
    { "_directoryName", 4, 0x1c },
    { "_entryName", 4, 0x20 },
    { "_entryIndex", 1, 0x24 },
    { "_externalFilePath", 4, 0x28 },
};
static const dw4_metafield mo_f644[] = {
    { "_directoryIndex", 1, 0x1c },
    { "_entryIndex", 1, 0x20 },
    { "_entryType", 0, 0x24 },
    { "_entryTypeIndex", 1, 0x28 },
    { "_objectType", 0, 0x2c },
    { "_objectTypeIndex", 1, 0x30 },
};
static const dw4_metafield mo_f645[] = {
    { "_key", 4, 0x1c },
    { "_directoryIndex", 1, 0x20 },
    { "_infoName", 4, 0x24 },
};
static const dw4_metafield mo_f646[] = {
    { "_synchronizer", 0, 0xc },
    { "_field", 0, 0x10 },
};
static const dw4_metafield mo_f648[] = {
    { "_views", 0, 0x8 },
};
static const dw4_metafield mo_f649[] = {
    { "_fileName", 4, 0xc },
    { "_readMode", 6, 0x10 },
    { "_openMode", 6, 0x14 },
    { "_fileHandle", 5, 0x18 },
    { "_optimalReadChunkSize", 1, 0x1c },
    { "_optimalWriteChunkSize", 1, 0x20 },
    { "_pageSize", 1, 0x24 },
    { "_completeFilename", 4, 0x28 },
};
static const dw4_metafield mo_f651[] = {
    { "_file", 0, 0x5c },
};
static const dw4_metafield mo_f652[] = {
    { "_externalEntryList", 0, 0xc },
    { "_infoList", 0, 0x10 },
    { "_fileInfoList", 0, 0x14 },
    { "_cachedFile", 0, 0x18 },
};
static const dw4_metafield mo_f654[] = {
    { "_pathList", 0, 0xc },
};
static const dw4_metafield mo_f656[] = {
    { "_defaultFilters", 0, 0x8 },
    { "_filters", 0, 0xc },
};
static const dw4_metafield mo_f657[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f661[] = {
    { "_value", 16, 0x8 },
};
static const dw4_metafield mo_f663[] = {
    { "_moveDirection", 36, 0x4c },
    { "_joystickT", 36, 0x58 },
    { "_joystickR", 37, 0x64 },
    { "_lastTranslation", 36, 0x6c },
    { "_lastRotation", 37, 0x78 },
    { "_speed", 16, 0x80 },
    { "_aiming", 2, 0x84 },
    { "_window", 0, 0x88 },
    { "_mousePos", 37, 0x8c },
    { "_lastAim", 37, 0x94 },
    { "_lastAimValid", 2, 0x9c },
};
static const dw4_metafield mo_f664[] = {
    { "_mode", 6, 0xc },
    { "_nearVal", 16, 0x10 },
    { "_farVal", 16, 0x14 },
    { "_density", 16, 0x18 },
    { "_color", 38, 0x1c },
};
static const dw4_metafield mo_f665[] = {
    { "_enabled", 2, 0xc },
};
static const dw4_metafield mo_f666[] = {
    { "_folderName", 4, 0x8 },
};
static const dw4_metafield mo_f667[] = {
    { "_height", 16, 0xc },
    { "_baseLine", 16, 0x10 },
    { "_attrList", 0, 0x14 },
    { "_vertexFlags", 9, 0x18 },
};
static const dw4_metafield mo_f668[] = {
    { "_compMat", 40, 0x1dc },
    { "_curMVMat", 5, 0x21c },
    { "_curProjectionMat", 5, 0x220 },
    { "_cd", 0, 0x224 },
    { "_outerFrustCullScale", 16, 0x228 },
    { "_outerScissorWindowScale", 16, 0x22c },
    { "_boundingBox", 0, 0x1d8 },
};
static const dw4_metafield mo_f671[] = {
    { "_renderList", 0, 0x28 },
};
static const dw4_metafield mo_f672[] = {
    { "_vertexArray", 0, 0xc },
    { "_indexArray", 0, 0x10 },
    { "_primType", 6, 0x14 },
    { "_numPrims", 9, 0x18 },
    { "_offset", 9, 0x1c },
    { "_primLengths", 0, 0x20 },
    { "_handle", 1, 0x24 },
    { "_dPds", 0, 0x28 },
    { "_dPdt", 0, 0x2c },
};
static const dw4_metafield mo_f673[] = {
    { "_stripLengths", 0, 0x30 },
};
static const dw4_metafield mo_f675[] = {
    { "_geometry", 0, 0x8 },
    { "_defaultSize", 36, 0xc },
    { "_color", 38, 0x18 },
    { "_sharableAttrs", 0, 0x28 },
};
static const dw4_metafield mo_f677[] = {
    { "_mask", 9, 0xc },
};
static const dw4_metafield mo_f678[] = {
    { "_vc", 0, 0xc },
    { "_renderListHandle", 1, 0x10 },
    { "_geometryAttrList", 0, 0x14 },
    { "_renderListState", 6, 0x18 },
    { "_drawState", 2, 0x1c },
};
static const dw4_metafield mo_f680[] = {
    { "_path", 0, 0x8 },
    { "_center", 36, 0xc },
    { "_length", 16, 0x18 },
};
static const dw4_metafield mo_f682[] = {
    { "_childList", 0, 0x1c },
};
static const dw4_metafield mo_f683[] = {
    { "_controller", 0, 0xc },
    { "_model", 0, 0x10 },
    { "_aspect", 0, 0x14 },
    { "_parent", 0, 0x18 },
    { "_guiSystem", 0, 0x8 },
    { "_node", 0, 0x1c },
    { "_linked", 2, 0x20 },
};
static const dw4_metafield mo_f684[] = {
    { "_node", 0, 0xc },
    { "_minSize", 36, 0x10 },
    { "_maxSize", 36, 0x1c },
};
static const dw4_metafield mo_f687[] = {
    { "_component", 0, 0x20 },
    { "_enabled", 2, 0xc },
    { "_hasFocus", 2, 0xd },
    { "_mouseOver", 2, 0xe },
    { "_pushed", 2, 0xf },
    { "_size", 36, 0x10 },
    { "_childHasFocus", 2, 0x1c },
};
static const dw4_metafield mo_f688[] = {
    { "_component", 0, 0x20 },
};
static const dw4_metafield mo_f689[] = {
    { "_renderer", 0, 0x8 },
    { "_model", 0, 0xc },
    { "_viewList", 0, 0x10 },
    { "_root", 0, 0x14 },
    { "_mouseCursor", 0, 0x18 },
    { "_mouseCursorTransform", 0, 0x1c },
    { "_mouseCursorVisible", 2, 0x20 },
};
static const dw4_metafield mo_f690[] = {
    { "_windowSize", 37, 0xc },
    { "_mousePosition", 37, 0x14 },
    { "_mousePressed", 2, 0x1c },
    { "_viewMatrix", 40, 0x20 },
    { "_projectionMatrix", 40, 0x60 },
    { "_active", 2, 0xa0 },
    { "_rootComponent", 0, 0xa4 },
    { "_focusedComponent", 0, 0xa8 },
    { "_componentUnderMouse", 0, 0xac },
    { "_pushedComponent", 0, 0xb0 },
    { "_windowCloseRequested", 2, 0xb4 },
};
static const dw4_metafield mo_f691[] = {
    { "_root", 0, 0xc },
    { "_model", 0, 0x10 },
    { "_commonTraversal", 0, 0x14 },
    { "_displayListAttr", 0, 0x18 },
};
static const dw4_metafield mo_f692[] = {
    { "_key", 6, 0x8 },
    { "_button", 6, 0xc },
    { "_action", 0, 0x10 },
};
static const dw4_metafield mo_f694[] = {
    { "_hotKeyList", 0, 0x8 },
};
static const dw4_metafield mo_f695[] = {
    { "_magicCookie", 1, 0x60 },
    { "_magicVersion", 1, 0x64 },
    { "_file", 0, 0x68 },
    { "_majorVersion", 1, 0x48 },
    { "_minorVersion", 1, 0x4c },
    { "_hasTemplates", 2, 0x6c },
    { "_entryCount", 1, 0x70 },
    { "_indexBufferSize", 1, 0x74 },
    { "_indexBuffer", 7, 0x78 },
    { "_entryBufferSize", 1, 0x7c },
    { "_metaObjectCount", 1, 0x80 },
    { "_metaObjectBufferSize", 1, 0x84 },
    { "_metaFieldCount", 1, 0x88 },
    { "_metaFieldBufferSize", 1, 0x8c },
    { "_objectCount", 1, 0x90 },
    { "_objectBufferSize", 1, 0x94 },
    { "_memoryRefCount", 1, 0x98 },
    { "_memoryRefBufferSize", 1, 0x9c },
    { "_userLoadFunction", 5, 0xa0 },
    { "_forceChunkSize", 1, 0xa4 },
    { "_endianSwap", 2, 0xa8 },
    { "_metaObjectBuffer", 7, 0xac },
    { "_dirBuf", 7, 0xb0 },
    { "_objBuf", 7, 0xb4 },
    { "_mfBuf", 7, 0xb8 },
    { "_metaFieldListInFile", 0, 0xbc },
    { "_metaObjectListInFile", 0, 0xc0 },
    { "_autoOpened", 1, 0xc4 },
    { "_basePath", 7, 0xc8 },
    { "imf", 0, 0xcc },
    { "smf", 0, 0xd0 },
    { "_hasInfo", 2, 0xd4 },
    { "_hasExternal", 2, 0xd5 },
    { "_sharedEntries", 2, 0xd6 },
    { "_hasVersion1Cruft", 2, 0xd7 },
    { "_version1CruftMultiply", 1, 0xd8 },
    { "_infoListPlace", 1, 0xdc },
    { "_externalDirectoryBuffer", 7, 0xe0 },
    { "_externalDirectoryBufferSize", 1, 0xe4 },
    { "_previousResourceFilePath", 4, 0xe8 },
    { "_alignmentBuffer", 7, 0xec },
    { "_alignmentBufferSize", 1, 0xf0 },
    { "_alignmentListInFile", 0, 0xf4 },
    { "_alignmentCount", 1, 0xf8 },
    { "_objectBufferPlace", 7, 0xfc },
    { "_memoryBufferPlace", 1, 0x100 },
    { "_chunkSize", 1, 0x104 },
    { "_chunk", 7, 0x108 },
    { "_chunkPlace", 1, 0x50 },
    { "_bufferPlace", 1, 0x54 },
    { "_bufferSize", 1, 0x58 },
    { "_memoryBytesCopied", 1, 0x10c },
    { "_bytesRemainingInChunk", 1, 0x110 },
    { "_hasCriticalFailure", 2, 0x114 },
    { "_autoReadFilePostProcessState", 2, 0x115 },
    { "_autoWriteFilePostProcessState", 2, 0x116 },
    { "_readFilePostProcessedState", 2, 0x117 },
    { "_temporaryMemoryPool", 0, 0x118 },
    { "_dataMemoryPool", 0, 0x11c },
    { "_objectMemoryPool", 0, 0x120 },
    { "_entryPool", 0, 0x5c },
    { "_hasMemoryPoolNames", 2, 0x124 },
    { "_memoryPoolNameBufferSize", 1, 0x128 },
    { "_memoryPoolNameBuffer", 7, 0x12c },
    { "_memoryPoolHandles", 0, 0x130 },
};
static const dw4_metafield mo_f696[] = {
    { "_px", 9, 0x8 },
    { "_py", 9, 0xc },
    { "_pz", 9, 0x10 },
    { "_ps", 9, 0x14 },
    { "_order", 9, 0x18 },
    { "_bitsRed", 9, 0x1c },
    { "_bitsGrn", 9, 0x20 },
    { "_bitsBlu", 9, 0x24 },
    { "_bitsAlpha", 9, 0x28 },
    { "_pfmt", 6, 0x2c },
    { "_imageSize", 1, 0x30 },
    { "_pImage", 7, 0x34 },
    { "_pName", 7, 0x38 },
    { "_localImage", 2, 0x3c },
    { "_bitsInt", 9, 0x40 },
    { "_pClut", 0, 0x44 },
    { "_bitsIdx", 9, 0x48 },
    { "_bytesPerRow", 1, 0x4c },
    { "_compressed", 2, 0x50 },
    { "_bitsDepth", 9, 0x54 },
    { "_pNameString", 4, 0x58 },
};
static const dw4_metafield mo_f701[] = {
    { "_indexData", 7, 0xc },
    { "_numIndices", 9, 0x10 },
    { "_dataSize", 6, 0x14 },
    { "_usageFlags", 9, 0x18 },
    { "_memPool", 0, 0x8 },
};
static const dw4_metafield mo_f702[] = {
    { "_directory", 0, 0xc },
    { "_resolveState", 2, 0x10 },
};
static const dw4_metafield mo_f704[] = {
    { "_insight", 0, 0xc },
};
static const dw4_metafield mo_f707[] = {
    { "_implementationName", 4, 0x18 },
    { "_fileCache", 0, 0x38 },
    { "_implementation", 0, 0x1c },
    { "_interface", 0, 0x20 },
    { "_interfaceFileName", 4, 0x24 },
    { "_interfaceSection", 1, 0x28 },
    { "_mp", 0, 0x2c },
    { "_data", 0, 0x30 },
    { "_cachedObjects", 0, 0x34 },
};
static const dw4_metafield mo_f708[] = {
    { "_managerList", 0, 0x8 },
    { "_scheduler", 0, 0xc },
    { "_infoList", 0, 0x10 },
    { "_window", 0, 0x14 },
    { "_visualContext", 0, 0x18 },
    { "_rendererList", 0, 0x1c },
    { "_dispatcher", 0, 0x20 },
    { "_windowResizeReceiver", 0, 0x24 },
    { "_messenger", 0, 0x28 },
    { "_clearRenderer", 0, 0x2c },
    { "_timer", 0, 0x30 },
    { "_frames", 1, 0x34 },
    { "_currentTime", 12, 0x38 },
    { "_frameTime", 12, 0x40 },
    { "_currentToWorldTimeFactor", 1, 0x48 },
    { "_worldTime", 12, 0x50 },
    { "_traversalTime", 12, 0x58 },
    { "_outputTime", 12, 0x60 },
    { "_plugins", 0, 0x68 },
};
static const dw4_metafield mo_f712[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f717[] = {
    { "_value", 1, 0x8 },
};
static const dw4_metafield mo_f719[] = {
    { "_devices", 0, 0x8 },
};
static const dw4_metafield mo_f720[] = {
    { "_optInterface", 0, 0x8 },
    { "_itemInterface", 0, 0xc },
    { "_listenerInterface", 0, 0x10 },
    { "_messageInterface", 0, 0x14 },
    { "_lockInterface", 0, 0x18 },
    { "_logInterface", 0, 0x1c },
};
static const dw4_metafield mo_f721[] = {
    { "_factory", 0, 0x18 },
    { "_objectMappings", 0, 0x1c },
};
static const dw4_metafield mo_f722[] = {
    { "_matStack", 0, 0x20 },
    { "_nodeStack", 0, 0x24 },
    { "_probe", 0, 0x28 },
    { "_mode", 1, 0x2c },
    { "_hitProc", 5, 0x30 },
    { "_volumes", 0, 0x34 },
    { "_ray", 0, 0x38 },
};
static const dw4_metafield mo_f728[] = {
    { "_itemDataBaseList", 0, 0x20 },
    { "_metaList", 0, 0x24 },
    { "_itemList", 0, 0x28 },
    { "_itemNameList", 0, 0x2c },
    { "_currentKnownItem", 9, 0x30 },
};
static const dw4_metafield mo_f729[] = {
    { "_iterated", 0, 0x8 },
    { "_current", 1, 0xc },
};
static const dw4_metafield mo_f730[] = {
    { "_iterated", 0, 0x8 },
    { "_current", 1, 0xc },
};
static const dw4_metafield mo_f731[] = {
    { "_currentPath", 0, 0xc },
    { "_currentIndices", 0, 0x10 },
    { "_actorSkinIterationState", 2, 0x8 },
};
static const dw4_metafield mo_f733[] = {
    { "_registerFunction", 5, 0x8 },
};
static const dw4_metafield mo_f736[] = {
    { "_lightType", 6, 0xc },
    { "_lightId", 1, 0x10 },
    { "_position", 36, 0x14 },
    { "_ambient", 38, 0x20 },
    { "_diffuse", 38, 0x30 },
    { "_specular", 38, 0x40 },
    { "_direction", 36, 0x50 },
    { "_falloff", 16, 0x5c },
    { "_cutoff", 16, 0x60 },
    { "_attenuation", 36, 0x64 },
    { "_shininess", 16, 0x70 },
    { "_cachedPosition", 36, 0x74 },
    { "_cachedDirection", 36, 0x80 },
    { "_vc", 0, 0x8c },
    { "_changed", 2, 0x90 },
    { "_cacheable", 2, 0x91 },
};
static const dw4_metafield mo_f738[] = {
    { "_lights", 0, 0x1c },
};
static const dw4_metafield mo_f740[] = {
    { "_light", 0, 0x10 },
    { "_enabled", 2, 0x14 },
    { "_internal", 0, 0xc },
};
static const dw4_metafield mo_f743[] = {
    { "_lightEnables", 0, 0x20 },
};
static const dw4_metafield mo_f744[] = {
    { "_enabled", 2, 0xc },
};
static const dw4_metafield mo_f745[] = {
    { "_fWidth", 16, 0x14 },
};
static const dw4_metafield mo_f747[] = {
    { "_instances", 0, 0x20 },
    { "_instancesListener", 0, 0x24 },
    { "_types", 0, 0x28 },
    { "_typesListener", 0, 0x2c },
};
static const dw4_metafield mo_f750[] = {
    { "_capacity", 1, 0x8 },
    { "_hashCapacity", 1, 0xc },
    { "_locations", 0, 0x10 },
    { "_hashIndex", 0, 0x14 },
    { "_symbolNames", 0, 0x18 },
    { "_sourceFileNames", 0, 0x1c },
};
static const dw4_metafield mo_f752[] = {
    { "_objectCacheNames", 0, 0x20 },
    { "_objectCacheValids", 0, 0x24 },
    { "_objectCacheLists", 0, 0x28 },
};
static const dw4_metafield mo_f753[] = {
    { "_rangeList", 0, 0x20 },
    { "_lastRange", 0, 0x24 },
    { "_lastIndex", 1, 0x28 },
    { "_lastLower", 16, 0x2c },
    { "_lastUpper", 16, 0x30 },
    { "_center", 36, 0x34 },
    { "_hysteresisList", 0, 0x40 },
};
static const dw4_metafield mo_f754[] = {
    { "_verbose", 2, 0x20 },
};
static const dw4_metafield mo_f755[] = {
    { "_time", 12, 0x10 },
    { "_geometryAttr", 0, 0x18 },
    { "_colorAttr", 0, 0x1c },
    { "_attrList", 0, 0x20 },
};
static const dw4_metafield mo_f756[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f760[] = {
    { "_startTime", 12, 0x8 },
    { "_additionalTime", 12, 0x10 },
    { "_resetTime", 12, 0x18 },
    { "_isStopped", 2, 0x20 },
};
static const dw4_metafield mo_f762[] = {
    { "_luaState", 5, 0xc },
    { "_memPool", 0, 0x10 },
};
static const dw4_metafield mo_f763[] = {
    { "_poolIndex", 1, 0x78 },
    { "_elementSize", 9, 0x7c },
    { "_maxSize", 13, 0x80 },
    { "_size", 13, 0x88 },
    { "_alignment", 10, 0x90 },
    { "_eventTracker", 0, 0x94 },
    { "_isActive", 2, 0x70 },
    { "_allocationLock", 0, 0x74 },
    { "_messageLevel", 6, 0x98 },
    { "_poolOptionFlags", 1, 0x9c },
};
static const dw4_metafield mo_f764[] = {
    { "_shininess", 16, 0xc },
    { "_diffuse", 38, 0x10 },
    { "_ambient", 38, 0x20 },
    { "_emission", 38, 0x30 },
    { "_specular", 38, 0x40 },
    { "_flags", 9, 0x50 },
};
static const dw4_metafield mo_f767[] = {
    { "_m", 40, 0x8 },
};
static const dw4_metafield mo_f770[] = {
    { "_enabled", 2, 0xc },
};
static const dw4_metafield mo_f773[] = {
    { "_isBinary", 2, 0x2c },
    { "_isOpen", 2, 0x2d },
    { "_write", 2, 0x2e },
    { "_read", 2, 0x2f },
    { "_bufSize", 1, 0x30 },
    { "_fileSize", 1, 0x34 },
    { "_bufPos", 1, 0x38 },
    { "_fBuf", 7, 0x3c },
    { "_media", 0, 0x40 },
};
static const dw4_metafield mo_f776[] = {
    { "_capacity", 1, 0x8 },
    { "_count", 1, 0xc },
    { "_memoryEntries", 0, 0x10 },
    { "_cachedIndex", 1, 0x14 },
};
static const dw4_metafield mo_f777[] = {
    { "_memSize", 1, 0x1c },
    { "_memTypeSize", 1, 0x20 },
    { "_memType", 0, 0x24 },
    { "_memTypeIndex", 1, 0x28 },
    { "_refCounted", 2, 0x34 },
    { "_alignmentTypeIndex", 1, 0x2c },
    { "_memoryPoolHandle", 1, 0x30 },
};
static const dw4_metafield mo_f778[] = {
    { "_bIsOpen", 2, 0x2c },
    { "_buffer", 5, 0x30 },
    { "_iBufferSize", 1, 0x34 },
    { "_iSeekPosition", 1, 0x38 },
};
static const dw4_metafield mo_f779[] = {
    { "_buffer", 5, 0xc },
    { "_size", 9, 0x10 },
};
static const dw4_metafield mo_f782[] = {
    { "_localAllocated", 12, 0x8 },
    { "_localFreed", 12, 0x10 },
    { "_localNetAllocated", 12, 0x18 },
    { "_localNetAllocatedHigh", 12, 0x20 },
    { "_localAllocatedWithOverhead", 12, 0x28 },
    { "_localFreedWithOverhead", 12, 0x30 },
    { "_localNetAllocatedWithOverhead", 12, 0x38 },
    { "_localNetAllocatedWithOverheadHigh", 12, 0x40 },
    { "_localAllocationCount", 12, 0x48 },
    { "_localFreeCount", 12, 0x50 },
    { "_localNetAllocationCount", 12, 0x58 },
    { "_localNetAllocationCountHigh", 12, 0x60 },
    { "_updateStatistics", 2, 0x68 },
    { "_updateGlobalStatistics", 2, 0x69 },
};
static const dw4_metafield mo_f783[] = {
    { "_memoryPoolInfos", 0, 0x14 },
};
static const dw4_metafield mo_f784[] = {
    { "_handleName", 4, 0x14 },
    { "_aliasedTo", 4, 0x18 },
    { "_size", 1, 0x1c },
    { "_maxSize", 1, 0x20 },
    { "_address", 1, 0x24 },
    { "_class", 4, 0x28 },
    { "_arenaType", 4, 0x2c },
    { "_source", 4, 0x30 },
    { "_scope", 4, 0x34 },
    { "_debugOptions", 4, 0x38 },
    { "_releaseOptions", 4, 0x3c },
    { "_debugChecking", 4, 0x40 },
    { "_releaseChecking", 4, 0x44 },
    { "_debugMessages", 4, 0x48 },
    { "_releaseMessages", 4, 0x4c },
    { "_eventTrackerCapacity", 1, 0x50 },
};
static const dw4_metafield mo_f786[] = {
    { "_num", 1, 0x50 },
};
static const dw4_metafield mo_f787[] = {
    { "_memSize", 1, 0x38 },
    { "_memType", 0, 0x3c },
    { "_releaseOnCopy", 2, 0x40 },
    { "_releaseOnReset", 2, 0x41 },
    { "_refCounted", 2, 0x42 },
    { "_alignmentType", 1, 0x44 },
    { "_memTypeRef", 0, 0x48 },
    { "_poolName", 4, 0x4c },
};
static const dw4_metafield mo_f788[] = {
    { "_mti", 1, 0x8 },
    { "_mt", 255, 0xc },
};
static const dw4_metafield mo_f791[] = {
    { "_msgHandler", 0, 0x8 },
    { "_msgHandlerFunc", 11, 0xc },
};
static const dw4_metafield mo_f793[] = {
    { "_msgType", 0, 0x8 },
    { "_receivers", 0, 0xc },
};
static const dw4_metafield mo_f795[] = {
    { "_messages", 0, 0x20 },
};
static const dw4_metafield mo_f799[] = {
    { "_dispatcher", 0, 0x8 },
};
static const dw4_metafield mo_f800[] = {
    { "_name", 4, 0x8 },
    { "_names", 0, 0xc },
    { "_values", 0, 0x10 },
};
static const dw4_metafield mo_f801[] = {
    { "_offset", 1, 0x8 },
    { "_fieldName", 4, 0xc },
    { "_typeIndex", 17, 0x10 },
    { "_internalIndex", 17, 0x12 },
    { "_size", 10, 0x14 },
    { "_parentMetaObject", 0, 0x18 },
    { "_externalEnumStorage", 5, 0x1c },
    { "_default", 7, 0x20 },
    { "_resetMethod", 3, 0x24 },
    { "_isRunTime", 2, 0x25 },
    { "_persistent", 2, 0x26 },
    { "_shallowCopyMethod", 3, 0x27 },
    { "_deepCopyMethod", 3, 0x28 },
    { "_constructCopyMethod", 3, 0x29 },
    { "_isAlikeExactlyMethod", 3, 0x2a },
    { "_isAlikeDeepMethod", 3, 0x2b },
    { "_isAlikeShallowMethod", 3, 0x2c },
    { "_invarianceFunction", 5, 0x30 },
};
static const dw4_metafield mo_f804[] = {
    { "_id", 1, 0x8 },
    { "_index", 1, 0xc },
    { "_majorVersion", 1, 0x10 },
    { "_minorVersion", 1, 0x14 },
    { "_volatile", 2, 0x18 },
    { "_persistent", 2, 0x19 },
    { "_abstractState", 2, 0x1a },
    { "_name", 4, 0x1c },
    { "_runTimeSize", 1, 0x20 },
    { "_validity", 1, 0x24 },
    { "_metaFields", 0, 0x28 },
    { "_instanceCount", 1, 0x2c },
    { "_instances", 0, 0x30 },
    { "_children", 0, 0x34 },
    { "_parent", 0, 0x38 },
    { "_abstractProxy", 5, 0x3c },
    { "_writeProxy", 5, 0x40 },
    { "_templateObject", 0, 0x44 },
    { "_sizeofSize", 1, 0x48 },
    { "_setupFunction", 5, 0x4c },
    { "_cleanupFunction", 5, 0x50 },
    { "_getMetaObjectFunction", 5, 0x54 },
    { "_requiredAlignment", 10, 0x58 },
    { "_vTablePointer", 5, 0x5c },
    { "_poolName", 4, 0x60 },
};
static const dw4_metafield mo_f807[] = {
    { "_views", 0, 0x8 },
};
static const dw4_metafield mo_f808[] = {
    { "_m", 40, 0xc },
};
static const dw4_metafield mo_f811[] = {
    { "_matrixIndex", 1, 0x20 },
};
static const dw4_metafield mo_f813[] = {
    { "_geometryElement", 0, 0x8 },
    { "_offset", 37, 0xc },
};
static const dw4_metafield mo_f814[] = {
    { "_guiSystem", 0, 0xc },
    { "_intersectTraversal", 0, 0x10 },
    { "_ray", 0, 0x14 },
    { "_impactLength", 16, 0x18 },
    { "_hit", 2, 0x1c },
    { "_hitPath", 0, 0x20 },
    { "_inverseProjectionMatrix", 40, 0x24 },
};
static const dw4_metafield mo_f817[] = {
    { "_path", 4, 0x14 },
    { "_type", 6, 0x18 },
    { "_loop", 2, 0x1c },
    { "_width", 1, 0x20 },
    { "_height", 1, 0x24 },
    { "_audioChannel", 1, 0x28 },
    { "_audioVolume", 1, 0x2c },
    { "_videoTextures", 0, 0x30 },
    { "_minificationFilter", 6, 0x34 },
    { "_magnificationFilter", 6, 0x38 },
    { "_tileWidth", 1, 0x3c },
    { "_tileHeight", 1, 0x40 },
    { "_codecType", 4, 0x44 },
    { "_codec", 0, 0x48 },
    { "_state", 6, 0x4c },
    { "_sceneInfo", 0, 0x50 },
    { "_runtimeImage", 0, 0x54 },
    { "_runtimeTextures", 0, 0x58 },
    { "_imageFormat", 6, 0x5c },
    { "_userdata", 0, 0x60 },
    { "_bitrate", 1, 0x64 },
};
static const dw4_metafield mo_f819[] = {
    { "_movieList", 0, 0x10 },
    { "_audioDisabled", 2, 0x14 },
    { "_audio", 0, 0x18 },
    { "_codecList", 0, 0x1c },
    { "_movieRenderer", 0, 0x20 },
    { "_rendererList", 0, 0x24 },
};
static const dw4_metafield mo_f820[] = {
    { "_movieManager", 0, 0x8 },
};
static const dw4_metafield mo_f821[] = {
    { "_movieManager", 0, 0xc },
};
static const dw4_metafield mo_f822[] = {
    { "_numPasses", 1, 0xc },
};
static const dw4_metafield mo_f824[] = {
    { "_name", 4, 0x8 },
};
static const dw4_metafield mo_f825[] = {
    { "_objects", 0, 0x14 },
};
static const dw4_metafield mo_f827[] = {
    { "_bound", 0, 0xc },
    { "_parentList", 0, 0x10 },
    { "_flags", 1, 0x14 },
    { "_handle", 1, 0x18 },
};
static const dw4_metafield mo_f839[] = {
    { "_enabled", 2, 0xc },
};
static const dw4_metafield mo_f840[] = {
    { "_parameters", 0, 0xc },
    { "_attrList", 0, 0x10 },
    { "_defaultAttrList", 0, 0x14 },
    { "_modelViewAttr", 0, 0x18 },
    { "_colorAttr", 0, 0x1c },
    { "_normals", 0, 0x20 },
    { "_invalidStoredNormals", 2, 0x24 },
    { "_path", 0, 0x28 },
    { "_draw", 2, 0x2c },
};
static const dw4_metafield mo_f842[] = {
    { "_typeMeta", 0, 0x1c },
    { "_typeMetaName", 4, 0x20 },
    { "_majorVersion", 1, 0x24 },
    { "_minorVersion", 1, 0x28 },
    { "_typeMetaIndex", 1, 0x30 },
    { "_memoryPoolHandle", 1, 0x2c },
};
static const dw4_metafield mo_f845[] = {
    { "_freeIndex", 1, 0x14 },
    { "_capabilityIncrease", 1, 0x18 },
    { "_resetMode", 2, 0x1c },
};
static const dw4_metafield mo_f846[] = {
    { "_num", 1, 0x44 },
};
static const dw4_metafield mo_f847[] = {
    { "_metaObject", 0, 0x38 },
    { "_refCounted", 2, 0x3c },
    { "_poolName", 4, 0x40 },
};
static const dw4_metafield mo_f848[] = {
    { "_names", 0, 0x8 },
    { "_data", 0, 0xc },
};
static const dw4_metafield mo_f850[] = {
    { "_value", 2, 0x24 },
};
static const dw4_metafield mo_f851[] = {
    { "_group", 0, 0xc },
};
static const dw4_metafield mo_f853[] = {
    { "_registry", 0, 0x20 },
    { "_configuration", 0, 0x24 },
};
static const dw4_metafield mo_f855[] = {
    { "_optimizationList", 0, 0x20 },
    { "_filePath", 4, 0x24 },
    { "_file", 0, 0x28 },
    { "_disabledInfos", 0, 0x2c },
};
static const dw4_metafield mo_f857[] = {
    { "_maxSize", 13, 0x78 },
    { "_eventTracker", 0, 0x80 },
    { "_isActive", 2, 0x70 },
    { "_allocationLock", 0, 0x74 },
    { "_poolIndex", 1, 0x84 },
    { "_messageLevel", 6, 0x88 },
    { "_poolOptionFlags", 1, 0x8c },
};
static const dw4_metafield mo_f858[] = {
    { "_particleFormat", 0, 0x8 },
    { "_maxNum", 9, 0xc },
    { "_arrayIndex", 9, 0x10 },
    { "_particleLifeStart", 16, 0x14 },
    { "_particleLifeEnd", 16, 0x18 },
    { "_currentTime", 16, 0x1c },
    { "_particleDataSize", 9, 0x20 },
    { "_particleArray", 7, 0x24 },
    { "_internalVertexArray", 0, 0x28 },
    { "_context", 0, 0x2c },
    { "_pointSpriteInterface", 0, 0x30 },
    { "_particleOffset", 9, 0x34 },
    { "_particleNum", 9, 0x38 },
    { "_primLengthArrayNum", 1, 0x3c },
    { "_primLengthArrayOffset", 1, 0x40 },
    { "_primLengthArray", 0, 0x44 },
    { "_setConstant", 2, 0x48 },
    { "_configured", 2, 0x49 },
    { "_updateFunction", 5, 0x4c },
    { "_timeControlState", 6, 0x50 },
    { "_particleLifetimeEndOffset", 16, 0x54 },
    { "_aliveParticleNum", 9, 0x58 },
};
static const dw4_metafield mo_f859[] = {
    { "_bUseCurrentTime", 2, 0xc },
    { "_particleArray", 0, 0x10 },
    { "_particleNum", 9, 0x14 },
    { "_particleOffset", 9, 0x18 },
    { "_startTime", 12, 0x20 },
    { "_time", 16, 0x28 },
    { "_offset", 16, 0x2c },
};
static const dw4_metafield mo_f860[] = {
    { "_position", 6, 0x8 },
    { "_color", 6, 0xc },
    { "_width", 6, 0x10 },
    { "_height", 6, 0x14 },
    { "_textureCoord", 6, 0x18 },
    { "_primType", 6, 0x1c },
    { "_spriteType", 6, 0x20 },
    { "_spriteSpace", 6, 0x24 },
    { "_rotation", 6, 0x28 },
    { "_lifetime", 6, 0x2c },
};
static const dw4_metafield mo_f861[] = {
    { "_parameters", 0, 0x4c },
    { "_guiSystem", 0, 0x50 },
    { "_cursor", 0, 0x54 },
    { "_savedCursor", 0, 0x58 },
    { "_savedCursorState", 2, 0x5c },
    { "_intersectTraversal", 0, 0x60 },
    { "_ray", 0, 0x64 },
    { "_impactLength", 16, 0x68 },
    { "_hit", 2, 0x6c },
    { "_hitPath", 0, 0x70 },
    { "_inverseProjectionMatrix", 40, 0x74 },
    { "_joystickT", 37, 0xb4 },
};
static const dw4_metafield mo_f862[] = {
    { "_pipelineMode", 6, 0xc },
};
static const dw4_metafield mo_f863[] = {
    { "_lights", 0, 0x28 },
    { "_mvmList", 0, 0x2c },
    { "_shadowPlane", 38, 0x30 },
    { "_shadowColor", 38, 0x40 },
    { "_shadowUseBlend", 2, 0x6c },
    { "_shadowUseStencil", 2, 0x6d },
    { "_mats", 0, 0x50 },
    { "_geoms", 0, 0x54 },
    { "_blendmats", 0, 0x58 },
    { "_savedBounds", 0, 0x5c },
    { "_unused", 0, 0x60 },
    { "_shadowColorAttr", 0, 0x64 },
    { "_stencilState", 0, 0x68 },
};
static const dw4_metafield mo_f864[] = {
    { "_norm", 36, 0x8 },
    { "_offset", 16, 0x14 },
    { "_octant", 6, 0x18 },
};
static const dw4_metafield mo_f865[] = {
    { "_pluginExtension", 4, 0x8 },
    { "_repositoryList", 0, 0xc },
    { "_libraryLoader", 0, 0x10 },
    { "_loadedPlugins", 0, 0x14 },
};
static const dw4_metafield mo_f866[] = {
    { "_location", 4, 0xc },
    { "_locationType", 6, 0x10 },
};
static const dw4_metafield mo_f868[] = {
    { "_context", 0, 0x14 },
    { "_vertexArray", 0, 0x18 },
    { "_spriteSize", 16, 0x1c },
    { "_inSpriteMode", 2, 0x20 },
    { "_spriteSizeSpace", 6, 0x24 },
    { "_previousModelview", 40, 0x28 },
    { "_previousProjection", 40, 0x68 },
    { "_orthoMatrix", 40, 0xa8 },
    { "_modelviewMatrix", 40, 0xe8 },
    { "_modelviewMatrixFrustum", 40, 0x128 },
    { "_currentWindowWidth", 1, 0x168 },
    { "_currentWindowHeight", 1, 0x16c },
    { "_frustumLeft", 16, 0x170 },
    { "_frustumRight", 16, 0x174 },
    { "_frustumBottom", 16, 0x178 },
    { "_frustumTop", 16, 0x17c },
    { "_frustumNear", 16, 0x180 },
    { "_frustumFar", 16, 0x184 },
};
static const dw4_metafield mo_f871[] = {
    { "_mode", 6, 0xc },
};
static const dw4_metafield mo_f872[] = {
    { "_lengthData", 7, 0x8 },
    { "_numStrips", 9, 0xc },
    { "_dataSize", 9, 0x10 },
};
static const dw4_metafield mo_f874[] = {
    { "_volume", 0, 0x8 },
    { "_rays", 0, 0xc },
    { "_intersectFaceType", 0, 0x10 },
};
static const dw4_metafield mo_f875[] = {
    { "_fileName", 4, 0x8 },
    { "_file", 0, 0xc },
};
static const dw4_metafield mo_f876[] = {
    { "_m", 40, 0xc },
};
static const dw4_metafield mo_f878[] = {
    { "_lightPos", 36, 0x20 },
    { "_lightDir", 36, 0x2c },
    { "_cutoff", 16, 0x38 },
    { "_shadowCasters", 0, 0x3c },
    { "_shadowReceivers", 0, 0x40 },
    { "_shadowFactor", 16, 0x44 },
    { "_shadowTexW", 1, 0x48 },
    { "_shadowTexH", 1, 0x4c },
    { "_shadowLightness", 16, 0x50 },
    { "_viewToProjectedLightTextureMatrixpAttrList", 0, 0x54 },
    { "_lightMVMAttr", 0, 0x58 },
    { "_lightProjAttr", 0, 0x5c },
    { "_blurMVMAttr", 0, 0x60 },
    { "_blurProjAttr", 0, 0x64 },
    { "_inited", 1, 0x68 },
    { "_quadsGeom", 0, 0x6c },
    { "_unused", 0, 0x70 },
    { "_shadowColor", 0, 0x74 },
    { "_blurState", 2, 0x78 },
    { "_zNear", 16, 0x7c },
    { "_zFar", 16, 0x80 },
    { "_upVector", 36, 0x84 },
    { "_viewToProjectedLightTextureMatrix", 0, 0x90 },
    { "_drawReceiver", 2, 0x94 },
    { "_updateShadowMap", 2, 0x95 },
    { "_pShadowTexRD", 0, 0x98 },
    { "_pSetShadowTexRD", 0, 0x9c },
    { "_pShadowTex", 0, 0xa0 },
    { "_pShadowTexBind", 0, 0xa4 },
    { "_pBlurTexRD", 0, 0xa8 },
    { "_pSetBlurTexRD", 0, 0xac },
    { "_pBlurTex", 0, 0xb0 },
    { "_pBlurTexBind", 0, 0xb4 },
    { "_shadowCopyBack", 0, 0xb8 },
    { "_shadowCopyBackImage", 0, 0xbc },
    { "_shadowViewport", 0, 0xc0 },
    { "_shadowInnerViewport", 0, 0xc4 },
    { "_light", 0, 0xc8 },
    { "_pShadowTexBind1", 0, 0xcc },
    { "_useOrthographic", 2, 0xd0 },
    { "_top", 16, 0xd4 },
    { "_bottom", 16, 0xd8 },
    { "_right", 16, 0xdc },
    { "_left", 16, 0xe0 },
    { "_unloadShadowTexRD", 0, 0xe4 },
    { "_unloadBlurTexRD", 0, 0xe8 },
    { "_releaseRenderDestinationAfterDraw", 2, 0xec },
    { "_useShadowFactor", 2, 0xed },
};
static const dw4_metafield mo_f879[] = {
    { "_connection", 0, 0xc },
    { "_streamingThread", 0, 0x10 },
    { "_window", 0, 0x14 },
    { "_sdInitValue", 9, 0x18 },
    { "_callBackForSetSourceDataASync", 5, 0x1c },
    { "_maxWavCount", 9, 0x20 },
    { "_maxVagCount", 9, 0x24 },
    { "_batchMemory", 7, 0x28 },
    { "_batchOffset", 1, 0x2c },
    { "_lastRequestID", 0, 0x30 },
};
static const dw4_metafield mo_f881[] = {
    { "_context", 0, 0x18 },
    { "_blendA", 1, 0x1c },
    { "_blendB", 1, 0x20 },
    { "_blendC", 1, 0x24 },
    { "_blendD", 1, 0x28 },
    { "_blendConstant", 3, 0x2c },
};
static const dw4_metafield mo_f883[] = {
    { "_id", 1, 0x20 },
    { "_refCount", 1, 0x24 },
};
static const dw4_metafield mo_f884[] = {
    { "_id", 10, 0x10 },
    { "_curr_id", 10, 0x12 },
    { "_term_id", 10, 0x14 },
    { "_buttonCount", 1, 0x18 },
    { "_joyCount", 10, 0x1c },
    { "_attachedWindow", 0, 0x20 },
    { "_x", 255, 0x24 },
    { "_y", 255, 0x2c },
    { "_connected", 2, 0x34 },
    { "_type", 6, 0x38 },
    { "_slot", 1, 0x3c },
    { "_port", 1, 0x40 },
    { "_buttonState", 10, 0x44 },
    { "_dmaBuffer", 5, 0x48 },
    { "_oldJoyX", 255, 0x4c },
    { "_oldJoyY", 255, 0x4e },
    { "_analogState", 2, 0x50 },
    { "_lockState", 2, 0x51 },
    { "_usePressure", 2, 0x52 },
    { "_hasPressure", 2, 0x53 },
    { "_phase", 6, 0x54 },
    { "_reseting", 2, 0x58 },
    { "_userReset", 2, 0x59 },
    { "_userResetAnalogOnly", 2, 0x5a },
};
static const dw4_metafield mo_f885[] = {
    { "_multitap", 6, 0xc },
    { "_validControllerManager", 2, 0x10 },
    { "_loadIRXs", 2, 0x11 },
};
static const dw4_metafield mo_f886[] = {
    { "_context", 0, 0x18 },
    { "_offsetUnits", 9, 0x1c },
};
static const dw4_metafield mo_f887[] = {
    { "_context", 0, 0x14 },
};
static const dw4_metafield mo_f888[] = {
    { "_envMapBlendFunc", 0, 0x70 },
    { "_envMapTexGenMatrix", 0, 0x74 },
    { "_multiPassEnable", 0, 0x78 },
};
static const dw4_metafield mo_f889[] = {
    { "_fBuf", 7, 0x2c },
    { "_bufSize", 1, 0x30 },
    { "_bufPos", 1, 0x34 },
    { "_fileSize", 1, 0x38 },
    { "_isBinary", 1, 0x3c },
    { "_isOpen", 1, 0x40 },
    { "_stringFile", 5, 0x44 },
    { "_prefix", 4, 0x48 },
};
static const dw4_metafield mo_f894[] = {
    { "_sifData", 5, 0x8 },
    { "_dataMemory", 5, 0xc },
    { "_sema", 1, 0x10 },
};
static const dw4_metafield mo_f897[] = {
    { "_headAndTailBuffer", 7, 0x8 },
    { "_connection", 0, 0xc },
    { "_sema", 0, 0x10 },
    { "_commandBuffer", 7, 0x14 },
    { "_writeBuffer", 7, 0x18 },
    { "_handlePool", 5, 0x1c },
    { "_conversionString", 0, 0x20 },
    { "_initialized", 2, 0x24 },
};
static const dw4_metafield mo_f898[] = {
    { "_context", 0, 0x14 },
    { "_blendFunction", 6, 0x18 },
    { "_blendingState", 2, 0x1c },
    { "_blendA", 6, 0x20 },
    { "_blendB", 6, 0x24 },
    { "_blendC", 6, 0x28 },
    { "_blendD", 6, 0x2c },
    { "_blendFIX", 8, 0x30 },
};
static const dw4_metafield mo_f899[] = {
    { "_hardwareSupport", 2, 0x5c },
    { "_currentEditIndex", 9, 0x60 },
    { "_ps2ParticleFormat", 5, 0x64 },
    { "_bSynchronize", 2, 0x68 },
    { "_lSequence", 12, 0x70 },
};
static const dw4_metafield mo_f900[] = {
    { "_context", 0, 0x188 },
};
static const dw4_metafield mo_f901[] = {
    { "_context", 0, 0x14 },
    { "_scissorEnable", 2, 0x18 },
    { "_scissorOrgX", 1, 0x1c },
    { "_scissorOrgY", 1, 0x20 },
    { "_scissorWidth", 1, 0x24 },
    { "_scissorHeight", 1, 0x28 },
};
static const dw4_metafield mo_f902[] = {
    { "_semaID", 1, 0xc },
    { "_initCount", 9, 0x10 },
    { "_maxCount", 9, 0x14 },
};
static const dw4_metafield mo_f903[] = {
    { "_threadID", 1, 0x3c },
    { "_threadDoneSema", 0, 0x30 },
    { "_result", 5, 0x34 },
    { "_isDeferred", 2, 0x38 },
    { "_stopRequested", 2, 0x39 },
    { "_atStoppingPoint", 2, 0x3a },
};
static const dw4_metafield mo_f905[] = {
    { "_context", 0, 0x14 },
    { "_currentDListHandle", 0, 0x18 },
    { "_pDLists", 0, 0x1c },
    { "_bCompiling", 2, 0x20 },
};
static const dw4_metafield mo_f906[] = {
    { "_pBlendedVertsList", 0, 0x30 },
    { "_pBlendedNormsList", 0, 0x34 },
    { "_pWaitSeqList", 0, 0x38 },
    { "_lastArrayUsed", 1, 0x3c },
    { "_lSequence", 12, 0x40 },
    { "_textureCoordCompiled", 255, 0x48 },
    { "_multipassCompiled", 1, 0x88 },
};
static const dw4_metafield mo_f908[] = {
    { "_scaleAlphaState", 2, 0x24 },
    { "_syncSequence", 13, 0x28 },
    { "_textureCoordCompiled", 255, 0x30 },
    { "_multipassCompiled", 9, 0x70 },
    { "_blendMatrixCount", 9, 0x74 },
    { "_blendIndexCount", 9, 0x78 },
    { "_vertexCountCompiled", 9, 0x7c },
    { "_renderListHandle", 1, 0x80 },
    { "_dmaBuffer", 7, 0x84 },
    { "_dmaBufferStruct", 7, 0x88 },
};
static const dw4_metafield mo_f909[] = {
    { "_current", 2, 0x141 },
    { "_iContextOpen", 2, 0x142 },
    { "_pTexList", 5, 0x144 },
    { "_pClutList", 5, 0x148 },
    { "_pTexLoadedList", 0, 0x14c },
    { "_currentTex", 1, 0x150 },
    { "_iNextFreeTexID", 1, 0x154 },
    { "_currentCLUT", 1, 0x158 },
    { "_currentTextureFilter", 255, 0x15c },
    { "_currentTextureClampU", 255, 0x19c },
    { "_currentTextureClampV", 255, 0x1dc },
    { "_currentTextureProjectiveState", 255, 0x21c },
    { "_texPageEnable", 2, 0x22c },
    { "_texStage", 1, 0x230 },
    { "_texEnable", 255, 0x234 },
    { "_texStageFunc", 255, 0x244 },
    { "_texCoordSource", 255, 0x284 },
    { "_texCoordIndex", 255, 0x2c4 },
    { "_texGenMat", 40, 0x304 },
    { "_iCLUT_I8", 1, 0x344 },
    { "_iCLUT_A8", 1, 0x348 },
    { "_iCLUT_IA16", 1, 0x34c },
    { "_iCLUT_IA8", 1, 0x350 },
    { "_pCLUT_I8", 7, 0x354 },
    { "_pCLUT_A8", 7, 0x358 },
    { "_pCLUT_IA16", 7, 0x35c },
    { "_pCLUT_IA8", 7, 0x360 },
    { "_pBufList", 5, 0x364 },
    { "_currentBuf", 1, 0x368 },
    { "_clearColor", 38, 0x36c },
    { "_clearDepth", 16, 0x37c },
    { "_uiClearColor", 9, 0x380 },
    { "_uiClearDepth", 9, 0x384 },
    { "_clearStencil", 9, 0x388 },
    { "_iDisplayWidth", 1, 0x38c },
    { "_iDisplayHeight", 1, 0x390 },
    { "_iViewportX", 1, 0x394 },
    { "_iViewportY", 1, 0x398 },
    { "_iViewportW", 1, 0x39c },
    { "_iViewportH", 1, 0x3a0 },
    { "_viewportNear", 16, 0x3a4 },
    { "_viewportFar", 16, 0x3a8 },
    { "_pVertexArray", 0, 0x3ac },
    { "_pIndexArray", 0, 0x3b0 },
    { "_pStripLengthArray", 0, 0x3b4 },
    { "_vMask", 9, 0x3b8 },
    { "_currentColor", 9, 0x3bc },
    { "_pDLists", 5, 0x3c0 },
    { "_currentDListHandle", 1, 0x3c4 },
    { "_dlistErrors", 2, 0x3c8 },
    { "_projMat", 0, 0x3cc },
    { "_mvMat", 0, 0x3d0 },
    { "_texMat", 0, 0x3d4 },
    { "_texgenMat", 0, 0x3d8 },
    { "_blendMat0", 0, 0x3dc },
    { "_blendMat1", 0, 0x3e0 },
    { "_blendMat2", 0, 0x3e4 },
    { "_blendMat3", 0, 0x3e8 },
    { "_invTransBlendMat0", 0, 0x3ec },
    { "_invTransBlendMat1", 0, 0x3f0 },
    { "_invTransBlendMat2", 0, 0x3f4 },
    { "_invTransBlendMat3", 0, 0x3f8 },
    { "_bVertexBlendingEnabled", 2, 0x3fc },
    { "_edgeAntiAliasEnable", 2, 0x3fd },
    { "_alphaEnable", 2, 0x3fe },
    { "_alphaFunc", 6, 0x400 },
    { "_alphaVal", 16, 0x404 },
    { "_bBlendingEnabled", 2, 0x408 },
    { "_blendSrcMode", 255, 0x40c },
    { "_blendDestMode", 255, 0x44c },
    { "_blendConst", 255, 0x48c },
    { "_clippingEnable", 2, 0x4cc },
    { "_scissoringExt", 0, 0x4d0 },
    { "_scissorX", 1, 0x4d4 },
    { "_scissorY", 1, 0x4d8 },
    { "_scissorW", 1, 0x4dc },
    { "_scissorH", 1, 0x4e0 },
    { "_colorMaskR", 2, 0x4e4 },
    { "_colorMaskG", 2, 0x4e5 },
    { "_colorMaskB", 2, 0x4e6 },
    { "_colorMaskA", 2, 0x4e7 },
    { "_shadingMode", 6, 0x4e8 },
    { "_stencilState", 6, 0x4ec },
    { "_stencilRefVal", 1, 0x4f0 },
    { "_cullFaceEnable", 2, 0x4f4 },
    { "_cullFaceMode", 6, 0x4f8 },
    { "_bDepthWrite", 2, 0x4fc },
    { "_depthTestEnable", 2, 0x4fd },
    { "_depthTestFunc", 6, 0x500 },
    { "_depthWriteEnable", 2, 0x504 },
    { "_stencilFunc", 6, 0x508 },
    { "_renderMode", 6, 0x50c },
    { "_renderSides", 6, 0x510 },
    { "_fogEnable", 2, 0x514 },
    { "_fogDensity", 16, 0x518 },
    { "_fogMode", 6, 0x51c },
    { "_fogColor", 38, 0x520 },
    { "_fogNear", 16, 0x530 },
    { "_fogFar", 16, 0x534 },
    { "_pLightList", 5, 0x538 },
    { "_bLightingEnabled", 2, 0x53c },
    { "_currentMaterial", 5, 0x540 },
    { "_videoMode", 11, 0x544 },
    { "_bNormalizeNormalsState", 2, 0x55c },
    { "_matrixOptimizationEnable", 2, 0x55d },
    { "_statisticState", 6, 0x560 },
    { "_scaleToPower2Warning", 2, 0x564 },
    { "_mipmapMethodL", 6, 0x568 },
    { "_mipmapMethodK", 6, 0x56c },
    { "_mipmapL", 1, 0x570 },
    { "_mipmapK", 16, 0x574 },
    { "_renderlistMode", 6, 0x578 },
    { "_needsValidate", 1, 0x57c },
    { "_destAlphaTestState", 2, 0x580 },
    { "_destAlphaTestFunc", 6, 0x584 },
    { "_vertexProgramState", 2, 0x588 },
    { "_inverseTransposeCount", 1, 0x58c },
    { "_inverseTransposeNeedValidation", 2, 0x590 },
    { "_colorScalerState", 6, 0x594 },
    { "_colorScalerValue", 38, 0x598 },
    { "_textureMatrixState", 2, 0x5a8 },
    { "_colorClampState", 2, 0x5a9 },
    { "_materialSpecularState", 2, 0x5aa },
    { "_bTextureColorComponent", 2, 0x140 },
    { "_bMultiPassNum", 1, 0x5ac },
    { "_multiPassBlendState", 2, 0x5b0 },
    { "_multiPassBlendSrc", 6, 0x5b4 },
    { "_multiPassBlendDst", 6, 0x5b8 },
    { "_clutOptimization", 2, 0x5bc },
    { "_maxStageNum", 1, 0x5c0 },
    { "_globalMinU", 1, 0x5c4 },
    { "_globalMinV", 1, 0x5c8 },
    { "_globalMaxU", 1, 0x5cc },
    { "_globalMaxV", 1, 0x5d0 },
    { "_globalWrapState", 2, 0x5d4 },
    { "_globalWrapMode", 6, 0x5d8 },
    { "_textureStateFilter", 2, 0x5dc },
    { "_textureMinFilter", 6, 0x5e0 },
    { "_textureMagFilter", 6, 0x5e4 },
    { "_pixelPipelineMode", 6, 0x5e8 },
    { "_clippingType", 6, 0x5ec },
    { "_clearType", 6, 0x5f0 },
    { "_frameBufferTexture", 255, 0x5f4 },
    { "_alphaBlendingControl", 2, 0x600 },
    { "_alphaBlendingCorrection", 2, 0x601 },
    { "_ditherMatrix", 13, 0x608 },
};
static const dw4_metafield mo_f910[] = {
    { "_width", 1, 0x8 },
    { "_height", 1, 0xc },
    { "_originX", 1, 0x10 },
    { "_originY", 1, 0x14 },
    { "_vc", 0, 0x18 },
    { "_controllerEnabled", 2, 0x1c },
    { "_winName", 4, 0x20 },
    { "_renderDestinationHandle", 1, 0x24 },
    { "_open", 2, 0x28 },
    { "_bpp", 1, 0x2c },
    { "_alpha", 1, 0x30 },
    { "_bppDepth", 1, 0x34 },
};
static const dw4_metafield mo_f912[] = {
    { "_serviceThreads", 0, 0x8 },
};
static const dw4_metafield mo_f913[] = {
    { "_model", 0, 0x8 },
    { "_selectedObserver", 0, 0xc },
    { "_observerList", 0, 0x10 },
    { "_alwaysSelected", 2, 0x14 },
    { "_lastSelected", 1, 0x18 },
    { "_defaultSelected", 1, 0x1c },
};
static const dw4_metafield mo_f914[] = {
    { "_selected", 1, 0xc },
};
static const dw4_metafield mo_f915[] = {
    { "_group", 0, 0xc },
};
static const dw4_metafield mo_f917[] = {
    { "_num", 1, 0x38 },
};
static const dw4_metafield mo_f919[] = {
    { "_pos", 36, 0x8 },
    { "_dir", 36, 0x14 },
    { "_len", 16, 0x20 },
};
static const dw4_metafield mo_f922[] = {
    { "_construct", 2, 0x34 },
    { "_destruct", 2, 0x35 },
};
static const dw4_metafield mo_f923[] = {
    { "_valueTable", 0, 0x8 },
    { "_registryFile", 0, 0xc },
    { "_additionalSectionNames", 0, 0x10 },
    { "_showQueries", 2, 0x14 },
    { "_valueNameCaseSensitive", 2, 0x15 },
};
static const dw4_metafield mo_f924[] = {
    { "_section", 1, 0x8 },
    { "_value", 0, 0xc },
    { "_valueName", 0, 0x10 },
};
static const dw4_metafield mo_f926[] = {
    { "_iCreateMode", 6, 0xc },
    { "_iTexCreateMode", 6, 0x10 },
    { "_iRDHandle", 1, 0x14 },
    { "_bEnabled", 2, 0x18 },
    { "_iPrevRDHandle", 1, 0x1c },
    { "_pTex", 0, 0x20 },
    { "_iType", 6, 0x24 },
    { "_iSizeX", 1, 0x28 },
    { "_iSizeY", 1, 0x2c },
    { "_iColorBitCount", 1, 0x30 },
    { "_iAlphaBitCount", 1, 0x34 },
    { "_iDepthBitCount", 1, 0x38 },
    { "_iStencilBitCount", 1, 0x3c },
    { "_vc", 0, 0x40 },
};
static const dw4_metafield mo_f927[] = {
    { "_handle", 1, 0xc },
    { "_vc", 0, 0x10 },
};
static const dw4_metafield mo_f928[] = {
    { "_stateAttrs", 0, 0x8 },
    { "_cachedStateAttrs", 0, 0xc },
    { "_geomAttrs", 0, 0x10 },
    { "_sortingCache", 5, 0x14 },
    { "_distance", 16, 0x18 },
    { "_theMass", 0, 0x1c },
};
static const dw4_metafield mo_f931[] = {
    { "_visualContext", 0, 0x8 },
};
static const dw4_metafield mo_f933[] = {
    { "_imageDirectory", 0, 0xc },
    { "_directoryList", 0, 0x10 },
    { "_relativeFilePath", 4, 0x14 },
    { "_absoluteFilePath", 4, 0x18 },
    { "_asyncLoadState", 2, 0x1c },
    { "_loadQueue", 0, 0x20 },
    { "_loadThread", 0, 0x24 },
    { "_autoCompatibility", 2, 0x28 },
    { "_alignmentStrings", 0, 0x2c },
    { "_alignmentValues", 0, 0x30 },
    { "_postProcessAsyncronousFilesState", 2, 0x34 },
    { "_temporaryMemoryPool", 0, 0x38 },
    { "_dataMemoryPool", 0, 0x3c },
    { "_objectMemoryPool", 0, 0x40 },
    { "_IGBSharingState", 2, 0x44 },
    { "_IGBChunkSize", 1, 0x48 },
    { "_useMemoryPoolAssignmentsState", 2, 0x8 },
};
static const dw4_metafield mo_f934[] = {
    { "_distance", 16, 0x4c },
    { "_lastMousePos", 37, 0x50 },
    { "_leftMouseActive", 2, 0x58 },
    { "_middleMouseActive", 2, 0x59 },
    { "_rightMouseActive", 2, 0x5a },
    { "_joystickT", 37, 0x5c },
    { "_joystickR", 37, 0x64 },
    { "_constraint", 2, 0x6c },
    { "_constraintAxis", 6, 0x70 },
    { "_active", 2, 0x74 },
    { "_maya", 2, 0x75 },
    { "_head", 16, 0x78 },
    { "_roll", 16, 0x7c },
    { "_pitch", 16, 0x80 },
    { "_zoom", 16, 0x84 },
    { "_translation", 36, 0x88 },
};
static const dw4_metafield mo_f935[] = {
    { "_sceneGraph", 0, 0x14 },
    { "_textures", 0, 0x18 },
    { "_cameras", 0, 0x1c },
    { "_animationBegin", 12, 0x20 },
    { "_animationEnd", 12, 0x28 },
    { "_upVector", 36, 0x30 },
    { "_sceneGraphList", 0, 0x3c },
};
static const dw4_metafield mo_f937[] = {
    { "_iterateGraph", 0, 0xc },
    { "_searchString", 4, 0x10 },
    { "_searchMeta", 0, 0x14 },
    { "_nextOfTypeCode", 6, 0x18 },
};
static const dw4_metafield mo_f940[] = {
    { "_managerList", 0, 0x8 },
    { "_cachedManagerList", 0, 0xc },
};
static const dw4_metafield mo_f941[] = {
    { "_pRDAttr", 0, 0xc },
};
static const dw4_metafield mo_f942[] = {
    { "_mode", 6, 0xc },
};
static const dw4_metafield mo_f943[] = {
    { "_attrPushLists", 0, 0x8 },
    { "_attrPopLists", 0, 0xc },
    { "_dataPumps", 0, 0x10 },
    { "_childLists", 0, 0x14 },
};
static const dw4_metafield mo_f944[] = {
    { "_attrNames", 0, 0xc },
    { "_attrTypes", 0, 0x10 },
    { "_fileCachingMode", 6, 0x14 },
};
static const dw4_metafield mo_f946[] = {
    { "_factoryList", 0, 0x14 },
};
static const dw4_metafield mo_f948[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f952[] = {
    { "_boneInfoList", 0, 0x10 },
    { "_invJointArray", 7, 0x14 },
    { "_jointCount", 1, 0x18 },
};
static const dw4_metafield mo_f953[] = {
    { "_parentIdx", 1, 0xc },
    { "_bmIdx", 1, 0x10 },
    { "_flags", 1, 0x14 },
};
static const dw4_metafield mo_f956[] = {
    { "_skinnedGraph", 0, 0xc },
    { "_bound", 0, 0x10 },
};
static const dw4_metafield mo_f958[] = {
    { "_dlist", 0, 0x8 },
    { "_mode", 1, 0xc },
    { "_renderPackagePool", 0, 0x10 },
    { "_tmpAttrs", 0, 0x14 },
    { "_transpPackages", 0, 0x18 },
    { "_opaquePackages", 0, 0x1c },
    { "_firstPackages", 0, 0x20 },
    { "_lightAttrs", 0, 0x24 },
    { "_firstAttrs", 0, 0x28 },
    { "_transpAttrs", 0, 0x2c },
    { "_opaqueAttrs", 0, 0x30 },
    { "_firstPackageIndices", 0, 0x34 },
    { "_transpPackageIndices", 0, 0x38 },
    { "_opaquePackageIndices", 0, 0x3c },
    { "_depthWriteDisable", 0, 0x40 },
    { "_cullFaceFront", 0, 0x44 },
    { "_cullFaceBack", 0, 0x48 },
    { "_transparencyDrawMode", 1, 0x4c },
    { "_emptyRenderPackage", 0, 0x50 },
    { "_emptyRenderPackageList", 0, 0x54 },
    { "_emptyRenderPackageIndices", 0, 0x58 },
    { "_lastEmptyRenderPackageAttrs", 0, 0x5c },
    { "_firstEmptyRenderPackageAttrs", 0, 0x60 },
    { "_emptyGeometry", 0, 0x64 },
    { "_curList", 0, 0x68 },
    { "_prevList", 0, 0x6c },
    { "_isCompoundPackageOpen", 2, 0x70 },
    { "_isCompoundPackageTransparent", 2, 0x71 },
    { "_isCompoundPackageFirst", 2, 0x72 },
    { "_compoundPackage", 0, 0x74 },
    { "_compoundPackageNestCount", 1, 0x78 },
    { "_cachedPackage", 0, 0x7c },
    { "_outputCreated", 2, 0x80 },
    { "_useZSort", 2, 0x81 },
    { "_forceNoSeparate", 2, 0x82 },
    { "_printOutputState", 2, 0x83 },
};
static const dw4_metafield mo_f959[] = {
    { "_center", 36, 0x8 },
    { "_radius", 16, 0x14 },
};
static const dw4_metafield mo_f960[] = {
    { "_poolIndex", 1, 0x90 },
    { "_alignment", 10, 0x70 },
    { "_rawMemory", 5, 0x74 },
    { "_totalSize", 13, 0x78 },
    { "_elementSize", 9, 0x80 },
    { "_stackPtr", 9, 0x84 },
    { "_nextInt", 9, 0x88 },
    { "_isActive", 2, 0x8c },
    { "_isAlchemyMemory", 2, 0x8d },
    { "_eventTracker", 0, 0x94 },
};
static const dw4_metafield mo_f961[] = {
    { "_insertLock", 0, 0xc },
    { "_removeLock", 0, 0x10 },
    { "_queueSema", 0, 0x14 },
    { "_capacity", 9, 0x18 },
    { "_insertElement", 9, 0x1c },
    { "_removeElement", 9, 0x20 },
    { "_data", 7, 0x24 },
    { "_maxCapacity", 9, 0x28 },
};
static const dw4_metafield mo_f962[] = {
    { "_value", 16, 0xc },
    { "_maximumValue", 16, 0x10 },
    { "_useMultiplier", 2, 0x14 },
    { "_text", 4, 0x18 },
    { "_numberFormat", 4, 0x1c },
    { "_visible", 2, 0x20 },
    { "_displayComponent", 0, 0x24 },
    { "_aspect", 0, 0x28 },
    { "_textElement", 0, 0x2c },
    { "_manager", 0, 0x30 },
    { "_statId", 6, 0x34 },
    { "_otherId", 1, 0x38 },
};
static const dw4_metafield mo_f964[] = {
    { "_refVal", 9, 0xc },
    { "_func", 6, 0x10 },
    { "_writeMask", 9, 0x14 },
    { "_readMask", 9, 0x18 },
    { "_stenFailOp", 6, 0x1c },
    { "_stenPassZPassOp", 6, 0x20 },
    { "_stenPassZFailOp", 6, 0x24 },
};
static const dw4_metafield mo_f965[] = {
    { "_enabled", 2, 0xc },
};
static const dw4_metafield mo_f966[] = {
    { "_num", 1, 0x3c },
};
static const dw4_metafield mo_f967[] = {
    { "_refCounted", 2, 0x38 },
};
static const dw4_metafield mo_f968[] = {
    { "_buffer", 7, 0x8 },
    { "_length", 9, 0xc },
};
static const dw4_metafield mo_f972[] = {
    { "_capacity", 1, 0x8 },
    { "_hashCapacity", 1, 0xc },
    { "_strings", 0, 0x10 },
    { "_hashIndex", 0, 0x14 },
};
static const dw4_metafield mo_f973[] = {
    { "_alignment", 1, 0x34 },
    { "_cppConstructor", 5, 0x38 },
    { "_cppDestructor", 5, 0x3c },
};
static const dw4_metafield mo_f974[] = {
    { "_childMask", 0, 0x20 },
};
static const dw4_metafield mo_f975[] = {
    { "_capacity", 1, 0x8 },
    { "_hashCapacity", 1, 0xc },
    { "_lowAddress", 9, 0x10 },
    { "_highAddress", 9, 0x14 },
    { "_hashIncrement", 9, 0x18 },
    { "_symbols", 0, 0x1c },
    { "_hashIndex", 0, 0x20 },
    { "_symbolNames", 0, 0x24 },
    { "_sourceFileNames", 0, 0x28 },
};
static const dw4_metafield mo_f976[] = {
    { "m", 40, 0xc },
    { "_unitID", 1, 0x4c },
};
static const dw4_metafield mo_f977[] = {
    { "_font", 0, 0x2c },
    { "_geometryAttr", 0, 0x30 },
    { "_text", 4, 0x34 },
};
static const dw4_metafield mo_f978[] = {
    { "_bColor", 9, 0x10 },
    { "_magFilter", 6, 0x14 },
    { "_minFilter", 6, 0x18 },
    { "_wrapS", 6, 0x1c },
    { "_wrapT", 6, 0x20 },
    { "_texId", 1, 0x24 },
    { "_mipmapMode", 6, 0x28 },
    { "_source", 6, 0x2c },
    { "_image", 0, 0x30 },
    { "_paging", 2, 0x34 },
    { "_tu", 0, 0x38 },
    { "_imageCount", 1, 0x3c },
    { "_imageMipMaps", 0, 0x40 },
    { "_vc", 0, 0xc },
    { "_videoBuffer", 5, 0x44 },
};
static const dw4_metafield mo_f979[] = {
    { "_texture", 0, 0xc },
    { "_unitID", 1, 0x10 },
};
static const dw4_metafield mo_f981[] = {
    { "_mode", 6, 0xc },
    { "_texCoordIndex", 1, 0x10 },
    { "_unitID", 1, 0x14 },
};
static const dw4_metafield mo_f982[] = {
    { "_cubeImage", 255, 0x48 },
    { "_applyType", 6, 0x60 },
    { "_unused", 1, 0x64 },
};
static const dw4_metafield mo_f983[] = {
    { "_mode", 6, 0xc },
    { "_unitID", 1, 0x10 },
    { "_arg0", 6, 0x14 },
    { "_arg1", 6, 0x18 },
    { "_type", 6, 0x1c },
    { "_call_state", 8, 0x20 },
    { "_functionType", 6, 0x24 },
};
static const dw4_metafield mo_f985[] = {
    { "_m", 40, 0xc },
    { "_unitID", 1, 0x4c },
    { "_outputElementCount", 17, 0x50 },
    { "_isProjective", 2, 0x52 },
};
static const dw4_metafield mo_f987[] = {
    { "_enabled", 2, 0xc },
    { "_unitID", 1, 0x10 },
};
static const dw4_metafield mo_f988[] = {
    { "_enabled", 2, 0xc },
    { "_unitID", 1, 0x10 },
};
static const dw4_metafield mo_f989[] = {
    { "_texture", 0, 0xc },
    { "_unitID", 1, 0x10 },
};
static const dw4_metafield mo_f990[] = {
    { "_file", 0, 0x8 },
    { "_palette", 7, 0xc },
    { "_tempMap", 7, 0x10 },
    { "_tempRow", 7, 0x14 },
    { "_bCount", 1, 0x18 },
    { "_bType", 1, 0x1c },
    { "_psize", 1, 0x20 },
    { "_nextChar", 1, 0x24 },
    { "_limitChar", 1, 0x28 },
    { "_sbpr", 1, 0x2c },
};
static const dw4_metafield mo_f991[] = {
    { "_priority", 6, 0x18 },
    { "_type", 6, 0xc },
    { "_scope", 6, 0x10 },
    { "_state", 6, 0x14 },
    { "_arg", 5, 0x1c },
    { "_stack", 5, 0x20 },
    { "_stackSize", 9, 0x24 },
    { "_function", 5, 0x28 },
    { "_isMaster", 2, 0x2c },
    { "_userStack", 2, 0x2d },
};
static const dw4_metafield mo_f993[] = {
    { "_threadList", 0, 0x8 },
    { "_sema", 0, 0xc },
};
static const dw4_metafield mo_f994[] = {
    { "_time", 12, 0x10 },
};
static const dw4_metafield mo_f998[] = {
    { "_m", 40, 0x20 },
    { "_target", 1, 0x60 },
    { "_mvm", 0, 0x64 },
    { "_transformInput", 0, 0x68 },
};
static const dw4_metafield mo_f1001[] = {
    { "_m", 40, 0x20 },
    { "_mvm", 40, 0x60 },
};
static const dw4_metafield mo_f1002[] = {
    { "_xlateList", 0, 0x8 },
    { "_quatList", 0, 0xc },
    { "_scaleList", 0, 0x10 },
    { "_timeList", 0, 0x14 },
    { "_startTime", 31, 0x18 },
    { "_uniformTimeEnabled", 2, 0x20 },
    { "_playMode", 6, 0x24 },
    { "_lastTime", 1, 0x28 },
    { "_centerOfRotation", 36, 0x2c },
};
static const dw4_metafield mo_f1003[] = {
    { "_timeListLong", 0, 0x38 },
    { "_interpolationDataTranslation", 0, 0x3c },
    { "_interpolationDataRotation", 0, 0x40 },
    { "_interpolationDataScale", 0, 0x44 },
    { "_drivenChannels", 8, 0x48 },
    { "_interpolationMethod", 255, 0x49 },
    { "_keyframeTimeOffset", 12, 0x50 },
    { "_animationDuration", 12, 0x58 },
    { "_compressedDataObject", 0, 0x60 },
};
static const dw4_metafield mo_f1007[] = {
    { "_nodeSelectProcEnabled", 2, 0x8 },
    { "_nodeSelectProc", 5, 0xc },
    { "_timeLong", 12, 0x10 },
    { "_userTimeState", 2, 0x18 },
    { "_travProcs", 0, 0x1c },
};
static const dw4_metafield mo_f1009[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f1012[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f1016[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f1018[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f1026[] = {
    { "_num", 1, 0x34 },
};
static const dw4_metafield mo_f1032[] = {
    { "_vdata", 7, 0x8 },
    { "_numVerts", 9, 0xc },
    { "_vtype", 9, 0x10 },
    { "_usageFlags", 9, 0x14 },
};
static const dw4_metafield mo_f1033[] = {
    { "_vertexFormat", 11, 0x1c },
    { "_blendWeights", 7, 0x20 },
    { "_blendIndices", 7, 0x24 },
    { "_blendIndex", 9, 0x28 },
    { "_pointSpriteSize", 7, 0x2c },
    { "_memPool", 0, 0x18 },
};
static const dw4_metafield mo_f1034[] = {
    { "_objList", 0, 0x10 },
    { "_vertexStream", 0, 0x14 },
    { "_internalBuffer", 0, 0xc },
};
static const dw4_metafield mo_f1035[] = {
    { "_vertexArray", 0, 0xc },
};
static const dw4_metafield mo_f1036[] = {
    { "_m", 40, 0xc },
    { "_blendMatID", 10, 0x4c },
};
static const dw4_metafield mo_f1038[] = {
    { "_matrixList", 0, 0x18 },
    { "_skeletonTransform", 40, 0x1c },
    { "_skeletonInverseTransform", 40, 0x5c },
    { "_matrixCache", 5, 0x10 },
    { "_isSkeletonTransformIdentity", 2, 0xc },
    { "_isSkeletonTransformSet", 2, 0xd },
    { "_currentMatrixCount", 1, 0x14 },
};
static const dw4_metafield mo_f1040[] = {
    { "_enabled", 2, 0xc },
};
static const dw4_metafield mo_f1041[] = {
    { "_data", 0, 0xc },
    { "_componentType", 6, 0x10 },
    { "_componentIndex", 9, 0x14 },
    { "_componentSize", 9, 0x18 },
    { "_userID", 1, 0x1c },
    { "_componentFraction", 9, 0x20 },
};
static const dw4_metafield mo_f1043[] = {
    { "_stream", 5, 0xc },
    { "_isConfigured", 2, 0x10 },
    { "_vertexDataList", 0, 0x14 },
    { "_accessMode", 6, 0x18 },
    { "_primitive", 6, 0x1c },
    { "_streamMode", 6, 0x20 },
};
static const dw4_metafield mo_f1044[] = {
    { "_model", 0, 0x8 },
};
static const dw4_metafield mo_f1046[] = {
    { "_viewMode", 0, 0x8 },
    { "_viewModel", 0, 0xc },
    { "_synchronizers", 0, 0x10 },
    { "_homeMatrix", 40, 0x14 },
};
static const dw4_metafield mo_f1047[] = {
    { "_inverseMatrix", 40, 0xc },
};
static const dw4_metafield mo_f1048[] = {
    { "_viewMatrix", 40, 0xc },
    { "_ratio", 16, 0x4c },
    { "_hfov", 16, 0x50 },
    { "_nearPlane", 16, 0x54 },
    { "_farPlane", 16, 0x58 },
    { "_position", 36, 0x5c },
    { "_direction", 36, 0x68 },
    { "_viewUpVector", 36, 0x74 },
    { "_viewLeftVector", 36, 0x80 },
    { "_sceneUpVector", 36, 0x8c },
    { "_drawTime", 12, 0x98 },
    { "_selectedCenter", 36, 0xa0 },
    { "_selectedLength", 16, 0xac },
};
static const dw4_metafield mo_f1049[] = {
    { "_ref", 0, 0x8 },
    { "_function", 11, 0xc },
};
static const dw4_metafield mo_f1050[] = {
    { "_dataPumpManager", 0, 0x10 },
};
static const dw4_metafield mo_f1051[] = {
    { "_menuBackColor", 0, 0x8 },
    { "_menuItemForeColor", 0, 0xc },
    { "_menuMarkColor", 0, 0x10 },
    { "_iconBackColor", 0, 0x14 },
    { "_bigIconColor", 0, 0x18 },
    { "_bigIconHighlightColor", 0, 0x1c },
    { "_smallIconOnOffColor", 0, 0x20 },
    { "_font", 0, 0x24 },
};
static const dw4_metafield mo_f1052[] = {
    { "_current", 2, 0x8 },
    { "_filename", 4, 0xc },
};
static const dw4_metafield mo_f1053[] = {
    { "_state", 2, 0x8 },
    { "_mode", 4, 0xc },
};
static const dw4_metafield mo_f1054[] = {
    { "_scene", 0, 0xc },
    { "_upVector", 36, 0x10 },
    { "_ratio", 16, 0x1c },
    { "_hfov", 16, 0x20 },
    { "_nearPlane", 16, 0x24 },
    { "_farPlane", 16, 0x28 },
    { "_projectionMatrix", 40, 0x2c },
    { "_viewMatrix", 40, 0x6c },
    { "_drawTime", 12, 0xb0 },
    { "_sortTexture", 2, 0xb8 },
    { "_sortTransparent", 2, 0xb9 },
    { "_sortTransparentDistance", 2, 0xba },
    { "_transparencyMode", 1, 0xbc },
    { "_useSceneLights", 2, 0xc0 },
    { "_useHeadLight", 2, 0xc1 },
    { "_useHeadLightSpecular", 2, 0xc2 },
    { "_alphaTest", 2, 0xc3 },
    { "_alphaTestForce", 2, 0xc4 },
    { "_backFaceCulling", 2, 0xc5 },
    { "_backFaceCullingForce", 2, 0xc6 },
    { "_wireframe", 2, 0xc7 },
    { "_wireframeForce", 2, 0xc8 },
    { "_flatShading", 2, 0xc9 },
    { "_flatShadingForce", 2, 0xca },
    { "_disables", 0, 0xcc },
    { "_showGui", 2, 0xd0 },
    { "_showBoundingBox", 2, 0xd1 },
    { "_showNormals", 2, 0xd2 },
    { "_flushFrames", 2, 0xd3 },
    { "_operationMode", 1, 0xd4 },
    { "_firstCameraMode", 1, 0xd8 },
    { "_cameras", 0, 0xdc },
    { "_beginTime", 12, 0xe0 },
    { "_endTime", 12, 0xe8 },
    { "_selectedObject", 0, 0xf0 },
    { "_timeOperation", 1, 0xf4 },
    { "_loopMode", 1, 0xf8 },
    { "_speed", 16, 0xfc },
    { "_cursorPosition", 37, 0x100 },
};
static const dw4_metafield mo_f1055[] = {
    { "_parameters", 0, 0xc },
    { "_backFaceCullingAttr", 0, 0x10 },
    { "_alphaTestAttr", 0, 0x14 },
    { "_shadeModelAttr", 0, 0x18 },
    { "_polygonModeAttr", 0, 0x1c },
    { "_lightingAttr", 0, 0x20 },
    { "_headlightAttr", 0, 0x24 },
    { "_headlightStateAttr", 0, 0x28 },
    { "_attrSet", 0, 0x2c },
    { "_attrSetOverride", 0, 0x30 },
    { "_headlightTransform", 0, 0x34 },
    { "_headlightSet", 0, 0x38 },
    { "_lightList", 0, 0x3c },
    { "_lightStateList", 0, 0x40 },
    { "_lightingState", 2, 0x44 },
    { "_lightTraversal", 0, 0x48 },
    { "_lightOutput", 0, 0x4c },
    { "_sceneTraversal", 0, 0x50 },
    { "_sceneOutput", 0, 0x54 },
    { "_disableExtension", 0, 0x58 },
};
static const dw4_metafield mo_f1056[] = {
    { "_applicationController", 0, 0x10 },
    { "_parameters", 0, 0x14 },
    { "_viewerRenderer", 0, 0x18 },
    { "_bboxRenderer", 0, 0x1c },
    { "_normalsRenderer", 0, 0x20 },
    { "_flushRenderer", 0, 0x24 },
    { "_clippingCheckFrame", 1, 0x28 },
    { "_gui", 0, 0x2c },
    { "_guiFactory", 0, 0x30 },
    { "_rootComponent", 0, 0x34 },
    { "_menuHolder", 0, 0x38 },
    { "_operationBoxHolder", 0, 0x3c },
    { "_operationBox", 0, 0x40 },
    { "_timeBoxHolder", 0, 0x44 },
    { "_timeBox", 0, 0x48 },
    { "_menuBar", 0, 0x4c },
    { "_viewMenu", 0, 0x50 },
    { "_viewportMenu", 0, 0x54 },
    { "_cameraMenu", 0, 0x58 },
    { "_cameraMenuActiver", 0, 0x5c },
    { "_optionMenu", 0, 0x60 },
    { "_disableMenu", 0, 0x64 },
    { "_statMenu", 0, 0x68 },
    { "_timeMenu", 0, 0x6c },
    { "_alchemyMenu", 0, 0x70 },
    { "_timeStatistic", 0, 0x74 },
    { "_speedStatistic", 0, 0x78 },
    { "_nearPlaneStatistic", 0, 0x7c },
    { "_farPlaneStatistic", 0, 0x80 },
    { "_hotKeyReceiver", 0, 0x84 },
    { "_viewManager", 0, 0x88 },
    { "_statManager", 0, 0x8c },
    { "_disableComponents", 0, 0x90 },
    { "_disableViews", 0, 0x94 },
    { "_operationModeGroup", 0, 0x98 },
    { "_references", 0, 0x9c },
    { "_frames", 1, 0xa0 },
    { "_lastStatTime", 12, 0xa8 },
    { "_guiVisibility", 6, 0xb0 },
    { "_textureList", 0, 0xb4 },
    { "_modeChange", 0, 0xb8 },
    { "_isCapturingBudget", 2, 0xbc },
    { "_hideAllStatisticsMenuItem", 0, 0xc0 },
};
static const dw4_metafield mo_f1057[] = {
    { "_application", 0, 0xc },
    { "_viewerRenderer", 0, 0x10 },
};
static const dw4_metafield mo_f1058[] = {
    { "_items", 0, 0x8 },
    { "_visualContext", 0, 0xc },
    { "_guiFactory", 0, 0x10 },
    { "_menu", 0, 0x14 },
    { "_boxComponent", 0, 0x18 },
    { "_string", 0, 0x1c },
    { "_recordStatisticMaximum", 2, 0x20 },
    { "_attrMetaObjects", 0, 0x24 },
    { "_extraSgStatistics", 0, 0x28 },
    { "_attrCount", 16, 0x2c },
    { "_displayListAttrCount", 16, 0x30 },
    { "_textureAttrCount", 16, 0x34 },
    { "_geometryAttrCount", 16, 0x38 },
    { "_geometrySetAttrCount", 16, 0x3c },
    { "_mvmAttrCount", 16, 0x40 },
};
static const dw4_metafield mo_f1059[] = {
    { "_x", 1, 0xc },
    { "_y", 1, 0x10 },
    { "_w", 1, 0x14 },
    { "_h", 1, 0x18 },
    { "_scissorExt", 0, 0x1c },
    { "_nearZ", 16, 0x20 },
    { "_farZ", 16, 0x24 },
};
static const dw4_metafield mo_f1060[] = {
    { "_origin", 37, 0x8 },
    { "_size", 37, 0x10 },
};
static const dw4_metafield mo_f1063[] = {
    { "_contextIndex", 1, 0x14 },
    { "_timer", 0, 0x38 },
    { "_showFrameRate", 2, 0x3c },
    { "_commandLineFrameRate", 2, 0x3d },
    { "_primitiveCount", 1, 0x40 },
    { "_frameStartTime", 16, 0x44 },
    { "_blendMatricesCount", 1, 0x48 },
    { "_blendIndex", 9, 0x4c },
    { "_inverseTranspose", 7, 0x50 },
    { "_blendMatrices", 5, 0x54 },
    { "_inverseTransposeCount", 9, 0x58 },
    { "_renderingTime", 12, 0x60 },
    { "_scissorType", 6, 0x68 },
    { "_viewMatrixHint", 40, 0x6c },
    { "_viewMatrixInverse", 40, 0xac },
    { "_viewMatrixDirty", 2, 0xec },
    { "_vertexArray2", 255, 0xf0 },
    { "_customStates", 0, 0x130 },
    { "_customFields", 0, 0x134 },
    { "_ditherState", 2, 0x138 },
    { "_driverDataMemoryPool", 0, 0x18 },
    { "_vertexMemoryPool", 0, 0x1c },
    { "_internalMemoryPool", 0, 0x20 },
    { "_temporaryMemoryPool", 0, 0x24 },
    { "_imageMemoryPool", 0, 0x28 },
    { "_textureMemoryPool", 0, 0x2c },
    { "_statisticsMemoryPool", 0, 0x30 },
    { "_listMemoryPool", 0, 0x34 },
};
static const dw4_metafield mo_f1064[] = {
    { "_visualContext", 0, 0x8 },
};
static const dw4_metafield mo_f1065[] = {
    { "_visualContext", 0, 0x8 },
};
static const dw4_metafield mo_f1070[] = {
    { "_insightCore", 0, 0x8 },
};
static const dw4_metafield mo_f1072[] = {
    { "_particleCtrl2", 0, 0x8 },
    { "_luaManager", 0, 0xc },
    { "_matCtrl", 0, 0x10 },
    { "_selectCtrl", 0, 0x14 },
    { "_waterPlain", 0, 0x18 },
    { "_action2", 0, 0x1c },
    { "_meterCtrl", 0, 0x20 },
    { "_targetObj", 0, 0x24 },
    { "_weapon", 0, 0x28 },
    { "_cameraCtrl", 0, 0x2c },
    { "_point01", 0, 0x30 },
    { "_bkColor", 0, 0x34 },
    { "_cpTransform", 0, 0x38 },
    { "_shadow01", 0, 0x3c },
    { "_generater", 0, 0x40 },
    { "_hitLandModel", 0, 0x44 },
    { "_hitLandDeliv", 0, 0x48 },
    { "_sound", 0, 0x4c },
    { "_seCtl", 0, 0x50 },
    { "_actionStarter", 0, 0x54 },
    { "_layerCtl", 0, 0x58 },
    { "_font", 0, 0x5c },
    { "_switchCtrl", 0, 0x60 },
    { "_lightCtrl", 0, 0x64 },
    { "_numberCtrl", 0, 0x68 },
    { "_staticInfoCtl", 0, 0x6c },
    { "_movie", 0, 0x70 },
    { "_dbManager", 0, 0x74 },
    { "_saveUtil", 0, 0x78 },
    { "_textureCtrl", 0, 0x7c },
    { "_system", 0, 0x80 },
    { "_messenger", 0, 0x84 },
    { "_fileList", 0, 0x88 },
    { "_padManager", 0, 0x8c },
    { "_cri", 0, 0x90 },
    { "_luaInterface", 0, 0x94 },
    { "_demoManager", 0, 0x98 },
    { "_timer", 0, 0x9c },
    { "_memory", 0, 0xa0 },
};
static const dw4_metafield mo_f1073[] = {
    { "_afsSetup", 0, 0x8 },
    { "_stageCtl", 0, 0xc },
    { "_panelWaza", 0, 0x10 },
    { "_logo", 0, 0x14 },
    { "_title2", 0, 0x18 },
    { "_loadCtrl2", 0, 0x1c },
    { "_loadIntf2", 0, 0x20 },
    { "_saveCtrl", 0, 0x24 },
    { "_saveIntf", 0, 0x28 },
    { "_gameRam", 0, 0x2c },
    { "_status", 0, 0x30 },
    { "_mdlPlayer", 0, 0x34 },
    { "_mdlPlayer2", 0, 0x38 },
    { "_mdlPBullet", 0, 0x3c },
    { "_mdlEnemy", 0, 0x40 },
    { "_mdlEBullet", 0, 0x44 },
    { "_mdlObject", 0, 0x48 },
    { "_mdlItem", 0, 0x4c },
    { "_mdlEffect", 0, 0x50 },
    { "_mdlMapBase", 0, 0x54 },
    { "_mdlMapCursor", 0, 0x58 },
};

const dw4_metaobject dw4_metaobjects[] = {
    { "ParticleArray", "igParticleArray", 0x80, 0x53b740, mo_f0, 11 },
    { "ParticleInfo", "igSceneInfo", 0x400, 0x533f50, mo_f1, 18 },
    { "ParticleTimer", "igGeometry", 0x40, 0x53b7f0, mo_f2, 3 },
    { "__internalNonRefCountedObjectList", "igObject", 0x10, 0x0, mo_f3, 2 },
    { "__internalObjectList", "__internalNonRefCountedObjectList", 0x10, 0x0, 0, 0 },
    { "be", "igInfoManager", 0x20, 0x539f10, mo_f5, 1 },
    { "beAction2", "beBaseInfoManager", 0x20, 0x539f90, 0, 0 },
    { "beAction2Data", "igNamedObject", 0x10, 0x533fc0, mo_f7, 1 },
    { "beAction2DataList", "igObjectList", 0x20, 0x534020, 0, 0 },
    { "beAction2FADESET", "igNamedObject", 0x20, 0x534150, mo_f9, 2 },
    { "beAction2FLASHSET", "igNamedObject", 0x10, 0x534210, 0, 0 },
    { "beAction2Info", "beBaseInfo", 0x30, 0x534270, mo_f11, 3 },
    { "beAction2InfoList", "igObjectList", 0x20, 0x5342e0, 0, 0 },
    { "beAction2InfoRam", "beBaseInfoRam", 0x40, 0x534350, mo_f13, 4 },
    { "beAction2InfoWork", "igObject", 0x60, 0x5343b0, mo_f14, 21 },
    { "beAction2JOINTSET", "igNamedObject", 0x20, 0x5340f0, mo_f15, 3 },
    { "beAction2MOTIONSET", "igNamedObject", 0x20, 0x534090, mo_f16, 3 },
    { "beAction2WAITCHECK", "igNamedObject", 0x10, 0x5341b0, mo_f17, 1 },
    { "beActionStarter", "beBaseInfoManager", 0x20, 0x53a030, 0, 0 },
    { "beActionStarterData", "igNamedObject", 0x30, 0x5344e0, mo_f19, 5 },
    { "beActionStarterData2", "beActionStarterData", 0x30, 0x534480, mo_f20, 1 },
    { "beActionStarterDataList", "igObjectList", 0x20, 0x534410, 0, 0 },
    { "beActionStarterInfo", "beBaseInfo", 0x20, 0x534610, mo_f22, 1 },
    { "beActionStarterInfoRam", "beBaseInfoRam", 0x30, 0x534680, 0, 0 },
    { "beAsTargetModelData", "igNamedObject", 0x10, 0x534540, mo_f24, 1 },
    { "beAsTargetModelDataList", "igObjectList", 0x20, 0x5345a0, 0, 0 },
    { "beBaseInfo", "igInfo", 0x20, 0x539dc0, mo_f26, 2 },
    { "beBaseInfoData", "igNamedObject", 0x10, 0x539350, mo_f27, 1 },
    { "beBaseInfoDataList", "igObjectList", 0x20, 0x5346e0, 0, 0 },
    { "beBaseInfoList", "igObjectList", 0x20, 0x534750, 0, 0 },
    { "beBaseInfoManager", "igInfoManager", 0x20, 0x53a0d0, mo_f30, 4 },
    { "beBaseInfoManagerList", "igObjectList", 0x20, 0x5347c0, 0, 0 },
    { "beBaseInfoRam", "igObject", 0x30, 0x539e90, mo_f32, 9 },
    { "beBaseInfoRamList", "igObjectList", 0x20, 0x534890, 0, 0 },
    { "beBaseInfoRamTimer", "beBaseInfoData", 0x40, 0x534830, mo_f34, 6 },
    { "beBinDataObject", "beBaseInfoData", 0x20, 0x0, mo_f35, 2 },
    { "beBkColor", "beBaseInfoManager", 0x30, 0x53a170, mo_f36, 1 },
    { "beBkColorInfo", "beBaseInfo", 0x30, 0x534900, mo_f37, 1 },
    { "beCameraBoxData", "igObject", 0x20, 0x5349d0, mo_f38, 5 },
    { "beCameraCtrl", "beBaseInfoManager", 0xe0, 0x53a210, mo_f39, 13 },
    { "beCameraCtrlInfo", "beBaseInfo", 0x20, 0x534a90, mo_f40, 1 },
    { "beCameraCtrlInfoRamShake", "beBaseInfoData", 0x40, 0x534970, mo_f41, 8 },
    { "beCameraDemoData", "igObject", 0x20, 0x534a30, mo_f42, 3 },
    { "beCameraMode", "igViewMode", 0x80, 0x53a2b0, mo_f43, 8 },
    { "beChangePosTransform", "beBaseInfoManager", 0x30, 0x53a340, mo_f44, 1 },
    { "beChangePosTransformInfo", "beBaseInfo", 0x20, 0x534b00, 0, 0 },
    { "beChangePosTransformInfoRam", "beBaseInfoRam", 0x30, 0x534b70, mo_f46, 1 },
    { "beCopyModelCtrl2", "igTransform", 0x70, 0x534bd0, mo_f47, 1 },
    { "beCopyTransform", "igTransform", 0x70, 0x534c70, mo_f48, 1 },
    { "beCountry", "igObject", 0x10, 0x534d10, 0, 0 },
    { "beCri", "igInfoManager", 0x50, 0x53a3e0, mo_f50, 12 },
    { "beCriAcxData", "beBinDataObject", 0x20, 0x534d70, 0, 0 },
    { "beCriAudio", "igObject", 0x20, 0x534e30, mo_f52, 4 },
    { "beCriFxInfo", "igInfo", 0x30, 0x534ef0, mo_f53, 4 },
    { "beCriFxXbData", "igObject", 0x40, 0x534e90, mo_f54, 12 },
    { "beCriHandle", "igNamedObject", 0x30, 0x534f60, mo_f55, 5 },
    { "beCriHandleList", "igObjectList", 0x20, 0x534fc0, 0, 0 },
    { "beCriSfpData", "beBinDataObject", 0x30, 0x535030, mo_f57, 4 },
    { "beCriSndf", "igObject", 0x20, 0x534dd0, mo_f58, 3 },
    { "beCriVolume", "igObject", 0x20, 0x535090, mo_f59, 6 },
    { "beDBManager", "beBaseInfoManager", 0x20, 0x53bb70, 0, 0 },
    { "beDBManagerInfo", "beBaseInfo", 0x20, 0x5350f0, mo_f61, 1 },
    { "beDataBase", "igObject", 0x40, 0x535160, mo_f62, 12 },
    { "beDataBaseList", "igObjectList", 0x20, 0x5351c0, 0, 0 },
    { "beDataObjBool", "igNamedObject", 0x10, 0x5352f0, mo_f64, 1 },
    { "beDataObjBoolList", "igNamedObject", 0x10, 0x535350, mo_f65, 1 },
    { "beDataObjFloatList", "igNamedObject", 0x10, 0x5354d0, mo_f66, 1 },
    { "beDataObjInt", "igNamedObject", 0x10, 0x535230, mo_f67, 1 },
    { "beDataObjIntList", "igNamedObject", 0x10, 0x535290, mo_f68, 1 },
    { "beDataObjList", "igObjectList", 0x20, 0x535530, 0, 0 },
    { "beDataObjListList", "igObjectList", 0x20, 0x5355a0, 0, 0 },
    { "beDataObjObjectList", "igNamedObject", 0x10, 0x535470, mo_f71, 1 },
    { "beDataObjString", "igNamedObject", 0x10, 0x5353b0, mo_f72, 1 },
    { "beDataObjStringList", "igNamedObject", 0x10, 0x535410, mo_f73, 1 },
    { "beDemoKeepMes", "igObject", 0x30, 0x535610, mo_f74, 7 },
    { "beDemoKeepMesList", "igObjectList", 0x20, 0x535670, 0, 0 },
    { "beDemoManager", "igInfoManager", 0x30, 0x53a460, mo_f76, 7 },
    { "beDemoManagerWork", "igObject", 0x10, 0x5356e0, mo_f77, 2 },
    { "beDemoManagerWorkList", "igObjectList", 0x20, 0x535740, 0, 0 },
    { "beFile", "igObject", 0x10, 0x535810, 0, 0 },
    { "beFileChkObj", "igObject", 0x10, 0x5357b0, mo_f80, 1 },
    { "beFileListInfo", "igInfo", 0x20, 0x535870, mo_f81, 2 },
    { "beFileListInfoManager", "igInfoManager", 0x40, 0x53a4e0, mo_f82, 12 },
    { "beFont", "beBaseInfoManager", 0x50, 0x53a5c0, mo_f83, 10 },
    { "beFontGeomAttrPair", "igObject", 0x20, 0x5358e0, mo_f84, 3 },
    { "beFontGeomAttrPairList", "igObjectList", 0x20, 0x535940, 0, 0 },
    { "beFontImage", "igBitmapFont", 0x30, 0x5359b0, 0, 0 },
    { "beFontImageList", "igObjectList", 0x20, 0x535a90, 0, 0 },
    { "beFontInfo", "beBaseInfo", 0x20, 0x535bd0, mo_f88, 1 },
    { "beFontInfoData", "beBaseInfoData", 0x30, 0x535b70, mo_f89, 7 },
    { "beGenerater", "beBaseInfoManager", 0x30, 0x53a660, mo_f90, 2 },
    { "beGeneraterData", "igNamedObject", 0x50, 0x535eb0, mo_f91, 12 },
    { "beGeneraterDataList", "igObjectList", 0x20, 0x535f10, 0, 0 },
    { "beGeneraterInfo", "beBaseInfo", 0x20, 0x535f80, mo_f93, 1 },
    { "beGeneraterInfoRam", "beBaseInfoRam", 0x30, 0x535ff0, mo_f94, 1 },
    { "beGeneraterInfoWork", "igObject", 0x30, 0x536050, mo_f95, 9 },
    { "beGeneraterItemData", "igNamedObject", 0x10, 0x535d10, mo_f96, 1 },
    { "beGeneraterItemDataList", "igObjectList", 0x20, 0x535d70, 0, 0 },
    { "beGeneraterItemDataOne", "igNamedObject", 0x20, 0x535c40, mo_f98, 3 },
    { "beGeneraterItemDataOneList", "igObjectList", 0x20, 0x535ca0, 0, 0 },
    { "beGeneraterPlayerData", "igObject", 0x20, 0x535de0, mo_f100, 4 },
    { "beGeneraterPlayerDataList", "igObjectList", 0x20, 0x535e40, 0, 0 },
    { "beGroupKeep", "igGroup", 0x20, 0x5360b0, 0, 0 },
    { "beGroupKeepList", "igObjectList", 0x20, 0x536150, 0, 0 },
    { "beHitLandDeliv", "beBaseInfoManager", 0x20, 0x53a700, 0, 0 },
    { "beHitLandDelivInfo", "beBaseInfo", 0x20, 0x5361c0, 0, 0 },
    { "beHitLandDelivInfoRam", "beBaseInfoRam", 0x70, 0x536230, mo_f106, 9 },
    { "beHitLandModel", "beBaseInfoManager", 0x70, 0x53a810, mo_f107, 5 },
    { "beHitLandModelInfo", "beBaseInfo", 0x30, 0x5363d0, mo_f108, 4 },
    { "beHitLandModelInfoRam", "beBaseInfoRam", 0x30, 0x536440, 0, 0 },
    { "beHitLandModelOrder", "igObject", 0x40, 0x53a7a0, mo_f110, 9 },
    { "beHitLandModelTraversal", "igIntersectTraversal", 0x50, 0x536360, mo_f111, 1 },
    { "beHitLandResultData", "igObject", 0x10, 0x536290, mo_f112, 2 },
    { "beHitLandResultDataList", "igObjectList", 0x20, 0x5362f0, 0, 0 },
    { "beKeyboardReceiver", "igEventReceiver", 0x10, 0x53a8b0, mo_f114, 1 },
    { "beLOA", "igGroup", 0x60, 0x5364a0, mo_f115, 10 },
    { "beLayerCtl", "beBaseInfoManager", 0x30, 0x53a940, mo_f116, 2 },
    { "beLayerGroup", "igNamedObject", 0x10, 0x536540, 0, 0 },
    { "beLayerGroupList", "igObjectList", 0x20, 0x5365a0, 0, 0 },
    { "beLayerInfo", "beBaseInfo", 0x20, 0x536610, mo_f119, 1 },
    { "beLayerInfoRam", "beBaseInfoRam", 0x30, 0x536680, 0, 0 },
    { "beLightCtrl", "beBaseInfoManager", 0x20, 0x53c260, 0, 0 },
    { "beLightCtrlInfo", "beBaseInfo", 0x20, 0x5366e0, mo_f122, 1 },
    { "beLoadIntf2ComMdlData", "igObject", 0x20, 0x53c810, mo_f123, 3 },
    { "beLoadIntf2ComMdlDataList", "igObjectList", 0x20, 0x53c870, 0, 0 },
    { "beLoadingNode", "beNodeAnim", 0x80, 0x538110, mo_f125, 2 },
    { "beLua", "igInfoManager", 0x20, 0x53a9e0, mo_f126, 4 },
    { "beLuaData", "igNamedObject", 0x10, 0x536890, mo_f127, 1 },
    { "beLuaDataList", "igObjectList", 0x20, 0x5368f0, 0, 0 },
    { "beLuaDataObject", "igObject", 0x10, 0x5367c0, mo_f129, 2 },
    { "beLuaDataObjectist", "igObjectList", 0x20, 0x536820, 0, 0 },
    { "beLuaInfo", "beBaseInfo", 0x20, 0x536960, mo_f131, 1 },
    { "beLuaState", "igLuaState", 0x20, 0x53aa60, mo_f132, 1 },
    { "beMatCtrl", "beBaseInfoManager", 0x50, 0x53aad0, mo_f133, 9 },
    { "beMatCtrlData", "igNamedObject", 0x10, 0x5369d0, mo_f134, 1 },
    { "beMatCtrlDataList", "igObjectList", 0x20, 0x536a30, 0, 0 },
    { "beMatCtrlInfo", "beBaseInfo", 0x30, 0x536b70, mo_f136, 3 },
    { "beMatCtrlInfoRam", "beBaseInfoRam", 0x30, 0x536be0, mo_f137, 1 },
    { "beMatCtrlInfoWork", "igObject", 0x10, 0x536c40, mo_f138, 2 },
    { "beMatCtrlSearch", "igObject", 0x20, 0x536aa0, mo_f139, 5 },
    { "beMatCtrlSearchList", "igObjectList", 0x20, 0x536b00, 0, 0 },
    { "beMemory", "igInfoManager", 0x30, 0x53c1e0, mo_f141, 5 },
    { "beMessenger", "igInfoManager", 0x40, 0x53ab70, mo_f142, 8 },
    { "beMessengerArgData", "igObject", 0x30, 0x536ca0, mo_f143, 10 },
    { "beMessengerArgDataList", "igObjectList", 0x20, 0x536d00, 0, 0 },
    { "beMessengerDelay", "igObject", 0x30, 0x536d70, mo_f145, 7 },
    { "beMessengerDelayList", "igObjectList", 0x20, 0x536dd0, 0, 0 },
    { "beMessengerGroup", "igNamedObject", 0x20, 0x536e40, mo_f147, 3 },
    { "beMessengerGroupList", "igObjectList", 0x20, 0x536ea0, 0, 0 },
    { "beMessengerWork", "igObject", 0x20, 0x536f10, mo_f149, 6 },
    { "beMessengerWorkList", "igObjectList", 0x20, 0x536f70, 0, 0 },
    { "beMeterCtrl", "beBaseInfoManager", 0x20, 0x53abf0, 0, 0 },
    { "beMeterCtrlInfo", "beBaseInfo", 0x20, 0x537040, mo_f152, 1 },
    { "beMeterCtrlInfoList", "igObjectList", 0x20, 0x5370b0, 0, 0 },
    { "beMeterCtrlNode", "igGroup", 0x40, 0x537120, mo_f154, 3 },
    { "beMeterCtrlOneData", "igNamedObject", 0x50, 0x536fe0, mo_f155, 14 },
    { "beModelCtrl", "beBaseInfoManager", 0x30, 0x53adb0, mo_f156, 3 },
    { "beModelCtrlACTION", "igNamedObject", 0x10, 0x5373b0, 0, 0 },
    { "beModelCtrlAIData", "igNamedObject", 0x20, 0x537830, mo_f158, 3 },
    { "beModelCtrlAIDataList", "igObjectList", 0x20, 0x537890, 0, 0 },
    { "beModelCtrlAIMAP", "igNamedObject", 0x10, 0x537710, 0, 0 },
    { "beModelCtrlAIMap", "igNamedObject", 0x40, 0x537900, mo_f161, 10 },
    { "beModelCtrlAIMapList", "igObjectList", 0x20, 0x537960, 0, 0 },
    { "beModelCtrlCTRL", "igNamedObject", 0x10, 0x537470, 0, 0 },
    { "beModelCtrlData", "igNamedObject", 0x10, 0x5371c0, mo_f164, 1 },
    { "beModelCtrlDataList", "igObjectList", 0x20, 0x537220, 0, 0 },
    { "beModelCtrlHITBOX", "igNamedObject", 0x30, 0x5377d0, mo_f166, 5 },
    { "beModelCtrlInfo", "beBaseInfo", 0x20, 0x537c10, mo_f167, 1 },
    { "beModelCtrlInfoAI", "igObject", 0x30, 0x537e20, mo_f168, 5 },
    { "beModelCtrlInfoDataAIH", "beBaseInfoData", 0x30, 0x537a30, mo_f169, 8 },
    { "beModelCtrlInfoDataAIM", "beBaseInfoData", 0x20, 0x5379d0, mo_f170, 1 },
    { "beModelCtrlInfoDataHit", "beBaseInfoData", 0x20, 0x537a90, mo_f171, 4 },
    { "beModelCtrlInfoDataSeq", "beBaseInfoData", 0x20, 0x537af0, mo_f172, 1 },
    { "beModelCtrlInfoDataTrc", "beBaseInfoData", 0x20, 0x537b50, mo_f173, 1 },
    { "beModelCtrlInfoHitBody", "igObject", 0x30, 0x537dc0, mo_f174, 7 },
    { "beModelCtrlInfoList", "igObjectList", 0x20, 0x537c80, 0, 0 },
    { "beModelCtrlInfoRamData", "beBaseInfoData", 0x20, 0x537bb0, mo_f176, 2 },
    { "beModelCtrlInfoRideOn", "igObject", 0x60, 0x537e80, mo_f177, 4 },
    { "beModelCtrlInfoRideOn2", "beModelCtrlInfoRideOn", 0x60, 0x53ad50, mo_f178, 1 },
    { "beModelCtrlInfoRideOn3", "beModelCtrlInfoRideOn", 0x70, 0x53acf0, mo_f179, 5 },
    { "beModelCtrlInfoRideOn4", "beModelCtrlInfoRideOn", 0x80, 0x53ac90, mo_f180, 5 },
    { "beModelCtrlInfoWork", "igObject", 0xf0, 0x537ee0, mo_f181, 50 },
    { "beModelCtrlJUMP", "igNamedObject", 0x10, 0x537410, 0, 0 },
    { "beModelCtrlLABEL", "igNamedObject", 0x10, 0x5372f0, 0, 0 },
    { "beModelCtrlLABELCTRL", "igNamedObject", 0x10, 0x537350, mo_f184, 1 },
    { "beModelCtrlLUACALL", "igNamedObject", 0x10, 0x537290, mo_f185, 1 },
    { "beModelCtrlMOVE", "igNamedObject", 0x20, 0x537530, mo_f186, 2 },
    { "beModelCtrlMOVEEX", "igNamedObject", 0x30, 0x537590, mo_f187, 6 },
    { "beModelCtrlMOVERL", "igNamedObject", 0x20, 0x5375f0, mo_f188, 2 },
    { "beModelCtrlMSGBOX", "igNamedObject", 0x10, 0x5374d0, 0, 0 },
    { "beModelCtrlMUTEKI", "igNamedObject", 0x10, 0x537770, mo_f190, 1 },
    { "beModelCtrlMoveObject", "igObject", 0x30, 0x537cf0, mo_f191, 9 },
    { "beModelCtrlMoveObjectList", "igObjectList", 0x20, 0x537d50, 0, 0 },
    { "beModelCtrlNode2", "igTransform", 0x90, 0x537f40, mo_f193, 4 },
    { "beModelCtrlPDMOVE", "igNamedObject", 0x20, 0x537650, mo_f194, 2 },
    { "beModelCtrlSCEffect", "beModelCtrlSubComBase", 0x40, 0x53aef0, mo_f195, 7 },
    { "beModelCtrlSCHitBox", "beModelCtrlSubComBase", 0x40, 0x53af60, mo_f196, 6 },
    { "beModelCtrlSCSound", "beModelCtrlSubComBase", 0x20, 0x53ae80, mo_f197, 2 },
    { "beModelCtrlSubCom", "igObject", 0x10, 0x537fe0, mo_f198, 1 },
    { "beModelCtrlSubComBase", "igObject", 0x20, 0x0, mo_f199, 3 },
    { "beModelCtrlWCHECK", "igNamedObject", 0x10, 0x5376b0, 0, 0 },
    { "beMovie", "beBaseInfoManager", 0x30, 0x53bad0, mo_f201, 2 },
    { "beMovieInfo", "beBaseInfo", 0x20, 0x5380a0, 0, 0 },
    { "beMovieInfoData", "beBaseInfoData", 0x20, 0x538040, mo_f203, 3 },
    { "beNDMWAfsSetup", "igInfoManager", 0x20, 0x53dfa0, mo_f204, 4 },
    { "beNDMWAfsSetupData", "igNamedObject", 0x10, 0x53c3a0, mo_f205, 1 },
    { "beNDMWAfsSetupDataList", "igObjectList", 0x20, 0x53c400, 0, 0 },
    { "beNDMWAfsSetupInfo", "igInfo", 0x20, 0x53c470, mo_f207, 2 },
    { "beNDMWAfsStageLoad", "igAction", 0x10, 0x53df40, mo_f208, 2 },
    { "beNDMWDegiData", "igObject", 0x50, 0x53c9a0, mo_f209, 13 },
    { "beNDMWDegiDataList", "igObjectList", 0x20, 0x53ca00, 0, 0 },
    { "beNDMWGameRam", "beBaseInfoManager", 0x50, 0x53ea40, mo_f211, 11 },
    { "beNDMWGameRamInfo", "beBaseInfo", 0x20, 0x53c4e0, 0, 0 },
    { "beNDMWGameRamInfoRam", "beBaseInfoRam", 0x30, 0x53c550, 0, 0 },
    { "beNDMWItemAbilityChip", "beNDMWItemBase", 0x20, 0x540810, 0, 0 },
    { "beNDMWItemBase", "igObject", 0x20, 0x0, mo_f215, 3 },
    { "beNDMWItemBaseList", "igObjectList", 0x20, 0x53c6e0, 0, 0 },
    { "beNDMWItemBlueArmor", "beNDMWItemRevisionPocketBase", 0x20, 0x5408f0, 0, 0 },
    { "beNDMWItemDisk", "beNDMWItemBase", 0x20, 0x5407a0, mo_f218, 1 },
    { "beNDMWItemImportant", "beNDMWItemBase", 0x20, 0x5406c0, 0, 0 },
    { "beNDMWItemInstant", "beNDMWItemBase", 0x20, 0x540730, mo_f220, 1 },
    { "beNDMWItemRevisionBase", "beNDMWItemBase", 0x20, 0x0, mo_f221, 1 },
    { "beNDMWItemRevisionPocketBase", "beNDMWItemRevisionBase", 0x20, 0x0, mo_f222, 1 },
    { "beNDMWItemWaza", "beNDMWItemBase", 0x20, 0x540650, mo_f223, 1 },
    { "beNDMWItemWeapon", "beNDMWItemRevisionPocketBase", 0x20, 0x540960, 0, 0 },
    { "beNDMWItemYellowArmor", "beNDMWItemRevisionBase", 0x20, 0x540880, 0, 0 },
    { "beNDMWListCtrl", "beNDMWWindowCtrl", 0x60, 0x53f2c0, mo_f226, 3 },
    { "beNDMWLoadCtrl2", "beBaseInfoManager", 0x30, 0x53e900, mo_f227, 3 },
    { "beNDMWLoadCtrl2CommonIntf", "beBaseInfoData", 0x50, 0x53ce00, mo_f228, 14 },
    { "beNDMWLoadCtrl2CtrlData", "beBaseInfoData", 0x30, 0x53c750, mo_f229, 5 },
    { "beNDMWLoadCtrl2Info", "beBaseInfo", 0x20, 0x53ce60, mo_f230, 1 },
    { "beNDMWLoadIntf2", "beBaseInfoManager", 0x30, 0x53e860, mo_f231, 4 },
    { "beNDMWLoadIntf2ChrDataSel", "beBaseInfoData", 0x50, 0x53d1e0, mo_f232, 16 },
    { "beNDMWLoadIntf2ComMdlCtrl", "beBaseInfoData", 0x30, 0x53c8e0, mo_f233, 4 },
    { "beNDMWLoadIntf2CtrlData", "beBaseInfoData", 0x40, 0x53ced0, mo_f234, 16 },
    { "beNDMWLoadIntf2DataSelIntf", "beBaseInfoData", 0x60, 0x53d0c0, mo_f235, 23 },
    { "beNDMWLoadIntf2DegiState", "igObject", 0x50, 0x53cf90, mo_f236, 16 },
    { "beNDMWLoadIntf2DegiStateCtrl", "beBaseInfoData", 0x20, 0x53d060, mo_f237, 1 },
    { "beNDMWLoadIntf2DegiStateList", "igObjectList", 0x20, 0x53cff0, 0, 0 },
    { "beNDMWLoadIntf2Diffselect", "beBaseInfoData", 0x50, 0x53d120, mo_f239, 16 },
    { "beNDMWLoadIntf2Info", "beBaseInfo", 0x20, 0x53d2a0, 0, 0 },
    { "beNDMWLoadIntf2MakeChr", "beBaseInfoData", 0x40, 0x53cf30, mo_f241, 4 },
    { "beNDMWLoadIntf2MesWin", "beBaseInfoData", 0x40, 0x53c940, mo_f242, 18 },
    { "beNDMWLoadIntf2NameSel", "beBaseInfoData", 0x70, 0x53d240, mo_f243, 25 },
    { "beNDMWLoadIntf2SelSlot", "beBaseInfoData", 0x60, 0x53d180, mo_f244, 22 },
    { "beNDMWLoadIntf2TextOrder", "beBaseInfoData", 0x20, 0x53c7b0, mo_f245, 2 },
    { "beNDMWLoadSavePlWork", "igObject", 0x40, 0x53ccd0, mo_f246, 14 },
    { "beNDMWLoadSavePlWorkList", "igObjectList", 0x20, 0x53cd30, 0, 0 },
    { "beNDMWLoadSlotPlayer", "igObject", 0x20, 0x53ca70, mo_f248, 3 },
    { "beNDMWLoadSlotPlayerList", "igObjectList", 0x20, 0x53cad0, 0, 0 },
    { "beNDMWLogo", "beBaseInfoManager", 0x50, 0x5409d0, mo_f250, 11 },
    { "beNDMWLogoCtrlData", "beBaseInfoData", 0x20, 0x53d310, mo_f251, 4 },
    { "beNDMWLogoInfo", "beBaseInfo", 0x20, 0x53d370, 0, 0 },
    { "beNDMWMcSlot", "igObject", 0x20, 0x0, mo_f253, 5 },
    { "beNDMWMcSlotGC", "beNDMWMcSlot", 0x20, 0x53cba0, mo_f254, 2 },
    { "beNDMWMcSlotList", "igObjectList", 0x20, 0x53cc60, 0, 0 },
    { "beNDMWMcSlotPS2", "beNDMWMcSlot", 0x20, 0x53cb40, 0, 0 },
    { "beNDMWMcSlotXbox", "beNDMWMcSlot", 0x20, 0x53cc00, mo_f257, 1 },
    { "beNDMWMcUtilCtrl", "igObject", 0x40, 0x53cda0, mo_f258, 17 },
    { "beNDMWMdlEBullet", "beModelCtrl", 0x30, 0x53e210, 0, 0 },
    { "beNDMWMdlEffect", "beModelCtrl", 0x30, 0x53e2e0, 0, 0 },
    { "beNDMWMdlEnemy", "beNDMWMdlPEBase", 0x30, 0x53e3b0, 0, 0 },
    { "beNDMWMdlEnemyInfoWork", "beNDMWMdlPEBaseInfoWork", 0x120, 0x53d3e0, 0, 0 },
    { "beNDMWMdlItem", "beModelCtrl", 0x40, 0x540450, mo_f263, 2 },
    { "beNDMWMdlItemInfoWork", "beModelCtrlInfoWork", 0x110, 0x53d440, mo_f264, 8 },
    { "beNDMWMdlMapBase", "beModelCtrl", 0x30, 0x540a70, 0, 0 },
    { "beNDMWMdlMapCursor", "beModelCtrl", 0x30, 0x540b40, 0, 0 },
    { "beNDMWMdlObject", "beModelCtrl", 0x30, 0x53e480, 0, 0 },
    { "beNDMWMdlPBullet", "beModelCtrl", 0x30, 0x53e550, 0, 0 },
    { "beNDMWMdlPEBase", "beModelCtrl", 0x30, 0x540580, 0, 0 },
    { "beNDMWMdlPEBaseInfoWork", "beModelCtrlInfoWork", 0x120, 0x540520, mo_f270, 10 },
    { "beNDMWMdlPlayer", "beNDMWMdlPEBase", 0x40, 0x53e620, mo_f271, 3 },
    { "beNDMWMdlPlayer2", "beModelCtrl", 0x30, 0x53e6f0, mo_f272, 1 },
    { "beNDMWMdlPlayer2InfoWork", "beModelCtrlInfoWork", 0x100, 0x53d500, mo_f273, 4 },
    { "beNDMWMdlPlayerInfoWork", "beNDMWMdlPEBaseInfoWork", 0x130, 0x53d4a0, mo_f274, 8 },
    { "beNDMWPanelObject", "igObject", 0x40, 0x53d560, mo_f275, 16 },
    { "beNDMWPanelObjectItem", "beNDMWPanelObject", 0x50, 0x53e130, mo_f276, 2 },
    { "beNDMWPanelObjectStat", "beNDMWPanelObject", 0x50, 0x53e0c0, mo_f277, 3 },
    { "beNDMWPanelObjectWaza", "beNDMWPanelObject", 0x50, 0x53e1a0, mo_f278, 2 },
    { "beNDMWPanelWaza", "beBaseInfoManager", 0x30, 0x53e020, mo_f279, 1 },
    { "beNDMWPanelWazaInfo", "beBaseInfo", 0x20, 0x53d690, 0, 0 },
    { "beNDMWPanelWazaInfoRam", "beBaseInfoRam", 0x30, 0x53d630, mo_f281, 1 },
    { "beNDMWPanelWazaInfoWork", "igObject", 0x30, 0x53d5d0, mo_f282, 11 },
    { "beNDMWSaveCtrl", "beBaseInfoManager", 0x30, 0x53eae0, mo_f283, 1 },
    { "beNDMWSaveCtrlCtrlData", "beBaseInfoData", 0x30, 0x53d700, mo_f284, 7 },
    { "beNDMWSaveCtrlInfo", "beBaseInfo", 0x20, 0x53d760, 0, 0 },
    { "beNDMWSaveIntf", "beBaseInfoManager", 0x30, 0x53eb80, mo_f286, 3 },
    { "beNDMWSaveIntfComMdlCtrl", "beBaseInfoData", 0x30, 0x53d900, mo_f287, 4 },
    { "beNDMWSaveIntfCtrlData", "beBaseInfoData", 0x40, 0x53d7d0, mo_f288, 15 },
    { "beNDMWSaveIntfInfo", "beBaseInfo", 0x20, 0x53d960, 0, 0 },
    { "beNDMWShinkaCtrl", "igObject", 0x20, 0x53c680, mo_f290, 6 },
    { "beNDMWShinkaObject", "igObject", 0x60, 0x53c5b0, mo_f291, 19 },
    { "beNDMWShinkaObjectList", "igObjectList", 0x20, 0x53c610, 0, 0 },
    { "beNDMWShopCtrl00", "beNDMWWindowCtrl", 0x60, 0x53feb0, 0, 0 },
    { "beNDMWShopCtrl10", "beNDMWWindowCtrl", 0x60, 0x53fe50, mo_f294, 2 },
    { "beNDMWShopCtrl30", "beNDMWWindowCtrl", 0x60, 0x53fdf0, mo_f295, 1 },
    { "beNDMWShopCtrl40", "beNDMWWindowCtrl", 0x60, 0x53fd90, mo_f296, 1 },
    { "beNDMWShopCtrl50", "beNDMWWindowCtrl", 0x70, 0x53fd30, mo_f297, 5 },
    { "beNDMWShopCtrlA0", "beNDMWWindowCtrl", 0x60, 0x53fc70, mo_f298, 2 },
    { "beNDMWShopCtrlA1", "beNDMWWindowCtrl", 0x60, 0x53fc10, mo_f299, 2 },
    { "beNDMWShopCtrlA2", "beNDMWWindowCtrl", 0x60, 0x53fbb0, 0, 0 },
    { "beNDMWShopCtrlDeviceSell", "beNDMWListCtrl", 0x70, 0x53f9b0, mo_f301, 1 },
    { "beNDMWShopCtrlDigilabo", "beNDMWWindowCtrl", 0x70, 0x53fae0, mo_f302, 7 },
    { "beNDMWShopCtrlDiskSell", "beNDMWWindowCtrl", 0x70, 0x53f950, mo_f303, 5 },
    { "beNDMWShopCtrlEditBit", "beNDMWWindowCtrl", 0x60, 0x53fa80, mo_f304, 2 },
    { "beNDMWShopCtrlEvolve", "beNDMWListCtrl", 0x70, 0x53fb40, mo_f305, 1 },
    { "beNDMWShopCtrlSales", "beNDMWListCtrl", 0x70, 0x53f8e0, mo_f306, 2 },
    { "beNDMWShopCtrlSell", "beNDMWWindowCtrl", 0x60, 0x53fa20, 0, 0 },
    { "beNDMWShopCtrlXdataChip", "beNDMWListCtrl", 0x70, 0x53f870, mo_f308, 1 },
    { "beNDMWShopDevice", "beNDMWListCtrl", 0x70, 0x53f800, mo_f309, 1 },
    { "beNDMWShopJunk", "beNDMWWindowCtrl", 0x60, 0x53fcd0, mo_f310, 3 },
    { "beNDMWShopSelect00", "beNDMWWindowSelect", 0x80, 0x540290, mo_f311, 1 },
    { "beNDMWShopSelect01", "beNDMWWindowSelect", 0x70, 0x540220, 0, 0 },
    { "beNDMWShopSelect02", "beNDMWWindowSelect", 0x80, 0x5401b0, mo_f313, 1 },
    { "beNDMWShopSelect03", "beNDMWWindowSelect", 0x70, 0x540140, 0, 0 },
    { "beNDMWShopSelect11", "beNDMWWindowSelect", 0x70, 0x5400d0, 0, 0 },
    { "beNDMWShopSelect34", "beNDMWWindowSelect", 0x70, 0x540060, 0, 0 },
    { "beNDMWShopSelect52", "beNDMWWindowSelect", 0x70, 0x53fff0, 0, 0 },
    { "beNDMWShopSelectA0", "beNDMWWindowSelect", 0x70, 0x53ff80, 0, 0 },
    { "beNDMWShopSelectB0", "beNDMWWindowSelect", 0x70, 0x53ff10, 0, 0 },
    { "beNDMWShopTitle00", "beNDMWWindowTitle", 0x50, 0x5403e0, 0, 0 },
    { "beNDMWShopTitle01", "beNDMWWindowTitle", 0x50, 0x540370, 0, 0 },
    { "beNDMWShopTitle03", "beNDMWWindowTitle", 0x50, 0x540300, 0, 0 },
    { "beNDMWStageCtl", "beBaseInfoManager", 0x30, 0x53dea0, mo_f323, 1 },
    { "beNDMWStageCtlInfo", "beBaseInfo", 0x20, 0x53d9d0, 0, 0 },
    { "beNDMWStageCtlInfoRam", "beBaseInfoRam", 0x30, 0x53da40, 0, 0 },
    { "beNDMWStatus", "beBaseInfoManager", 0x30, 0x53e7c0, mo_f326, 3 },
    { "beNDMWStatusCtrl00", "beNDMWWindowCtrl", 0x60, 0x53f260, mo_f327, 1 },
    { "beNDMWStatusCtrlBaseEquip", "beNDMWWindowCtrl", 0x80, 0x53f150, mo_f328, 10 },
    { "beNDMWStatusCtrlBit", "beNDMWWindowCtrl", 0x60, 0x53ed50, mo_f329, 1 },
    { "beNDMWStatusCtrlD0", "beNDMWListCtrl", 0x80, 0x53eed0, mo_f330, 8 },
    { "beNDMWStatusCtrlDisk", "beNDMWWindowCtrl", 0x70, 0x53edb0, mo_f331, 6 },
    { "beNDMWStatusCtrlEquip", "beNDMWWindowCtrl", 0x60, 0x53f200, mo_f332, 1 },
    { "beNDMWStatusCtrlFlag", "beNDMWWindowCtrl", 0x60, 0x53ee10, mo_f333, 1 },
    { "beNDMWStatusCtrlFolder", "beNDMWWindowCtrl", 0x60, 0x53ee70, mo_f334, 1 },
    { "beNDMWStatusCtrlSendBit", "beNDMWWindowCtrl", 0x70, 0x53ecf0, mo_f335, 4 },
    { "beNDMWStatusCtrlSkill", "beNDMWListCtrl", 0x70, 0x53ec80, mo_f336, 3 },
    { "beNDMWStatusInfo", "beBaseInfo", 0x20, 0x53dbc0, 0, 0 },
    { "beNDMWStatusInfoRam", "beBaseInfoRam", 0x30, 0x53db60, mo_f338, 1 },
    { "beNDMWStatusInfoWork", "igObject", 0x30, 0x53db00, mo_f339, 7 },
    { "beNDMWStatusMainSlot", "beNDMWStatusCtrlBaseEquip", 0x80, 0x53eff0, 0, 0 },
    { "beNDMWStatusPowerSocket", "beNDMWStatusCtrlBaseEquip", 0x80, 0x53f0a0, 0, 0 },
    { "beNDMWStatusSelect00", "beNDMWWindowSelect", 0x70, 0x53f480, 0, 0 },
    { "beNDMWStatusSelect01", "beNDMWWindowSelect", 0x70, 0x53f410, 0, 0 },
    { "beNDMWStatusSelectE0", "beNDMWWindowSelect", 0x70, 0x53f3a0, 0, 0 },
    { "beNDMWStatusSelectE1", "beNDMWWindowSelect", 0x70, 0x53f330, 0, 0 },
    { "beNDMWStatusSubMenu", "beNDMWWindowCtrl", 0x70, 0x53ec20, mo_f346, 5 },
    { "beNDMWStatusSubSlot", "beNDMWStatusCtrlBaseEquip", 0x80, 0x53ef40, 0, 0 },
    { "beNDMWStatusTitle00", "beNDMWWindowTitle", 0x50, 0x53f720, 0, 0 },
    { "beNDMWStatusTitle01", "beNDMWWindowTitle", 0x50, 0x53f6b0, 0, 0 },
    { "beNDMWStatusTitle02", "beNDMWWindowTitle", 0x50, 0x53f640, 0, 0 },
    { "beNDMWStatusTitle03", "beNDMWWindowTitle", 0x50, 0x53f5d0, 0, 0 },
    { "beNDMWStatusTitle04", "beNDMWWindowTitle", 0x50, 0x53f560, 0, 0 },
    { "beNDMWTitle2", "beBaseInfoManager", 0x30, 0x53e9a0, mo_f353, 4 },
    { "beNDMWTitle2CtrlData", "beBaseInfoData", 0x30, 0x53dc90, mo_f354, 8 },
    { "beNDMWTitle2Info", "beBaseInfo", 0x20, 0x53dd50, 0, 0 },
    { "beNDMWTitle2Option", "beBaseInfoData", 0x40, 0x53dcf0, mo_f356, 10 },
    { "beNDMWWindow", "igObject", 0x50, 0x53dc30, mo_f357, 18 },
    { "beNDMWWindowCtrl", "beNDMWWindow", 0x60, 0x53daa0, mo_f358, 1 },
    { "beNDMWWindowList", "igObjectList", 0x20, 0x53ddc0, 0, 0 },
    { "beNDMWWindowSelect", "beNDMWWindow", 0x70, 0x53f4f0, mo_f360, 6 },
    { "beNDMWWindowTitle", "beNDMWWindow", 0x50, 0x53f790, 0, 0 },
    { "beNodeAnim", "igGroup", 0x70, 0x5381b0, mo_f362, 10 },
    { "beNumVerData", "igObject", 0x10, 0x538400, mo_f363, 2 },
    { "beNumVerDataList", "igObjectList", 0x20, 0x538460, 0, 0 },
    { "beNumVerInsideData", "igObject", 0x10, 0x538330, mo_f365, 2 },
    { "beNumVerInsideDataList", "igObjectList", 0x20, 0x538390, 0, 0 },
    { "beNumberCtrl", "beBaseInfoManager", 0x20, 0x53b890, 0, 0 },
    { "beNumberCtrlInfo", "beBaseInfo", 0x20, 0x538250, 0, 0 },
    { "beNumberCtrlInfoList", "igObjectList", 0x20, 0x5382c0, 0, 0 },
    { "beNumberCtrlInfoRam", "beBaseInfoRam", 0x50, 0x5384d0, mo_f370, 6 },
    { "beNumberCtrlInfoWork", "igObject", 0x20, 0x538530, mo_f371, 3 },
    { "beOptInfo", "igInfo", 0x30, 0x538590, mo_f372, 4 },
    { "bePadData", "igObject", 0x70, 0x53afd0, mo_f373, 22 },
    { "bePadDataList", "igObjectList", 0x20, 0x538600, 0, 0 },
    { "bePadManager", "igInfoManager", 0x20, 0x53b030, mo_f375, 5 },
    { "beParticleCtrl2", "beBaseInfoManager", 0x20, 0x53b0b0, 0, 0 },
    { "beParticleCtrl2Info", "beBaseInfo", 0x30, 0x538670, mo_f377, 4 },
    { "beParticleCtrl2InfoRam", "beBaseInfoRam", 0x40, 0x538740, mo_f378, 3 },
    { "beParticleCtrl2InfoWork", "igObject", 0x20, 0x5386e0, mo_f379, 2 },
    { "bePlaySE", "igObject", 0x20, 0x539220, mo_f380, 2 },
    { "bePlaySEList", "igObjectList", 0x20, 0x539280, 0, 0 },
    { "bePoint01", "beBaseInfoManager", 0x30, 0x53b150, mo_f382, 1 },
    { "bePoint01Info", "beBaseInfo", 0x30, 0x5387a0, mo_f383, 2 },
    { "beResetNode", "igGroup", 0x30, 0x538810, mo_f384, 2 },
    { "beSaveApi", "igObject", 0x40, 0x53c070, mo_f385, 13 },
    { "beSaveDataDeliver", "igObject", 0x10, 0x538910, mo_f386, 2 },
    { "beSaveIntfComMdlData", "igObject", 0x20, 0x53d830, mo_f387, 3 },
    { "beSaveIntfComMdlDataList", "igObjectList", 0x20, 0x53d890, 0, 0 },
    { "beSaveMemoryObj", "igObject", 0x10, 0x53c0e0, mo_f389, 1 },
    { "beSaveUtil", "beBaseInfoManager", 0x30, 0x53c140, mo_f390, 2 },
    { "beSaveUtilInfo", "beBaseInfo", 0x20, 0x538da0, 0, 0 },
    { "beSaveUtilInfoRam", "beBaseInfoRam", 0x40, 0x538e10, mo_f392, 2 },
    { "beSeCtl", "beBaseInfoManager", 0x30, 0x53b1f0, mo_f393, 1 },
    { "beSeData", "igNamedObject", 0x20, 0x538e70, mo_f394, 2 },
    { "beSeDataList", "igObjectList", 0x20, 0x538ed0, 0, 0 },
    { "beSeInfo", "beBaseInfo", 0x20, 0x538fa0, 0, 0 },
    { "beSeInfoData", "beBaseInfoData", 0x20, 0x538f40, mo_f397, 1 },
    { "beSelectCtrl", "beBaseInfoManager", 0x30, 0x53b290, mo_f398, 2 },
    { "beSelectCtrlInfo", "beBaseInfo", 0x20, 0x5390d0, 0, 0 },
    { "beSelectCtrlInfoRamData", "beBaseInfoData", 0x20, 0x539070, mo_f400, 4 },
    { "beSelectCtrlInfoWork", "igObject", 0x30, 0x539010, mo_f401, 5 },
    { "beShadow01", "beBaseInfoManager", 0x30, 0x53b330, mo_f402, 2 },
    { "beShadow01Info", "beBaseInfo", 0x30, 0x539140, mo_f403, 3 },
    { "beShadow01InfoList", "igObjectList", 0x20, 0x5391b0, 0, 0 },
    { "beSound", "beBaseInfoManager", 0x30, 0x53b3d0, mo_f405, 3 },
    { "beSoundData", "beBaseInfoData", 0x20, 0x5392f0, mo_f406, 6 },
    { "beSoundInfo", "beBaseInfo", 0x30, 0x5393b0, mo_f407, 4 },
    { "beStaticInfo", "beBaseInfo", 0x20, 0x539420, 0, 0 },
    { "beStaticInfoCtl", "beBaseInfoManager", 0x30, 0x53b9b0, mo_f409, 1 },
    { "beSvConnectCheck", "beSaveApi", 0x40, 0x53bc10, 0, 0 },
    { "beSvDeliver", "igObject", 0x50, 0x5388b0, mo_f411, 18 },
    { "beSvEndApi", "beSaveApi", 0x40, 0x53bc80, 0, 0 },
    { "beSvFileFindApi", "beSaveApi", 0x40, 0x53bf90, 0, 0 },
    { "beSvFileMakeApi", "beSaveApi", 0x50, 0x53c000, mo_f414, 2 },
    { "beSvFormatApi", "beSaveApi", 0x40, 0x53bf20, 0, 0 },
    { "beSvGetFreeSizeApi", "beSaveApi", 0x50, 0x53bd60, mo_f416, 3 },
    { "beSvPlatBaseData", "igObject", 0x20, 0x538d40, mo_f417, 4 },
    { "beSvPlatDataGC", "beSvPlatBaseData", 0x90, 0x538b00, mo_f418, 13 },
    { "beSvPlatDataPC", "beSvPlatBaseData", 0x20, 0x538ce0, 0, 0 },
    { "beSvPlatDataPS2", "beSvPlatBaseData", 0xe0, 0x538bc0, mo_f420, 22 },
    { "beSvPlatDataXbox", "beSvPlatBaseData", 0x30, 0x538c80, mo_f421, 4 },
    { "beSvPs2McImage128k", "igObject", 0x10, 0x538b60, mo_f422, 2 },
    { "beSvReadMediaApi", "beSaveApi", 0x60, 0x53be40, mo_f423, 5 },
    { "beSvSlotData", "igObject", 0x20, 0x0, mo_f424, 5 },
    { "beSvSlotDataList", "igObjectList", 0x20, 0x538a90, 0, 0 },
    { "beSvSlotGC", "beSvSlotData", 0x20, 0x5389d0, 0, 0 },
    { "beSvSlotPS2", "beSvSlotData", 0x20, 0x538a30, 0, 0 },
    { "beSvSlotXbox", "beSvSlotData", 0x40, 0x538970, mo_f428, 4 },
    { "beSvStartApi", "beSaveApi", 0x40, 0x53bcf0, 0, 0 },
    { "beSvUseCheckApi", "beSaveApi", 0x40, 0x53beb0, 0, 0 },
    { "beSvWriteMediaApi", "beSaveApi", 0x50, 0x53bdd0, mo_f431, 2 },
    { "beSwitchCtrl", "beBaseInfoManager", 0x20, 0x53b470, 0, 0 },
    { "beSwitchCtrlInfo", "beBaseInfo", 0x20, 0x539490, mo_f433, 1 },
    { "beSystem", "igInfoManager", 0x70, 0x53b510, mo_f434, 26 },
    { "beTargetObj", "igInfoManager", 0x20, 0x53ba50, mo_f435, 3 },
    { "beTextureCtrl", "beBaseInfoManager", 0x30, 0x53c300, mo_f436, 2 },
    { "beTextureCtrlAttr", "igNamedObject", 0x10, 0x5395c0, mo_f437, 1 },
    { "beTextureCtrlData", "igNamedObject", 0x10, 0x539560, mo_f438, 1 },
    { "beTextureCtrlInfo", "beBaseInfo", 0x30, 0x539620, mo_f439, 2 },
    { "beTextureCtrlInfoList", "igObjectList", 0x20, 0x539690, 0, 0 },
    { "beTextureCtrlWork", "igObject", 0x10, 0x539500, mo_f441, 2 },
    { "beTimer", "igInfoManager", 0x30, 0x53b930, mo_f442, 5 },
    { "beTimerData", "igObject", 0x20, 0x539700, mo_f443, 4 },
    { "beTimerDataList", "igObjectList", 0x20, 0x539760, 0, 0 },
    { "beTransformSync", "igTransform", 0x70, 0x5397d0, mo_f445, 1 },
    { "beUnicode", "igObject", 0x10, 0x539870, 0, 0 },
    { "beUnicodeObj", "igNamedObject", 0x10, 0x53a560, mo_f447, 1 },
    { "beUnicodeObjList", "igObjectList", 0x20, 0x535b00, 0, 0 },
    { "beWaterMove", "igObject", 0x30, 0x539a10, mo_f449, 5 },
    { "beWaterMoveData", "igObject", 0x20, 0x539940, mo_f450, 3 },
    { "beWaterMoveDataList", "igObjectList", 0x20, 0x5399a0, 0, 0 },
    { "beWaterPlain", "beBaseInfoManager", 0x20, 0x53b590, 0, 0 },
    { "beWaterPlainInfo", "beBaseInfo", 0x20, 0x5398d0, 0, 0 },
    { "beWaterPlainInfoRam", "beBaseInfoRam", 0xc0, 0x539a70, mo_f454, 27 },
    { "beWeapon", "beBaseInfoManager", 0x30, 0x53b630, mo_f455, 1 },
    { "beWeaponAttachData", "igObject", 0x10, 0x539bb0, mo_f456, 2 },
    { "beWeaponAttachDataList", "igObjectList", 0x20, 0x539c10, 0, 0 },
    { "beWeaponInfo", "beBaseInfo", 0x30, 0x539d50, mo_f458, 3 },
    { "beWeaponInfoRam", "beBaseInfoRam", 0x30, 0x539e30, 0, 0 },
    { "beWeaponSeqData", "igNamedObject", 0x10, 0x539c80, mo_f460, 1 },
    { "beWeaponSeqDataList", "igObjectList", 0x20, 0x539ce0, 0, 0 },
    { "beXboxImage24k", "igObject", 0x10, 0x538c20, mo_f462, 2 },
    { "igAABox", "igVolume", 0x20, 0x5277e0, mo_f463, 2 },
    { "igAABoxList", "igObjectList", 0x20, 0x527840, 0, 0 },
    { "igAction", "igObject", 0x10, 0x0, 0, 0 },
    { "igActiveComponentsObserver", "igView", 0x20, 0x541020, mo_f466, 3 },
    { "igActor", "igGroup", 0x100, 0x5296b0, mo_f467, 13 },
    { "igActorInfo", "igInfo", 0x30, 0x5297c0, mo_f468, 5 },
    { "igActorList", "igObjectList", 0x20, 0x529750, 0, 0 },
    { "igActorManager", "igInfoManager", 0x40, 0x5429f0, mo_f470, 10 },
    { "igActorManagerParams", "igModel", 0x10, 0x541fe0, mo_f471, 2 },
    { "igAdx", "igObject", 0x10, 0x533790, 0, 0 },
    { "igAdxAfsFile", "igFileName", 0x20, 0x533b40, mo_f473, 2 },
    { "igAdxAfsFileList", "igObjectList", 0x20, 0x533c00, 0, 0 },
    { "igAdxAudio", "igObject", 0x30, 0x533730, mo_f475, 9 },
    { "igAdxFile", "igFile", 0x60, 0x5337f0, mo_f476, 14 },
    { "igAliasMemoryPool", "igMemoryPool", 0xc0, 0x5313a0, mo_f477, 14 },
    { "igAlphaFunctionAttr", "igVisualAttribute", 0x20, 0x524390, mo_f478, 2 },
    { "igAlphaStateAttr", "igVisualAttribute", 0x10, 0x524300, mo_f479, 1 },
    { "igAnimation", "igNamedObject", 0x40, 0x52a9b0, mo_f480, 8 },
    { "igAnimationBinding", "igObject", 0x20, 0x529b70, mo_f481, 5 },
    { "igAnimationBindingList", "igObjectList", 0x20, 0x529bd0, 0, 0 },
    { "igAnimationCombiner", "igAnimationSystem", 0x60, 0x529630, mo_f483, 14 },
    { "igAnimationCombinerBoneInfo", "igObject", 0x40, 0x529d30, mo_f484, 8 },
    { "igAnimationCombinerBoneInfoList", "igObjectList", 0x20, 0x529d90, 0, 0 },
    { "igAnimationCombinerBoneInfoListList", "igObjectList", 0x20, 0x529e00, 0, 0 },
    { "igAnimationCombinerBoneInfoPool", "igObjectPool", 0x20, 0x529e70, 0, 0 },
    { "igAnimationCombinerList", "igObjectList", 0x20, 0x529cc0, 0, 0 },
    { "igAnimationDatabase", "igInfo", 0x30, 0x5295c0, mo_f489, 5 },
    { "igAnimationHierarchy", "igNamedObject", 0x10, 0x0, mo_f490, 1 },
    { "igAnimationList", "igObjectList", 0x20, 0x529b00, 0, 0 },
    { "igAnimationModifier", "igObject", 0x20, 0x529ee0, mo_f492, 3 },
    { "igAnimationModifierList", "igObjectList", 0x20, 0x529f40, 0, 0 },
    { "igAnimationSequence", "igTransformSource", 0x10, 0x0, 0, 0 },
    { "igAnimationState", "igObject", 0xa0, 0x529550, mo_f495, 26 },
    { "igAnimationStateList", "igObjectList", 0x20, 0x529fb0, 0, 0 },
    { "igAnimationStatePool", "igObjectPool", 0x20, 0x52a020, 0, 0 },
    { "igAnimationSystem", "igNamedObject", 0x10, 0x0, mo_f498, 1 },
    { "igAnimationTrack", "igNamedObject", 0x30, 0x529830, mo_f499, 3 },
    { "igAnimationTrackList", "igObjectList", 0x20, 0x529890, 0, 0 },
    { "igAnimationTransitionDefinition", "igObject", 0x20, 0x529a30, mo_f501, 3 },
    { "igAnimationTransitionDefinitionList", "igObjectList", 0x20, 0x529a90, 0, 0 },
    { "igAnimationTransitionParams", "igObject", 0x20, 0x529900, mo_f503, 4 },
    { "igAnimationTransitionPoint", "igObject", 0x20, 0x529960, mo_f504, 2 },
    { "igAnimationTransitionPointList", "igObjectList", 0x20, 0x5299c0, 0, 0 },
    { "igAppearance", "igNamedObject", 0x20, 0x52a090, mo_f506, 5 },
    { "igAppearanceList", "igObjectList", 0x20, 0x52a0f0, 0, 0 },
    { "igAppearanceListList", "igObjectList", 0x20, 0x539b40, 0, 0 },
    { "igArenaMemoryPool", "igMemoryPool", 0xd0, 0x531030, mo_f509, 18 },
    { "igAttr", "igObject", 0x10, 0x0, mo_f510, 2 },
    { "igAttrDefaultManager", "igObject", 0x10, 0x0, 0, 0 },
    { "igAttrList", "igObjectList", 0x20, 0x524420, 0, 0 },
    { "igAttrListList", "igObjectList", 0x20, 0x524570, 0, 0 },
    { "igAttrPool", "igObject", 0x20, 0x5242a0, mo_f514, 3 },
    { "igAttrSet", "igGroup", 0x30, 0x5294b0, mo_f515, 2 },
    { "igAttrStack", "igNonRefCountedObjectStack", 0x40, 0x52a160, mo_f516, 8 },
    { "igAttrStackList", "igObjectList", 0x20, 0x52a1c0, 0, 0 },
    { "igAttrStackManager", "igObject", 0x50, 0x529450, mo_f518, 17 },
    { "igAudioContext", "igObject", 0x10, 0x0, mo_f519, 1 },
    { "igBase", "igInterfaced", 0x20, 0x0, 0, 0 },
    { "igBasicColorChanger", "igColorChanger", 0x60, 0x541550, mo_f521, 2 },
    { "igBillboard", "igGroup", 0x40, 0x52a2a0, mo_f522, 4 },
    { "igBitMask", "igUnsignedIntList", 0x20, 0x52a340, mo_f523, 1 },
    { "igBitmapFont", "igFont", 0x30, 0x541610, mo_f524, 2 },
    { "igBlendEquationExt", "igContextExt", 0x20, 0x0, mo_f525, 1 },
    { "igBlendFunctionAttr", "igVisualAttribute", 0x40, 0x524210, mo_f526, 11 },
    { "igBlendListRecord", "igObject", 0x10, 0x52a670, mo_f527, 2 },
    { "igBlendMatricesAttr", "igVisualAttribute", 0x20, 0x524190, mo_f528, 3 },
    { "igBlendMatricesAttrPool", "igObjectPool", 0x20, 0x52b190, 0, 0 },
    { "igBlendMatrixPaletteAttr", "igVisualAttribute", 0x20, 0x524110, mo_f530, 4 },
    { "igBlendMatrixPaletteAttrList", "igObjectList", 0x20, 0x5246c0, 0, 0 },
    { "igBlendMatrixSelect", "igAttrSet", 0xb0, 0x52a400, mo_f532, 3 },
    { "igBlendStateAttr", "igVisualAttribute", 0x10, 0x524080, mo_f533, 1 },
    { "igBoolArrayMetaField", "igBoolMetaField", 0x40, 0x530c80, mo_f534, 1 },
    { "igBoolList", "igDataList", 0x20, 0x5319f0, 0, 0 },
    { "igBoolMetaField", "igMetaField", 0x40, 0x0, 0, 0 },
    { "igBoolObject", "igObject", 0x10, 0x52b9b0, mo_f537, 1 },
    { "igBoundingBoxRenderer", "igRenderer", 0x30, 0x542a70, mo_f538, 8 },
    { "igBoundingBoxesMaker", "igObject", 0x30, 0x52a4a0, mo_f539, 8 },
    { "igBoundingSphereMaker", "igObject", 0x10, 0x52d230, mo_f540, 1 },
    { "igBoxComponent", "igGuiComponent", 0x30, 0x5417e0, 0, 0 },
    { "igCallStackTable", "igObject", 0x20, 0x530c00, mo_f542, 4 },
    { "igCallStackTracer", "igUnsignedIntListNoClean", 0x20, 0x530b80, 0, 0 },
    { "igCamera", "igNode", 0x40, 0x52a500, mo_f544, 7 },
    { "igCameraMode", "igViewMode", 0x60, 0x0, mo_f545, 2 },
    { "igCapabilityManager", "igObject", 0x10, 0x0, 0, 0 },
    { "igCharArrayMetaField", "igCharMetaField", 0x40, 0x530a80, mo_f547, 1 },
    { "igCharList", "igDataList", 0x20, 0x531ab0, 0, 0 },
    { "igCharListNoClean", "igCharList", 0x20, 0x531a50, 0, 0 },
    { "igCharMetaField", "igMetaField", 0x40, 0x0, 0, 0 },
    { "igCharMetricsList", "igDataList", 0x20, 0x541780, 0, 0 },
    { "igCharMetricsMetaField", "igCompoundMetaField", 0x40, 0x541680, 0, 0 },
    { "igClearAttr", "igVisualAttribute", 0x50, 0x524000, mo_f553, 7 },
    { "igClearRenderer", "igRenderer", 0x10, 0x540c80, mo_f554, 1 },
    { "igClippingStateAttr", "igVisualAttribute", 0x10, 0x523f70, mo_f555, 1 },
    { "igClut", "igObject", 0x20, 0x5269f0, mo_f556, 7 },
    { "igCollisionCell", "igObject", 0x20, 0x52d290, mo_f557, 6 },
    { "igCollisionCellList", "igObjectList", 0x20, 0x52d2f0, 0, 0 },
    { "igCollisionGrid", "igObject", 0x50, 0x52d1c0, mo_f559, 15 },
    { "igCollisionGridHelper", "igObject", 0x10, 0x52d360, mo_f560, 2 },
    { "igCollisionGroup", "igGroup", 0x60, 0x52d3c0, mo_f561, 8 },
    { "igCollisionGroupList", "igObjectList", 0x20, 0x52d460, 0, 0 },
    { "igCollisionInfo", "igInfo", 0x20, 0x52d4d0, mo_f563, 1 },
    { "igColorAttr", "igVisualAttribute", 0x20, 0x523ee0, mo_f564, 2 },
    { "igColorChanger", "igObject", 0x10, 0x5415b0, 0, 0 },
    { "igColorMaskAttr", "igVisualAttribute", 0x20, 0x523e50, mo_f566, 5 },
    { "igCommonTraversal", "igTraversal", 0x1e0, 0x5293c0, mo_f567, 35 },
    { "igCompileTraversal", "igCommonTraversal", 0x210, 0x529330, mo_f568, 12 },
    { "igCompiledTransform", "igObject", 0x30, 0x52a5a0, mo_f569, 8 },
    { "igCompiledTransformList", "igObjectList", 0x20, 0x52a600, 0, 0 },
    { "igCompoundList", "igObject", 0x20, 0x52c750, mo_f571, 3 },
    { "igCompoundMetaField", "igMetaField", 0x40, 0x0, mo_f572, 1 },
    { "igCompressedAnimationSequenceQS", "igAnimationSequence", 0x40, 0x529260, mo_f573, 12 },
    { "igCompressedTransformSequence1_5Data", "igObject", 0x30, 0x52a6d0, mo_f574, 10 },
    { "igContainsFunctionList", "igDataList", 0x20, 0x527af0, 0, 0 },
    { "igContainsRayFunctionList", "igDataList", 0x20, 0x527c10, 0, 0 },
    { "igContainsVecFunctionList", "igDataList", 0x20, 0x527cd0, 0, 0 },
    { "igContext", "igObject", 0x20, 0x0, mo_f578, 3 },
    { "igContextExt", "igContext", 0x20, 0x0, 0, 0 },
    { "igContextExtInfo", "igObject", 0x20, 0x5318b0, mo_f580, 3 },
    { "igContextExtInfoList", "igObjectList", 0x20, 0x531910, 0, 0 },
    { "igContextExtList", "igObjectList", 0x20, 0x531980, 0, 0 },
    { "igContextList", "igNonRefCountedObjectList", 0x20, 0x531840, 0, 0 },
    { "igController", "igEventProducer", 0x10, 0x0, mo_f584, 2 },
    { "igControllerList", "igObjectList", 0x20, 0x524f70, 0, 0 },
    { "igControllerManager", "igEventProducer", 0x10, 0x0, mo_f586, 1 },
    { "igCopyRenderDestinationAttr", "igVisualAttribute", 0x40, 0x523dd0, mo_f587, 10 },
    { "igCreateCollisionDatabase", "igOptBase", 0x50, 0x52d130, mo_f588, 7 },
    { "igCriMovieCodec", "igMovieCodec", 0x20, 0x533c70, mo_f589, 3 },
    { "igCriMovieData", "igObject", 0x20, 0x533d00, mo_f590, 5 },
    { "igCullFaceAttr", "igVisualAttribute", 0x20, 0x523d40, mo_f591, 2 },
    { "igCustomState", "igNamedObject", 0x10, 0x0, 0, 0 },
    { "igCustomStateCollection", "igObjectList", 0x20, 0x526d10, mo_f593, 2 },
    { "igCustomStateCollectionList", "igObjectList", 0x20, 0x526d80, 0, 0 },
    { "igCustomStateField", "igNamedObject", 0x20, 0x526df0, mo_f595, 2 },
    { "igCustomStateFieldList", "igObjectList", 0x20, 0x526e50, 0, 0 },
    { "igDataList", "igObject", 0x20, 0x5309b0, mo_f597, 3 },
    { "igDataPump", "igObject", 0x20, 0x52b950, mo_f598, 5 },
    { "igDataPumpInfo", "igInfo", 0x20, 0x52ba10, mo_f599, 1 },
    { "igDataPumpInterface", "igObject", 0x10, 0x0, 0, 0 },
    { "igDataPumpList", "igObjectList", 0x20, 0x52ba80, 0, 0 },
    { "igDataPumpManager", "igObject", 0x10, 0x52baf0, mo_f602, 1 },
    { "igDecalExt", "igContextExt", 0x20, 0x0, mo_f603, 1 },
    { "igDefaultAspect", "igGuiComponentAspect", 0x30, 0x541480, mo_f604, 1 },
    { "igDefaultAspectElement", "igObject", 0x20, 0x541840, mo_f605, 6 },
    { "igDefaultAspectElementList", "igObjectList", 0x20, 0x5418a0, 0, 0 },
    { "igDefaultInterfaceManager", "igInterfaceManager", 0x50, 0x524e50, mo_f607, 16 },
    { "igDependencyList", "igDataList", 0x20, 0x532360, 0, 0 },
    { "igDependencyMetaField", "igCompoundMetaField", 0x40, 0x532260, 0, 0 },
    { "igDependencyOrderedList", "igObject", 0x20, 0x52cc20, mo_f610, 5 },
    { "igDepthStateAttr", "igVisualAttribute", 0x10, 0x523cb0, mo_f611, 1 },
    { "igDepthWriteStateAttr", "igVisualAttribute", 0x10, 0x523c20, mo_f612, 1 },
    { "igDirEntry", "igNamedObject", 0x20, 0x530900, mo_f613, 4 },
    { "igDirectory", "igObjectList", 0x50, 0x530890, mo_f614, 18 },
    { "igDirectoryList", "igObjectList", 0x20, 0x5323c0, 0, 0 },
    { "igDisableExt", "igContextExt", 0x20, 0x0, 0, 0 },
    { "igDisplayListAttr", "igAttr", 0x10, 0x523ba0, mo_f617, 1 },
    { "igDoubleArrayMetaField", "igDoubleMetaField", 0x40, 0x530790, mo_f618, 1 },
    { "igDoubleList", "igDataList", 0x20, 0x52b630, 0, 0 },
    { "igDoubleMetaField", "igMetaField", 0x40, 0x530690, 0, 0 },
    { "igDriverDatabase", "igObject", 0x40, 0x530630, mo_f621, 12 },
    { "igElfFile", "igProgramFile", 0x70, 0x52e0a0, mo_f622, 9 },
    { "igEmptyFunctionList", "igDataList", 0x20, 0x527d90, 0, 0 },
    { "igEnbayaAnimationSource", "igObject", 0x30, 0x5291e0, mo_f624, 6 },
    { "igEnbayaAnimationState", "igAnimationState", 0xb0, 0x529170, mo_f625, 2 },
    { "igEnbayaContextPool", "igObject", 0x20, 0x529110, mo_f626, 3 },
    { "igEnbayaTransformSource", "igTransformSource", 0x10, 0x529080, mo_f627, 2 },
    { "igEnumArrayMetaField", "igEnumMetaField", 0x40, 0x5304f0, mo_f628, 1 },
    { "igEnumMetaField", "igMetaField", 0x40, 0x0, mo_f629, 1 },
    { "igEnvironmentMapShader2", "igGroup", 0x70, 0x0, mo_f630, 21 },
    { "igEnvironmentMapShader2List", "igObjectList", 0x20, 0x52a730, 0, 0 },
    { "igErrorHandler", "igObject", 0x10, 0x532530, 0, 0 },
    { "igEventDispatcher", "igInterfaceManager", 0x20, 0x5413d0, mo_f633, 2 },
    { "igEventProducer", "igObject", 0x10, 0x0, 0, 0 },
    { "igEventProducerList", "igObjectList", 0x20, 0x525040, 0, 0 },
    { "igEventReceiver", "igObject", 0x10, 0x52cce0, 0, 0 },
    { "igEventReceiverOrderedList", "igDependencyOrderedList", 0x20, 0x541910, 0, 0 },
    { "igEventTracker", "igObject", 0x2530, 0x530420, mo_f638, 33 },
    { "igExtendByFunctionList", "igDataList", 0x20, 0x527a90, 0, 0 },
    { "igExtendByRayFunctionList", "igDataList", 0x20, 0x527bb0, 0, 0 },
    { "igExtendByVecFunctionList", "igDataList", 0x20, 0x527c70, 0, 0 },
    { "igExternalDirEntry", "igDirEntry", 0x30, 0x530360, mo_f642, 4 },
    { "igExternalImageEntry", "igExternalDirEntry", 0x30, 0x526930, 0, 0 },
    { "igExternalIndexedEntry", "igDirEntry", 0x40, 0x5302b0, mo_f644, 6 },
    { "igExternalInfoEntry", "igDirEntry", 0x30, 0x530200, mo_f645, 3 },
    { "igFieldChangeView", "igView", 0x20, 0x541360, mo_f646, 2 },
    { "igFieldChangeViewList", "igObjectList", 0x20, 0x5419d0, 0, 0 },
    { "igFieldSynchronizer", "igObject", 0x10, 0x541a40, mo_f648, 1 },
    { "igFile", "igNamedObject", 0x30, 0x0, mo_f649, 8 },
    { "igFileImage", "igImage", 0x60, 0x0, 0, 0 },
    { "igFileImagePng", "igFileImage", 0x60, 0x525d20, mo_f651, 1 },
    { "igFileInfo", "igNamedObject", 0x20, 0x52c170, mo_f652, 4 },
    { "igFileInfoList", "igObjectList", 0x20, 0x52c1d0, 0, 0 },
    { "igFileName", "igNamedObject", 0x10, 0x533ba0, mo_f654, 1 },
    { "igFileNameList", "igObjectList", 0x20, 0x533ad0, 0, 0 },
    { "igFilterMessageDispatcher", "igMessageDispatcher", 0x10, 0x52c8b0, mo_f656, 2 },
    { "igFloatArrayMetaField", "igFloatMetaField", 0x40, 0x530050, mo_f657, 1 },
    { "igFloatList", "igDataList", 0x20, 0x531e20, 0, 0 },
    { "igFloatListList", "igObjectList", 0x20, 0x531e80, 0, 0 },
    { "igFloatMetaField", "igMetaField", 0x40, 0x52ff50, 0, 0 },
    { "igFloatObject", "igObject", 0x10, 0x52bb50, mo_f661, 1 },
    { "igFlushRenderer", "igRenderer", 0x10, 0x52ca80, 0, 0 },
    { "igFlyMode", "igViewMode", 0xa0, 0x0, mo_f663, 11 },
    { "igFogAttr", "igVisualAttribute", 0x30, 0x523b20, mo_f664, 5 },
    { "igFogStateAttr", "igVisualAttribute", 0x10, 0x523a90, mo_f665, 1 },
    { "igFolder", "igObject", 0x10, 0x52fee0, mo_f666, 1 },
    { "igFont", "igNamedObject", 0x20, 0x535a20, mo_f667, 4 },
    { "igFrustCullTraversal", "igCommonTraversal", 0x230, 0x528f10, mo_f668, 7 },
    { "igGenericAttrDefaultManager", "igAttrDefaultManager", 0x10, 0x523a20, 0, 0 },
    { "igGenericCapabilityManager", "igCapabilityManager", 0x10, 0x5268c0, 0, 0 },
    { "igGeometry", "igAttrSet", 0x30, 0x528e70, mo_f671, 1 },
    { "igGeometryAttr", "igVisualAttribute", 0x30, 0x0, mo_f672, 9 },
    { "igGeometryAttr1_5", "igGeometryAttr", 0x40, 0x5238c0, mo_f673, 1 },
    { "igGeometryAttrList", "igObjectList", 0x20, 0x5245e0, 0, 0 },
    { "igGeometryElement", "igObject", 0x30, 0x0, mo_f675, 4 },
    { "igGeometryList", "igObjectList", 0x20, 0x52a7a0, 0, 0 },
    { "igGeometryMaskAttr", "igVisualAttribute", 0x10, 0x523840, mo_f677, 1 },
    { "igGeometrySetAttr", "igVisualAttribute", 0x20, 0x5237b0, mo_f678, 5 },
    { "igGetCenterFunctionList", "igDataList", 0x20, 0x527e50, 0, 0 },
    { "igGraphPath", "igObject", 0x20, 0x52a810, mo_f680, 3 },
    { "igGraphPathList", "igObjectList", 0x20, 0x52a870, 0, 0 },
    { "igGroup", "igNode", 0x20, 0x528dd0, mo_f682, 1 },
    { "igGuiComponent", "igObject", 0x30, 0x541300, mo_f683, 7 },
    { "igGuiComponentAspect", "igView", 0x30, 0x0, mo_f684, 3 },
    { "igGuiComponentController", "igView", 0x10, 0x541270, 0, 0 },
    { "igGuiComponentList", "igObjectList", 0x20, 0x541aa0, 0, 0 },
    { "igGuiComponentModel", "igModel", 0x30, 0x541e30, mo_f687, 7 },
    { "igGuiComponentNode", "igGroup", 0x30, 0x5411d0, mo_f688, 1 },
    { "igGuiSystem", "igEventReceiver", 0x30, 0x540f20, mo_f689, 7 },
    { "igGuiSystemModel", "igModel", 0xc0, 0x541170, mo_f690, 11 },
    { "igGuiSystemRenderer", "igRenderer", 0x20, 0x540fb0, mo_f691, 4 },
    { "igHotKeyBinding", "igObject", 0x20, 0x541b70, mo_f692, 3 },
    { "igHotKeyBindingList", "igObjectList", 0x20, 0x541bd0, 0, 0 },
    { "igHotKeyEventReceiver", "igEventReceiver", 0x10, 0x540e90, mo_f694, 1 },
    { "igIGBFile", "igDirectory", 0x140, 0x52fe50, mo_f695, 65 },
    { "igImage", "igObject", 0x60, 0x0, mo_f696, 21 },
    { "igImageConvert", "igImageUtils", 0x10, 0x0, 0, 0 },
    { "igImageLoader", "igImageUtils", 0x10, 0x0, 0, 0 },
    { "igImageMipMapList", "igObjectList", 0x20, 0x5248e0, 0, 0 },
    { "igImageUtils", "igObject", 0x10, 0x0, 0, 0 },
    { "igIndexArray", "igObject", 0x20, 0x0, mo_f701, 5 },
    { "igInfo", "igNamedObject", 0x20, 0x52fde0, mo_f702, 2 },
    { "igInfoList", "igObjectList", 0x20, 0x532600, 0, 0 },
    { "igInfoManager", "igNamedObject", 0x10, 0x0, mo_f704, 1 },
    { "igInfoManagerList", "igObjectList", 0x20, 0x52caf0, 0, 0 },
    { "igInfoManagerOrderedList", "igDependencyOrderedList", 0x20, 0x52cb60, 0, 0 },
    { "igIniShaderFactory", "igShaderFactory", 0x40, 0x528d60, mo_f707, 9 },
    { "igInsightCore", "igObject", 0x70, 0x52c990, mo_f708, 19 },
    { "igInsightPlugin", "igObject", 0x10, 0x5338a0, 0, 0 },
    { "igInsightPluginList", "igObjectList", 0x20, 0x52cd70, 0, 0 },
    { "igInsightScheduler", "igObject", 0x10, 0x0, 0, 0 },
    { "igIntArrayMetaField", "igIntMetaField", 0x40, 0x52fce0, mo_f712, 1 },
    { "igIntList", "igDataList", 0x20, 0x531b70, 0, 0 },
    { "igIntListList", "igObjectList", 0x20, 0x532110, 0, 0 },
    { "igIntListNoClean", "igIntList", 0x20, 0x531b10, 0, 0 },
    { "igIntMetaField", "igMetaField", 0x40, 0x0, 0, 0 },
    { "igIntObject", "igObject", 0x10, 0x52bbb0, mo_f717, 1 },
    { "igInterface", "igInterfaced", 0x20, 0x52c670, 0, 0 },
    { "igInterfaceManager", "igObject", 0x10, 0x0, mo_f719, 1 },
    { "igInterfaced", "igObject", 0x20, 0x0, mo_f720, 6 },
    { "igInterpretedShaderData", "igTransientShaderData", 0x20, 0x52a8e0, mo_f721, 2 },
    { "igIntersectTraversal", "igTraversal", 0x40, 0x528cf0, mo_f722, 7 },
    { "igIntersectionFunctionList", "igDataList", 0x20, 0x527a30, 0, 0 },
    { "igIsEmptyFunctionList", "igDataList", 0x20, 0x527df0, 0, 0 },
    { "igItemBase", "igBase", 0x20, 0x0, 0, 0 },
    { "igItemDataBaseField", "igCompoundMetaField", 0x40, 0x52c240, 0, 0 },
    { "igItemDataBaseList", "igCompoundList", 0x20, 0x52c340, 0, 0 },
    { "igItemInterface", "igInterface", 0x40, 0x52c0f0, mo_f728, 5 },
    { "igIterateDerived", "igIterator", 0x10, 0x52c3a0, mo_f729, 2 },
    { "igIterateField", "igIterator", 0x10, 0x52c400, mo_f730, 2 },
    { "igIterateGraph", "igIterator", 0x20, 0x52c460, mo_f731, 3 },
    { "igIterator", "igObject", 0x10, 0x0, 0, 0 },
    { "igLibrary", "igObject", 0x10, 0x0, mo_f733, 1 },
    { "igLibraryList", "igObjectList", 0x20, 0x532830, 0, 0 },
    { "igLibraryLoader", "igObject", 0x10, 0x0, 0, 0 },
    { "igLightAttr", "igVisualAttribute", 0xa0, 0x523700, mo_f736, 16 },
    { "igLightList", "igObjectList", 0x20, 0x524730, 0, 0 },
    { "igLightSet", "igNode", 0x20, 0x528c60, mo_f738, 1 },
    { "igLightSetList", "igObjectList", 0x20, 0x536750, 0, 0 },
    { "igLightStateAttr", "igVisualAttribute", 0x20, 0x523670, mo_f740, 3 },
    { "igLightStateAttrList", "igObjectList", 0x20, 0x5247a0, 0, 0 },
    { "igLightStateAttrPool", "igObjectPool", 0x20, 0x52ae10, 0, 0 },
    { "igLightStateSet", "igGroup", 0x30, 0x528bc0, mo_f743, 1 },
    { "igLightingStateAttr", "igVisualAttribute", 0x10, 0x5235e0, mo_f744, 1 },
    { "igLineWidthExt", "igContextExt", 0x20, 0x0, mo_f745, 1 },
    { "igListenerBase", "igBase", 0x20, 0x52c7b0, 0, 0 },
    { "igListenerInterface", "igInterface", 0x30, 0x52c080, mo_f747, 4 },
    { "igListenerList", "igObjectList", 0x20, 0x52c4c0, 0, 0 },
    { "igListenerListList", "igObjectList", 0x20, 0x52c530, 0, 0 },
    { "igLocationTable", "igObject", 0x20, 0x52fc50, mo_f750, 6 },
    { "igLockBase", "igInterfaced", 0x20, 0x0, 0, 0 },
    { "igLockInterface", "igInterface", 0x30, 0x52c010, mo_f752, 3 },
    { "igLod", "igGroup", 0x50, 0x528b20, mo_f753, 7 },
    { "igLogInterface", "igInterface", 0x30, 0x52bfa0, mo_f754, 1 },
    { "igLogoRenderer", "igRenderer", 0x30, 0x542230, mo_f755, 4 },
    { "igLongArrayMetaField", "igLongMetaField", 0x40, 0x52fb50, mo_f756, 1 },
    { "igLongList", "igDataList", 0x20, 0x531bd0, 0, 0 },
    { "igLongMetaField", "igMetaField", 0x40, 0x52fa50, 0, 0 },
    { "igLongStack", "igDataList", 0x20, 0x52bdb0, 0, 0 },
    { "igLongTimer", "igTimer", 0x30, 0x0, mo_f760, 4 },
    { "igLuaGlue", "igObject", 0x10, 0x52d540, 0, 0 },
    { "igLuaState", "igNamedObject", 0x20, 0x52d660, mo_f762, 2 },
    { "igMallocMemoryPool", "igMemoryPool", 0xa0, 0x530e90, mo_f763, 10 },
    { "igMaterialAttr", "igVisualAttribute", 0x60, 0x523540, mo_f764, 6 },
    { "igMatrix44fList", "igDataList", 0x20, 0x5279d0, 0, 0 },
    { "igMatrix44fMetaField", "igMetaField", 0x40, 0x5276e0, 0, 0 },
    { "igMatrixObject", "igObject", 0x50, 0x52bc10, mo_f767, 1 },
    { "igMatrixObjectList", "igObjectList", 0x20, 0x52bc70, 0, 0 },
    { "igMatrixObjectPool", "igObjectPool", 0x20, 0x52b0b0, 0, 0 },
    { "igMatrixOptStateAttr", "igVisualAttribute", 0x10, 0x5234b0, mo_f770, 1 },
    { "igMatrixStack", "igDataList", 0x20, 0x52bd50, 0, 0 },
    { "igMedia", "igObject", 0x10, 0x0, 0, 0 },
    { "igMediaFile", "igFile", 0x50, 0x52f9a0, mo_f773, 9 },
    { "igMediaList", "igObjectList", 0x20, 0x5328a0, 0, 0 },
    { "igMemoryDescriptorMetaField", "igCompoundMetaField", 0x40, 0x530d90, 0, 0 },
    { "igMemoryDictionary", "igObject", 0x20, 0x52f910, mo_f776, 4 },
    { "igMemoryDirEntry", "igDirEntry", 0x40, 0x52f860, mo_f777, 7 },
    { "igMemoryFile", "igFile", 0x40, 0x52f7b0, mo_f778, 4 },
    { "igMemoryFileEntry", "igNamedObject", 0x20, 0x532910, mo_f779, 2 },
    { "igMemoryFileEntryList", "igObjectList", 0x20, 0x532970, 0, 0 },
    { "igMemoryImage", "igImage", 0x60, 0x0, 0, 0 },
    { "igMemoryPool", "igObject", 0x70, 0x0, mo_f782, 14 },
    { "igMemoryPoolContextInfo", "igInfo", 0x20, 0x52f4a0, mo_f783, 1 },
    { "igMemoryPoolInfo", "igInfo", 0x60, 0x52f430, mo_f784, 16 },
    { "igMemoryPoolInfoList", "igObjectList", 0x20, 0x5329e0, 0, 0 },
    { "igMemoryRefArrayMetaField", "igMemoryRefMetaField", 0x60, 0x52f330, mo_f786, 1 },
    { "igMemoryRefMetaField", "igRefMetaField", 0x50, 0x532a50, mo_f787, 8 },
    { "igMersenneTwisterRandomNumber", "igRandomNumber", 0x10, 0x52b8e0, mo_f788, 2 },
    { "igMessage", "igObject", 0x10, 0x52d000, 0, 0 },
    { "igMessageBase", "igBase", 0x20, 0x52c6e0, 0, 0 },
    { "igMessageDefaultReceiver", "igMessageReceiver", 0x10, 0x52c930, mo_f791, 2 },
    { "igMessageDispatcher", "igObject", 0x10, 0x0, 0, 0 },
    { "igMessageFilter", "igObject", 0x10, 0x52cde0, mo_f793, 2 },
    { "igMessageFilterList", "igObjectList", 0x20, 0x52ce40, 0, 0 },
    { "igMessageInterface", "igInterface", 0x30, 0x52bf30, mo_f795, 1 },
    { "igMessageList", "igObjectList", 0x20, 0x52c5a0, 0, 0 },
    { "igMessageReceiver", "igObject", 0x10, 0x0, 0, 0 },
    { "igMessageReceiverList", "igObjectList", 0x20, 0x52ceb0, 0, 0 },
    { "igMessenger", "igObject", 0x10, 0x52cf20, mo_f799, 1 },
    { "igMetaEnum", "igObject", 0x20, 0x532b50, mo_f800, 3 },
    { "igMetaField", "igObject", 0x40, 0x0, mo_f801, 18 },
    { "igMetaFieldInfo", "igInfo", 0x20, 0x52f1c0, 0, 0 },
    { "igMetaFieldList", "igObjectList", 0x20, 0x5320a0, 0, 0 },
    { "igMetaObject", "igObject", 0x70, 0x532bb0, mo_f804, 25 },
    { "igMetaObjectList", "igObjectList", 0x20, 0x531fc0, 0, 0 },
    { "igMetaObjectListList", "igObjectList", 0x20, 0x532030, 0, 0 },
    { "igModel", "igObject", 0x10, 0x540e30, mo_f807, 1 },
    { "igModelViewMatrixAttr", "igVisualAttribute", 0x50, 0x523420, mo_f808, 1 },
    { "igModelViewMatrixAttrList", "igObjectList", 0x20, 0x524810, 0, 0 },
    { "igModelViewMatrixAttrPool", "igObjectPool", 0x20, 0x52ae80, 0, 0 },
    { "igModelViewMatrixBoneSelect", "igGroup", 0x30, 0x52aa10, mo_f811, 1 },
    { "igModelViewMatrixBoneSelectList", "igObjectList", 0x20, 0x539ad0, 0, 0 },
    { "igMouseCursor", "igObject", 0x20, 0x541b10, mo_f813, 2 },
    { "igMousePosObserver", "igView", 0x70, 0x541090, mo_f814, 7 },
    { "igMovieCodec", "igNamedObject", 0x10, 0x533d60, 0, 0 },
    { "igMovieCodecList", "igObjectList", 0x20, 0x533a60, 0, 0 },
    { "igMovieInfo", "igInfo", 0x70, 0x533910, mo_f817, 21 },
    { "igMovieInfoList", "igObjectList", 0x20, 0x5339f0, 0, 0 },
    { "igMovieManager", "igInfoManager", 0x30, 0x533e50, mo_f819, 6 },
    { "igMoviePlugin", "igInsightPlugin", 0x10, 0x533ee0, mo_f820, 1 },
    { "igMovieRenderer", "igRenderer", 0x10, 0x533de0, mo_f821, 1 },
    { "igMultiPassStateAttr", "igVisualAttribute", 0x10, 0x523390, mo_f822, 1 },
    { "igMultiTextureExt", "igContextExt", 0x20, 0x0, 0, 0 },
    { "igNamedObject", "igObject", 0x10, 0x524950, mo_f824, 1 },
    { "igNamedObjectInfo", "igInfo", 0x20, 0x52f150, mo_f825, 1 },
    { "igNamedObjectList", "igObjectList", 0x20, 0x532c10, 0, 0 },
    { "igNode", "igNamedObject", 0x20, 0x528a90, mo_f827, 4 },
    { "igNodeList", "igObjectList", 0x20, 0x52ab20, 0, 0 },
    { "igNodeListList", "igObjectList", 0x20, 0x52ab90, 0, 0 },
    { "igNonRefCountedAttrList", "igNonRefCountedObjectList", 0x20, 0x524490, 0, 0 },
    { "igNonRefCountedAttrStackManagerList", "igNonRefCountedObjectList", 0x20, 0x52a230, 0, 0 },
    { "igNonRefCountedMatrixObjectList", "igNonRefCountedObjectList", 0x20, 0x52bce0, 0, 0 },
    { "igNonRefCountedNodeList", "igNonRefCountedObjectList", 0x20, 0x52ac00, 0, 0 },
    { "igNonRefCountedObjectList", "igDataList", 0x20, 0x524500, 0, 0 },
    { "igNonRefCountedObjectStack", "igDataList", 0x20, 0x524fe0, 0, 0 },
    { "igNonRefCountedThreadList", "igNonRefCountedObjectList", 0x20, 0x5333c0, 0, 0 },
    { "igNonRefCountedTransformList", "igNonRefCountedObjectList", 0x20, 0x52b760, 0, 0 },
    { "igNonRefCountedViewList", "igNonRefCountedObjectList", 0x20, 0x541f70, 0, 0 },
    { "igNormalizeNormalsStateAttr", "igVisualAttribute", 0x10, 0x523310, mo_f839, 1 },
    { "igNormalsRenderer", "igRenderer", 0x30, 0x5422a0, mo_f840, 9 },
    { "igObject", "-", 0x10, 0x0, 0, 0 },
    { "igObjectDirEntry", "igDirEntry", 0x40, 0x52f040, mo_f842, 6 },
    { "igObjectList", "igDataList", 0x20, 0x5249b0, 0, 0 },
    { "igObjectListList", "igObjectList", 0x20, 0x532180, 0, 0 },
    { "igObjectPool", "igObjectList", 0x20, 0x52b5c0, mo_f845, 3 },
    { "igObjectRefArrayMetaField", "igObjectRefMetaField", 0x50, 0x52ef40, mo_f846, 1 },
    { "igObjectRefMetaField", "igRefMetaField", 0x50, 0x532c80, mo_f847, 3 },
    { "igObjectStringMap", "igObject", 0x10, 0x532d80, mo_f848, 2 },
    { "igOnOffColorChanger", "igBasicColorChanger", 0x60, 0x5414f0, 0, 0 },
    { "igOnOffModel", "igGuiComponentModel", 0x30, 0x541c40, mo_f850, 1 },
    { "igOnOffValueObserver", "igView", 0x10, 0x540cf0, mo_f851, 1 },
    { "igOnOffValueObserverList", "igObjectList", 0x20, 0x541d00, 0, 0 },
    { "igOptBase", "igBase", 0x30, 0x0, mo_f853, 2 },
    { "igOptConfiguration", "igObject", 0x10, 0x52c610, 0, 0 },
    { "igOptInterface", "igInterface", 0x30, 0x52be10, mo_f855, 4 },
    { "igOverrideAttrSet", "igAttrSet", 0x30, 0x52ac70, 0, 0 },
    { "igPageMemoryPool", "igMemoryPool", 0x90, 0x5311f0, mo_f857, 7 },
    { "igParticleArray", "igObject", 0x60, 0x5266c0, mo_f858, 22 },
    { "igParticleAttr", "igVisualAttribute", 0x30, 0x523280, mo_f859, 7 },
    { "igParticleFormat", "igObject", 0x30, 0x526fc0, mo_f860, 10 },
    { "igPickMode", "igViewMode", 0xc0, 0x0, mo_f861, 12 },
    { "igPixelPipelineModeAttr", "igVisualAttribute", 0x10, 0x523200, mo_f862, 1 },
    { "igPlanarShadowShader", "igAttrSet", 0x70, 0x5289f0, mo_f863, 13 },
    { "igPlane", "igVolume", 0x20, 0x527eb0, mo_f864, 3 },
    { "igPluginHelper", "igObject", 0x20, 0x52eee0, mo_f865, 4 },
    { "igPluginRepository", "igNamedObject", 0x20, 0x532de0, mo_f866, 2 },
    { "igPluginRepositoryList", "igObjectList", 0x20, 0x532e40, 0, 0 },
    { "igPointSpriteExt", "igContextExt", 0x190, 0x0, mo_f868, 18 },
    { "igPointerList", "igDataList", 0x20, 0x531ef0, 0, 0 },
    { "igPointerListList", "igObjectList", 0x20, 0x531f50, 0, 0 },
    { "igPolygonModeAttr", "igVisualAttribute", 0x10, 0x523170, mo_f871, 1 },
    { "igPrimLengthArray", "igObject", 0x20, 0x0, mo_f872, 3 },
    { "igPrimLengthArray1_1", "igPrimLengthArray", 0x20, 0x526590, 0, 0 },
    { "igProbe", "igObject", 0x20, 0x52a950, mo_f874, 3 },
    { "igProgramFile", "igObject", 0x10, 0x52e010, mo_f875, 2 },
    { "igProjectionMatrixAttr", "igVisualAttribute", 0x50, 0x5230e0, mo_f876, 1 },
    { "igProjectionMatrixAttrPool", "igObjectPool", 0x20, 0x52af60, 0, 0 },
    { "igProjectiveShadowShader", "igGroup", 0xf0, 0x528950, mo_f878, 48 },
    { "igPsx2AudioContext", "igAudioContext", 0x40, 0x524a80, mo_f879, 10 },
    { "igPsx2AudioSourceList", "igDataList", 0x20, 0x524b80, 0, 0 },
    { "igPsx2BlendEquationExt", "igBlendEquationExt", 0x30, 0x525770, mo_f881, 6 },
    { "igPsx2CallStackTracer", "igCallStackTracer", 0x20, 0x52dcb0, 0, 0 },
    { "igPsx2Clut", "igClut", 0x30, 0x526a60, mo_f883, 2 },
    { "igPsx2Controller", "igController", 0x60, 0x524d00, mo_f884, 24 },
    { "igPsx2ControllerManager", "igControllerManager", 0x20, 0x524c90, mo_f885, 3 },
    { "igPsx2DecalExt", "igDecalExt", 0x20, 0x5256f0, mo_f886, 2 },
    { "igPsx2DisableExt", "igDisableExt", 0x20, 0x5257f0, mo_f887, 1 },
    { "igPsx2EnvironmentMapShader", "igEnvironmentMapShader2", 0x80, 0x528170, mo_f888, 3 },
    { "igPsx2File", "igFile", 0x50, 0x52dc00, mo_f889, 8 },
    { "igPsx2Folder", "igFolder", 0x10, 0x52db90, 0, 0 },
    { "igPsx2Image", "igMemoryImage", 0x60, 0x525630, 0, 0 },
    { "igPsx2ImageConvert", "igImageConvert", 0x10, 0x5255a0, 0, 0 },
    { "igPsx2IndexArray", "igIndexArray", 0x20, 0x526ad0, 0, 0 },
    { "igPsx2IopRpcConnection", "igObject", 0x20, 0x52db30, mo_f894, 3 },
    { "igPsx2LongList", "igDataList", 0x20, 0x526bf0, 0, 0 },
    { "igPsx2LongTimer", "igLongTimer", 0x30, 0x52da90, 0, 0 },
    { "igPsx2Media", "igMedia", 0x30, 0x52da00, mo_f897, 8 },
    { "igPsx2MultiTextureExt", "igMultiTextureExt", 0x40, 0x525510, mo_f898, 8 },
    { "igPsx2ParticleArray", "igParticleArray", 0x80, 0x5253e0, mo_f899, 5 },
    { "igPsx2PointSpriteExt", "igPointSpriteExt", 0x190, 0x0, mo_f900, 1 },
    { "igPsx2ScissorExt", "igScissorExt", 0x30, 0x525480, mo_f901, 6 },
    { "igPsx2Semaphore", "igSemaphore", 0x20, 0x52d970, mo_f902, 3 },
    { "igPsx2Thread", "igThread", 0x40, 0x52d7c0, mo_f903, 6 },
    { "igPsx2ThreadManager", "igThreadManager", 0x10, 0x52d750, 0, 0 },
    { "igPsx2UserUCodeExt", "igUserUCodeExt", 0x30, 0x5252a0, mo_f905, 4 },
    { "igPsx2VertexArray1_1", "igVertexArray1_1", 0x90, 0x525190, mo_f906, 7 },
    { "igPsx2VertexArray2", "igVertexArray2", 0x20, 0x525120, 0, 0 },
    { "igPsx2VertexStream", "igVertexStream", 0x90, 0x5250b0, mo_f908, 10 },
    { "igPsx2VisualContext", "igVisualContext", 0x610, 0x525870, mo_f909, 146 },
    { "igPsx2Window", "igWindow", 0x40, 0x524be0, mo_f910, 12 },
    { "igQuaternionfList", "igDataList", 0x20, 0x527970, 0, 0 },
    { "igQueue", "igObject", 0x10, 0x0, mo_f912, 1 },
    { "igRadioGroup", "igObject", 0x20, 0x540dd0, mo_f913, 6 },
    { "igRadioGroupModel", "igModel", 0x10, 0x541ca0, mo_f914, 1 },
    { "igRadioGroupSelectedObserver", "igView", 0x10, 0x540d60, mo_f915, 1 },
    { "igRandomNumber", "igObject", 0x10, 0x0, 0, 0 },
    { "igRawRefArrayMetaField", "igRawRefMetaField", 0x40, 0x52ed50, mo_f917, 1 },
    { "igRawRefMetaField", "igRefMetaField", 0x40, 0x0, 0, 0 },
    { "igRay", "igObject", 0x30, 0x527f10, mo_f919, 3 },
    { "igRayIntersectionFunctionList", "igDataList", 0x20, 0x527b50, 0, 0 },
    { "igRayList", "igObjectList", 0x20, 0x527f70, 0, 0 },
    { "igRefMetaField", "igMetaField", 0x40, 0x0, mo_f922, 2 },
    { "igRegistry", "igObject", 0x20, 0x52ebf0, mo_f923, 5 },
    { "igRegistryValue", "igObject", 0x20, 0x532fb0, mo_f924, 3 },
    { "igRegistryValueList", "igObjectList", 0x20, 0x533010, 0, 0 },
    { "igRenderDestinationAttr", "igVisualAttribute", 0x50, 0x523060, mo_f926, 14 },
    { "igRenderListAttr", "igVisualAttribute", 0x20, 0x522fd0, mo_f927, 2 },
    { "igRenderPackage", "igObject", 0x20, 0x52b480, mo_f928, 6 },
    { "igRenderPackageList", "igNonRefCountedObjectList", 0x20, 0x52b550, 0, 0 },
    { "igRenderPackagePool", "igObjectPool", 0x20, 0x52b4e0, 0, 0 },
    { "igRenderer", "igObject", 0x10, 0x0, mo_f931, 1 },
    { "igRendererOrderedList", "igDependencyOrderedList", 0x20, 0x541d70, 0, 0 },
    { "igResource", "igObject", 0x50, 0x52eb90, mo_f933, 17 },
    { "igRotateMode", "igViewMode", 0xa0, 0x0, mo_f934, 16 },
    { "igSceneInfo", "igInfo", 0x40, 0x5288e0, mo_f935, 7 },
    { "igScissorExt", "igContextExt", 0x20, 0x0, 0, 0 },
    { "igSearchSceneGraph", "igNamedObject", 0x20, 0x52d0d0, mo_f937, 4 },
    { "igSegment", "igGroup", 0x20, 0x52ad10, 0, 0 },
    { "igSemaphore", "igNamedObject", 0x10, 0x0, 0, 0 },
    { "igSerialScheduler", "igInsightScheduler", 0x10, 0x52c830, mo_f940, 2 },
    { "igSetRenderDestinationAttr", "igVisualAttribute", 0x10, 0x522f50, mo_f941, 1 },
    { "igShadeModelAttr", "igVisualAttribute", 0x10, 0x522ec0, mo_f942, 1 },
    { "igShaderData", "igObject", 0x20, 0x528870, mo_f943, 4 },
    { "igShaderFactory", "igNamedObject", 0x20, 0x528800, mo_f944, 3 },
    { "igShaderFactoryList", "igObjectList", 0x20, 0x52b200, 0, 0 },
    { "igShaderInfo", "igInfo", 0x20, 0x528790, mo_f946, 1 },
    { "igShaderProcessor", "igObject", 0x10, 0x528720, 0, 0 },
    { "igShortArrayMetaField", "igShortMetaField", 0x40, 0x52ea90, mo_f948, 1 },
    { "igShortList", "igDataList", 0x20, 0x531cf0, 0, 0 },
    { "igShortListList", "igObjectList", 0x20, 0x531d50, 0, 0 },
    { "igShortMetaField", "igMetaField", 0x40, 0x0, 0, 0 },
    { "igSkeleton", "igAnimationHierarchy", 0x20, 0x5286a0, mo_f952, 3 },
    { "igSkeletonBoneInfo", "igNamedObject", 0x20, 0x52b270, mo_f953, 3 },
    { "igSkeletonBoneInfoList", "igObjectList", 0x20, 0x52b2d0, 0, 0 },
    { "igSkeletonList", "igObjectList", 0x20, 0x52b340, 0, 0 },
    { "igSkin", "igNamedObject", 0x20, 0x52b3b0, mo_f956, 2 },
    { "igSkinList", "igObjectList", 0x20, 0x52b410, 0, 0 },
    { "igSorter", "igObject", 0x90, 0x528630, mo_f958, 36 },
    { "igSphere", "igVolume", 0x20, 0x527fe0, mo_f959, 2 },
    { "igStackMemoryPool", "igMemoryPool", 0xa0, 0x52de80, mo_f960, 10 },
    { "igStandardQueue", "igQueue", 0x30, 0x52ddf0, mo_f961, 8 },
    { "igStatisticsItem", "igView", 0x40, 0x542620, mo_f962, 12 },
    { "igStatisticsItemList", "igObjectList", 0x20, 0x5421c0, 0, 0 },
    { "igStencilFunctionAttr", "igVisualAttribute", 0x30, 0x522e20, mo_f964, 7 },
    { "igStencilStateAttr", "igVisualAttribute", 0x10, 0x522d90, mo_f965, 1 },
    { "igStringArrayMetaField", "igStringMetaField", 0x40, 0x52e990, mo_f966, 1 },
    { "igStringMetaField", "igRefMetaField", 0x40, 0x0, mo_f967, 1 },
    { "igStringObj", "igObject", 0x10, 0x533280, mo_f968, 2 },
    { "igStringObjList", "igObjectList", 0x20, 0x5332e0, 0, 0 },
    { "igStringRefList", "igDataList", 0x20, 0x52e930, 0, 0 },
    { "igStringRefListList", "igObjectList", 0x20, 0x5321f0, 0, 0 },
    { "igStringTable", "igObject", 0x20, 0x52e8c0, mo_f972, 4 },
    { "igStructMetaField", "igMetaField", 0x40, 0x52e7c0, mo_f973, 3 },
    { "igSwitch", "igGroup", 0x30, 0x528590, mo_f974, 1 },
    { "igSymbolTable", "igObject", 0x30, 0x52e730, mo_f975, 9 },
    { "igTexGenMatrixAttr", "igVisualAttribute", 0x50, 0x522d00, mo_f976, 2 },
    { "igTextElement", "igGeometryElement", 0x40, 0x540c10, mo_f977, 3 },
    { "igTextureAttr", "igVisualAttribute", 0x50, 0x522c60, mo_f978, 15 },
    { "igTextureBindAttr", "igVisualAttribute", 0x20, 0x522bd0, mo_f979, 2 },
    { "igTextureBindAttrList", "igObjectList", 0x20, 0x533980, 0, 0 },
    { "igTextureCoordSourceAttr", "igVisualAttribute", 0x20, 0x522b40, mo_f981, 3 },
    { "igTextureCubeAttr", "igTextureAttr", 0x70, 0x522aa0, mo_f982, 3 },
    { "igTextureFunctionAttr", "igVisualAttribute", 0x30, 0x522a10, mo_f983, 7 },
    { "igTextureList", "igObjectList", 0x20, 0x524650, 0, 0 },
    { "igTextureMatrixAttr", "igVisualAttribute", 0x60, 0x522980, mo_f985, 4 },
    { "igTextureMatrixAttrPool", "igObjectPool", 0x20, 0x52b120, 0, 0 },
    { "igTextureMatrixStateAttr", "igVisualAttribute", 0x20, 0x5228f0, mo_f987, 2 },
    { "igTextureStateAttr", "igVisualAttribute", 0x20, 0x522860, mo_f988, 2 },
    { "igTextureUnloadAttr", "igVisualAttribute", 0x20, 0x5227d0, mo_f989, 2 },
    { "igTgaLoader", "igImageLoader", 0x30, 0x525cc0, mo_f990, 10 },
    { "igThread", "igNamedObject", 0x30, 0x0, mo_f991, 10 },
    { "igThreadList", "igObjectList", 0x20, 0x533350, 0, 0 },
    { "igThreadManager", "igObject", 0x10, 0x0, mo_f993, 2 },
    { "igTimeAttr", "igVisualAttribute", 0x20, 0x522750, mo_f994, 1 },
    { "igTimeAttrPool", "igObjectPool", 0x20, 0x52aef0, 0, 0 },
    { "igTimer", "igObject", 0x10, 0x0, 0, 0 },
    { "igTrackedElementMetaField", "igCompoundMetaField", 0x40, 0x526ec0, 0, 0 },
    { "igTransform", "igGroup", 0x70, 0x0, mo_f998, 4 },
    { "igTransformFunctionList", "igDataList", 0x20, 0x527d30, 0, 0 },
    { "igTransformList", "igObjectList", 0x20, 0x52b6f0, 0, 0 },
    { "igTransformRecorder", "igGroup", 0xa0, 0x52b7d0, mo_f1001, 2 },
    { "igTransformSequence", "igTransformSource", 0x40, 0x0, mo_f1002, 9 },
    { "igTransformSequence1_5", "igTransformSequence", 0x70, 0x5282c0, mo_f1003, 9 },
    { "igTransformSource", "igObject", 0x10, 0x0, 0, 0 },
    { "igTransformStack", "igNonRefCountedObjectStack", 0x20, 0x52b690, 0, 0 },
    { "igTransientShaderData", "igShaderData", 0x20, 0x52b870, 0, 0 },
    { "igTraversal", "igObject", 0x20, 0x528250, mo_f1007, 5 },
    { "igTraversalFunctionList", "igDataList", 0x20, 0x52adb0, 0, 0 },
    { "igUnsignedCharArrayMetaField", "igUnsignedCharMetaField", 0x40, 0x52e630, mo_f1009, 1 },
    { "igUnsignedCharList", "igDataList", 0x20, 0x531dc0, 0, 0 },
    { "igUnsignedCharMetaField", "igMetaField", 0x40, 0x52e530, 0, 0 },
    { "igUnsignedIntArrayMetaField", "igUnsignedIntMetaField", 0x40, 0x52e430, mo_f1012, 1 },
    { "igUnsignedIntList", "igDataList", 0x20, 0x52a3a0, 0, 0 },
    { "igUnsignedIntListNoClean", "igUnsignedIntList", 0x20, 0x531c30, 0, 0 },
    { "igUnsignedIntMetaField", "igMetaField", 0x40, 0x0, 0, 0 },
    { "igUnsignedLongArrayMetaField", "igUnsignedLongMetaField", 0x40, 0x52e330, mo_f1016, 1 },
    { "igUnsignedLongMetaField", "igMetaField", 0x40, 0x0, 0, 0 },
    { "igUnsignedShortArrayMetaField", "igUnsignedShortMetaField", 0x40, 0x52e230, mo_f1018, 1 },
    { "igUnsignedShortList", "igDataList", 0x20, 0x531c90, 0, 0 },
    { "igUnsignedShortMetaField", "igMetaField", 0x40, 0x0, 0, 0 },
    { "igUserUCodeExt", "igContextExt", 0x20, 0x0, 0, 0 },
    { "igVec2fList", "igDataList", 0x20, 0x5278b0, 0, 0 },
    { "igVec2fMetaField", "igMetaField", 0x40, 0x5275e0, 0, 0 },
    { "igVec3fList", "igDataList", 0x20, 0x524880, 0, 0 },
    { "igVec3fMetaField", "igMetaField", 0x40, 0x5274e0, 0, 0 },
    { "igVec4fArrayMetaField", "igVec4fMetaField", 0x40, 0x5273e0, mo_f1026, 1 },
    { "igVec4fMetaField", "igMetaField", 0x40, 0x5272e0, 0, 0 },
    { "igVec4ucList", "igDataList", 0x20, 0x527910, 0, 0 },
    { "igVec4ucMetaField", "igMetaField", 0x40, 0x5271e0, 0, 0 },
    { "igVectorBlending", "igObject", 0x10, 0x528040, 0, 0 },
    { "igVectorMorphing", "igObject", 0x10, 0x5280a0, 0, 0 },
    { "igVertexArray", "igObject", 0x20, 0x0, mo_f1032, 4 },
    { "igVertexArray1_1", "igVertexArray", 0x30, 0x0, mo_f1033, 6 },
    { "igVertexArray2", "igNamedObject", 0x20, 0x526410, mo_f1034, 3 },
    { "igVertexArray2Helper", "igNamedObject", 0x10, 0x5262a0, mo_f1035, 1 },
    { "igVertexBlendMatrixAttr", "igVisualAttribute", 0x50, 0x5226c0, mo_f1036, 2 },
    { "igVertexBlendMatrixAttrPool", "igObjectPool", 0x20, 0x52afd0, 0, 0 },
    { "igVertexBlendMatrixListAttr", "igVisualAttribute", 0xa0, 0x522640, mo_f1038, 7 },
    { "igVertexBlendMatrixListAttrPool", "igObjectPool", 0x20, 0x52b040, 0, 0 },
    { "igVertexBlendStateAttr", "igVisualAttribute", 0x10, 0x5225b0, mo_f1040, 1 },
    { "igVertexData", "igNamedObject", 0x30, 0x5270a0, mo_f1041, 6 },
    { "igVertexDataList", "igObjectList", 0x20, 0x527100, 0, 0 },
    { "igVertexStream", "igNamedObject", 0x30, 0x5263a0, mo_f1043, 6 },
    { "igView", "igObject", 0x10, 0x0, mo_f1044, 1 },
    { "igViewList", "igObjectList", 0x20, 0x541f00, 0, 0 },
    { "igViewManager", "igEventReceiver", 0x60, 0x542690, mo_f1046, 4 },
    { "igViewMode", "igView", 0x50, 0x0, mo_f1047, 1 },
    { "igViewModel", "igModel", 0xb0, 0x542040, mo_f1048, 13 },
    { "igViewerAction", "igAction", 0x10, 0x542460, mo_f1049, 2 },
    { "igViewerDataPumpManager", "igInfoManager", 0x20, 0x542310, mo_f1050, 1 },
    { "igViewerGuiFactory", "igObject", 0x30, 0x542390, mo_f1051, 8 },
    { "igViewerLoadingFileMessage", "igMessage", 0x10, 0x542100, mo_f1052, 2 },
    { "igViewerModeChangeMessage", "igMessage", 0x10, 0x542160, mo_f1053, 2 },
    { "igViewerParameters", "igModel", 0x110, 0x5420a0, mo_f1054, 39 },
    { "igViewerRenderer", "igRenderer", 0x60, 0x5423f0, mo_f1055, 20 },
    { "igViewerSceneInfoManager", "igInfoManager", 0xd0, 0x5424c0, mo_f1056, 43 },
    { "igViewerSceneInfoManagerController", "igView", 0x20, 0x542540, mo_f1057, 2 },
    { "igViewerStatisticsManager", "igObject", 0x50, 0x5425b0, mo_f1058, 15 },
    { "igViewportAttr", "igVisualAttribute", 0x30, 0x522520, mo_f1059, 7 },
    { "igViewportResizedMessage", "igMessage", 0x20, 0x52cc80, mo_f1060, 2 },
    { "igVirtualCFuncMetaField", "igMetaField", 0x40, 0x52e130, 0, 0 },
    { "igVisualAttribute", "igAttr", 0x10, 0x0, 0, 0 },
    { "igVisualContext", "igContext", 0x140, 0x0, mo_f1063, 28 },
    { "igVisualContextAttrDefaultManager", "igAttrDefaultManager", 0x10, 0x5224b0, mo_f1064, 1 },
    { "igVisualContextCapabilityManager", "igCapabilityManager", 0x10, 0x525de0, mo_f1065, 1 },
    { "igVisualContextList", "igNonRefCountedObjectList", 0x20, 0x527170, 0, 0 },
    { "igVolume", "igObject", 0x10, 0x0, 0, 0 },
    { "igVolumeList", "igObjectList", 0x20, 0x528100, 0, 0 },
    { "igWindow", "igEventProducer", 0x10, 0x0, 0, 0 },
    { "igWindowResizeEventReceiver", "igEventReceiver", 0x10, 0x52c9f0, mo_f1070, 1 },
    { "igWindowSizeObserver", "igView", 0x10, 0x541100, 0, 0 },
    { "libBecRuntimePlugin", "igInsightPlugin", 0xb0, 0x53b6d0, mo_f1072, 39 },
    { "libNdmwRuntimePlugin", "igInsightPlugin", 0x60, 0x53de30, mo_f1073, 21 },
};
const int dw4_nmetaobjects = 1074;
