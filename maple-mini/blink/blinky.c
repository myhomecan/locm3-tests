#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#ifdef STM32F1
#  define LED_PORT GPIOB
#  define LED_PIN GPIO1
#  define LED_RCC RCC_GPIOB
#endif

static void _delay_ms(const uint32_t delay) {
  uint32_t i, j;

  for (i = 0; i < delay; i++)
    for (j = 0; j < 1000; j++)
      __asm__("nop");
}

int main(void) {
  rcc_periph_clock_enable(LED_RCC);
  gpio_set_mode(LED_PORT, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, LED_PIN);

  while (1) {
    gpio_set(LED_PORT, LED_PIN);
    _delay_ms(500);
    gpio_clear(LED_PORT, LED_PIN);
    _delay_ms(1000);
  }
  return 0;
}
