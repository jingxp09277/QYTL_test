struct _finddata_t
{
    unsigned attrib;
    size_t time_create;
    size_t time_access;
    size_t time_write;
    _fsize_t size;
    char name[_MAX_PATH];
};