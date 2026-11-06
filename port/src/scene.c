/* dw4/scene.c — the pack loader: the file's ids become 32-bit handles into one arena.
 * See include/dw4/scene.h for why, and include/dw4/mesh.h for the geometry rule it shares with
 * the file reader. */
#include "dw4/scene.h"

#include "dw4/igb.h"
#include "dw4/mesh.h"
#include "dw4/sequencefraction.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

/* The geometry chain's field offsets -- the same ones src/models.c reads, from
 * data/reflection.json (a base class declares its own fields, at absolute offsets). */
#define GA_VERTEX_ARRAY   0x0cu   /* igGeometryAttr._vertexArray */
#define GA_PRIM_TYPE      0x14u   /* igGeometryAttr._primType */
#define GA_NUM_PRIMS      0x18u   /* igGeometryAttr._numPrims */
#define GA_STRIP_LENGTHS  0x30u   /* igGeometryAttr1_5._stripLengths */
#define VA_VDATA          0x08u   /* igVertexArray._vdata */
#define VA_NUM_VERTS      0x0cu   /* igVertexArray._numVerts */
#define PL_LENGTH_DATA    0x08u   /* igPrimLengthArray._lengthData */
#define PL_NUM_STRIPS     0x0cu   /* igPrimLengthArray._numStrips */
#define SHAPE_NAME_ORD     2u     /* igGeometry's DCC name (a string value) */
#define SHAPE_ATTRS_ORD    8u     /* igGeometry's igAttrList id */
#define ATTRLIST_ARRAY    0x10u   /* igAttrList._array */
#define ATTRLIST_COUNT    0x08u   /* igAttrList._count */
/* The material -> texture chain (findings: the front-end title's UI textures are inline in the
 * pack).  The ordinals are the classes' own descriptor slots, read from the pack's class triples
 * (not guessed): igAttrSet._attributes, igTextureBindAttr._texture, igTextureAttr._image,
 * igImage._px/_py/_imageSize/_pImage/_pClut/_bytesPerRow/_pNameString, igClut._pData. */
/* `igTransformSequence1_5`'s two `igVec3fList` slots (the class' descriptor order). */
#define SEQ_TRANS_ORD        2u
#define SEQ_SCALE_ORD        4u
#define ATTRSET_ATTRS_ORD    8u   /* igAttrSet._attributes (an igAttrList id) */
#define FOGSTATE_EN_ORD      4u   /* igFogStateAttr._enabled */
#define ALPHAFN_REF_ORD      5u   /* igAlphaFunctionAttr._refValue (a float; _func is ordinal 4) */
#define BLENDFN_SRC_ORD      4u   /* igBlendFunctionAttr._src / _dst (probed from the pack's triples) */
#define BLENDFN_DST_ORD      5u
#define XFORM_TARGET_ORD     9u   /* igTransform._target (read from the pack's triples, #716) */
#define COLOR_VALUE_ORD      4u   /* igColorAttr._color (the 4-float RGBA) */
#define TEXBIND_TEX_ORD      4u   /* igTextureBindAttr._texture (an igTextureAttr id) */
#define TEXATTR_IMAGE_ORD   12u   /* igTextureAttr._image (an igImage id) */
#define IMG_PX_ORD           2u
#define IMG_PY_ORD           3u
#define IMG_IMAGESIZE_ORD   12u
#define IMG_PIMAGE_ORD      13u
#define IMG_PCLUT_ORD       17u
#define IMG_BPR_ORD         19u
#define IMG_NAMESTR_ORD     22u
#define CLUT_PDATA_ORD       5u

#define MAX_LENGTHS (1u << 20)

static uint32_t rd32(const uint8_t *p)
{
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}

const dw4_scene_ent *dw4_scene_lookup(const dw4_scene *s, uint32_t id)
{
    if (!s->ent || id >= s->nent)
        return NULL;
    return &s->ent[id];
}

dw4_handle dw4_scene_handle(const dw4_scene *s, uint32_t id)
{
    dw4_handle h = { 0 };
    const dw4_scene_ent *e = dw4_scene_lookup(s, id);
    return e ? e->h : h;
}

static const dw4_scene_ent *ent_of_handle(const dw4_scene *s, dw4_handle h)
{
    uint32_t lo = 0, hi = s->nent;
    while (lo < hi) {                     /* the table is in id order, so in handle order */
        uint32_t mid = lo + (hi - lo) / 2;
        if (s->ent[mid].h.off == h.off)
            return &s->ent[mid];
        if (s->ent[mid].h.off < h.off)
            lo = mid + 1;
        else
            hi = mid;
    }
    return NULL;
}

uint32_t dw4_scene_id_of(const dw4_scene *s, dw4_handle h)
{
    const dw4_scene_ent *e = ent_of_handle(s, h);
    return e ? e->id : 0;
}

const void *dw4_scene_host(const dw4_scene *s, dw4_handle h)
{
    if (!s->arena || h.off < DW4_SCENE_BASE || h.off >= s->arena_len)
        return NULL;
    return s->arena + h.off;
}

/* A reference field of a record, as a handle.  Not a guess: after the id -> pointer pass every
 * `igObjectRef`/`igMemoryRef` value IS a handle (or NULL), so a reader takes it as one.  A block's
 * *contents* are still ids -- that pass is deliberate (see scene.h) -- and those go through
 * `dw4_scene_handle()`. */
static dw4_handle field_ref(const uint8_t *rec, uint32_t off)
{
    dw4_handle h = { 0 };
    uint32_t v = rd32(rec + off);
    if (v != 0xFFFFFFFF)
        h.off = v;
    return h;
}

/* Does this id name a block of exactly `size` bytes?  The check that makes the stream pair
 * self-validating (a stream's `_memSize` IS its content size). */
static int block_of_size(const dw4_scene *s, uint32_t id, uint32_t size, dw4_handle *out)
{
    const dw4_scene_ent *e = dw4_scene_lookup(s, id);
    if (!e || e->kind != 1 || e->size != size)
        return 0;
    if (out)
        *out = e->h;
    return 1;
}

/* The record at `h` has this class name? */
static int class_is(const dw4_scene *s, const dw4_igb *g, dw4_handle h, const char *name)
{
    const uint8_t *rec = (const uint8_t *)dw4_scene_host(s, h);
    uint32_t cl;
    if (!rec)
        return 0;
    cl = rd32(rec);
    return cl < g->nclasses && g->classes[cl].name && strcmp(g->classes[cl].name, name) == 0;
}

/* One value of an arena record, by the container's own *ordinal* (never by a byte offset: a
 * variable-length value such as the name string shifts everything after it).  Returns the 4-byte
 * value, and for a string sets `*str`.  0 when the ordinal is not in the record. */
static uint32_t rec_value(const dw4_igb *g, const uint8_t *rec, uint32_t ordinal, const char **str)
{
    uint32_t cl = rd32(rec), q = 8, k;
    const dw4_igb_class *c;

    if (str)
        *str = NULL;
    if (cl >= g->nclasses)
        return 0;
    c = &g->classes[cl];
    for (k = 0; k < c->ntriples; k++) {
        const dw4_igb_triple *t = &c->triples[k];
        if (t->type == 4) {
            uint32_t n = rd32(rec + q);
            if (t->ordinal == ordinal) {
                if (str && n)
                    *str = (const char *)(rec + q + 4);
                return 0;
            }
            q += 4 + n;
        } else {
            uint32_t w = (t->size + 3u) & ~3u;
            if (t->ordinal == ordinal)
                return rd32(rec + q);
            q += w;
        }
    }
    return 0;
}

/* The byte offset of the class value with `ordinal` in `rec`, walking the class's triples exactly as
 * `rec_value` does (so a vector field can be read in place).  0 when the class has no such slot. */
static uint32_t rec_off(const dw4_igb *g, const uint8_t *rec, uint32_t ordinal)
{
    uint32_t cl = rd32(rec), q = 8, k;
    const dw4_igb_class *c;

    if (cl >= g->nclasses)
        return 0;
    c = &g->classes[cl];
    for (k = 0; k < c->ntriples; k++) {
        const dw4_igb_triple *t = &c->triples[k];

        if (t->type == 4) {
            if (t->ordinal == ordinal)
                return 0;
            q += 4 + rd32(rec + q);
        } else {
            if (t->ordinal == ordinal)
                return q;
            q += (t->size + 3u) & ~3u;
        }
    }
    return 0;
}

static void add_mesh(dw4_scene *s, const dw4_igb *g, uint32_t id, const uint8_t *rec,
                     const char *name)
{
    dw4_scene_mesh m;
    uint32_t vrec_id, nv, i, ns;
    dw4_handle vrec, lengths = { 0 };
    const uint8_t *vrec_p, *vd_p;
    uint32_t blen = 0;

    memset(&m, 0, sizeof(m));
    m.attr_id = id;
    m.attr = dw4_scene_handle(s, id);
    m.prim_type = rd32(rec + GA_PRIM_TYPE);
    if (m.prim_type != 3 && m.prim_type != 4)
        return;
    m.name = name;
    m.num_prims = rd32(rec + GA_NUM_PRIMS);

    /* _vertexArray -> igVertexArray1_1, then _vdata (a block listing the streams) + _numVerts.
     * `_vertexArray` is an igObjectRef, so after materialisation it is a handle. */
    vrec = field_ref(rec, GA_VERTEX_ARRAY);
    vrec_id = dw4_scene_id_of(s, vrec);          /* the pack's id, for the mesh's name/id */
    m.vertex_array_id = vrec_id;
    vrec_p = (const uint8_t *)dw4_scene_host(s, vrec);
    if (!vrec_p || !class_is(s, g, vrec, "igVertexArray1_1"))
        return;
    {
        dw4_handle vd_h = field_ref(vrec_p, VA_VDATA);
        const dw4_scene_ent *e = ent_of_handle(s, vd_h);
        vd_p = dw4_scene_host(s, vd_h);
        if (!vd_p || !e)
            return;
        blen = e->size;
    }
    nv = rd32(vrec_p + VA_NUM_VERTS);
    if (!vd_p || !nv)
        return;
    ns = blen / 4;
    for (i = 0; i < ns; i++) {
        uint32_t sid = rd32(vd_p + 4 * i);
        dw4_handle h;
        if (block_of_size(s, sid, 12 * nv, &h) && !m.positions.off)
            m.positions = h;
        else if (block_of_size(s, sid, 12 * nv, &h) && !m.normals.off)
            m.normals = h;         /* the second 12*n stream is the vertex normals */
        else if (block_of_size(s, sid, 8 * nv, &h) && !m.uvs.off)
            m.uvs = h;
    }
    if (!m.positions.off)
        return;
    m.num_verts = nv;

    /* _stripLengths -> igPrimLengthArray1_1, validated by sum(lengths) == _numVerts */
    if (m.prim_type == 4) {
        dw4_handle pl_h = field_ref(rec, GA_STRIP_LENGTHS);
        const uint8_t *pl = dw4_scene_host(s, pl_h);
        if (!pl || !class_is(s, g, pl_h, "igPrimLengthArray1_1"))
            return;
        {
            dw4_handle ld_h = field_ref(pl, PL_LENGTH_DATA);
            uint32_t n = rd32(pl + PL_NUM_STRIPS);
            const dw4_scene_ent *le = ent_of_handle(s, ld_h);
            const uint8_t *ld_p;
            uint32_t sum = 0, k;
            if (!n || n > MAX_LENGTHS || !le || le->kind != 1 || le->size != 4 * n)
                return;                   /* the count must match the block's size */
            lengths = ld_h;
            ld_p = (const uint8_t *)dw4_scene_host(s, lengths);
            for (k = 0; k < n; k++)
                sum += rd32(ld_p + 4 * k);
            if (sum != nv)
                return;
            m.lengths = lengths;
            m.num_lengths = n;
        }
    }
    if (s->nmesh < 0x10000u) {
        dw4_scene_mesh *dst = (dw4_scene_mesh *)realloc(s->mesh, (s->nmesh + 1) * sizeof(*dst));
        if (!dst)
            return;
        s->mesh = dst;
        s->mesh[s->nmesh++] = m;
    }
}

