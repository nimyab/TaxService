#pragma once
#include "Property.h"
#include"json.hpp"

class Car :
    public Property
{
private:
    double horsepower=0;

public:
    Car() {}
    Car(unsigned int worth, double horsepower) :Property(worth) {
        this->horsepower = horsepower;
    }
    double calculateTax() override;
    void setHorsepower(double hp) { this->horsepower = hp; }
    nlohmann::json toFile() override;
    string getNameProp()override { return "Car"; }
    void fromFile(nlohmann::json json) override;
    void secondParam(double value) override;
    void fromFileXml(xml_node& doc)override;
    void toFileXml(xml_node& doc)override;
};

