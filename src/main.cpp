#include <iostream>
#include <string>


enum validCommands
{
    echo,
    cd,
    exit0,
    type,
    invalid,
};

validCommands isValid(std::string command){
    command = command.substr(0,command.find(" "));

    if(command == "echo") return validCommands::echo;
    if(command == "cd") return validCommands::cd;
    if(command == "exit") return validCommands::exit0;
    if(command == "type") return validCommands::type;

    return invalid;
}

std::string valid[4] = {"echo", "cd", "exit0"};

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

                break;
            case echo:
                input.erase(0,input.find(" ")+1);
                std::cout<<input<<"\n";
                break;
            case exit0:
                exit=true;
                break;
            case type:
                input.erase(0,input.find(" ")+1);
                if(isValid(input) != invalid){
                    std::cout<<input<<" is a shell builin\n";
                }
                else{
                    std::cout<<input<<" not found\n";
                }
                break;
            default:
                std::cout<<input<<": command not found\n";
                break;
        }
    }

}
