/*
* Author		: Omar Ayman
* Date			: 27th MAY 2024
* Copyrights	: omar.ayman@crewteq.com
*
*
* do NOT use this for adding history to track you code edits,
* use the version control instead (GIT)
*/

#include <iostream>
#include <string>
#include <vector>

/* the base class */
class MCU
{
	public:
		MCU();
		~MCU();
		int getRAMsizeInKb(void);
		void setRAMsizeInKb(int newSizeOfRAM);
		int getFLASHsizeInKb(void);
		void setFLASHsizeInKb(int newSizeOfFLASH);
	private:
		int RAMsizeInkb;
		int FLASHsizeInKb;
	protected:
};

class PIC16F :public MCU
{
	public:
		int getRAMsizeInKb(void);
	private:
	protected:
};

class STM32F103 :public MCU
{
	public:
	private:
	protected:
};

int main()
{
    /*
		providing new classes from existing one
		focusing the common att and features of the existing classes 
		it is to reuse mechanism 
		Base class : is the class being inherited from 
		Derived class : the class being created from the Base class
		its a relationship 
		what is difference between composition and inheritance ?
		both allow reuse of existing classes 
		inh is a relationship 
		comp has a relationship
	*/
	PIC16F PIC16F877A;
	PIC16F877A.setRAMsizeInKb(5);
	std::cout << "size of RAM : " << PIC16F877A.getRAMsizeInKb() << "kb" << std::endl;
	std::cout << "size of FLASH : " << PIC16F877A.getFLASHsizeInKb() << "kb" << std::endl;
}

MCU::MCU()
	:RAMsizeInkb{10}, FLASHsizeInKb{32}
{
}

MCU::~MCU()
{
	/*do nothing*/
}

int MCU::getRAMsizeInKb(void)
{
	return RAMsizeInkb;
}

void MCU::setRAMsizeInKb(int newSizeOfRAM)
{
	RAMsizeInkb = newSizeOfRAM;
}

int MCU::getFLASHsizeInKb(void)
{
	return FLASHsizeInKb;
}

void MCU::setFLASHsizeInKb(int newSizeOfFLASH)
{
	FLASHsizeInKb = newSizeOfFLASH;
}

int PIC16F::getRAMsizeInKb(void)
{
	return 100;
}
