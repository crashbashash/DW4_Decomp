void *Gap__Sg__igAnimationDatabase__vfunc_24(O_1aea60 *arg0, char *arg1) {
    int sp106C;
    char sp50[4096];
    char *var_a1;
    R_1aea60 *var_s0;
    R_1aea60 *var_s1;

    var_a1 = arg0->f8;
    if (var_a1 != 0) {
        var_a1 = (char *)var_a1;
    } else {
        var_a1 = ((char *)emptyString);
    }
    if (strcmp(arg1, var_a1) == 0) {
        return arg0;
    }
    var_s0 = ((R_1aea60 *)igProperty_FindByName(arg0->f20, g_propertyNameField[0], arg1));
    if (var_s0 == 0) {
        var_s0 = ((R_1aea60 *)igProperty_FindByName(arg0->f28, g_propertyNameField[0], arg1));
    }
    if (var_s0 == 0) {
        var_s0 = ((R_1aea60 *)igProperty_FindByName(arg0->f24, g_propertyNameField[0], arg1));
    }
    if (var_s0 == 0) {
        var_s0 = ((R_1aea60 *)igProperty_FindByName(arg0->f32, g_propertyNameField[0], arg1));
    }
    if (var_s0 == 0) {
        var_s0 = ((R_1aea60 *)igProperty_FindByName(arg0->f36, g_propertyNameField[0], arg1));
    }
    if (strncmp(arg1, DAT_004e44f8, strlen(DAT_004e44f8)) == 0) {
        if (DAT_00562560[0] == 0) {
            var_s1 = ((R_1aea60 *)igMetaObject_FindFieldByName(g_igAnimation_metaObject[0], text_trackList));
            if ((var_s1 != 0) && (igObject_IsKindOf(var_s1, g_igObjectRefMetaField_metaObject[0]) != 0)) {
                var_s1 = (R_1aea60 *)var_s1;
            } else {
                var_s1 = 0;
            }
            DAT_00562560[0] = (int *)var_s1;
        }
        sscanf(arg1 + strlen(DAT_004e44f8), DAT_004e4500, sp50, &sp106C);
        igSmartPointer<R_1aea60> record(((R_1aea60 *)igProperty_FindByName(arg0->f24, g_propertyNameField[0], sp50)), kRetainReference);
        if (record.get() != 0) {
            var_s1 = *(R_1aea60 **)((char *)record.get() + DAT_00562560[0][2]);
            if ((var_s1 != 0) && (igObject_IsKindOf(var_s1, g_igAnimationTrackList_metaObject[0]) != 0)) {
                var_s1 = (R_1aea60 *)var_s1;
            } else {
                var_s1 = 0;
            }
            igSmartPointer<R_1aea60> list(var_s1, kRetainReference);
            if (list.get() != 0) {
                igSmartPointer<R_1aea60> entry((R_1aea60 *)list.get()->f16[sp106C], kRetainReference);
                if (entry.get() != 0) {
                    var_s0 = (R_1aea60 *)entry.get()->f12;
                }
            }
        }
    }
    igSmartPointer<R_1aea60> keep = igSmartPointer<R_1aea60>(var_s0, kRetainReference);
    return var_s0;
}

int FUN_001aedd0(void *self, igTDataList<AnimDbRecord *> *list, int file, AnimDbRecord *object) {
    RecordRef held(object);
    AnimDbRecord *current = held.p;
    if (list->find(current) != -1) {
        RecordRef named(castToNamed(current));
        if (named.p != 0) {
            return (unsigned char)FUN_002e2d30(file, self, nameOf(named.p), object);
        }
    }
    return 0;
}

#define CAST_INLINE(NAME, META) static inline AnimDbObject *NAME(AnimDbObject *o) { if (o != 0 && igObject_IsKindOf(o, META) != 0) { return o; } return 0; }
int Gap__Sg__igAnimationDatabase__vfunc_23(AnimDbRec *db, int file, AnimDbObject *obj) {
    char name[4096];
    int r;
    if ((void *)obj == (void *)db) {
        return FUN_002e2d30(file, db, nameOf(db->_name), obj);
    }
    if ((unsigned char)FUN_001aedd0(db, (igTDataList<AnimDbRecord *> *)db->_animationList, file, (AnimDbRecord *)obj) == 1) {
        return 1;
    }
    if ((unsigned char)FUN_001aedd0(db, (igTDataList<AnimDbRecord *> *)db->_skeletonList, file, (AnimDbRecord *)obj) == 1) {
        return 1;
    }
    if ((unsigned char)FUN_001aedd0(db, (igTDataList<AnimDbRecord *> *)db->_skinList, file, (AnimDbRecord *)obj) == 1) {
        return 1;
    }
    if ((unsigned char)FUN_001aedd0(db, (igTDataList<AnimDbRecord *> *)db->_appearanceList, file, (AnimDbRecord *)obj) == 1) {
        return 1;
    }
    if ((unsigned char)FUN_001aedd0(db, (igTDataList<AnimDbRecord *> *)db->_combinerList, file, (AnimDbRecord *)obj) == 1) {
        return 1;
    }
    igSmartPointer<AnimDbObject> held(obj, kRetainReference);
    igSmartPointer<AnimDbObject> skel(castSkeleton(held.p), kRetainReference);
    if (skel.p != 0 && igDirectory_FindSortedInsertIndex(db->_directory, DAT_00586730, obj) < db->_directory->_count) {
        int i;
        int n;
        if (DAT_00562568 == 0) {
            DAT_00562568 = (AnimDbField *)castField((AnimDbObject *)((void *)igMetaObject_FindFieldByName(((igMetaObject *)g_igAnimation_metaObject[0]), text_trackList)));
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
                    sprintf(name, text_s_s_d, DAT_004e44f8, nameOf(skin.p->_name), a);
                    r = (unsigned char)FUN_002e2d30(file, db, name, obj);
                    return r;
                }
            }
        }
    }
    return 0;
}
