#ifndef DW4_MATHS_LIBRARY_H
#define DW4_MATHS_LIBRARY_H

#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" {

struct OpTable;
struct InstanceNode;
typedef struct M { char pad4[4]; int f4; char pad8[10]; short f18; } M;
typedef struct R { char pad12[12]; int f12; } R;
int igMetaObject_RunStaticInit(...);
struct S;
struct V3;
struct B;
struct B2;
struct P;
struct B4;
struct V;
struct Box;
struct Plane;
struct S2;
struct P2;
struct V4;
struct S18d110;
struct A;
struct B5;
struct S4;
struct S5;
struct IndexedWordPairKey;
struct PairKeyedItem;
struct IndexedSlotKey;
struct IndexedWordKey;
class igVec3fMetaFieldView;
typedef enum Intersection {
    kDisjoint,
    kIntersecting
} Intersection;
int FUN_0018ac80(...);

int igMetaEnum_Create(...);

extern int DAT_0048ad10[4];
extern int DAT_0048ad30[4];
extern int DAT_004e0960[4];
extern int DAT_00560f00[4];

void FUN_00186e40(void);
void FUN_00186f70(void);
void FUN_00190370(void);

extern unsigned char DAT_00554b7c;

igMetaObject *igMetaObject_Create(int);

int Memory_GetAllocatorBySelector(...);

extern igMetaObject *g_igVolume_metaObject[4];
extern int g_metadataAllocatorKey[4];

void FUN_00186b20(void);
igMetaObject *igVolume_GetMetaObject(void);
void igVolume_Register(void);

extern char igObject_GetMetaObject_ParentAccessor[];

void thunk_igVolume_GetMetaObject(void);
void FUN_00186bc0(void);

extern char igObject_Register[];
extern char igVolume_className[];

int igMetaObject_RegisterClass(...);

extern int igVolume_InitFields_00186bb0[4];

int FUN_002fe480(...);
void thunk_FUN_0018f4a0(void);
void FUN_0018ec40(void);
int FUN_002fe490(...);
void FUN_0018edb0(int meta);
void FUN_0018f4a0(void);
void FUN_00186d20(void);
M *igMetaObject_CreateInstance(...);

extern igMetaObject *g_igVolumeList_metaObject[4];

igMetaObject *igVolumeList_GetMetaObject(void);

struct Obj { int *vt; char pad[28]; };

int igObject_InitHeader(...);

extern int DAT_00528100[4];

extern void *g_objectSystem[4];
void igVolumeList_Register(void);

extern char igObjectList_GetPublishedMetaObject[];

void thunk_igVolumeList_GetMetaObject(void);

extern char igObjectList_Register[];
extern char g_igVolumeList_callbackList[];
extern char igVolumeList_className[];

extern igMetaObject *g_igVectorMorphing_metaObject[4];
igMetaObject *FUN_00186db0(void);

struct Obj2 { int *vt; int pad; };
extern int DAT_005280a0[4];

void igVectorMorphing_Register(void);

extern char thunk_igVectorMorphing_GetMetaObject_00186ec0[];

void FUN_00186ed0(void);

extern char igVectorMorphing_className[];

void FUN_0018ec10(void);
extern igMetaObject *g_igVectorBlending_metaObject[4];
igMetaObject *FUN_00186ee0(void);

struct Obj3 { int *vt; char pad[4]; };
extern int DAT_00528040[4];

void igVectorBlending_Register(void);

extern char thunk_igVectorBlending_GetMetaObject_00186ff0[];

void FUN_00187000(void);

extern char igVectorBlending_className[];

void FUN_0018e9b0(void);
extern igMetaObject *g_igVec4ucMetaField_metaObject[4];
void FUN_001870f0(void);
igMetaObject *FUN_00187010(void);
int StringChunk_ReleaseHeader(...);
int igMetaField_Init(...);

extern int DAT_005271e0[4];
extern int g_igMetaField_vtable[4];
union U { int vt; char b[64]; };

void igVec4ucMetaField_Register(void);

extern char thunk_igVec4ucMetaField_GetMetaObject_00187170[];
extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char g_igVec4ucMetaField_callbackList[];
extern char igVec4ucMetaField_className[];

extern int g_igMetaField_metaObject[4];

R *FUN_002fc250(...);
int MetaRefList_AppendRetained(...);
int igMetaField_FinalizeDescriptor(...);
void igObject_Destroy(void *);