/* The shape -> attribute link: an igGeometry's ordinal-2 value names it and its ordinal-8
 * igAttrList's array holds the ids of its attributes.  By ordinal, because a record's byte
 * offsets shift with the length of its name string. */
static void add_names(dw4_scene *s, const dw4_igb *g)
{
    uint32_t i;
    for (i = 0; i < s->nent; i++) {
        const uint8_t *rec;
        const char *name = NULL;
        uint32_t list;
        dw4_handle al_h, arr_h;
        const uint8_t *al;
        uint32_t count, k;
        const uint8_t *arr_p;

        if (s->ent[i].kind != 2)
            continue;
        rec = (const uint8_t *)dw4_scene_host(s, s->ent[i].h);
        if (!rec || !class_is(s, g, s->ent[i].h, "igGeometry"))
            continue;
        rec_value(g, rec, SHAPE_NAME_ORD, &name);
        /* by ordinal, never by offset: the name string before it shifts every later value */
        list = rec_value(g, rec, SHAPE_ATTRS_ORD, NULL);
        al_h.off = list == 0xFFFFFFFF ? 0 : list;
        al = (const uint8_t *)dw4_scene_host(s, al_h);
        if (!name || !name[0] || !al || !class_is(s, g, al_h, "igAttrList"))
            continue;
        count = rd32(al + ATTRLIST_COUNT);
        arr_h = field_ref(al, ATTRLIST_ARRAY);
        arr_p = (const uint8_t *)dw4_scene_host(s, arr_h);
        if (!arr_p || !count)
            continue;
        {
            const dw4_scene_ent *e = ent_of_handle(s, arr_h);
            if (!e || e->kind != 1 || e->size != 4 * count)
                continue;                     /* the list's count disagrees with its array */
        }
        for (k = 0; k < count; k++) {
            uint32_t aid = rd32(arr_p + 4 * k);
            uint32_t j;
            for (j = 0; j < s->nmesh; j++)
                if (s->mesh[j].attr_id == aid)
                    s->mesh[j].name = name;
        }
    }
}

/* A record field's value after the id -> pointer pass is already a handle (or 0xFFFFFFFF for
 * NULL); a block's *contents* are still ids.  This turns the former into a handle. */
static dw4_handle refh(uint32_t v)
{
    dw4_handle h;
    h.off = (v == 0xFFFFFFFFu) ? 0u : v;
    return h;
}

/* Keep an inline image (`igImage` + its `igClut`) once, keyed by id.  `rec` is the materialised
 * igImage record; the grid and palette blocks are read later through `dw4_scene_host`. */
static void scene_add_image(dw4_scene *s, const dw4_igb *g, uint32_t id, const uint8_t *rec)
{
    dw4_scene_image im;
    const char *nm = NULL;

    if (dw4_scene_image_of(s, id))
        return;
    memset(&im, 0, sizeof(im));
    im.id = id;
    im.w = rec_value(g, rec, IMG_PX_ORD, NULL);
    im.h = rec_value(g, rec, IMG_PY_ORD, NULL);
    im.size = rec_value(g, rec, IMG_IMAGESIZE_ORD, NULL);
    im.bpr = rec_value(g, rec, IMG_BPR_ORD, NULL);
    rec_value(g, rec, IMG_NAMESTR_ORD, &nm);
    im.name = nm;
    im.grid = refh(rec_value(g, rec, IMG_PIMAGE_ORD, NULL));
    {
        dw4_handle ch = refh(rec_value(g, rec, IMG_PCLUT_ORD, NULL));
        const uint8_t *cr = (const uint8_t *)dw4_scene_host(s, ch);
        if (cr && class_is(s, g, ch, "igClut"))
            im.pal = refh(rec_value(g, cr, CLUT_PDATA_ORD, NULL));
    }
    if (!im.bpr)
        im.bpr = im.w;
    if (!im.size)
        im.size = im.w * im.h;
    {
        dw4_scene_image *d = (dw4_scene_image *)realloc(s->img, (s->nimg + 1) * sizeof(*d));
        if (!d)
            return;
        s->img = d;
        s->img[s->nimg++] = im;
    }
}

/* The material -> texture link.  An `igAttrSet`'s ordinal-2 `_attributes` igAttrList holds the set's
 * attribute objects; an `igTextureBindAttr` among them names an `igTextureAttr` whose ordinal-10
 * `_image` is the inline `igImage`.  Recorded on the attr-set node, so a geometry node inherits it
 * from its nearest ancestor -- this is the pack's own binding, not a name convention. */
static void add_materials(dw4_scene *s, const dw4_igb *g)
{
    uint32_t i;

    /* World packs leave igTextureBindAttr._texture NULL. The controller names
     * a texture in a separately mounted pack and the exact attribute-set target.
     * Apply to every occurrence of that object in the flattened graph. */
    for (i = 0; i < s->nent; i++) {
        const uint8_t *rec;
        const char *name = NULL;
        uint32_t target, j;
        if (s->ent[i].kind != 2 ||
            !class_is(s, g, s->ent[i].h, "beTextureCtrlAttr")) continue;
        rec = dw4_scene_host(s, s->ent[i].h);
        rec_value(g, rec, 2, &name);
        target = dw4_scene_id_of(s, refh(rec_value(g, rec, 3, NULL)));
        if (!name || !target) continue;
        for (j = 0; j < s->nnode; j++)
            if (s->node[j].id == target) s->node[j].tex_name = name;
    }

    for (i = 0; i < s->nnode; i++) {
        dw4_scene_node *n = &s->node[i];
        dw4_handle h, al_h;
        const uint8_t *rec, *al, *arr_p;
        uint32_t list, count, k;

        if (!n->class_name || (strcmp(n->class_name, "igAttrSet") != 0 &&
                              strcmp(n->class_name, "igGeometry") != 0 &&
                              strcmp(n->class_name, "igBlendMatrixSelect") != 0))
            continue;
        h = dw4_scene_handle(s, n->id);
        rec = (const uint8_t *)dw4_scene_host(s, h);
        if (!rec)
            continue;
        list = rec_value(g, rec, ATTRSET_ATTRS_ORD, NULL);
        al_h = refh(list);
        al = (const uint8_t *)dw4_scene_host(s, al_h);
        if (!al || !class_is(s, g, al_h, "igAttrList"))
            continue;
        count = rd32(al + ATTRLIST_COUNT);
        arr_p = (const uint8_t *)dw4_scene_host(s, field_ref(al, ATTRLIST_ARRAY));
        if (!arr_p || !count)
            continue;
        for (k = 0; k < count; k++) {
            dw4_handle ah = dw4_scene_handle(s, rd32(arr_p + 4 * k));
            const uint8_t *ar = (const uint8_t *)dw4_scene_host(s, ah);
            dw4_handle th, ih;
            const uint8_t *tr, *ir;
            uint32_t img_id;

            if (!ar)
                continue;
            if (getenv("DW4_SCENE_ATTRS")) {   /* probe: every attribute an attr-set holds */
                uint32_t cl = rd32(ar), o;
                printf("  attrset node %u '%s' attr %u %s:", i, n->name ? n->name : "-", k,
                       cl < g->nclasses && g->classes[cl].name ? g->classes[cl].name : "?");
                for (o = 1; o <= 12; o++)
                    printf(" o%u=%u", o, rec_value(g, ar, o, NULL));
                printf("\n");
            }
            if (class_is(s, g, ah, "igModelViewMatrixAttr") ||
                class_is(s, g, ah, "igProjectionMatrixAttr")) {
                uint32_t off = rec_off(g, ar, 4);
                const dw4_scene_ent *ae = ent_of_handle(s, ah);
                int view = class_is(s, g, ah, "igModelViewMatrixAttr");
                if (off && ae && off + 64 <= ae->size) {
                    memcpy(view ? n->view : n->projection, ar + off, 64);
                    if (view) n->has_view = 1; else n->has_projection = 1;
                }
            }
            if (class_is(s, g, ah, "igViewportAttr")) {
                uint32_t v;
                for (v = 0; v < 4; v++) n->viewport[v] = rec_value(g, ar, 4 + v, NULL);
                for(v=0;v<2;v++){
                    uint32_t value=rec_value(g,ar,9+v,NULL);
                    memcpy(n->viewport_z+v,&value,sizeof value);
                }
                n->has_viewport = 1;
            }
            /* The set's own colour: an `igColorAttr` in the same list carries the RGBA the pack
             * shades the set with.  Its `_color` is the record's ordinal-4 value. */
            if (!n->has_color && class_is(s, g, ah, "igColorAttr")) {
                uint32_t co = rec_off(g, ar, COLOR_VALUE_ORD);
                if (co) {
                    memcpy(n->color, ar + co, 4 * sizeof(float));
                    n->has_color = 1;
                }
            }
            if (!n->has_blend && class_is(s, g, ah, "igBlendFunctionAttr")) {
                n->blend_src = rec_value(g, ar, BLENDFN_SRC_ORD, NULL);
                n->blend_dst = rec_value(g, ar, BLENDFN_DST_ORD, NULL);
                n->has_blend = 1;
            }
            if (!n->has_alpha && class_is(s, g, ah, "igAlphaFunctionAttr")) {
                uint32_t bits = rec_value(g, ar, ALPHAFN_REF_ORD, NULL);

                memcpy(&n->alpha_ref, &bits, 4);
                n->has_alpha = 1;
            }
            if (!n->has_fog && class_is(s, g, ah, "igFogStateAttr")) {
                n->fog_enabled = rec_value(g, ar, FOGSTATE_EN_ORD, NULL);
                n->has_fog = 1;
            }
            if (class_is(s, g, ah, "igMaterialAttr")) {
                uint32_t df = rec_off(g, ar, 5), am = rec_off(g, ar, 6), em = rec_off(g, ar, 7);
                if (df && am && em) {
                    memcpy(n->material_diffuse, ar+df, 16);
                    memcpy(n->material_ambient, ar+am, 16);
                    memcpy(n->material_emission, ar+em, 16);
                    n->has_material = 1;
                }
            }
            if (class_is(s, g, ah, "igLightingStateAttr")) {
                n->has_lighting = 1;
                n->lighting_enabled = rec_value(g, ar, 4, NULL) != 0;
            }
            if (class_is(s, g, ah, "igTextureMatrixStateAttr"))
                n->texmat_state = 1;
            if (class_is(s, g, ah, "igLightingStateAttr") || class_is(s, g, ah, "igLightAttr") ||
                class_is(s, g, ah, "igLightStateAttr"))
                n->light_state = 1;
            if (class_is(s, g, ah, "igBlendStateAttr")) {
                n->has_blend_state = 1;
                n->blend_enabled = rec_value(g, ar, 4, NULL) != 0;
            }
            if (class_is(s, g, ah, "igDepthWriteStateAttr")) {
                n->has_depth_write = 1;
                n->depth_write = rec_value(g, ar, 4, NULL) != 0;
            }
            if(class_is(s,g,ah,"igDepthStateAttr")){
                n->has_depth_state=1;
                n->depth_enabled=rec_value(g,ar,4,NULL)!=0;
            }
            if(class_is(s,g,ah,"igColorMaskAttr")){
                n->has_color_mask=1;n->color_mask=0;
                /* Original reflected _red/_green/_blue/_alpha booleans enable
                 * writes. Their false values correspond to masked GS bytes. */
                for(unsigned channel=0;channel<4;channel++)
                    if(!rec_value(g,ar,4+channel,NULL))n->color_mask|=1u<<channel;
            }
            if (n->tex_image)
                continue;
            if (!class_is(s, g, ah, "igTextureBindAttr"))
                continue;
            th = refh(rec_value(g, ar, TEXBIND_TEX_ORD, NULL));
            tr = (const uint8_t *)dw4_scene_host(s, th);
            if (!tr || !class_is(s, g, th, "igTextureAttr"))
                continue;
            ih = refh(rec_value(g, tr, TEXATTR_IMAGE_ORD, NULL));
            ir = (const uint8_t *)dw4_scene_host(s, ih);
            if (!ir || !class_is(s, g, ih, "igImage"))
                continue;
            img_id = dw4_scene_id_of(s, ih);
            n->tex_image = img_id;
            scene_add_image(s, g, img_id, ir);
        }
    }
}

