#include "dw4/support/reflected.h"

extern "C" {

class W { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int, int, int, int, float, float); };
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igObject.h"
#include "dw4/viewer/igViewerSceneInfoManager.h"
void igActorManager_Start(igActorManager *self);



typedef struct L { char pad[8]; int n; int p; int *arr; } L;
typedef struct A { char pad[24]; L *f24; } A;
struct ActorListOwner;
void igActorManager_AddUniqueActor(struct ActorListOwner *self, int actor);
#include "dw4/scenegraph/igActorInfo.h"
#define F24 (*(L **)&info->f24)

#include "dw4/core/igDataLists.h"

struct ActorList { char pad[8]; int n; int p12; int *arr; };
struct ActorListOwner { char pad[24]; struct ActorList *f24; };
static inline int indexOf(struct ActorList *list, const int *value) {
    int i = 0;
    int n = list->n;
    if (0 < n) {
        int *p = list->arr;
        int wanted = *value;
        do {
            if (wanted == *p) {
                return i;
            }
            i++;
            p++;
        } while (i < n);
    }
    return -1;
}

#include "dw4/viewer/igActorManager.h"

void igActorManager_Start(igActorManager *self) {
    igObject *sceneInfoManager;
    igObject *oldViewerScene;

    sceneInfoManager = igInsightCore_FindManager((igInsightCore *)self->_insight, g_igViewerSceneInfoManager_metaObject);
    if (sceneInfoManager != 0) {
        sceneInfoManager->_refCount = sceneInfoManager->_refCount + 1;
    }
    oldViewerScene = (igObject *)self->_vsim;
    if (oldViewerScene != 0) {
        oldViewerScene->_refCount = oldViewerScene->_refCount - 1;
        if ((oldViewerScene->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(oldViewerScene);
        }
    }
    self->_vsim = (int)sceneInfoManager;
    ((W *)self->_viewport)->vX(0, 0, 0, 0, 0.0f, 1.0f);
    ((W *)self->_skelViewport)->vX(0, 0, 0, 0, 0.0f, 0.2f);
}

void igActorManager_Stop(void) {

}

void igActorManager_Activate(igActorManager *self) {
    igInsightCore_AddToScheduler((igInsightCore *)self->_insight, self);
}

void igActorManager_Deactivate(igActorManager *self) {
    igInsightCore_RemoveFromScheduler((igInsightCore *)self->_insight, self);
}

/* Releases every actor the manager holds and leaves the actor list empty. */
void igActorManager_RemoveAllInfo(igActorManager *self) {
    igObjectList *actors = (igObjectList *)self->_actors;
    int count = actors->_count;
    int i;
    for (i = 0; i < count; i++) {
        igObject *actor = ((igObject **)actors->_data)[i];
        if (actor != 0) {
            actor->_refCount = actor->_refCount - 1;
            if ((actor->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(actor);
            }
        }
    }
    int remaining = actors->_count;
    int j;
    for (j = 0; j < remaining; j++) {
        ((igObject **)actors->_data)[j] = 0;
    }
    actors->_count = 0;
}

/* The list pointer is re-read in the body and in the loop test, with a `0 < n` guard. */
int igActorManager_AddInfo(int self, A *info) {
    int i;
    int off;
    if (((Gap::Core::igObject *)info)->isOfType(igActorInfo_GetMetaObject()) != 0) {
        i = 0;
        if (0 < info->f24->n) {
            off = 0;
            do {
                igActorManager_AddUniqueActor((ActorListOwner *)self, *(int *)((char *)F24->arr + off));
                i++;
                off += 4;
            } while (i < F24->n);
        }
        return 1;
    }
    return 0;
}

void igActorManager_AddUniqueActor(struct ActorListOwner *self, int actor) {
    struct ActorList *list = self->f24;
    /* matching construct: retail keeps the value in a stack slot */
    int value = actor;
    if (indexOf(list, (const int *)&value) < 0) {
        ObjectList_AppendRetained((igObjectList *)self->f24, (igObject *)actor);
    }
}

void igActorManager_Update(void) {

}

igMetaObject *igActorManager_GetMeta(void) {
    return g_igActorManager_metaObject;
}

}
