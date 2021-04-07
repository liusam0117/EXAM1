  
#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn bottom1(D8);
DigitalIn bottom2(D9);
DigitalIn bottom3(D10);

uLCD_4DGL uLCD(D1, D0, D2);

void print_num(int num);

int main()
{
    int bt1 = 0, bt2 = 0, bt3 = 0;
    int num = 0;
    int selected_num = 0;
    uLCD.background_color(BLACK);
    uLCD.color(GREEN);
    uLCD.textbackground_color(BLACK);
    uLCD.text_width(3);
    uLCD.text_height(3);
    uLCD.locate(0, 2);
    uLCD.printf(" 1/8 ");
    while (1) {
        if (!bt1 && bottom1) {
            num = (num + 1) % 4;
            uLCD.locate(0, 2);
            uLCD.color(GREEN);
            print_num(num);
            bt1 = bottom1;
        } else if (bt1 && !bottom1) {
            bt1 = bottom1;
        }

        if (!bt2 && bottom2) {
            num = (num + 3) % 4;
            uLCD.locate(0, 2);
            uLCD.color(GREEN);
            print_num(num);
            bt2 = bottom2;
        } else if (bt2 && !bottom2) {
            bt2 = bottom2;
        }

        if (!bt3 && bottom3) {
            selected_num = num;
            uLCD.locate(0, 2);
            uLCD.color(RED);
            print_num(num);
            uLCD.color(GREEN);
            bt3 = bottom3;
        } else if (bt3 && !bottom3) {
            bt3 = bottom3;
        }

        ThisThread::sleep_for(100ms);
    }
}

void print_num(int num) {
    switch (num) {
        case 0:
            uLCD.printf(" 1/8 ");
            break;
        case 1:
            uLCD.printf(" 1/4 ");
            break;
        case 2:
            uLCD.printf(" 1/2 ");
            break;
        case 3:
            uLCD.printf("  1  ");
            break;
        default:
            break;
    }
}