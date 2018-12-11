/*
* profiling.h
*/
#ifndef PROFILING_H_
#define PROFILING_H_


#if defined(_WIN32)

#include <windows.h>

typedef LARGE_INTEGER profileTime_t;

static __inline double profileTime_getMilliseconds(profileTime_t ticks) {
	LARGE_INTEGER ticksPerSecond;
	QueryPerformanceFrequency(&ticksPerSecond);
	return ticks.QuadPart * 1000.0 / ticksPerSecond.QuadPart;
}

#define profileTime_setCurrentTicks(a)    QueryPerformanceCounter(&a)
#define profileTime_add(a, b)             (a).QuadPart += (b).QuadPart
#define profileTime_sub(a, b)             (a).QuadPart -= (b).QuadPart
#define profileTime_cmp(a, b, cmp)        ((a).QuadPart cmp (b).QuadPart)
#define profileTime_isSet(a)             ((a).QuadPart != 0)
#define profileTime_init(a)              (a).QuadPart = 0
#define profileTime_initMin(a)            (a).QuadPart = LLONG_MAX

#else
// LINUX

#include <time.h>

typedef struct timespec profileTime_t;

#define profileTime_getMilliseconds(a)    (1000.0 * (double) a.tv_sec + (double) a.tv_nsec / 1000000.0)
#define profileTime_setCurrentTicks(a)    clock_gettime(CLOCK_REALTIME, &a)
#define profileTime_add(a, b)\
     (a).tv_sec += (b).tv_sec;\
     (a).tv_nsec += (b).tv_nsec;\
     if ((a).tv_nsec >= 1000000000) {\
             (a).tv_sec++;\
             (a).tv_nsec -= 1000000000;\
     }

#define profileTime_sub(a, b)\
     (a).tv_sec -= (b).tv_sec;\
     (a).tv_nsec -= (b).tv_nsec;\
     if ((a).tv_nsec < 0) {\
             (a).tv_sec--;\
             (a).tv_nsec += 1000000000;\
     }

#define profileTime_isSet(a)    \
    ((a).tv_sec != 0 && (a).tv_nsec != 0)

#define profileTime_cmp(a, b, cmp)\
      (((a).tv_sec == (b).tv_sec) ?\
       ((a).tv_nsec cmp (b).tv_nsec) :\
       ((a).tv_sec cmp (b).tv_sec))

#define profileTime_init(a)\
        (a).tv_sec = 0;\
        (a).tv_nsec = 0

#define profileTime_initMin(a)\
        (a).tv_sec = LONG_MAX;\
        (a).tv_nsec = LONG_MAX
#endif


/************************************************************************************************
* Profile
************************************************************************************************/

typedef struct profile_t profile_t;
struct profile_t {
	profileTime_t _start;
	profileTime_t _stop;

	void(*start) (profile_t *profile);
	double(*stop) (profile_t *profile);
	double(*lap) (profile_t *profile);
	double(*elapsed) (profile_t *profile);
	void(*reset) (profile_t *profile);
};

/************************************************************************************************
* Profile Stats
************************************************************************************************/

typedef struct profileStats_t profileStats_t;
struct profileStats_t {
	double cur;
	double min;
	double max;
	double tot;
	unsigned int cnt;

	void(*printf) (profileStats_t *stats, int header, int newline);
	void(*sprintf) (profileStats_t *stats, char* str, int header, int newline);
	void(*add) (profileStats_t *stats, double time);
	void(*reset) (profileStats_t *stats);
	double(*getAvg)(profileStats_t *stats);
};



#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	// Profiling
	profile_t* profile_init();
	void profile_dispose(profile_t* profile);


	// Profiling stats
	profileStats_t* profileStats_init();
	void profileStats_dispose(profileStats_t* profile);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */


#endif /* PROFILING_H_ */
