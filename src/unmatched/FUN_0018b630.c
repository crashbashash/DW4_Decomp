struct B { char pad[8]; float lox; float loy; float loz; float hix; float hiy; float hiz; };
struct V { float x; float y; float z; };
int FUN_0018b630(struct B *arg0, struct V *arg1) {
    float temp_f1;
    float temp_f1_2;
    float temp_f1_3;
    temp_f1 = arg1->x;
    if (arg0->lox <= temp_f1 && temp_f1 <= arg0->hix) {
        temp_f1_2 = arg1->y;
        if ((arg0->loy <= temp_f1_2) && (temp_f1_2 <= arg0->hiy)) {
            temp_f1_3 = arg1->z;
            if ((arg0->loz <= temp_f1_3) && (temp_f1_3 <= arg0->hiz)) {
                return 2;
            }
        }
    }
    return 0;
}
