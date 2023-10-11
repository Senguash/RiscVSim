#include <stdio.h>
#include <stdlib.h>

#include "memMan.h"


int main(){
    initMem();
    word cp = getInitPC();

    setWord(1234,cp);
    word r = getWord(cp);

    cp += 4;
    setHWord(123,cp);
    hWord hr = getHWord(cp);

    cp += 4;
    setByte(13,cp);
    byte br = getByte(cp);

	printf("%ld\n", r);
    printf("%d\n", hr);
    printf("%d\n", br);
}
