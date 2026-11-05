struct V { int a, b, c, d; };
void FUN_00192f00(struct V *o, float t, struct V *a, struct V *b);
void FUN_001930f0(struct V *out, struct V *p1, struct V *p2, struct V *p3, struct V *p4, float t) {
    struct V v5, v4, v3, v2, v1;
    FUN_00192f00(&v1, t, p1, p2);
    FUN_00192f00(&v2, t, p2, p3);
    FUN_00192f00(&v3, t, p3, p4);
    FUN_00192f00(&v4, t, &v1, &v2);
    FUN_00192f00(&v5, t, &v2, &v3);
    FUN_00192f00(out, t, &v4, &v5);
}
