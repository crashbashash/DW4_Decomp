/* The arena contract (docs/arena-object-model.md, P0): handle validity, alignment, exhaustion, reuse, the two regions, the class
 * registry with inherited slots, and igObject reference counting with the engine's destructor order. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "dw4/arena.h"
#include "dw4/reflected.h"

static int bad;
#define CHECK(cond) do { if (!(cond)) { printf("FAIL line %d: %s\n", __LINE__, #cond); bad++; } } while (0)

static int destruct_log[8], destruct_n;
static void dtor_a(dw4_arena *a, dw4_handle h) { (void)a; (void)h; destruct_log[destruct_n++] = 8; }
static void dtor_b(dw4_arena *a, dw4_handle h) { (void)a; (void)h; destruct_log[destruct_n++] = 10; }
static void dtor_c(dw4_arena *a, dw4_handle h) { (void)a; (void)h; destruct_log[destruct_n++] = 0; }
static void other(void) {}

int main(void)
{
    char err[128];
    dw4_arena *a = dw4_arena_open(64 * 1024, err, sizeof err);
    dw4_handle h1, h2, h3, none = {0};
    uint8_t *p;
    int i;

    CHECK(a != NULL);
    CHECK(dw4_arena_open(100, err, sizeof err) == NULL && err[0]);                 /* too small */

    /* NULL, out-of-range and misaligned handles are refused */
    CHECK(dw4_arena_at(a, none, 4) == NULL && dw4_arena_status_last(a) == DW4_ARENA_BAD_HANDLE);
    {
        dw4_handle far = {0x7fffffffu}, odd = {DW4_ARENA_BASE + 17u};
        CHECK(dw4_arena_at(a, far, 4) == NULL);
        CHECK(dw4_arena_at(a, odd, 4) == NULL);
    }

    /* alloc: 16-byte aligned, never NULL, zero-filled, distinct, handle >= the base */
    h1 = dw4_arena_alloc(a, DW4_REGION_PERSISTENT, 40);
    h2 = dw4_arena_alloc(a, DW4_REGION_PERSISTENT, 40);
    CHECK(h1.off && h2.off && h1.off != h2.off);
    CHECK(h1.off >= DW4_ARENA_BASE && (h1.off % DW4_ARENA_ALIGN) == 0 && (h2.off % DW4_ARENA_ALIGN) == 0);
    p = (uint8_t *)dw4_arena_at(a, h1, 40);
    CHECK(p != NULL);
    for (i = 0; p && i < 40; i++) CHECK(p[i] == 0);
    CHECK(dw4_arena_at(a, h1, 4096) == NULL && dw4_arena_status_last(a) == DW4_ARENA_TOO_SMALL);   /* larger than the block */
    CHECK(dw4_arena_alloc(a, DW4_REGION_PERSISTENT, 0).off == 0 && dw4_arena_status_last(a) == DW4_ARENA_BAD_SIZE);

    /* a freed block is not live; a second free is refused; the exact-size block is reused (and zeroed) */
    if (p) memset(p, 0xaa, 40);
    CHECK(dw4_arena_free(a, h1) == 0);
    CHECK(dw4_arena_at(a, h1, 4) == NULL && dw4_arena_status_last(a) == DW4_ARENA_NOT_LIVE);
    CHECK(dw4_arena_free(a, h1) == -1 && dw4_arena_status_last(a) == DW4_ARENA_NOT_LIVE);
    h3 = dw4_arena_alloc(a, DW4_REGION_PERSISTENT, 33);          /* rounds to the same 48-byte class */
    CHECK(h3.off == h1.off);
    p = (uint8_t *)dw4_arena_at(a, h3, 48);
    for (i = 0; p && i < 48; i++) CHECK(p[i] == 0);

    /* exhaustion is explicit: a NULL handle and a status, and nothing is corrupted */
    {
        uint32_t n = 0;
        dw4_handle h;
        while ((h = dw4_arena_alloc(a, DW4_REGION_PERSISTENT, 1024)).off) n++;
        CHECK(n > 10 && dw4_arena_status_last(a) == DW4_ARENA_EXHAUSTED);
        CHECK(dw4_arena_at(a, h2, 40) != NULL);
    }
    dw4_arena_close(a);

    /* regions: the stage region is released as a whole and reports what is still live */
    a = dw4_arena_open(64 * 1024, err, sizeof err);
    {
        dw4_handle pers = dw4_arena_alloc(a, DW4_REGION_PERSISTENT, 64);
        dw4_handle s1 = dw4_arena_alloc(a, DW4_REGION_STAGE, 64);
        dw4_handle s2 = dw4_arena_alloc(a, DW4_REGION_STAGE, 128);
        CHECK(pers.off && s1.off && s2.off && s1.off > pers.off);
        CHECK(dw4_arena_live(a, DW4_REGION_STAGE) == 2 && dw4_arena_live(a, DW4_REGION_PERSISTENT) == 1);
        CHECK(dw4_arena_free(a, s1) == 0 && dw4_arena_live(a, DW4_REGION_STAGE) == 1);
        CHECK(dw4_arena_stage_reset(a) == 1);                    /* s2 leaked */
        CHECK(dw4_arena_at(a, s2, 4) == NULL && dw4_arena_at(a, s1, 4) == NULL);   /* stale stage handles never validate */
        CHECK(dw4_arena_at(a, pers, 64) != NULL);                /* the persistent region is untouched */
        CHECK(dw4_arena_live(a, DW4_REGION_STAGE) == 0 && dw4_arena_stage_reset(a) == 0);
        CHECK(dw4_arena_alloc(a, DW4_REGION_STAGE, 64).off != 0);   /* the region is usable again */
    }

    /* the class registry: inheritance, inherited slots, class_is, the generated schema */
    CHECK(dw4_class_register(a, 0x600000, "Base", 0, 16) == 0);
    CHECK(dw4_class_register(a, 0x600010, "Derived", 0x600000, 32) == 0);
    CHECK(dw4_class_register(a, 0x600010, "Dup", 0, 32) == -1);
    CHECK(dw4_class_register(a, 0, "Zero", 0, 8) == -1);
    CHECK(dw4_class_set_slot(a, 0x600000, DW4_SLOT_DESTRUCT_A, (dw4_slot_fn)dtor_a) == 0);
    CHECK(dw4_class_set_slot(a, 0x600010, DW4_SLOT_DESTRUCT_B, (dw4_slot_fn)dtor_b) == 0);
    CHECK(dw4_class_set_slot(a, 0x600010, DW4_SLOT_DESTRUCT_C, (dw4_slot_fn)dtor_c) == 0);
    CHECK(dw4_class_slot(a, 0x600010, DW4_SLOT_DESTRUCT_A) == (dw4_slot_fn)dtor_a);       /* inherited */
    CHECK(dw4_class_slot(a, 0x600000, DW4_SLOT_DESTRUCT_B) == NULL);
    CHECK(dw4_class_set_slot(a, 0x699999, 3, other) == -1);                              /* unknown class */
    CHECK(dw4_class_is(a, 0x600010, 0x600000) == 1 && dw4_class_is(a, 0x600000, 0x600010) == 0 && dw4_class_is(a, 0x600010, 0x600010) == 1);
    CHECK(dw4_class_is(a, 0x123, 0x600000) == 0 && dw4_class_name(a, 0x123) == NULL);
    CHECK(strcmp(dw4_class_name(a, 0x600010), "Derived") == 0 && dw4_class_size(a, 0x600010) == 32);
    {
        int n = dw4_class_register_schema(a);
        CHECK(n > 100);
        CHECK(dw4_class_name(a, 0x53b740) != NULL && strcmp(dw4_class_name(a, 0x53b740), "ParticleArray") == 0);
        CHECK(dw4_class_size(a, 0x53b740) == 0x80);
    }

    /* objects: header stamped like igObject_InitHeader, class vtable at +0, counted references, destructor order */
    {
        dw4_handle o = dw4_arena_object_new(a, DW4_REGION_PERSISTENT, 0x600010);
        igObject *g = DW4_ARENA_OBJ(a, igObject, o);
        CHECK(o.off && g != NULL);
        CHECK(g && g->_vtable == 0x600010 && g->_refCount == 1u);
        CHECK(dw4_arena_object_refcount(a, o) == 1 && dw4_arena_object_vtable(a, o) == 0x600010);
        CHECK(dw4_arena_object_is(a, o, 0x600000) == 1 && dw4_arena_object_is(a, o, 0x53b740) == 0);
        CHECK(dw4_arena_object_addref(a, o) == 2 && dw4_arena_object_release(a, o) == 1);
        destruct_n = 0;
        CHECK(dw4_arena_object_release(a, o) == 0);               /* destroyed */
        CHECK(destruct_n == 3 && destruct_log[0] == 8 && destruct_log[1] == 10 && destruct_log[2] == 0);   /* igObject_Destroy order */
        CHECK(dw4_arena_at(a, o, 4) == NULL);                     /* the block is gone */
        CHECK(dw4_arena_object_release(a, o) == -1);              /* a stale handle cannot be released */
        CHECK(dw4_arena_object_new(a, DW4_REGION_PERSISTENT, 0x424242).off == 0 && dw4_arena_status_last(a) == DW4_ARENA_BAD_CLASS);
    }
    dw4_arena_close(a);

    /* the session arena is one shared arena; owners give back what they allocated; it can be closed and recreated */
    {
        dw4_arena *s = dw4_session_arena(), *again = dw4_session_arena();
        dw4_arena_owned held = {0};
        dw4_handle x, y;
        CHECK(s != NULL && s == again);
        CHECK(dw4_class_name(s, 0x53b740) != NULL);                       /* the schema classes are registered */
        x = dw4_arena_alloc(s, DW4_REGION_PERSISTENT, 100);
        y = dw4_arena_alloc(s, DW4_REGION_PERSISTENT, 200);
        CHECK(dw4_arena_owned_add(&held, x) == 0 && dw4_arena_owned_add(&held, y) == 0);
        CHECK(dw4_arena_live(s, DW4_REGION_PERSISTENT) == 2);
        dw4_arena_owned_release(s, &held);
        CHECK(dw4_arena_live(s, DW4_REGION_PERSISTENT) == 0 && held.n == 0 && dw4_arena_at(s, x, 4) == NULL);
        dw4_session_arena_close();
        CHECK(dw4_session_arena() != NULL);                                /* a fresh one on the next use */
        dw4_session_arena_close();
    }

    /* a handle is a 4-byte offset, never a host pointer */
    CHECK(sizeof(dw4_handle) == 4);

    if (bad) {
        printf("arena: %d failures\n", bad);
        return 1;
    }
    printf("arena: handles, regions, exhaustion, reuse, class registry and igObject reference counting verified\n");
    return 0;
}
