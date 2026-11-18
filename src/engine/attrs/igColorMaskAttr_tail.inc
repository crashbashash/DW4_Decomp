/* Setter for the colour write mask: one flag per channel. */

void igColorMaskAttr_SetMask(igColorMaskAttr *self, char red, char green, char blue, char alpha) {
    self->_red = red;
    self->_green = green;
    self->_blue = blue;
    self->_alpha = alpha;
}

void igColorMaskAttr_apply(unsigned char *arg0, igPsx2VisualContext *arg1) {
    igPsx2VisualContext_SetColorMask(arg1, arg0[12], arg0[13], arg0[14], arg0[15]);
}

void igColorMaskAttr_SynchronizeDefault(R_13c8e0 *arg0, VC_13c8e0 *arg1) {
    unsigned char sp2F;
    unsigned char sp2E;
    unsigned char sp2D;
    unsigned char sp2C;

    arg1->vX(&sp2F, &sp2E, &sp2D, &sp2C);
    arg0->b0 = sp2F;
    arg0->b1 = sp2E;
    arg0->b2 = sp2D;
    arg0->b3 = sp2C;
}