extern M *DAT_00560f30[4];
void FUN_001873c0(void);
extern igMetaObject *g_igVec4fMetaField_metaObject[4];
igMetaObject *igVec4fMetaField_GetMetaObject(void);

struct Obj4 { int *vt; int pad[2]; };
struct F { struct Obj4 obj; int *ref; int pad[12]; };
int FUN_002fbfe0(struct F *);
extern int DAT_005272e0[4];

void igVec4fMetaField_Register(void);
void thunk_igVec4fMetaField_GetMetaObject(void);

extern char g_igVec4fMetaField_callbackList[];
extern char igVec4fMetaField_className[];


extern int g_igVec4fMetaField_descriptor[4];
void FUN_00187680(void);
extern igMetaObject *g_igVec4fArrayMetaField_metaObject[4];
igMetaObject *igVec4fArrayMetaField_GetMetaObject(void);

extern int DAT_005273e0[4];

void igVec4fArrayMetaField_Register(void);
void thunk_igVec4fArrayMetaField_GetMetaObject(void);

extern char igVec4fMetaField_GetPublishedMetaObject[];
extern char g_igVec4fArrayMetaField_callbackList[];
extern char igVec4fArrayMetaField_className[];

void igVec4fArrayMetaField_InitFields(void);
int FUN_002ea4b0(...);
int igMetaObject_CreateFields(...);
int igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
int igMetaObject_NameFields(...);

extern int DAT_0048ad70[4];
extern int DAT_0048ad78[4];
extern int DAT_0048ad80[4];
extern int DAT_0048ad88[4];

extern M * g_igVec4fArrayMetaField_descriptor[4];

void FUN_001879b0(void);
extern igMetaObject *g_igVec3fMetaField_metaObject[4];
igMetaObject *igVec3fMetaField_GetMetaObject(void);

struct Obj5 { int *vt; char pad[8]; char *m; char pad2[48]; };
extern int DAT_005274e0[4];

void igVec3fMetaField_Register(void);
void thunk_igVec3fMetaField_GetMetaObject(void);

extern char g_igVec3fMetaField_callbackList[];
extern char igVec3fMetaField_className[];


extern int g_igVec3fMetaField_descriptor[4];
void FUN_00187c70(void);
extern igMetaObject *g_igVec2fMetaField_metaObject[4];
igMetaObject *igVec2fMetaField_GetMetaObject(void);

typedef struct { int *vt; int p1; int p2; void *str; int pad[12]; } Obj6;
extern int DAT_005275e0[4];

void igVec2fMetaField_Register(void);
void thunk_igVec2fMetaField_GetMetaObject(void);

extern char g_igVec2fMetaField_callbackList[];
extern char igVec2fMetaField_className[];


extern int g_igVec2fMetaField_descriptor[4];
void FUN_00187f30(void);

extern igMetaObject *g_igSphere_metaObject[4];

igMetaObject *igSphere_GetMetaObject(void);

extern int DAT_00527fe0[4];
union U2 { int vt; char b[32]; };

void igSphere_Register(void);
void thunk_igSphere_GetMetaObject(void);

extern char igVolume_GetPublishedMetaObject[];

void thunk_FUN_0018d480(void);

extern char igSphere_className[];

void igSphere_InitFields(void);
void FUN_0018e470(igVec3fMetaFieldView *self, const float *value);

int FUN_002e3810(int, float);
extern int DAT_0048ada0[4];
extern int DAT_0048ada8[4];
extern int DAT_0048adb0[4];
extern int DAT_0048adb8[4];

void FUN_0018d480(void);

extern igMetaObject *g_igRayList_metaObject[4];

void FUN_00188190(void);
igMetaObject *igRayList_GetMetaObject(void);

extern int DAT_00527f70[4];

void igRayList_Register(void);
void thunk_igRayList_GetMetaObject(void);

extern char g_igRayList_callbackList[];
extern char igRayList_className[];

void FUN_00188340(void);

extern igMetaObject *g_igRay_metaObject[4];

igMetaObject *igRay_GetMetaObject(void);

struct Obj7 { int *vt; char pad[44]; };
extern int DAT_00527f10[4];

void igRay_Register(void);
void thunk_igRay_GetMetaObject(void);

extern char igRay_className[];

void igRay_InitFields(void);

extern int DAT_0048adc8[4];
extern int DAT_0048add8[4];
extern int DAT_0048ade8[4];
extern int DAT_0048adf8[4];

