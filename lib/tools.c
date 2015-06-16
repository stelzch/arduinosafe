#include "tools.h"

/**
 * Converts an array of chars to an array of bytes
 * @param chararray the array which will be converted to a byte array
 * @return the bytearray
 */
byte* chararray_to_bytearray(char* chararray) {
  return reinterpret_cast<byte*>(chararray);
};
/**
 * Convert an array of bytes to an array of chars
 * @param bytearray the array which will be converted to a char array
 * @return the chararray
 */
char* bytearray_to_chararray(byte* bytearray) {
  return reinterpret_cast<char*>(bytearray);
}