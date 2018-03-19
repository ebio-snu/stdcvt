/**
 * Copyright © 2018 EBIO Lab. SNU. 
 * All Rights Reserved.
 *
 * \file node.h
 * \brief Node 의 통신부를 맡고 있는 클래스
 */

#ifndef _NODE_H_
#define _NODE_H_

#include <util.h>
#include <controller.h>


class EbioNode {
protected:
	SensorObserver senobs;
	MotorController mtctrl;
	SwitchController swctrl;
    HardwareSerial *serial;

    void setupcontroller () {
        senobs.setup ();
		mtctrl.setup ();
		swctrl.setup ();
    }

public:
    EbioNode (HardwareSerial *serial) {
        this->serial = serial;
    }

    int getdisplayvalue (int i) {
        switch (i) {
            case 0:
                return senobs.getvalue(10);
            case 1:
                return senobs.getvalue(11);
            case 2:
                return swctrl.getstatus(30);
            case 3:
                return swctrl.getstatus(31);
            case 4:
                return mtctrl.getvalue(20);
            case 5:
                return mtctrl.getstatus(20);
            case 6:
                return mtctrl.getvalue(21);
            case 7:
                return mtctrl.getstatus(22);
            default:
                return 0;
        }
    }

    int process () {
        static unsigned long last = 0;
        unsigned long current = millis ();
               
        receive ();

        senobs.process();
        mtctrl.process();
        swctrl.process();

        if (current - last >= DEFAULT_TERM) {
            last = current;
            notify();
        }

        return 0;
    }

    void setup () {
        SENDOK(serial);

        setupcontroller ();
    }

    int notify () {
        senobs.notify (serial);
        mtctrl.notify (serial);
        swctrl.notify (serial);
    }

    int receive () {
        static char buf[BUFSIZE];
        static int n;

        while (serial->available () > 0) {
            buf[n] = serial->read ();
            if (buf[n] == SMASK) {
                n = 0;
            } else if (buf[n] == EMASK) {
                if (n == 0)  {  // receive init message
                    notify ();
                } else {
                    buf[n] = '\0';
                    if (buf[0] == 'm') {
                        mtctrl.control(serial, buf);
                    } else if (buf[0] == 'w') {
                        swctrl.control(serial, buf);
                    }
                    n = 0;
                }
            } else {
                n++;
            }
        }
        return 0;
    }
};

#endif

