void Gap__Attrs__igCopyRenderDestinationAttr__vfunc_24(S_13c940 *arg0, Q_13c940 *arg1) {
    int v;
    if (arg0->f16 != 0) v = arg0->f16->f20;
    else v = arg1->getId();
    switch (arg0->mode) {
    case 1:
        if (arg0->f24->f36 < 0) arg0->f24->touch(arg1);
        Gap__Gfx__igPsx2VisualContext__vfunc_171(arg1, v, arg0->f24->f36, arg0->f28, arg0->f32, arg0->f44, arg0->f48, arg0->f36, (long long)arg0->f40);
        return;
    case 2:
        Gap__Gfx__igPsx2VisualContext__vfunc_172(arg1, v, arg0->f20, arg0->f28, arg0->f32, arg0->f44, arg0->f48);
        break;
    case 0:
        break;
    case 3: case 4:
        break;
    default:
        break;
    }
}

/* Empty override of attribute vtable slot 26, which igLightAttr implements as a reset to the
 * unassigned state: the copy-render-destination attribute has nothing to reset here. */
void Gap__Attrs__igCopyRenderDestinationAttr__vfunc_26(void) {

}

