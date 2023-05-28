#pragma once
#include "json.hpp"
#include "../pugixml-1.13/src/pugixml.hpp"

using namespace std;
using nlohmann::json;
using namespace pugi;

class Ijsonio
{
public:
	virtual void fromFile(nlohmann::json json) = 0;
	virtual nlohmann::json toFile() = 0;
	virtual ~Ijsonio() {}
};

class Ixmlio
{
public:
	virtual void fromFileXml(xml_node& doc) = 0;
	virtual void toFileXml(xml_node& doc) = 0;
	virtual ~Ixmlio() {}
};