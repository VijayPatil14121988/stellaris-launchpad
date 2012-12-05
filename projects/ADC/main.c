#include "inc/lm4f120h5qr.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"


	unsigned int a=0;

void TIMER0_ISR_A(void);
// main function.
unsigned long period;
int main(void) {
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_32_BIT_PER);
	period = (SysCtlClockGet()/10)/2;
	TimerLoadSet(TIMER0_BASE,TIMER_A,40000000);
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
	IntMasterEnable();
	TimerEnable(TIMER0_BASE,TIMER_A);
    GPIO_PORTF_DATA_R=0;

	while(1) {
	}
}

void TIMER0_ISR_A(void)
{
	TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT);
	GPIO_PORTF_DATA_R = 255;
	SysCtlDelay(1000000);

	GPIO_PORTF_DATA_R = 0;
}
