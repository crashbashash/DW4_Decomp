void igMatrix44f_SetIdentity(void *);
void Matrix44_Copy(void *, void *);
float FUN_00192290(void *);
void FUN_00190cb0(void *, void *);
void FUN_001925f0(void *, void *);
void FUN_00192990(void *, float *, float *, float *);
float sqrtf(float);
typedef struct KeyVec3View { float x, y, z; } KeyVec3View;
typedef struct KeyVec3ListView { int _vtable; unsigned int _refCount; int _count; int _capacity; KeyVec3View *_data; } KeyVec3ListView;
typedef struct KeyQuatView { float x, y, z, w; } KeyQuatView;
typedef struct KeyQuatListView { int _vtable; unsigned int _refCount; int _count; int _capacity; KeyQuatView *_data; } KeyQuatListView;
typedef struct KeySequenceView { int _vtable; unsigned int _refCount; KeyVec3ListView *_xlateList; KeyQuatListView *_quatList; KeyVec3ListView *_scaleList; char pad[52]; unsigned char _drivenChannels; } KeySequenceView;
typedef struct KeyMatrixView { float r[3][4]; float tx, ty, tz, tw; } KeyMatrixView;
void Gap__Sg__igTransformSequence1_5__vfunc_34(KeySequenceView *o, int index, KeyMatrixView *m) {
    int off;
    int i;
    KeyQuatView *q;
    float *s;
    float *pz;
    float *py;
    float z;
    float y;
    float x;
    float euler[3];
    float inv[3];
    float rot[16];
    if (o->_drivenChannels & 1) {
        KeyVec3View *t = &o->_xlateList->_data[index];
        t->x = m->tx;
        t->y = m->ty;
        t->z = m->tz;
    }
    igMatrix44f_SetIdentity(rot);
    if (o->_drivenChannels & 8) {
        s = (float *)&o->_scaleList->_data[index];
        for (i = 0; i < 3; i++) {
            float *r = m->r[i];
            s[i] = sqrtf(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
        }
        Matrix44_Copy(rot, m);
        if (FUN_00192290(m) < 0.0f) {
            s[0] = -s[0];
            s[1] = -s[1];
            s[2] = -s[2];
        }
        {
                        z = 1.0f / s[2];
            x = 1.0f / s[0];
            y = 1.0f / s[1];
            inv[0] = x;
            inv[2] = z;
            inv[1] = y;
        }
        FUN_00190cb0(rot, inv);
    } else {
        Matrix44_Copy(rot, m);
    }
    if (o->_drivenChannels & 2) {
        FUN_001925f0(&o->_quatList->_data[index], rot);
    } else if (o->_drivenChannels & 4) {
        off = index * 16;
        FUN_001925f0((char *)o->_quatList->_data + off, rot);
        pz = &euler[2];
        py = &euler[1];
        FUN_00192990((char *)o->_quatList->_data + off, euler, py, pz);
        euler[0] = euler[0] * 57.29578f;
        *py = *py * 57.29578f;
        *pz = *pz * 57.29578f;
        q = (KeyQuatView *)((char *)o->_quatList->_data + off);
        {
            float a;
            float b;
            float c;
            c = *pz;
            b = *py;
            a = euler[0];
            q->x = a;
            q->y = b;
            q->z = c;
        }
        q->w = 0.0f;
    }
}
