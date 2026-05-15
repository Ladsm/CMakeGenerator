#include <iostream>
#include <fstream>
#include <filesystem>
#include <limits>
#include "file.h"

namespace fs = std::filesystem;

void write_file(const std::string& path, const std::string& content) {
    fs::path p(path);
    if (!p.parent_path().empty()) {
        fs::create_directories(p.parent_path());
    }
    std::ofstream file(path, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        std::cerr << "Failed to create file: " << path << '\n';
        return;
    }
    file << content;
    if (!file) {
        std::cerr << "Failed to write file: " << path << '\n';
    }
}

std::string get_project_name() {
    std::string name;
    std::cout << "Project name: ";
    std::getline(std::cin, name);
    return name;
}

int get_project_type() {
    int type = 0;
    std::cout << "Select type:\n";
    std::cout << "1. Binary\n";
    std::cout << "2. Library\n";
    std::cout << "> ";
    if (!(std::cin >> type)) {
        return 0;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return type;
}

void create_binary_project(const std::string& project_name) {
    fs::create_directories(project_name + "/src");
    fs::create_directories(project_name + "/include");
    write_file(
        project_name + "/CMakeLists.txt",
        make_binary(project_name)
    );
    write_file(
        project_name + "/src/main.cpp",
        R"(#include <iostream>
int main() {
    std::cout << "Hello, World!\n";
    return 0;
}
)"
);
    std::cout << "Binary project created successfully.\n";
}

void create_library_project(const std::string& project_name) {
    fs::create_directories(project_name + "/include");
    fs::create_directories(project_name + "/src");
    fs::create_directories(project_name + "/Demo");
    fs::create_directories(project_name + "/cmake");
    write_file(
        project_name + "/CMakeLists.txt",
        make_library(project_name)
    );
    write_file(
        project_name + "/cmake/" + project_name + "Config.cmake",
        make_config(project_name)
    );
    write_file(
        project_name + "/Demo/Demo.cpp",
        R"(#include <iostream>
int main() {
    std::cout << "Library demo\n";
    return 0;
}
)"
);
    std::cout << "Library project created successfully.\n";
}

bool create_project_root(const std::string& project_name) {
    if (fs::exists(project_name)) {
        std::cerr << "Directory already exists.\n";
        return false;
    }
    fs::create_directories(project_name);
    return true;
}

void init_git_repository(const std::string& project_name) {
    int create_git = 0;
    std::cout << "Create git?\n0 - Yes\n1 - No\n";
    std::cin >> create_git;
    if (!create_git == 1) {
        fs::path old_path = fs::current_path();
        fs::current_path(project_name);
        int result = std::system("git init");
        if (result == 0) {
            std::cout << "Git repository initialized.\n";
        }
        else {
            std::cerr << "Failed to initialize git repository.\n";
        }
        write_file(
            ".gitignore",
            R"(build/
out/
build/
.vscode/
.vs/
.idea/
*.o
*.obj
*.exe
*_i.c
*_p.c
*_h.h
*.ilk
*.meta
*.obj
*.iobj
*.pch
*.pdb
*.ipdb
*.pgc
*.pgd
*.rsp
*.sbr
*.tlb
*.tli
*.tlh
*.tmp
*.tmp_proj
*_wpftmp.csproj
*.log
*.vspscc
*.vssscc
.builds
*.pidb
*.svclog
*.scc
)"
);
        std::system("git add .");
        std::system("git commit -m \"Initial commit\"");
        fs::current_path(old_path);
    }
}