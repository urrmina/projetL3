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
	button_sensor::value(0); // the button has been pressed or not
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
 
	if(ev == sensors_event) {  // If the event is provoked by the user button, then...
           if(data == &button_sensor) {		
		etimer_set(&et, CLOCK_SECOND*seconds);  // Set the timer
		printf("#########\n######### Timer started #########\n#########\n");
           }
        }
 	
 	// to make the leds blink after pressing the button
	if(etimer_expired(&et)) {  // If the event it's provoked by the timer expiration, then...
		leds_toggle(LEDS_BLUE); // to switch between ON & OFF for the active button (BLUE)
		if (ticks % 2 == 0) {
			printf("LED BLUE [ON]\n");
			leds_on(LEDS_GREEN);
                }
		else { 
			printf("LED BLUE [OFF]\n");
			leds_toggle(LEDS_RED);
                }
		etimer_reset(&et);
		ticks++;
                }	
	}
	// the timer will sychronize all button to turn on & off together		
	exit:
		leds_off(LEDS_ALL);
		PROCESS_END();
}
