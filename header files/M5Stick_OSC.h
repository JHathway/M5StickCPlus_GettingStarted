//=========================================================
// File:   M5StickOSC.h
//
// Author: J Hathway 2023
//
// Dependencies:
//      - M5StickCPlus library (M5Stack)
//      - OSC library (Adrien Freed)
//
// This file contains functions for sending OSC messages 
// on M5Stick
//=========================================================

#ifndef JH_DBG
#define JH_DBG
#ifdef USING_SERIAL
#define LOG Serial
#else 
#define LOG M5.Lcd
#endif
#endif

#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>

WiFiUDP _udp;

const char *_udpAddress;
int _udpPort;

/// SendTo
/// - set IP address and port to send to
/// @param _address 
/// @param _port 
void sendTo(const char *_address, int _port)
{
    _udpAddress = _address;
    _udpPort = _port;

    LOG.println("Sending to:");
    LOG.println("IP: " + String(_udpAddress));
    LOG.printf("Port: %i", _udpPort);
}

/// SendOscMessage<T>
/// - template function for sending OSC messages
/// @param _route (const char*) message route
/// @param _message (T) message
template <typename T>
void sendOscMessage(const char *_route, T _message)
{
    // init message
    OSCMessage _oscMsg(_route);
    _oscMsg.add((T)_message);     

    // send message
    _udp.beginPacket(_udpAddress, _udpPort);
    _oscMsg.send(_udp);

    // clear message
    _udp.endPacket(); 
    _oscMsg.empty();   
}