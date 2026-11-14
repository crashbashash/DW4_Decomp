beNDMWWindowCtrl *beNDMWWindowCtrl_Destroy(beNDMWWindowCtrl *self, long long flags) {
    if (self) {
        self->_vtable = (int)g_beNDMWWindowCtrl_vtable;
        if (self) {
            self->_vtable = (int)g_beNDMWWindow_vtable;
            ObjectRef_Destruct_001c6460(&self->_modelCloseSeqNameList, -1);
            ObjectRef_Destruct_00150eb0(&self->_modelCloseRamNoList, -1);
            ObjectRef_Destruct_001c6460(&self->_modelCloseInfoNameList, -1);
            ObjectRef_Destruct_001c6460(&self->_textCloseNameList, -1);
            ObjectRef_Destruct_001c6460(&self->_textCloseTypeList, -1);
            FUN_003b2f30((void **)&self->_mother, -1);
            FUN_003b2fb0((void **)&self->_subWindow, (short)(-1));
        }
        if ((short)flags > 0) thunk_Memory_FreeBuffer(self);
    }
    return self;
}

