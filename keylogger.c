#include "keylogger.h"

time_t timeSinceLastKeypress;
long keyPressesSinceLastWrite;
const time_t idleTimeToWaitBeforeFileWrite = 5; // we wait 5 seconds
const char *numberLocation = "/tmp/keyCounter";
int isRunning = 0;
pthread_t workThread;

void *writeToFile();
int isIdle();
void uglyPrint(char *string);

int main(int argc, const char *argv[]) {
  timeSinceLastKeypress = 0;
  keyPressesSinceLastWrite = 0;
  // Create an event tap to retrieve keypresses
  CGEventMask eventMask =
      (CGEventMaskBit(kCGEventKeyDown) | CGEventMaskBit(kCGEventFlagsChanged));
  CFMachPortRef eventTap =
      CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0, eventMask,
                       CGEventCallback, NULL);

  // Exit the program if unable to create the event tap.
  if (!eventTap) {
    fprintf(stderr, "ERROR: Unable to create event tap.\n");
    exit(1);
  }
  // Start workthread
  isRunning = 1;
  uglyPrint("starting threadf");
  int err = pthread_create(&workThread, NULL, writeToFile, NULL);
  if (err) {
    uglyPrint("Thread error");
  }

  // Create a run loop source and add enable the event tap.
  CFRunLoopSourceRef runLoopSource =
      CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
  CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource,
                     kCFRunLoopCommonModes);
  CGEventTapEnable(eventTap, true);

  CFRunLoopRun();

  return 0;
}

// The following callback method is invoked on every keypress.
CGEventRef CGEventCallback(CGEventTapProxy proxy, CGEventType type,
                           CGEventRef event, void *refcon) {
  if (type != kCGEventKeyDown && type != kCGEventFlagsChanged &&
      type != kCGEventKeyUp) {
    return event;
  }
  time_t tempTime = time(NULL);
  timeSinceLastKeypress = tempTime;
  ++keyPressesSinceLastWrite;
  fprintf(stderr, "%lu\n", keyPressesSinceLastWrite);

  return event;
}

void *writeToFile() {
  uglyPrint("we are starting");
  while (isRunning) {
    uglyPrint("we are running");
    sleep(1); // check every 1 second if we are idle?
    if (isIdle() || keyPressesSinceLastWrite == 0) {
      FILE *fp = fopen(numberLocation, "r");
      long buff[1]; // we only need one long
      fscanf(fp, "%lu", buff);
      long newCount = buff[0] + keyPressesSinceLastWrite;
      keyPressesSinceLastWrite = 0;
      fprintf(stderr, "%lu\n", newCount);
      fp = fopen(numberLocation, "w");
      fprintf(fp, "%lu", newCount);
      fflush(fp);
      fclose(fp);
    }
  }
  return NULL;
}

int isIdle() {
  time_t tempTime = time(NULL);
  time_t timeDiff = tempTime - timeSinceLastKeypress;
  if (timeDiff > idleTimeToWaitBeforeFileWrite) {
    return 1;
  } else {
    return 0;
  }
}

void uglyPrint(char *string) { fprintf(stderr, "%s", string); }
