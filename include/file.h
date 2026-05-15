#pragma once
#include <string>
#include "textblobs.h"

void write_file(const std::string& path, const std::string& content);
std::string get_project_name();
int get_project_type();
void create_binary_project(const std::string& project_name);
void create_library_project(const std::string& project_name);
bool create_project_root(const std::string& project_name);
void init_git_repository(const std::string& project_name);