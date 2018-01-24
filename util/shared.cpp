
#include <iostream>
#include <fstream>

#include "shared.h"

using namespace std;
int readFile(const char* fname, float *& fptr)
{
  ifstream in_file(fname, ios::in | ios::binary | ios::ate);
  if (in_file.is_open())
  {
    streampos size = in_file.tellg();
    fptr = new float[1024*1024];
    cout << "Reading " << size/sizeof(float) << " words from " << fname << endl;
    in_file.seekg(0, ios::beg);
    in_file.read(reinterpret_cast<char*>(&fptr[0]), size);
    in_file.close();
    return size/sizeof(float);
  }
  else
  {
    cout << "Couldn't open file: " << fname << endl;
    return -1;
  }
}

