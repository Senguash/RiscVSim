#include <stdio.h>
#include <stdlib.h>

#include "memMan.h"


int main(){
    initMem();
    word cp = getInitCP();

    setWord(0x11223344,cp);
    word r = getWord(cp);

    cp += 4;
    setHWord(0x1122,cp);
    hWord hr = getHWord(cp);

    cp += 4;
    setByte(0x11,cp);
    byte br = getByte(cp);

	printf("%ld\n", r);
    printf("%\n", hr);
    printf("%c\n", br);
}
