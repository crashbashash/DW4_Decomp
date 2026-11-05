/* 0x002653c8 — FUN_002653c8 (96 bytes). Copies a 4-word record into a 6-word stack record (fourth word = third + 1, sixth = 25) and hands it, or 0 when there is no source, to FUN_00264910. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Rec_2653c8 {
    int a;
    int b;
    int c;
    int d;
} Rec_2653c8;

typedef struct Desc_2653c8 {
    int a;      /* 0x00: src->a */
    int b;      /* 0x04: src->b */
    int first;  /* 0x08: src->c */
    int next;   /* 0x0c: first + 1 */
    int d;      /* 0x10: src->d */
    int kind;   /* 0x14: always 25 */
} Desc_2653c8;

int FUN_00264910(Desc_2653c8 *desc);

void FUN_002653c8(Rec_2653c8 *src) {
    Desc_2653c8 desc;
    Desc_2653c8 *p;

    if (src != 0) {
        /* matching construct: permuter — the copy of src->d is written first */
        desc.d = src->d;
        desc.a = src->a;
        desc.b = src->b;
        desc.first = src->c;
        desc.next = desc.first + 1;
        desc.kind = 25;
        p = &desc;
    } else {
        p = 0;
    }
    FUN_00264910(p);
}
