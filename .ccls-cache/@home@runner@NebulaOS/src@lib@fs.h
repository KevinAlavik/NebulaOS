#ifndef FS_H
#define FS_H

#define MAX_FILENAME_LENGTH 255
#define MAX_FILE_SIZE 1024

typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    char data[MAX_FILE_SIZE];
    int size;
} File;

typedef struct {
    char foldername[MAX_FILENAME_LENGTH];
    File *files[MAX_FILE_SIZE];
    int file_count;
} Folder;

typedef struct {
    Folder root;
} FileSystem;

void initializeFileSystem(FileSystem *fs);
void createFolder(FileSystem *fs, const char *foldername);
void createFile(FileSystem *fs, const char *foldername, const char *filename);
void writeFile(FileSystem *fs, const char *foldername, const char *filename, const char *data);
File* readFile(FileSystem *fs, const char *foldername, const char *filename);

#endif /* FS_H */
