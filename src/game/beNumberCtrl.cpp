#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/gfx/igVertexArrayLock.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/beNumberCtrl.h"
#include "dw4/game/beNumberCtrlInfo.h"
#include "dw4/game/beNumberCtrlInfoWork.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igObject.h"
#include "dw4/support/emptyString.h"

extern "C" void beNumberCtrl_Prepare(void);
extern "C" igMetaObject *beNumberCtrl_GetInfoMeta(void);
extern "C" void beNumberCtrl_UpdateRam(beNumberCtrl *self, beNumberCtrlInfoRam *ram);
extern "C" void beNumberCtrl_DisplayNumber(beNumberCtrl *self, beNumberCtrlInfoRam *ram, int number, int reserved);
extern "C" int beNumberCtrl_CalcChangeNum(beNumberCtrl *self, int difference);
extern "C" void beNumberCtrl_OnAddRam(beNumberCtrl *self, beNumberCtrlInfoRam *ram);
extern "C" int beNumberCtrl_OnMessage(beNumberCtrl *self, beNumberCtrlInfoRam *ram, beMessengerWork *work);
extern "C" igMetaObject *beNumberCtrl_GetMeta(void);
extern "C" char NUMBERCTRL_4[];

/* The messages a beNumberCtrl answers, in the order of its message enum. */
enum NumberCtrlMessage { kGetValue = 0, kSetValue = 1, kSetValueDirect = 2, kAddValue = 3 };

/* The allocator new members come from: the owner's own, or the user pool. */
static inline int allocatorFor(void *owner) {
    int allocator = (int)(((Gap::Core::igObject *)owner)->getMemoryPool());
    return (int)(g_useOwnerAllocator != 0 ? allocator : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1));
}

/* Makes `work` the ram's counter record, retaining it and releasing the one it held. */
static inline void setWork(beNumberCtrlInfoRam *ram, igObject *work) {
    if (work != 0) work->_refCount = work->_refCount + 1;
    igRelease((igObject *)ram->_work);
    ram->_work = (int)work;
}

void beNumberCtrl_Prepare(void)
{
}

igMetaObject *beNumberCtrl_GetInfoMeta(void)
{
    return g_beNumberCtrlInfo_metaObject;
}

/* Counts the displayed number toward the real one by the change step, one step a frame. */
void beNumberCtrl_UpdateRam(beNumberCtrl *self, beNumberCtrlInfoRam *ram) {
    switch (ram->_st0) {
    case 0:
    default:
        if (ram->_work == 0) {
            igSmartPointer<beNumberCtrlInfoWork> created(beNumberCtrlInfoWork_Create(allocatorFor(self)));
            setWork(ram, (igObject *)created.p);
        }
        ram->_st0 = ram->_st0 + 1;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
    case 1: {
        int next;
        beNumberCtrlInfoWork *work = (beNumberCtrlInfoWork *)ram->_work;
        if (work->_dispNum != work->_realNum) {
            next = work->_dispNum + work->_changeNum;
            if (work->_changeNum > 0) {
                if (work->_realNum < next) next = work->_realNum;
            } else if (work->_changeNum < 0) {
                if (next < work->_realNum) next = work->_realNum;
            } else {
                next = work->_realNum;
            }
            beNumberCtrl_DisplayNumber(self, ram, next, 0);
            work->_dispNum = next;
        }
        break;
    }
    case 2:
        break;
    case 3:
        break;
    }
}

/* The digit lists as the classes hold them, with their inline accessors. */
struct NumVerInsideDataList : beNumVerInsideDataList {
    int getCount() const { return _count; }
    beNumVerInsideData *get(int index) const { return ((beNumVerInsideData **)_data)[index]; }
};
struct NumVerDataList : beNumVerDataList {
    int getCount() const { return _count; }
    beNumVerData *get(int index) const { return ((beNumVerData **)_data)[index]; }
};

static inline NumVerDataList *Digits(const beNumberCtrlInfoRam &ram) { return (NumVerDataList *)ram._numList; }
static inline NumVerInsideDataList *Corners(beNumVerData *digit) { return (NumVerInsideDataList *)digit->_verDataList; }

static inline float LeftEdge(int digit, const float width) { return (float)digit * width; }

/* The vertex array of the number's geometry: the first attribute's. */
static inline igVertexArray *VertexArray(const beNumberCtrlInfoRam *ram) {
    igGeometryAttr *geometryAttr = ((igGeometryAttr **)((igObjectList *)((igGeometry *)ram->_geometry)->_attributes)->_data)[0];
    return (igVertexArray *)geometryAttr->_vertexArray;
}

/* Shows `number`: each digit takes its decimal digit, lowest first (leading zeros 0 or blank by
 * _mode, a negative number all of them), and each digit's six corners take the texture coordinates
 * of its cell in the digit strip. */
