/* Reports DAT_004ee178 for a null object; otherwise, between FUN_0025f2d0 and FUN_0025f2e8, calls
 * FUN_0026b978 with the object and its field 16, invokes slot 5 of the attached interface at
 * offset 20, sets the state byte to 4 and passes the 2048-byte sector count at offset 62 to
 * FUN_00277658 for the handle at offset 148, then FUN_00277210 and FUN_0026d158(object, 1). */
typedef struct Interface_2638a0 Interface_2638a0;
typedef struct InterfaceTable_2638a0 {
    void (*slot[6])(Interface_2638a0 *self);
} InterfaceTable_2638a0;
struct Interface_2638a0 {
    InterfaceTable_2638a0 *table;
};

typedef struct Object_2638a0 {
    char f0;
    char f1;
    char state;                  /* 0x02 */
    char pad3[13];
    int f16;                     /* 0x10 */
    Interface_2638a0 *source;    /* 0x14 */
    char pad24[38];
    short sectors;               /* 0x3e */
    char pad64[84];
    void *handle;                /* 0x94 */
} Object_2638a0;

extern char DAT_004ee178[];
void FUN_002607e8(const char *message);
void FUN_0026bbc0(void);
void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void FUN_0026b978(Object_2638a0 *object, int value);
void FUN_00277658(void *handle, int bytes);
void FUN_00277210(void *handle);
void FUN_0026d158(Object_2638a0 *object, int value);

void FUN_002638a0(Object_2638a0 *object) {
    void *handle = object->handle;
    Interface_2638a0 *source;

    if (object == 0) {
        FUN_002607e8(DAT_004ee178);
        return;
    }
    FUN_0026bbc0();
    FUN_0025f2d0();
    FUN_0026b978(object, object->f16);
    source = object->source;
    source->table->slot[5](source);
    object->state = 4;
    FUN_00277658(handle, object->sectors << 11);
    FUN_0025f2e8();
    FUN_00277210(handle);
    FUN_0026d158(object, 1);
}
