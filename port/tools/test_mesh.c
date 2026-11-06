#include "dw4/mesh.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Two strips: the first has an odd length, so the second starts on an odd vertex. */
static const uint8_t lengths[] = {3, 0, 0, 0, 4, 0, 0, 0};

static void check(int (*tris)(uint32_t, uint32_t, uint32_t, const uint8_t *, uint32_t, uint32_t **,
                              uint32_t *, const char **),
                  const uint32_t *expected)
{
    uint32_t *t = NULL, n = 0;
    const char *why = NULL;

    assert(!tris(4, 2, 7, lengths, 2, &t, &n, &why));
    assert(n == 3 && !memcmp(t, expected, 9 * sizeof *t));
    free(t);
}

int main(void)
{
    static const uint32_t per_strip[] = {0, 1, 2, 3, 4, 5, 5, 4, 6};
    static const uint32_t whole_geometry[] = {0, 1, 2, 4, 3, 5, 4, 5, 6};

    check(dw4_mesh_tris, per_strip);
    check(dw4_mesh_collision_tris, whole_geometry);
    return 0;
}
