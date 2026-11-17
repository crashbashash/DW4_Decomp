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
    float len, inv;
    ray->_pos[0] = from[0];
    ray->_pos[1] = from[1];
    ray->_pos[2] = from[2];
    ray->_dir[0] = to[0] - from[0];
    ray->_dir[1] = to[1] - from[1];
    ray->_dir[2] = to[2] - from[2];
    len = sqrtf(ray->_dir[0] * ray->_dir[0] + ray->_dir[1] * ray->_dir[1] + ray->_dir[2] * ray->_dir[2]);
    ray->_len = len;
    if (4.99999999e-07f < len) {
        inv = 1.0f / len;
        ray->_dir[0] = ray->_dir[0] * inv;
        ray->_dir[1] = ray->_dir[1] * inv;
        ray->_dir[2] = ray->_dir[2] * inv;
    }
}

void igRay_Transform(igRay *ray, const float *matrix) {
    igVec3f2 end;
    float len;
    float scale;

    len = ray->_len;
    end.x = ray->_pos[0] + len * ray->_dir[0];
    end.y = ray->_pos[1] + len * ray->_dir[1];
    end.z = ray->_pos[2] + len * ray->_dir[2];
    Vec3f_TransformProjective(ray->_pos, ray->_pos, matrix);
    Vec3f_TransformProjective(&end.x, &end.x, matrix);
    end.subtractInto(ray->_dir, ray->_pos);
    len = lengthOf(ray->_dir);
    scale = 1.0f / len;
    ray->_dir[0] = ray->_dir[0] * scale;
    ray->_dir[1] = ray->_dir[1] * scale;
    ray->_dir[2] = ray->_dir[2] * scale;
    ray->_len = len;
}

