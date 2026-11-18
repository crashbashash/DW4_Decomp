void igTransform_Transform(void *arg0, int arg1) {
    void *self = arg0;
    arg0 = *(void **)((char *)self + 104);
    if (arg0 == 0) {
        void *p = (char *)self + 0x20;
        igMatrix44f_Multiply((float *)p, (const float *)p, (const float *)arg1);
        return;
    }
    ((VC_1dd010 *)arg0)->vX(arg1);
}

