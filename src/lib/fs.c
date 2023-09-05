#include "fs.h"
#include <string.h>
#include <stdio.h>

void initializeFileSystem(FileSystem *fs) {
    strcpy(fs->root.foldername, "root");
    fs->root.file_count = 0;
}

void createFolder(FileSystem *fs, const char *foldername) {
    Folder *new_folder = (Folder*)malloc(sizeof(Folder));
    strcpy(new_folder->foldername, foldername);
    new_folder->file_count = 0;
    fs->root.files[fs->root.file_count++] = new_folder;
}

void createFile(FileSystem *fs, const char *foldername, const char *filename) {
    for (int i = 0; i < fs->root.file_count; i++) {
        Folder *folder = fs->root.files[i];
        if (strcmp(folder->foldername, foldername) == 0) {
            File *new_file = (File*)malloc(sizeof(File));
            strcpy(new_file->filename, filename);
            new_file->size = 0;
            folder->files[folder->file_count++] = new_file;
        }
    }
}

void writeFile(FileSystem *fs, const char *foldername, const char *filename, const char *data) {
    for (int i = 0; i < fs->root.file_count; i++) {
        Folder *folder = fs->root.files[i];
        if (strcmp(folder->foldername, foldername) == 0) {
            for (int j = 0; j < folder->file_count; j++) {
                File *file = folder->files[j];
                if (strcmp(file->filename, filename) == 0) {
                    strcpy(file->data, data);
                    file->size = strlen(data);
                }
            }
        }
    }
}

File* readFile(FileSystem *fs, const char *foldername, const char *filename) {
    for (int i = 0; i < fs->root.file_count; i++) {
        Folder *folder = fs->root.files[i];
        if (strcmp(folder->foldername, foldername) == 0) {
            for (int j = 0; j < folder->file_count; j++) {
                File *file = folder->files[j];
                if (strcmp(file->filename, filename) == 0) {
                    return file;
                }
            }
        }
    }
    return NULL;
}
