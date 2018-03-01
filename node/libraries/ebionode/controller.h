/**
 * Copyright © 2018 EBIO Lab. SNU. 
 * All Rights Reserved.
 *
 * \file controller.h
 * \brief 센서, 모터, 스위치 가상 컨트롤러
 */

#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <util.h>

class Controller {
protected:
    virtual void getmessage (char *buf, int size) = 0;

    char setbuf(char *buf) {
		return *strtok(buf, DELIM);
    }

    int getnext() {
        return atoi (strtok (NULL, DELIM));
    }
    
public:
    Controller () {
    }

	virtual void setup () = 0;
    virtual int getnumber () = 0;
    virtual int getdeviceid (int idx) = 0;
    virtual int hasdeviceid (int devid) = 0;
    virtual int getstatus (int devid) = 0;
    virtual int setstatus (int devid, int status) = 0;
    virtual int getvalue (int devid) = 0;
    virtual int control (HardwareSerial *serial, char *buf) = 0;
    virtual int stop (int devid) = 0;
	virtual void process () = 0;

    void notify (HardwareSerial *serial) {
        char buf[BUFSIZE];
        getmessage (buf, BUFSIZE);
        WRITE(serial, buf);
    }
};


#define SENSOR_ID	10
#define MOTOR_ID	20
#define SWITCH_ID	30


#define ONE_WIRE_BUS	2

class SensorObserver : public Controller {
private:
    int value;
    int stat;
    OneWire *pwire;
    DallasTemperature *ptemp;

public:
    SensorObserver () : Controller () {
        pwire = new OneWire(ONE_WIRE_BUS);
        ptemp = new DallasTemperature(pwire);
        stat = 1;
    }

	void setup () {
        ptemp->begin();
	}

    int getnumber () {
		return 1;
	}

    int getdeviceid (int idx) {
		if (idx == 0)
			return SENSOR_ID;
		else
			return 0;
	}

    int hasdeviceid (int devid) {
		if (devid == SENSOR_ID)
			return 1;
		else
			return 0;
	}

    int getstatus (int devid) {
		if (devid == SENSOR_ID)
			return stat;
		else
			return 0;
	}

    int setstatus (int devid, int status) {
        if (devid == SENSOR_ID)
        	stat = status;
        return stat;
	}

    int getvalue (int devid) {
		return value;
	}

    int control (HardwareSerial *serial, char *buf) {
        return 0;
	}

    int stop (int devid) {
		return 0;
	}

	void process () {
        ptemp->requestTemperatures(); 
        value = (int)(ptemp->getTempCByIndex(0) * 10);
	}

    void getmessage (char *buf, int size) {
        snprintf(buf, size, "^s %d %d.%d %d$", SENSOR_ID, value/10, value%10, stat);
    }
};

class MotorController : public Controller {
private:
	int current;
	int command;
	int stat;

public:
    MotorController () : Controller () {
    }

	void setup () {
		current = 0;
		command = 0;
		stat = 0;
	}

    int getnumber () {
		return 1;
	}

    int getdeviceid (int idx) {
		if (idx == 0)
			return MOTOR_ID;
		else
			return 0;
	}

    int hasdeviceid (int devid) {
		if (devid == MOTOR_ID)
			return 1;
		else
			return 0;
	}

    int getstatus (int devid) {
		if (devid == MOTOR_ID)
			return stat;
		else
			return 0;
	}

    int setstatus (int devid, int status) {
        if (devid == MOTOR_ID)
	        stat = status;
        return stat;
	}

    int getvalue (int devid) {
		if (devid == MOTOR_ID)
            return current;
        else
		    return 0;
	}

    int control (HardwareSerial *serial, char *buf) {
        INFO(serial, "motor control");
        INFO(serial, buf);

        if (setbuf (buf) != 'm')
            return 0;

        int devid = getnext();
        int cmdid = getnext();
        int cmd = getnext();

		if (devid != MOTOR_ID)
			return 0;

        if (cmd == -1) {
            stat = 0;
        } else {
            if (current > cmd) { //close
				stat = 2;
			} else if (current < cmd) { // open
				stat = 1;
			} else { // error
				stat = 0;
			}
			command = cmd;
        }

        SENDOK(serial);
		return 1;
	}

    int stop (int devid) {
		stat = 0;
		return 0;
	}

	void process () {
		if (stat == 1 && current < command) // open
			current ++;
		else if (stat == 2 && current > command) // close
			current --;	
        else
            stat = 0;
	}

    void getmessage (char *buf, int size) {
        snprintf(buf, size, "^m %d %d %d %d$", MOTOR_ID, current, command, stat);
    }
};

class SwitchController : public Controller {
private:
	int stat;

public:
    SwitchController () : Controller () {
    }

	void setup () {
		stat = 0;
	}

    int getnumber () {
		return 1;
	}

    int getdeviceid (int idx) {
		if (idx == 0)
			return SWITCH_ID;
		else
			return 0;
	}

    int hasdeviceid (int devid) {
		if (devid == SWITCH_ID)
			return 1;
		else
            return 0;
    }

    int getstatus (int devid) {
		if (devid == SWITCH_ID)
			return stat;
		else
			return 0;
	}

    int setstatus (int devid, int status) {
        if (devid == SWITCH_ID)
        	stat = status;
        return stat;
	}

    int getvalue(int devid) {
		return stat;
	}

    int control (HardwareSerial *serial, char *buf) {
        INFO(serial, "switch control");
        INFO(serial, buf);

        if (setbuf (buf) != 'w')
            return 0;

        int devid = getnext();
        int cmdid = getnext();
        int cmd = getnext();

		if (devid != SWITCH_ID)
			return 0;

		stat = cmd;
        SENDOK(serial);
		return 1;
	}

    int stop (int devid) {
		stat = 0;
		return 0;
	}

	void process () {
	}

    void getmessage (char *buf, int size) {
        snprintf(buf, size, "^w %d %d$", SWITCH_ID, stat);
    }
};

#endif
