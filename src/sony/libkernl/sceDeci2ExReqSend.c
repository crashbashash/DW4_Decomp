int Deci2Call(int call, int *args);

#define DECI2_EX_REQ_SEND -7

int sceDeci2ExReqSend(int socket, char dest) {
    int args[4];
    args[0] = socket;
    args[1] = dest;
    return Deci2Call(DECI2_EX_REQ_SEND, args);
}
