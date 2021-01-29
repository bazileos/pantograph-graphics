#include "Serial.hpp"

void Serial::setPort(std::string p) {
	portString = p;
}

void Serial::read() {

	// opening serial port
	asio::io_service io;
	asio::serial_port port(io);
	port.open(portString);
	port.set_option(asio::serial_port_base::baud_rate(115200));

	// getting response string (until \n character)
	rsp = "";
	do {
		asio::read(port, asio::buffer(&c, 1));
		rsp += c;
	} while (c != '\n');

	port.close();

	outputFile << rsp; // log to output file

	rsp.erase(std::remove(rsp.begin(), rsp.end(), '\n'), rsp.end());

	// extracting coordinates from response
	pos = 0;
	isEffectorPos = false;
	isBallPos = false;
	coordCount = 0;
	while ((pos = rsp.find(delimiter)) != std::string::npos) {
		item = rsp.substr(0, pos);
		recordCoordinate(item);

		if (item == "e") {
			isBallPos = false;
			isEffectorPos = true;
			coordCount = 0;
		}
		if (item == "b") {
			isBallPos = true;
			isEffectorPos = false;
			coordCount = 0;
		}

		rsp.erase(0, pos + delimiter.length());
	}
	recordCoordinate(rsp);
}

void Serial::recordCoordinate(std::string item) {
	if (isEffectorPos && coordCount == 0) effectorX = std::stof(item);
	if (isEffectorPos && coordCount == 1) effectorY = std::stof(item);
	if (isBallPos && coordCount == 0) ballX = std::stof(item);
	if (isBallPos && coordCount == 1) ballY = std::stof(item);
	coordCount++;
}

void Serial::openOutputFile() {
	std::time_t t = std::time(0);
	outputFile.open("output_"+std::to_string(t)+".csv", std::ios_base::app);
}

Serial::~Serial() {
	outputFile.close();
}