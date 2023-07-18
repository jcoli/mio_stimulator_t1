/**
Version: 0a
Tecnocoli - 06/2023
jcoli - Jeferson Coli - jcoli@teccnocoli.com.br
STM32F401 - Mio Stimulation
**/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* defines */
#define V03_MAX 3.6
#define V03_MIN 3.1
#define V05_MAX 5.5
#define V05_MIN 4.8
#define VBAT_MAX 8.4
#define VBAT_MIN 6.6  

#define TEMP_MAX 50
#define TEMP_MIN 10

#define CALX_TEMP 25
#define V25       760
#define AVG_SLOPE 2500
#define VREFINT   1210

#define LL_ADC_RESOLUTION LL_ADC_RESOLUTION_12B
#define ADC_RANGE 4096

static const char version[] = "0.0a";
static const char develop[] =  "jcoli-Tecnocoli";
static const char email_develop[] = "jcoli@tecnocoli.com.br";
static const char processor[] = "STM32F401CC";

#define TIMER_INTERVAL_0_1S           100L
#define TIMER_INTERVAL_0_3S           300L
#define TIMER_INTERVAL_1S             1000L
#define TIMER_INTERVAL_1_5S           1500L
#define TIMER_INTERRUPT_DEBUG         0
#define _TIMERINTERRUPT_LOGLEVEL_     0 
#define TIMER_INTERVAL_MS         100
#define HW_TIMER_INTERVAL_MS      50





#endif