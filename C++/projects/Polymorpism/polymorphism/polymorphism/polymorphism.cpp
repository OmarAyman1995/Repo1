/*
* Author		: Omar Ayman
* Date			: 4th June 2024
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
	MCU(int RAMsizeInkb);
	MCU();
	virtual ~MCU();
	MCU(const MCU& DistMcuToCopy);
	int getRAMsizeInKb(void);
	void setRAMsizeInKb(int newSizeOfRAM);
	int getFLASHsizeInKb(void);
	void setFLASHsizeInKb(int newSizeOfFLASH);
	int getBusWidthInKb(void);
	virtual void showMyNameClass(void);
private:
	int RAMsizeInkb;
	int FLASHsizeInKb;
protected: /* accessible from Base calss itself, from derived classes
		   , not accessible from obects of base or derived classes*/
	int BusWidth = 32;

};

class PIC16F :public MCU
{
	//using MCU::MCU;  //--> this will make derived class able to use the base constructors/Distructors
public:
	PIC16F();
	~PIC16F()override;
	PIC16F(const PIC16F& DistPic16fToCopy);
	virtual int getRAMsizeInKb(void) final;
	int getBusWidthInKb(void);

	 bool IsEUSARTmoduleExisted(void);
	void setEUSARTmodule(bool EUSARTmodule);

	void showMyNameClass(void)override;
private:
	bool EUSART;
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
		there are two types of polymorphisms 
		1- compile time - static ( functions/operators overloading)
		2- RUN time / dynamic binding  

		the two methods you want to dynamically bind should have the exactly same signature,
		otherwise it will be redefinintion not overriding

		abstract classes : are classes we are not able to instintiate objects from them 
		, they are contains at least one pure virtual function!
	*/
	

	MCU* mcu1 = new PIC16F();
	mcu1->showMyNameClass();

	delete mcu1;

}

MCU::MCU(int RAMsizeInkb)
	:RAMsizeInkb{ 10 }, FLASHsizeInKb{ 32 }
{
	this->RAMsizeInkb = RAMsizeInkb;
	std::cout << "this is the constructor of the Base (MCU) class !" << std::endl;
}

MCU::MCU()
	:RAMsizeInkb{ 10 }, FLASHsizeInKb{ 32 }
{

	std::cout << "this is the constructor of the Base (MCU) class !" << std::endl;
}

MCU::~MCU()
{
	std::cout << "this is the Destructor of the Base (MCU) class !" << std::endl;
}

MCU::MCU(const MCU & DistMcuToCopy)
	:RAMsizeInkb{ DistMcuToCopy.RAMsizeInkb }, FLASHsizeInKb{ DistMcuToCopy.FLASHsizeInKb }, BusWidth{ DistMcuToCopy.BusWidth }
{
	std::cout << "this is the Copy Constructor of the Base (MCU) class !" << std::endl;
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

int MCU::getBusWidthInKb(void)
{
	return 32;
}

void MCU::showMyNameClass(void)
{
	std::cout << "this is the MCU Class ! " << std::endl;
}

PIC16F::PIC16F()
{
	this->BusWidth = 8;
	std::cout << "this is the constructor of the Derived (PIC16F) class !" << std::endl;
}

PIC16F::~PIC16F()
{
	std::cout << "this is the Destructor of the Derived (PIC16F) class !" << std::endl;
}
PIC16F::PIC16F(const PIC16F & DistPic16fToCopy)
	:MCU(DistPic16fToCopy)
{
	this->EUSART = DistPic16fToCopy.EUSART;
	std::cout << "this is the Copy Constructor of the Derived (PIC16F) class !" << std::endl;
}


int PIC16F::getRAMsizeInKb(void)
{
	return 100;
}

int PIC16F::getBusWidthInKb(void)
{
	return this->BusWidth;
}

bool PIC16F::IsEUSARTmoduleExisted(void)
{
	return this->EUSART;
}

void PIC16F::setEUSARTmodule(bool EUSART)
{
	this->EUSART = EUSART;
}

void PIC16F::showMyNameClass(void)
{
	std::cout << "this is the PIC16F Class ! " << std::endl;
}
