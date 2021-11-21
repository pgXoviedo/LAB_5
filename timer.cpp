#include "timer.h"

/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){

// Set Timer 1 into CTC mode by setting WGM12 to 1 and all others to zero
TCCR1A &= ~(1 << WGM10);
TCCR1A &= ~(1 << WGM11);
TCCR1A |= (1 << WGM12);
TCCR1A &= ~(1 << WGM13);

// Set OCRIA = 16 - 1 = 15
OCR1A = 10;

}

/* This delays the program an amount of microseconds specified by unsigned int delay.
*/
void delayUs(unsigned int delay){

unsigned int count = 0;

//Set prescalar to 1024 and start timer 
TCCR1B |= ((1 << CS12) | (1 << CS10));
TCCR1B &= ~(1 << CS11);

// Set counter to 0
TIFR1 |= (1 << OCF1A);
TCNT1 = 0;

while(count < delay){
    if((TIFR1 & (1 << OCF1A))){ //increment every time the timer raises a flag
        count++;
        // set timer to start counting again
        // TIFR1 |= (1 << OCF1A);
    }
}
// end timer
TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));
}


// -----------------------------------------------------------------------------------------------------------------------------//


/* Initialize timer 0, you should not turn the timer on here.
* You will need to use CTC mode */
void initTimer0(){
    TCCR0A &= ~(1 << WGM00); //Set timer to be in CTC mode
    TCCR0A |= (1 << WGM01);
    TCCR0B &= ~(1 << WGM02);
}

/* This delays the program an amount specified by unsigned int delay.
* Use timer 0. Keep in mind that you need to choose your prescalar wisely
* such that your timer is precise to 1 millisecond and can be used for
* 100-200 milliseconds
*/
void delayMs(unsigned int delay){

unsigned int delayCnt = 0;

// Set prescalar to 64, and turn timer on
TCCR0B &= ~(1 << CS02);
TCCR0B |= (1 << CS01) | (1 << CS00); 

// my calculated value for OCR0A was 250 and a 64 prescalar
OCR0A = 249;


while(delayCnt < delay){
    // set the flag down (important to set flag down, After event takes place)
    TIFR0 |= (1 << OCF0A);
    
    // initialize TCNT0 = 0 to start counting from 0
    TCNT0 = 0;
    
    //while flag is down do nothing 
    while(!(TIFR0 & (1 << OCF0A)));
    //exit while loop when flag is up

    // increment our variable delayCnt
    delayCnt++;
}

//turn clock off
TCCR0B &= ~((1 << CS02) | (1 << CS01) | (1 << CS00)); 
}