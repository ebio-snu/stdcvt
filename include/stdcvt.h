/*
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file stdcvt.h
 @date 2018-03-24, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for Standard Converter
 refer from: https://github.com/ebio-snu/stdcvt
*/

#ifndef _STD_CVT_
#define _STD_CVT_

#include <iostream>

#include <boost/dll/import.hpp> 
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpath/json_query.hpp>

#include <glog/logging.h>

class StdConverter {
private:
    boost::shared_ptr<CvtDriver> _ssdriver;
    vector<boost::shared_ptr<CvtDriver>> _dsdrivers;
    boost::asio::io_service *_pio;

    boost::asio::deadline_timer _timer;

public:
    StdConverter(boost::asio::io_service& io, 
            boost::shared_ptr<CvtDriver> ssdriver,
            vector<boost::shared_ptr<CvtDriver>> dsdrivers)
        : _timer(io, boost::posix_time::seconds(1)) {

        _pio = &io;
        _ssdriver = ssdriver;
        _dsdrivers = dsdrivers;
        _timer.async_wait(boost::bind(&StdConverter::timer, this));
    }

    ~StdConverter() {
    }

    void sharedevice (CvtDevice *pdev, unsigned int drvidx) {
        bool ret;
        for (unsigned int i = 0; i < _dsdrivers.size(); i++) {
            if (i != drvidx)  {
                ret = _dsdrivers[i]->sharedevice (pdev);
                LOG(INFO) << "  DSDriver " << i << " : " 
                    << (ret ? "shared" : "not shared");
            }
        }
        ret = _ssdriver->sharedevice (pdev);
        LOG(INFO) << "  SSDriver : " << (ret ? "shared" : "not shared");
    }

    void execute() {
        // share device
        LOG(INFO) << "Sharing devices...";
        for (unsigned int i = 0; i < _dsdrivers.size(); i++) {
            CvtDevice *pdev;
            LOG(INFO) << "DSDriver " << i << " : "<< _dsdrivers[i]->getmodel();
            for (unsigned int j = 0; (pdev = _dsdrivers[i]->getdevice(j)) != nullptr; j++) {
                LOG(INFO) << "  Device : " << pdev->tostring();
                sharedevice (pdev, i);
            }
        }
        
        // control
        CvtCommand *pcmd = _ssdriver->getcommand ();

        if (pcmd) {
            LOG(INFO) << "Sending Commands ...";

            do {
                LOG(INFO) << "Command : " << pcmd->getid();
                for (unsigned int i = 0; i < _dsdrivers.size(); i++) {
                    bool ret = _dsdrivers[i]->control (pcmd);
                    LOG (INFO) << "  DSDriver " << i << " : "
                        << (ret ? "received " : "not received");
                }
            } while ((pcmd = _ssdriver->getcommand ()) != nullptr);
        }
    }

    void timer() {
        execute ();
        resettimer ();
    }

    void resettimer () {
        //_pio->stop ();
        //++_count;
        _timer.expires_at(_timer.expires_at() + boost::posix_time::seconds(1));
        _timer.async_wait(boost::bind(&StdConverter::timer, this));
    }
};

#endif
