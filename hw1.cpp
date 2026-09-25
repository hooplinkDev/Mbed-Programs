#include "mbed.h"

DigitalOut led(LED1);          // LD3 (D13)
DigitalIn  btn(D2, PullUp);    // idle = 1, pressed = 0

int main()
{
    bool blinking = false;
    int  last = 1;
    Timer t;
    t.start();

    while (true) {
        int now = btn.read();
        if (now != last) {                 // any edge
            if (now == 0) {                // press
                blinking = !blinking;
                if (!blinking) led = 0;
            }
            last = now;
            ThisThread::sleep_for(30ms);   // debounce both press and release
        }
        if (blinking && t.elapsed_time() >= 250ms) {
            t.reset();
            led = !led;                    // 2 Hz blink
        }
        ThisThread::sleep_for(5ms);
    }
}