#ifndef __FILE_HANDLER_H__
#define __FILE_HANDLER_H__

#include <stdint.h>

typedef uint32_t data_type_t;

class file_handler_t {
public:
    file_handler_t();
    ~file_handler_t();

    void read(const std::string m_file_name);
    data_type_t size() const;
    data_type_t get(size_t i) const;

private:
    data_type_t *elements;
    data_type_t data_size;
};

#endif

