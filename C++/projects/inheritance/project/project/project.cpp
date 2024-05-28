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
		MCU(int RAMsizeInkb);
		MCU();
		~MCU();
		MCU(const MCU& DistMcuToCopy);
		int getRAMsizeInKb(void);
		void setRAMsizeInKb(int newSizeOfRAM);
		int getFLASHsizeInKb(void);
		void setFLASHsizeInKb(int newSizeOfFLASH);
		int getBusWidthInKb(void);

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
		~PIC16F();
		PIC16F(const PIC16F& DistPic16fToCopy);
		int getRAMsizeInKb(void);
		int getBusWidthInKb(void);

		bool IsEUSARTmoduleExisted(void);
		void setEUSARTmodule(bool EUSARTmodule);
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


		A deriv class does NOT inherit Base class constructors
		A deriv class does NOT inherit Base class Destructor
		A deriv class does NOT inherit Base class friend functions
		A deriv class does NOT inherit Base class overloaded assigment operators 
		However, the derived class constructors ,dest,overloaded can invok the base class versions
		f
	*/
	PIC16F PIC16F877A;
	PIC16F877A.setRAMsizeInKb(5);
	PIC16F877A.setEUSARTmodule(true);
	PIC16F PIC18F4550{ PIC16F877A };

	std::cout << "for PIC16f877a :: size of RAM : " << PIC16F877A.getRAMsizeInKb() << "kb" << std::endl;
	std::cout << "for PIC16f877a :: size of FLASH : " << PIC16F877A.getFLASHsizeInKb() << "kb" << std::endl;
	std::cout << "for PIC16f877a :: bus Width : " << PIC16F877A.getBusWidthInKb() << "bits" << std::endl;
	
	std::cout << "for PIC18f4550 :: size of RAM : " << PIC18F4550.getRAMsizeInKb() << "kb" << std::endl;
	std::cout << "for PIC18f4550 :: size of FLASH : " << PIC18F4550.getFLASHsizeInKb() << "kb" << std::endl;
	std::cout << "for PIC18f4550 :: bus Width : " << PIC18F4550.getBusWidthInKb() << "bits" << std::endl;

}

MCU::MCU(int RAMsizeInkb)
	:RAMsizeInkb{10}, FLASHsizeInKb{32}
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
	:RAMsizeInkb{DistMcuToCopy.RAMsizeInkb},FLASHsizeInKb{DistMcuToCopy.FLASHsizeInKb},BusWidth{DistMcuToCopy.BusWidth}
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
