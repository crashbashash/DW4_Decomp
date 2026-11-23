namespace Gap {
namespace Gui {

void igModel::appendView(igView *view)
{
    int index = _views->find(0);

    if (index < 0) {
        _views->append(view);
    } else {
        _views->set(index, view);
    }
    view->notify(igNotifyEvent(igNotifyEvent::ATTACH));
}

void igModel::removeView(igView *view)
{
    view->notify(igNotifyEvent(igNotifyEvent::DETACH));

    int index = _views->find(view);

    if (index >= 0) {
        _views->set(index, 0);
    }
}

void igModel::notifyAllViews(const igNotifyEvent &event)
{
    for (int i = 0; i < _views->getCount(); i++) {
        igView *view = _views->get(i);

        if (view && view != event._notifier) {
            view->notify(event);
        }
    }
}

void igModel::userDestruct()
{
    int count = _views->getCount();

    for (int i = 0; i < count; i++) {
        igView *view = _views->get(i);

        if (view) {
            view->setModel(0);
        }
    }
}
}
}