void FUN_00188520(void);
extern igMetaObject *g_igPlane_metaObject[4];
igMetaObject *igPlane_GetMetaObject(void);

extern int DAT_00527eb0[4];

void igPlane_Register(void);
void thunk_igPlane_GetMetaObject(void);
void thunk_FUN_0018c660(void);

extern char igPlane_className[];

void igPlane_InitFields(void);

extern int DAT_0048ae08[4];
extern int DAT_0048ae18[4];
extern int DAT_0048ae28[4];
extern int DAT_0048ae38[4];

void FUN_0018c660(void);
void FUN_00188780(void);

extern igMetaObject *g_igMatrix44fMetaField_metaObject[4];

igMetaObject *igMatrix44fMetaField_GetMetaObject(void);

extern int DAT_005276e0[4];

void igMatrix44fMetaField_Register(void);
void thunk_igMatrix44fMetaField_GetMetaObject(void);

extern char g_igMatrix44fMetaField_callbackList[];
extern char igMatrix44fMetaField_className[];

extern int g_igMatrix44fMetaField_descriptor[4];
void FUN_001889f0(void);
extern igMetaObject *g_igGetCenterFunctionList_metaObject[4];
igMetaObject *igGetCenterFunctionList_GetMetaObject(void);

extern int DAT_00527e50[4];

void igGetCenterFunctionList_Register(void);

extern char igDataList_GetPublishedMetaObject[];

void thunk_igGetCenterFunctionList_GetMetaObject(void);

extern char igDataList_Register[];
extern char igGetCenterFunctionList_className[];

void FUN_00188b50(void);
extern igMetaObject *g_igIsEmptyFunctionList_metaObject[4];
igMetaObject *igIsEmptyFunctionList_GetMetaObject(void);

extern int DAT_00527df0[4];
union U3 { int vt; char b[32]; };

void igIsEmptyFunctionList_Register(void);
void thunk_igIsEmptyFunctionList_GetMetaObject(void);

extern char igIsEmptyFunctionList_className[];

void FUN_00188cb0(void);
extern igMetaObject *g_igEmptyFunctionList_metaObject[4];
igMetaObject *igEmptyFunctionList_GetMetaObject(void);

extern int DAT_00527d90[4];

void igEmptyFunctionList_Register(void);
void thunk_igEmptyFunctionList_GetMetaObject(void);

extern char igEmptyFunctionList_className[];

void FUN_00188e10(void);
extern igMetaObject *g_igTransformFunctionList_metaObject[4];
igMetaObject *igTransformFunctionList_GetMetaObject(void);

extern int DAT_00527d30[4];

void igTransformFunctionList_Register(void);
void thunk_igTransformFunctionList_GetMetaObject(void);

extern char igTransformFunctionList_className[];

void FUN_00188f70(void);
extern igMetaObject *g_igContainsVecFunctionList_metaObject[4];
igMetaObject *igContainsVecFunctionList_GetMetaObject(void);

extern int DAT_00527cd0[4];

void igContainsVecFunctionList_Register(void);
void thunk_igContainsVecFunctionList_GetMetaObject(void);

extern char igContainsVecFunctionList_className[];

void FUN_001890d0(void);
extern igMetaObject *g_igExtendByVecFunctionList_metaObject[4];
igMetaObject *igExtendByVecFunctionList_GetMetaObject(void);

extern int DAT_00527c70[4];

void igExtendByVecFunctionList_Register(void);
void thunk_igExtendByVecFunctionList_GetMetaObject(void);

extern char igExtendByVecFunctionList_className[];

void FUN_00189230(void);
extern igMetaObject *g_igContainsRayFunctionList_metaObject[4];
igMetaObject *igContainsRayFunctionList_GetMetaObject(void);

extern int DAT_00527c10[4];
union U4 { int vt; char b[32]; };

void igContainsRayFunctionList_Register(void);
void thunk_igContainsRayFunctionList_GetMetaObject(void);

extern char igContainsRayFunctionList_className[];

void FUN_00189390(void);
extern igMetaObject *g_igExtendByRayFunctionList_metaObject[4];
igMetaObject *igExtendByRayFunctionList_GetMetaObject(void);

extern int DAT_00527bb0[4];

void igExtendByRayFunctionList_Register(void);
void thunk_igExtendByRayFunctionList_GetMetaObject(void);

extern char igExtendByRayFunctionList_className[];

