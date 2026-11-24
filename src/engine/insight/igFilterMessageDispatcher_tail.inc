namespace Gap {
namespace Insight {

igMessageFilter *igFilterMessageDispatcher::getFilter(igMetaObject *msgType) const
{
    int filterCount = _defaultFilters->getCount();

    for (int i = 0; i < filterCount; i++) {
        igMessageFilter *filter = _defaultFilters->get(i);

        if (msgType == filter->_msgType.get()) {
            return filter;
        }
    }
    return 0;
}

igSmartPointer<igMessageFilter> igFilterMessageDispatcher::getFilterOrCreate(igMetaObject *msgType)
{
    igSmartPointer<igMessageFilter> filter(getFilter(msgType), kRetainReference);

    if (filter == 0) {
        igMemoryPoolView *pool = getMemoryPool();
        filter.release();
        filter.p = igMessageFilter::_instantiateFromPool(pool);
        filter->_msgType = msgType;
        _defaultFilters->append(filter.get());
    }
    return filter;
}

void igFilterMessageDispatcher::postMessage(igMessage *msg) const
{
    int filterCount = _filters->getCount();

    for (int i = 0; i < filterCount; i++) {
        igMessageFilter *filter = _filters->get(i);

        if (filter->acceptMessage(msg)) {
            int receiverCount = filter->_receivers->getCount();

            for (int j = 0; j < receiverCount; j++) {
                filter->_receivers->get(j)->messageHandler(msg);
            }
        }
    }
}
}
}

