#include "Appartment.h"

double Appartment::calculateTax()
{
    double tax;
    if (square < TAX_RATES::LIMIT_APPARTMENT_SQUARE) {
        tax = getWorth() * TAX_RATES::APPARTMENT_TAX;
    }
    else {
        tax = getWorth() * TAX_RATES::APPARTMENT_LUXURY_TAX;
    }
    return tax;
}

nlohmann::json Appartment::toFile()
{
    json obj;
    obj["Appartment"] = calculateTax();

    return obj;
}

void Appartment::fromFile(nlohmann::json js)
{
    this->square = js["square"].get<double>();
    unsigned int worth_ = js["worth"].get<unsigned int>();
    this->setWorth(worth_);

}

void Appartment::fromFileXml(xml_node& doc)
{
    double square = stod(doc.child_value("square"));
    int worth = stoi(doc.child_value("worth"));
    setWorth(worth);
    secondParam(square);
}

void Appartment::toFileXml(xml_node& doc)
{
    xml_node prop = doc.append_child("Appartment");
    prop.text().set(to_string(calculateTax()).c_str());
}
