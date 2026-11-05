/* pose.c — the player's skinning chain from a live dump.  See dw4/pose.h. */
#include "dw4/pose.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dw4_pose {
    uint8_t *b;
    size_t len;
    uint32_t base;

    uint32_t select, palette, node;
    int count;

    uint32_t *slots;   /* bone -> matrix slot */
    int nslots;

    float *mat;        /* count x 16 floats */
    float node_m[16];
};

static uint32_t p_u32(const dw4_pose *p, uint32_t a)
{
    size_t o;
    if (a < p->base || (o = (size_t)(a - p->base)) + 4 > p->len)
        return 0;
    return (uint32_t)p->b[o] | ((uint32_t)p->b[o + 1] << 8) |
           ((uint32_t)p->b[o + 2] << 16) | ((uint32_t)p->b[o + 3] << 24);
}

static const uint8_t *p_ptr(const dw4_pose *p, uint32_t a, size_t n)
{
    size_t o;
    if (a < p->base || (o = (size_t)(a - p->base)) + n > p->len)
        return NULL;
    return p->b + o;
}

dw4_pose *dw4_pose_open(const char *path)
{
    FILE *fp;
    long sz;
    dw4_pose *p;

    if (!path)
        return NULL;
    fp = fopen(path, "rb");
    if (!fp)
        return NULL;
    fseek(fp, 0, SEEK_END);
    sz = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (sz <= 0) {
        fclose(fp);
        return NULL;
    }
    p = (dw4_pose *)calloc(1, sizeof(*p));
    if (!p) {
        fclose(fp);
        return NULL;
    }
    p->len = (size_t)sz;
    p->b = (uint8_t *)malloc(p->len);
    if (!p->b || fread(p->b, 1, p->len, fp) != p->len) {
        fclose(fp);
        free(p->b);
        free(p);
        return NULL;
    }
    fclose(fp);
    /* the same two shapes livetex accepts: 32 MB from 0, 31 MB from 0x00100000 */
    if (p->len == 0x2000000u)
        p->base = 0;
    else if (p->len == 0x1f00000u)
        p->base = 0x00100000u;
    else {
        free(p->b);
        free(p);
        return NULL;
    }
    return p;
}

void dw4_pose_close(dw4_pose *p)
{
    if (!p)
        return;
    free(p->b);
    free(p->slots);
    free(p->mat);
    free(p);
}

int dw4_pose_config(dw4_pose *p, uint32_t select, uint32_t palette, int count, uint32_t node)
{
    uint32_t lst, cnt, arr, i;
    const uint8_t *m;

    if (!p)
        return -1;
    /* select == 0 means an identity bone -> slot mapping: the game's real skinned
     * palette (e.g. the per-bone VU staging copy at 0x1b753b0) is indexed by the
     * bone number itself, so the igBlendMatrixSelect list is not consulted. */
    if (select == 0) {
        lst = 0;
        cnt = (uint32_t)count;
        arr = 0;
    } else {
        lst = p_u32(p, select + 0x28);
        cnt = p_u32(p, lst + 0x08);
        arr = p_u32(p, lst + 0x10);
        if (!cnt || cnt > 256 || !arr || !p_ptr(p, arr, 4 * cnt)) {
            fprintf(stderr, "pose: select %08x has no readable _blendMatrixIndices list\n", select);
            return -1;
        }
    }
    if (count <= 0 || count > 256) {
        fprintf(stderr, "pose: palette count %d is not a matrix count\n", count);
        return -1;
    }
    m = p_ptr(p, palette, (size_t)64 * count);
    if (!m) {
        fprintf(stderr, "pose: palette %08x (%d matrices) is not inside the dump\n", palette, count);
        return -1;
    }
    if (!p_ptr(p, node + 0x20, 64)) {
        fprintf(stderr, "pose: node %08x has no +0x20 matrix in the dump\n", node);
        return -1;
    }
    free(p->slots);
    p->slots = (uint32_t *)malloc(cnt * sizeof(uint32_t));
    if (!p->slots)
        return -1;
    for (i = 0; i < cnt; i++)
        p->slots[i] = arr ? p_u32(p, arr + 4 * i) : i;
    p->nslots = (int)cnt;
    free(p->mat);
    p->mat = (float *)malloc((size_t)16 * count * sizeof(float));
    if (!p->mat)
        return -1;
    memcpy(p->mat, m, (size_t)16 * count * sizeof(float));
    memcpy(p->node_m, p_ptr(p, node + 0x20, 64), 64);
    p->select = select;
    p->palette = palette;
    p->node = node;
    p->count = count;
    return 0;
}

int dw4_pose_count(const dw4_pose *p)
{
    return p ? p->count : 0;
}

int dw4_pose_mesh(const dw4_pose *p, const float *pos, const float *nrm, const uint8_t *bones,
                  int nv, float *out_pos, float *out_nrm)
{
    int i;

    if (!p || !p->mat || !pos || !bones || !out_pos)
        return -1;
    for (i = 0; i < nv; i++) {
        uint32_t b = bones[i];
        uint32_t s;
        const float *m;
        float x, y, z;

        if (b >= (uint32_t)p->nslots)
            return -1;
        s = p->slots[b];
        if (s >= (uint32_t)p->count)
            return -1;
        m = p->mat + 16 * s;
        x = pos[3 * i]; y = pos[3 * i + 1]; z = pos[3 * i + 2];
        /* the matrix read column-wise: basis (m0,m4,m8), translation (m12..14) (#540) */
        out_pos[3 * i] = m[0] * x + m[4] * y + m[8] * z + m[12];
        out_pos[3 * i + 1] = m[1] * x + m[5] * y + m[9] * z + m[13];
        out_pos[3 * i + 2] = m[2] * x + m[6] * y + m[10] * z + m[14];
        if (out_nrm && nrm) {
            /* rotation only; the packed shape normals are the bind ones */
            float nx = nrm[3 * i], ny = nrm[3 * i + 1], nz = nrm[3 * i + 2];
            out_nrm[3 * i] = m[0] * nx + m[4] * ny + m[8] * nz;
            out_nrm[3 * i + 1] = m[1] * nx + m[5] * ny + m[9] * nz;
            out_nrm[3 * i + 2] = m[2] * nx + m[6] * ny + m[10] * nz;
        }
    }
    return 0;
}
