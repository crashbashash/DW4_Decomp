struct CurvePoint4 { int a, b, c, d; };
void FUN_00192f00(struct CurvePoint4 *o, float t, struct CurvePoint4 *a, struct CurvePoint4 *b);
void FUN_001930f0(struct CurvePoint4 *out, struct CurvePoint4 *p1, struct CurvePoint4 *p2, struct CurvePoint4 *p3, struct CurvePoint4 *p4, float t) {
    struct CurvePoint4 v1, v2, v3, v4, v5;
    FUN_00192f00(&v1, t, p1, p2);
    FUN_00192f00(&v2, t, p2, p3);
    FUN_00192f00(&v3, t, p3, p4);
    FUN_00192f00(&v4, t, &v1, &v2);
    FUN_00192f00(&v5, t, &v2, &v3);
    FUN_00192f00(out, t, &v4, &v5);
}
