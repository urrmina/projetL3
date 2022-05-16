#include <stdio.h> 
#include "contiki.h" /*system file, always included*/
#include "dev/leds.h"/*leds driver*/
#include "dev/button-sensor.h" /*user button driver*/

/* test with skymote LEDs*/
/* A quick program that blinks LEDs*/

static struct etimer blinktimer; /* creating a timer */

static uint8_t blinks; /*a date type that have 8bit variables*/

PROCESS(blink_process, "LED BLINK PROCESS"); 
AUTOSTART_PROCESSES(&blink_process); /* Load process at boot*/
 
 PROCESS_THREAD(blink_process, ev, data) /*ev is event time*/
 {
  PROCESS_EXITHANDLER(goto exit); // for when another process already exists.
  PROCESS_BEGIN();
 //blinks=0;
 while(1) {
  	etimer_set(&blinktimer, CLOCK_SECOND);
  	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&blinktimer));
  	leds_on(blinks & LEDS_ALL);
  	etimer_set(&blinktimer, CLOCK_SECOND);
  	PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&blinktimer));
  	leds_off(LEDS_ALL);
 }
 
 exit;
 leds_off(LEDS_ALL);
 PROCESS_END();
 }
