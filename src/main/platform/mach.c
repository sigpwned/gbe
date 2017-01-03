#ifdef __MACH__

#include <time.h>
#include <sys/time.h>
#include <mach/mach.h>
#include <mach/clock.h>
#include <mach/mach_time.h>

/**
 * @see https://github.com/ChisholmKyle/PosixMachTiming
 ******************************************************************************/
#define CLOCK_REALTIME 0
#define CLOCK_MONOTONIC 1

/* mach clock port */
extern mach_port_t clock_port;

static struct TimingMach {
  mach_timebase_info_data_t timebase;
  clock_serv_t cclock;
} timing_mach_g;

int timing_mach_init(void) {
  int retval = mach_timebase_info(&timing_mach_g.timebase);
  if (retval != 0) return retval;
  retval = host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &timing_mach_g.cclock);
  return retval;
}

int mach_clock_gettime(int id, struct timespec *tspec) {
  mach_timespec_t mts;
  int retval = 0;
  if (id == CLOCK_REALTIME) {
    retval = clock_get_time(timing_mach_g.cclock, &mts);
    if (retval != 0) return retval;
    tspec->tv_sec = mts.tv_sec;
    tspec->tv_nsec = mts.tv_nsec;
  } else if (id == CLOCK_MONOTONIC) {
    retval = clock_get_time(clock_port, &mts);
    if (retval != 0) return retval;
    tspec->tv_sec = mts.tv_sec;
    tspec->tv_nsec = mts.tv_nsec;
  } else {
    /* only CLOCK_MONOTOIC and CLOCK_REALTIME clocks supported */
    return -1;
  }
  return 0;
}

/******************************************************************************/

void gbe_setup() {
  timing_mach_init();
}

void gbe_cleanup() {
}

void gbe_gettime(struct timespec* tp) {
  mach_clock_gettime(CLOCK_MONOTONIC, tp);
}

#endif
