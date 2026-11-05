/* dw4/mesh.c — see include/dw4/mesh.h.  Shared by the file reader and the scene loader. */
#include "dw4/mesh.h"

#include <stdlib.h>
#include <string.h>

#define MAX_LENGTHS (1u << 20)

static uint32_t rd32(const uint8_t *p)
{
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}

static float rdf(const uint8_t *p)
{
    float f;
    memcpy(&f, p, 4);
    return f;
}

int dw4_mesh_tris(uint32_t prim_type, uint32_t num_prims, uint32_t num_verts,
                  const uint8_t *lengths, uint32_t num_lengths,
                  uint32_t **out, uint32_t *ntris, const char **why)
{
    uint32_t i, k, n = 0, base = 0, *t;

    *out = NULL;
    *ntris = 0;
    if (prim_type == 3) {
        if (num_verts < 3 * num_prims) {
            *why = "list: _numVerts < 3*_numPrims";
            return -1;
        }
        n = num_prims;
        t = n ? (uint32_t *)malloc(3u * n * sizeof(uint32_t)) : NULL;
        if (n && !t)
            return -1;
        for (i = 0; i < n; i++) {
            t[3 * i] = 3 * i;
            t[3 * i + 1] = 3 * i + 1;
            t[3 * i + 2] = 3 * i + 2;
        }
    } else {
        uint32_t cnt = 0, sum = 0;
        if (!lengths || !num_lengths || num_lengths > MAX_LENGTHS) {
            *why = "strip: no primitive lengths";
            return -1;
        }
        for (i = 0; i < num_lengths; i++) {
            uint32_t L = rd32(lengths + 4 * i);
            if (L < 3) {
                *why = "strip: degenerate primitive length";
                return -1;
            }
            cnt += L - 2;
            sum += L;
        }
        if (sum != num_verts) {
            *why = "strip: the lengths do not sum to _numVerts";
            return -1;
        }
        t = cnt ? (uint32_t *)malloc(3u * cnt * sizeof(uint32_t)) : NULL;
        if (cnt && !t)
            return -1;
        for (i = 0; i < num_lengths; i++) {
            uint32_t L = rd32(lengths + 4 * i);
            for (k = 0; k + 2 < L; k++) {
                /* A strip alternates winding -- triangle k is (k, k+1, k+2) for even k and
                 * (k+1, k, k+2) for odd k -- so every triangle keeps the same facing.  The old
                 * form emitted (k, k+1, k+2) for both, so half of every strip was wound the
                 * other way; that was invisible while nothing culled, and it is what makes
                 * back-face culling (the game's VU1 CULLBACK) possible now (finding #575). */
                if ((k & 1) == 0) {
                    t[3 * n] = base + k;
                    t[3 * n + 1] = base + k + 1;
                    t[3 * n + 2] = base + k + 2;
                } else {
                    t[3 * n] = base + k + 1;
                    t[3 * n + 1] = base + k;
                    t[3 * n + 2] = base + k + 2;
                }
                n++;
            }
            base += L;               /* a strip's next primitive starts at the next vertex */
        }
    }
    *out = t;
    *ntris = n;
    return 0;
}

void dw4_mesh_obj_basename(const char *name, uint32_t id, char *out, size_t cap)
{
    size_t n = 0, k;

    n += (size_t)snprintf(out + n, cap - n, "model_");
    if (name && name[0]) {
        for (k = 0; name[k] && n + 1 < cap; k++) {
            char c = name[k];
            int ok = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
                     (c >= '0' && c <= '9') || c == '.' || c == '_' || c == '-';
            out[n++] = ok ? c : '_';
        }
    } else {
        n += (size_t)snprintf(out + n, cap - n, "%u", id);
    }
    snprintf(out + n, cap - n, ".obj");
}

int dw4_mesh_write_obj(FILE *f, const uint8_t *pos, const uint8_t *uv, uint32_t num_verts,
                       const uint32_t *tris, uint32_t ntris)
{
    uint32_t i;

    if (!pos)
        return -1;
    fprintf(f, "# DW4 model, extracted offline from the model pack\n");
    for (i = 0; i < num_verts; i++)
        fprintf(f, "v %.6f %.6f %.6f\n", (double)rdf(pos + 12 * i),
                (double)rdf(pos + 12 * i + 4), (double)rdf(pos + 12 * i + 8));
    if (uv)
        for (i = 0; i < num_verts; i++)
            fprintf(f, "vt %.6f %.6f\n", (double)rdf(uv + 8 * i),
                    (double)rdf(uv + 8 * i + 4));
    for (i = 0; i < ntris; i++) {
        uint32_t a = tris[3 * i] + 1, b = tris[3 * i + 1] + 1, c = tris[3 * i + 2] + 1;
        if (uv)
            fprintf(f, "f %u/%u %u/%u %u/%u\n", a, a, b, b, c, c);
        else
            fprintf(f, "f %u %u %u\n", a, b, c);
    }
    return 0;
}
