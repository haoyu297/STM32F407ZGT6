#include <includes.h> 
#include "include.h"

#if DEBUG > 0
struct __FILE { int handle; /* Add whatever is needed */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}

#else

void Nothing(const char* format,...){};
	
	
#endif




