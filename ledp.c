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
	SENSORS_ACTIVATE(button_sensor);
	leds_off(LEDS_ALL);
	printf("All leds are off\n");   
	printf("Press the user button to start\n");
 
    while(1) {
	static uint32_t ticks = 0;
	static uint32_t seconds = 5;
	static struct etimer et; // creating a timer
 
	PROCESS_WAIT_EVENT();
 
	if(ev == sensors_event) {  // If the event it's provoked by the user button, then...
           if(data == &button_sensor) {		
		etimer_set(&et, CLOCK_SECOND*seconds);  // Set the timer
		printf("Timer started\n");
           }
        }
 
	if(etimer_expired(&et)) {  // If the event it's provoked by the timer expiration, then...
		leds_toggle(LEDS_BLUE);
		if (ticks % 2 == 0) {
			printf("LED BLUE .............. [ON]\n");
                }
		else { 
			printf("LED BLUE ............. [OFF]\n");
                }
		etimer_reset(&et);
		ticks++;
                }	
	}		
	exit:
		leds_off(LEDS_ALL);
		PROCESS_END();
}
