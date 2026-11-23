namespace Gap {
namespace Gui {

void igOnOffValueObserver::notify(const igNotifyEvent &event)
{
    if (event._field == igOnOffModel::k_value || event._eventType == igNotifyEvent::ATTACH) {
        _group->itemValueChanged(this);
    }
}

void igOnOffValueObserver::setSelected(unsigned char selected)
{
    igOnOffModel *model = (igOnOffModel *)getModel();

    if (model) {
        // byte-only spelling: retail holds the field's address across the compare and store, and
        // reloads the model from this for the notification
        unsigned char *value = &model->_value;
        if (*value != selected) {
            *value = selected;
            getModel()->notifyAllViews(igNotifyEvent(igOnOffModel::k_value));
        }
    }
}

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

