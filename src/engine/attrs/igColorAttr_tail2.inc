igMetaObject *igColorAttr_GetMeta(void) {
    return g_igColorAttr_metaObject;
}

void igColorAttr_SetColor(igColorAttr *arg0, float *arg1) {
    *(float *)&arg0->_color[0] = arg1[0];
    *(float *)&arg0->_color[1] = arg1[1];
    *(float *)&arg0->_color[2] = arg1[2];
    *(float *)&arg0->_color[3] = arg1[3];
    igColorAttr_SynchronizeColorPacked(arg0);
}

