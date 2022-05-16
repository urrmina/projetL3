 #include "contiki.h"
 #include <stdio.h>
 #include "dev/leds.h"
 #include "dev/button-sensor.h"
 PROCESS(led_process,"LED_PROCESS");
 AUTOSTART_PROCESSES(&led_process);
 PROCESS_THREAD(led_process,ev,data)
 {
 PROCESS_BEGIN();
 SENSORS_ACTIVATE(button_sensor);
 while(1)
 {
 printf("Press the button of the sensor");
 PROCESS_WAIT_EVENT_UNTIL(ev=sensors_event && data==&button_sensor);
 leds_toggle(LEDS_GREEN);
 }
 printf("The sensor valus ls %u \n", leds_get());
 PROCESS_END();
 }
