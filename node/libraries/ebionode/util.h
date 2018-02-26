/**
 * Copyright © 2018 EBIO Lab. SNU. 
 * All Rights Reserved.
 *
 * \file util.h
 * \brief 아두이노 코드를 위한 간단한 유틸 정의
 */

#ifndef _UTIL_H_
#define _UTIL_H_

#define DELIM			","
#define BUFSIZE     	64
#define SMASK			'^'
#define EMASK			'$'
#define DEFAULT_TERM	10000

#ifdef _DEBUG_
  #define SENDOK(serial) {serial->write (SMASK); serial->write (EMASK); serial->write('\n'); serial->flush ();}
  #define WRITE(serial,buf) {serial->write (buf); serial->write('\n'); serial->flush ();}
  #define INFO(serial,buf)  {serial->write (buf); serial->write('\n'); serial->flush ();}
#else
  #define SENDOK(serial) {serial->write (SMASK); serial->write (EMASK); serial->flush ();}
  #define WRITE(serial,buf) {serial->write (buf); serial->flush ();}
  #define INFO(serial,buf)  
#endif


void reset () {
#if defined(__SAM3X8E__)
    REQUEST_EXTERNAL_RESET;
#else
    void (*resetfunc)(void) = 0;
    resetfunc ();
#endif
}

#endif
