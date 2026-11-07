class SwapDescriptor { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
 virtual void Swap(void *, int);
};
struct FieldMetaView { char pad[25]; unsigned char _persistent; };
class FieldObjectView { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13();
 virtual void Finish();
 virtual void e15(); virtual void e16(); virtual void e17(); virtual void e18(); virtual void e19();
 virtual FieldMetaView *Meta();
};
class FieldEntryView { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
 virtual void Prepare(FieldObjectView *);
 char pad[48]; unsigned char _skipReset;
};
struct FieldOffsetList { char pad[8]; int count; int cap; short *data; };
struct FieldListTable { char pad[16]; FieldOffsetList **data; };
struct FieldDirView { char pad[60]; FieldListTable *lists; };
struct FieldRecordHead { int kind; int size; };
extern "C" {
SwapDescriptor *igIntMetaField_GetDefaultDescriptor();
int igMetaObject_GetFieldCount(void *);
FieldEntryView *igMetaObject_GetFieldAt(void *, int);
int igObject_IsKindOf(void *, int);
void igMetaField_Reset(FieldEntryView *, FieldObjectView *);
int FUN_002fc780(FieldEntryView *, FieldObjectView *, char *, FieldDirView *, int);
extern int DAT_00585a60;
extern void *DAT_00587198;
}
extern "C" int FUN_00300250(FieldObjectView *object, FieldRecordHead *head, FieldDirView *dir, int unused, int swap) {
    FieldMetaView *meta;
    FieldListTable *lists;
    FieldOffsetList *offsets;
    char *data;
    int i;
    int first;
    int count;
    int done;
    int next;
    short limit;
    FieldEntryView *field;
    int size;
    meta = object->Meta();
    if (meta->_persistent == 0) {
        return 0;
    }
    lists = dir->lists;
    if (swap != 0) {
        igIntMetaField_GetDefaultDescriptor()->Swap(head, 2);
    }
    offsets = lists->data[head->kind];
    data = (char *)head + 8;
    first = igMetaObject_GetFieldCount(DAT_00587198);
    count = igMetaObject_GetFieldCount(meta);
    done = 0;
    next = 0;
    if (offsets->count == 0) {
        limit = count;
    } else {
        limit = offsets->data[next++];
    }
    for (i = first; i < count; i++) {
        field = igMetaObject_GetFieldAt(meta, i);
        if (i < limit) {
            field->Prepare(object);
            if (igObject_IsKindOf(field, DAT_00585a60) == 0 || field->_skipReset == 0) {
                igMetaField_Reset(field, object);
            }
        } else {
            done++;
            data += FUN_002fc780(field, object, data, dir, swap);
            if (done == offsets->count) {
                limit = count;
            } else {
                limit = offsets->data[next++];
            }
        }
    }
    size = head->size;
    if (swap != 0) {
        igIntMetaField_GetDefaultDescriptor()->Swap(head, 2);
    }
    object->Finish();
    return size;
}