/* Retail lights with a packed block of infinite lights that the VU1 program CALC_INFINITE_4 rotates in place into object space on
 * every draw that follows a hardware matrix upload (draw-submit flag DAT_0056b5f8, one-shot).  The EE re-sends a fresh eye-space
 * block only after a model-view upload, so the k-th draw after a fresh block sees the light rotated k further times.  Count k per
 * mesh from the depth-first draw order of each "BG02" root:
 *   root start                                  pending, fresh
 *   igTransform target 0, enter and leave       pending, fresh      (a model-view upload re-sends the block)
 *   igTransform target 9, enter                 pending             (a texture-matrix upload)
 *   igTransform target 9, leave                 pending in the transform model only
 *   texture-matrix scope, enter and leave       pending in the scope model only (leaving restores the identity matrix)
 *   mesh: if pending { k = fresh ? 0 : k + 1; fresh = 0; pending = 0 }
 * The transform model and the scope model are run side by side and a mesh keeps its k only where they agree; both reproduce the
 * measured stag0001 draws (k = 0 ground, 1, 2, 3, 3 for the grid overlays).  Anything the walk does not model -- a node class other
 * than igAttrSet / igGroup / igGeometry / igTransform below the root, an igTransform with another target, a light or lighting-state
 * attribute -- poisons the rest of the root: those meshes keep k = 0.  Whether a hidden switch branch hides uploads is the reason
 * switches poison too.  Evidence is one stage (stag0001); other stages are the same rule extrapolated. */
struct lr_model { unsigned char pending, fresh, k; };
static void lr_event(struct lr_model *m, int fresh) { m->pending = 1; if (fresh) m->fresh = 1; }
static void lr_mesh(struct lr_model *m)
{
    if (!m->pending) return;
    if (m->fresh) { m->k = 0; m->fresh = 0; }
    else if (m->k < 255) m->k++;
    m->pending = 0;
}

static void lr_walk(dw4_scene *s, uint32_t root, const uint32_t *first, const uint32_t *next, uint32_t *cursor, uint32_t *stack)
{
    struct lr_model a = {1, 1, 0}, b = {1, 1, 0};   /* a: transform model, b: scope model */
    int poison = 0;
    uint32_t sp = 0;

    stack[sp++] = root;
    cursor[root] = first[root];
    while (sp) {
        uint32_t node = stack[sp - 1], c = cursor[node];
        const dw4_scene_node *n;
        const char *cl;

        if (c == 0xFFFFFFFFu) {                      /* leave */
            n = &s->node[node];
            cl = n->class_name ? n->class_name : "";
            sp--;
            if (node == root)
                break;
            if (!strcmp(cl, "igTransform")) {
                if (n->xform_target == 0) { lr_event(&a, 1); lr_event(&b, 1); }
                else if (n->xform_target == 9) lr_event(&a, 0);
            }
            if (n->texmat_state) lr_event(&b, 0);
            continue;
        }
        cursor[node] = next[c];                      /* enter child c */
        n = &s->node[c];
        cl = n->class_name ? n->class_name : "";
        if (!strcmp(cl, "igTransform")) {
            if (n->xform_target == 0) { lr_event(&a, 1); lr_event(&b, 1); }
            else if (n->xform_target == 9) { lr_event(&a, 0); lr_event(&b, 0); }
            else poison = 1;
        } else if (strcmp(cl, "igAttrSet") && strcmp(cl, "igGroup") && strcmp(cl, "igGeometry"))
            poison = 1;
        if (n->texmat_state) lr_event(&b, 0);
        if (n->light_state) poison = 1;
        if (n->mesh < s->nmesh) {
            lr_mesh(&a);
            lr_mesh(&b);
            s->node[c].light_rot = !poison && a.k == b.k ? a.k : 0;
        }
        stack[sp++] = c;
        cursor[c] = first[c];
    }
}

static void compute_light_rot(dw4_scene *s)
{
    uint32_t i, *first, *next, *last, *stack;

    if (!s->nnode)
        return;
    first = (uint32_t *)malloc((size_t)s->nnode * 4 * sizeof *first);
    if (!first)
        return;
    next = first + s->nnode;
    last = next + s->nnode;
    stack = last + s->nnode;
    for (i = 0; i < s->nnode; i++)
        first[i] = next[i] = last[i] = 0xFFFFFFFFu;
    for (i = 0; i < s->nnode; i++) {
        uint32_t p = s->node[i].parent;

        if (p >= s->nnode)
            continue;
        if (first[p] == 0xFFFFFFFFu) first[p] = i; else next[last[p]] = i;
        last[p] = i;
    }
    for (i = 0; i < s->nnode; i++) {
        const dw4_scene_node *n = &s->node[i];
        uint32_t p, guard = 0;
        int root = n->name && !strcmp(n->name, "BG02");

        for (p = n->parent; root && p < s->nnode && guard++ < s->nnode; p = s->node[p].parent)
            if (s->node[p].name && !strcmp(s->node[p].name, "BG02"))
                root = 0;                           /* the outermost BG02 starts the walk */
        if (root)
            lr_walk(s, i, first, next, last, stack);   /* last[] is free to serve as the child cursor now */
    }
    free(first);
}

uint32_t dw4_scene_node_light_rot(const dw4_scene *s, uint32_t node)
{
    return s && s->node && node < s->nnode ? s->node[node].light_rot : 0;
}

/* node -> mesh by attribute id.  A geometry class node's igGeometry's ordinal-8 igAttrList names
 * its attributes; the mesh whose `attr_id` is in that list is the one it draws.  Exact, so the
 * several shapes that share a DCC name stay distinct. */
static void link_nodes(dw4_scene *s, const dw4_igb *g)
{
    uint32_t i;

    for (i = 0; i < s->nnode; i++) {
        dw4_scene_node *n = &s->node[i];
        dw4_handle h, al_h;
        const uint8_t *rec, *al, *arr_p;
        uint32_t list, count, k;

        if (!n->class_name || strcmp(n->class_name, "igGeometry") != 0 || n->mesh != 0xFFFFFFFFu)
            continue;
        h = dw4_scene_handle(s, n->id);
        rec = (const uint8_t *)dw4_scene_host(s, h);
        if (!rec)
            continue;
        list = rec_value(g, rec, SHAPE_ATTRS_ORD, NULL);
        al_h = refh(list);
        al = (const uint8_t *)dw4_scene_host(s, al_h);
        if (!al || !class_is(s, g, al_h, "igAttrList"))
            continue;
        count = rd32(al + ATTRLIST_COUNT);
        arr_p = (const uint8_t *)dw4_scene_host(s, field_ref(al, ATTRLIST_ARRAY));
        if (!arr_p || !count)
            continue;
        for (k = 0; k < count; k++) {
            uint32_t aid = rd32(arr_p + 4 * k), j;

            /* The geometry's own colour: its attribute list names the `igColorAttr` the pack shades
             * this mesh with, read in place from the record's ordinal-4 `_color`. */
            if (!n->has_color) {
                dw4_handle ch = dw4_scene_handle(s, aid);
                const uint8_t *cr = (const uint8_t *)dw4_scene_host(s, ch);

                if (cr && class_is(s, g, ch, "igColorAttr")) {
                    uint32_t co = rec_off(g, cr, COLOR_VALUE_ORD);

                    if (co) {
                        memcpy(n->color, cr + co, 4 * sizeof(float));
                        n->has_color = 1;
                    }
                }
            }
            if (!n->has_alpha) {
                dw4_handle xh = dw4_scene_handle(s, aid);
                const uint8_t *xr = (const uint8_t *)dw4_scene_host(s, xh);

                if (xr && class_is(s, g, xh, "igAlphaFunctionAttr")) {
                    uint32_t bits = rec_value(g, xr, ALPHAFN_REF_ORD, NULL);

                    memcpy(&n->alpha_ref, &bits, 4);
                    n->has_alpha = 1;
                }
            }
            if (!n->has_blend) {
                dw4_handle bh = dw4_scene_handle(s, aid);
                const uint8_t *br = (const uint8_t *)dw4_scene_host(s, bh);

                if (br && class_is(s, g, bh, "igBlendFunctionAttr")) {
                    n->blend_src = rec_value(g, br, BLENDFN_SRC_ORD, NULL);
                    n->blend_dst = rec_value(g, br, BLENDFN_DST_ORD, NULL);
                    n->has_blend = 1;
                }
            }
            if (n->mesh != 0xFFFFFFFFu)
                continue;
            for (j = 0; j < s->nmesh; j++)
                if (s->mesh[j].attr_id == aid) {
                    n->mesh = j;
                    break;
                }
        }
    }
}

