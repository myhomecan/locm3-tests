#include <stdio.h>

#include <atom.h>
#include <atomport-private.h>
#include <atomtimer.h>

#include "maple-mini.h"

#define STACK_SIZE      1024
#define THREAD_PRIO     42

static ATOM_TCB main_tcb;
static ATOM_TCB usart_tcb;
static uint8_t thread_stacks[3][STACK_SIZE];
static void main_thread_func(uint32_t data);
static void usart_thread_func(uint32_t data);

int main(void) {
  int8_t status;

  board_setup();

  status = atomOSInit(&thread_stacks[0][0], STACK_SIZE, FALSE);

  if (status == ATOM_OK) {
    atomThreadCreate(&main_tcb, THREAD_PRIO, main_thread_func, 0,
                     &thread_stacks[1][0], STACK_SIZE, TRUE);

    atomThreadCreate(&usart_tcb, 50, usart_thread_func, 0,
                     &thread_stacks[2][0], STACK_SIZE, TRUE);

    atomOSStart();
  }

  while (1);
  return 0;
}

static void main_thread_func(uint32_t data __maybe_unused) {
  while (1) {
    led_toggle();
    atomTimerDelay(SYSTEM_TICKS_PER_SEC >> 2);
  }
}

char buf[16];
size_t recv;

static void usart_thread_func(uint32_t data __maybe_unused) {
  while (1) {
    _write(0, "Hi!\n", 4);
    recv = _read(0, buf, 5);
    _write(0, "You say: ", 9);
    _write(0, buf, 5);
    _write(0, "\n", 1);
  }
}
