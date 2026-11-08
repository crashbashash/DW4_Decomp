typedef struct {
    unsigned int base0;
    unsigned int size0;
    unsigned int base1;
    unsigned int size1;
} Map2a40b8;

int FUN_002a40b8(Map2a40b8 *map, unsigned int addr) {
    int offset;

    if (addr >= map->base0 && addr < map->base0 + map->size0) {
        offset = addr - map->base0;
    } else if (addr >= map->base1 && addr < map->base1 + map->size1) {
        offset = addr - map->base1 + map->size0;
    } else {
        offset = 0;
    }
    return offset;
}