uint32_t dw4_scene_node_mesh(const dw4_scene *s, uint32_t node)
{
    if (!s || !s->node || node >= s->nnode)
        return 0xFFFFFFFFu;
    return s->node[node].mesh;
}

int dw4_scene_node_fog(const dw4_scene *s, uint32_t node, uint32_t *enabled)
{
    uint32_t guard = 0;

    if (!s || !s->node || node >= s->nnode)
        return 0;
    while (node < s->nnode && guard++ < 64u) {
        if (s->node[node].has_fog) {
            if (enabled)
                *enabled = s->node[node].fog_enabled;
            return 1;
        }
        if (s->node[node].parent == 0xFFFFFFFFu)
            break;
        node = s->node[node].parent;
    }
    return 0;
}

int dw4_scene_node_alpha_ref(const dw4_scene *s, uint32_t node, float *ref)
{
    uint32_t guard = 0;

    if (!s || !s->node || node >= s->nnode)
        return 0;
    while (node < s->nnode && guard++ < 64u) {
        if (s->node[node].has_alpha) {
            if (ref)
                *ref = s->node[node].alpha_ref;
            return 1;
        }
        if (s->node[node].parent == 0xFFFFFFFFu)
            break;
        node = s->node[node].parent;
    }
    return 0;
}

int dw4_scene_node_blend(const dw4_scene *s, uint32_t node, uint32_t *src, uint32_t *dst)
{
    uint32_t guard = 0;

    if (!s || !s->node || node >= s->nnode)
        return 0;
    while (node < s->nnode && guard++ < 64u) {
        if (s->node[node].has_blend) {
            if (src)
                *src = s->node[node].blend_src;
            if (dst)
                *dst = s->node[node].blend_dst;
            return 1;
        }
        if (s->node[node].parent == 0xFFFFFFFFu)
            break;
        node = s->node[node].parent;
    }
    return 0;
}

uint32_t dw4_scene_node_texture(const dw4_scene *s, uint32_t node)
{
    uint32_t guard = 0;

    if (!s || !s->node || node >= s->nnode)
        return 0;
    while (node < s->nnode && guard++ < 64u) {   /* MAX_DEPTH (the graph's own bound) */
        if (s->node[node].tex_name) return 0;
        if (s->node[node].tex_image)
            return s->node[node].tex_image;
        if (s->node[node].parent == 0xFFFFFFFFu)
            break;
        node = s->node[node].parent;
    }
    return 0;
}

const char *dw4_scene_node_texture_name(const dw4_scene *s, uint32_t node)
{
    uint32_t guard = 0;
    if (!s) return NULL;
    while (node < s->nnode && guard++ < 64u) {
        if (s->node[node].tex_name) return s->node[node].tex_name;
        if (s->node[node].tex_image) return NULL;
        node = s->node[node].parent;
    }
    return NULL;
}

const dw4_scene_image *dw4_scene_image_of(const dw4_scene *s, uint32_t image_id)
{
    uint32_t i;

    if (!s || !image_id)
        return NULL;
    for (i = 0; i < s->nimg; i++)
        if (s->img[i].id == image_id)
            return &s->img[i];
    return NULL;
}

/* The loader's id -> pointer pass.  Every object record's `igObjectRef` and
 * `igMemoryRef` values become handles; the kind is the value's own descriptor type id (finding
 * #482), so no table is involved.  A NULL stays NULL. */
static void materialise(dw4_scene *s, const dw4_igb *g)
{
    uint32_t i;

    for (i = 0; i < s->nent; i++) {
        uint8_t *rec;
        const dw4_igb_class *c;
        uint32_t k, q, cl, nref = 0;

        if (s->ent[i].kind != 2)
            continue;
        rec = s->arena + s->ent[i].h.off;
        cl = rd32(rec);
        if (cl >= g->nclasses || s->ent[i].size < 8)
            continue;
        c = &g->classes[cl];
        q = 8;
        for (k = 0; k < c->ntriples; k++) {
            const dw4_igb_triple *t = &c->triples[k];
            if (t->type == 4) {
                q += 4 + rd32(rec + q);
                continue;
            }
            if (t->type == DW4_IGB_TY_OBJECTREF || t->type == DW4_IGB_TY_MEMREF) {
                uint32_t v = rd32(rec + q);
                if (v == 0xFFFFFFFF) {
                    s->nnull++;
                } else {
                    dw4_handle h = dw4_scene_handle(s, v);
                    if (h.off) {
                        memcpy(rec + q, &h.off, 4);
                        s->nref++;
                        nref++;
                    } else {
                        s->nref_bad++;      /* must stay 0: a reference type is an id or NULL */
                    }
                }
            }
            q += (t->size + 3u) & ~3u;
        }
        (void)nref;
    }
}

/* ---- the scene graph (porting P4.2) --------------------------------------------------------
 *
 *   igSceneInfo  name + igGraphPathList
 *     igGraphPath      -> igNodeList            (the path's roots)
 *       igNodeList     -> node ids
 *         node         -> its name (a string value), an igMatrix44f (when it has one), an
 *                         igNodeList of children, and an igGeometry it draws
 *
 * Every value is found by its descriptor **type**, never by a hardcoded class or offset: the matrix
 * is whichever value is an igMatrix44f (type 40), the children whichever reference resolves to an
 * igNodeList, the geometry whichever resolves to an igGeometry. That is all a pack states -- and a
 * list's items are ids in the block behind its igMemoryRef, resolved through the handle table.
 */
#define MAX_NODES  65536u
#define MAX_DEPTH  64u

static uint32_t graph_budget;      /* one walk at a time (a load is single-threaded) */

/* The ids a list *object* holds: its igMemoryRef value is a materialised handle and the block
 * behind it holds the item ids.  Returns the block's bytes and sets `*count`. */
static const uint8_t *list_items(const dw4_scene *s, const dw4_igb *g, dw4_handle list,
                                 uint32_t *count)
{
    const uint8_t *lp = (const uint8_t *)dw4_scene_host(s, list);
    const dw4_igb_class *c;
    uint32_t cl, k, q;

    *count = 0;
    if (!lp)
        return NULL;
    cl = rd32(lp);
    if (cl >= g->nclasses)
        return NULL;
    c = &g->classes[cl];
    q = 8;
    for (k = 0; k < c->ntriples; k++) {
        const dw4_igb_triple *t = &c->triples[k];
        if (t->type == 4) {
            q += 4 + rd32(lp + q);
            continue;
        }
        if (t->type == DW4_IGB_TY_MEMREF) {
            dw4_handle bh = field_ref(lp, q);
            const dw4_scene_ent *e = ent_of_handle(s, bh);
            if (!e || e->kind != 1)
                return NULL;
            *count = e->size / 4;
            return (const uint8_t *)dw4_scene_host(s, bh);
        }
        q += (t->size + 3u) & ~3u;
    }
    return NULL;
}

/* The bytes behind a *value* list object (igVec3fList/igQuaternionfList/igLongList), via its
 * `igMemoryRef`.  Sets `*bytes` to the block length. */
static const uint8_t *list_block(const dw4_scene *s, const dw4_igb *g, dw4_handle list,
                                 uint32_t *bytes)
{
    const uint8_t *lp = (const uint8_t *)dw4_scene_host(s, list);
    const dw4_igb_class *c;
    uint32_t cl, k, q;

    *bytes = 0;
    if (!lp)
        return NULL;
    cl = rd32(lp);
    if (cl >= g->nclasses)
        return NULL;
    c = &g->classes[cl];
    q = 8;
    for (k = 0; k < c->ntriples; k++) {
        const dw4_igb_triple *t = &c->triples[k];
        if (t->type == 4) {
            q += 4 + rd32(lp + q);
            continue;
        }
        if (t->type == DW4_IGB_TY_MEMREF) {
            dw4_handle bh = field_ref(lp, q);
            const dw4_scene_ent *e = ent_of_handle(s, bh);
            if (!e || e->kind != 1)
                return NULL;
            *bytes = e->size;
            return (const uint8_t *)dw4_scene_host(s, bh);
        }
        q += (t->size + 3u) & ~3u;
    }
    return NULL;
}

/* Read an `igTransformSequence1_5`'s keyframe lists.  The lists are found by their *class*, not
 * their field name, and the two `igVec3fList`s are told apart by their **descriptor slot**: a node
 * may carry only the scale (a pop-in/out with no translation at all), and reading whichever vec3
 * list came first as the translation left those nodes with no scale -- so their geometry never
 * collapsed and the opening's staggered reveal never happened.  `igQuaternionfList` is the rotation
 * and `igLongList` the times. */
