/* 
 * File:   File.h
 * Author: aliyasineser
 *
 * Created on December 19, 2015, 10:40 PM
 */

#ifndef FILE_H
#define	FILE_H

#include <string>

using namespace std;

namespace GTU_YASIN_FILE {

    class File {
    public:
        //Constructors
        File();
        File(const string _name);
        File(const string _name, const string _owner, const int _size,
                const string _lastModification);
        File(const File& orig);
        ~File(); // Destructor

        //Setters
        void setName(const string _name);
        void setOwner(const string _owner);
        void setSize(const int _size);
        void setlastModification(const string _lastMod);
        void setPath();
        void setPath(const string _path);

        //Getters
        string getName() const;
        string getOwner() const;
        int getSizeOfTheFile() const;
        string getLastModification() const;
        string getPath() const; // This function works like path function-operation
        
        
        //File Operations -> Pure virtual, so we can't create an objet for File class, only derived
        virtual string path() const = 0;
        virtual void ls(string parameters) const = 0;
        virtual File & cd(string _path) = 0;
        virtual bool cp(const File &other) = 0;
        


    private:
        //Data members
        string name;
        string owner;
        int size;
        string lastModification;
        string file_path;

    };
}
#endif	/* FILE_H */

