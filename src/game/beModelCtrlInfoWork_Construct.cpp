/* 0x003bf650 — beModelCtrlInfoWork constructor (finding #501: the engine
 * constructor shape).  Initialises the igObject header, stamps the class
 * vtable at 0x00537ee0 (also used by beNDMWMdlPEBaseInfoWork_Construct) and
 * zeroes the reflected data fields. */
#include "dw4/reflected.h"
extern "C" {
int igObject_InitHeader();
extern int g_beModelCtrlInfoWork_vtable[4];
void *beModelCtrlInfoWork_Construct(beModelCtrlInfoWork *self);
}
void *beModelCtrlInfoWork_Construct(beModelCtrlInfoWork *self) {
    igObject_InitHeader();
    self->_vtable = (int)(&g_beModelCtrlInfoWork_vtable[0]);
    self->_mHp = 0;
    self->_hp = 0;
    self->_seqCodeName = 0;
    self->_comData = 0;
    self->_labelSeqList = 0;
    self->_labelNameList = 0;
    self->_labelOffsetList = 0;
    self->_luaBHit = 0;
    self->_luaWHit = 0;
    self->_luaFHit = 0;
    self->_pdMoveDataList = 0;
    self->_wCheckName = 0;
    self->_aI = 0;
    self->_targetMode = 0;
    self->_targetKind = 0;
    self->_targetSpc1 = 0;
    self->_keyEventName = 0;
    self->_posLockNode = 0;
    self->_posLockTrc = 0;
    self->_posLockModelName = 0;
    self->_posLockBoneName = 0;
    self->_moveObjectList = 0;
    self->_rideOnData = 0;
    self->_debugHitBoxNode = 0;
    self->_hitBody = 0;
    self->_hitParentName = 0;
    self->_subCommand = 0;
    self->_baseAABox = 0;
    return self;
}
