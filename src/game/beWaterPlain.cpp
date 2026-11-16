#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igVec3f.h"
#include "dw4/igMatrix44f.h"
#include "dw4/igVertexArrayLock.h"

extern "C" {
void *igInsightCore_FindManager(int insight, int metaObject);
void igMatrix44f_PreMultiply(float *matrix, const float *by);
int igFrustCullTraversal_ClassifyBox(const float *boxMin, const float *boxMax, const float *matrix);
void Vec3f_CrossInPlace(float *a, float *b);
float sqrtf(float);
int igVertexArrayLock_Init(igVertexArrayLock *lock);
void igMatrix44f_GetTranslation(const float *matrix, float *translation);
void beMessenger_SendGroup(int messenger, const char *group, const char *message);
int beMessenger_GetMatrixCount(int messenger);
void beMessenger_GetMatrix(float *matrix, int messenger, int index);
int beMessenger_GetVec3Count(int messenger);
void beMessenger_GetVec3(float *vector, int messenger, int index);
unsigned int beMessenger_ResolveEnumValue(int messenger, int enumeration, int value);
void beMessenger_RegisterReceiver(int messenger, int receiver, char *name, int, int);
int beWaterPlain_GetMessageEnum(void);
extern int g_igViewerSceneInfoManager_metaObject[4];
extern int g_beWaterPlainInfo_metaObject[4];
extern int g_beWaterPlain_metaObject[4];
extern char WATERPLAIN[];

bool beWaterPlain_IsBoxVisible(beWaterPlain *self, const float *boxMin, const float *boxMax);
void beWaterPlain_StepWaves(beWaterPlain *self, beWaterPlainInfoRam *ram, igFloatList *heights, igFloatList *previousHeights);
void beWaterPlain_SetHeightAtCell(beWaterPlain *self, beWaterPlainInfoRam *ram, igFloatList *heights, int width, int index, float height);
void beWaterPlain_Splash(beWaterPlain *self, beWaterPlainInfoRam *ram, igFloatList *heights, const float *point, float amount);
bool beWaterPlain_IsPointInWater(beWaterPlain *self, beWaterPlainInfoRam *ram, float *point);
void beWaterPlain_Simulate(beWaterPlain *self, beWaterPlainInfoRam *ram);
void beWaterPlain_Flatten(beWaterPlain *self, beWaterPlainInfoRam *ram);
void beWaterPlain_Prepare(void);
void beWaterPlain_UpdateRam(beWaterPlain *self, beWaterPlainInfoRam *ram);
int beWaterPlain_GetInfoMeta(void);
void beWaterPlain_OnAddRam(beWaterPlain *self, int receiver, char *, int, int);
int beWaterPlain_OnMessage(beWaterPlain *self, beWaterPlainInfoRam *ram, beMessengerWork *work);
int beWaterPlain_GetMeta(void);
}

/* an igVec3fMetaField member, which reflected.h declares as float[3] */
static inline const igVec3f &vec3f(const float *field) { return *(const igVec3f *)field; }
static inline float listFloat(igFloatList *list, int i) { return ((float *)list->_data)[i]; }
static inline int listInt(igIntList *list, int i) { return ((int *)list->_data)[i]; }

static inline igFloatList *heightGrid(beWaterPlainInfoRam *ram, int index) { return ((igFloatList **)((igObjectList *)ram->_gridLists)->_data)[index]; }

static inline void igObjectListSet(igObject *object, igObjectList *list, int index) {
    if (object != 0) object->_refCount = object->_refCount + 1;
    igRelease(((igObject **)list->_data)[index]);
    if (list->_count != 0 && index >= 0 && index < list->_count) ((igObject **)list->_data)[index] = object;
}

