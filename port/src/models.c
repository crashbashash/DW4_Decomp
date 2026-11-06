/* dw4/models.c — see include/dw4/models.h for the format and the findings behind it. */
#include "dw4/models.h"

#include "dw4/mesh.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Record-relative field offsets, from DW4_Decomp/data/reflection.json: a base class declares
 * its own fields, at absolute offsets within the object, so the *declaring* class is named
 * here (`igGeometryAttr`, `igVertexArray`, `igPrimLengthArray`, and igGeometryAttr1_5's own
 * `_stripLengths`). */
#define GA_VERTEX_ARRAY   0x0cu   /* igGeometryAttr._vertexArray */
#define GA_PRIM_TYPE      0x14u   /* igGeometryAttr._primType */
#define GA_NUM_PRIMS      0x18u   /* igGeometryAttr._numPrims */
#define GA_STRIP_LENGTHS  0x30u   /* igGeometryAttr1_5._stripLengths */
#define VA_VDATA          0x08u   /* igVertexArray._vdata */
#define VA_NUM_VERTS      0x0cu   /* igVertexArray._numVerts */
#define PL_LENGTH_DATA    0x08u   /* igPrimLengthArray._lengthData */
#define PL_NUM_STRIPS     0x0cu   /* igPrimLengthArray._numStrips */

#define MAX_LENGTHS (1u << 20)

static uint32_t rd32(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}


/* Does the record at `rec` have this class?  The class index is the record's first word. */
static int class_is(const dw4_models *m, uint32_t rec, const char *name)
{
    uint32_t cl = rd32(m->b + rec);
    return cl < m->igb.nclasses && m->igb.classes[cl].name &&
           strcmp(m->igb.classes[cl].name, name) == 0;
}

/* Does the block `vdata` list a stream of exactly `want` bytes?  This is the check that makes
 * `_vdata`/`_numVerts` self-validating (`_memSize` IS the stream's content size, #477). */
static int stream_size_is(const dw4_models *m, uint32_t vdata, uint32_t want)
{
    uint32_t i, n = 0, off = 0, len = 0;

    if (dw4_igb_ref(&m->igb, vdata, &off, &len) != 1)
        return 0;
    for (i = 0; i + 4 <= len; i += 4) {
        uint32_t id = rd32(m->b + off + i);
        uint32_t ilen = 0;
        if (dw4_igb_ref(&m->igb, id, NULL, &ilen) == 1 && ilen == want)
            return 1;
        n++;
    }
    (void)n;
    return 0;
}

static void add_geometry(dw4_models *m, uint32_t rec)
{
    dw4_model g;
    uint32_t pt = rd32(m->b + rec + GA_PRIM_TYPE);

    if (pt != 3 && pt != 4)
        return;
    memset(&g, 0, sizeof(g));
    g.rec_off = rec;
    g.vertex_array = rd32(m->b + rec + GA_VERTEX_ARRAY);
    g.prim_type = pt;
    g.num_prims = rd32(m->b + rec + GA_NUM_PRIMS);

    /* The vertex array: `_vdata` names a block that lists this array's streams, and one of
     * them must be `12*_numVerts` bytes -- so the pair validates itself. */
    {
        uint32_t vrec = 0;
        if (dw4_igb_ref(&m->igb, g.vertex_array, &vrec, NULL) == 2 &&
            class_is(m, vrec, "igVertexArray1_1")) {
            uint32_t vd = rd32(m->b + vrec + VA_VDATA);
            uint32_t nv = rd32(m->b + vrec + VA_NUM_VERTS);
            if (nv && stream_size_is(m, vd, 12 * nv)) {
                g.vdata = vd;
                g.num_verts = nv;
            }
        }
    }
    /* The primitive lengths, validated by `sum(lengths) == _numVerts`. */
    if (pt == 4 && g.num_verts) {
        uint32_t prec = 0, pl = rd32(m->b + rec + GA_STRIP_LENGTHS);
        uint32_t ld, ns, off, len, i, sum = 0;
        if (dw4_igb_ref(&m->igb, pl, &prec, NULL) == 2 && class_is(m, prec, "igPrimLengthArray1_1")) {
            ld = rd32(m->b + prec + PL_LENGTH_DATA);
            ns = rd32(m->b + prec + PL_NUM_STRIPS);
            if (ns && ns < MAX_LENGTHS && dw4_igb_ref(&m->igb, ld, &off, &len) == 1 &&
                ns * 4u <= len) {
                for (i = 0; i < ns; i++)
                    sum += rd32(m->b + off + 4 * i);
                if (sum == g.num_verts) {
                    g.lengths_id = ld;
                    g.num_lengths = ns;
                }
            }
        }
    }
    if (m->n < DW4_MODELS_MAX)
        m->m[m->n++] = g;
}

