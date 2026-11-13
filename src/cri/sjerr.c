/* CRI SJERR: the stream joints' error report, handed to the CRI error callback. */

void SVM_CallErr1(const char *message);

void SJERR_CallErr(const char *message)
{
    SVM_CallErr1(message);
}
