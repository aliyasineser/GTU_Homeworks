/* 
 * File:   TextFile.h
 * Author: aliyasineser
 *
 * Created on December 20, 2015, 4:32 PM
 */

#ifndef TEXTFILE_H
#define	TEXTFILE_H

#include "File.h"

namespace GTU_YASIN_FILE {

    class TextFile : public File {
    public:
        TextFile();
        TextFile(const string _name, const string _owner, const int _size,
            const string _lastModification, const string _TextFile);
        TextFile(const string _name);
        TextFile(const TextFile& orig);
        virtual ~TextFile();

        string getTextType() const;
        void setTextType(string _type);
        
        string path() const;
        void ls(string parameters) const;
        File & cd(string _path);
        bool cp(const File &other);

    private:
        string textType;

    };
}
#endif	/* TEXTFILE_H */

