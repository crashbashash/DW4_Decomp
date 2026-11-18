int igLightSet_GetInherantFlags(void) {
    return 1;
}

void igLightSet_userConstruct(void **arg0, int arg1) {
    igNode_userConstruct(arg0, arg1);
    if (arg1 == 0) {
        ((DW4VC_112_2 *)(arg0))->vX((int)(1), (int)(1));
    }
}

void igLightSet_Reset(O_1d0330 *arg0) {
    unsigned int n;
    unsigned int i;
    n = arg0->l->n;
    for (i = 0; i < n; i++) {
        arg0->l->a[i]->vX();
    }
}

void igLightSet_Transform(S_1d03b0 *arg0, int arg1) {
    int sp70[4];
    int sp60[4];
    unsigned int n;
    unsigned int i;
    LS *o;

    n = arg0->list->n;
    for (i = 0; i < n; i++) {
        o = (LS *)arg0->list->data[i];
        Vec3f_TransformProjective((float *)sp70, (const float *)((char *)o + ((D_1d03b0 * *)DAT_0055f0a0)[0]->off), (const float *)arg1);
        o->vA(sp70);
        Vec3f_TransformDirection((float *)sp60, (const float *)((char *)o + ((D_1d03b0 *)g_igLightAttr_directionMetaField)->off), (const float *)arg1);
        o->vB(sp60);
    }
}

void igLightStateSet_userConstruct(void **self, int flag) {
    igNode_userConstruct((void * *)self, flag);
}

