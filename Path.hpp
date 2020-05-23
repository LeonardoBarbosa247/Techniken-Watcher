#ifndef Path_hpp
#define Path_hpp


#include <string>  
#include <iostream>  
#include <sstream>  
#include <filesystem>  
#include <chrono>
#include <iomanip>
#include <unistd.h>
#include <vector>

#define CREATE  0
#define MODIFY  1
#define DELETE  2
#define MOVE    3
#define EQUAL   4

using namespace std;
namespace fs = std::filesystem;

class Path
{
    private:
        fs::path p;
        time_t time;
        string folder;
        string file;
    public:
        Path(string name, time_t time);
        ~Path();
        time_t getTime();
        string getFilename();
        string getFolder();
        string getFile();
        string toString();
};

int operator==(Path a, Path b);
void technikenWatcher(Path p, int flag);
bool searchingPath(Path p, string directory);
bool searchingPath(Path p, vector<Path> v);

#endif