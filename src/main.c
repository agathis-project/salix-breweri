#include<avr/io.h>
#include<util/delay.h>
////////////////////////////////////////////////////////////////////////////////
void sleep(uint8_t millisec) {
  while(millisec) {
    _delay_ms(1);  // 1 ms delay
    millisec--;
  }
}
////////////////////////////////////////////////////////////////////////////////
inline void clock_init() {
  CCP = CCP_IOREG_gc;
  OSC.CTRL = OSC_RC32MEN_bm;
  while(!(OSC.STATUS & OSC_RC32MRDY_bm));

  CCP = CCP_IOREG_gc;
  CLK.CTRL = CLK_SCLKSEL_RC32M_gc;
}
////////////////////////////////////////////////////////////////////////////////
inline void IO_init() {
  // ==PORTB==
  // PIN3 - GPIO.10 - initial 0
  // PIN4 - GPIO.1 - initial 0
  // PIN6 - GPIO.2 - initial 0
  // PIN7 - GPIO.9 - initial 0
  PORTB.DIRSET = (PIN3_bm | PIN4_bm | PIN6_bm | PIN7_bm);
  PORTC.OUTCLR = (PIN3_bm | PIN4_bm | PIN6_bm | PIN7_bm);

  // ==portC==
  // PIN4 - XTST-MCU.GPIO1 - initial 1
  // PIN5 - WARMRSTn - initial 0
  // PIN7 - GPIO.0 - initial0
  PORTC.DIRSET = (PIN4_bm | PIN5_bm | PIN7_bm);
  PORTC.OUTSET = PIN4_bm;
  PORTC.OUTCLR = (PIN5_bm | PIN7_bm);

  // ==PORTD==
  // PIN3 - HUBCTRL.EN - initial 0
  // PIN4 - GPIO.3 - initial 0
  // PIN5 - GPIO.11 - initial 0
  PORTD.DIRSET = (PIN3_bm | PIN4_bm |PIN5_bm);
  PORTD.OUTCLR = (PIN3_bm | PIN4_bm |PIN5_bm);

  // ==PORTE==
  // PIN1 - MSYNC3M - initial 1
  // PIN3 - EN-VUSBIN - initial 1
  // PIN6 - EN-SDCARD - initial 0
  PORTE.DIRSET = (PIN1_bm | PIN3_bm | PIN6_bm);
  PORTE.OUTSET = (PIN1_bm | PIN3_bm);
  PORTE.OUTCLR = PIN6_bm;

  // ==PORTF==
  // PIN0 - BRANCH-CTRL.TRIG - initial 0
  // PIN1 - BRANCH-CTRL.INTSn - initial 0
  // PIN2 - BRANCH-CTRL.INTGn - initial 0
  // PIN3 - DBLR-CLK - initial 0
  // PIN4 - BRANCH-CTRL.A1 - initial 0
  // PIN5 - EN-VUSBOUT - initial 0
  // PIN6 - EN-PWRCLK - initial 0
  // PIN7 - USB-SW-CTRL.USB-TO-CPU - initial 0
  PORTF.DIRSET = 0xFF;
  PORTF.OUTCLR = 0xFF;

  // ==PORTH==
  // PIN0 - USB-SW-CTRL.SWEN - initial 0
  // PIN1 - ETHCTRL-e2.EN - initial 0
  // PIN3 - HUBCTRL.RSTn - initial 0
  // PIN4 - USB0.ID - initial 0
  // PIN5 - BRANCH-CTRL.ENn - initial 0
  // PIN6 - BRANCH-CTRL.A2 - initial 0
  PORTH.DIRSET = (PIN0_bm | PIN1_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm);
  PORTH.OUTCLR = (PIN0_bm | PIN1_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm);

  // ==PORTJ==
  // PIN0 - EN-V1P8 - initial 0
  // PIN1 - EN-eMMC - initial 0
  // PIN5 - ETHCTRL-e1.EN - initial 0
  // PIN7 - EN-VCORE - initial 0
  PORTJ.DIRSET = (PIN0_bm |PIN1_bm | PIN5_bm | PIN7_bm);
  PORTJ.OUTCLR = (PIN0_bm |PIN1_bm | PIN5_bm | PIN7_bm);

  // ==PORTK==
  // PIN2 - BRANCH-CTRL.A0 - initial 0
  // PIN3 - PWRONRSTn - initial 0
  // PIN4 - QB.0 - initial 0
  // PIN5 - QB.1 - initial 0
  // PIN6 - QC.0 - initial 1
  // PIN7 - QC.1 - initial 0
  PORTK.DIRSET = (PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN6_bm | PIN7_bm);
  PORTK.OUTSET = PIN6_bm;
  PORTK.OUTCLR = (PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm | PIN7_bm);

  // ==PORTQ==
  // PIN2 - VSEL - initial 0
  // PIN3 - GPIO.8 - initial 0
  PORTQ.DIRSET = (PIN2_bm | PIN3_bm);
  PORTQ.OUTCLR = (PIN2_bm | PIN3_bm);

  // ==PORTR==
  // PIN0 - EN-V3P3 - initial 0
  // PIN1 - WP - initial 0
  PORTR.DIRSET = (PIN0_bm | PIN1_bm);
  PORTR.OUTCLR = (PIN0_bm | PIN1_bm);
}
////////////////////////////////////////////////////////////////////////////////
void uP_pwr_up() {
  //enable V18P
  PORTJ.OUTSET = PIN0_bm;
  sleep(2);
  //enable V3P3
  PORTR.OUTSET = PIN0_bm;
  sleep(2);
  //enable VCORE
  PORTJ.OUTSET = PIN7_bm;
}
////////////////////////////////////////////////////////////////////////////////
void uP_pwr_down() {
  //disable VCORE
  PORTJ.OUTCLR = PIN7_bm;
  sleep(2);
  //disable V3P3
  PORTR.OUTCLR = PIN0_bm;
  sleep(2);
  //disable V18P
  PORTJ.OUTCLR = PIN0_bm;
}
////////////////////////////////////////////////////////////////////////////////
int main(void) {
  //clock_init();
  IO_init();

  //sleep(10);
  uP_pwr_up();
  //sleep(100);
  //uP_pwr_down();

  while(1) {
    sleep(100);
    PORTC.OUTTGL = PIN4_bm;

    sleep(100);
    PORTC.OUTTGL = PIN4_bm;
  }
}
