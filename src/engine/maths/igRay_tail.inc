void FUN_0018d260(void) {

}

int FUN_0018d270(void) {
    return 0;
}

void FUN_0018d280(void *arg0, void *arg1) {
    float temp_f1;

    temp_f1 = *(float *)((char *)(arg0) + 20);
    *(float *)((char *)(arg1) + 0) = (float) (temp_f1 * *(float *)((char *)(arg0) + 8));
    *(float *)((char *)(arg1) + 4) = (float) (temp_f1 * *(float *)((char *)(arg0) + 12));
    *(float *)((char *)(arg1) + 8) = (float) (temp_f1 * *(float *)((char *)(arg0) + 16));
}

void igRay_SetFromPoints(igRay *ray, const float *from, const float *to) {
    float len;
    ray->_pos.set(from);
    ray->_dir[0] = to[0] - from[0];
    ray->_dir[1] = to[1] - from[1];
    ray->_dir[2] = to[2] - from[2];
    len = ray->_dir.length();
    ray->_len = len;
    if (4.99999999e-07f < len) {
        ray->_dir.scale(1.0f / len);
    }
}

void igRay_Transform(igRay *ray, const float *matrix) {
    igVec3f end;

    end.addScaled(ray->_pos, ray->_len, ray->_dir);
    Vec3f_TransformProjective(ray->_pos.vec, ray->_pos.vec, matrix);
    Vec3f_TransformProjective(end.vec, end.vec, matrix);
    ray->_dir.subtract(end, ray->_pos);
    ray->_len = ray->_dir.normalize();
}