void beNumberCtrl_DisplayNumber(beNumberCtrl *self, beNumberCtrlInfoRam *ram, int number, int reserved) {
    if (number >= 0) {
        /* matching construct: register-allocator tracer — declared ahead of the loop index, the digit takes t2 and the index t1 */
        int digit;
        for (int i = 0; i < Digits(*ram)->getCount(); i++) {
            if (number != 0 || i == 0) digit = number % 10;
            else if (ram->_mode == 0) digit = 0;
            else digit = -1;
            Digits(*ram)->get(i)->_disp = digit;
            number = number / 10;
        }
    } else {
        for (int i = 0; i < Digits(*ram)->getCount(); i++) {
            if (ram->_mode == 0) Digits(*ram)->get(i)->_disp = 0;
            else Digits(*ram)->get(i)->_disp = -1;
        }
    }
    igVertexArray *array = VertexArray(ram);
    igVertexArrayLock texCoords;
    igVertexArrayLock_Init(&texCoords);
    texCoords.firstVertex = 0;
    texCoords.component = 3;
    texCoords.componentIndex = 0;
    texCoords.count = array->_numVerts;
    ((igVertexArrayView *)array)->lock(&texCoords, 0);
    int stride = texCoords.getStride();
    for (int i = 0; i < Digits(*ram)->getCount(); i++) {
        for (int k = 0; k < 6; k++) {
            beNumVerData *digit = Digits(*ram)->get(i);
            beNumVerInsideData *corner = Corners(digit)->get(k);
            float *uv = (float *)(texCoords.getData() + stride * corner->_index);
            if (digit->_disp >= 0) {
                switch (corner->_kind) {
                case 0:
                    uv[0] = LeftEdge(digit->_disp, ram->_offsetNext);
                    uv[1] = 0.0f;
                    break;
                case 1:
                    uv[0] = ram->_offsetNext + LeftEdge(digit->_disp, ram->_offsetNext);
                    uv[1] = 0.0f;
                    break;
                case 2:
                    uv[0] = LeftEdge(digit->_disp, ram->_offsetNext);
                    uv[1] = 1.0f;
                    break;
                case 3:
                    uv[0] = ram->_offsetNext + LeftEdge(digit->_disp, ram->_offsetNext);
                    uv[1] = 1.0f;
                    break;
                }
            } else {
                uv[0] = 0.0f;
                uv[1] = 0.0f;
            }
        }
    }
    ((igVertexArrayView *)array)->unlock(&texCoords, 0);
}

/* The step a frame for closing `difference`: one per 128 plus one, at most 99, never a multiple
 * of ten so the lowest digit keeps turning. */
int beNumberCtrl_CalcChangeNum(beNumberCtrl *self, int difference) {
    int step = 0;
    if (difference > 0) {
        step = difference / 128 + 1;
        if (step >= 100) step = 99;
        if (step % 10 == 0) step++;
    } else if (difference < 0) {
        step = difference / 128 - 1;
        if (step < -99) step = -99;
        if (step % 10 == 0) step--;
    }
    return step;
}

/* Registers the ram with the messenger under NUMBERCTRL, by its info's name and its ram number. */
void beNumberCtrl_OnAddRam(beNumberCtrl *self, beNumberCtrlInfoRam *ram) {
    int ramNo = ram->_ramNo;
    int *name = (int *)((beNumberCtrlInfo *)ram->_parentInfo)->_name;
    name = name != 0 ? name : (int *)emptyString;
    beMessenger_RegisterReceiver((beMessenger *)self->_messenger, (beBaseInfoRam *)ram, NUMBERCTRL_4, (const char *)name, ramNo);
}

/* GETVALUE answers the real number; SETVALUE shows a number at once, ADDVALUE adds to the real
 * number and has the display count toward it. */
int beNumberCtrl_OnMessage(beNumberCtrl *self, beNumberCtrlInfoRam *ram, beMessengerWork *work) {
    int value = work->_message;
    beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beNumberCtrl_GetMessageEnum(), (const char *)value);
    beNumberCtrlInfoWork *counter = (beNumberCtrlInfoWork *)ram->_work;
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beNumberCtrl_GetMessageEnum(), (const char *)value)) {
    case kGetValue:
        if (counter != 0) beMessenger_AppendInt((beMessenger *)self->_messenger, counter->_realNum);
        return 1;
    case kSetValue:
        if (counter == 0) {
            igSmartPointer<beNumberCtrlInfoWork> created(beNumberCtrlInfoWork_Create(allocatorFor(self)));
            setWork(ram, (igObject *)created.p);
            counter = created.p;
        }
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) == 0) return 1;
        value = beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        if (value < 0) value = 0;
        if (ram->_maxValue < value) value = ram->_maxValue;
        beNumberCtrl_DisplayNumber(self, ram, value, 0);
        counter->_dispNum = value;
        counter->_realNum = value;
        counter->_changeNum = 0;
        return 1;
    case kAddValue:
        if (counter == 0) {
            igSmartPointer<beNumberCtrlInfoWork> created(beNumberCtrlInfoWork_Create(allocatorFor(self)));
            setWork(ram, (igObject *)created.p);
            counter = created.p;
        }
        if (beMessenger_GetIntCount((beMessenger *)self->_messenger) == 0) return 1;
        value = counter->_realNum;
        counter->_realNum = value + beMessenger_GetInt((beMessenger *)self->_messenger, 0);
        if (counter->_realNum < 0) counter->_realNum = 0;
        if (ram->_maxValue < counter->_realNum) counter->_realNum = ram->_maxValue;
        counter->_changeNum = beNumberCtrl_CalcChangeNum(self, counter->_realNum - counter->_dispNum);
        return 1;
    default:
        return 0;
    }
}

igMetaObject *beNumberCtrl_GetMeta(void)
{
    return g_beNumberCtrl_metaObject;
}
