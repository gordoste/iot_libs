#include "ConfConf.h"

template <class T>
T *ConfConf<T>::read(Stream &in, T *dest) {
    if (dest == NULL) dest = m_data;
    return readImpl(in, dest);
}

template <class T>
T *ConfConf<T>::read(FS &fs, String fileName, T *dest) {
    if (dest == NULL) dest = m_data;
    File cfgFile = fs.open(fileName);
    T *_result = NULL;
    if (cfgFile) {
        _result = read(cfgFile, dest);
        cfgFile.close();
    }
    return _result;
}

template <class T>
T *ConfConf<T>::read(char *str, T *dest) {
    if (dest == NULL) dest = m_data;
    return read(StringStream(String(str)), dest);
}

template <class T>
bool ConfConf<T>::write(Stream &out, T *src) {
    if (src == NULL) src = m_data;
    return writeImpl(out, src);
}

template <class T>
bool ConfConf<T>::write(FS &fs, const char *fnam, T *src) {
    if (src == NULL) src = m_data;
    File cfgFile = fs.open(fnam, "w");
    if (!cfgFile) return false;
    bool _res = write(cfgFile, src);
    cfgFile.close();
    return _res;
}

template <class T>
bool ConfConf<T>::writeHumanReadable(Stream &out, T *src) {
    if (src == NULL) src = m_data;
    // Default impl just calls writeImpl - override to change
    return writeImpl(out, src);
}

template <class T>
bool ConfConf<T>::writeNewConf(Stream &out) {
    return write(out, new T());
}
