#include <iostream>
#include <string>
#include <sstream>
#include <filesystem>
#include <stdio.h>

using namespace std;

enum validCommands
{
    echo,
    cd,
    exit0,
    pwd,
    type,
    invalid,
};

validCommands isValid(std::string command){
    command = command.substr(0,command.find(" "));

    if(command == "echo") return validCommands::echo;
    if(command == "cd") return validCommands::cd;
    if(command == "exit") return validCommands::exit0;
    if(command == "type") return validCommands::type;
    if(command == "pwd") return validCommands::pwd;

    return invalid;
}

std::string valid[5] = {"echo", "cd", "exit0", "pwd", "type"};

std::string cwd = filesystem::current_path().string();

std::string get_path(std::string command){
    std::string path_env = std::getenv("PATH");

    std::stringstream ss(path_env);
    std::string path;

    while(!ss.eof()){
        getline(ss, path, ':');

        string abs_path = path + '/' + command;

        if(filesystem::exists(abs_path)){
            return abs_path;
        }
    }
    return "";  
}

int main() {

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    // std::cout << "Logs from your program will appear here!\n";

    bool exit = false;

    while (!exit){
        // Flush after every std::cout / std:cerr
        std::cout << std::unitbuf;
        std::cerr << std::unitbuf;
        std::cout << "$ ";
        std::string input;
        std::getline(std::cin, input);

        switch(isValid(input)){
            case cd:
                {
                string dir = input.substr(input.find(" ")+1); 

                if(filesystem::is_directory(dir)){
                    // Change directory
                    filesystem::current_path(dir);
                    cwd = dir;
                }   
                else{
                    std::cout<<"cd: "<<dir<<": No such file or directory.";
                }
                break;
                }
            case echo:
                input.erase(0,input.find(" ")+1);
                std::cout<<input<<"\n";
                break;
            case exit0:
                exit=true;
                break;
            case pwd:
                std::cout<<cwd<<endl;
            case type:
                input.erase(0,input.find(" ")+1);
                if(isValid(input) != invalid){
                    std::cout<<input<<" is a shell builtin\n";
                }
                else{
                    std::string path = get_path(input);

                    if(path.empty()){
                        std::cout<<input<<": not found\n";
                    }
                    else{
                        std::cout<<input<<" is "<<path<<std::endl;
                    }
                }
                break;
            default:
                string command = input.substr(0,input.find(" "));

                string path = get_path(command);

                if(path.empty()){
                    std::cout<<input<<": command not found\n";
                }
                else{
                    string full = path + input.substr(command.length());

                    char buffer[128];
                    string result;

                    FILE *pipe = popen(full.c_str(), "r");

                    while(!feof(pipe)){
                        if(fgets(buffer, 128, pipe) != NULL){
                            cout<<buffer;
                        }
                    }

                    pclose(pipe);
                }
                break;
        }
    }

}
