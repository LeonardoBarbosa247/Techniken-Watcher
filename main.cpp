
#include "Path.hpp"
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <map>
#include <list>



int main(int argc, char** argv)
{
    if(argc!=2)
    {
        cout << "Techniken Watcher requer diretório como parâmetro" << endl;
        cout << "Techniken Watcher finalizado" << endl;
        return 0;
    }
    cout << "Techniken Watcher" << endl;
    vector<Path> v;
    map<string,int> exist;
    list<int> thisList;
    string file = argv[1];
    for(auto& p: fs::recursive_directory_iterator(argv[1]))
    {
        static int i = 0;
        auto ftime = fs::last_write_time(p);
        time_t cftime = decltype(ftime)::clock::to_time_t(ftime);
        Path tck(p.path(), cftime);
        if(tck.getFile() != "." and tck.getFile() != ".." and tck.getFile() != ".DS_Store")
        {
            thisList.push_back(i);
            exist[p.path()] = ++i;
            v.push_back(tck);
        }
    }
    cout << "Watching " << v.size() << " files and directories" << endl;


    while(true)
    {
        int it = 0;
        int cont = 0;
        list<int> notSearching = thisList;

        for(auto& p: fs::recursive_directory_iterator(argv[1]))
        {
            bool error = false;
            time_t cftime;
            try
            {
                auto ftime = fs::last_write_time(p);  
                cftime = decltype(ftime)::clock::to_time_t(ftime);
            }
            catch(const std::exception& e)
            {
                error = true;
            }
            if(!error)
            {
                Path tck(p.path(), cftime);
                if(tck.getFile() != "." and tck.getFile() != ".." and tck.getFile() != ".DS_Store")
                {
                    int i = exist[p.path()];
                    if( i == 0) technikenWatcher(tck, searchingPath(tck, v) ? MOVE : CREATE);
                    else if( i > 0)
                    {
                        notSearching.remove((i-1));
                        if((tck == v[(i-1)]) == MODIFY) technikenWatcher(tck, MODIFY); 
                    }
                }
            }
        }
        
        for(list<int>::iterator it = notSearching.begin(); it != notSearching.end() ; it++)
        {
            if(searchingPath(v[*it], argv[1])) technikenWatcher(v[*it], MOVE); 
        } 
        
        if(notSearching.size() > 0) technikenWatcher(v[*notSearching.begin()], DELETE);
        usleep(100000);
    }
}