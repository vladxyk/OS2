#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <filesystem>
#include <dirent.h>
#include <iomanip>
#include <sys/types.h>

#define PROC_DIRECTORY "/proc/"
using namespace std;

void help(){
  cout << "AUTHORS:" << endl << "Goriunova" << endl << "Eremin" << endl << "Dultseva" << endl << endl;
  cout << "AVAILABLE OPTIONS: " << endl;
  cout << "-mf: move a file" << endl;
  cout << "-cf: copy a file" << endl;
  cout << "-rmf: remove a file" << endl;
  cout << "-ssf: show size of file" << endl;
  cout << "-saf: show all files in directory" << endl;
  cout << "-sap: show all processes" << endl << endl;
  cout << "PROJECT DESCRIPTION: " << endl << "Working with the file system" << endl << endl;
  cout << "EXAMPLES OF STARTING: " << endl << "./oslab2 -cf from_file to_file" << endl;
}

void show_all_files(const char *path){
  DIR *dir = opendir(path);
  dirent *entry;
  if (dir == NULL){
    return;
  }

  while ((entry = readdir(dir)) != NULL){
    cout << entry->d_name << endl;
  }
  closedir(dir);
}

int showsize(string filesize){
	int allsize = 0;
	
  struct stat fileinfo;
  if(stat(filesize.c_str(), &fileinfo) != 0){
    return -1;
  }
  if(S_ISDIR(fileinfo.st_mode)){
    DIR *dir = opendir(filesize.c_str());
    dirent *entry;
    while((entry = readdir(dir)) != nullptr){
      if((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)){
        string next = filesize + "/" + entry->d_name;
        allsize += showsize(next);
      }
    }
    closedir(dir);
    return allsize;
  }
  else{
    return fileinfo.st_size;
  }
}

int showp(){
  DIR *dir = opendir("/proc/");
  if (dir == nullptr){
        return -1;
  }
  dirent *entry;

  while ((entry = readdir(dir)) != NULL){
    cout << entry->d_name << endl;
  }
  closedir(dir);
}

bool copyFile(const char *copyfromfile, const char *copytofile){
  ifstream cff(copyfromfile);
  ofstream ctf(copytofile);
 
  char sym;
  // цикл посимвольного чтения
  while (cff)
  {
    cff.get(sym);
    if (cff) {
      ctf.put(sym);
    }
  }
  cff.close();
  ctf.close();
  return 0;
}



int main(int argc, char *argv[]){
  if (string(argv[1]) == "-h"){
    help();
  } 
    
  if (string(argv[1]) == "--help"){
    help();
  }

  if (string(argv[1]) == "-mf"){
    rename(argv[2] , argv[3]);
  }

  if (string(argv[1]) == "-rmf"){
    remove(argv[2]);
  }

  if (string(argv[1]) == "-cf"){
    copyFile(argv[2], argv[3]);
  }

  if (string(argv[1]) == "-saf"){
    show_all_files(argv[2]);
  }

  if (string(argv[1]) == "-sap"){
    showp();
  }

  if (string(argv[1]) == "-ssf"){
    cout << "Size is " << showsize(argv[2]) << " bytes" << endl;
  }

return 0;
}
