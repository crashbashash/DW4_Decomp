namespace Gap {
namespace Insight {

void igFilterMessageDispatcher::addFiltering(igMessageReceiver *receiver, igMetaObject *msgType)
{
    igSmartPointer<igMessageFilter> filter = getFilterOrCreate(msgType);

    addFiltering(receiver, filter.get());
}

void igFilterMessageDispatcher::addFiltering(igMessageReceiver *receiver, igMessageFilter *msgFilter)
{
    msgFilter->_receivers->appendUnique(receiver);
    _filters->appendUnique(msgFilter);
}

void igFilterMessageDispatcher::removeFiltering(igMessageReceiver *receiver, igMetaObject *msgType)
{
    igMessageFilter *filter = getFilter(msgType);

    if (filter != 0) {
        removeFiltering(receiver, filter);
    }
}

void igFilterMessageDispatcher::removeFiltering(igMessageReceiver *receiver)
{
    for (int i = _filters->getCount() - 1; i >= 0; i--) {
        removeFiltering(receiver, _filters->get(i));
    }
}

void igFilterMessageDispatcher::removeFiltering(igMessageReceiver *receiver, igMessageFilter *msgFilter)
{
    msgFilter->_receivers->removeByValue(receiver, 0);
    if (msgFilter->_receivers->getCount() == 0) {
        _filters->removeByValue(msgFilter, 0);
        _defaultFilters->removeByValue(msgFilter, 0);
    }
}

void igMessenger::registerReceiver(igMessageReceiver *receiver, igMetaObject *msgType) const
{
    _dispatcher->addFiltering(receiver, msgType);
}

void igMessenger::postMessage(igMessage *msg) const
{
    _dispatcher->postMessage(msg);
}
}
}

