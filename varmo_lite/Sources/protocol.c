#include "ESW3.h"
#include "ASerialLdd1.h"

#include "protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

void send(){
	ESW3_SendBlock(&Get, 11,1);
}

#ifdef __cplusplus
}  /* extern "C" */
#endif