static dw4_scene_seq read_seq(const dw4_scene *s, const dw4_igb *g, dw4_handle seq)
{
    dw4_scene_seq out;
    const uint8_t *rec = (const uint8_t *)dw4_scene_host(s, seq);
    const dw4_igb_class *c;
    uint32_t cl, k, q;

    memset(&out, 0, sizeof(out));
    if (!rec)
        return out;
    cl = rd32(rec);
    if (cl >= g->nclasses)
        return out;
    c = &g->classes[cl];
    q = 8;
    out.interpolation_method = rec_value(g, rec, 16, NULL);
    for (k = 0; k < c->ntriples; k++) {
        const dw4_igb_triple *t = &c->triples[k];
        if (t->type == 4) {
            q += 4 + rd32(rec + q);
            continue;
        }
        if (t->type == DW4_IGB_TY_OBJECTREF) {
            dw4_handle lh = field_ref(rec, q);
            uint32_t bytes = 0;
            const uint8_t *b = lh.off ? list_block(s, g, lh, &bytes) : NULL;
            if (b) {
                if (class_is(s, g, lh, "igVec3fList")) {
                    /* The slot decides, not the order seen: slot 2 is `_interpolationDataTranslation`,
                     * slot 4 `_interpolationDataScale` (the class' descriptor order -- the reflection
                     * names the fields in the same order, at 60 then 68).  A node may carry only the
                     * scale -- the trace groups do -- and calling that list the translation left them
                     * with no scale at all, so nothing ever collapsed and the opening's staged reveal
                     * never happened. */
                    if (t->ordinal == SEQ_TRANS_ORD) {
                        out.trans = b;
                        out.ntrans = bytes / 12u;
                        out.trans_ord = t->ordinal;
                    } else {
                        out.scale = b;
                        out.nscale = bytes / 12u;
                        out.scale_ord = t->ordinal;
                    }
                } else if (class_is(s, g, lh, "igQuaternionfList")) {
                    out.rot = b;
                    out.nrot = bytes / 16u;
                } else if (class_is(s, g, lh, "igLongList")) {
                    out.times = b;
                    out.ntimes = bytes / 8u;
                }
                if (getenv("DW4_FL_SEQ")) {   /* probe: every list in the sequence, by class */
                    const uint8_t *lr = (const uint8_t *)dw4_scene_host(s, lh);
                    uint32_t lcl = lr ? rd32(lr) : 0xFFFFFFFFu;
                    uint32_t z;
                    printf("    list ord=%-3u %-22s bytes=%-4u first=", t->ordinal,
                           (lcl < g->nclasses && g->classes[lcl].name) ? g->classes[lcl].name : "?", bytes);
                    for (z = 0; z < 4 && z * 4 < bytes; z++)
                        printf(" %g", ((const float *)b)[z]);
                    printf("\n");
                }
            }
        }
        q += (t->size + 3u) & ~3u;
    }
    return out;
}

/* QS packs quantize each component as base + ushort * range/65535.
 * Time keys are sign-magnitude nanoseconds in 2^23 units (retail getter
 * 0x001bf790); duration is not a quantization multiplier. */
static dw4_scene_seq read_compressed_seq(const dw4_scene *s, const dw4_igb *g, dw4_handle h)
{
    dw4_scene_seq out = {0};
    const uint8_t *r = dw4_scene_host(s, h), *data[3] = {0};
    uint32_t sizes[3] = {0}, count[3] = {0};
    uint64_t duration = 0;
    float base[2], step[2];
    for (unsigned i = 0; i < 3; ++i) {
        dw4_handle list = refh(rec_value(g, r, i+2, NULL));
        if (list.off) data[i] = list_block(s, g, list, &sizes[i]);
        if (data[i]) {
            const uint8_t *lr = dw4_scene_host(s, list);
            unsigned stride = i == 0 ? 3 : i == 1 ? 4 : 1;
            unsigned elements = rec_value(g, lr, 2, NULL);
            if (elements > sizes[i]/2 || elements % stride) return out;
            count[i] = elements / stride;
        }
    }
    uint32_t off = rec_off(g, r, 9);
    if (off) memcpy(&duration, r+off, 8);
    if (!count[2] || !duration || duration>INT64_MAX || (count[0] && count[0] != count[2]) ||
        (count[1] && count[1] != count[2])) return out;
    for (unsigned i = 0; i < 2; ++i) {
        uint32_t b = rec_value(g,r,5+i*2,NULL), t = rec_value(g,r,6+i*2,NULL);
        memcpy(&base[i], &b, 4); memcpy(&step[i], &t, 4);
    }
    size_t bytes = count[2]*8u + count[0]*12u + count[1]*16u;
    uint8_t *decoded = malloc(bytes);
    if (!decoded) return out;
    out.owned = decoded;
    out.duration_ns=(int64_t)duration;out.play_mode=rec_value(g,r,10,NULL);
    out.times = decoded; out.ntimes = count[2];
    out.trans = decoded + count[2]*8u; out.ntrans = count[0];
    out.rot = decoded + count[2]*8u + count[0]*12u; out.nrot = count[1];
    out.interpolation_method = rec_value(g,r,13,NULL);
    for (unsigned i = 0; i < count[2]; ++i) {
        uint16_t v; memcpy(&v,data[2]+i*2,2);
        int64_t ns = (int64_t)(v & 0x7fffu) * 8388608LL;
        ((int64_t *)decoded)[i] = (v & 0x8000u) ? -ns : ns;
    }
    for (unsigned j = 0; j < 2; ++j) {
        float *p = (float *)(j ? out.rot : out.trans);
        for (unsigned i = 0; i < count[j] * (j ? 4u : 3u); ++i) {
            uint16_t v; memcpy(&v,data[j]+i*2,2);
            p[i] = base[j] + v * step[j];
        }
    }
    return out;
}

static void graph_add(dw4_scene *s, const dw4_igb *g, uint32_t id, uint32_t parent,
                      uint32_t scene, uint32_t depth, int actor_skins)
{
    dw4_handle h = dw4_scene_handle(s, id);
    const dw4_scene_ent *he = ent_of_handle(s, h);
    const uint8_t *rec = (const uint8_t *)dw4_scene_host(s, h);
    const dw4_igb_class *c;
    dw4_scene_node n;
    uint32_t cl, k, q, idx;

    if (!rec || !he || depth > MAX_DEPTH || s->nnode >= MAX_NODES - 1 || graph_budget-- == 0)
        return;
    cl = rd32(rec);
    if (cl >= g->nclasses)
        return;
    c = &g->classes[cl];
    memset(&n, 0, sizeof(n));
    n.id = id;
    n.mesh = 0xFFFFFFFFu;
    n.time_scale = 1.0f;                /* beModelCtrlNode2._timeScale defaults to 1.0 */
    /* the class directory lives in the container, which is closed when loading ends -- so the
     * name is owned here (the nodes outlive the parse) */
    if (c->name) {
        char *copy = (char *)malloc(strlen(c->name) + 1);
        if (copy)
            strcpy(copy, c->name);
        n.class_name = copy;
    }
    n.parent = parent;
    n.scene = scene;
    n.depth = depth;
    idx = s->nnode++;
    q = 8;
    for (k = 0; k < c->ntriples; k++) {
        const dw4_igb_triple *t = &c->triples[k];
        if (t->type == 4) {
            uint32_t len = rd32(rec + q);
            if (len && !n.name)
                n.name = (const char *)(rec + q + 4);
            q += 4 + len;
            continue;
        }
        if (t->type == 1 && t->ordinal == XFORM_TARGET_ORD && c->name &&
            strcmp(c->name, "igTransform") == 0 && q + 4 <= he->size) {
            n.xform_target = rd32(rec + q);                 /* igTransform._target */
        } else if (t->type == 40 && q + 64 <= he->size) {   /* igMatrix44f */
            memcpy(n.m, rec + q, 64);
            n.has_matrix = 1;
        } else if (t->type == DW4_IGB_TY_OBJECTREF) {
            dw4_handle th = field_ref(rec, q);
            if (th.off) {
                if (class_is(s, g, th, "igNodeList")) {
                    uint32_t cnt = 0, j;
                    const uint8_t *it = list_items(s, g, th, &cnt);
                    if (it)
                        for (j = 0; j < cnt; j++)
                            graph_add(s, g, rd32(it + 4 * j), idx, scene, depth + 1, actor_skins);
                } else if (class_is(s, g, th, "igGeometry") && !n.geometry.off) {
                    n.geometry = th;
                } else if (!strcmp(c->name,"igSwitch") && class_is(s,g,th,"igBitMask")) {
                    const uint8_t *mask=dw4_scene_host(s,th);
                    n.switch_bits=rec_value(g,mask,5,NULL);
                    n.switch_mask=refh(rec_value(g,mask,4,NULL));
                } else if (!strcmp(c->name,"igLod") && class_is(s,g,th,"igFloatList")) {
                    uint32_t count=0;const uint8_t *ranges=list_items(s,g,th,&count);
                    if(ranges && !n.lod_ranges.off) {
                        n.lod_ranges.off=(uint32_t)(ranges-s->arena);n.lod_count=count;
                    }
                } else if (class_is(s, g, th, "igCompressedAnimationSequenceQS") && !n.has_seq) {
                    dw4_scene_seq sq = read_compressed_seq(s, g, th);
                    if (sq.ntimes) n.seq = sq, n.has_seq = 1;
                } else if (class_is(s, g, th, "igTransformSequence1_5") && !n.has_seq) {
                    /* a placeholder `_m` means the real transform is the sequence */
                    dw4_scene_seq sq = read_seq(s, g, th);
                    if (sq.ntimes)
                        n.seq = sq, n.has_seq = 1;
                }
            }
        }
        q += (t->size + 3u) & ~3u;
    }
    /* Preview-only: the actor's appearance owns a skin graph, outside its node list.
     * These vertices are the bind pose; animation/skinning is a separate runtime step. */
    if (actor_skins && !strcmp(c->name, "igActor")) {
        dw4_handle appearance = refh(rec_value(g, rec, 11, NULL));
        const uint8_t *ar = dw4_scene_host(s, appearance);
        if (ar && class_is(s, g, appearance, "igAppearance")) {
            dw4_handle skin = refh(rec_value(g, ar, 3, NULL));
            const uint8_t *sr = dw4_scene_host(s, skin);
            if (sr && class_is(s, g, skin, "igSkin")) {
                dw4_handle graph = refh(rec_value(g, sr, 3, NULL));
                const dw4_scene_ent *ge = ent_of_handle(s, graph);
                if (ge)
                    graph_add(s, g, ge->id, idx, scene, depth + 1, actor_skins);
            }
        }
    }
    s->node[idx] = n;                        /* written last: the children went above it */
}

int dw4_scene_switch_set(dw4_scene *s,uint32_t node,int child,int visible)
{
    if(!s || node>=s->nnode || child < -1) return -1;
    dw4_scene_node *n=&s->node[node];
    const uint32_t *initial=dw4_scene_host(s,n->switch_mask);
    const dw4_scene_ent *entry=ent_of_handle(s,n->switch_mask);
    unsigned bytes=((n->switch_bits+31)/32)*4;
    if(!initial || !entry || bytes>entry->size || (child>=0 && (unsigned)child>=n->switch_bits)) return -1;
    if(!n->switch_values) {
        n->switch_values=malloc(bytes);if(!n->switch_values) return -1;
        memcpy(n->switch_values,initial,bytes);
    }
    uint32_t *mask=n->switch_values;
    for(uint32_t i=0;i<n->switch_bits;i++) if(child<0 || i==(unsigned)child) {
        uint32_t bit=1u<<(i&31);if(visible) mask[i>>5]|=bit;else mask[i>>5]&=~bit;
    }
    return 0;
}

