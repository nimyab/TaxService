#include "Owner.h"

nlohmann::json Owner::toFile()
{
    nlohmann::json object;
    object["fullname"] = fullname;
    object["inn"] = inn;
    double sumtax = 0;
    for (int i = 0; i < properties.size(); i++) {
        sumtax += properties[i]->calculateTax();
    }
    object["sumtax"] = sumtax;
    vector<json> propert;
    for (int i = 0; i < properties.size(); i++) {

        propert.push_back(properties[i]->toFile());
    }
    object["taxs"] = propert;
    return object;
}

void Owner::fromFile(nlohmann::json js)
{
    this->fullname = js["fullname"].get<string>();
    this->inn = js["inn"].get<string>();
    vector<json> propert = js["properties"].get<vector<json>>();
    
    for (json prop : propert) {
        string key = prop.items().begin().key();
        Property* object = PropertyFactoryMethod::getProperty(key);
        json j = prop[key].get<json>();
        object->fromFile(j);
        this->properties.push_back(object);
    }
}

void Owner::fromFileXml(xml_node& doc)
{
    string fullname = doc.attribute("fullname").as_string();
    string inn = doc.attribute("inn").as_string();
    this->fullname = fullname;
    this->inn = inn;
    for (xml_node pr : doc.children("properties")) {
        string prop = pr.attribute("prop").as_string();
        Property* property = PropertyFactoryMethod::getProperty(prop);
        property->fromFileXml(pr);
        addProperty(property);
    }
}

void Owner::toFileXml(xml_node& doc)
{
    xml_node owner_node = doc.append_child("Owner");

    xml_attribute attrName = owner_node.append_attribute("fullname");
    attrName.set_value(fullname.c_str());

    xml_attribute attrInn = owner_node.append_attribute("inn");
    attrInn.set_value(inn.c_str());

    xml_node sumtax = owner_node.append_child("sumtax");
    sumtax.text().set(to_string(calculateTax()).c_str());

    xml_node tax = owner_node.append_child("tax");
    for (int i = 0; i < properties.size(); i++)
        properties[i]->toFileXml(tax);
}
