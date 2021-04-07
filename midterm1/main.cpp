#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

InterruptIn Up(D10);
InterruptIn Down(D9);
InterruptIn Confirm(D8);

AnalogIn Ain(D12);
AnalogOut Aout(D7);

EventQueue queue(32 * EVENTS_EVENT_SIZE);
float curr_sel = 0.5; 

Thread t;
bool wave_start = false;
bool a = true;
int while_num = -1, finish = 0;

void up_()
{
    if (curr_sel != 1)
        curr_sel *= 2;
}
void down_()
{
    if (curr_sel != 1/8)
        curr_sel /= 2;
}
void confirm_()
{
    uLCD.printf("%f\r\n", curr_sel);
    
    // int count = 0;
    // period without waiting = 2.320 ms
    //cutoff freq. = 1 / (2 * pi * (4700 + 3900) * 0.047 * 10^-6) = 393.75 Hz
    //period = 2.54 ms
    for (int count = 1; count<=240; count++){
    // if (count == 240)
    //     count = 0;
    // else
     if (count <= 80 * curr_sel)
        Aout = count / (1.0f * 1.1 * 80 * curr_sel);
    else if (count >= 240 - 80 * curr_sel)  
        Aout = (240 - count) / (1.0f * 1.1 * 80 * curr_sel);
    else 
        Aout = 1 / 1.0f / 1.1;

    // count++;
}
    // wait_us(wait);
}
int main()
{  
    // float wait = 0;
   
    // while (1)
    // {
        // while_num++;

    uLCD.printf("Hello");
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    Up.rise(&up_);
    Down.rise(&down_);
    Confirm.rise(queue.event(confirm_));
    //     if (a && finish == 500)
    //     {
    //         a= false;
    //         //printf ("%d\r\n", freq);
    //         //ThisThread::sleep_for(500ms);
    //         for (int i = 0; i < 500; i++)
    //             {
    //                 printf("%f\r\n", ADCdata[i]);
    //             }
    //     }
    // }
    while (1)
        ;
}