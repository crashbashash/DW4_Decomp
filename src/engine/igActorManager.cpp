#include "dw4/reflected.h"

extern "C" {

class W { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int, int, int, int, float, float); };
struct R { int w0; int rc; };
R *FUN_00236f80(...);
int igObject_Destroy(...);
extern int g_igViewerSceneInfoManager_metaObject[4];
void Gap__Viewer__igActorManager__vfunc_25(igActorManager *arg0);

int FUN_00236be0(...);

void FUN_00236c40(int, int);

typedef struct L { char pad[8]; int n; int p; int *arr; } L;
typedef struct A { char pad[24]; L *f24; } A;
int igObject_IsKindOf(A *, int);
struct ActorListOwner;
void FUN_00467030(struct ActorListOwner *arg0, int arg1);
int igActorInfo_GetMetaObject(void);
#define F24 (*(L **)&arg1->f24)

int ObjectList_AppendRetained(...);

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

extern int g_igActorManager_metaObject[4];

void Gap__Viewer__igActorManager__vfunc_25(igActorManager *arg0) {
    R *temp_v0;
    R *temp_a0;

    temp_v0 = FUN_00236f80(arg0->_insight, g_igViewerSceneInfoManager_metaObject[0]);
    if (temp_v0 != 0) {
        temp_v0->rc = temp_v0->rc + 1;
    }
    temp_a0 = (R *)arg0->_vsim;
    if (temp_a0 != 0) {
        temp_a0->rc = temp_a0->rc - 1;
        if ((temp_a0->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_vsim = (int)temp_v0;
    ((W *)arg0->_viewport)->vX(0, 0, 0, 0, 0.0f, 1.0f);
    ((W *)arg0->_skelViewport)->vX(0, 0, 0, 0, 0.0f, 0.2f);
}

void Gap__Viewer__igActorManager__vfunc_26(void) {

}

void Gap__Viewer__igActorManager__vfunc_23(int arg0) {
    FUN_00236be0(*(int *)(arg0 + 12), arg0);
}

void Gap__Viewer__igActorManager__vfunc_24(int arg0) {
    FUN_00236c40(*(int *)((char *)(arg0) + 12), arg0);
}

/* The list pointer is re-read in the body and in the loop test, with a `0 < n` guard. */
int Gap__Viewer__igActorManager__vfunc_27(int arg0, A *arg1) {
    int i;
    int off;
    if (igObject_IsKindOf(arg1, igActorInfo_GetMetaObject()) != 0) {
        i = 0;
        if (0 < arg1->f24->n) {
            off = 0;
            do {
                FUN_00467030((ActorListOwner *)arg0, *(int *)((char *)F24->arr + off));
                i++;
                off += 4;
            } while (i < F24->n);
        }
        return 1;
    }
    return 0;
}

void FUN_00467030(struct ActorListOwner *arg0, int arg1) {
    struct ActorList *list = arg0->f24;
    /* matching construct: retail keeps the value in a stack slot */
    int value = arg1;
    if (indexOf(list, (const int *)&value) < 0) {
        ObjectList_AppendRetained(arg0->f24, arg1);
    }
}

void Gap__Viewer__igActorManager__vfunc_29(void) {

}

int Gap__Viewer__igActorManager__vfunc_22(void) {
    return g_igActorManager_metaObject[0];
}

}
