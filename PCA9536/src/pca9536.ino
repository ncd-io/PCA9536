#include "Particle.h"
#include "PCA9536.h"

PCA9536 buzzer;

void setup() {
  	buzzer.setPortDirection(3, false);
	buzzer.init(true);

	Particle.variable("inputs", buzzer.input_status);
	Particle.function("buzzer", beep);
}

void loop() {
	buzzer.readAllInputs();
}

int beep(String cmd){
	int duration = cmd.toInt();
	if(duration == 0) buzzer.momentary(3);
	else buzzer.momentary(3, duration);
}
