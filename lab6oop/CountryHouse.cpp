#include "CountryHouse.h"

double CountryHouse::calculateTax()
{
    double tax;
    if (distanceFromCity < LIMIT_DISTANCE_FROM_CITY) {
        tax = getWorth() * APPARTMENT_TAX;
    }
    else {
        tax = getWorth() * COUNTRY_HOUSE_TAX;
    }
    return tax;
}

nlohmann::json CountryHouse::toFile()
{
    json obj;
    obj["CountryHouse"] = calculateTax();

    return obj;
}

void CountryHouse::fromFile(nlohmann::json js)
{
    this->distanceFromCity = js["distanceFromCity"].get<unsigned int>();
    unsigned int worth_ = js["worth"].get<unsigned int>();
    this->setWorth(worth_);
}

void CountryHouse::fromFileXml(xml_node& doc)
{
    double distanceFromCity = stod(doc.child_value("distanceFromCity"));
    int worth = stoi(doc.child_value("worth"));
    setWorth(worth);
    this->distanceFromCity = distanceFromCity;
    
}

void CountryHouse::toFileXml(xml_node& doc)
{
    xml_node prop = doc.append_child("CountryHouse");
    prop.text().set(to_string(calculateTax()).c_str());
}
