#include "mbed.h"
#include "uLCD_4DGL.h"

InterruptIn mypin1(D8);
InterruptIn mypin2(D9);
InterruptIn mypin3(D10);
AnalogOut aout(PA_4); // D7
AnalogIn Ain(A0);

uLCD_4DGL uLCD(D1, D0, D2);



int freq = 0;
Thread t;
void gen_waveform();

int main()
{
    int counter = 0;
    int S;
    int freq_rate = 20;
    uLCD.text_width(2); //4X size text
    uLCD.background_color(0xFFFFFF);
    uLCD.textbackground_color(0xFFFFFF);
    uLCD.text_height(2);
    uLCD.color(RED);
    
    while(!mypin3){
        uLCD.locate(1,2);
        //uLCD.printf("%2d",counter);
        if(mypin1 && counter < 4){           
            counter++;
            freq = (counter+1)*freq_rate; 
            uLCD.printf("%3dHz",freq);
        }else if(mypin2 && counter > 0){            
            counter--;
            freq = (counter+1)*freq_rate; 
            uLCD.printf("%3dHz",freq);
        }else {
            freq = (counter+1)*freq_rate;
            uLCD.printf("%3dHz",freq);
        }
        ThisThread::sleep_for(300ms);
    }
    uLCD.locate(1,2);
    uLCD.textbackground_color(BLACK);
    freq = (counter+1)*freq_rate;
    uLCD.printf("%3dHz",freq);
    
    ThisThread::sleep_for(500ms);
    float data[600] = {0};
    int i=0,j=0,triwave;
    int up_twaste, down_twaste;
    up_twaste = 3600/freq/2;
    down_twaste = 400/freq/2;
    while(j<600){
        if(i<up_twaste){
            triwave = (uint16_t)(65535 * 3/3.3 * i/up_twaste);
            aout.write_u16(triwave);
        }else{
            triwave = (uint16_t)(65535 * 3/3.3 - (65535 * 3/3.3 * (i-up_twaste)/down_twaste));
            aout.write_u16(triwave);
        }   
        data[j] = Ain;
        
        if(i<(up_twaste + down_twaste)-1){
            i++;
        }else{
            i=0;
        }
        j++;
        wait_us(500);// 100Hz
    }
    for(j=100;j<600;j++){
        printf("%f\n", data[j]);
    }

}