int dw4_scene_node_visible(const dw4_scene *s,uint32_t node,float distance)
{
    if(!s || node>=s->nnode || !isfinite(distance) || distance<0) return 0;
    while(s->node[node].parent<s->nnode) {
        uint32_t parent=s->node[node].parent,index=0;
        for(uint32_t i=parent+1;i<node;i++) if(s->node[i].parent==parent) index++;
        const dw4_scene_node *n=&s->node[parent];
        if(n->switch_mask.off) {
            const uint32_t *mask=n->switch_values?n->switch_values:dw4_scene_host(s,n->switch_mask);
            if(!mask || index>=n->switch_bits || !(mask[index>>5]&(1u<<(index&31)))) return 0;
        }
        if(n->lod_ranges.off) {
            const float *ranges=dw4_scene_host(s,n->lod_ranges);
            if(!ranges || index>=n->lod_count || distance<ranges[index] ||
                (index+1<n->lod_count && distance>=ranges[index+1])) return 0;
        }
        node=parent;
    }
    return 1;
}

/* Walk an `igGraphPathList`: each `igGraphPath` carries an `igNodeList` of root nodes.  World
 * stages put the scene here; the front-end's title scenes put their *cameras* here. */
static void add_path_nodes(dw4_scene *s, const dw4_igb *g, dw4_handle paths, uint32_t scene, int actor_skins)
{
    uint32_t cnt = 0, j;
    const uint8_t *it = list_items(s, g, paths, &cnt);

    for (j = 0; it && j < cnt; j++) {
        dw4_handle ph = dw4_scene_handle(s, rd32(it + 4 * j));
        const uint8_t *pp = (const uint8_t *)dw4_scene_host(s, ph);
        const dw4_igb_class *pc;
        uint32_t pcl, pk, pq;

        if (!pp || !class_is(s, g, ph, "igGraphPath"))
            continue;
        /* a graph path carries its own igNodeList (the path's roots), not a memory ref */
        pcl = rd32(pp);
        if (pcl >= g->nclasses)
            continue;
        pc = &g->classes[pcl];
        pq = 8;
        for (pk = 0; pk < pc->ntriples; pk++) {
            const dw4_igb_triple *pt = &pc->triples[pk];
            if (pt->type == 4) {
                pq += 4 + rd32(pp + pq);
                continue;
            }
            if (pt->type == DW4_IGB_TY_OBJECTREF) {
                dw4_handle nh = field_ref(pp, pq);
                uint32_t cnt2 = 0, m;
                const uint8_t *it2;
                if (nh.off && class_is(s, g, nh, "igNodeList")) {
                    it2 = list_items(s, g, nh, &cnt2);
                    for (m = 0; it2 && m < cnt2; m++)
                        graph_add(s, g, rd32(it2 + 4 * m), 0xFFFFFFFFu, scene, 0, actor_skins);
                }
            }
            pq += (pt->size + 3u) & ~3u;
        }
    }
}

/* The beHitLandModelInfo kinds whose static graphs the collision keeps: floor (1), wall (2) and the special wall kinds 4, 8 and 0x802 (dw4_collision_special_kind). */
static int collision_kind(uint32_t kind){return kind==1 || kind==2 || kind==4 || kind==8 || kind==0x802;}
static void build_graph(dw4_scene *s, const dw4_igb *g, int actor_skins)
{
    uint32_t i;

    s->node = (dw4_scene_node *)calloc(MAX_NODES, sizeof(*s->node));
    if (!s->node)
        return;
    graph_budget = 200000u;
    for (i = 0; i < s->nent; i++) {
        const uint8_t *rec;
        const dw4_igb_class *c;
        dw4_handle paths = { 0 };     /* _sceneGraph when it is an igGraphPathList (world stages) */
        dw4_handle root = { 0 };      /* _sceneGraph in the front-end's attribute-set form */
        dw4_handle cams = { 0 };      /* _cameras -- a graph path list the front-end keeps apart */
        int root_paths = 0;
        const char *name = NULL;
        uint32_t cl, k, q, scene, before;

        if (s->ent[i].kind != 2)
            continue;
        rec = (const uint8_t *)dw4_scene_host(s, s->ent[i].h);
        if (!rec || !class_is(s, g, s->ent[i].h, "igSceneInfo"))
            continue;
        cl = rd32(rec);
        c = &g->classes[cl];
        q = 8;
        for (k = 0; k < c->ntriples; k++) {
            const dw4_igb_triple *t = &c->triples[k];
            if (t->type == 4) {
                uint32_t len = rd32(rec + q);
                if (len && !name)
                    name = (const char *)(rec + q + 4);
                q += 4 + len;
                continue;
            }
            if (t->type == DW4_IGB_TY_OBJECTREF) {
                dw4_handle th = field_ref(rec, q);
                /* igSceneInfo._sceneGraph is ordinal 5.  Its root can be any igNode
                 * subclass, or an igGraphPathList; _cameras is a separate path list. */
                if (th.off && t->ordinal == 5) {
                    if (class_is(s, g, th, "igGraphPathList")) {
                        paths = th; root = th; root_paths = 1;
                    } else {
                        /* _sceneGraph is an igNode reference.  Derived roots include igSwitch
                         * and igLightStateSet (the character-select backdrop); restricting this
                         * to three class names silently replaced those graphs with their cameras. */
                        root = th; root_paths = 0;
                    }
                } else if (th.off && !cams.off && class_is(s, g, th, "igGraphPathList")) {
                    cams = th;       /* the front-end keeps its cameras in a separate path list */
                }
            }
            q += (t->size + 3u) & ~3u;
        }
        if (!root.off)
            continue;
        scene = s->ngraph;
        {
            dw4_scene_graph *gr = (dw4_scene_graph *)realloc(s->graph,
                                                             (s->ngraph + 1) * sizeof(*gr));
            if (!gr)
                return;
            s->graph = gr;
        }
        s->graph[scene].name = name;
        s->graph[scene].node = s->nnode;
        s->graph[scene].nnodes = 0;
        s->ngraph++;
        before = s->nnode;
        if (!root_paths) {
            /* the attribute-set form: `_sceneGraph` is the root node itself */
            const dw4_scene_ent *re = ent_of_handle(s, root);
            if (re)
                graph_add(s, g, re->id, 0xFFFFFFFFu, scene, 0, actor_skins);
            if (cams.off)
                add_path_nodes(s, g, cams, scene, actor_skins);   /* the scene's own cameras */
        } else {
            add_path_nodes(s, g, paths, scene, actor_skins);
        }
        s->graph[scene].nnodes = s->nnode - before;
    }
    /* Shadow receivers are registered outside igSceneInfo's visible graph.
     * Actor-aware loads retain these explicit graphs for the native projective
     * pass; ordinary world/analysis loads keep their existing node coverage. */
    if(actor_skins) for(i=0;i<s->nent;i++) {
        const uint8_t *rec=dw4_scene_host(s,s->ent[i].h);
        if(s->ent[i].kind!=2 || !rec || !class_is(s,g,s->ent[i].h,"beShadow01Info")) continue;
        dw4_handle receiver=refh(rec_value(g,rec,7,NULL));
        const dw4_scene_ent *entry=ent_of_handle(s,receiver);
        if(!entry) continue;
        unsigned j;
        for(j=0;j<s->nnode;j++) if(s->node[j].id==entry->id) break;
        if(j==s->nnode) graph_add(s,g,entry->id,UINT32_MAX,UINT32_MAX,0,actor_skins);
    }

    /* Gameplay preparation needs the info-owned static collision graphs, whose
     * debug switch masks are independent of physical floor/wall admission. */
    if(actor_skins&2)for(i=0;i<s->nent;i++) {
        const uint8_t *rec=dw4_scene_host(s,s->ent[i].h);
        if(s->ent[i].kind!=2 || !rec || !class_is(s,g,s->ent[i].h,"beHitLandModelInfo"))continue;
        uint32_t kind=rec_value(g,rec,10,NULL);if(!collision_kind(kind))continue;
        dw4_handle graph=refh(rec_value(g,rec,7,NULL));
        const dw4_scene_ent *entry=ent_of_handle(s,graph);if(!entry)continue;
        unsigned node;
        for(node=0;node<s->nnode;node++)if(s->node[node].id==entry->id && s->node[node].parent==UINT32_MAX)break;
        if(node==s->nnode)graph_add(s,g,entry->id,UINT32_MAX,UINT32_MAX,0,actor_skins);
        if(node==s->nnode)continue;
        dw4_scene_collision *rows=realloc(s->collision,(s->ncollision+1)*sizeof *rows);
        if(!rows)continue;
        s->collision=rows;rows[s->ncollision++]=(dw4_scene_collision){i,kind,node};
    }
    /* The dynamic prop walls (kind 0x402) come after the static rows, so the static indices that the door bookkeeping addresses never move. Retail's
     * wall walk (FUN_00388640) visits only the ordinal-8 _checkSwitch of such an info: one beCopyTransform per ram slot of the model of the same name,
     * each holding a small proxy geometry. The ordinal-7 graph also wraps the prop's visual model, which a wall query never touches. */
    if(actor_skins&2)for(i=0;i<s->nent;i++) {
        const uint8_t *rec=dw4_scene_host(s,s->ent[i].h);
        const char *name=NULL;
        if(s->ent[i].kind!=2 || !rec || !class_is(s,g,s->ent[i].h,"beHitLandModelInfo") || rec_value(g,rec,10,NULL)!=DW4_HITLAND_DYNAMIC_WALL)continue;
        rec_value(g,rec,2,&name);
        dw4_handle check=refh(rec_value(g,rec,8,NULL));
        const dw4_scene_ent *entry=ent_of_handle(s,check);
        if(!name || !entry || !class_is(s,g,check,"igSwitch"))continue;
        unsigned before=s->nnode,node,nslot=0;
        graph_add(s,g,entry->id,UINT32_MAX,UINT32_MAX,0,actor_skins);
        if(s->nnode==before || s->node[before].id!=entry->id)continue;
        node=before;
        for(unsigned c=node+1;c<s->nnode && s->node[c].depth>s->node[node].depth;c++)nslot+=s->node[c].parent==node;
        float *bound=malloc((nslot?nslot:1)*6*sizeof *bound);
        dw4_scene_dynamic *rows=realloc(s->dynamic,(s->ndynamic+1)*sizeof *rows);
        if(!bound || !rows){free(bound);if(rows)s->dynamic=rows;continue;}
        s->dynamic=rows;
        unsigned slot=0;
        for(unsigned c=node+1;c<s->nnode && s->node[c].depth>s->node[node].depth;c++) {
            if(s->node[c].parent!=node)continue;
            float *b=bound+6*slot++;
            for(unsigned k=0;k<6;k++)b[k]=k<3?-INFINITY:INFINITY;
            /* the proxy's bound is its first child's igAABox (igGeometry ordinal 3, min/max at ordinals 2 and 3) */
            for(unsigned q=c+1;q<s->nnode && s->node[q].depth>s->node[c].depth;q++) {
                if(s->node[q].parent!=c)continue;
                const uint8_t *geometry=dw4_scene_host(s,dw4_scene_handle(s,s->node[q].id));
                dw4_handle box=geometry?refh(rec_value(g,geometry,3,NULL)):(dw4_handle){0};
                const uint8_t *bx=dw4_scene_host(s,box);
                if(bx && class_is(s,g,box,"igAABox")) {
                    uint32_t lo=rec_off(g,bx,2),hi=rec_off(g,bx,3);
                    if(lo && hi && lo+12<=ent_of_handle(s,box)->size && hi+12<=ent_of_handle(s,box)->size) {
                        for(unsigned k=0;k<3;k++) {
                            float a,z;uint32_t wa=rd32(bx+lo+4*k),wz=rd32(bx+hi+4*k);memcpy(&a,&wa,4);memcpy(&z,&wz,4);
                            if(isfinite(a) && isfinite(z)){b[k]=a;b[3+k]=z;}
                        }
                    }
                }
                break;
            }
        }
        rows[s->ndynamic++]=(dw4_scene_dynamic){i,node,nslot,name,bound};
    }
}

