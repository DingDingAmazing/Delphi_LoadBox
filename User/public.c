#include "public.h"

//us time delay
void bsp_uDelay (const uint32_t usec)
{
    uint32_t count = 0;
    const uint32_t utime = (48 * usec / 7);
    do
    {
        if ( ++count > utime )
        {
            return ;
        }
    }
    while (1);
}

//ms time delay
void bsp_mDelay (const uint32_t msec)
{
    bsp_uDelay(msec * 1000);   
}

//timer start
void tmr_start(tmr_t *tmr,const tmr_ticks_t delay_in_ticks)
{
    tmr->delay_in_ticks = delay_in_ticks;
    tmr->start_tick     = 	rt_tick;
    tmr->state          =  TMR_STARTED;
}

bool_t tmr_has_expired(tmr_t *tmr)
{
    tmr_ticks_t  tick_old;

    if(tmr->state == TMR_STOPPED)
        return FALSE;
    if(tmr->state != TMR_EXPIRED)
    {
        tick_old=rt_tick;	
        if(tick_old-tmr->start_tick > tmr->delay_in_ticks)
        {
            tmr->state = TMR_EXPIRED;
            return TRUE;
        }
        else
            return FALSE;			
    }
    else
        return TRUE;		
}

void tmr_reset(tmr_t *tmr)
{
    tmr->start_tick +=tmr->delay_in_ticks;
    //		tmr->start_tick =  rt_tick;
    tmr->state        =  TMR_STARTED;
}

void tmr_stop(tmr_t *tmr)
{
    tmr->state = TMR_STOPPED;
}
