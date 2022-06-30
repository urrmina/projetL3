#include <stdio.h> 
#include "contiki.h" /*system file, always included*/
#include "dev/leds.h"/*leds driver*/
#include "dev/button-sensor.h" /*user button driver*/

PROCESS(blink_timer_process, "blink with timer example");
AUTOSTART_PROCESSES(&blink_timer_process);

PROCESS_THREAD(blink_timer_process, ev, data)
{
  PROCESS_EXITHANDLER(goto exit); /*In case another process already exists*/
  PROCESS_BEGIN();
 
  	/* Initializing stuff here */ 
	SENSORS_ACTIVATE(button_sensor); // activate the button sensor
	leds_off(LEDS_ALL);
	printf("All leds are off\n");   
	printf("Press the user button to start\n");
 
    while(1) {
	static uint32_t ticks = 0;
	static struct etimer et; // creating a timer
 
	PROCESS_WAIT_EVENT();
	
 	if(ticks < 2310) { //the led will e on for approximatly one minute
		if (ev == sensors_event && data == &button_sensor) {
			   etimer_set(&et, CLOCK_SECOND*5);		
			   printf("	Timer started 		\n");
		}

 		// to make the leds blink after pressing the button
		if(etimer_expired(&et)) {
			if (ticks % 2 == 0) {
				printf("LED RED BLINK [ON]\n");
				leds_on(LEDS_GREEN);
		        }
			else { 
				printf("LED RED BLINK [OFF]\n");
				leds_toggle(LEDS_RED);
		        }
			etimer_reset(&et);
			ticks++;
		}	
	} else {
		leds_off(LEDS_RED);
		leds_off(LEDS_GREEN);
		ticks = 0;
	}
	}
  exit:
  	leds_off(LEDS_ALL);
  PROCESS_END();
}
