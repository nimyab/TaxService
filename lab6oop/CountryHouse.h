#pragma once
#include "Property.h"
#include"json.hpp"

using namespace TAX_RATES;

class CountryHouse :
    public Property
{
private:
    unsigned int distanceFromCity=0;

public:
    CountryHouse() {}
    CountryHouse(unsigned int worth, unsigned int distance_From_City): Property(worth) {
        this->distanceFromCity = distance_From_City;
    }
    double calculateTax() override;
    string getNameProp()override { return "CountryHouse"; }
    nlohmann::json toFile() override;
    void fromFile(nlohmann::json json) override;
    void secondParam(double value) override { this->distanceFromCity = value; }
    void fromFileXml(xml_node& doc)override;
    void toFileXml(xml_node& doc)override;
};

