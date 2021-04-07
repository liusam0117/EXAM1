#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn mypin1(D8);
DigitalIn mypin2(D9);
DigitalIn mypin3(D10);
AnalogOut aout(PA_4); // D7
AnalogIn Ain(A0);

uLCD_4DGL uLCD(D1, D0, D2);

EventQueue queue(32 * EVENTS_EVENT_SIZE);

Thread t;

int freq = 100;
int slewrates = 0;

void Gen_wave()  {
   
}

int main()
{
    int counter = 0;
    uLCD.text_width(2); //4X size text
    uLCD.background_color(0xFFFFFF);
    uLCD.textbackground_color(0xFFFFFF);
    uLCD.text_height(2);
    uLCD.color(BLUE);
    uLCD.printf("SLEWRATE:");
    while(!mypin3){
        uLCD.locate(3,2);
        //uLCD.printf("%2d",counter);
        if(mypin2 && counter < 3){           
            counter++;
            slewrates = pow(2, counter); 
            uLCD.printf("1/%d",slewrates);
        }else if(mypin1 && counter > 0){            
            counter--;
            slewrates = pow(2, counter); 
            uLCD.printf("1/%d",slewrates);
        }else {
            slewrates = pow(2, counter);
            uLCD.printf("1/%d",slewrates);
        }
        ThisThread::sleep_for(300ms);
    }
    uLCD.locate(3,2);
    uLCD.textbackground_color(BLACK);
    slewrates = pow(2, counter);
    uLCD.printf("1/%d",slewrates);
    
    ThisThread::sleep_for(500ms);
    float data[500] = {0};
    int i=0,j=0,triwave;
    int up_twaste, down_twaste, remain_twaste;
    up_twaste = 40/slewrates;
    down_twaste = 40/slewrates;
    remain_twaste = 120 - up_twaste - down_twaste;
    while(j<500){
        if(i<up_twaste){
            triwave = (uint16_t)(65535 * 3/3.3 * i/up_twaste);
            aout.write_u16(triwave);
        }else if(i<remain_twaste + up_twaste){
            triwave = (uint16_t)(65535 * 3/3.3 * 1);
            aout.write_u16(triwave);
        }else{
            triwave = (uint16_t)(65535 * 3/3.3 - (65535 * 3/3.3 * (i-up_twaste-remain_twaste)/down_twaste));
            aout.write_u16(triwave);
        }   
        data[j] = Ain;
        
        if(i<(up_twaste + down_twaste + remain_twaste)-1){
            i++;
        }else{
            i=0;
        }
        j++;
        wait_us(2000);// 240ms period
    }
    for(j=0;j<500;j++){
        printf("%f\n", data[j]);
    }
}