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

void FUN_0018d2b0(S3 *s, V33 *a, V33 *b) {
    float len, inv;
    s->p.x = a->x;
    s->p.y = a->y;
    s->p.z = a->z;
    s->d.x = b->x - a->x;
    s->d.y = b->y - a->y;
    s->d.z = b->z - a->z;
    len = sqrtf(s->d.x * s->d.x + s->d.y * s->d.y + s->d.z * s->d.z);
    s->len = len;
    if (4.99999999e-07f < len) {
        inv = 1.0f / len;
        s->d.x = s->d.x * inv;
        s->d.y = s->d.y * inv;
        s->d.z = s->d.z * inv;
    }
}

void FUN_0018d360(igRay *ray, const void *matrix) {
    igVec3f2 end;
    float len;
    float scale;

    len = ray->_len;
    end.x = ray->_pos[0] + len * ray->_dir[0];
    end.y = ray->_pos[1] + len * ray->_dir[1];
    end.z = ray->_pos[2] + len * ray->_dir[2];
    Vec3f_TransformProjective(ray->_pos, ray->_pos, (float *)matrix);
    Vec3f_TransformProjective((float *)&end, (float *)&end, (float *)matrix);
    end.subtractInto(ray->_dir, ray->_pos);
    len = lengthOf(ray->_dir);
    scale = 1.0f / len;
    ray->_dir[0] = ray->_dir[0] * scale;
    ray->_dir[1] = ray->_dir[1] * scale;
    ray->_dir[2] = ray->_dir[2] * scale;
    ray->_len = len;
}

