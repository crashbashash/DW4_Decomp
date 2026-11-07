void Matrix44_Copy(void *, void *);
float FUN_00192290(void *);
void FUN_00190cb0(void *, void *);
void FUN_001925f0(void *, void *);
float sqrtf(float);
typedef struct TransformSampleVec3ListView { int _vtable; unsigned int _refCount; int _count; int _capacity; float (*_data)[3]; } TransformSampleVec3ListView;
typedef struct TransformSampleQuatListView { int _vtable; unsigned int _refCount; int _count; int _capacity; float (*_data)[4]; } TransformSampleQuatListView;
typedef struct TransformSampleView { int _vtable; unsigned int _refCount; TransformSampleVec3ListView *_xlateList; TransformSampleQuatListView *_quatList; TransformSampleVec3ListView *_scaleList; } TransformSampleView;
void FUN_001dd0e0(TransformSampleView *o, int index, float (*m)[4]) {
    float rot[4][4];
    float inv[3];
    float *t;
    float *s;
    int i;
    t = o->_xlateList->_data[index];
    t[0] = m[3][0];
    t[1] = m[3][1];
    t[2] = m[3][2];
    s = o->_scaleList->_data[index];
    for (i = 0; i < 3; i++) {
        float *r = m[i];
        s[i] = sqrtf(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
    }
    Matrix44_Copy(rot, m);
    if (FUN_00192290(m) < 0.0f) {
        s[0] = -s[0];
        s[1] = -s[1];
        s[2] = -s[2];
    }
    {
        float z;
        float y;
        float x;
        z = 1.0f / s[2];
        x = 1.0f / s[0];
        y = 1.0f / s[1];
        inv[0] = x;
        inv[2] = z;
        inv[1] = y;
    }
    FUN_00190cb0(rot, inv);
    FUN_001925f0(o->_quatList->_data[index], rot);
}
