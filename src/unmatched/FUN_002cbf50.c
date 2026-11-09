typedef struct Owner {
    char pad[52];
    int field52;
} Owner;

void FUN_002cbf60(int value);

void FUN_002cbf50(Owner *owner)
{
    FUN_002cbf60(owner->field52);
}
