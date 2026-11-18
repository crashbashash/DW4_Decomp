/* The Viewer library's out-of-line copies of shared inlines, which the linker placed at the head of the
 * library: smart-pointer destructors and constructors for the field types of igViewerSceneInfoManager,
 * igViewerStatisticsManager and igActorManager, and igInfoManager's constructor. */
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/insight/igInfoManager.h"
#include "dw4/viewer/ViewerInlineCopies.h"

extern "C" {

igSmartPointer<igObject> *igSmartPointer_igViewerGuiFactory_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igRadioGroup_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igViewerSceneInfoManager_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igStatisticsItem_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if ((object->_refCount & 0x7fffff) == 0)
                igObject_Destroy(object);
        }
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

int *igSmartPointer_igStatisticsItem_Construct(int *p) {
    *p = 0;
    return p;
}

int *igSmartPointer_igGuiComponent_Construct(int *p) {
    *p = 0;
    return p;
}

int *igSmartPointer_igBoxComponent_Construct(int *p) {
    *p = 0;
    return p;
}

int *igSmartPointer_igViewerGuiFactory_Construct(int *p) {
    *p = 0;
    return p;
}

igInfoManager *igInfoManager_Construct(igInfoManager *self) {
    igObject_InitHeader((igObject *)self);
    self->_vtable = (int)&g_igNamedObject_vtable[0];
    self->_name = 0;
    self->_vtable = (int)&g_igInfoManager_vtable[0];
    return self;
}

}
