void igGuiSystemRenderer_InitializeDrawing(int *arg0) {
    int m[16];
    ((Obj_456610 *)arg0[5])->vX(arg0[2]);
    igMatrix44f_Copy((float *)m, (const float *)((char *)arg0[4] + 0x20));
    igCommonTraversal_SetViewMatrix((int)((void *)arg0[5]), (int *)m);
}

void igGuiSystemRenderer_ReleaseDrawing(void) {

}

void igGuiSystemRenderer_Traverse(int *arg0) {
    igObject *temp_v0;
    igObject *temp_a0_4;
    ((C29 *)arg0[5])->vX();
    ((C23 *)arg0[5])->vX(arg0[3]);
    temp_v0 = ((C28_456670 *)arg0[5])->vX();
    if (temp_v0 != 0) {
        temp_v0->_refCount = temp_v0->_refCount + 1;
    }
    temp_a0_4 = (igObject *)arg0[6];
    if (temp_a0_4 != 0) {
        temp_a0_4->_refCount = temp_a0_4->_refCount - 1;
        if ((temp_a0_4->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0_4);
        }
    }
    arg0[6] = (int)temp_v0;
}

void igGuiSystemRenderer_Render(igGuiSystemRenderer *self) {
    ((CA *)(self->_visualContext))->vX(0, self->_model + 0x60);
    ((CB *)(self->_displayListAttr))->vX(self->_visualContext);
}

