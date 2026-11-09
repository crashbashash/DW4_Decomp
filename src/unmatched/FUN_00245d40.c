typedef struct HashNode {
    unsigned int key;
    struct HashNode *next;
    struct HashNode *prev;
} HashNode;

void FUN_002450c0(void);
extern unsigned int DAT_004986b0;
extern unsigned int DAT_004986b8;
extern unsigned int DAT_0056deb8;
extern HashNode **DAT_0056dec0;

void FUN_00245d40(HashNode *node) {
    HashNode **bucket;

    if (node->next != 0) {
        node->next->prev = node->prev;
    }
    if (node->prev != 0) {
        node->prev->next = node->next;
    } else {
        bucket = &DAT_0056dec0[(DAT_004986b8 - 1) & (node->key ^ (node->key >> DAT_004986b0))];
        if (*bucket == node) {
            *bucket = node->next;
        } else {
            return;
        }
    }
    DAT_0056deb8--;
    FUN_002450c0();
}
