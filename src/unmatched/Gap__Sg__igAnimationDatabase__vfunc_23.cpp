#include "dw4/igSmartPointer.h"
struct AnimDbObject : public igObject { int _name; int _source; int _f16; int _f20; };
struct AnimDbList { char pad[8]; int _count; int _capacity; AnimDbObject **_data; };
struct AnimDbDirectory { char pad[8]; int _count; };
struct AnimDbField { char pad[8]; int _offset; };
struct AnimDbRec { char pad[8]; int _name; AnimDbDirectory *_directory; char pad16[4]; AnimDbList *_skeletonList; AnimDbList *_animationList; AnimDbList *_skinList; AnimDbList *_appearanceList; AnimDbList *_combinerList; };
extern char DAT_004e0858[];
extern char DAT_004e4130[];
extern char DAT_004e4508[];
extern char DAT_004e44f8[];
extern igMetaObject *DAT_005611d0;
extern igMetaObject *DAT_00585b20;
extern igMetaObject *DAT_00562428;
extern igMetaObject *DAT_00562370;
extern int DAT_00586730;
extern AnimDbField *DAT_00562568;
extern "C" {
int igObject_IsKindOf(void *, igMetaObject *);
int FUN_002e2d30(int, void *, const char *, void *);
int FUN_002d86b0(AnimDbDirectory *, int, AnimDbObject *);
int FUN_001aedd0(void *self, AnimDbList *list, int file, AnimDbObject *obj);
void *igMetaObject_FindFieldByName(igMetaObject *, const char *);
int sprintf(char *, const char *, ...);
int Gap__Sg__igAnimationDatabase__vfunc_23(AnimDbRec *db, int file, AnimDbObject *obj);
}

#define CAST_INLINE(NAME, META) static inline AnimDbObject *NAME(AnimDbObject *o) { if (o != 0 && igObject_IsKindOf(o, META) != 0) { return o; } return 0; }
CAST_INLINE(castSkeleton, DAT_005611d0)
CAST_INLINE(castField, DAT_00585b20)
CAST_INLINE(castBoolList, DAT_00562428)
static inline const char *nameOf(int name) {
    const char *n = (const char *)name;
    if (n != 0) {
        return n;
    }
    return DAT_004e0858;
}
int Gap__Sg__igAnimationDatabase__vfunc_23(AnimDbRec *db, int file, AnimDbObject *obj) {
    char name[4096];
    int r;
    if ((void *)obj == (void *)db) {
        return FUN_002e2d30(file, db, nameOf(db->_name), obj);
    }
    if ((unsigned char)FUN_001aedd0(db, db->_animationList, file, obj) == 1) {
        return 1;
    }
    if ((unsigned char)FUN_001aedd0(db, db->_skeletonList, file, obj) == 1) {
        return 1;
    }
    if ((unsigned char)FUN_001aedd0(db, db->_skinList, file, obj) == 1) {
        return 1;
    }
    if ((unsigned char)FUN_001aedd0(db, db->_appearanceList, file, obj) == 1) {
        return 1;
    }
    if ((unsigned char)FUN_001aedd0(db, db->_combinerList, file, obj) == 1) {
        return 1;
    }
    igSmartPointer<AnimDbObject> held(obj, kRetainReference);
    igSmartPointer<AnimDbObject> skel(castSkeleton(held.p), kRetainReference);
    if (skel.p != 0 && FUN_002d86b0(db->_directory, DAT_00586730, obj) < db->_directory->_count) {
        int i;
        int n;
        if (DAT_00562568 == 0) {
            DAT_00562568 = (AnimDbField *)castField((AnimDbObject *)igMetaObject_FindFieldByName(DAT_00562370, DAT_004e4130));
        }
        n = db->_animationList->_count;
        for (i = 0; i < n; i++) {
            int a;
            int total;
            AnimDbList *list;
            AnimDbObject *target;
            igSmartPointer<AnimDbObject> skin(db->_animationList->_data[i], kRetainReference);
            igSmartPointer<AnimDbObject> app(castBoolList(*(AnimDbObject **)((char *)skin.p + DAT_00562568->_offset)), kRetainReference);
            list = (AnimDbList *)app.get();
            target = skel.get();
            total = list->_count;
            for (a = 0; a < total; a++) {
                if ((AnimDbObject *)list->_data[a]->_source == target) {
                    sprintf(name, DAT_004e4508, DAT_004e44f8, nameOf(skin.p->_name), a);
                    r = (unsigned char)FUN_002e2d30(file, db, name, obj);
                    return r;
                }
            }
        }
    }
    return 0;
}
