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

unsigned char igPsx2VisualContext_GetMaterialSpecularState(void *arg0) {
    return *(int *)((char *)(arg0) + 1450);
}

void Gap__Gfx__igPsx2VisualContext__vfunc_121(void) {

}

int igPsx2VisualContext_GetTextureMatrixState(void *arg0) {
    return *(unsigned char *)((char *)(arg0) + 1448) != 0;
}

void igVisualContext_MakeCurrent(void) {
    igContextExt_MakeCurrent();
}

void igVisualContext_IsCurrent(void) {
    igContextExt_IsCurrent();
}

void igVisualContext_Activate(void) {

}

void igVisualContext_Deactivate(void) {

}

void igVisualContext_DrawIndexed(igPsx2VisualContextSlots_180dd0 *self)
{
    self->vfunc_69();
}

