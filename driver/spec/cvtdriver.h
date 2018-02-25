/**
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file cvtdriver.h
 @date 2018-02-24, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is template of CvtDriver.
 refer from: https://github.com/ebio-snu/stdcvt
*/

#ifndef _CVT_DRIVER_
#define _CVT_DRIVER_

namespace stdcvt {

/*
 @brief CvtDriver is a virtual class for a converter driver.
*/
virtual class CvtDriver {
private:
    int _modelcode;         //< 모델코드. 회사코드에 개별모델의 번호를 합하여 만든다.
    int _apispec;            //< 적용API버전. API 버전에 따라 메소드구성에 차이가 있을 수 있다.

public:
    /**
     새로운 드라이버를 생성한다.
     @param modelcode 모델코드
     @param apispec API 버전
    */
    CvtDriver(int modelcode, int apispec) {
        _modelcode = modelcode;
        _apispec = apispec;
    }

    ~CvtDriver();

    /**
     드라이버의 모델코드를 확인한다.
     @return 드라이버의 모델코드
    */
    int getmodelcode() {
        return _modelcode;
    }

    /**
     드라이버의 API 버전을 확인한다.
     @return 드라이버의 API 버전
    */
    int getapispec() {
        return _apispec;
    }

    /**
     드라이버 제작자가 부여하는 버전번호를 확인한다.
     컨버터에서는 해당 버전을 로깅용도로만 사용한다.
     문자열 비교를 통해 후순위가 더 높은 버전이 된다.
     @return 문자열 형식의 버전번호
    */
    virtual string getversion ();

    /**
     드라이버 제작자가 부여하는 모델번호를 확인한다.
     컨버터에서는 모델코드만 확인하고, 모델번호에 대해서는 로깅용도로만 사용한다.
     @return 문자열 형식의 모델번호
    */
    virtual string getmodel ();

    /**
     드라이버 제조사명을 확인한다.
     컨버터에서는 제조사명을 로깅용도로만 사용한다.
     @return 문자열 형식의 제조사명
    */
    virtual string getcompany ();

    /**
     드라이버를 초기화 한다. 드라이버 동작을 위한 option 은 key-value 형식으로 전달된다.
     @param option 드라이버동작을 위한 옵션
     @return 초기화 성공 여부
    */
    virtual bool initialize (CvtConfig option);

    /**
     드라이버를 종료한다.
     @return 종료 성공 여부
    */
    virtual bool finalize ();

    /**
     드라이버간 상태교환을 하기전에 호출되는 메소드로 전처리를 수행한다.
     @return 전처리 성공 여부
    */
    virtual bool preprocess ();

    /**
     드라이버간 상태교환이 이루어진 이후에 호출되는 메소드로 후처리를 수행한다.
     @return 후처리 성공 여부
    */
    virtual bool postprocess ();

    /**
     드라이버가 관리하고 있는 장비의 포인터를 꺼내준다.
     @param index 얻고자 하는 장비의 인덱스 번호. 0에서 시작한다.
     @return 인덱스에 해당하는 장비의 포인터. NULL 이라면 이후에 장비가 없다는 의미이다.
    */
    virtual CvtDevice *getdevice(int index);
};

} // namespace stdcvt

#endif
