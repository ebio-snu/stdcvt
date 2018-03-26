/*
 Copyright © 2018 ebio lab. SNU. All Rights Reserved.

 @file stdcvt.cpp
 @date 2018-03-24, JoonYong
 @author Kim, JoonYong <tombraid@snu.ac.kr>

 This file is for standard converter.
 refer from: https://github.com/ebio-snu/stdcvt
*/

#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <errno.h>

#include <iostream>

#include <boost/dll/import.hpp>
#include <boost/asio.hpp>
#include <glog/logging.h>

#include <cvtdriver.h>

using namespace std;
using namespace stdcvt;

namespace dll = boost::dll;

#include "stdcvt.h"

void
daemonize () {
    int x;
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);

    /* On success: The child process becomes session leader */
    if (setsid() < 0)
        exit(EXIT_FAILURE);

    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);
    if (pid > 0)
        exit(EXIT_SUCCESS);

    umask(0);

    /* Close all open file descriptors */
    for (x = sysconf(_SC_OPEN_MAX); x > 0; x--) {
        //close (x);
    }

    int pidf = open("/var/run/stdcvt.pid", O_CREAT | O_RDWR, 0666);
    if (flock(pidf, LOCK_EX | LOCK_NB) == -1) {
        LOG (FATAL) << "Another instance is running.";
    } else {
        char pids[10];
        int n = sprintf (pids, "%d\n", getpid ());
        LOG (INFO) << "Process ID : " << getpid ();
        write (pidf, pids, n);
    }
    close (pidf);
}

boost::shared_ptr<CvtDriver>
loaddriver(json driver, void *pio) {
    boost::shared_ptr<CvtDriver> pdriver;

    string driverfile = driver["driver"].as<string>();

    CvtOption option(driver["option"]);
    option.setobject (CVT_OPTION_ASIO_SERVICE, pio);

    LOG(INFO) << "Loading Driver : " << driver["driver"].as<string>();

    pdriver = dll::import<CvtDriver>(driverfile, "plugin",                
                    dll::load_mode::append_decorations);

    pdriver->initialize (option);

    LOG(INFO) << "A driver loadded : " << pdriver->getcompany () << " "
        << pdriver->getmodel() << " " << pdriver->getversion ();

    return pdriver;
}

void
execute (string conffile) {
    boost::asio::io_service io_service;
    ifstream is(conffile);
    json config = json::parse(is);

    boost::shared_ptr<CvtDriver> ssdriver;
    vector<boost::shared_ptr<CvtDriver>> dsdrivers;

    json driver = config["ssdriver"][0];
    ssdriver = loaddriver (driver, (void *)(&io_service));

    for (unsigned int i = 0; i < config["dsdriver"].size(); i++) {
        driver = config["dsdriver"][i];
        dsdrivers.push_back (loaddriver (driver, (void *)(&io_service)));
    }

    StdConverter stdcvt(io_service, config["stdcvt"], ssdriver, dsdrivers);
    io_service.run();

    ssdriver->finalize ();
    for (unsigned int i = 0; i < dsdrivers.size(); i++) {
        dsdrivers[i]->finalize ();
    }
}

int
main (int argc, char **argv) {
    int dflag = 0;
    char *conffile = (char *)"../conf/stdcvt.json";
    int c;

    FLAGS_log_dir = "/var/log/stdcvt";
    FLAGS_max_log_size = 10;
    FLAGS_logbufsecs = 0;
    google::InitGoogleLogging (argv[0]);

    opterr = 0;
    while ((c = getopt (argc, argv, "c:d")) != -1) {
        switch (c) {
            case 'd':
                dflag = 1;
                break;
            case 'c':
                conffile = optarg;
                break;
            case '?':
                if (optopt == 'c')
                    LOG(ERROR) << "Option -" << optopt << " requires an argument.";
                else if (isprint (optopt))
                    LOG(ERROR) << "Unknown Option -" << optopt << ".";
                else
                    LOG(ERROR) << "Unknown Option -" << (int)optopt << ".";
                return 1;
            default:
                abort ();
        }
    }

    if (dflag)
        daemonize ();

    execute (conffile);

    return 0;
}

