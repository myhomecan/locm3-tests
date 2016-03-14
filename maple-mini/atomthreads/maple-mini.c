#include <stdbool.h>
#include <stdint.h>

#include <libopencm3/cm3/cortex.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>

#include <atomport.h>

#include "maple-mini.h"

#define STD_CON USART2



static void clock_setup(void) {
  rcc_clock_setup_in_hse_8mhz_out_72mhz();
}

static void led_setup(void) {
  rcc_periph_clock_enable(RCC_GPIOB);

  gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO1);

  gpio_set(GPIOB, GPIO1);
}

static void usart_setup(uint32_t baud) {
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_AFIO);
  rcc_periph_clock_enable(RCC_USART2);

  usart_disable(USART2);

  gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL,
                GPIO_USART2_TX);

  gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO_USART2_RX);

  usart_set_baudrate(USART2, baud);
  usart_set_databits(USART2, 8);
  usart_set_stopbits(USART2, USART_STOPBITS_1);
  usart_set_parity(USART2, USART_PARITY_NONE);
  usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);
  usart_set_mode(USART2, USART_MODE_TX_RX);

  usart_enable(USART2);
}

static void systick_setup(void) {
  systick_set_frequency(SYSTEM_TICKS_PER_SEC, 72000000);
  systick_interrupt_enable();
  systick_counter_enable();
}

int board_setup(void) {
  cm_mask_interrupts(true);

  clock_setup();
  led_setup();
  usart_setup(115200);

  systick_setup();

  nvic_set_priority(NVIC_PENDSV_IRQ, 0xFF);
  nvic_set_priority(NVIC_SYSTICK_IRQ, 0xFE);

  return 0;
}

void led_set(void) {
  gpio_set(GPIOB, GPIO1);
}

void led_clear(void) {
  gpio_clear(GPIOB, GPIO1);
}

void led_toggle(void) {
  gpio_toggle(GPIOB, GPIO1);
}
