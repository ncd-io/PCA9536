#include "PCA9536.h"

PCA9536::PCA9536() : timer(100, &PCA9536::momentaryOff, *this, true) {}
PCA9536::~PCA9536(){}

void PCA9536::init(bool outputsOff){
	init();
	writeByte(PCA9536_OUTPUT_REG, 0);
}

void PCA9536::init(){
	begin();
	writeByte(PCA9536_POLARITY_REG, polarity);
	writeByte(PCA9536_CONFIG_REG, inputs);
}

void PCA9536::setPortPolarity(int port, bool invert){
	if(invert) polarity |= (1 << port);
	else polarity &= ~(1 << port);
}

void PCA9536::setPortDirection(int port, bool is_input){
	if(is_input) inputs |= (1 << port);
	else inputs &= ~(1 << port);
}

bool PCA9536::readPortStatus(int port){
	readAllPorts();
	int portbit = (1 << port);
	return ((portbit & input_status) == (portbit & ~polarity));
}

int PCA9536::readAllPorts(){
	input_status = readByte(PCA9536_INPUT_REG);
	return input_status;
}

void PCA9536::setOutput(int port, bool on){
	readAllPorts();
	if(on) writeByte(PCA9536_OUTPUT_REG, input_status | (1 << port));
	else writeByte(PCA9536_OUTPUT_REG, input_status & ~(1 << port));
}

void PCA9536::momentary(int port){
	momentary(port, 100);
}

void PCA9536::momentary(int port, int duration){
	if(momentary_active){
		timer.stop();
		momentaryOff();
	}
	momentary_port = port;
	momentary_active = true;
	setOutput(momentary_port, true);
	timer.changePeriod(duration);
    timer.start();
}

void PCA9536::momentaryOff(){
	setOutput(momentary_port, false);
	momentary_active = false;
}

void PCA9536::begin(){
	if(!Wire.isEnabled()) Wire.begin();
}

int PCA9536::readByte(int reg){
	writeByte(reg, 256);
	Wire.requestFrom(address, 1);
	return Wire.read();
}

void PCA9536::writeByte(int reg, int data){
	Wire.beginTransmission(address);
	Wire.write(reg);
	if(data < 256) Wire.write(data);
	Wire.endTransmission();
}
