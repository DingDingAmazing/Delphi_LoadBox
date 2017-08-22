#ifndef _PUBLIC_H
#define _PUBLIC_H

#include "stm32f0xx.h"
#include "stm32f0xx_it.h"

typedef unsigned char UINT8;
typedef unsigned short UINT16;
/**************struct tmr_t************/
typedef enum
{
    TMR_STOPPED = 0,
    TMR_STARTED,
    TMR_EXPIRED,
} tmr_state_t;
typedef uint32_t tmr_ticks_t;
typedef struct
{
    tmr_state_t state;           ///< State of timer: STOPPED, STARTED or EXPIRED
    tmr_ticks_t start_tick;      ///< Tick when timer started
    tmr_ticks_t delay_in_ticks;  ///< Timer delay
} tmr_t;
/**************end struct tmr_t************/

#define BYTE UINT8
#define WORD UINT16
#define HIBYTE(a) ((BYTE)(a>>8))
#define LOBYTE(a) ((BYTE)a)
#define bool_t _Bool
#define FALSE  0
#define TRUE   (!FALSE)

extern void bsp_uDelay (const uint32_t usec);
extern void bsp_mDelay (const uint32_t msec);
extern void tmr_start(tmr_t *tmr,const tmr_ticks_t delay_in_ticks);
extern bool_t tmr_has_expired(tmr_t *tmr);
extern void tmr_reset(tmr_t *tmr);
extern void tmr_stop(tmr_t *tmr);
#endif
