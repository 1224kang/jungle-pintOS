/* Checks that when the alarm clock wakes up threads, the
   higher-priority threads run first. */

#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

static thread_func alarm_priority_thread;
static int64_t wake_time;
static struct semaphore wait_sema;

void
test_alarm_priority (void) 
{
  int i;
  
  /* This test does not work with the MLFQS. */
  ASSERT (!thread_mlfqs);

  wake_time = timer_ticks () + 5 * TIMER_FREQ; //지금부터 5초 뒤
  sema_init (&wait_sema, 0);
  
  for (i = 0; i < 10; i++) //우선순위가 섞인 스레드 10개 생성
    {
      int priority = PRI_DEFAULT - (i + 5) % 10 - 1;
      char name[16];
      snprintf (name, sizeof name, "priority %d", priority);
      thread_create (name, priority, alarm_priority_thread, NULL);
    }

  thread_set_priority (PRI_MIN); //main이 우선순위를 0으로 낮춤

  for (i = 0; i < 10; i++)
    sema_down (&wait_sema);
}

/*
 * 10개 스레드 각각이 실행하는 코드  
 */
static void
alarm_priority_thread (void *aux UNUSED) 
{
  /* 틱이 바뀔 때까지 바쁜 대기 */
  int64_t start_time = timer_ticks ();
  while (timer_elapsed (start_time) == 0) 
    continue;

  /* 타이머 틱이 막 시작된 시점이므로 다음 틱까지 여유 충분 -> 계산 도중 틱이 바뀔 걱정없음 */
  timer_sleep (wake_time - timer_ticks ()); //wake_time까지 잠듦

  /* Print a message on wake-up. */
  msg ("Thread %s woke up.", thread_name ());

  sema_up (&wait_sema);
}
