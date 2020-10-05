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

ifstream::pos_type filesize(const char *s_path){
   ifstream size(s_path);
   size.seekg(0, ios::end);
   int file_size = size.tellg();
   cout<<"Size of the file is"<<" "<< file_size<<" "<<"bytes" << endl;
   return 0;
}

int showp(){
  struct dirent* dirEntity;
  DIR* dir_proc;

  dir_proc = opendir(PROC_DIRECTORY);
      
  while ((dirEntity = readdir(dir_proc)) != NULL){
    if (dirEntity->d_type == DT_DIR){
      if (dirEntity->d_name){
        string path = string(PROC_DIRECTORY) + dirEntity->d_name + "/cmdline";

        ifstream cmdLineFile(path.c_str());
        string cmdLine;
        if (cmdLineFile){
          getline(cmdLineFile, cmdLine);
        }
        cout << "pid: " << dirEntity->d_name << " " << cmdLine << endl;
      }
    }
  }
  closedir(dir_proc);
  return 0;
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
    filesize(argv[2]);
  }

return 0;
}