void FUN_001894f0(void);
extern igMetaObject *g_igRayIntersectionFunctionList_metaObject[4];
igMetaObject *igRayIntersectionFunctionList_GetMetaObject(void);

extern int DAT_00527b50[4];

void igRayIntersectionFunctionList_Register(void);
void thunk_igRayIntersectionFunctionList_GetMetaObject(void);

extern char igRayIntersectionFunctionList_className[];

void FUN_00189650(void);
extern igMetaObject *g_igContainsFunctionList_metaObject[4];
igMetaObject *igContainsFunctionList_GetMetaObject(void);

extern int DAT_00527af0[4];

void igContainsFunctionList_Register(void);
void thunk_igContainsFunctionList_GetMetaObject(void);

extern char igContainsFunctionList_className[];

void FUN_001897b0(void);
extern igMetaObject *g_igExtendByFunctionList_metaObject[4];
igMetaObject *igExtendByFunctionList_GetMetaObject(void);

typedef struct { int *vt; int pad[7]; } Obj8;
extern int DAT_00527a90[4];

void igExtendByFunctionList_Register(void);
void thunk_igExtendByFunctionList_GetMetaObject(void);

extern char igExtendByFunctionList_className[];

void FUN_00189910(void);
extern igMetaObject *g_igIntersectionFunctionList_metaObject[4];
igMetaObject *igIntersectionFunctionList_GetMetaObject(void);

extern int DAT_00527a30[4];

void igIntersectionFunctionList_Register(void);
void thunk_igIntersectionFunctionList_GetMetaObject(void);

extern char igIntersectionFunctionList_className[];

extern igMetaObject *g_igMatrix44fList_metaObject[4];
void FUN_00189a80(void);
igMetaObject *igMatrix44fList_GetMetaObject(void);

extern int DAT_005279d0[4];

void igMatrix44fList_Register(void);
void thunk_igMatrix44fList_GetMetaObject(void);

extern char igMatrix44fList_className[];
extern int igMatrix44fList_InitFields_00189b10[4];

int ObjectPointerList_FindIndex(...);
int igMetaObject_FinalizeAndReplaceField(...);
void **igMetaObject_FindFieldByName(...);
extern int DAT_004e0ca0[4];
extern int DAT_00561080[4];

void FUN_00189b10(void);

class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };

void FUN_00189cf0(void);
extern igMetaObject *g_igQuaternionfList_metaObject[4];
igMetaObject *igQuaternionfList_GetMetaObject(void);

extern int DAT_00527970[4];

void igQuaternionfList_Register(void);
void thunk_igQuaternionfList_GetMetaObject(void);

extern char igQuaternionfList_className[];
extern int igQuaternionfList_InitFields_00189d80[4];

extern int DAT_00561090[4];

void FUN_00189d80(void);
void FUN_00189f10(void);
extern igMetaObject *g_igVec4ucList_metaObject[4];
igMetaObject *igVec4ucList_GetMetaObject(void);

extern int DAT_00527910[4];

void igVec4ucList_Register(void);
void thunk_igVec4ucList_GetMetaObject(void);

extern char igVec4ucList_className[];
extern int igVec4ucList_InitFields_00189fa0[4];


extern int DAT_005610a0[4];

void FUN_00189fa0(void);
void FUN_0018a180(void);
extern igMetaObject *g_igVec3fList_metaObject[4];
igMetaObject *igVec3fList_GetMetaObject(void);

extern int DAT_00524880[4];

void igVec3fList_Register(void);
void thunk_igVec3fList_GetMetaObject(void);

extern char igVec3fList_className[];
extern int igVec3fList_InitFields_0018a210[4];

extern int DAT_005610c0[4];

void FUN_0018a210(void);
void FUN_0018a3a0(void);
extern igMetaObject *g_igVec2fList_metaObject[4];
igMetaObject *igVec2fList_GetMetaObject(void);

extern int DAT_005278b0[4];

void igVec2fList_Register(void);
void thunk_igVec2fList_GetMetaObject(void);

extern char igVec2fList_className[];
extern int igVec2fList_InitFields_0018a430[4];


extern int DAT_005610d0[4];

void FUN_0018a430(void);

extern igMetaObject *g_igAABoxList_metaObject[4];

void FUN_0018a5d0(void);
igMetaObject *igAABoxList_GetMetaObject(void);

extern int DAT_00527840[4];

