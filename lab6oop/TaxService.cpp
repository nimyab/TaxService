#include "TaxService.h"

nlohmann::json TaxService::toFile()
{
    json obj;
    vector<json> owners_tax;
    for (int i = 0; i < owners.size(); i++) {
        owners_tax.push_back(owners[i].toFile());
    }
    obj["TaxOwnres"] = owners_tax;
    return obj;
}

void TaxService::fromFile(nlohmann::json js)
{
    vector<json> _owners = js["Owners"].get<vector<json>>();
    for (json _owner : _owners) {
        Owner owner;
        owner.fromFile(_owner);
        this->owners.push_back(owner);
    }
}



void TaxService::fromFileXml(xml_node& doc)
{
    vector<Owner> owner;
    for (xml_node node : doc.child("Owners").children("Owner")) {
        Owner own;
        own.fromFileXml(node);
        owner.push_back(own);
    }
    this->owners = owner;
}

void TaxService::toFileXml(xml_node& doc)
{
    for (Owner owner : this->owners)//ошибка была здесь, только на строчку выше, я создавал поле owners в поле owners, щас 23 38 я как плавленный сыр))
        owner.toFileXml(doc);
}

void TaxService::printXMl(string filename)
{
    xml_document docOut;
    xml_node node = docOut.append_child("Owners");
    toFileXml(node);
    docOut.save_file(filename.c_str());

}