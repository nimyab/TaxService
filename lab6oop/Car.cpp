#include "Car.h"

double Car::calculateTax()
{
    double tax;
    if (horsepower < TAX_RATES::LOW_HORSEPOWER) {
        tax = getWorth() * TAX_RATES::CAR_TAX;
    }
    else {
        if (horsepower < TAX_RATES::HIGH_HORSEPOWER) {
            tax = getWorth() * TAX_RATES::CAR_TRUCK_TAX;
        }
        else {
            tax = getWorth() * TAX_RATES::CAR_LUXURY_TAX;
        }
    }
    return tax;
}

nlohmann::json Car::toFile()
{
    json obj;
    obj["Car"] = calculateTax();

    return obj;
}

void Car::fromFile(nlohmann::json js)
{
    this->horsepower = js["horsepower"].get<double>();
    unsigned int worth_ = js["worth"].get<unsigned int>();
    this->setWorth(worth_);
}

void Car::secondParam(double value)
{
    this->horsepower = value;
}

void Car::fromFileXml(xml_node& doc)
{
    double horsepower = stod(doc.child_value("horsepower"));
    int worth = stoi(doc.child_value("worth"));
    setWorth(worth);
    secondParam(horsepower);
}

void Car::toFileXml(xml_node& doc)
{
    xml_node prop = doc.append_child("Car");
    prop.text().set(to_string(calculateTax()).c_str());
}
