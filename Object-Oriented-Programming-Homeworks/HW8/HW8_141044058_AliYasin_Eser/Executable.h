/* 
 * File:   Executable.h
 * Author: aliyasineser
 *
 * Created on December 20, 2015, 4:30 PM
 */

#ifndef EXECUTABLE_H
#define	EXECUTABLE_H

#include "File.h"

namespace GTU_YASIN_FILE {

    class Executable : public File {
    public:
        Executable();
        Executable(const string _name, const string _owner, const int _size,
                const string _lastModification, const string _Compiler);
        Executable(string _name);
        Executable(const Executable& orig);
        ~Executable();

        void setCompiler(string);
        string getCompiler() const;

        string path() const;
        void ls(string parameters) const;
        File & cd(string _path);
        bool cp(const File &other);

    private:
        string compiler;

    };
}
#endif	/* EXECUTABLE_H */