bool beWaterPlain_IsBoxVisible(beWaterPlain *self, const float *boxMin, const float *boxMax) {
    bool visible = false;
    igViewerParameters *parameters = (igViewerParameters *)((igViewerSceneInfoManager *)igInsightCore_FindManager(self->_insight, g_igViewerSceneInfoManager_metaObject[0]))->_parameters;
    igMatrix44f viewProjection;
    float *m = (float *)&viewProjection;
    m[0] = parameters->_projectionMatrix[0];
    m[1] = parameters->_projectionMatrix[1];
    m[2] = parameters->_projectionMatrix[2];
    m[3] = parameters->_projectionMatrix[3];
    m[4] = parameters->_projectionMatrix[4];
    m[5] = parameters->_projectionMatrix[5];
    m[6] = parameters->_projectionMatrix[6];
    m[7] = parameters->_projectionMatrix[7];
    m[8] = parameters->_projectionMatrix[8];
    m[9] = parameters->_projectionMatrix[9];
    m[10] = parameters->_projectionMatrix[10];
    m[11] = parameters->_projectionMatrix[11];
    m[12] = parameters->_projectionMatrix[12];
    m[13] = parameters->_projectionMatrix[13];
    m[14] = parameters->_projectionMatrix[14];
    m[15] = parameters->_projectionMatrix[15];
    igMatrix44f_PreMultiply(viewProjection.m, parameters->_viewMatrix);
    switch (igFrustCullTraversal_ClassifyBox(boxMin, boxMax, viewProjection.m)) {
    case 1: case 3: case 4: case 5: visible = true; break;
    case 2: break;
    }
    return visible;
}

void beWaterPlain_StepWaves(beWaterPlain *self, beWaterPlainInfoRam *ram, igFloatList *heights, igFloatList *previousHeights) {
    igVertexArrayLock positions;
    igVertexArrayLock normals;
    igVertexArrayLock_Init(&positions);
    igVertexArrayLock_Init(&normals);
    {
        igVertexArrayView *vertices = (igVertexArrayView *)ram->_vertexArray;
        positions.component = 0;
        positions.firstVertex = 0;
        positions.componentIndex = 0;
        positions.count = ((igVertexArray *)vertices)->_numVerts;
        normals.component = 1;
        normals.firstVertex = 0;
        normals.componentIndex = 0;
        normals.count = ((igVertexArray *)vertices)->_numVerts;
        vertices->lock(&positions, 0);
        vertices->lock(&normals, 0);
    }
    int width = ram->_mapWidth;
    int height = ram->_mapHeight;
    int lastRow = height - 1;
    int lastColumn = width - 1;
    for (int y = 1; y < lastRow; y++) {
        for (int x = 1; x < lastColumn; x++) {
            int index = y * width + x;
            float damping = listFloat((igFloatList *)ram->_dampeningGrid, index);
            if (damping == 0.0f) continue;
            float left, right, below, above;
            int i = index - 1;
            if (i >= 0) {
                if (listFloat((igFloatList *)ram->_dampeningGrid, i) == 0.0f) left = ram->_defaultY;
                else left = listFloat(heights, listInt((igIntList *)ram->_dplist2VertexNO, i));
            } else left = ram->_defaultY;
            i = index + 1;
            if (i < ((igIntList *)ram->_dplist2VertexNO)->_count) {
                if (listFloat((igFloatList *)ram->_dampeningGrid, i) == 0.0f) right = ram->_defaultY;
                else right = listFloat(heights, listInt((igIntList *)ram->_dplist2VertexNO, i));
            } else right = ram->_defaultY;
            i = index + width;
            if (i < ((igIntList *)ram->_dplist2VertexNO)->_count) {
                if (listFloat((igFloatList *)ram->_dampeningGrid, i) == 0.0f) below = ram->_defaultY;
                else below = listFloat(heights, listInt((igIntList *)ram->_dplist2VertexNO, i));
            } else below = ram->_defaultY;
            i = index - width;
            if (i >= 0) {
                if (listFloat((igFloatList *)ram->_dampeningGrid, i) == 0.0f) above = ram->_defaultY;
                else above = listFloat(heights, listInt((igIntList *)ram->_dplist2VertexNO, i));
            } else above = ram->_defaultY;
            int vertex = listInt((igIntList *)ram->_dplist2VertexNO, index);
            const float coefA = ram->_A;
            float next = coefA * (left + right + below + above) + ram->_B * listFloat(heights, vertex)
                          - listFloat(previousHeights, vertex);
            next = damping * next;
            float maxY = ram->_maxY;
            if (next > maxY) next = maxY;
            if (next < ram->_minY) next = ram->_minY;
            if (previousHeights->_count != 0 && vertex >= 0 && vertex < previousHeights->_count)
                ((float *)previousHeights->_data)[vertex] = next;
            *(float *)(positions.getData() + vertex * positions.getStride() + 4) = next;
            unsigned int normalStride = normals.getStride();
            float cell = ram->_cellSize;
            float tangent[3];
            float bitangent[3];
            /* matching construct: permutation search — the order of the px and pz statements */
            float px = (float)x * cell;
            tangent[0] = (float)(x + 1) * cell - (float)(x - 1) * cell;
            tangent[1] = right - left;
            float pz = (float)y * cell;
            tangent[2] = pz - pz;
            bitangent[0] = px - px;
            bitangent[1] = above - below;
            bitangent[2] = (float)(y - 1) * cell - (float)(y + 1) * cell;
            Vec3f_CrossInPlace(tangent, bitangent);
            float inverseLength = 1.0f / sqrtf(tangent[0] * tangent[0] + tangent[1] * tangent[1] + tangent[2] * tangent[2]);
            tangent[0] *= inverseLength;
            tangent[1] *= inverseLength;
            tangent[2] *= inverseLength;
            float *normal = (float *)(normals.getData() + vertex * normalStride);
            normal[0] = tangent[0];
            normal[1] = tangent[1];
            normal[2] = tangent[2];
        }
    }
    igVertexArrayView *vertices = (igVertexArrayView *)ram->_vertexArray;
    vertices->unlock(&positions, 0);
    vertices->unlock(&normals, 0);
}

