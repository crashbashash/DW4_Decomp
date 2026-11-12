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

