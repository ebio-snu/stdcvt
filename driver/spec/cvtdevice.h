/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file cvtdevice.h
 @date 2018-02-24, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is template of CvtDevice.
 refer from: https://github.com/ebio-snu/stdcvt
*/

#ifndef _CVT_DEVICE_
#define _CVT_DEVICE_

namespace stdcvt {

/*
 @brief CvtDevice is a virtual class for a smartfarm device.
*/
virtual class CvtDevice {
private:
    int _id;                //< 장비 ID
    devtype_t _type;        //< 장비 종류
    devstat_t _status;      //< 장비 상태
    devsec_t _section;      //< 장비 설치 구역
    devtarget_t _target;    //< 장비의 대상

protected:
    /**
     아이디를 제외한 장비의 속성을 복사한다.
     @param pdev 복사할 소스 장비에 대한 포인터
    */
    bool copyproperites (CvtDevice *pdev) {
        _type = *pdev->_type;
        _status = *pdev->_status;
    }

public:
    /**
     새로운 장비를 생성한다.
     @param devid 장비의 아이디
     @param devtype 장비의 종류
     @param devstatus 장비의 상태
    */
    CvtDevice(int devid, devtype_t devtype, devstat_t devstatus) {
        _id = devid;
        _type = devtype;
        _status = devstatus;
    }

    ~CvtDevice();

    /**
     장비에 부여된 아이디를 리턴한다.
     @return 장비의 아이디
    */
    int getid() {
        return _id;
    }

    /**
     장비의 종류를 리턴한다.
     @return 장비의 종류
    */
    devtype_t gettype () {
        return _type;
    }

    /**
     장비의 상태를 리턴한다.
     @return 장비의 상태
    */
    devstat_t getstatus () {
        return _status;
    }

    /**
     장비의 상태를 세팅한다.
     @param devstatus 새로 세팅할 장비의 상태
     @return 세팅된 장비의 상태
    */
    devstat_t setstatus (devstat_t devstatus) {
        _status = devstatus;
        return _status;
    }

    /**
     장비의 상태를 전이하는데 사용되는 메소드이다.
     드라이버 제작자가 꼭 구현해야 하는 메소드이다.
     copyproperties 를 활용할 수 있다.
     @param pdev 소스 장비에 대한 포인터
     @return 상태전이의 성공여부로 true라면 성공이다.
    */
    virtual bool stream(CvtDevice *pdevice);
};

virtual class CvtSensor : public CvtDevice {
private:
    obsunit_t _unit;          //< 관측치의 단위
    double _value;            //< 센서의 관측치

public:

    /**
     새로운 센서를 생성한다.
     @param devid 센서의 아이디
     @param devstatus 센서의 상태
     @param unit 관측치의 단위
    */
    CvtSensor (int devid, devstat_t devstatus, obsunit_t unit) {
        CvtDevice (devid, DT_SENSOR, devstatus);
        _unit = unit;
    }

    /**
     관측치 단위를 읽는다.
     @return 관측치 단위
    */
    obsunit_t getunit () {
        return _unit;
    }

    /**
     관측치 단위를 세팅한다.
     @param unit 새로 세팅할 관측치 단위
     @return 관측치 단위
    */
    obsunit_t setunit (obsunit_t unit) {
        _unit = unit;
        return _unit;
    }

    /**
     관측치를 기록한다.
     @param value 관측치
     @return 기록한 관측치값
    */
    double writeobservation (double value) {
        _value = value;
        return _value;
    }

    /**
     관측치를 읽는다.
     @return 관측치값
    */
    double readobservation () {
        return _value;
    }

    /**
     장비의 상태를 전이하는데 사용되는 메소드이다.
     드라이버 제작자가 꼭 구현해야 하는 메소드이다.
     copyproperties 를 활용할 수 있다.
     @code

    bool stream(CvtDevice *pdevice) {
        CvtSensor *psensor = <static>(CvtSensor *)(pdevice);
        _unit = psensor->_unit;
        _value = psensor->_value;
        return copyproperites(pdevice);
    }
    */
};

} // namespace stdcvt
#endif
