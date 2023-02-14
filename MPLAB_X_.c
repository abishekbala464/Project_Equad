#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#define _XTAL_FREQ 6000000

//--------Initializing the variables and arrays(coordinates)--------
unsigned int x=0,y=0;
unsigned int a,b,i,j,k,n=20,x1=0,x0=0,y1=0;
int arr1[20][2]={{92,1555},{92,1558},{92,1561},{92,1563},{92,1566},{92,1568},{95,1526},{95,1529},{95,1531},{95,1534},{95,1537},{95,1539},{95,1542},{95,1545},{95,1547},{95,1550},{95,1553},{95,1571},{95,1574},{95,1576}};
int arr2[20][2]={{95,1579},{95,1582},{95,1584},{95,1587},{95,1590},{97,1521},{97,1523},{97,1592},{97,1595},{100,1510},{100,1513},{100,1516},{100,1518},{100,1598},{100,1600},{100,1603},{100,1606},{103,1502},{103,1505},{103,1508}} ;
int arr3[20][2]={{103,1608},{103,1611},{103,1613},{103,1616},{105,1497},{105,1500},{105,1619},{105,1621},{108,1492},{108,1494},{108,1624},{111,1486},{111,1489},{111,1627},{111,1629},{113,1481},{113,1484},{113,1632},{113,1635},{116,1476}} ;

\\---------One revolution(1mm) of Stepper motor along positive y-axis------------
void y_axis_positive()
{  PORTC=0x03;__delay_ms(100); 
   PORTC=0x02;__delay_ms(100);
   PORTC=0x06;__delay_ms(100);
   PORTC=0x04;__delay_ms(100); 
   PORTC=0x0C;__delay_ms(100); 
   PORTC=0x08;__delay_ms(100);
   PORTC=0x09;__delay_ms(100);
   PORTC=0x01;__delay_ms(100);
   PORTC=0x03;__delay_ms(100); }

\\---------One revolution(1mm) of Stepper motor along positive x-axis------------
void x_axis_positive()
{  PORTD=0x03;__delay_ms(100);
   PORTD=0x02;__delay_ms(100);
   PORTD=0x06;__delay_ms(100);
   PORTD=0x04;__delay_ms(100);
   PORTD=0x0C;__delay_ms(100);
   PORTD=0x08;__delay_ms(100);
   PORTD=0x09;__delay_ms(100);
   PORTD=0x01;__delay_ms(100);
   PORTD=0x03;__delay_ms(100); }

\\---------One revolution(1mm) of Stepper motor along negative y-axis------------
void y_axis_negative()
{  PORTC=0x03;__delay_ms(100); 
   PORTC=0x01;__delay_ms(100);
   PORTC=0x09;__delay_ms(100);
   PORTC=0x08;__delay_ms(100); 
   PORTC=0x0C;__delay_ms(100); 
   PORTC=0x04;__delay_ms(100);
   PORTC=0x06;__delay_ms(100);
   PORTC=0x02;__delay_ms(100);
   PORTC=0x03;__delay_ms(100); }

\\---------------------Move the DC motor (Driller) based on the coordinates-------
void  mov_2_pos(x1,y,x0){
    x=x1-x0;
    for(k=0;k<x;k++)
    { x_axis_positive();__delay_ms(100);}
    for(k=0;k<y;k++)
    { y1++;y_axis_positive();__delay_ms(100);}
    for(k=0;k<y;k++)
    { y1--;y_axis_negative();__delay_ms(100);}
}
void main() {
    TRISC=0x00;
    TRISD=0x00;
    TRISB=0x00;
    PORTC=0x00;
    PORTD=0x00;
    PORTB=0x00;
    
    \\-----------Formatting the coordinates in arrays-------
    while(1)
    {   PORTB=0x01;
        for(i=0;i<n;i++){ mov_2_pos(arr1[i][0],arr1[i][1],arr1[i-1][0]);}
        for(i=0;i<n;i++){ mov_2_pos(arr2[i][0],arr2[i][1],arr1[i-1][0]);}
        for(i=0;i<n;i++){ mov_2_pos(arr3[i][0],arr3[i][1],arr1[i-1][0]);}
    }
    }
