#pragma once
#include "Property.h"
#include"json.hpp"

class Appartment :
    public Property
{
private:
    double square=0;

public:
    Appartment() {}
    Appartment(unsigned int worth, double square) :Property(worth) {
        this->square = square;
    }
    double calculateTax() override;
    nlohmann::json toFile() override;
    string getNameProp()override { return "Appartment"; }
    void fromFile(nlohmann::json json) override;
    void secondParam(double value) override { this->square = value; }
    void fromFileXml(xml_node& doc)override;
    void toFileXml(xml_node& doc)override;
};

