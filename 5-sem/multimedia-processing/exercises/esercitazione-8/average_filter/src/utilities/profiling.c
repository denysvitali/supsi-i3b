#include "profiling.h"

#include <stdio.h>
#include <limits.h>

#if defined(_WIN32)
#include <windows.h>
#include <tchar.h>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4996) // _CRT_SECURE_NO_WARNINGS
#endif


#else
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <sys/vtimes.h>
#endif

/************************************************************************************************
* Profile
************************************************************************************************/

static void profile_start(profile_t *p) {
	profileTime_setCurrentTicks(p->_start);
}

static void profile_reset(profile_t *p) {
	profileTime_init(p->_start);
	profileTime_init(p->_stop);
}

static double profile_stop(profile_t *p) {
	profileTime_setCurrentTicks(p->_stop);
	if (profileTime_isSet(p->_start)) {
		profileTime_t tmp = p->_stop;
		profileTime_sub(tmp, p->_start);
		return profileTime_getMilliseconds(tmp);
	}
	return 0.0;
}

static double profile_lap(profile_t *p) {
	if (profileTime_isSet(p->_start)) {
		profileTime_setCurrentTicks(p->_start);
		return 0.0;
	}
	else {
		profileTime_t tmp;
		profileTime_setCurrentTicks(p->_stop);
		tmp = p->_stop;
		profileTime_sub(tmp, p->_start);
		p->_start = p->_stop;
		return profileTime_getMilliseconds(tmp);
	}
}

static double profile_elapsed(profile_t *p) {
	profileTime_t tmp;
	profileTime_setCurrentTicks(tmp);
	profileTime_sub(tmp, p->_start);
	return profileTime_getMilliseconds(tmp);
}

profile_t* profile_init() {
	profile_t *p = (profile_t*)malloc(sizeof(profile_t));

	p->reset = profile_reset;
	p->start = profile_start;
	p->stop = profile_stop;
	p->lap = profile_lap;
	p->elapsed = profile_elapsed;

	profileTime_init(p->_start);
	profileTime_init(p->_stop);
	return p;
}

void profile_dispose(profile_t* profile) {
	free(profile);
}

/************************************************************************************************
* Profile Stats
************************************************************************************************/
static void profileStats_printf(profileStats_t* p, int header, int newline) {
	if (header)
		printf("(min,avg,max,cnt,tot)\t");

	if (p->cnt <= 0)
		printf("%.6f\t%.6f\t%.6f\t%u\t%.6f", 0.0, 0.0, 0.0, 0, 0.0);
	else
		printf("%.6f\t%.6f\t%.6f\t%u\t%.6f", p->min, (p->tot / (double)p->cnt), p->max, p->cnt, p->tot);

	if (newline)
		printf("\n");
}

static void profileStats_sprintf(profileStats_t* p, char* str, int header, int newline) {
	char tmp[512];
	str[0] = '\0';
	if (header)
		sprintf(str, "(min,avg,max,cnt,tot)\t");

	if (p->cnt <= 0) {
		sprintf(tmp, "%.6f\t%.6f\t%.6f\t%u\t%.6f", 0.0, 0.0, 0.0, 0, 0.0);
		strcat(str, tmp);
	} else {
		sprintf(tmp, "%.6f\t%.6f\t%.6f\t%u\t%.6f", p->min, (p->tot / (double)p->cnt), p->max, p->cnt, p->tot);
		strcat(str, tmp);
	}

	if (newline)
		strcat(str, "\n");
}

static double profileStats_getAvg(profileStats_t *p) {
	return p->cnt == 0 ? 0.0 : p->tot / (double)p->cnt;
}

static void profileStats_add(profileStats_t* p, double value) {
	if (value <= 0.0)
		return;
	if (p->min > value)
		p->min = value;
	if (p->max < value)
		p->max = value;
	p->cur = value;
	p->tot += value;
	p->cnt++;
}

static void profileStats_reset(profileStats_t* p) {
	p->min = (double)INT_MAX;
	p->max = (double)-INT_MAX;
	p->tot = 0.0;
	p->cnt = 0;
	p->cur = 0.0;
}

profileStats_t* profileStats_init() {
	profileStats_t *p = (profileStats_t*)malloc(sizeof(profileStats_t));

	p->min = (double)INT_MAX;
	p->max = (double)-INT_MAX;
	p->tot = 0.0;
	p->cnt = 0;

	p->printf = profileStats_printf;
	p->sprintf = profileStats_sprintf;
	p->add = profileStats_add;
	p->reset = profileStats_reset;
	p->getAvg = profileStats_getAvg;

	return p;
}

void profileStats_dispose(profileStats_t* profile) {
	free(profile);
}


#if defined(_MSC_VER)
#pragma warning(pop)
#endif
