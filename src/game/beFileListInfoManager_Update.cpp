#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igObjectDispatchView.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/beFileListInfoManager.h"
#include "dw4/game/beLoadingNode.h"
#include "dw4/game/beLua.h"
#include "dw4/game/beMessenger.h"
#include "dw4/core/igDataLists.h"
#include "dw4/scenegraph/igGroup.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igObject.h"
#include "dw4/scenegraph/igSceneInfo.h"
#include "dw4/core/igStringObj.h"
#include <stdio.h>
#include <string.h>
#include "dw4/core/igResource.h"
#include "dw4/support/emptyString.h"
#include "dw4/support/list-services.h"
extern char text_notDefined[];
extern char text_ld[];
extern char text_igb_3[];
extern char text_loadingUSA[];
extern char text_BecText_igb[];
extern char text_common_sbiallse_igb[];
extern char SOUND_11[];
extern char SEARCH_2[];
extern char MAKEBINLIST[];
extern char ISDONETRANS[];
extern char text_s_lua_2[];
extern char text_func_lua[];
extern char text_boot_lua[];
extern char LAYERCTL_6[];
extern char ORDER[];
extern char LOADING[];
extern char SET_3[];
extern char SWITCH_11[];
extern char GETLAYERNODE_2[];
extern char TEXTCTL_11[];
extern char INITIALIZE[];
extern char text_start_lua[];
extern char text_first_lua[];
extern char text_stagIS08[];
extern char text_stagIS09[];
extern char text_stagIS10[];
extern char text_stagIS12[];

/* Retained interned-string share. The stage-name object share (cases 0 and 1) and the interned
 * file-name shares (cases 1, 102, 9) are RAII locals. The copy constructor takes the extra share
 * that StringList_AppendRetained hands to the list. */
struct StringRef {
    char *p;
    char *const *ref() const { return &p; }
    StringRef(char *s) : p(s) {}
    StringRef(const StringRef &o) : p(o.p) { if (p != 0) ((int *)p)[-1] = ((int *)p)[-1] + 1; }
    ~StringRef() { char *s = p; if (s != 0) { int *hd = (int *)s - 2; int cnt = ((int *)s)[-1] - 1; ((int *)s)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd); } }
};
/* Retained share of the stage-name string object. */


static inline unsigned int igStringObj_Length(const igStringObj *s) { return s->_length; }
static inline const char *igStringObj_Text(const igStringObj *s) { return (char *)s->_buffer == 0 ? (char *)g_stringObjEmptyText : (char *)s->_buffer; }
#define EMPTY ((int *)emptyString)
#define REL_STR(p) { \
    int *q = (int *)(p); \
    if (q != 0) { \
        int *h = q - 2; \
        int r = q[-1] - 1; \
        q[-1] = r; \
        if (r == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h); \
    } }
#define REL_OBJ(o) { \
    int *q = (int *)(o); \
    if (q != 0) { \
        ((igObject *)q)->_refCount = (int)((igObject *)q)->_refCount - 1; \
        if (((unsigned long long)((long long)(int)((igObject *)q)->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)q); \
    } }
#define POOL() { \
    if (g_stringPool == 0) { \
        StringPool *pv = (StringPool *)StringPool_Allocate(0x10); \
        if (pv != 0) { pv = StringPool_Construct(pv); } \
        g_stringPool = pv; \
    } }
#define CLEAR(T, src) { \
    T *l = (T *)(src); \
    int n = l->_count; \
    int i; \
    int m; \
    int j; \
    int *o; \
    for (i = 0; i < n; i++) { \
        o = ((int **)l->_data)[i]; \
        REL_OBJ(o) \
    } \
    m = l->_count; \
    for (j = 0; j < m; j++) { \
        ((int *)l->_data)[j] = 0; \
    } \
    l->_count = 0; }

