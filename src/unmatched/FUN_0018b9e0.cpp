typedef struct { unsigned int mant : 23; unsigned int exp : 8; unsigned int sign : 1; } FB;
static inline bool isNeg(float x) { return ((FB *)&x)->sign != 0; }
static inline bool isPos(float x) { return !isNeg(x); }
static inline bool isZero(float x) { return x >= -5e-7f && x <= 5e-7f; }
struct V { float x, y, z; V() {} V(float a, float b, float c) { x = a; y = b; z = c; }
 float dot(const V &o) const { return x * o.x + y * o.y + z * o.z; }
 V operator-(const V &o) const { return V(x - o.x, y - o.y, z - o.z); }
 V operator+(const V &o) const { return V(x + o.x, y + o.y, z + o.z); }
 V operator*(float s) const { return V(x * s, y * s, z * s); }
 void madd(const V &a, const V &b, float s) { x = a.x + s * b.x; y = a.y + s * b.y; z = a.z + s * b.z; }
 void madd2(const V &a, float s, const V &b) { float m = s * b.x; x = a.x + m; m = s * b.y; y = a.y + m; m = s * b.z; z = a.z + m; }
 void sub(const V &a, const V &b) { x = a.x - b.x; y = a.y - b.y; z = a.z - b.z; }
 void add(const V &a, const V &b) { x = a.x + b.x; y = a.y + b.y; z = a.z + b.z; }
 void scale(const V &a, float s) { x = a.x * s; y = a.y * s; z = a.z * s; }
};
static inline V operator*(float s, const V &a) { return V(s * a.x, s * a.y, s * a.z); }
static inline V sub2(const V &a, const V &b) { V r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
static inline V add2(const V &a, const V &b) { V r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r; }
static inline float dotv(V a, V b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
static inline float madd_(float o, float t, float d) { return o + t * d; }
struct Ray { char pad[8]; V o; V d; float maxT; };
extern "C" float sqrtf(float);
extern "C" void FUN_00192dd0(V *out, V *a, V *b);
static inline float dot(const V *a, const V *b) { return a->x * b->x + a->y * b->y + a->z * b->z; }
static inline float dot3(float ax, float ay, float az, float bx, float by, float bz) { return ax * bx + ay * by + az * bz; }
static inline float lerp(float o, float t, float d) { float m = t * d; return o + m; }
extern "C" float FUN_0018b9e0(Ray *ray, V *a, V *b, V *c, V *hit, V *n, int mode) {
    /* matching construct: enumeration — d1, d2 and d3 reused as temporaries in the hit-point calculation */
    V e1,e2,ha,hb,hc,c1,c2,c3;
    float denom, t, inv, d1, d2, d3, m1, m2, m3;
    e1.x = b->x - a->x; e1.y = b->y - a->y; e1.z = b->z - a->z;
    e2.x = c->x - a->x; e2.y = c->y - a->y; e2.z = c->z - a->z;
    FUN_00192dd0(n, &e1, &e2);
    inv = 1.0f / sqrtf(dot(n, n));
    n->x *= inv; n->y *= inv; n->z *= inv;
    denom = n->dot(ray->d);
    if (mode != 2) {
        if ((isPos(denom) && mode == 0) || (isNeg(denom) && mode == 1) || isZero(denom) || denom != denom)
            return -2.0f;
    }
    t = -n->dot(ray->o - *a) / denom;
    if (isNeg(t) || !(t <= ray->maxT)) return -3.0f;
    d1 = t*ray->d.x; hit->x = ray->o.x + d1; d2 = t*ray->d.y; hit->y = ray->o.y + d2; d3 = t*ray->d.z; hit->z = ray->o.z + d3;
    ha.x = a->x - hit->x; ha.y = a->y - hit->y; ha.z = a->z - hit->z;
    hb.x = b->x - hit->x; hb.y = b->y - hit->y; hb.z = b->z - hit->z;
    hc.x = c->x - hit->x; hc.y = c->y - hit->y; hc.z = c->z - hit->z;
    FUN_00192dd0(&c1, &ha, &hb);
    FUN_00192dd0(&c2, &hb, &hc);
    FUN_00192dd0(&c3, &hc, &ha);
    d1 = c1.x * n->x + c1.y * n->y + c1.z * n->z;
    d2 = c2.x * n->x + c2.y * n->y + c2.z * n->z;
    d3 = c3.x * n->x + c3.y * n->y + c3.z * n->z;
    if ((isNeg(d1) & isNeg(d2) & isNeg(d3)) || (isPos(d1) & isPos(d2) & isPos(d3)))
        return t;
    return -4.0f;
}
