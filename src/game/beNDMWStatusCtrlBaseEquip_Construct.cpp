/* Constructor of the equipment page of the status window controller. The base constructors stamp
 * their own vtable and null their reference cells in turn, so the object ends up stamped with each
 * ancestor table before its final one (retail RTTI; the Window and WindowCtrl pair is described in
 * docs/engine/window-object-lifetime.md). The "Construct" name is descriptive, not an original
 * method spelling. */
#include "dw4/reflected.h"
extern "C" {
int igObject_InitHeader();
}
/* vtables: Gap::Bec::beNDMWWindowCtrl, Gap::Bec::beNDMWWindow and the final
 * beNDMWStatusCtrlBaseEquip table. */
extern "C" {
extern int g_beNDMWWindowCtrl_vtable[4];
extern int g_beNDMWWindow_vtable[4];
extern int g_beNDMWStatusCtrlBaseEquip_vtable[4];
void *beNDMWStatusCtrlBaseEquip_Construct(beNDMWStatusCtrlBaseEquip *self);
}
void *beNDMWStatusCtrlBaseEquip_Construct(beNDMWStatusCtrlBaseEquip *self) {
    igObject_InitHeader();
    /* beNDMWWindow part: sub-window, parent and the five close-list references */
    self->_vtable = (int)(&g_beNDMWWindow_vtable[0]);
    self->_subWindow = 0;
    self->_mother = 0;
    self->_textCloseTypeList = 0;
    self->_textCloseNameList = 0;
    self->_modelCloseInfoNameList = 0;
    self->_modelCloseRamNoList = 0;
    self->_modelCloseSeqNameList = 0;
    self->_vtable = (int)(&g_beNDMWWindowCtrl_vtable[0]);
    /* equipment page: player list and the item-list pockets */
    self->_vtable = (int)(&g_beNDMWStatusCtrlBaseEquip_vtable[0]);
    self->_playerList = 0;
    self->_powerSocket = 0;
    self->_mainSlot = 0;
    self->_subSlot = 0;
    self->_wpuPocket = 0;
    self->_apuPocket = 0;
    self->_deviceFolder = 0;
    return self;
}
