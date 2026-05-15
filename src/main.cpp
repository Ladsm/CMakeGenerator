#include "file.h"
#include <iostream>

int main() {
    std::string project_name = get_project_name();
    int type = get_project_type();
    if (!create_project_root(project_name)) {
        return 1;
    }
    switch (type) {
    case 1:
        create_binary_project(project_name); 
        init_git_repository(project_name); break;
    case 2:
        create_library_project(project_name); 
        init_git_repository(project_name);
        break;
    default:
        std::cerr << "Invalid selection.\n"; return 1;
    }
    return 0;
}