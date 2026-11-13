#include "dw4/igSmartPointer.h"

class igViewerSceneInfoManager;
typedef void (igViewerSceneInfoManager::*ViewerActionFunction)();

/* The igViewerAction instance (reflected as igViewerAction in dw4/reflected.h, which types _function as a word): the object the action calls and the member function it calls on it. */
struct ViewerAction : public igObject {
    igObject *_ref;
    ViewerActionFunction _function;
};

extern "C" ViewerAction *igViewerAction_Create(void *pool);

static inline void createAction(igSmartPointer<ViewerAction> &holder, AdoptReference) {
    igRelease(holder.p);
    holder.p = igViewerAction_Create(0);
}

/* The GUI factory's action builder: a new action bound to `ref` and `function`. */
extern "C" igSmartPointer<ViewerAction> igViewerGuiFactory_CreateAction(void *factory, igObject *ref, ViewerActionFunction function) {
    igSmartPointer<ViewerAction> action;
    createAction(action, AdoptReference());
    action->_ref = ref;
    action->_function = function;
    return action;
}
