/* 0x003c0120 — beNDMWMdlPEBaseInfoWork_Construct
 *
 * Constructor of the per-object info block shared by the player and enemy model controllers
 * (beNDMWMdlPlayerInfoWork and beNDMWMdlEnemyInfoWork derive from it, data/class-hierarchy.tsv).
 * It stamps the parent's vtable (beModelCtrlInfoWork), runs the default constructor of every
 * member whose type has one, then stamps its own vtable and clears the trailing list references.
 * The per-member constructors are 8..12-byte leaves that zero the member or do nothing: one
 * shared leaf per member type (igString 0x229270, igVec3f 0x19ace0), and one per object-reference
 * element type (igObjectRef<T> default constructors, 0x350f10..0x350fa0).  Each call below is
 * named by the reflected member it initialises. */
#include "dw4/reflected.h"
int FUN_001510d0();
int FUN_0019ace0();
int FUN_0019d1f0();
int FUN_001a1090();
int FUN_00229260();
int FUN_00229270();
int FUN_00350f10();
int FUN_00350f20();
int FUN_00350f30();
int FUN_00350f40();
int FUN_00350f50();
int FUN_00350f60();
int FUN_00350f70();
int FUN_00350f80();
int FUN_00350f90();
int FUN_00350fa0();
int igObject_InitHeader();
/* vtables: data/vtables.json 0x537ee0 = Gap::Bec::beModelCtrlInfoWork, 0x540520 = this class */
extern int g_beModelCtrlInfoWork_vtable_00537ee0[4];
extern int g_beNDMWMdlPEBaseInfoWork_vtable_00540520[4];
void *beNDMWMdlPEBaseInfoWork_Construct(beNDMWMdlPEBaseInfoWork *self) {
    igObject_InitHeader();
    self->_vtable = (int)(&g_beModelCtrlInfoWork_vtable_00537ee0[0]);
    FUN_00350fa0(&self->_mHp);
    FUN_00350fa0(&self->_hp);
    FUN_00229270(&self->_seqCodeName);
    FUN_00350f90(&self->_comData);
    FUN_00229260(&self->_labelSeqList);
    FUN_00229260(&self->_labelNameList);
    FUN_001510d0(&self->_labelOffsetList);
    FUN_00229270(&self->_luaBHit);
    FUN_00229270(&self->_luaWHit);
    FUN_00229270(&self->_luaFHit);
    FUN_0019d1f0(&self->_pdMoveDataList);
    FUN_00229270(&self->_wCheckName);
    FUN_00350f80(&self->_aI);
    FUN_00229270(&self->_targetMode);
    FUN_00229270(&self->_targetKind);
    FUN_00229270(&self->_targetSpc1);
    FUN_0019ace0(self->_targetPos);
    FUN_00229270(&self->_keyEventName);
    FUN_0019ace0(self->_targetDirection);
    FUN_0019ace0(self->_directionLimiter);
    FUN_0019ace0(self->_direction);
    FUN_00350f70(&self->_posLockNode);
    FUN_00350f60(&self->_posLockTrc);
    FUN_00229270(&self->_posLockModelName);
    FUN_00229270(&self->_posLockBoneName);
    FUN_0019ace0(self->_posLockOffset);
    FUN_00350f50(&self->_moveObjectList);
    FUN_00350f40(&self->_rideOnData);
    FUN_00350f30(&self->_debugHitBoxNode);
    FUN_00350f20(&self->_hitBody);
    FUN_00229270(&self->_hitParentName);
    FUN_00350f10(&self->_subCommand);
    FUN_001a1090(&self->_baseAABox);
    self->_vtable = (int)(&g_beNDMWMdlPEBaseInfoWork_vtable_00540520[0]);
    self->_dispRamNoList = 0;
    self->_dispPosNoList = 0;
    self->_timerList = 0;
    self->_isFirstList = 0;
    self->_downDataList = 0;
    self->_upDataList = 0;
    return self;
}
