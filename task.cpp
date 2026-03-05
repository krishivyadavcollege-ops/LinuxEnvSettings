#include"task.h"
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>
#include <format>
#include <string>
#include <vector>

using namespace std;

int update_bashrc()
{
    try{
    const char* env = getenv("HOME");
    string bashrc_path = (env) ? string(env) + "/.bashrc" : ".bashrc";
    ifstream f1("buffer.txt");
    ofstream f2(bashrc_path);

    if(!f1.is_open()) {cout<<"buffer.txt didnt open"<<endl;return 1;}
    if(!f2.is_open()) {cout<<"Basrc file didnt open"<<endl;return 1;}

    string line;
    while(getline(f1,line))
    {
        f2<<line<<endl;
    }
    cout<<"file 2 updated"<<endl;
    f1.close();
    f2.close();

    if(system("bash -c 'source ~/.bahsrc'") == 0)
    {
        cout<<"Bashrc Updated"<<endl;
    }

    return 0;
    }
    catch(exception &e)
    {
        cerr<<"Error Occured whilw writing file: "<<e.what()<<endl;
        return 1;
    }

}


void data_file()
{
    string bshrc_File_path ;
    const char *env = getenv("HOME");
     if(env != NULL)
     {
     bshrc_File_path = (env != NULL) ? string(env) + "/.bashrc" : ".bashrc";
     }
     else {
     bshrc_File_path = ".bashrc";
}

    ifstream bashrc_File(bshrc_File_path);
    ofstream buffer_bashrc("buffer.txt");
    string line;

    if(!bashrc_File.is_open()) {cout<<"Bashrc File Didnt Open"<<endl;return ;}
    if(!buffer_bashrc.is_open()) {cout<<"Buffer File Didnt Open"<<endl;return ;}

    while(getline(bashrc_File,line))
    {
        //cout<<line<<endl;
        buffer_bashrc<<line<<endl;
    }
    bashrc_File.close();
    buffer_bashrc.close();


}

void make_path(string path, string path_alias)
{
        string path_in_quotation = R"(")" + path + R"(")";
        string l1 = format("export {}_root={}",path_alias,path_in_quotation);
        string l2 = format("export PATH=${}_root:$PATH",path_alias);
        ofstream buffer_bashrc("buffer.txt",ios::app);
        buffer_bashrc<<l1<<endl;
        buffer_bashrc<<l2<<endl;
        buffer_bashrc.close();

        if(update_bashrc() == 0)
        {
        string comment = format("Path Created {}",path_alias);
            cout<<comment<<endl;
        }
        else
        {
            cerr<<"Error Occured"<<endl;
        }
}

void create_alias(std::string alias_name, std::string alias_path)
{
    string to_append = format("alias {}='{}'",alias_name,alias_path);
    ofstream f("buffer.txt",ios::app);
    f<<to_append<<endl;
    f.close();
    if(update_bashrc() == 0)
    {
        cout<<"Alias Created"<<alias_name<<endl;
    }
    else {
    cout<<"Error Occured"<<endl;
}
}

void delete_path(string path_alias)
{
    ifstream f1("buffer.txt");
    if(!f1.is_open())
    {
        cout<<"buffer.txt couldnt open"<<endl;
        return ;
    }
    string line;
    vector<string> linedata;
    string to_find1 = path_alias + "_root";
    string to_find2 = "$"+path_alias + "_root$PATH";
    int number_of_lines = 0;
    while(getline(f1,line))
    {

        if(line.find(to_find1) != string::npos)
        {
            cout<<number_of_lines<<". found "<<path_alias<<"_root"<<endl;
            number_of_lines +=1;
            continue;
        }
        else if(line.find(to_find2) != string::npos)
        {
            cout<<number_of_lines<<". found "<<"$"<<path_alias<<"_root$PATH"<<endl;
            number_of_lines +=1;
            continue;
        }
        else
        {
            //cout<<number_of_lines<<". Appending "<<line<<endl;
            number_of_lines +=1;
            linedata.push_back(line);
        }
    }
    f1.close();
    ofstream f2("buffer.txt");
    if(!f2.is_open())
    {
        cout<<"buffer.txt couldnt open to write"<<endl;
        return ;
    }
    for(string l :linedata)
    {
        f2<<l<<endl;
    }

    if(update_bashrc() == 0)
    {
         cout<<"Deleted the path for "<<path_alias<<endl;
    }
    else
    {
        cerr<<"Some error occured while writing bashrc"<<endl;
    }


}
