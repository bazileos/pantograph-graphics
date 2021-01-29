#ifndef SERIAL_H
#define SERIAL_H

#include <iostream>
#include <string>
#include <boost/asio/serial_port.hpp> 
#include <boost/asio.hpp> 
#include <algorithm>
#include <fstream>
#include <ctime>
#include <Magnum/Math/Vector2.h>

typedef Magnum::Math::Vector2<Magnum::Float> Vector2;

using namespace boost;

/*
	Class for getting position data of objects through serial protocol.
*/
class Serial {
	std::string portString;
	std::ofstream outputFile;

	// temporary variables
	char c;
	std::string rsp;
	size_t pos;
	std::string item;
	std::string delimiter = ";";
	bool isEffectorPos;
	bool isBallPos;
	int coordCount;

	void recordCoordinate(std::string item);
public:
	// coordinates of objects
	float effectorX, effectorY, ballX, ballY;

	void setPort(std::string p);
	void read();
	void openOutputFile();
	~Serial();
};

#endif