int dw4_scene_load_file(dw4_scene *s, const dw4_igfile *f)
{
    return dw4_scene_load(s, dw4_igfile_data(f), dw4_igfile_size(f));
}

static int scene_load(dw4_scene *s, const uint8_t *blob, size_t len, int actor_skins)
{
    dw4_igb g;
    uint32_t i, off;
    size_t total = 0;

    memset(s, 0, sizeof(*s));
    if (dw4_igb_open(&g, blob, len, 0) != 0)
        return -1;
    if (dw4_igb_refs_open(&g) != 0) {
        dw4_igb_close(&g);
        return -1;
    }
    s->nent = g.table_n;
    s->ent = (dw4_scene_ent *)calloc(g.table_n ? g.table_n : 1, sizeof(*s->ent));
    if (!s->ent) {
        dw4_igb_close(&g);
        return -1;
    }
    /* The loader allocates, so it decides the layout: each id's payload in id order, at
     * DW4_SCENE_ALIGN.  Nothing here depends on the file's own offsets. */
    for (i = 0; i < g.table_n; i++)
        total += (g.id_len[i] + (DW4_SCENE_ALIGN - 1)) & ~(size_t)(DW4_SCENE_ALIGN - 1);
    s->arena = (uint8_t *)calloc(1, DW4_SCENE_BASE + (total ? total : 1));
    if (!s->arena) {
        dw4_igb_close(&g);
        return -1;
    }
    off = DW4_SCENE_BASE;
    for (i = 0; i < g.table_n; i++) {
        uint32_t size = g.id_len[i];
        memcpy(s->arena + off, blob + g.id_off[i], size);
        s->ent[i].id = i;
        s->ent[i].h.off = off;
        s->ent[i].size = size;
        s->ent[i].kind = (uint8_t)g.id_kind[i];
        if (g.id_kind[i] == 1)
            s->nblock++;
        else
            s->nobject++;
        off += (size + (DW4_SCENE_ALIGN - 1)) & ~(DW4_SCENE_ALIGN - 1);
    }
    s->arena_len = off;
    /* The id -> pointer pass, then read the geometry the way the game does: through the handles. */
    materialise(s, &g);
    build_graph(s, &g, actor_skins);
    if(actor_skins&2) {
        unsigned expected=0;
        for(i=0;i<s->nent;i++) {
            const uint8_t *rec=dw4_scene_host(s,s->ent[i].h);
            if(s->ent[i].kind==2 && rec && class_is(s,&g,s->ent[i].h,"beHitLandModelInfo")) {
                uint32_t kind=rec_value(&g,rec,10,NULL);expected+=collision_kind(kind);
            }
        }
        if(expected!=s->ncollision) {
            fprintf(stderr,"scene: incomplete authored static collision graphs\n");
            dw4_igb_close(&g);dw4_scene_close(s);return -1;
        }
    }
    for (i = 0; i < s->nent; i++) {
        const uint8_t *rec;
        if (s->ent[i].kind != 2)
            continue;
        rec = (const uint8_t *)dw4_scene_host(s, s->ent[i].h);
        if (rec && class_is(s, &g, s->ent[i].h, "igGeometryAttr1_5"))
            add_mesh(s, &g, i, rec, NULL);
    }
    add_names(s, &g);
    add_materials(s, &g);
    link_nodes(s, &g);
    compute_light_rot(s);
    dw4_igb_close(&g);
    return 0;
}

int dw4_scene_load(dw4_scene *s, const uint8_t *blob, size_t len)
{
    return scene_load(s, blob, len, 0);
}

int dw4_scene_load_actor_preview(dw4_scene *s, const uint8_t *blob, size_t len)
{
    return scene_load(s, blob, len, 1);
}

int dw4_scene_load_world(dw4_scene *s,const uint8_t *blob,size_t len)
{return scene_load(s,blob,len,3);}

void dw4_scene_close(dw4_scene *s)
{
    free(s->arena);
    free(s->ent);
    free(s->mesh);
    free(s->img);
    if (s->node) {
        uint32_t i;
        for (i = 0; i < s->nnode; i++) {
            free((void *)s->node[i].class_name);
            free(s->node[i].switch_values);
            free(s->node[i].seq.owned);
        }
    }
    free(s->node);
    free(s->graph);
    free(s->collision);
    for (uint32_t i = 0; i < s->ndynamic; i++)
        free(s->dynamic[i].bound);
    free(s->dynamic);
    memset(s, 0, sizeof(*s));
}

int dw4_scene_tris(const dw4_scene *s, const dw4_scene_mesh *g, uint32_t **out, uint32_t *ntris,
                   const char **why)
{
    return dw4_mesh_tris(g->prim_type, g->num_prims, g->num_verts,
                         (const uint8_t *)dw4_scene_host(s, g->lengths), g->num_lengths,
                         out, ntris, why);
}

int dw4_scene_write_obj(const dw4_scene *s, const dw4_scene_mesh *g, FILE *f)
{
    uint32_t *tris = NULL, ntris = 0;
    const char *why = NULL;
    int rc;

    if (dw4_scene_tris(s, g, &tris, &ntris, &why) != 0)
        return -1;
    rc = dw4_mesh_write_obj(f, (const uint8_t *)dw4_scene_host(s, g->positions),
                            (const uint8_t *)dw4_scene_host(s, g->uvs), g->num_verts,
                            tris, ntris);
    free(tris);
    return rc;
}

/* --- the stage's own camera ---------------------------------------------
 *
 * A node carries its local igMatrix44f; its world is the chain composed child x parent (the
 * row-vector convention, translation at words 12..14), and the view is that world's affine
 * inverse.  `dw4_scene_camera()` picks the stage camera and returns the node index so a caller can
 * name what it used. */
static int mat_identity(const float m[16])
{
    int k;
    for (k = 0; k < 16; k++) {
        float want = (k % 5 == 0) ? 1.0f : 0.0f;
        if (fabsf(m[k] - want) > 1e-5f)
            return 0;
    }
    return 1;
}

/* out = a x b, row-major. */
static void mat_mul(const float a[16], const float b[16], float out[16])
{
    int r, c, k;
    for (r = 0; r < 4; r++)
        for (c = 0; c < 4; c++) {
            float acc = 0;
            for (k = 0; k < 4; k++)
                acc += a[4 * r + k] * b[4 * k + c];
            out[4 * r + c] = acc;
        }
}

/* The affine inverse: for R|t it is R^T | -R^T t. */
static void mat_affine_inv(const float m[16], float out[16])
{
    float tx = m[12], ty = m[13], tz = m[14];
    int r, c;
    for (r = 0; r < 3; r++)
        for (c = 0; c < 3; c++)
            out[4 * r + c] = m[4 * c + r];
    for (r = 0; r < 3; r++)
        out[12 + r] = -(out[4 * r] * tx + out[4 * r + 1] * ty + out[4 * r + 2] * tz);
    out[3] = out[7] = out[11] = 0.0f;
    out[15] = 1.0f;
}

static void mat_identity_set(float m[16])
{
    int k;
    for (k = 0; k < 16; k++)
        m[k] = (k % 5 == 0) ? 1.0f : 0.0f;
}

int dw4_scene_node_camera(const dw4_scene *s, uint32_t j, float world[16], float view[16])
{
    float wm[16];

    if (!s || !s->node || j >= s->nnode || !s->node[j].class_name ||
        strcmp(s->node[j].class_name, "igCamera") != 0)
        return -1;
    dw4_scene_node_world(s, j, wm);
    if (world) memcpy(world, wm, sizeof(wm));
    if (view) mat_affine_inv(wm, view);
    return 0;
}

/* Evaluate a sequence's local transform at `ns` (nanoseconds): the translation and the scale
 * interpolated between the bracketing keys, and the rotation quaternion along the shortest arc.
 * Out of range clamps to the first/last key; no times is the identity. */
static int getenv_zero_scale(void)
{
    static int v = -1;
    if (v < 0) {
        const char *e = getenv("DW4_SEQ_UNDRIVEN_ZERO");
        v = e ? atoi(e) : 0;
    }
    return v;
}

