#include <REGX52.h>

#define uint unsigned int

/* ---------- OUTPUTS ---------- */
sbit GREEN  = P1^0;
sbit YELLOW = P1^1;
sbit RED    = P1^2;
sbit BUZZER = P1^3;

/* ---------- ULTRASONIC ---------- */
/* ---------- FRONT ---------- */
sbit FRONT_TRIG = P3^5;
sbit FRONT_ECHO = P3^2;

/* ---------- LEFT ---------- */
sbit LEFT_TRIG  = P3^4;
sbit LEFT_ECHO  = P3^1;

/* ---------- RIGHT ---------- */
sbit RIGHT_TRIG = P3^3;
sbit RIGHT_ECHO = P3^0;

/* ---------- GLOBALS ---------- */
unsigned int left_distance;
unsigned int front_distance;
unsigned int right_distance;

/* ---------- DELAY ---------- */
void delay(uint ms)
{
    uint i,j;

    for(i=0;i<ms;i++)
    {
        for(j=0;j<1275;j++);
    }
}

/* ---------- FRONT TRIGGER ---------- */
void send_front_pulse(void)
{
    TH0 = 0x00;
    TL0 = 0x00;

    FRONT_TRIG = 0;

    FRONT_TRIG = 1;
    FRONT_TRIG = 1;
    FRONT_TRIG = 1;
    FRONT_TRIG = 1;
    FRONT_TRIG = 1;
    FRONT_TRIG = 1;
    FRONT_TRIG = 1;
    FRONT_TRIG = 1;
    FRONT_TRIG = 1;
    FRONT_TRIG = 1;

    FRONT_TRIG = 0;
}

/* ---------- LEFT TRIGGER ---------- */
void send_left_pulse(void)
{
    TH0 = 0x00;
    TL0 = 0x00;

    LEFT_TRIG = 0;

    LEFT_TRIG = 1;
    LEFT_TRIG = 1;
    LEFT_TRIG = 1;
    LEFT_TRIG = 1;
    LEFT_TRIG = 1;
    LEFT_TRIG = 1;
    LEFT_TRIG = 1;
    LEFT_TRIG = 1;
    LEFT_TRIG = 1;
    LEFT_TRIG = 1;

    LEFT_TRIG = 0;
}

/* ---------- RIGHT TRIGGER ---------- */
void send_right_pulse(void)
{
    TH0 = 0x00;
    TL0 = 0x00;

    RIGHT_TRIG = 0;

    RIGHT_TRIG = 1;
    RIGHT_TRIG = 1;
    RIGHT_TRIG = 1;
    RIGHT_TRIG = 1;
    RIGHT_TRIG = 1;
    RIGHT_TRIG = 1;
    RIGHT_TRIG = 1;
    RIGHT_TRIG = 1;
    RIGHT_TRIG = 1;
    RIGHT_TRIG = 1;

    RIGHT_TRIG = 0;
}
/* ---------- FRONT DISTANCE ---------- */
unsigned int get_front_range(void)
{
    unsigned long timer_val;
    unsigned int timeout = 60000;

    send_front_pulse();

    while(!FRONT_ECHO)
    {
        timeout--;
        if(timeout==0)
            return 999;
    }

    TH0=0;
    TL0=0;
    TR0=1;

    timeout=60000;

    while(FRONT_ECHO)
    {
        timeout--;
        if(timeout==0)
        {
            TR0=0;
            return 999;
        }
    }

    TR0=0;

    timer_val=((unsigned long)TH0<<8)|TL0;

    return timer_val/58;
}

/* ---------- LEFT DISTANCE ---------- */
unsigned int get_left_range(void)
{
    unsigned long timer_val;
    unsigned int timeout = 60000;

    send_left_pulse();

    while(!LEFT_ECHO)
    {
        timeout--;
        if(timeout==0)
            return 999;
    }

    TH0=0;
    TL0=0;
    TR0=1;

    timeout=60000;

    while(LEFT_ECHO)
    {
        timeout--;
        if(timeout==0)
        {
            TR0=0;
            return 999;
        }
    }

    TR0=0;

    timer_val=((unsigned long)TH0<<8)|TL0;

    return timer_val/58;
}

/* ---------- RIGHT DISTANCE ---------- */
unsigned int get_right_range(void)
{
    unsigned long timer_val;
    unsigned int timeout = 60000;

    send_right_pulse();

    while(!RIGHT_ECHO)
    {
        timeout--;
        if(timeout==0)
            return 999;
    }

    TH0=0;
    TL0=0;
    TR0=1;

    timeout=60000;

    while(RIGHT_ECHO)
    {
        timeout--;
        if(timeout==0)
        {
            TR0=0;
            return 999;
        }
    }

    TR0=0;

    timer_val=((unsigned long)TH0<<8)|TL0;

    return timer_val/58;
}

/* ---------- LEFT INDICATOR ---------- */
void left_indicator(void)
{
    GREEN = 1;
    YELLOW = 0;
    RED = 0;
    BUZZER = 0;
}

/* ---------- FRONT INDICATOR ---------- */
void front_indicator(void)
{
    GREEN = 0;
    YELLOW = 1;
    RED = 0;
    BUZZER = 0;
}
/* ---------- RIGHT INDICATOR ---------- */
void right_indicator(void)
{
    GREEN = 0;
    YELLOW = 0;
    RED = 1;
    BUZZER = 1;
}

void main(void)
{
    TMOD = 0x01;
    TR0 = 0;
    TH0 = 0x00;
    TL0 = 0x00;

    GREEN = 0;
    YELLOW = 0;
    RED = 0;
    BUZZER = 0;

    while(1)
    {
        left_distance  = get_left_range();
        front_distance = get_front_range();
        right_distance = get_right_range();

        GREEN = 0;
        YELLOW = 0;
        RED = 0;
        BUZZER = 0;

        if(left_distance < 40)
        {
            left_indicator();
        }

        if(front_distance < 40)
        {
            front_indicator();
        }

        if(right_distance < 40)
        {
            right_indicator();
        }

        delay(100);
    }
}
