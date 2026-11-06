/* BeCameraCtrl message handler (ResolveEnumValue over the camera message table). Per message: 0/1
 * camera box on/off, 2 report the average position, 3/4 arm / disarm the info, 5 reset, 6 arm
 * unless another camera info of the same manager has the named camera, 7 report the info name, 8
 * poll for a finished shake, 9 start a shake record (SHAKEONE / SHAKEALL), 10/11 freeze toggles on
 * the camera mode, 12..14 debug zoom. Returns 1 when the message was handled. */
#include "dw4/reflected.h"
#pragma inline_depth(8)
extern "C" {
int FUN_001b1cf0(...);
int FUN_001b1dc0(...);
int FUN_00230110(float);
int FUN_00236f80(...);
int FUN_002eb010(...);
void *FUN_003694a0(...);
int FUN_003697c0(...);
int FUN_00378e40(...);
int FUN_00378e80(...);
int FUN_00378ec0(...);
int FUN_003a7a20(...);
int FUN_003a8580(...);
int FUN_00462d20(...);
void *Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
void *beBaseInfoDataList_Create(...);
int beMessenger_AppendString(...);
int beMessenger_AppendVec3(...);
int beMessenger_GetBool(...);
int beMessenger_GetBoolCount(...);
float beMessenger_GetFloat(...);
char *beMessenger_GetString(...);
int beMessenger_ResizeBool(...);
unsigned int beMessenger_ResolveEnumValue(...);
int beMessenger_SetBool(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
void *igProperty_FindByName(...);
int igStrCmp(...);
extern char DAT_004e0858[];
extern int DAT_0050e210[4];
extern int DAT_0050e228[4];
extern int DAT_0050e238[4];
extern int DAT_00585be0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_0058c790[4];
extern unsigned char GPR_00554c14;
}

/* the camera info's box data: +8 is the camera switch node whose +0x20 is the box handle */
struct SwitchNode { char pad[0x20]; int _handle; };
struct BoxData { int _vtable; unsigned int _refCount; SwitchNode *_switch; };
struct CamInfo { int _vtable; unsigned int _refCount; char *_name; char pad[0x10]; BoxData *_data; };
struct ModeFlags { char pad[0x70]; unsigned char _isEnd; unsigned char _isFreeze; };
struct CamOwner { char pad[0x18]; igObjectList *_ramList; };
struct CamInfoPtr { char pad[8]; char *_name; };

#define ALLOC_OF(owner, a) { a = igObject_GetAllocator(owner); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); }
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define NAME_OR_EMPTY(n) ((n) != 0 ? (n) : DAT_004e0858)
/* holder whose destructor drops the construction reference (the retail code releases at block exit) */
struct RPD { igObject *p; RPD(void *x) { p = (igObject *)x; } ~RPD() { igObject *q = p; if (q != 0) { q->_refCount = q->_refCount - 1; if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q); } } };
struct RPE { igObject *p; RPE(void *x) { p = (igObject *)x; } ~RPE() { igObject *q = p; if (q != 0) { q->_refCount = q->_refCount - 1; if (((unsigned long long)(long long)(int)q->_refCount & 0x7fffffULL) == 0) igObject_Destroy(q); } } };
/* create the per-info data list on first use (same shape as the matched per-frame update FUN_00378ed0).
 * Matching construct: this one is an inline member, while the first and third holders in message 9 are written out
 * as blocks; that is what orders the three holder stack slots as retail has them (block locals before inline ones). */
struct UP { static inline void Ensure(void *owner, beBaseInfoRam *ram) {
    if (ram->_dataList == 0) {
        void *alloc;
        ALLOC_OF(owner, alloc)
        RPD h(beBaseInfoDataList_Create(alloc));
        igObject *r = h.p;
        if (r != 0) r->_refCount = r->_refCount + 1;
        { igObject *o = (igObject *)ram->_dataList; REL(o) }
        ram->_dataList = (int)r;
    } } };

