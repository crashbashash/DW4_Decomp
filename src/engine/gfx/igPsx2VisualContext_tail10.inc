namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setNativeWindowHandle(void *pHandle) {

}

/* Empty slot: returns 0 without touching the receiver. */
void *igPsx2VisualContext::getNativeWindowHandle() const {
    return 0;
}

void igPsx2VisualContext::setNativeDeviceHandle(void *pHandle) {

}

/* Empty slot: returns 0 without touching the receiver. */
void *igPsx2VisualContext::getNativeDeviceHandle() const {
    return 0;
}

void igPsx2VisualContext::setNativeRenderContextHandle(void *pHandle) {

}

/* Empty slot: returns 0 without touching the receiver. */
void *igPsx2VisualContext::getNativeRenderContextHandle() const {
    return 0;
}

void igPsx2VisualContext::setNativeVisualInfo(void *pInfo) {

}

/* igPsx2VisualContext vtable slot 45 (+0xb4): leaf that returns 0 and ignores the context, the PS2
 * backend's "nothing to report" answer for an igVisualContext virtual. */
void *igPsx2VisualContext::getNativeVisualInfo() const {
    return 0;
}

bool igPsx2VisualContext::getMaterialSpecularState() const {
    return _materialSpecularState;
}

void igPsx2VisualContext::getTextureInfo(int handle, int &width, int &height, int &format, int &source, unsigned int &textureMode) const {

}

bool igPsx2VisualContext::getTextureMatrixState(int stage) const {
    return _textureMatrixState != 0;
}
}
}

