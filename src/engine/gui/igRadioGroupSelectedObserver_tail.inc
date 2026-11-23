namespace Gap {
namespace Gui {

void igRadioGroup::globalValueChanged()
{
    if (_lastSelected != _model->_selected) {
        igOnOffValueObserverList *observers = _observerList;

        if (_model->_selected < observers->getCount()) {
            if (_model->_selected >= 0) {
                observers->get(_model->_selected)->setSelected(1);
            }
            if (_lastSelected >= 0) {
                _observerList->get(_lastSelected)->setSelected(0);
            }
            _lastSelected = _model->_selected;
        }
    }
}

void igRadioGroup::itemValueChanged(igOnOffValueObserver *observer)
{
    unsigned char selected = ((igOnOffModel *)observer->getModel())->_value;
    int index = _observerList->find(observer, 0);

    if (selected) {
        if (index != _model->_selected) {
            _model->_selected = index;
            _model->notifyAllViews(igNotifyEvent(igRadioGroupModel::k_selected));
        }
    } else if (index == _model->_selected) {
        if (_alwaysSelected) {
            observer->setSelected(1);
            return;
        }
        _model->_selected = -1;
        _model->notifyAllViews(igNotifyEvent(igRadioGroupModel::k_selected));
    }
}

void igRadioGroupSelectedObserver::notify(const igNotifyEvent &event)
{
    if (event._field == igRadioGroupModel::k_selected) {
        _group->globalValueChanged();
    }
}
}
}

