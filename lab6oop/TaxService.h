#pragma once
#include "Car.h"
#include "CountryHouse.h"
#include <string>
#include <vector>
#include "Owner.h"
#include <iostream>
#include"json.hpp"

class TaxService:public Ijsonio, public Ixmlio
{
private:
	vector<Owner> owners;

public:
	inline void setOwners(vector<Owner> arr) { this->owners = arr; }
	nlohmann::json toFile() override;
	void fromFile(nlohmann::json json) override;
	void fromFileXml(xml_node& doc) override;
	void toFileXml(xml_node& doc) override;
	void printXMl(string filename);
};

