#include "myDefs.h"
#if MILESTONE_1==1
#ifndef LCD_TASK_H
#define LCD_TASK_H
#include "FreeRTOS.h"
#include "queue.h"
#include "timers.h"

// NOTE: This is a reasonable API definition file because there is nothing in it that the
//   user of the API does not need (e.g., no private definitions) and it defines the *only*
//   way a user of the API is allowed to interact with the task


// Define a data structure that is used to pass and hold parameters for this task
// Functions that use the API should not directly access this structure, but rather simply
//   pass the structure as an argument to the API calls
typedef struct __vtLCDStruct {
	xQueueHandle inQ;					   	// Queue used to send messages from other tasks to the LCD task to print
} vtLCDStruct;

// Added by Matthew Ibarra 2/2/2013
// This defines the width and height of the LCD screen
#define WIDTH 320;
#define HEIGHT 240;

// Structure used to define the messages that are sent to the LCD thread
//   the maximum length of a message to be printed is the size of the "buf" field below
#define vtLCDMaxLen 20

// actual data structure that is sent in a message
typedef struct __vtLCDMsg {
	uint8_t msgType;
	uint8_t	length;	 // Length of the message to be printed
	uint8_t buf[vtLCDMaxLen+1]; // On the way in, message to be sent, on the way out, message received (if any)
} vtLCDMsg;
// end of defs

/* ********************************************************************* */
// The following are the public API calls that other tasks should use to work with the LCD task
//   Note: This is *not* the API for actually manipulating the graphics -- that API is defined in GLCD.h
//         and is accessed by the LCD task (other tasks should not access it or conflicts may occur).
//
// Start the task
// Args:
//   lcdData -- a pointer to a variable of type vtLCDStruct
//   uxPriority -- the priority you want this task to be run at
void StartLCDTask(vtLCDStruct *lcdData,unsigned portBASE_TYPE uxPriority);
//
// Send a timer message to the LCD task
// Args:
//   lcdData -- a pointer to a variable of type vtLCDStruct
//   ticksElapsed -- number of ticks since the last message (this will be sent in the message)
//   ticksToBlock -- how long the routine should wait if the queue is full
// Return:
//   Result of the call to xQueueSend()
portBASE_TYPE SendLCDTimerMsg(vtLCDStruct *lcdData,portTickType ticksElapsed,portTickType ticksToBlock);
// Send a string message to the LCD task for it to print
// Args:
//   lcdData -- a pointer to a variable of type vtLCDStruct
//   length -- number of characters in the string -- the call will result in a fatal error if you exceed the maximum length
//   pString -- string to print to the LCD
//   ticksToBlock -- how long the routine should wait if the queue is full
// Return:
//   Result of the call to xQueueSend()
portBASE_TYPE SendLCDPrintMsg(vtLCDStruct *lcdData,int length,char *pString,portTickType ticksToBlock);

// Send an integer message to the LCD task for it to output to the LCD screen as a point in the waveform
// Args:
//	 lcdData -- a pointer to a variable of type vtLCDStruct
//	 data -- the integer value that will be plotted
//	 ticksToBlock -- how long the routine should wait if the queue is full
// Return:
//	 Result of the call to xQueueSend()
portBASE_TYPE SendLCDADCMsg(vtLCDStruct *lcdData,int data,portTickType ticksToBlock);
/* ********************************************************************* */


void LCDTimerCallback(xTimerHandle);

#endif
#endif