namespace Gap {
namespace Gui {

void igFieldChangeView::notify(const igNotifyEvent &event)
{
    if (event._eventType == igNotifyEvent::ATTACH || _field.get() == event._field) {
        if (_synchronizer) {
            _synchronizer->synchronizeTo(this);
        }
    }
}

void igFieldChangeView::synchronizeTo(igModel *model, igMetaField *field)
{
    _field->setFromField(_model, field, model);
    _model->notifyAllViews(igNotifyEvent(_field, this));
}

void igFieldSynchronizer::appendModelAndField(igModel *model, igMetaField *field)
{
    igSmartPointer<igFieldChangeView> view = igFieldChangeView::_instantiateFromPool(getMemoryPool());

    _views->append(view);
    view->setSynchronizer(this);
    view->setField(field);
    view->setModel(model);
}

void igFieldSynchronizer::synchronizeTo(igFieldChangeView *view)
{
    int count = _views->getCount();

    for (int i = 0; i < count; i++) {
        igFieldChangeView *other = _views->get(i);

        if (other != view) {
            other->synchronizeTo(view->_model, view->_field);
        }
    }
}
}
}

int beFontImage_CountTriangles(beFontImage *image, const char *text) {
    int s = 0;
    const char *p = text;
    while (*p != 0) {
        s += ((VC_455370 *)image)->vX(*p);
        p++;
    }
    return s;
}

int beFontImage_CountTrianglesWide(beFontImage *image, const unsigned short *text) {
    int sum;
    const unsigned short *p;
    int c;
    p = text;
    sum = 0;
    while ((c = *p) != 0) {
        sum += ((VC100 *)image)->vX(c);
        p += 1;
    }
    return sum;
}

