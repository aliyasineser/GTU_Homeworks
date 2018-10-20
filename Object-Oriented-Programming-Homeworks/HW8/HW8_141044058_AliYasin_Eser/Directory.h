/* 
 * File:   Directory.h
 * Author: aliyasineser
 *
 * Created on December 20, 2015, 4:37 PM
 */

#ifndef DIRECTORY_H
#define	DIRECTORY_H

#include "File.h"
#include <vector>

namespace GTU_YASIN_FILE {

    class Directory : File {
    public:
        Directory();
        Directory(const string _name, const string _owner, const int _size,
                const string _lastModification);
        Directory(const Directory& orig);
        ~Directory();


        string getCurrentPath() const;
        int getFileCount() const;

        string path() const;
        void ls(string parameters) const;
        File & cd(string _path);
        bool cp(const File &other);
 

    private:



        int fileCount;
        string cd_path;
        vector<File*> Files;


    };
}
#endif	/* DIRECTORY_H */

