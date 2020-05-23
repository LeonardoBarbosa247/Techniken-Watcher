#include "Path.hpp"


Path::Path(string name, time_t time)
{
    this->time = time;
    this->p = name.c_str();
    string ss = (this->p).string();
    string file;
    string folder;
    for(int i = 0; i < ss.size(); i++)
    {
        file+=ss[i];
        if(ss[i] == '/')
        {
            folder+=file;
            file.clear();
        }
    }
    this->folder = folder;
    this->file = file;
}

Path::~Path()
{

}

time_t Path::getTime()
{
    return this->time;
}

string Path::getFolder()
{
    return folder;
}

string Path::getFile()
{
    return file;
}

string Path::getFilename()
{
    return p.string();
}

string Path::toString()
{
    stringstream ss;
    ss << p.string() << " || " << asctime(localtime(&time)) << endl;
    return ss.str();
}

int operator==(Path a, Path b)
{
   if(a.getFile() == b.getFile()) 
   {
       /*
       if(a.getTime() == b.getTime())
       {
           if(a.getFolder() == b.getFolder()) return EQUAL;
           else return MOVE;
       }else
       {
           cout << a.getTime() << " diferente de " << b.getTime()  << endl;
           return MODIFY;
       }
       */
      if(a.getFolder() == b.getFolder() )
      {
          if(a.getTime() == b.getTime()) return EQUAL;
          else return MODIFY;
      }else return MOVE;
      
   }
   return 0;
}

void technikenWatcher(Path p, int flag)
{
    string watcher = (flag == CREATE ? " CREATE " : flag == MODIFY ? " MODIFY " : flag == DELETE ? " DELETE " : " MOVE ");
    puts((p.getFolder() + watcher + p.getFile()).c_str());
    //system("sudo ./TechnikenWatcher /Users/leonardo_barbosa/Documents/");
    exit(0);
}

bool searchingPath(Path s, string directory)
{
jump:
    for(auto& p: fs::recursive_directory_iterator(directory.c_str()))
    {
        time_t cftime;
        bool error = false;
        try
        {
            auto ftime = fs::last_write_time(p);  
            time_t cftime = decltype(ftime)::clock::to_time_t(ftime);    
        }
        catch(const std::exception& e)
        {
            error = true;
            goto jump;
        }
        if(!error)
        {
            Path tck(p.path(), cftime);
            if(tck.getFile() == s.getFile()) return true;
        }
    }
    return false;
}

bool searchingPath(Path p, vector<Path> v)
{
    for(vector<Path>::iterator it = v.begin(); it != v.end(); it++) if((*it == p) == MOVE) return true;
    return false;
}