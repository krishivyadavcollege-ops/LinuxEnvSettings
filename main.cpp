#include <iostream>
#include "task.h"
#include <cstring>
using namespace std;




int main(int argscount , char * arg[])
{
    data_file();
    if(arg[1] == NULL)
    {
        cout<<"Type --help for available commands"<<endl;
    }
    else if(strcmp(arg[1],"--version") == 0)
    {
        cout<<"The Enviornment variable set Version : v1.1"<<endl;
    }
    else if(strcmp(arg[1],"-mp") == 0)
    {
        if(arg[2] != NULL and arg[3] != NULL)
        {
            make_path(string(arg[2]),string(arg[3]));
        }
        else
        {
            if(arg[2] == NULL)
            {
                cout<<"Expected the path string!"<<endl;
                cout<<"Example command : EnvSetting -mp {path} {path alias}"<<endl;
            }
            else
            {
                cout<<"Expected the path alias"<<endl;
                cout<<"Example command : EnvSetting -mp {path} {path alias}"<<endl;
            }
        }
    }

    else if(strcmp(arg[1], "-ca") == 0)
    {
        if(arg[2] == NULL)
        {
            cout<<"Expected Alias Name"<<endl;
            cout<<"Example command: env -ca {alias name} {alias path}";
        }
        else if(arg[3] == NULL)
        {
            cout<<"Expected Alias Path"<<endl;
            cout<<"Example command: env -ca {alias name} {alias path}";
        }
        else
        {
            create_alias(arg[2],arg[3]);
        }
    }
    else if(strcmp(arg[1], "-dp") == 0)
    {
        if(arg[2] == NULL)
        {
            cout<<"Expected Path Alias"<<endl;
            cout<<"Example command : env -dp {path alias}"<<endl;
        }
        else
        {
            delete_path(string(arg[2]));
        }
    }

    else
    {
        cout<<"No Argument Given"<<endl;
    }

    return 0;

}
