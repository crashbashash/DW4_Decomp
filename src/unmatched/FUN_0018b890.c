struct Box { char pad[8]; float mn[3]; float mx[3]; };
void FUN_0018b890(struct Box *arg0, float *arg1) {
    float t;

    t = arg1[0];
    if (!(arg0->mn[0] <= t)) {
        arg0->mn[0] = t;
    }
    t = arg1[1];
    if (!(arg0->mn[1] <= t)) {
        arg0->mn[1] = t;
    }
    t = arg1[2];
    if (!(arg0->mn[2] <= t)) {
        arg0->mn[2] = t;
    }
    t = arg1[0];
    if (arg0->mx[0] < t) {
        arg0->mx[0] = t;
    }
    t = arg1[1];
    if (arg0->mx[1] < t) {
        arg0->mx[1] = t;
    }
    t = arg1[2];
    if (arg0->mx[2] < t) {
        arg0->mx[2] = t;
    }
}