extern "C" void beFileListInfoManager_Update(beFileListInfoManager *self) {
    beSystem *sys;
    int bootScriptPath[8];
    int startScriptPath[8];
    int firstScriptPath[8];

    sys = (beSystem *)self->_system;
    if (sys->_execDvdErr <= 0) {
        switch (self->_proc) {
        default:
            self->_proc = -1;
            break;
        case -1:
            break;
        case 0: {
            int *t0;
            int *v;
            int *s1;
            int x0;
            beFileListInfo *info;
            beSystem *s0;
            if (((igInfoList *)self->_infoList)->_count <= 0) {
                self->_proc = -1;
                break;
            }
            sys->_isActive = 0;
            info = ((beFileListInfo **)((igInfoList *)self->_infoList)->_data)[0];
            s1 = (int *)info->_name;
            if (s1 != 0) { v = s1; } else { v = EMPTY; }
            if (v != 0) {
                int *nw;
                int *old;
                s1 = s1 ? s1 : EMPTY;
                s0 = (beSystem *)self->_system;
                POOL()
                nw = (int *)StringPool_Intern(g_stringPool, (const char *)s1);
                old = (int *)s0->_stageName;
                REL_STR(old)
                s0->_stageName = (int)nw;
            } else {
                int *old;
                int *nw;
                s0 = (beSystem *)self->_system;
                POOL()
                nw = (int *)StringPool_Intern(g_stringPool, text_notDefined);
                old = (int *)s0->_stageName;
                REL_STR(old)
                s0->_stageName = (int)nw;
            }
            igResource_StartAsyncLoading(g_globalContext);
            {
            igSmartPointer<igStringObj> stageObj((igStringObj *)((beSystem *)self->_system)->_globalStrObj, kRetainReference);
            igStringObj_Set(stageObj.p, (const char *)((beSystem *)self->_system)->_stageName);
            igStringObj_Erase(stageObj.p, 0, 2);
            t0 = (int *)stageObj.p; igStringObj_Insert((igStringObj *)t0, text_ld, 0, strlen(text_ld));
            { int *ta = (int *)stageObj.p; int xa = ta[3]; igStringObj_Insert((igStringObj *)ta, text_igb_3, (unsigned int)xa, strlen(text_igb_3)); }
            t0 = (int *)stageObj.p; igStringObj_Insert((igStringObj *)t0, text_loadingUSA, 0, strlen(text_loadingUSA));
            {
                int a1 = ((int *)stageObj.p)[2];
                int r;
                int a2;
                if (a1 == 0) { a2 = (int)g_stringObjEmptyText; } else { a2 = a1; }
                r = (int)igResource_LoadDirectory((igResource *)g_globalContext, (const char *)a2);
                ObjectList_AppendRetained((igObjectList *)self->_dirList, (igObject *)r);
            }
            }
            self->_proc = 1;
            break;
        }
        case 1: {
            unsigned char found;
            igObjectList *s4;
            int i;
            int idx;
            int k;
            int *s1;
            int j;
            igObjectList *s5;
            s1 = ((int **)((igDirectoryList *)self->_dirList)->_data)[0];
            if (igResource_IsDirectoryLoaded((igResource *)g_globalContext, (igDirectory *)s1) == 0) {
                break;
            }
            s4 = (igObjectList *)s1[7];
            for (k = 0; k < s4->_count; k++) {
                igInsightCore_AddInfo((igInsightCore *)self->_insight, (igObject *)((int *)s4->_data)[k]);
            }
            igResource_UnloadDirectory((igResource *)g_globalContext, (const char *)s1[5]);
            CLEAR(igDirectoryList, self->_dirList)
            s5 = (igObjectList *)((beFileListInfo **)((igInfoList *)self->_infoList)->_data)[0]->_fnames;
            if (self->_isReadOnetime == 0) {
                int *v;
                if ((char *)text_BecText_igb == 0) { v = 0; } else {
                    POOL()
                    v = (int *)StringPool_Intern(g_stringPool, text_BecText_igb);
                }
                StringRef firstName((char *)v);
                StringList_AppendRetained((igStringRefList *)self->_fnames, StringRef(firstName).ref());
                if ((char *)text_common_sbiallse_igb == 0) { v = 0; } else {
                    POOL()
                    v = (int *)StringPool_Intern(g_stringPool, text_common_sbiallse_igb);
                }
                StringRef secondName((char *)v);
                StringList_AppendRetained((igStringRefList *)self->_fnames, StringRef(secondName).ref());
                self->_isReadOnetime = 1;
                self->_onetimeCount = 2;
            }
            igSmartPointer<igStringObj> stageObj((igStringObj *)((beSystem *)self->_system)->_globalStrObj, kRetainReference);
            found = 0;
            i = 0;
            if (0 < s5->_count) {
                do {
                    unsigned int lim;
                    int *tmp;
                    int *s4n;
                    s4n = (int *)((beFileListInfo **)s5->_data)[i]->_name;
                    s4n = s4n ? s4n : EMPTY;
                    if (s4n == 0) { tmp = 0; } else {
                        POOL()
                        tmp = (int *)StringPool_Intern(g_stringPool, (const char *)s4n);
                    }
                    {
                    StringRef entryName((char *)tmp);
                    idx = -1;
                    igStringObj_Set(stageObj.p, entryName.p);
                    for (j = 0; (unsigned int)j < igStringObj_Length(stageObj); j++) {
                        const char *text = igStringObj_Text(stageObj);
                        if (text[j] == '/') { idx = j; break; }
                    }
                    if (idx == -1) { idx = 0; }
                    { int *t10 = (int *)entryName.p;
                    if (((char *)t10)[idx + 1] == 0x73) {
                        StringList_AppendRetained((igStringRefList *)self->_fnames, StringRef(entryName).ref());
                        {
                            int *o = ((int **)s5->_data)[i];
                            found = 1;
                            REL_OBJ(o)
                        }
                        List_RemoveWordAt((igDataList *)s5, i);
                        i -= 1;
                        ((int *)s5->_data)[s5->_count] = 0;
                    } }
                    }
                    i += 1;
                } while (i < s5->_count);
            }
            if (found) { self->_proc = 100; } else { self->_proc = 102; }
            break;
        }
        case 100: {
            igStringRefList *s6;
            int n;
            int k;
            if (!beFileListInfoManager_LoadNextFile(self, (igStringRefList *)self->_fnames)) {
                break;
            }
            beFileListInfoManager_AddReadInfos(self);
            CLEAR(igInfoList, self->_readInfoList)
            self->_loaded = 0;
            s6 = (igStringRefList *)self->_fnames;
            n = s6->_count;
            k = 0;
            if (0 < n) {
                int **slot;
                int *old;
                int *nw;
                int off;
                off = 0;
                do {
                    slot = (int **)((char *)s6->_data + off);
                    POOL()
                    nw = (int *)StringPool_Intern(g_stringPool, 0);
                    old = *slot;
                    REL_STR(old)
                    k += 1;
                    *slot = nw;
                    off += 4;
                } while (k < n);
            }
            s6->_count = 0;
            beMessenger_SendGroup((beMessenger *)self->_messenger, SOUND_11, SEARCH_2);
            if (beMessenger_GetBool((beMessenger *)self->_messenger, 0)) {
                self->_proc = 0x65;
                beMessenger_SendGroup((beMessenger *)self->_messenger, SOUND_11, MAKEBINLIST);
                break;
            }
            self->_proc = 0x66;
            break;
        }
        case 101:
            beMessenger_SendGroup((beMessenger *)self->_messenger, SOUND_11, ISDONETRANS);
            if (beMessenger_GetBool((beMessenger *)self->_messenger, 0) == 1) {
                self->_proc = 0x66;
                break;
            }
            break;
        case 102: {
            igObjectList *s3;
            int i;
            s3 = (igObjectList *)((beFileListInfo **)((igInfoList *)self->_infoList)->_data)[0]->_fnames;
            i = 0;
            if (0 < s3->_count) {
                do {
                    int *s4n;
                    int *tmp;
                    s4n = (int *)((beFileListInfo **)s3->_data)[i]->_name;
                    s4n = s4n ? s4n : EMPTY;
                    if (s4n == 0) { tmp = 0; } else {
                        POOL()
                        tmp = (int *)StringPool_Intern(g_stringPool, (const char *)s4n);
                    }
                    {
                    StringRef entryName((char *)tmp);
                    StringList_AppendRetained((igStringRefList *)self->_fnames, StringRef(entryName).ref());
                    }
                    i += 1;
                } while (i < s3->_count);
            }
            self->_proc = 2;
            break;
        }
        case 2:
            if (beFileListInfoManager_LoadNextFile(self, (igStringRefList *)self->_fnames)) {
                self->_loaded = 0;
                self->_proc = 3;
                break;
            }
            break;
        case 3: {
            int s0 = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject);
            if (s0 != 0) {
                sprintf((char *)bootScriptPath, text_s_lua_2, ((beSystem *)self->_system)->_stageName);
                beLua_ResetLuaState((beLua *)s0);
                beLua__RunNamedChunk((beLua *)s0, text_func_lua, (const char *)bootScriptPath);
                beLua__RunNamedChunk((beLua *)s0, text_boot_lua, (const char *)bootScriptPath);
            }
            self->_proc = 4;
            break;
        }
        case 4: {
            int cnt;
            int s1;
            int s0;
            int *lst;
            int li;
            unsigned char s3;
            int v1;
            s0 = sys->_readFileList;
            lst = (int *)*(int *)(*(int *)(*(int *)(self->_sceneInfoManager + 20) + 12) + 28);
            s1 = 0;
            if (lst != 0) { cnt = ((igInfoList *)lst)->_count; } else { cnt = 0; }
            li = (int)lst;
            if (cnt > 0) {
                igInfoList *il = (igInfoList *)li; int *ob = *(int **)il->_data;
                if (ob != 0 && igObject_IsKindOf((igObject *)ob, g_beLoadingNode_metaObject) != 0) { s1 = (int)ob; } else { s1 = 0; }
                if (s1 != 0) { s3 = beLoadingNode_IsPastPlayLimit((beLoadingNode *)s1); } else { s3 = 1; }
            } else {
                s3 = 1;
            }
            v1 = beFileListInfoManager_LoadNextFile(self, (igStringRefList *)s0);
            if (s3 && v1) {
                self->_loaded = 0;
                self->_proc = 0x14;
                if (s1 != 0) {
                    beLoadingNode_Lock((beLoadingNode *)s1);
                }
                while (((igInfoList *)self->_importantInfoList)->_count > 0) {
                    igInfoList *l;
                    int *o;
                    l = (igInfoList *)self->_importantInfoList;
                    ObjectList_AppendRetained((igObjectList *)self->_readInfoList, (igObject *)*(int *)l->_data);
                    l = (igInfoList *)self->_importantInfoList;
                    o = *(int **)l->_data;
                    REL_OBJ(o)
                    List_RemoveWordAt((igDataList *)l, 0);
                    ((int *)l->_data)[l->_count] = 0;
                }
                igResource_StopAsyncLoading(g_globalContext);
                break;
            }
            break;
        }
        case 20:
            self->_proc = 0x15;
            break;
        case 21:
            self->_proc = 5;
            break;
        case 5:
            if (beFileListInfoManager_AddReadInfos(self) != 0) {
                CLEAR(igInfoList, self->_readInfoList)
                self->_proc = 6;
                break;
            }
            break;
        case 6: {
            int i;
            igInfoList *il;
            beMessenger_SendGroup((beMessenger *)self->_messenger, LAYERCTL_6, ORDER);
            if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) > 0) {
                beMessenger_SelectGroup((beMessenger *)self->_messenger, LAYERCTL_6);
                beMessenger_AppendString((beMessenger *)self->_messenger, LOADING);
                beMessenger_AppendString((beMessenger *)self->_messenger, SET_3);
                beMessenger_DispatchSelected((beMessenger *)self->_messenger, SWITCH_11);
                if (((igInfoList *)self->_infoList)->_count > 1) {
                    for (i = 1; i < ((igInfoList *)self->_infoList)->_count; i++) {
                        int *obj;
                        int *s4;
                        igMetaObject *sceneInfoMeta;
                        int *nm;
                        sceneInfoMeta = g_igSceneInfo_metaObject;
                        s4 = ((int **)((igInfoList *)self->_infoList)->_data)[i];
                        if (sceneInfoMeta == ((igObjectDispatchView *)s4)->GetMeta()) {
                            obj = (int *)s4[5];
                            beMessenger_SelectGroup((beMessenger *)self->_messenger, LAYERCTL_6);
                            nm = (int *)obj[2];
                            nm = nm ? nm : EMPTY;
                            beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)nm);
                            beMessenger_DispatchSelected((beMessenger *)self->_messenger, GETLAYERNODE_2);
                            if (beMessenger_GetObjectCount((beMessenger *)self->_messenger) > 0) {
                                igGroup_AppendChild((igGroup *)beMessenger_GetObject((beMessenger *)self->_messenger, 0), (igNode *)obj);
                            }
                        }
                    }
                }
            }
            self->_proc = 7;
            break;
        }
        case 7: {
            int s0;
            beMessenger_SendGroup((beMessenger *)self->_messenger, TEXTCTL_11, INITIALIZE);
            s0 = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject);
            if (s0 != 0) {
                sprintf((char *)startScriptPath, text_s_lua_2, ((beSystem *)self->_system)->_stageName);
                beLua__RunNamedChunk((beLua *)s0, text_start_lua, (const char *)startScriptPath);
            }
            self->_proc = 8;
            break;
        }
        case 8:
            sys->_isActive = 1;
            self->_proc = 9;
            break;
        case 9: {
            int s0 = (int)igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject);
            int *nm;
            int *rv;
            if (s0 != 0) {
                sprintf((char *)firstScriptPath, text_s_lua_2, ((beSystem *)self->_system)->_stageName);
                beLua__RunNamedChunk((beLua *)s0, text_first_lua, (const char *)firstScriptPath);
            }
            self->_proc = -1;
            if ((char *)text_stagIS08 == 0) { rv = 0; } else {
                POOL()
                rv = (int *)StringPool_Intern(g_stringPool, text_stagIS08);
            }
            StringRef resetName0((char *)rv);
            if ((char *)text_stagIS09 == 0) { rv = 0; } else {
                POOL()
                rv = (int *)StringPool_Intern(g_stringPool, text_stagIS09);
            }
            StringRef resetName1((char *)rv);
            if ((char *)text_stagIS10 == 0) { rv = 0; } else {
                POOL()
                rv = (int *)StringPool_Intern(g_stringPool, text_stagIS10);
            }
            StringRef resetName2((char *)rv);
            if ((char *)text_stagIS12 == 0) { rv = 0; } else {
                POOL()
                rv = (int *)StringPool_Intern(g_stringPool, text_stagIS12);
            }
            StringRef resetName3((char *)rv);
            nm = (int *)((beSystem *)self->_system)->_stageName;
            if (nm == 0) { rv = 0; } else {
                POOL()
                rv = (int *)StringPool_Intern(g_stringPool, (const char *)nm);
            }
            StringRef curName((char *)rv);
            {
                int *c = (int *)curName.p;
                if ((c != (int *)resetName0.p) && (c != (int *)resetName1.p) && (c != (int *)resetName2.p) && (c != (int *)resetName3.p)) {
                    ((beSystem *)self->_system)->_isSResetEnable = 1;
                }
            }
            break;
        }
        }
    }
}
