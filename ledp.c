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
	/* For the lights to function */
	leds_toggle(LEDS_RED); //keeps lights red when they turn
	leds_off(LEDS_ALL);

 
    while(1) {
	static uint32_t ticks = 0;
	static uint32_t seconds = 5;
	static struct etimer et; // creating a timer
 
	PROCESS_WAIT_EVENT();
 
	if(ticks < 11550) { //the led will be on for approximatly five minute (1min = 2310ticks)
		if (ev == sensors_event && data == &button_sensor) {	
		etimer_set(&et, CLOCK_SECOND*seconds);  // Set the timer
		printf("#########\n######### Timer started #########\n#########\n");
        }
 	
		if(etimer_expired(&et)) {  // If the event it's provoked by the timer expiration, then...
			
			if (ticks % 2 == 0) {
				printf("LED GREEN [ON]  LED RED [OFF]\n");
				leds_on(LEDS_GREEN);
				leds_off(LEDS_RED);
					}
			else {
				printf("LED GREEN [OFF] LED RED [ON] \n");
				leds_off(LEDS_GREEN);
				leds_on(LEDS_RED);
					}
				
			etimer_reset(&et);
			ticks++;
					}
	} else {
		leds_off(LEDS_RED);
		leds_off(LEDS_GREEN);
		ticks = 0;
		printf("All leds are off\n");   
		printf("Press the user button to start again\n");
	}	
	}
		
	exit:
		leds_off(LEDS_ALL);
		PROCESS_END();
}