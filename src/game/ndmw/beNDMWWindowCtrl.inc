beNDMWWindowCtrl *beNDMWWindowCtrl_Destroy(beNDMWWindowCtrl *self, long long flags) {
    if (self) {
        self->_vtable = (int)g_beNDMWWindowCtrl_vtable;
        if (self) {
            self->_vtable = (int)g_beNDMWWindow_vtable;
            igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)&self->_modelCloseSeqNameList, -1);
            igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&self->_modelCloseRamNoList, -1);
            igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)&self->_modelCloseInfoNameList, -1);
            igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)&self->_textCloseNameList, -1);
            igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)&self->_textCloseTypeList, -1);
            beNDMWWindow_igSmartPointer_beNDMWWindow_Destruct((igSmartPointer<igObject> *)&self->_mother, -1);
            igSmartPointer_beNDMWWindowList_Destruct((igSmartPointer<igObject> *)&self->_subWindow, -1);
        }
        if ((short)flags > 0) Memory_FreeBufferAliasC(self);
    }
    return self;
}

