#pragma once
#include "Property.h"
#include "Appartment.h"
#include "Car.h"
#include "CountryHouse.h"
#include <string>
#include <vector>
#include <iostream>
#include"Ijsonio.h"
#include"json.hpp"

using namespace std;

class Owner : public Ijsonio,public Ixmlio
{
private:
	string fullname;
	string inn;
	vector<Property*> properties;

public:
	inline void setName(string fullname) { this->fullname = fullname; }
	inline void setInn(string inn) { this->inn = inn; }
	inline string getName() { return fullname; }
	inline string getInn() { return inn; }
	inline vector<Property*> getProp() { return properties; }
	inline void printProperty() {
		for (int i = 0; i < properties.size(); i++) {
			cout << (*properties[i]).getWorth() << " ";
		}
		cout << endl;
	}
	Owner(string fullname, string inn):fullname(fullname), inn(inn) {}
	Owner() :fullname(""), inn("") {}
	inline void addProperty(Property* property) {
		properties.push_back(property);
	}
	inline void deleteProperty() {
		properties.pop_back();
	}
	inline double calculateTax() {
		double tax=0;
		for (int i = 0; i < properties.size(); i++) {
			tax += (*properties[i]).calculateTax();
		}
		return tax;
	}

	nlohmann::json toFile() override;
	void fromFile(nlohmann::json json) override;
	void fromFileXml(xml_node& doc)override;
	void toFileXml(xml_node& doc)override;
};

class PropertyFactoryMethod
{
public:
	inline static Property* getProperty(std::string key) {
		if (key == "Appartment") {
			return new Appartment();
		}
		if (key == "Car") {
			return new Car();
		}
		if (key == "CountryHouse") {
			return new CountryHouse();
		}
	}
};

