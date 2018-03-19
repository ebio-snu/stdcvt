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
#include <DHT.h>
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
    virtual int getdeviceid (unsigned int idx) = 0;
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


#define NUMOFSENSOR 2
#define DHTPIN      4

class SensorObserver : public Controller {
private:
    int value[NUMOFSENSOR];
    int stat[NUMOFSENSOR];
    DHT *pdht;

public:
    SensorObserver () : Controller () {
        pdht = new DHT(DHTPIN, DHT22);
        stat[0] = stat[1] = 1;
        value[0] = value[1] = 1;
    }

	void setup () {
        pdht->begin();
	}

    int getnumber () {
		return NUMOFSENSOR;
	}

    int getdeviceid (unsigned int idx) {
        if (idx < NUMOFSENSOR)
            return SENSOR_ID + idx;
        return 0;
	}

    int hasdeviceid (int devid) {
        if ((devid >= SENSOR_ID) 
            && (devid < SENSOR_ID + NUMOFSENSOR))
			return 1;
		else
			return 0;
	}

    int getstatus (int devid) {
        if ((devid >= SENSOR_ID) 
            && (devid < SENSOR_ID + NUMOFSENSOR))
			return stat[devid - SENSOR_ID];
		else
			return 0;
	}

    int setstatus (int devid, int status) {
        if ((devid >= SENSOR_ID) 
            && (devid < SENSOR_ID + NUMOFSENSOR)) {
        	stat[devid - SENSOR_ID] = status;
            return status;
        } else {
            return 0;
        }
	}

    int getvalue (int devid) {
        if ((devid >= SENSOR_ID) 
            && (devid < SENSOR_ID + NUMOFSENSOR))
		    return value[devid - SENSOR_ID];
        else
            return 0;
	}

    int control (HardwareSerial *serial, char *buf) {
        return 0;
	}

    int stop (int devid) {
		return 0;
	}

	void process () {
        value[0] = (int)(pdht->readHumidity() * 10);
        value[1] = (int)(pdht->readTemperature() * 10);
	}

    void getmessage (char *buf, int size) {
        snprintf(buf, size, "^s %d %d.%d %d$^s %d %d.%d %d$", 
                SENSOR_ID, value[0]/10, value[0]%10, stat[0],
                SENSOR_ID+1, value[1]/10, value[1]%10, stat[1]);
    }
};

#define NUMOFMOT    2

class MotorController : public Controller {
private:
	int current[NUMOFMOT];
	int command[NUMOFMOT];
	int stat[NUMOFMOT];

public:
    MotorController () : Controller () {
    }

	void setup () {
		current[0] = current[1] = 0;
		command[0] = command[1] = 0;
		stat[0] = stat[1] = 0;
	}

    int getnumber () {
		return NUMOFMOT;
	}

    int getdeviceid (unsigned int idx) {
		if ((idx >= 0) && (idx < NUMOFMOT))
			return MOTOR_ID + idx;
		else
			return 0;
	}

    int hasdeviceid (int devid) {
		if ((devid >= MOTOR_ID) 
            && (devid < MOTOR_ID))
			return 1;
		else
			return 0;
	}

    int getstatus (int devid) {
		if ((devid >= MOTOR_ID) 
            && (devid < MOTOR_ID + NUMOFMOT))
			return stat[devid - MOTOR_ID];
		else
			return 0;
	}

    int setstatus (int devid, int status) {
		if ((devid >= MOTOR_ID) 
            && (devid < MOTOR_ID + NUMOFMOT)) {
			stat[devid - MOTOR_ID] = status;
			return status;
        } else {
            return 0;
        }
	}

    int getvalue (int devid) {
		if ((devid >= MOTOR_ID) 
            && (devid < MOTOR_ID + NUMOFMOT))
            return current[devid - MOTOR_ID];
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

		if ((devid >= MOTOR_ID) 
            && (devid < MOTOR_ID + NUMOFMOT)) {

            int idx = devid = MOTOR_ID;

            if (cmd == -1) {
                stat[idx] = 0;
            } else {
                if (current[idx] > cmd) { //close
                    stat[idx] = 2;
                } else if (current[idx] < cmd) { // open
                    stat[idx] = 1;
                } else { // error
                    stat[idx] = 0;
                }
                command[idx] = cmd;
            }
            SENDOK(serial);
		    return 1;
        } else {
            return 0;
        }
	}

    int stop (int devid) {
		if ((devid >= MOTOR_ID) 
            && (devid < MOTOR_ID + NUMOFMOT)) 
		    stat[devid - MOTOR_ID] = 0;
		return 0;
	}

	void process () {
        for (int i = 0; i < NUMOFMOT; i++) {
            if (stat[i] == 1 && current[i] < command[i]) // open
                current[i] ++;
            else if (stat[i] == 2 && current[i] > command[i]) // close
                current[i] --;	
            else
                stat[i] = 0;
        }
	}

    void getmessage (char *buf, int size) {
        snprintf(buf, size, "^m %d %d %d %d$^m %d %d %d %d$", 
                MOTOR_ID, current[0], command[0], stat[0],
                MOTOR_ID + 1, current[1], command[1], stat[1]);
    }
};

#define NUMOFSWC    2

class SwitchController : public Controller {
private:
	int stat[NUMOFSWC];

public:
    SwitchController () : Controller () {
    }

	void setup () {
		stat[0] = stat[1] = 0;
	}

    int getnumber () {
		return NUMOFSWC;
	}

    int getdeviceid (unsigned int idx) {
		if ((idx >= 0) && (idx < NUMOFSWC))
			return SWITCH_ID + idx;
		else
			return 0;
	}

    int hasdeviceid (int devid) {
		if ((devid >= SWITCH_ID)
            && (devid < SWITCH_ID + NUMOFSWC))
			return 1;
		else
            return 0;
    }

    int getstatus (int devid) {
		if ((devid >= SWITCH_ID)
            && (devid < SWITCH_ID + NUMOFSWC))
			return stat[devid - SWITCH_ID];
		else
			return 0;
	}

    int setstatus (int devid, int status) {
		if ((devid >= SWITCH_ID)
            && (devid < SWITCH_ID + NUMOFSWC)) {
			stat[devid - SWITCH_ID] = status;
        	return status;
        } else {
            return 0;
        }
	}

    int getvalue(int devid) {
		if ((devid >= SWITCH_ID)
            && (devid < SWITCH_ID + NUMOFSWC))
		    return stat[devid - SWITCH_ID];
        else
            return 0;
	}

    int control (HardwareSerial *serial, char *buf) {
        INFO(serial, "switch control");
        INFO(serial, buf);

        if (setbuf (buf) != 'w')
            return 0;

        int devid = getnext();
        int cmdid = getnext();
        int cmd = getnext();

		if ((devid >= SWITCH_ID)
            && (devid < SWITCH_ID + NUMOFSWC)) {
            stat[devid - SWITCH_ID] = cmd;
            SENDOK(serial);
            return 1;
        } else {
			return 0;
        }
	}

    int stop (int devid) {
		if ((devid >= SWITCH_ID)
            && (devid < SWITCH_ID + NUMOFSWC)) 
		    stat[devid - SWITCH_ID] = 0;
		return 0;
	}

	void process () {
	}

    void getmessage (char *buf, int size) {
        snprintf(buf, size, "^w %d %d$^w %d %d$", 
                SWITCH_ID, stat[0], SWITCH_ID + 1, stat[1]);
    }
};

#endif
