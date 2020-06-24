#include  "waveoutWra.h"
#include  "../waveout/waveout.h"

waveout wout;



int wstart(){
	return wout.start();
}




int wstop(){
	return wout.stop();
}

int winput(unsigned char* buf){
	return wout.input(buf);
}


