#include <iostream>
#include <fstream>
using namespace std;

const char * flog_name = "log_split_list.txt";

int main(int argc, char ** argv){
  if(argc != 3){
    cerr << "Invalid arguments" << endl;
    cerr << "./split_list <fsrc> <ddst>" << endl;
    return -1;
  }

  char * fsrc_name = argv[1];
  char * ddst = argv[2];
  
  ifstream fsrc(fsrc_name);
  if(!fsrc.good()){
    cerr << "Error : Couldn't open " << fsrc_name << "." << endl;
    return -1;
  }

  char buf[1024];
  int num_imgs = 0;
  while(fsrc.getline(buf, 1024)){
    num_imgs++;
  }
  fsrc.clear();
  fsrc.seekg(0, fsrc.beg);

  cout << "number of images in " << fsrc_name
       << " is " << num_imgs << "." << endl;

  ofstream flog(flog_name);
  if(!flog.good()){
    return -1;
  }

  cout << "Info : " << flog_name << " was opened." << endl;

  int prev_label = -1;
  ofstream fdst;
  char fdst_name[1024]; 
  while(fsrc.getline(buf, 1024)){
    char  fimg_path[1024];
    int label;
    sscanf(buf, "%s %d", fimg_path, &label);
    if(prev_label != label){
      cout << "Info : " << fdst_name << " was closed." << endl;
      fdst.close();
      
      sprintf(fdst_name, "%s%s%d.txt", ddst, fsrc_name, label); 
      fdst.open(fdst_name, ofstream::app);
      if(!fdst.good()){
	cerr << "Error : Couldn't open "
	     << fdst_name << "." << endl;
	return -1;
      }
      cout << "Info : " << fdst_name << " was opened." << endl;
    }

    fdst << fimg_path;
    prev_label = label;
  }
  return 0;
}
