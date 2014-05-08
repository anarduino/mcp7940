/*
 * mcp7940.h - library for mcp7940n RTC
 * This library is intended to be uses with Arduino Time.h library functions
 */

#ifndef MCP7940_H
#define MCP7940_H
#define MCP7940_CTRL_ID 0x6F 

#include "Arduino.h"

typedef uint8_t byte;

// library interface description
class mcp7940
{
  // user-accessible "public" interface
  public:
    mcp7940();
    time_t get();
    //static time_t getAlarm(int alarm);

	void set(time_t t);
	void setAlarm0(time_t t);
	void clearAlarm0();
	//static void setAlarm(int alarm, time_t t);
	//static void setAlarmCtl(int alarm, int params);

	void read(tmElements_t &tm);
	void write(tmElements_t &tm);
	void getDateStr(char *dateStr);
	
	uint8_t getSecond();
	uint8_t getMinute();
	uint8_t getHour();
	uint8_t getDay();
	uint8_t getDayOfWeek();
	uint8_t getMonth();
	uint8_t getYear();
	time_t getTimeRTC();
	void setTimeRTC(time_t t);

  private:
	uint8_t dec2bcd(uint8_t num);
    uint8_t bcd2dec(uint8_t num);
    void loadDT();
};

#endif
 