/* The shape -> attribute link (reached offline).  A shape is an `igGeometry`
 * record: its ordinal-2 value is the DCC part name (`pCylinderShape3`, `M_BK17v1_barrelmShape`, ...)
 * and ordinal 8 is its `igAttrList`, whose `_array` (+0x10) is a block of attribute ids.  The ids
 * that are `igGeometryAttr1_5` records are that shape's geometry, so they take its name.  Found by
 * *ordinal*, not by offset: a record's byte offsets shift with a variable-length value (a long name
 * pushes everything after it), while the container's slot numbers do not.  The list's count (+0x08)
 * having to equal the array block's u32 count is the self-check. */
#define GEOM_ATTR_LIST_ORDINAL 8u

static void name_from_shape(dw4_models *m, uint32_t rec)
{
    dw4_igb_record r;
    const char *name = NULL;
    uint32_t i, list = 0, off = 0;

    if (!dw4_igb_decode(&m->igb, rec, &r))
        return;
    for (i = 0; i < r.nvalues; i++) {
        if (r.values[i].ordinal == 2 && r.values[i].type == 4)
            name = r.values[i].str;
        else if (r.values[i].ordinal == GEOM_ATTR_LIST_ORDINAL)
            list = r.values[i].raw;
    }
    if (!list) {             /* fallback: any value whose target is an igAttrList */
        for (i = 0; i < r.nvalues; i++) {
            uint32_t t = 0;
            if (dw4_igb_ref(&m->igb, r.values[i].raw, &t, NULL) == 2 &&
                class_is(m, t, "igAttrList")) {
                list = r.values[i].raw;
                break;
            }
        }
    }
    dw4_igb_record_free(&r);
    if (!name || !name[0] || !list)
        return;
    if (dw4_igb_ref(&m->igb, list, &off, NULL) != 2 || !class_is(m, off, "igAttrList"))
        return;
    {
        uint32_t count = rd32(m->b + off + 0x08);
        uint32_t arr = rd32(m->b + off + 0x10);
        uint32_t aoff = 0, alen = 0;
        if (dw4_igb_ref(&m->igb, arr, &aoff, &alen) != 1 || alen != 4 * count)
            return;                       /* the list's count disagrees with its array */
        for (i = 0; i < count; i++) {
            uint32_t id = rd32(m->b + aoff + 4 * i);
            uint32_t k;
            for (k = 0; k < m->n; k++)
                if (m->m[k].id == id)
                    m->m[k].name = name;
        }
    }
}

static void add_names(dw4_models *m)
{
    uint32_t off = m->igb.chain2_off, i, end;

    for (i = 0; i < m->igb.chain2_n; i++) {
        if (!dw4_igb_record_end(&m->igb, off, &end))
            break;
        if (class_is(m, off, "igGeometry"))
            name_from_shape(m, off);
        off = end;
    }
}

int dw4_models_open(dw4_models *m, const uint8_t *blob, size_t len)
{
    uint32_t off, i, end, idc = 0;

    memset(m, 0, sizeof(*m));
    m->b = blob;
    m->len = len;
    if (dw4_igb_open(&m->igb, blob, len, 0) != 0)
        return -1;
    if (dw4_igb_refs_open(&m->igb) != 0) {
        dw4_igb_close(&m->igb);
        return -1;
    }
    m->pool_off = m->igb.pool_off;
    /* Section 2 is the object chain; walk it by record size (records tile, so a record that
     * does not validate ends the walk -- exactly as the Python decoder collects them).  The
     * table's *object* entries are in this same record order (the format's own invariant), so
     * a cursor over them yields each record's id -- checked against the id's offset, which
     * makes the pairing self-validating rather than assumed. */
    off = m->igb.chain2_off;
    for (i = 0; i < m->igb.chain2_n; i++) {
        uint32_t cl, id = 0xFFFFFFFFu;
        while (idc < m->igb.table_n && m->igb.id_kind[idc] != 2)
            idc++;
        if (idc < m->igb.table_n && m->igb.id_off[idc] == off)
            id = idc++;
        if (!dw4_igb_record_end(&m->igb, off, &end))
            break;
        cl = rd32(blob + off);
        if (cl < m->igb.nclasses && m->igb.classes[cl].name &&
            strcmp(m->igb.classes[cl].name, "igGeometryAttr1_5") == 0) {
            add_geometry(m, off);
            if (m->n)
                m->m[m->n - 1].id = id;
        }
        off = end;
    }
    add_names(m);
    return 0;
}

