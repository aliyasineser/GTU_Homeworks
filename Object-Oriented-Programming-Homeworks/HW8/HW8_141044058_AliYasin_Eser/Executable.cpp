/* 
 * File:   Executable.cpp
 * Author: aliyasineser
 * 
 * Created on December 20, 2015, 4:30 PM
 */


#include "Executable.h"
#include "Exception.h"
#include <iostream>
#include <cstring>
using namespace std;

const string FILE_NAME = "MyFile";
const string FILE_OWNER = "MyFile";
const int FILE_SIZE = 100;
const string LAST_MOD = "21.05.2016";
const string COMPILER = "g++";

namespace GTU_YASIN_FILE {

    Executable::Executable() : File() {
        setCompiler(COMPILER);
    }

    Executable::Executable(const string _name, const string _owner, const int _size,
            const string _lastModification, const string _Compiler) :
    File(_name, _owner, _size, _lastModification) {

        setCompiler(_Compiler);
    }

    Executable::Executable(const string _name) : File(_name) {
        setCompiler(COMPILER);
    }

    Executable::Executable(const Executable& orig) {
        setName(orig.getName());
        setOwner(orig.getOwner());
        setSize(orig.getSizeOfTheFile());
        setlastModification(orig.getLastModification());
        setCompiler(orig.getCompiler());
        setPath();
    }

    Executable::~Executable() {

    }

    string Executable::path() const {
        return getPath();
    }

    void Executable::ls(string parameters) const {

        if (parameters == "lRa" || parameters == "laR" || parameters == "Rla"
                || parameters == "Ral" || parameters == "alR" || parameters == "aRl") {
            cout << getName() << "  " << "-rw-" << "  " << getOwner() <<
                    "  " << getCompiler() << "  " << getSizeOfTheFile() <<
                    "  " << getLastModification() << endl;
        } else if (parameters == "aR" || parameters == "Ra") {
            cout << getName() << endl;

        } else if (parameters == "al" || parameters == "la") {
            cout << getName() << "  " << "-rw-" << "  " << getOwner() <<
                    "  " << getCompiler() << "  " << getSizeOfTheFile() <<
                    "  " << getLastModification() << endl;
        } else if (parameters == "Rl" || parameters == "lR") {
            string temp = getName();
            if (temp[0] = '.') {
            } else
                cout << getName() << "  " << "-rw-" << "  " << getOwner() <<
                "  " << getCompiler() << "  " << getSizeOfTheFile() <<
                "  " << getLastModification() << endl;
        } else if (parameters == "Rl" || parameters == "lR") {
            string temp = getName();
            if (temp[0] = '.') {
            } else
                cout << getName() << endl;
        } else if (parameters == "l") {
            cout << getName() << "  " << "-rw-" << "  " << getOwner() <<
                    "  " << getCompiler() << "  " << getSizeOfTheFile() <<
                    "  " << getLastModification() << endl;
        } else if (parameters == "R") {
            cout << getName() << endl;
        } else if (parameters == "a") {
            cout << getName() << endl;
        }


    }

    File & Executable::cd(string _path) {
        cerr << "Executable files can't have subdirectories!" << endl;
        throw pathException();

        return *this;
    }

    bool Executable::cp(const File &other) {
        cerr << "Executable files can't take copies!" << endl;
        throw cpException();

        return false;

    }

    void Executable::setCompiler(string _comp) {
        compiler = _comp;
    }

    string Executable::getCompiler() const {
        return compiler;
    }


}
