#include "Particle.h"

#define PCA9536_INPUT_REG 0x00
#define PCA9536_OUTPUT_REG 0x01
#define PCA9536_POLARITY_REG 0x02
#define PCA9536_CONFIG_REG 0x03

class PCA9536{
public:
	PCA9536();
	virtual ~PCA9536();
	int polarity = 0;
	int inputs = 15;
	int input_status = 0;

	void init();
	void init(bool outputsOff);

	void setPortPolarity(int port, bool invert);
	void setPortDirection(int port, bool is_input);
	bool readInputStatus(int port);
	int readAllInputs();

	void setOutput(int port, bool on);
	void momentary(int port);
	void momentary(int port, int duration);
private:
	Timer timer;
	int address = 0x41;
	int momentary_port;
	int momentary_active = false;
	void momentaryOff();

	int readByte(int reg);
	void writeByte(int reg, int data);
	void begin();
};