void dw4_models_close(dw4_models *m)
{
    if (m->igb.classes || m->igb.id_kind)
        dw4_igb_close(&m->igb);
    m->b = NULL;
    m->len = 0;
    m->n = 0;
}

const dw4_model *dw4_models_find(const dw4_models *m, uint32_t vertex_array_id)
{
    uint32_t i;
    for (i = 0; i < m->n; i++)
        if (m->m[i].vertex_array == vertex_array_id)
            return &m->m[i];
    return NULL;
}

void dw4_models_obj_basename(const dw4_model *g, char *out, size_t cap)
{
    dw4_mesh_obj_basename(g->name, g->vertex_array, out, cap);
}

uint32_t dw4_models_streams(const dw4_models *m, uint32_t vdata, uint32_t *ids, uint32_t cap)
{
    uint32_t i, n = 0, off = 0, len = 0;

    if (dw4_igb_ref(&m->igb, vdata, &off, &len) != 1)
        return 0;
    for (i = 0; i + 4 <= len; i += 4) {
        uint32_t id = rd32(m->b + off + i);
        if (dw4_igb_ref(&m->igb, id, NULL, NULL) == 1) {
            if (n < cap)
                ids[n] = id;
            n++;
        }
    }
    return n;
}

int dw4_models_arrays(const dw4_models *m, const dw4_model *g, const uint8_t **pos,
                      const uint8_t **uv)
{
    uint32_t i, n, off = 0, len = 0;

    *pos = NULL;
    *uv = NULL;
    if (!g->num_verts || dw4_igb_ref(&m->igb, g->vdata, &off, &len) != 1)
        return -1;
    n = len / 4;
    for (i = 0; i < n; i++) {
        uint32_t id = rd32(m->b + off + 4 * i);
        uint32_t boff = 0, blen = 0;
        if (dw4_igb_ref(&m->igb, id, &boff, &blen) != 1)
            continue;
        if (!*pos && blen == 12 * g->num_verts)
            *pos = m->b + boff;
        else if (!*uv && blen == 8 * g->num_verts)
            *uv = m->b + boff;
    }
    return *pos ? 0 : -1;
}

int dw4_models_tris(const dw4_models *m, const dw4_model *g, uint32_t **tris, uint32_t *ntris,
                    const char **why)
{
    const uint8_t *lengths = NULL;
    uint32_t off = 0, len = 0;

    /* The triangle rule and the OBJ text live in src/mesh.c, shared with the scene loader so the
     * two front ends cannot drift (the check in tools/verify_scene.py diffs them). */
    if (g->prim_type == 4 && g->lengths_id &&
        dw4_igb_ref(&m->igb, g->lengths_id, &off, &len) == 1)
        lengths = m->b + off;
    return dw4_mesh_tris(g->prim_type, g->num_prims, g->num_verts, lengths, g->num_lengths,
                         tris, ntris, why);
}

int dw4_models_write_obj(const dw4_models *m, const dw4_model *g, FILE *f)
{
    const uint8_t *pos = NULL, *uv = NULL;
    uint32_t *tris = NULL, ntris = 0;
    const char *why = NULL;
    int rc;

    if (dw4_models_arrays(m, g, &pos, &uv) != 0)
        return -1;
    if (dw4_models_tris(m, g, &tris, &ntris, &why) != 0)
        return -1;
    rc = dw4_mesh_write_obj(f, pos, uv, g->num_verts, tris, ntris);
    free(tris);
    return rc;
}
