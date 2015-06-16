#ifndef TOOLS_H_
#define TOOLS_H_

#ifndef ARDUINO
typedef unsigned char byte;
#endif

byte* chararray_to_bytearray(char* chararray);
char* bytearray_to_chararray(byte* bytearray);


#endif