#include "config.h"
#include "stm32f10x.h"                  // Device header

/******************** 外设参数 ************************/
// 电机PWM参数
#define MOTOR_PSC 71
#define MOTOR_ARR 99
#define PWM_MAX_DUTY 100

/******************** 业务参数 ************************/
// 电机档数
#define MOTOR_SPEED_SSTOP 0
#define MOTOR_SPEED_30PER 30
#define MOTOR_SPEED_60PER 60
#define MOTOR_SPEED_FULL 100

// 环境温度阈值
#define AD_TEMP_LOW 25
#define AD_TEMP_HIGH 30

// 对射式红外传感器
#define IR_BLOCK_FLAG 1
#define IR_NORMAL_FLAG 0

// 

