#include <iostream>
#include "Owner.h"
#include "Car.h"
#include "Appartment.h"
#include "CountryHouse.h"
#include "Property.h"
#include <stdlib.h>
#include <fstream>
#include "TaxService.h"
#include "../pugixml-1.13/src/pugixml.hpp"

using namespace std;
using nlohmann::json;
using namespace pugi;

void menu() {
    cout << "1. добавить собственность " << endl
        << "2. добавить собственика " << endl
        << "3. удалить собственика из конца списка" << endl
        << "4. удалить собственность из конца списка" << endl
        << "5. посчитать общий налог налог" << endl
        << "6. запись в файл" << endl
        << "7. выпись из файла" << endl
        << "8. Вывод собственников в файл" << endl
        << "9. вывод в файл расчетов налогов собственников " << endl;
}



void printOwners(vector<Owner> owners) {
    for (int i = 0; i < owners.size(); i++) {
        cout << owners[i].getName()<<" " << owners[i].getInn() << endl;
    }
}

int main(int argc, char* argv[])
{
    setlocale(0, "");
    
    if (argc == 3) {
        //lab6oop.exe owners.json js.json
        //lab6oop.exe owners.xml js.json
        //lab6oop.exe owners.json newxml.xml
        //lab6oop.exe owners.xml newxml.xml
        string filein = argv[1];
        string fileout = argv[2];
        
        if (filein[filein.size() - 1] == 'l') {
            if (fileout[fileout.size() - 1] == 'l') {
                xml_document doc;
                char* c = const_cast<char*>(filein.c_str());
                xml_parse_result result = doc.load_file(c);
                TaxService taxS;
                taxS.fromFileXml(doc);

                taxS.printXMl(fileout);
            }
            else {
                xml_document doc;
                char* c = const_cast<char*>(filein.c_str());
                xml_parse_result result = doc.load_file(c);
                
                TaxService taxS;
                taxS.fromFileXml(doc);
                ofstream fout(argv[2]);
                json js = taxS.toFile();
                fout << js;
                fout.close();
            }
        }
        else {
            if (fileout[fileout.size() - 1] == 'l') {
                ifstream fin(argv[1]);
                TaxService taxS;
                json jpl = json::parse(fin);
                taxS.fromFile(jpl);
                fin.close();

                taxS.printXMl(fileout);
            }
            else {
                ofstream fout(fileout);
                ifstream fin(filein);
                TaxService ser;
                json jpl = json::parse(fin);
                ser.fromFile(jpl);
                json js = ser.toFile();
                fout << js;
                fin.close();
                fout.close();
            }
        }
        cout << "File is ready" << endl;
    }
    
    if(argc == 1) {
        ofstream fout;
        ifstream fin;

        vector<Owner> owners;
        Owner owner1("Zholobov Artemon", "123456789");
        Owner owner2("Zemleedov Nimyab", "987654321");
        Owner owner3("Steo Insidovich", "135792468");
        Car car1(13, 13);
        Car car2(100, 100);
        Car car3(150, 150);
        Car car4(210, 210);
        CountryHouse countryhouse1(3000, 30);
        CountryHouse countryhouse2(5000, 10);
        CountryHouse countryhouse3(1500, 50);
        CountryHouse countryhouse4(1000, 100);
        Appartment appartment1(200, 50);
        Appartment appartment2(250, 78);
        Appartment appartment3(3000, 101);
        Appartment appartment4(10000, 200);

        owner1.addProperty(&car1);
        owner1.addProperty(&car2);
        owner1.addProperty(&countryhouse1);
        owner1.addProperty(&appartment1);

        owner2.addProperty(&car3);
        owner2.addProperty(&countryhouse2);
        owner2.addProperty(&countryhouse3);
        owner2.addProperty(&appartment2);

        owner3.addProperty(&car4);
        owner3.addProperty(&countryhouse4);
        owner3.addProperty(&appartment3);
        owner3.addProperty(&appartment4);

        owners.push_back(owner1);
        owners.push_back(owner2);
        owners.push_back(owner3);



        int flag = -1;


        while (flag != 0) {
            printOwners(owners);
            menu();
            cin >> flag;
            TaxService serv;
            string filename;
            json js;
            json jpl;
            string fullname = "", inn = "";
            Owner owner("", "");
            Owner owne("", "");
            int index, n, param, worse;
            string filein;
            char* c;
            string fileout;
            switch (flag)

            {
            case 1:
                cout << "выберете собсвенника ";

                cin >> index;
                cout << "выберите какую собственность добавить 1 машина 2 квартира 3 домик и введите их параметры , а затем цену ";
                cin >> n >> param >> worse;
                if (n == 1) {
                    Car car(worse, param);
                    owners[index].addProperty(&car);
                }
                if (n == 2) {
                    Appartment appartment(worse, param);
                    owners[index].addProperty(&appartment);
                }
                if (n == 3) {
                    CountryHouse countryHouse(worse, param);
                    owners[index].addProperty(&countryHouse);
                }
                break;
            case 2:

                cout << "Введите полное имя \n";
                cin >> fullname;
                cout << "Введите полное инн ";
                cin >> inn;
                owner.setName(fullname);
                owner.setInn(inn);

                owners.push_back(owner);
                break;
            case 3:
                owners.pop_back();
                break;
            case 4:
                cout << "выберете собсвенника ";

                cin >> index;
                owners[index].deleteProperty();
                break;
            case 5:
                cout << "выберете собсвенника ";

                cin >> index;
                cout << owners[index].calculateTax() << " общий налог" << endl;
                break;
            case 6:

                cout << "Введите название файла ";
                //("js.json")
                cin >> filename;
                fout.open(filename);
                cout << "введите номер собственника ";

                cin >> n;
                js = owners[n].toFile();
                fout << js;
                cout << "файл готов" << endl;
                fout.close();
                break;
            case 7:

                cout << "Введите название файла ";
                //("asdasd.json")
                cin >> filename;
                fin.open(filename);
                jpl = json::parse(fin);

                owne.fromFile(jpl);
                owners.push_back(owne);
                fin.close();
                break;
            case 8:
                //js.json
                //newxml.xml
                cout << "Введите файл для записи собственников ";
                cin >> fileout;
                serv.setOwners(owners);
                if (fileout[fileout.size() - 1] == 'l') {
                    serv.printXMl(fileout);
                }
                else {
                    ofstream fout(fileout);
                    json js = serv.toFile();
                    fout << js;
                    fout.close();
                }
                cout << "file is ready" << endl;
                break;
            case 9:
                cout << "Введите файл данных и файл записи ";
                
                cin >> filein;
                cin >> fileout;
                //owners.json js.json
                //owners.xml js.json
                //owners.json newxml.xml
                //owners.xml newxml.xml
                if (filein[filein.size() - 1] == 'l') {
                    if (fileout[fileout.size() - 1] == 'l') {
                        xml_document doc;
                        c = const_cast<char*>(filein.c_str());
                        xml_parse_result result = doc.load_file(c);
                        TaxService taxS;
                        taxS.fromFileXml(doc);

                        taxS.printXMl(fileout);
                    }
                    else {
                        xml_document doc;
                        c = const_cast<char*>(filein.c_str());
                        xml_parse_result result = doc.load_file(c);
                        TaxService taxS;
                        taxS.fromFileXml(doc);

                        ofstream fout(fileout);
                        json js = taxS.toFile();
                        fout << js;
                        fout.close();
                    }
                }
                else {
                    if (fileout[fileout.size() - 1] == 'l') {
                        ifstream fin(filein);
                        TaxService taxS;
                        json jpl = json::parse(fin);
                        taxS.fromFile(jpl);
                        fin.close();

                        taxS.printXMl(fileout);
                    }
                    else {
                        ofstream fout(fileout);
                        ifstream fin(filein);
                        TaxService ser;
                        json jpl = json::parse(fin);
                        ser.fromFile(jpl);
                        json js = ser.toFile();
                        fout << js;
                        fin.close();
                        fout.close();
                    }
                }
                cout << "файл готов!" << endl;
                break;
            default:
                break;
            }
            
        }
    }
    
    
    

}

