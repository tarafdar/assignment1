#ifndef _SHARED_H
#define _SHARED_H

#include <vector>

std::vector<int> readFile(std::string fname,
              float *& fptr,
              const int max_alloc);

#endif