void igAABoxList_Register(void);
void thunk_igAABoxList_GetMetaObject(void);

extern char g_igAABoxList_callbackList[];
extern char igAABoxList_className[];

void FUN_0018a780(void);

extern igMetaObject *g_igAABox_metaObject[4];

igMetaObject *igAABox_GetMetaObject(void);

extern int DAT_005277e0[4];

void igAABox_Register(void);
void thunk_igAABox_GetMetaObject(void);
void thunk_FUN_0018a8f0(void);

extern char igAABox_className[];

void igAABox_InitFields(void);

extern int DAT_0048ae58[4];
extern int DAT_0048ae60[4];
extern int DAT_0048ae68[4];
extern int DAT_0048ae70[4];

void FUN_0018a8f0(void);
int FUN_0018afa0(igAABox *box, igSphere *sphere);
int FUN_0018b050(struct B *arg0, struct B *arg1);
int FUN_0018b110(void *arg0, void *arg1);
int FUN_0018b170(...);
int FUN_0018b300(igAABox *box, void *other);
int FUN_0018b350(struct B2 *arg0, struct B2 *arg1);
int FUN_0018b450(float *a, float *b);
int FUN_0018b540(void *parg0, struct P *b);
int FUN_0018b630(struct B4 *arg0, struct V *arg1);

void FUN_0018b6b0(void);

void FUN_0018b890(struct Box *arg0, float *arg1);
int thunk_FUN_0018ac80();
void FUN_0018b990(float *arg0, float *arg1);
void FUN_0018b730(igAABox *box, igAABox *other);
void FUN_0018b7d0(igAABox *box, igSphere *sphere);
void FUN_0018b940(igAABox *box);
int FUN_0018b970(void *arg0);
void FUN_0018fbc0(void *arg0, void *arg1, int arg2);
void FUN_0018fc30(struct IndexedWordPairKey *arg0, struct IndexedWordPairKey *arg1, int arg2);
void FUN_0018fca0(struct PairKeyedItem *a, struct PairKeyedItem *b, int v);
void FUN_0018fd10(int *arg0, int arg1);
void FUN_0018fd50(struct IndexedSlotKey *arg0, int arg1);
void FUN_0018fd90(struct IndexedWordKey *arg0, int arg1);
void FUN_0018fdd0(igMetaObject *meta, int arg1);
void FUN_0018fe10(int *arg0, int arg1);
void FUN_0018fe50(struct IndexedSlotKey *arg0, int arg1);
void FUN_0018fe90(struct IndexedWordKey *arg0, int arg1);
void FUN_0018fed0(igMetaObject *meta, int arg1);
void FUN_0018ff10(int *arg0, int arg1);

typedef struct S { int pad[2]; float f[6]; } S;

typedef struct V3 { float x, y, z; } V3;

struct B { char pad[8]; float f8; float f12; float f16; float f20; float f24; float f28; };

int FUN_0018d060(struct P2 *p, float *v);

enum { kOutside, kInside };

int FUN_0018c920(void *arg0, void *arg1);

typedef struct B2 { char p0[8]; float x0, y0, z0, x1, y1, z1; } B2;

int FUN_0018ffa0(void **arg0, void **arg1);

typedef struct B3 { char p0[8]; float f8; char p1[8]; float f20; } B3;
typedef struct P { char p0[8]; float f8; float f12; float f16; float f20; float f24; float f28; float f32; } P;

struct B4 { char pad[8]; float lox; float loy; float loz; float hix; float hiy; float hiz; };
struct V { float x; float y; float z; };

struct Box { char pad[8]; float mn[3]; float mx[3]; };