void beWaterPlain_SetHeightAtCell(beWaterPlain *self, beWaterPlainInfoRam *ram, igFloatList *heights, int width, int index, float height) {
    int vertex = listInt((igIntList *)ram->_dplist2VertexNO, index);
    if (vertex != -1) {
        if (heights->_count != 0 && vertex >= 0 && vertex < heights->_count) ((float *)heights->_data)[vertex] = height;
    }
}

void beWaterPlain_Splash(beWaterPlain *self, beWaterPlainInfoRam *ram, igFloatList *heights, const float *point, float amount) {
    int row = (int)((point[2] - vec3f(ram->_areaMin)[2] - ram->_pos[2]) / ram->_cellSize);
    int column = (int)((point[0] - vec3f(ram->_areaMin)[0] - ram->_pos[0]) / ram->_cellSize);
    int width = ram->_mapWidth;
    int index = column + row * width;
    igIntList *vertexNo = (igIntList *)ram->_dplist2VertexNO;
    if (index < vertexNo->_count && listInt(vertexNo, index) != -1) {
        float factor = -2.0f;
        float y = point[1];
        if (!(ram->_pos[1] + ram->_shallmin < y) && (ram->_pos[1] + ram->_shallmax < y)) factor = ram->_shalldamp;
        else if (!(ram->_pos[1] + ram->_deepmin < y) && (ram->_pos[1] + ram->_deepmax < y)) factor = ram->_deepdamp;
        factor *= amount;
        beWaterPlain_SetHeightAtCell(self, ram, heights, width, index, factor);
    }
}

bool beWaterPlain_IsPointInWater(beWaterPlain *self, beWaterPlainInfoRam *ram, float *point) {
    bool inside = false;
    float margin = ram->_cellSize;
    float y = point[1];
    float originX = ram->_pos[0];
    float minX = originX + (ram->_areaMin[0] + margin);
    float maxX = originX + (vec3f(ram->_areaMax)[0] - margin);
    float minZ = ram->_pos[2] + (ram->_areaMin[2] + margin);
    float maxZ = ram->_pos[2] + (vec3f(ram->_areaMax)[2] - margin);
    if ((!(ram->_pos[1] + ram->_shallmin < y) && (ram->_pos[1] + ram->_shallmax < y)) || (!(ram->_pos[1] + ram->_deepmin < y) && (ram->_pos[1] + ram->_deepmax < y))) {
        if (minX <= point[0] && !(maxX < point[0])) {
            if (minZ <= point[2] && !(maxZ < point[2])) inside = true;
        }
    }
    return inside;
}

