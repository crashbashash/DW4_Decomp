typedef struct DecInfoInfo {
    int w[32];
} DecInfoInfo;

typedef struct DecInfoObj {
    char pad[464];
    DecInfoInfo info;
    char pad592[88];
    int f680;
    int f684;
    int f688;
    int f692;
    int f696;
    int f700;
    char pad704[240];
    int handle;
} DecInfoObj;

void FUN_00285410(int h, DecInfoInfo *info);
void FUN_00285438(int h, int *a);
void FUN_00285460(int h, int *a, int *b, int *c);
void FUN_00285488(int h, int *a, int *b);

/* matching construct: 120-order sweep of the five field stores */
void FUN_002915a0(DecInfoObj *obj)
{
    DecInfoInfo info;
    int a;
    int b, c, d;
    int e, f;

    FUN_00285410(obj->handle, &info);
    FUN_00285438(obj->handle, &a);
    FUN_00285460(obj->handle, &b, &c, &d);
    FUN_00285488(obj->handle, &e, &f);
    obj->info = info;
    obj->f680 = a;
    obj->f684 = b / 2048;
    obj->f700 = c;
    obj->f692 = e;
    obj->f696 = f;
}
