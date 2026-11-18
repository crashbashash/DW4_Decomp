void igRadioGroup_resetFields(void *arg0, int flags) {
    Gap__Core__igObject__resetFields((igObject *)arg0, flags);
    *(int *)((char *)(*(int *)((char *)(arg0) + 12)) + 12) = (int)(arg0);
    igView_SetModel((igView *)(*(int *)((char *)(arg0) + 12)), (igModel *)(*(int *)((char *)(arg0) + 8)));
}

