// This program is to implement a commend which can copy directoies and files under Linux. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

/// @brief: Copy a file from src to dest
/// @param src: the source file   
/// @param dest: the destination file 
/// @return true for success, false for failure
bool copy_file(const char* src,const char* dest){
    FILE* in = fopen(src,"rb");
    if(in == NULL){
        perror("fail to open file.");
        return false;
    }

    FILE* out = fopen(dest,"wb");
    if(out == NULL){
        perror("fail to open file.");
        fclose(in);
        return false;
    }

    char buf[4096]={0};
    size_t size;
    while((size = fread(buf,1,sizeof(buf),in)) > 0){
        fwrite(buf,1,size,out);
    }
    fclose(in);
    fclose(out);
    return true;
}

/// @brief : copy a softlink from src to dest
/// @param src : the source softlink
/// @param dest : the destination softlink
/// @return true for success, false for failure
bool copy_link(const char* src,const char* dest){
    char file_path[4096]={0};
    ssize_t size=readlink(src,file_path,sizeof(file_path)-1);//an empty char for '\0'
    if(size==-1){
        perror("fail to read link.");
        return false;
    }
    file_path[size]  ='\0';//add '\0' to the end of the string
    if(symlink(file_path,dest)==-1){
        perror("fail to create link.");
        return false;
    }
    return true;
}

/// @brief : copy a directory from src to dest
/// @param src : the source directory
/// @param dest : the destination directory
/// @return true for success, false for failure
bool copy_dir(const char* src,const char* dest){
    DIR* dir=opendir(src);
    if(dir==NULL){
        perror("fail to open directory.");
        return false;
    }
    if(mkdir(dest,0755)==-1 && errno!=EEXIST){
        perror("fail to create directory.");
        return false;
    }

    //Copy directory contents recursively
    struct dirent* entry;
    while((entry = readdir(dir))!=NULL){
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0){
            continue;
        }

        char src_path[4096]={0};
        char dest_path[4096]={0};
        sprintf(src_path,"%s/%s",src,entry->d_name);
        sprintf(dest_path,"%s/%s",dest,entry->d_name);

        struct stat st;
        if(lstat(src_path,&st)==-1){
            perror("fail to get file status.");
            return false;
        }

        if(S_ISREG(st.st_mode)){
            if(copy_file(src_path,dest_path)==false){
                perror("fail to copy file.");
                return false;
            }
        }
        else if(S_ISLNK(st.st_mode)){
            if(copy_link(src_path,dest_path)==false){
                perror("fail to copy link.");
                return false;
            }
        }
        else if(S_ISDIR(st.st_mode)){
            if(copy_dir(src_path,dest_path)==false){
                perror("fail to copy directory.");
                return false;
            }
        }
        else{
            perror("unknow file type.");
            return false;
        }
    }
    closedir(dir);
    return true;
}

int main(int argc,char** argv){
    if(argc!=3){
        fprintf(stderr,"Usage: %s <src> <dest>\n",argv[0]);
        return -1;
    }

    const char* src=argv[1];
    const char* dest=argv[2];

    struct stat st;
    if(lstat(src,&st)==-1){
        perror("fail to get file status.");
        return -1;
    }

    if(S_ISREG(st.st_mode)){
        if(copy_file(src,dest)==false){
            perror("fail to copy file.");
            return -1;
        }
    }
    else if(S_ISLNK(st.st_mode)){
        if(copy_link(src,dest)==false){
            perror("fail to copy link.");
            return -1;
        }
    }
    else if(S_ISDIR(st.st_mode)){
        if(copy_dir(src,dest)==false){
            perror("fail to copy directory.");
            return -1;
        }
    }
    else{
        perror("unknow file type.");
        return -1;
    }
    
    return 0;
}