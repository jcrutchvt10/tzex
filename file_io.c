#include "file_io.h"

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
int write_file(const char* path, uint8_t* data, size_t size, loff_t offset)
{
    struct file *f;
    mm_segment_t fs_org;

    f = filp_open(path, O_WRONLY | O_CREAT, 0);
    fs_org = get_fs();
    
    set_fs(get_ds());

    vfs_write(f, data, size, &offset);
    
    set_fs(fs_org);

    filp_close(f, NULL);

    return 0;
}

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
int read_file(const char* path, uint8_t* buffer, size_t amount, loff_t offset)
{
    struct file *f;
    mm_segment_t fs_org;

    f = filp_open(path, O_RDONLY, 0);

    fs_org = get_fs();
    
    set_fs(get_ds());
    
    f->f_op->read(f, buffer, amount, &offset);
    
    set_fs(fs_org);

    filp_close(f, NULL);

    return 0;
}

/**
* @brief read_file_size - Get the size of a file in bytes
*
* @param const char* path - Path of file to get size
*
* @return size_t - Size of file in bytes
*/
size_t read_file_size(const char* path)
{
    int ret;       
    struct file *f;
    struct kstat stat;
   
    mm_segment_t fs_org;

    f = filp_open(path, O_RDONLY, 0);

    fs_org = get_fs();
    
    set_fs(get_ds());
    
    //f->f_op->read(f, buffer, amount, &offset);
    ret = vfs_getattr(f->f_vfsmnt, f->f_dentry, &stat);
    
    if (ret) {
        logd("[-] Error trying to get file size of %s\n", path);
    }

    set_fs(fs_org);

    filp_close(f, NULL);

    return stat.size;
}