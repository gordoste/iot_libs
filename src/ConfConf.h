#ifndef _CONFCONF_H
#define _CONFCONF_H

#include <Arduino.h>
#include <FS.h>
#include "StringStream.h"

template <typename T>
class ConfConf {
public:
    // Read config from a stream. Reads to internal storage if no destination given. Returns the config
    T *read(Stream &in, T *dest = NULL);
    // Read config from a file. Reads to internal storage if no destination given. Returns the config
    T *read(FS &fs, String fileName, T *dest = NULL);
    // Read config from a string. Reads to internal storage if no destination given. Returns the config
    T *read(char *str, T *dest = NULL);

    // Write config to a stream. Writes from internal storage if no source given.
    bool write(Stream &out, T *src = NULL);
    // Write config to a file. Writes from internal storage if no source given.
    bool write(FS &fs, const char *fnam, T *src = NULL);
    // Write config in human readable form to a stream. Writes from internal storage if no source given.
    virtual bool writeHumanReadable(Stream &out, T *src = NULL);
    // Write a blank config to a stream
    bool writeNewConf(Stream &out);

protected:
    T m_data;

private:
    virtual T *readImpl(Stream &in, T *dest) = 0;
    virtual bool writeImpl(Stream &out, T *src) = 0;

};

#endif // #ifndef _CONFCONF_H