#ifndef WAVEOUTWRA_H_
#define WAVEOUTWRA_H_



#ifdef __cplusplus
extern "C"
{
#endif

int wstart();
int wstop();
int winput(unsigned char* buf);

#ifdef __cplusplus
}
#endif

#endif // WAVEOUTWRA_H_