/*
 * PCA9670.h
 *
 *  Created on: 3 Jun 2016
 *      Author: WillyKaze
 */

#ifndef SOURCES_PCA9670_H_
#define SOURCES_PCA9670_H_

#ifdef __cplusplus
extern "C" {
#endif

void PCA9670_Init();
void PCA9670_SendByte(byte, uint16_t);

#ifdef __cplusplus
}  /* extern "C" */
#endif


#endif /* SOURCES_PCA9670_H_ */
