void Gap__Gui__igGuiSystemRenderer__vfunc_23(int *arg0) {
    int m[16];
    ((Obj_456610 *)arg0[5])->vX(arg0[2]);
    Matrix44_Copy(m, (char *)arg0[4] + 0x20);
    FUN_001b6ee0((void *)arg0[5], m);
}

void Gap__Gui__igGuiSystemRenderer__vfunc_24(void) {

}

void Gap__Gui__igGuiSystemRenderer__vfunc_25(int *arg0) {
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

void Gap__Gui__igGuiSystemRenderer__vfunc_26(char *arg0) {
    ((CA *)(*(int *)(arg0 + 8)))->vX(0, *(int *)(arg0 + 16) + 0x60);
    ((CB *)(*(int *)(arg0 + 24)))->vX(*(int *)(arg0 + 8));
}

