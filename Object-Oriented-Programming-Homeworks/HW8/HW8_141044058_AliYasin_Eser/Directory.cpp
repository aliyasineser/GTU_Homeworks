/* 
 * File:   Directory.cpp
 * Author: aliyasineser
 * 
 * Created on December 20, 2015, 4:37 PM
 */

#include "Directory.h"
#include "Executable.h"
#include "TextFile.h"
#include <vector>

const string FILE_NAME = "MyFile";
const string FILE_OWNER = "MyFile";
const int FILE_SIZE = 100;
const string LAST_MOD = "21.05.2016";
const string DIR_NAME = "MyDir";
const int ZERO = 0;

namespace GTU_YASIN_FILE {

    Directory::Directory() : File(DIR_NAME) {
        fileCount = ZERO;
    }

    Directory::Directory(const Directory& orig) {
        setName(orig.getName());
        setOwner(orig.getOwner());
        setSize(orig.getSizeOfTheFile());
        setlastModification(orig.getLastModification());
        fileCount = orig.fileCount;
        setPath();
    }

    Directory::~Directory() {
    }

    string Directory::path() const {
        return getPath();
    }

    void Directory::ls(string parameters) const {

        cout << "Total " << getFileCount() << " files." << endl << endl;

        for (int i = 0; i < Files.size(); ++i) {
            Files[i].ls(parameters);
        }

    }

    File & Directory::cd(string _path) {
    }

    bool Directory::cp(const File &other) {

        const File * file_p = &other;


        if (dynamic_cast<const Executable*> (file_p) != NULL) {
            const Executable & exe = dynamic_cast<const Executable&> (other);
            Executable* temp = new Executable;
            *temp = exe;
            Files.push_back(temp);
            string tempStr = getPath() + "/" + temp->getName();
            Files[Files.size() - 1]->setPath(tempStr);
            ++fileCount;
        } else if (dynamic_cast<const TextFile*> (file_p) != NULL) {
            const TextFile & text = dynamic_cast<const TextFile&> (other);
            TextFile* temp = new TextFile;
            *temp = text;
            Files.push_back(temp);
            string tempStr = getPath() + "/" + temp->getName();
            Files[Files.size() - 1]->setPath(tempStr);
            ++fileCount;
        } else if (dynamic_cast<const Directory*> (file_p) != NULL) {
            const Directory & dir = dynamic_cast<const Directory&> (other);
            Directory* temp = new Directory;
            *temp = dir;
            Files.push_back(temp);
            string tempStr = getPath() + "/" + temp->getName();
            Files[Files.size() - 1]->setPath(tempStr);
            ++fileCount;
        }



    }



}