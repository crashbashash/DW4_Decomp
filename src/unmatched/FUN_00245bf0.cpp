struct HashedObject;

struct HashLink {
    unsigned int key;
    HashedObject *next;
    HashedObject *prev;
};

struct HashedHeader {
    int words[3];
};

struct HashedObject : HashedHeader, HashLink {
};

extern "C" {
void FUN_00245520(void);
extern unsigned int DAT_004986d0;
extern unsigned int DAT_004986d8;
extern unsigned int DAT_0056dee8;
extern HashedObject **DAT_0056def0;
/* matching construct: 9 spellings, the key in a local */
void FUN_00245bf0(HashLink *link);
}

void FUN_00245bf0(HashLink *link) {
    HashedObject **bucket;
    HashedObject *object;
    unsigned int index;
    unsigned int key;

    if (link->next != 0) {
        link->next->prev = link->prev;
    }
    if (link->prev != 0) {
        link->prev->next = link->next;
    } else {
        key = link->key;
        index = (DAT_004986d8 - 1) & (key ^ (key >> DAT_004986d0));
        object = static_cast<HashedObject *>(link);
        bucket = &DAT_0056def0[index];
        if (*bucket == object) {
            *bucket = link->next;
        } else {
            return;
        }
    }
    DAT_0056dee8--;
    FUN_00245520();
}
