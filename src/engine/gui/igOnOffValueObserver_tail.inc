void igOnOffValueObserver_OnModelChange(igOnOffValueObserver *self, void *arg1) {
    if ((*(int *)((char *)arg1 + 8) == (int)g_igOnOffModel_valueMetaField) || (*(int *)((char *)arg1 + 0) == 0)) {
        FUN_00457ab0((igRadioGroup *)(self->_group), (igRadioGroupSelectedObserver *)self, (int)self);
    }
}

void FUN_00457c40(struct S_457c40 *arg0, unsigned char arg1) {
    unsigned char temp_a2;
    struct T_457c40 *temp_v1;
    unsigned char *pb;

    temp_v1 = arg0->t;
    if (temp_v1 != 0) {
        temp_a2 = temp_v1->b;
        pb = &temp_v1->b;
        if (temp_a2 != arg1) {
            *pb = arg1;
            igNotifyEvent sp((Gap::Core::igMetaField *)g_igOnOffModel_valueMetaField);
            ((Gap::Gui::igModel *)arg0->t)->notifyAllViews(sp);
        }
    }
}

namespace Gap {
namespace Gui {

void igRenderer::setVisualContext(igVisualContext *context)
{
    if (_visualContext != context) {
        if (_visualContext)
            terminateDrawing();
        _visualContext = context;
        if (_visualContext)
            initializeDrawing();
    }
}
}
}

