/* 
 * File:   File.cpp
 * Author: aliyasineser
 * 
 * Created on December 19, 2015, 10:40 PM
 */

#include "File.h"
#include <iostream>

const string FILE_NAME = "MyFile";
const string FILE_OWNER = "MyFile";
const int FILE_SIZE = 100;
const string LAST_MOD = "21.05.2016";

namespace GTU_YASIN_FILE {

    File::File() {
        setName(FILE_NAME);
        setOwner(FILE_OWNER);
        setSize(FILE_SIZE);
        setlastModification(LAST_MOD);
        setPath();
    }

    File::File(const string _name, const string _owner, const int _size,
            const string _lastModification) {

        setName(_name);
        setOwner(_owner);
        setSize(_size);
        setlastModification(_lastModification);
        setPath();

    }

    File::File(const string _name) {
        setName(_name);
        setOwner(FILE_OWNER);
        setSize(FILE_SIZE);
        setlastModification(LAST_MOD);
        setPath();
    }

    File::File(const File& orig) {
        setName(orig.getName());
        setOwner(orig.getOwner());
        setSize(orig.getSizeOfTheFile());
        setlastModification(orig.getLastModification());
        setPath();
    }

    File::~File() {


    }


    //Setters

    void File::setName(const string _name) {
        name = _name;
    }

    void File::setOwner(const string _owner) {
        owner = _owner;
    }

    void File::setSize(const int _size) {
        if (_size >= 0)
            size = _size;
        else {
            cerr << "Size must be greater than zero kilobyte." << endl;
        }
    }

    void File::setlastModification(const string _lastMod) {
        lastModification = _lastMod;
    }

    //Getters

    string File::getName() const {
        return name;
    }

    string File::getOwner() const {
        return owner;
    }

    int File::getSizeOfTheFile() const {
        return size;
    }

    string File::getLastModification() const {
        return lastModification;
    }

    void File::setPath() {
        file_path = "/home/user/" + getName();
    }

    string File::getPath() const {
        return file_path;
    }

    void File::setPath(const string _path) {
        file_path = _path;
    }



}