static inline beWaterMoveData *nextSplash(beWaterMove *move, long long now) {
    beWaterMoveData *splash = 0;
    move->_elapseTime = now - move->_baseTime;
    if (!(move->_elapseTime < move->_maxTime)) {
        move->_baseTime = now;
        move->_elapseTime = move->_elapseTime - move->_maxTime;
        move->_targetData = 0;
    }
    beWaterMoveDataList *splashes = (beWaterMoveDataList *)move->_dataList;
    int next = move->_targetData;
    if (next < splashes->_count) {
        beWaterMoveData *candidate = ((beWaterMoveData **)splashes->_data)[next];
        if (candidate->_time <= move->_elapseTime) {
            splash = candidate;
            move->_targetData = next + 1;
        }
    }
    return splash;
}

void beWaterPlain_Simulate(beWaterPlain *self, beWaterPlainInfoRam *ram) {
    igSmartPointer<igFloatList> heights(heightGrid(ram, 0), kRetainReference);
    igSmartPointer<igFloatList> previousHeights(heightGrid(ram, 1), kRetainReference);
    for (int pass = 0; pass < 2; pass++) {
        int count;
        switch (pass) {
        case 0:
            beMessenger_SendGroup(self->_messenger, "PLAYER", "GETMATRIX");
            count = beMessenger_GetMatrixCount(self->_messenger);
            break;
        case 1:
            beMessenger_SendGroup(self->_messenger, "ENEMY", "GETMATRIX");
            count = beMessenger_GetMatrixCount(self->_messenger);
            break;
        default:
            count = 0;
        }
        for (int i = 0; i < count; i++) {
            float matrix[16];
            float point[3];
            beMessenger_GetMatrix(matrix, self->_messenger, i);
            igMatrix44f_GetTranslation(matrix, point);
            if (beWaterPlain_IsPointInWater(self, ram, point)) beWaterPlain_Splash(self, ram, heights, point, 1.0f);
        }
    }
    if (ram->_waterMove != 0) {
        int i;
        long long now = ((igInsightCore *)self->_insight)->_worldTime;
        beWaterMove *move = (beWaterMove *)ram->_waterMove;
        beWaterMoveData *splash = nextSplash(move, now);
        if (splash != 0) {
            for (i = 0; i < ((igVec3fList *)splash->_posList)->_count; i++) {
                float point[3];
                float x = ((float *)((igVec3fList *)splash->_posList)->_data)[i * 3];
                point[0] = x + ram->_pos[0];
                float y = ((float *)((igVec3fList *)splash->_posList)->_data)[i * 3 + 1];
                point[1] = y + ram->_pos[1];
                float z = ((float *)((igVec3fList *)splash->_posList)->_data)[i * 3 + 2];
                point[2] = z + ram->_pos[2];
                if (beWaterPlain_IsPointInWater(self, ram, point)) beWaterPlain_Splash(self, ram, heights, point, splash->_power);
            }
        }
    }
    beWaterPlain_StepWaves(self, ram, heights, previousHeights);
    igObjectListSet(previousHeights.p, (igObjectList *)ram->_gridLists, 0);
    igObjectListSet(heights.p, (igObjectList *)ram->_gridLists, 1);
}

static inline void fillFloatList(igFloatList *list, float value) {
    int count = list->_count;
    float *data = (float *)list->_data;
    for (int i = 0; i < count; i++) data[i] = value;
}

