#pragma once
#include"json.hpp"
#include"Ijsonio.h"

namespace TAX_RATES
{
	const double CAR_TAX = 0.0007;
	const double CAR_TRUCK_TAX = 0.007;
	const double CAR_LUXURY_TAX = 0.027;
	const double APPARTMENT_TAX = 0.001;
	const double APPARTMENT_LUXURY_TAX = 0.004;
	const double COUNTRY_HOUSE_TAX = 0.01;

	const double LOW_HORSEPOWER = 100;
	const double HIGH_HORSEPOWER = 200;
	const unsigned int LIMIT_DISTANCE_FROM_CITY = 30;
	const int LIMIT_APPARTMENT_SQUARE = 100;
}

class Property:public Ijsonio, public Ixmlio
{
private:
	unsigned int worth;

public:
	Property() { this->worth=0; }
	inline Property(unsigned int worth) { this->worth = worth; }
	inline unsigned int getWorth() { return worth; }
	inline void setWorth(unsigned int worth){ this->worth = worth; }
	virtual double calculateTax() = 0;
	virtual string getNameProp() = 0;
	virtual void secondParam(double value) = 0;
	double calculateIncomeTax() {
		return worth * 0.13;
	}
	virtual ~Property() {}
	
};

