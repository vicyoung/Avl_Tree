#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "file_handler.h"

using namespace std;

file_handler_t::file_handler_t() :
    elements(NULL) {
}

file_handler_t::~file_handler_t() {
    delete [] elements;
}

void file_handler_t::read(const string m_file_name) {
    fstream file_stream;
    file_stream.open(m_file_name.c_str(), fstream::in|fstream::binary);
    if(!file_stream.is_open()) {
        cerr << "Error: failed to open " << m_file_name << endl;
        exit(1);
    }
    delete []  elements;
    file_stream.read((char*)&data_size, sizeof(data_type_t));
    elements = new data_type_t[data_size];
    if(!file_stream.read((char*)elements, data_size*sizeof(data_type_t))) {
        cerr << "Error: failed to read " << m_file_name << endl;
        delete [] elements;
        file_stream.close();
        exit(1);
    }
    file_stream.close();
}

data_type_t file_handler_t::size() const { return data_size; }

data_type_t file_handler_t::get(size_t i) const { return elements[i]; }