typedef struct { unsigned int mant : 23; unsigned int exp : 8; unsigned int sign : 1; } FB;
static inline bool isNeg(float x) { return ((FB *)&x)->sign != 0; }
static inline bool isPos(float x) { return !isNeg(x); }
static inline bool isZero(float x) { return x >= -5e-7f && x <= 5e-7f; }
struct V2 { float x, y, z; V2() {} V2(float a, float b, float c) { x = a; y = b; z = c; }
 float dot(const V2 &o) const { return x * o.x + y * o.y + z * o.z; }
 V2 operator-(const V2 &o) const { return V2(x - o.x, y - o.y, z - o.z); }
 V2 operator+(const V2 &o) const { return V2(x + o.x, y + o.y, z + o.z); }
 V2 operator*(float s) const { return V2(x * s, y * s, z * s); }
 void madd(const V2 &a, const V2 &b, float s) { x = a.x + s * b.x; y = a.y + s * b.y; z = a.z + s * b.z; }
 void madd2(const V2 &a, float s, const V2 &b) { float m = s * b.x; x = a.x + m; m = s * b.y; y = a.y + m; m = s * b.z; z = a.z + m; }
 void sub(const V2 &a, const V2 &b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; }
 void add(const V2 &a, const V2 &b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; }
 void scale(const V2 &a, float s) { x = a.x * s; y = a.y * s; z = a.z * s; }
};
static inline V2 operator*(float s, const V2 &a) { return V2(s * a.x, s * a.y, s * a.z); }
static inline V2 sub2(const V2 &a, const V2 &b) { V2 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
static inline V2 add2(const V2 &a, const V2 &b) { V2 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r; }
static inline float dotv(V2 a, V2 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
static inline float madd_(float o, float t, float d) { return o + t * d; }
struct Ray { char pad[8]; V2 o; V2 d; float maxT; };

float sqrtf(float);
void FUN_00192dd0(float *arg0, float *arg1, float *arg2);

static inline float dot(const V2 *a, const V2 *b) { return a->x * b->x + a->y * b->y + a->z * b->z; }
static inline float dot3(float ax, float ay, float az, float bx, float by, float bz) { return ax * bx + ay * by + az * bz; }
static inline float lerp(float o, float t, float d) { float m = t * d; return o + m; }

void **FUN_002c4870(...);

void igMatrix44fMetaField_SwapBytes(igMatrix44fMetaField *arg0, int arg1, int arg2);

class DW4VC_208_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int, int); };

void FUN_0018be80(int, int, int, int, int);

class igMatrix44fMetaFieldView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32();
    virtual void SetDefault(const void *value);
};

void FUN_0018cc10(void);

void FUN_0018d110(int arg0, struct S18d110 *arg1);
void FUN_0018d160(struct A *arg0, struct B5 *arg1);
void thunk_FUN_0018c820(igPlane *plane, const void *matrix);
int FUN_0018cf20(igPlane *plane, igSphere *sphere);
int FUN_0018c990(void *arg0, void *arg1);
int FUN_0018ca00(struct Plane *a, struct Plane *b);
int FUN_0018ca80(void *arg0, void *arg1);
void FUN_0018d100(void);
void FUN_0018d260(void);
int FUN_0018d270(void);
void FUN_0018d280(void *arg0, void *arg1);
int FUN_0018cb10(struct Plane *a, struct Plane *b);
int FUN_0018cfb0(void *arg0, struct S2 *arg1);
void FUN_0018d0b0(struct V4 *a, float *b);
void FUN_0018d1d0(void *arg0, float *arg1);

struct igVec3f {
    float x;
    float y;
    float z;
    float dot(const float *o) const { return o[0] * x + o[1] * y + o[2] * z; }
};

void FUN_00192f50(float *out, float *v, float *m);
void FUN_00192fc0(float *out, float *v, float *m);

int FUN_00192e50(const float *normal);

void FUN_0018c820(igPlane *plane, const void *matrix);

