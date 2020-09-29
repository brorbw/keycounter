#ifndef __KEYCOUNTER_H__
#define __KEYCOUNTER_H__

#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// https://developer.apple.com/library/mac/documentation/Carbon/Reference/QuartzEventServicesRef/Reference/reference.html

CGEventRef CGEventCallback(CGEventTapProxy, CGEventType, CGEventRef, void *);

#endif
