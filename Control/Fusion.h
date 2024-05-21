#ifndef __FUSION_H
#define __FUSION_H

#include "stm32f10x.h"
#include "openmv.h"
#include "TOF.h"

typedef struct {
    __IO uint8_t Enable;
    __IO uint16_t LowerBound;
    __IO uint16_t UpperBound;
    __IO uint8_t Directin;
    __IO int8_t MoveSpeed;
}Fusion_TypeDef;

extern Fusion_TypeDef fusion;

void Fusion_Init(Fusion_TypeDef *Fusion);
void Fusion_Set(Fusion_TypeDef *Fusion,uint16_t lower_bound,uint16_t upper_bound,uint8_t direction,int8_t speed);
void Fusion_FindBall(Fusion_TypeDef *Fusion);
void Fusion_Detect(Fusion_TypeDef *Fusion);

#endif
