#include "dw4/support/reflected.h"

#include "dw4/datapump/igDataPumpManager.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igObject.h"

#include "dw4/datapump/igDataPumpInfo.h"



#include "dw4/viewer/igViewerDataPumpManager.h"

int igViewerDataPumpManager_AddInfo(igViewerDataPumpManager *self, igObject *info) {
    if (igObject_IsKindOf(info, g_igDataPumpInfo_metaObject) != 0) {
        igDataPumpManager_AppendInfo((struct igDataPumpManager *)self->_dataPumpManager, (struct igDataPumpInfo *)info);
        igInsightCore_AddToScheduler((struct igInsightCore *)self->_insight, (igObject *)self);
        return 1;
    }
    return 0;
}

void igViewerDataPumpManager_RemoveAllInfo(igViewerDataPumpManager *self) {
    igDataPumpList *l;
    int n;
    int i;
    int off;
    int m;
    int j;
    int lim;
    int off2;
    igObject *o;

    l = (igDataPumpList *)(((igDataPumpManager *)self->_dataPumpManager)->_dataPumpList);
    n = l->_count;
    i = 0;
    if (0 < n) {
        off = 0;
        do {
            o = (igObject *)(*(int *)((char *)l->_data + off));
            if (o != 0) {
                *(int *)&o->_refCount = *(int *)&o->_refCount - 1;
                if (((unsigned long long) ((long long) *(int *)&o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
            i += 1;
            off += 4;
        } while (i < n);
    }
    m = l->_count;
    j = 0;
    if (0 < m) {
        if (m > 8) {
            lim = m - 8;
            off2 = 0;
            do {
                j += 8;
                *(int *)((char *)l->_data + off2) = 0;
                *(int *)((char *)l->_data + off2 + 4) = 0;
                *(int *)((char *)l->_data + off2 + 8) = 0;
                *(int *)((char *)l->_data + off2 + 12) = 0;
                *(int *)((char *)l->_data + off2 + 16) = 0;
                *(int *)((char *)l->_data + off2 + 20) = 0;
                *(int *)((char *)l->_data + off2 + 24) = 0;
                *(int *)((char *)l->_data + off2 + 28) = 0;
                off2 += 0x20;
            } while (j < lim);
        }
        off2 = j * 4;
        if (j < m) {
            do {
                j += 1;
                *(int *)((char *)l->_data + off2) = 0;
                off2 += 4;
            } while (j < m);
        }
    }
    l->_count = 0;
    igInsightCore_RemoveFromScheduler((struct igInsightCore *)self->_insight, (igObject *)self);
}

void igViewerDataPumpManager_Update(igViewerDataPumpManager *self) {
    igDataPumpManager_Update((struct igDataPumpManager *)self->_dataPumpManager, *(long long *)((char *)(self->_insight) + 80));
}

struct igMetaObject *igViewerDataPumpManager_GetMeta(void) {
    return g_igViewerDataPumpManager_metaObject;
}

void igViewerDataPumpManager_Start(void) {

}

void igViewerDataPumpManager_Stop(void) {

}

void igViewerDataPumpManager_Activate(void) {

}

void igViewerDataPumpManager_Deactivate(void) {

}
