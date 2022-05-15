#include <stdio.h>
#include "contiki.h"
#include "dev/leds.h"

/* test with skymote LEDs*/

/*Creating a timer, etimer is event time*/
static struct etimer blinktimer;

static uint8_t blinks; /*a date type that have 8bit variables*/

PROCESS(blink_process, "LED BLINK PROCESS"); /*a contiki process */
AUTOSTART_PROCESSES(&blink_process);
 
 PROCESS_THREAD(blink_process,ev,data) /*ev is event time*/
 {
 PROCESS_BEGIN();
 blinks=0;
 while(1)
 {
 etimer_set(&blinktimer, CLOCK_SECOND);
 /* CLOCK_SECOND generates 1 to 10 ms timing signals according to the motes */
 PROCESS_WAIT_EVENT_UNTIL(ev==PROCESS_EVENT_TIMER);
 leds_off(LEDS_ALL);
 leds_on(blinks & LEDS_ALL);
 blinks++;
 printf("State of LED %02X \n", leds_get());
 }
 PROCESS_END();
 }