static inline float lengthOf(const float *v) {
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

typedef struct Plane { char pad[8]; float x, y, z, d; } Plane;

static inline float fabs_(float x) { ((FB *)&x)->sign = 0; return x; }
typedef struct { float x, y, z; } V32;

struct S2 { char p[8]; float a[3]; float b[3]; };

typedef struct P2 { char pad[8]; float a; float b; float c; float d; } P2;

typedef struct V4 { float p0, p4, f8, f12, f16, f20; } V4;

void FUN_00190120(void **arg0, int arg1, int arg2);

struct S18d110 { char pad[8]; float a; char pad2[8]; float b; };

struct A { char p[8]; float f8; float f12; float f16; };
struct B5 { char p[8]; float f8; float f12; float f16; float f20; };

typedef struct { float x, y, z; } V33;
typedef struct { int pad0, pad1; V33 p; V33 d; float len; } S3;

struct igVec3f2 {
    float x;
    float y;
    float z;
    void subtractInto(float *out, const float *o) const { out[0] = x - o[0]; out[1] = y - o[1]; out[2] = z - o[2]; }
};

void FUN_0018d360(igRay *ray, const void *matrix);
Intersection FUN_0018d9b0(igSphere *sphere, void *other);
void FUN_0018dd20(struct S4 *p, struct S4 *q);
void thunk_FUN_0018d630(void);

void FUN_0018da00(void);

int FUN_0018d700(igSphere *sphere, igAABox *box);
int FUN_0018d7b0(igSphere *sphere, igPlane *plane);
int FUN_0018d820(igSphere *a, igSphere *b);

void FUN_0018d8b0(void);

int FUN_0018db20(igSphere *a, igSphere *b);
int FUN_0018dcb0(igSphere *sphere, float *point);

void FUN_0018e040(void);

void FUN_0018e150(void *arg0);
int FUN_0018e160(void *arg0);
void FUN_0018e190(void *arg0, void *arg1);
int FUN_0018dbc0(...);
int FUN_0018de10(...);
void FUN_0018dfc0(void *parg0, struct S5 *arg1);

typedef struct S4 { int pad[2]; float x, y, z, r, ax, ay, az; } S4;

typedef struct S5 { char pad[8]; float x, y, z; float dx, dy, dz; float s; } S5;

void FUN_001900d0(void **arg0, int arg1);
int FUN_0018d630(...);
void igVec2fMetaField_SwapBytes(igVec2fMetaField *arg0, int arg1, int arg2);
int sprintf(...);

void *StringPool_Allocate(int size);
void *StringPool_Construct(void *pool);

int StringPool_Intern(void *pool, const char *text);

extern char DAT_004e0db0[];
extern void *g_stringPool[4];
static inline int internString(const char *text) {
    if (text == 0) {
        return 0;
    }
    if (g_stringPool[0] == 0) {
        void *pool = StringPool_Allocate(16);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    return StringPool_Intern(g_stringPool[0], text);
}

class igVec2fMetaFieldView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32();
    virtual void SetDefault(const void *value);
};

void igVec3fMetaField_SwapBytes(igVec3fMetaField *arg0, int arg1, int arg2);

extern char DAT_004e0db8[];

class igVec3fMetaFieldView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32();
    virtual void SetDefault(const void *value);
};

void igVec4fArrayMetaField_SwapBytes(igVec4fArrayMetaField *arg0, int arg1, int arg2);
void igVec4fMetaField_SwapBytes(igVec4fMetaField *arg0, int arg1, int arg2);

extern char DAT_004e0dc8[];

class igVec4fMetaFieldView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32();
    virtual void SetDefault(const void *value);
};

void **igUnsignedCharMetaField_GetDefaultDescriptor(...);

void igVec4ucMetaField_SwapBytes(igVec4ucMetaField *arg0, int arg1, int arg2);

extern char DAT_004e0de0[];

extern int * DAT_005610f8[4];
extern int * DAT_00561100[4];

int FUN_0018e7d0(...);

static inline void addScaled(float *out, float weight, const float *v) {
    float x = weight * v[0];
    float y = weight * v[1];
    float z = weight * v[2];
    out[0] += x;
    out[1] += y;
    out[2] += z;
}

extern int * DAT_00561108[4];
extern int * DAT_00561110[4];

int FUN_0018ea90(...);

