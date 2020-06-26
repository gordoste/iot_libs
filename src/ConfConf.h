#ifndef _CONFCONF_H
#define _CONFCONF_H

#include "StringStream.h"
#include <Arduino.h>
#include <FS.h>

template <typename T>
class ConfConf {
public:
    // Read config from a stream. Reads to internal storage if no destination given. Returns the config
    T *read(Stream &in, T *dest = NULL) {
        if (dest == NULL) dest = &m_data;
        return readImpl(in, dest);
    }

    // Read config from a file. Reads to internal storage if no destination given. Returns the config
    T *read(FS &fs, String fileName, T *dest = NULL) {
        if (dest == NULL) dest = &m_data;
        File cfgFile = fs.open(fileName);
        T *_result = NULL;
        if (cfgFile) {
            _result = read(cfgFile, dest);
            cfgFile.close();
        }
        return _result;
    }

    // Read config from a string. Reads to internal storage if no destination given. Returns the config
    T *read(char *str, T *dest = NULL) {
        if (dest == NULL) dest = &m_data;
        return read(StringStream(String(str)), dest);
    }


    // Write config to a stream. Writes from internal storage if no source given.
    bool write(Stream &out, T *src = NULL) {
        if (src == NULL) src = &m_data;
        return writeImpl(out, src);
    }

    // Write config to a file. Writes from internal storage if no source given.
    bool write(FS &fs, const char *fnam, T *src = NULL) {
        if (src == NULL) src = &m_data;
        File cfgFile = fs.open(fnam, "w");
        if (!cfgFile) return false;
        bool _res = write(cfgFile, src);
        cfgFile.close();
        return _res;
    }

    // Write config in human readable form to a stream. Writes from internal storage if no source given.
    virtual bool writeHumanReadable(Stream &out, T *src = NULL) {
        if (src == NULL) src = &m_data;
        // Default impl just calls writeImpl - override to change
        return writeImpl(out, src);
    }

    // Write a blank config to a stream
    bool writeNewConf(Stream &out) {
        return write(out, new T());
    }

protected:
    T m_data;

private:
    virtual T *readImpl(Stream &in, T *dest) = 0;
    virtual bool writeImpl(Stream &out, T *src) = 0;
};

#endif // #ifndef _CONFCONF_H