extern "C" int Gap__Bec__beCameraCtrl__vfunc_33(beCameraCtrl *self, beBaseInfoRam *ram, int msg);
int Gap__Bec__beCameraCtrl__vfunc_33(beCameraCtrl *self, beBaseInfoRam *ram, int msg) {
    float pos[3];
    CamInfo *info = (CamInfo *)ram->_parentInfo;
    char *wanted;
    char *nm;
    beCameraCtrlInfoRamShake *shake;

    switch (beMessenger_ResolveEnumValue(self->_messenger, FUN_003697c0(), msg)) {
    case 7:
        if (FUN_00378e80(self, info) != 0) {
            beMessenger_AppendString(self->_messenger, NAME_OR_EMPTY(info->_name));
        }
        return 1;
    case 5:
        if (FUN_00378e40(self, info) != 0) {
            ram->_isRun = 1;
            ram->_st0 = 0;
            ram->_st3 = 0;
            ram->_st2 = 0;
            ram->_st1 = 0;
        } else {
            ram->_isRun = 0;
        }
        return 1;
    case 6:
        wanted = beMessenger_GetString(self->_messenger, 0);
        if (FUN_00378e40(self, info) != 0) {
            CamOwner *owner = (CamOwner *)ram->_parentManager;
            bool found = false;
            int n = owner->_ramList->_count;
            int i = 0;
            if (0 < n) {
                CamInfoPtr *other;
                int off = 0;
                do {
                    other = *(CamInfoPtr **)((char *)owner->_ramList->_data + off);
                    if (FUN_00378e80(self, other) != 0) {
                        if (igStrCmp(NAME_OR_EMPTY(other->_name), wanted) == 0) {
                            found = true;
                            break;
                        }
                    }
                    i += 1;
                    off += 4;
                } while (i < n);
            }
            if (found) {
                ram->_isRun = 0;
            } else {
                ram->_isRun = 1;
            }
        } else {
            if (igStrCmp(wanted, NAME_OR_EMPTY(info->_name)) == 0) {
                ram->_isRun = 1;
                ram->_st0 = 0;
                ram->_st3 = 0;
                ram->_st2 = 0;
                ram->_st1 = 0;
            } else {
                ram->_isRun = 0;
            }
        }
        return 1;
    case 8:
        if (beMessenger_GetBoolCount(self->_messenger) <= 0) {
            beMessenger_ResizeBool(self->_messenger, 1);
            beMessenger_SetBool(self->_messenger, 0, 0);
        } else if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) == 1) {
            return 1;
        }
        if (ram->_isRun == 1 && FUN_00378e80(self, info) != 0) {
            switch (ram->_st0) {
            case 0:
                beMessenger_SetBool(self->_messenger, 0, 1);
                break;
            case 1:
                if (((ModeFlags *)self->_cameraMode)->_isEnd == 0) {
                    beMessenger_SetBool(self->_messenger, 0, 1);
                }
                break;
            }
        }
        return 1;
    case 2:
        pos[0] = *(float *)&self->_avgPos[0];
        pos[1] = *(float *)&self->_avgPos[1];
        pos[2] = *(float *)&self->_avgPos[2];
        beMessenger_AppendVec3(self->_messenger, pos);
        return 1;
    case 0:
        if (FUN_00378e40(self, info) != 0) {
            FUN_001b1cf0(info->_data->_switch->_handle);
        }
        return 1;
    case 1:
        if (FUN_00378e40(self, info) != 0) {
            FUN_001b1dc0(info->_data->_switch->_handle);
        }
        return 1;
    case 3:
        if (FUN_00378e40(self, info) != 0) {
            ram->_isRun = 1;
        }
        return 1;
    case 4:
        if (FUN_00378e40(self, info) != 0) {
            ram->_isRun = 0;
        }
        return 1;
    case 9:
        if (FUN_00378e40(self, info) != 0) {
            /* data list for the camera info (inline-expanded; see UP::Ensure) */
            if (ram->_dataList == 0) {
                void *alloc;
                ALLOC_OF(self, alloc)
                RPD h(beBaseInfoDataList_Create(alloc));
                igObject *r = h.p;
                if (r != 0) r->_refCount = r->_refCount + 1;
                { igObject *o = (igObject *)ram->_dataList; REL(o) }
                ram->_dataList = (int)r;
            }
            UP::Ensure(ram, ram);
            shake = (beCameraCtrlInfoRamShake *)igProperty_FindByName((void *)ram->_dataList, DAT_00585be0[0], &DAT_0050e210[0]);
            if (shake == 0) {
                void *alloc;
                ALLOC_OF(self, alloc)
                RPE created(FUN_003694a0(alloc));
                ObjectList_AppendRetained((void *)ram->_dataList, (void *)created.p);
                shake = (beCameraCtrlInfoRamShake *)created.p;
            }
            nm = beMessenger_GetString(self->_messenger, 0);
            if (DAT_00586f20[0] == 0) {
                int pool = FUN_002eb010(0x10);
                if (pool != 0) pool = StringPool_Construct(pool);
                DAT_00586f20[0] = pool;
            }
            {
                char *interned = StringPool_Intern(DAT_00586f20[0], nm);
                char *old = (char *)shake->_moveCode;
                if (old != 0) {
                    int *hd = (int *)old - 2;
                    int cnt = ((int *)old)[-1] - 1;
                    ((int *)old)[-1] = cnt;
                    if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
                }
                shake->_moveCode = (int)interned;
            }
            shake->_value = beMessenger_GetFloat(self->_messenger, 0);
            shake->_oneTime = beMessenger_GetFloat(self->_messenger, 1);
            shake->_endTime = beMessenger_GetFloat(self->_messenger, 2);
            shake->_movePoint = 0;
            /* matching construct: endTime goes through a local (as in FUN_00378ed0) to order the float loads; seconds -> ticks at 60 fps */
            { float w = shake->_endTime; w = w; FUN_003a7a20(ram, &DAT_0050e238[0], FUN_00230110((1e9f * w) / 60.0f)); w = 0.0f; }
            FUN_003a8580(ram, &DAT_0050e228[0]);
            shake->_isFirst = 1;
        }
        return 1;
    case 12:
        if (FUN_00378e40(self, info) != 0) {
            FUN_00378ec0(self, ram, 1);
            self->_debugZoom = 1.0f;
        }
        return 1;
    case 13:
        if (FUN_00378e40(self, info) != 0) {
            float z;
            FUN_00378ec0(self, ram, 1);
            z = self->_debugZoom - 0.2f;
            if (!(z <= 0.0f)) {
                self->_debugZoom = z;
            }
            FUN_00378ec0(self, ram, 0);
        }
        return 1;
    case 14:
        if (FUN_00378e40(self, info) != 0) {
            FUN_00378ec0(self, ram, 1);
            if (self->_debugZoom == 1.0f) {
                int snd = FUN_00236f80(self->_insight, DAT_0058c790[0]);
                int k = 0;
                do {
                    FUN_00462d20(snd);
                    k += 1;
                } while (k < 6);
            }
            self->_debugZoom = 0.2f + (float)self->_debugZoom; /* matching construct: the cast keeps retail's operand order */
            FUN_00378ec0(self, ram, 0);
        }
        return 1;
    case 10:
        if (ram->_isRun != 0 && FUN_00378e80(self, info) != 0) {
            ((ModeFlags *)self->_cameraMode)->_isFreeze = 1;
        }
        return 1;
    case 11:
        if (ram->_isRun != 0 && FUN_00378e80(self, info) != 0) {
            ((ModeFlags *)self->_cameraMode)->_isFreeze = 0;
        }
        return 1;
    default:
        return 0;
    }
}
