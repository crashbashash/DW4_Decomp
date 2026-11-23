#ifndef DW4_IGNOTIFYEVENT_H
#define DW4_IGNOTIFYEVENT_H

#ifdef __cplusplus
namespace Gap {
namespace Core {
class igMetaField;
}
namespace Gui {
class igView;

/* A notification of a change in a model's data (alchemy-kit_202309 igGui/igView.h): what changed, the view that
 * started the change (it is not notified of it) and, for a field, which one and which list item. */
class igNotifyEvent {
public:
    enum LIST_EVENT_TYPE { ATTACH, DETACH, CHANGE, INSERT, REMOVE } _eventType;
    igView *_notifier;
    Core::igMetaField *_field;
    int _index;

    igNotifyEvent(LIST_EVENT_TYPE eventType, igView *notifier = 0)
        : _eventType(eventType), _notifier(notifier), _field(0) {}
    igNotifyEvent(Core::igMetaField *field, igView *notifier = 0)
        : _eventType(CHANGE), _notifier(notifier), _field(field) {}
    igNotifyEvent(LIST_EVENT_TYPE eventType, Core::igMetaField *field, int index, igView *notifier = 0)
        : _eventType(eventType), _notifier(notifier), _field(field), _index(index) {}
};
}
}
using Gap::Gui::igNotifyEvent;
#endif

#endif
