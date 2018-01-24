#ifndef _SHARED_H
#define _SHARED_H

#include <string>
#include <vector>

int* readFile(const std::string fname,
              float *& fptr,
              const int max_alloc);

#endif