void beWaterPlain_Flatten(beWaterPlain *self, beWaterPlainInfoRam *ram) {
    fillFloatList(heightGrid(ram, 0), ram->_defaultY);
    fillFloatList(heightGrid(ram, 1), ram->_defaultY);
    igVertexArray *array = (igVertexArray *)ram->_vertexArray;
    igVertexArrayView *vertices = (igVertexArrayView *)array;
    igVertexArrayLock positions;
    igVertexArrayLock_Init(&positions);
    positions.component = 0;
    positions.firstVertex = 0;
    positions.componentIndex = 0;
    positions.count = array->_numVerts;
    vertices->lock(&positions, 0);
    unsigned int stride = positions.getStride();
    for (int i = 0; i < (int)array->_numVerts; i++) *(float *)(positions.getData() + i * stride + 4) = 0.0f;
    vertices->unlock(&positions, 0);
}

void beWaterPlain_Prepare(void) {
}

static inline void restartMove(beWaterPlain *self, beWaterPlainInfoRam *ram) {
    beWaterMove *move = (beWaterMove *)ram->_waterMove;
    if (move != 0) {
        move->_baseTime = ((igInsightCore *)self->_insight)->_worldTime;
        move->_elapseTime = 0;
        move->_targetData = 0;
    }
}

static inline void setState(beWaterPlainInfoRam *ram, int state) {
    ram->_st0 = state;
    ram->_st3 = 0;
    ram->_st2 = 0;
    ram->_st1 = 0;
}

void beWaterPlain_UpdateRam(beWaterPlain *self, beWaterPlainInfoRam *ram) {
    float boxMin[3];
    float boxMax[3];
    long long now = ((igInsightCore *)self->_insight)->_worldTime;
    boxMin[0] = ram->_pos[0] + vec3f(ram->_areaMin)[0];
    boxMin[1] = ram->_pos[1] - 1.0f;
    boxMin[2] = ram->_pos[2] + vec3f(ram->_areaMin)[2];
    boxMax[0] = ram->_pos[0] + vec3f(ram->_areaMax)[0];
    boxMax[1] = 1.0f + ram->_pos[1];
    boxMax[2] = ram->_pos[2] + vec3f(ram->_areaMax)[2];
    switch (ram->_st0) {
    case 0:
        beWaterPlain_Flatten(self, ram);
        ram->_updateTime = now;
        if (beWaterPlain_IsBoxVisible(self, boxMin, boxMax)) {
            restartMove(self, ram);
            setState(ram, 1);
        } else {
            setState(ram, 2);
        }
        break;
    case 1:
        if (!(now - ram->_updateTime < 16666665)) {
            ram->_updateTime = now;
            if (beWaterPlain_IsBoxVisible(self, boxMin, boxMax)) {
                beWaterPlain_Simulate(self, ram);
            } else {
                beWaterPlain_Flatten(self, ram);
                setState(ram, 2);
            }
        }
        break;
    case 2:
        if (beWaterPlain_IsBoxVisible(self, boxMin, boxMax)) {
            restartMove(self, ram);
            setState(ram, 1);
        }
        break;
    }
}

int beWaterPlain_GetInfoMeta(void) {
    return g_beWaterPlainInfo_metaObject[0];
}

void beWaterPlain_OnAddRam(beWaterPlain *self, int receiver, char *, int, int) {
    beMessenger_RegisterReceiver(self->_messenger, receiver, WATERPLAIN, 0, -1);
}

int beWaterPlain_OnMessage(beWaterPlain *self, beWaterPlainInfoRam *ram, beMessengerWork *work) {
    switch (beMessenger_ResolveEnumValue(self->_messenger, beWaterPlain_GetMessageEnum(), work->_message)) {
    case 0:
        if (beMessenger_GetVec3Count(self->_messenger) > 0 && ram->_st0 == 1) {
            float pos[3];
            beMessenger_GetVec3(pos, self->_messenger, 0);
            if (beWaterPlain_IsPointInWater(self, ram, pos))
                beWaterPlain_Splash(self, ram, heightGrid(ram, 0), pos, 1.0f);
        }
        break;
    default:
        return 0;
    }
    return 1;
}

int beWaterPlain_GetMeta(void) {
    return g_beWaterPlain_metaObject[0];
}