static void seq_local(const dw4_scene_seq *q, double ns, float out[16])
{
    const int64_t *T = (const int64_t *)q->times;
    const float *tr = (const float *)q->trans;
    const float *sc = (const float *)q->scale;
    const float *rt = (const float *)q->rot;
    uint32_t i = 0, j = 0, n = q->ntimes, ka, kb;
    float u = 0.0f, tx = 0, ty = 0, tz = 0, sx = 1, sy = 1, sz = 1, qa[4] = {0, 0, 0, 1}, qb[4] = {0, 0, 0, 1};

    mat_identity_set(out);
    if (!T || n == 0)
        return;
    if (n == 1 || ns <= (double)T[0]) {
        i = j = 0;
    } else if (ns >= (double)T[n - 1]) {
        i = j = n - 1;
    } else {
        for (i = 0; i + 1 < n && (double)T[i + 1] <= ns; i++)
            ;
        j = i + 1;
        if(q->rotation_euler){
            /* The explicit camera adapter uses its separately verified
             * degree-XYZ timeline rather than an igTransformSequence1_5. */
            double a=(double)T[i],b=(double)T[j];
            u=b>a?(float)((ns-a)/(b-a)):0;
        }else{
            uint32_t fraction=dw4_sequence_fraction((int64_t)ns,T[i],T[j]);
            memcpy(&u,&fraction,sizeof u);
        }
    }
    if (tr && q->ntrans) {
        ka = i < q->ntrans ? i : q->ntrans - 1;
        kb = j < q->ntrans ? j : q->ntrans - 1;
        tx = tr[3 * ka] + (tr[3 * kb] - tr[3 * ka]) * u;
        ty = tr[3 * ka + 1] + (tr[3 * kb + 1] - tr[3 * ka + 1]) * u;
        tz = tr[3 * ka + 2] + (tr[3 * kb + 2] - tr[3 * ka + 2]) * u;
    }
    if (sc && q->nscale) {
        ka = i < q->nscale ? i : q->nscale - 1;
        kb = j < q->nscale ? j : q->nscale - 1;
        sx = sc[3 * ka] + (sc[3 * kb] - sc[3 * ka]) * u;
        sy = sc[3 * ka + 1] + (sc[3 * kb + 1] - sc[3 * ka + 1]) * u;
        sz = sc[3 * ka + 2] + (sc[3 * kb + 2] - sc[3 * ka + 2]) * u;
    }
    /* Probe (DW4_SEQ_UNDRIVEN_ZERO=1): a node that HAS a sequence but whose sequence drives NO
     * scale key collapses -- `igTransformSequence1_5` keeps one key list per channel and a channel
     * with no list is zero, not identity.  Only nodes WITH a sequence are affected here; nodes
     * with none take their `_m` (identity), which is why the earlier blanket test also collapsed
     * the traces.  =2 also zeroes an undriven translation. */
    if (getenv_zero_scale() && !q->nscale) {
        sx = sy = sz = 0;
        if (getenv_zero_scale() > 1 && !q->ntrans) { tx = ty = tz = 0; }
    }
    if (rt && q->nrot) {
        float d;
        ka = i < q->nrot ? i : q->nrot - 1;
        kb = j < q->nrot ? j : q->nrot - 1;
        memcpy(qa, rt + 4 * ka, sizeof(qa));
        memcpy(qb, rt + 4 * kb, sizeof(qb));
        if (q->rotation_euler) {
            float m[16], axis[16], product[16];
            for (int z = 0; z < 3; z++) qa[z] += (qb[z]-qa[z])*u;
            mat_identity_set(m);
            for (int z = 0; z < 3; z++) {
                int a = (z+1)%3, b = (z+2)%3;
                float angle = qa[z]*0.017453292519943295f;
                mat_identity_set(axis);
                axis[a*4+a] = axis[b*4+b] = cosf(angle);
                axis[a*4+b] = sinf(angle);
                axis[b*4+a] = -sinf(angle);
                mat_mul(m, axis, product);
                memcpy(m, product, sizeof m);
            }
            memcpy(out, m, sizeof m);
            for (int z = 0; z < 3; z++) {
                out[z] *= sx; out[4+z] *= sy; out[8+z] *= sz;
            }
            out[12]=tx; out[13]=ty; out[14]=tz;
            return;
        }
        d = qa[0] * qb[0] + qa[1] * qb[1] + qa[2] * qb[2] + qa[3] * qb[3];
        if (d < 0.0f) {          /* shortest arc: negate one side */
            int z;
            for (z = 0; z < 4; z++)
                qb[z] = -qb[z];
        }
        for (int z = 0; z < 4; z++)
            qa[z] = qa[z] + (qb[z] - qa[z]) * u;
        {   /* the blend of two unit quaternions is shorter than one; a rotation matrix needs a unit one */
            float len = sqrtf(qa[0] * qa[0] + qa[1] * qa[1] + qa[2] * qa[2] + qa[3] * qa[3]);

            if (len > 1e-6f)
                for (int z = 0; z < 4; z++)
                    qa[z] /= len;
        }
    }
    {   /* row-major: the rotation rows, scaled by the scale (row-vector convention), then T */
        float x = qa[0], y = qa[1], z = qa[2], w = qa[3];
        float r[9];
        r[0] = 1 - 2 * (y * y + z * z); r[1] = 2 * (x * y - z * w);     r[2] = 2 * (x * z + y * w);
        r[3] = 2 * (x * y + z * w);     r[4] = 1 - 2 * (x * x + z * z); r[5] = 2 * (y * z - x * w);
        r[6] = 2 * (x * z - y * w);     r[7] = 2 * (y * z + x * w);     r[8] = 1 - 2 * (x * x + y * y);
        out[0] = r[0] * sx; out[1] = r[1] * sx; out[2] = r[2] * sx;
        out[4] = r[3] * sy; out[5] = r[4] * sy; out[6] = r[5] * sy;
        out[8] = r[6] * sz; out[9] = r[7] * sz; out[10] = r[8] * sz;
    }
    out[12] = tx; out[13] = ty; out[14] = tz; out[15] = 1.0f;
}

int dw4_scene_node_local(const dw4_scene *s, uint32_t j, float out[16])
{
    const dw4_scene_node *n;

    if (!s || !s->node || j >= s->nnode)
        return 0;
    n = &s->node[j];
    if (n->has_seq) {
        seq_local(&n->seq, n->driven ? n->tnode : s->time_ns, out);
        return 1;
    }
    if (n->has_matrix) {
        memcpy(out, n->m, sizeof(n->m));
        return 1;
    }
    return 0;
}

void dw4_scene_set_time(dw4_scene *s, double ns)
{
    uint32_t i;

    if (!s)
        return;
    s->time_ns = ns;
    /* the analysis timeline takes the nodes back from any controller drive */
    for (i = 0; s->node && i < s->nnode; i++)
        s->node[i].driven = 0;
}

void dw4_scene_node_drive(dw4_scene *s, uint32_t node, float time_scale, long long time_bias)
{
    if (!s || !s->node || node >= s->nnode)
        return;
    s->node[node].time_scale = time_scale;
    s->node[node].time_bias = time_bias;
    /* The effective node time follows at once (the same rule as dw4_scene_set_engine_time), so a driven copy of a graph does not
     * keep a stale value from the original it was copied from. */
    if (s->node[node].has_seq) {
        long long e = s->engine_time >> 18;
        s->node[node].tnode = (double)((((long long)(s->node[node].time_scale * (double)e)) << 18) + s->node[node].time_bias);
        s->node[node].driven = 1;
    }
}
int64_t dw4_scene_node_loop_time(const dw4_scene *s,uint32_t node,int64_t clock)
{
    if(!s || node>=s->nnode)return 0;
    const dw4_scene_seq *q=&s->node[node].seq;
    if(q->duration_ns>0 && q->ntimes && (q->play_mode==0 || q->play_mode==3)) {
        int64_t first=((const int64_t *)q->times)[0];
        /* 1bf7d0 wraps strictly after first+duration, retaining the exact end
         * sample. The last compressed key is not the authored duration. */
        clock=dw4_sequence_loop_clock(clock,first,q->duration_ns);
    }
    return clock;
}

void dw4_scene_set_engine_time(dw4_scene *s, long long engine_ns)
{
    uint32_t i;
    long long e;

    if (!s)
        return;
    s->engine_time = engine_ns;
    if (!s->node)
        return;
    e = engine_ns >> 18;                 /* the `>>18 ... <<18` pair evaluates _timeScale at a
                                          * 2^18 ns rounding granularity, not a rescale */
    for (i = 0; i < s->nnode; i++) {
        dw4_scene_node *n = &s->node[i];
        if (!n->has_seq)
            continue;
        n->tnode = (double)((((long long)(n->time_scale * (double)e)) << 18) + n->time_bias);
        n->driven = 1;
    }
}

int dw4_scene_node_uv_offset(const dw4_scene *s, uint32_t node, float *du, float *dv)
{
    uint32_t guard = 0;

    if (du)
        *du = 0.0f;
    if (dv)
        *dv = 0.0f;
    if (!s || !s->node || node >= s->nnode)
        return 0;
    while (node < s->nnode && guard++ < 64u) {
        if (s->node[node].xform_target) {
            float lm[16];

            if (!dw4_scene_node_local(s, node, lm))
                return 0;
            if (du)
                *du = lm[12];
            if (dv)
                *dv = lm[13];
            return 1;
        }
        if (s->node[node].parent == 0xFFFFFFFFu)
            break;
        node = s->node[node].parent;
    }
    return 0;
}

/* Any node's world: its local matrix composed down the parent chain, root first. */
int dw4_scene_node_world(const dw4_scene *s, uint32_t j, float world[16])
{
    float wm[16], t[16], lm[16];
    uint32_t chain[64], nc = 0, k;

    if (!s || !s->node || j >= s->nnode)
        return -1;
    for (k = j; k != 0xFFFFFFFFu && nc < 64; k = s->node[k].parent)
        chain[nc++] = k;
    mat_identity_set(wm);
    while (nc--) {                           /* root first: world = local x parent */
        if (s->node[chain[nc]].xform_target)
            continue;                        /* a UV-offset transform, not a position */
        if (!dw4_scene_node_local(s, chain[nc], lm))
            continue;
        mat_mul(lm, wm, t);
        memcpy(wm, t, sizeof(wm));
    }
    if (world) memcpy(world, wm, sizeof(wm));
    return 0;
}

int dw4_scene_camera(const dw4_scene *s, const char *name, float world[16], float view[16])
{
    uint32_t j;
    int first = -1;

    if (!s || !s->node)
        return -1;
    for (j = 0; j < s->nnode; j++) {
        const dw4_scene_node *n = &s->node[j];
        float wm[16];

        if (!n->class_name || strcmp(n->class_name, "igCamera") != 0)
            continue;
        if (name && (!n->name || strcmp(n->name, name) != 0))
            continue;
        if (first < 0)
            first = (int)j;
        dw4_scene_node_camera(s, j, wm, NULL);
        if (!name && mat_identity(wm))
            continue;                        /* a local-only camera is not the stage camera */
        if (world) memcpy(world, wm, sizeof(wm));
        if (view) mat_affine_inv(wm, view);
        return (int)j;
    }
    if (first >= 0) {                        /* no transformed camera: use the first one */
        dw4_scene_node_camera(s, (uint32_t)first, world, view);
    }
    return first;
}

float dw4_scene_camera_aspect(int width, int height)
{
    /* The measured projection has m[0]/m[5] = 448/640 = 0.7; the renderer builds
     * its scale from the vertical fov, so the horizontal multiplier is 0.7 * width / height. */
    if (width <= 0 || height <= 0)
        return 0.7f;
    return 0.7f * (float)width / (float)height;
}
