/**
*	Casper drive_server Header 
*	Author @Pontus Pohl and @Linus Eiderström Swahn
*/

#ifndef lidarserver_hpp
#define lidarserver_hpp

class sockethandler;
class lidarScanner;
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/UInt16.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <ostream>
#include <iostream>
#include <array>
#include <sqlite3.h>
#include <time.h>
// #include <SocketHandler.hpp>
// #include <serialhandler.hpp>


/**
* **** OUTGOING ****
*/
// HEADER FLAGS
#define HEADER_START 0x48
#define HEADER_WALL_FLAG 0x77
#define HEADER_OBSTACLE_FLAG 0x6f
#define HEADER_CAR_CLAG 0x63
// SUBPACKET FLAGS
#define WALL_START_FLAG 0x4c
#define OBSTACLE_START_FLAG 0x49
#define CAR_START_FLAG 
// END FLAGS
#define CARRIAGE_RETURN 0x0d
#define LINE_FEED 0x0a
#define END_OF_TRANSMISSION 0x04
/**
* **** INCOMMING ****
*/
#define MAP_REQUEST_START_FLAG 0x53
// OTHER
#define READ_BUF 21





typedef boost::shared_ptr<sockethandler> socket_handler_ptr;
typedef boost::shared_ptr<lidarScanner>  lidar_scanner_ptr;
class lidarserver{

private:    
    //serial_handler_ptr serialHandler;
    socket_handler_ptr socket_handler;
    lidar_scanner_ptr  lidar_scanner;     
    std::array<char,READ_BUF> read_buf;
    std::string token; 
    boost::asio::io_service io_service;
    std::string port;
    int baud_rate;
    char lidarStart[2];
    char lidarStop[2];
    int argc;
    char ** argv;
    std::string frame_id;
    static sqlite3 *sqlite_open();  
    int verifyToken(const char token[]) const;
    boost::thread service_thread;
    bool initialized = false;

public:
    lidarserver(void);
    lidarserver(const std::string port, int baud_r, int argc, char** argv);
    ~lidarserver();    
    int startPolling();
    int stopPolling();    
    int parseRequest(std::array<char,21> &buf, int len);
    int start();
    bool polling;

    
    
};









#endif // drive_server_hpp