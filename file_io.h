#ifndef _FILE_IO_H
#define _FILE_IO_H

#include <linux/fs.h> 
#include <asm/uaccess.h>  
#include <linux/path.h>
#include <linux/namei.h>
#include <linux/version.h>
#include "debug.h"

/**
* @brief write_file - Write n amount from buffer into file
*
* @param const char* path - Path to file to write to
* @param uint8_t* buffer - Data to write
* @param size_t - Amount of data to write
* @param loff_t - Offset in file to write to
*
* @return int
*/
int write_file(const char* path, uint8_t* data, size_t size, loff_t offset);
/**
* @brief read_file - Read n amount from file into buffer
*
* @param const char* path - Path to file to read
* @param uint8_t* buffer - To store the read data
* @param size_t - Amount of data to read from the file
* @param loff_t - Offset in file to read from
*
* @return int
*/
int read_file(const char* path, uint8_t* buffer, size_t amount, loff_t offset);

/**
* @brief read_file_size - Get the size of a file in bytes
*
* @param const char* path - Path of file to get size
*
* @return size_t - Size of file in bytes
*/
size_t read_file_size(const char* path);

#endif // _FILE_IO_H