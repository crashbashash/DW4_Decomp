void igPsx2VisualContext_SetNativeWindowHandle(void) {

}

/* Empty slot: returns 0 without touching the receiver. */
int igPsx2VisualContext_GetNativeWindowHandle(void) {
    return 0;
}

void igPsx2VisualContext_SetNativeDeviceHandle(void) {

}

/* Empty slot: returns 0 without touching the receiver. */
int igPsx2VisualContext_GetNativeDeviceHandle(void) {
    return 0;
}

void igPsx2VisualContext_SetNativeRenderContextHandle(void) {

}

/* Empty slot: returns 0 without touching the receiver. */
int igPsx2VisualContext_GetNativeRenderContextHandle(void) {
    return 0;
}

void igPsx2VisualContext_SetNativeVisualInfo(void) {

}

/* igPsx2VisualContext vtable slot 45 (+0xb4): leaf that returns 0 and ignores the context, the PS2
 * backend's "nothing to report" answer for an igVisualContext virtual. */
int igPsx2VisualContext_GetNativeVisualInfo(igPsx2VisualContext *self) {
    return 0;
}

unsigned char igPsx2VisualContext_GetMaterialSpecularState(igPsx2VisualContext *self) {
    return self->_materialSpecularState;
}

void igPsx2VisualContext_GetTextureInfo(void) {

}

int igPsx2VisualContext_GetTextureMatrixState(igPsx2VisualContext *self) {
    return self->_textureMatrixState != 0;
}