typedef int (*UnaryOp)(void **, int);
typedef int (*BinaryOp)(void **, void **);
struct OpTable { int vtable; int references; int count; int capacity; int *data; };
struct IndexedWordKey { char pad[8]; int idx; };
struct IndexedWordPairKey { char pad[8]; unsigned int idx; };
typedef struct PairKeyedItem { int pad0[2]; unsigned int key; } PairKeyedItem;
struct IndexedSlotKey { char pad[8]; int idx; };
struct InstanceNode : public igObject { };
unsigned FUN_002fe2c0(int);
int FUN_002fe2e0(int, unsigned);
int FUN_00301ee0(InstanceNode *, unsigned);
int FUN_00100610(void *);
extern int DAT_00587038[4];
extern OpTable *DAT_00561118;
extern OpTable *DAT_00561120;
extern OpTable *DAT_00561128;
extern OpTable *DAT_00561130;
extern OpTable *DAT_00561138;
extern OpTable *DAT_00561140;
extern OpTable *DAT_00561148;
extern OpTable *DAT_00561150;
extern OpTable *DAT_00561158;
extern OpTable *DAT_00561160;
extern OpTable *DAT_00561168;
extern OpTable *DAT_00561170;
igSmartPointer<InstanceNode> FUN_002fd6e0(int, int);
struct NodeList : InstanceNode { int count; int capacity; InstanceNode **data; };
struct InstanceListRef {
    NodeList *p;
    InstanceListRef(NodeList *list) : p(list) {}
    InstanceListRef(const InstanceListRef &other) : p(other.p) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
    ~InstanceListRef() {
        InstanceNode *node = p;
        if (node != 0) {
            node->_refCount = node->_refCount - 1;
            if ((node->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(node);
            }
        }
    }
};
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *vX(); };
static inline void setEntry(OpTable *g, int idx, int v) {
    if (g->count != 0 && idx >= 0 && idx < g->count) {
        g->data[idx] = v;
    }
}
static inline void setAt(OpTable *t, int i, int v) {
    if (t->count != 0 && i >= 0 && i < t->count) { t->data[i] = v; }
}
// igTDataList<int>::set(index, const int &): the value reference makes the slot's value
// materialise before the bounds checks.
static inline void setSlot(OpTable *t, int i, const int &v) {
    if (t->count != 0 && i >= 0 && i < t->count) {
        t->data[i] = v;
    }
}
void FUN_002d6790(OpTable *, int, int);
static inline void setCount(OpTable *t, int n) {
    if (n >= 0) {
        if (n <= t->capacity) {
            t->count = n;
        } else {
            FUN_002d6790(t, n, 4);
        }
    }
}
static inline void setElement(const InstanceListRef &list, int index, const igSmartPointer<InstanceNode> &element) {
    InstanceNode *value = element.p;
    NodeList *l = list.p;
    InstanceNode *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = l->data[index];
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    if (l->count != 0 && index >= 0 && index < l->count) {
        l->data[index] = value;
    }
}
#define REL(g) { OpTable *o=g; if(o){ --o->references; if(((unsigned long long)(long long)o->references & 0x7fffffULL)==0) igObject_Destroy(o);} }
int FUN_002fe290(int, int);

int FUN_0018f3e0(void);
void FUN_0018f3f0(void);
int FUN_0018f400(void);
void FUN_0018f410(void);
int FUN_0018f420(void);
void FUN_0018f430(void);
void FUN_0018f440(void);
int FUN_0018f450(void);
void FUN_0018f460(void);
int FUN_0018f470(void);
void FUN_0018f480(void);
int FUN_0018f490(void);

int Matrix44_Copy(float *, float *);

class ScaleVec { public: float _v[3]; float operator[](int i) const { return _v[i]; } };

void FUN_00190f50(float *arg0, float *arg1, float fparg0);

extern float g_vec3Zero[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
extern float DAT_004e11c0[4];
extern float DAT_004e11c4[4];
extern float DAT_004e11c8[4];
extern float DAT_004e11cc[4];

void FUN_001910c0(float *m, float x, float y, float z);

typedef union U5 { float f; struct { unsigned char p0, p1, p2; unsigned char lo : 7; unsigned char sign : 1; } b; } U5;
float cosf(float);
float sinf(float);

int FUN_001906d0(...);
int FUN_001904f0(...);
void Matrix44_SetQuaternion(float *m, float *q);

float atanf(float);
float tanf(float);

extern int g_statusSucceeded[4];

typedef union U6 { float f; struct { unsigned char p0, p1, p2; unsigned char lo : 7; unsigned char sign : 1; } b; } U6;
extern int g_allocatorFailureStatus[4];
int FUN_00192030(int, int, float *);

float FUN_00192290(float *m);

typedef struct S6 { float f0; char p4[28]; float f32; float f36; float f40; char p44[12]; float f56; } S6;

float asinf(float);
float atan2f(float, float);

struct CurvePoint4 { int a, b, c, d; };

extern float g_vec4Zero[4];
extern float D_004e1170[4];
extern float D_004e1180[4];
extern float DAT_004e1174[4];
extern float DAT_004e1178[4];
extern float DAT_004e117c[4];
extern float DAT_004e1180[4];
extern float DAT_004e1184[4];
extern float DAT_004e1188[4];
extern float DAT_004e118c[4];

typedef struct Color4f { float x, y, z, w; } Color4f;
#define BYTE_TO_UNIT(packed, mask, shift) ((float)(((packed) & (mask)) >> (shift)) / 255.0f)

extern int g_igVec4fMetaField_descriptor[4];


extern int g_igVec3fMetaField_descriptor[4];

extern int g_igVec2fMetaField_descriptor[4];

extern int g_igMatrix44fMetaField_descriptor[4];

int List_Reserve(...);


#endif
