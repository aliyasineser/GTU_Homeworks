/* 
 * File:   TextFile.cpp
 * Author: aliyasineser
 * 
 * Created on December 20, 2015, 4:33 PM
 */
#include "Exception.h"
#include "TextFile.h"
#include <iostream>

const string FILE_NAME = "MyFile";
const string FILE_OWNER = "MyFile";
const int FILE_SIZE = 100;
const string LAST_MOD = "21.05.2016";
const string TEXT_TYPE = "Unicode";
using namespace std;

namespace GTU_YASIN_FILE {

    string TextFile::getTextType() const {
        return textType;
    }

    TextFile::TextFile() : File() {
        setTextType(TEXT_TYPE);
    }

    TextFile::TextFile(const string _name, const string _owner, const int _size,
            const string _lastModification, const string _TextFile)
    : File(_name, _owner, _size, _lastModification) {
        setTextType(_TextFile);
    }

    TextFile::TextFile(const string _name) : File(_name) {

        setTextType(TEXT_TYPE);
    }

    TextFile::TextFile(const TextFile& orig) {

        setName(orig.getName());
        setOwner(orig.getOwner());
        setSize(orig.getSizeOfTheFile());
        setlastModification(orig.getLastModification());
        setTextType(orig.getTextType());
        setPath();

    }

    TextFile::~TextFile() {


    }

    void TextFile::setTextType(string _type) {
        textType = _type;
    }

    string TextFile::path() const {
        return getPath();
    }

    void TextFile::ls(string parameters) const {
        if (parameters == "lRa" || parameters == "laR" || parameters == "Rla"
                || parameters == "Ral" || parameters == "alR" || parameters == "aRl") {
            cout << getName() << "  " << "-rw-" << "  " << getOwner() <<
                    "  " << getTextType() << "  " << getSizeOfTheFile() <<
                    "  " << getLastModification() << endl;
        } else if (parameters == "aR" || parameters == "Ra") {
            cout << getName() << endl;

        } else if (parameters == "al" || parameters == "la") {
            cout << getName() << "  " << "-rw-" << "  " << getOwner() <<
                    "  " << getTextType() << "  " << getSizeOfTheFile() <<
                    "  " << getLastModification() << endl;
        } else if (parameters == "Rl" || parameters == "lR") {
            string temp = getName();
            if (temp[0] = '.') {
            } else
                cout << getName() << "  " << "-rw-" << "  " << getOwner() <<
                "  " << getTextType() << "  " << getSizeOfTheFile() <<
                "  " << getLastModification() << endl;
        } else if (parameters == "Rl" || parameters == "lR") {
            string temp = getName();
            if (temp[0] = '.') {
            } else
                cout << getName() << endl;
        } else if (parameters == "l") {
            cout << getName() << "  " << "-rw-" << "  " << getOwner() <<
                    "  " << getTextType() << "  " << getSizeOfTheFile() <<
                    "  " << getLastModification() << endl;
        } else if (parameters == "R") {
            cout << getName() << endl;
        } else if (parameters == "a") {
            cout << getName() << endl;
        }
    }

    File & TextFile::cd(string _path) {
        cerr << "Text files can't have subdirectories!" << endl;
        throw pathException();

        return *this;

    }

    bool TextFile::cp(const File &other) {
        cerr << "Text files can't take copies!" << endl;
        throw cpException();

        return false;
    }


}