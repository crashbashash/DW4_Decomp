void Gap__Gui__igClearRenderer__vfunc_23(O_457d60 *arg0) {
    E_457d60 *temp_a0;
    E_457d60 *temp_s0;
    temp_a0 = arg0->f8;
    temp_a0->v732(0);
    arg0->f12 = 3;
    temp_s0 = arg0->f8;
    if (temp_s0->v228(temp_s0->v200()) > 0) {
        arg0->f12 = arg0->f12 | 4;
    }
}

void Gap__Gui__igClearRenderer__vfunc_26(igClearRendererView *self)
{
    self->_visualContext->vfunc_174(self->_buffersToClear);
}

