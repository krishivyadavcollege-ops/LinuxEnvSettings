#ifndef TASK_H
#define TASK_H

#include <string>

void data_file();
void make_path(std::string path,std::string path_alias);
void create_alias(std::string alias_name, std::string alias_path);
int update_bashrc();
void delete_path(std::string path_alias);

#endif
