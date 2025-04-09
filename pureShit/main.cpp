#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Tasks {
private:
    json data;
    int lastID;
public:
    Tasks() {
        std::ifstream f("user_data.json");
        data = json::parse(f);
        lastID = data["lastID"].get<int>();
        //std::cout << data["tasks"]["1"][1];
    }
    ~Tasks() {
        std::ofstream o("user_data.json");
        o << data.dump(4);  // pretty-print with indent=4
        o.close();
    }

    void add(std::string str) {
        data["tasks"][std::to_string(++lastID)] = { str, "todo" };
        data["lastID"] = lastID;
    }

    void remove(std::string str) {
        data["tasks"].erase(str);
        lastID--;
        data["lastID"] = lastID;
    }

    void order(int& argc, char* argv[]) {
        std::cout << "BEGINING..." << std::endl;
        if (argv[1] == "list") {
            if (argc == 2) {
                for (int i = 1; i <= lastID; i++) {
                    
                    std::cout << i << " : " 
                        << data["tasks"][std::to_string(i)][0].get<std::string>()
                        << " : " << data["tasks"][std::to_string(i)][1].get<std::string>();
                }
            }
            else if (argv[2] == "todo") {
                for (int i = 1; i <= lastID; i++) {
                    if (data["tasks"][std::to_string(i)][1] == "todo") {
                        std::cout << "el: " << data["tasks"][std::to_string(i)][0].get<std::string>()
                            << ": " << data["tasks"][std::to_string(i)][1].get<std::string>();
                    }
                }
            }
            else if (argv[2] == "in-progress") {
                for (int i = 1; i <= lastID; i++) {
                    if (data["tasks"][std::to_string(i)][1] == "in-progress") {
                        std::cout << "el: " << data["tasks"][std::to_string(i)][0].get<std::string>()
                            << ": " << data["tasks"][std::to_string(i)][1].get<std::string>();
                    }
                }
            }
            else if (argv[2] == "done") {
                for (int i = 1; i <= lastID; i++) {
                    if (data["tasks"][std::to_string(i)][1] == "done") {
                        std::cout << "el: " << data["tasks"][std::to_string(i)][0].get<std::string>()
                            << ": " << data["tasks"][std::to_string(i)][1].get<std::string>();
                    }
                }
            }
            
        }
        else if (argv[1] == "add") {
            add(argv[2]);
        }
        else if (argv[1] == "delete") {
            remove(argv[2]);
        }
        else if (argv[1] == "update") {
            std::string index(argv[2]);
            std::string content(argv[3]);
            data["tasks"][index][0] = content;
        }
        else if (argv[1] == "mark-todo") {
            std::string index(argv[2]);
            data["tasks"][index][1] = "todo";
        }
        else if (argv[1] == "mark-in-progress") {
            std::string index(argv[2]);
            data["tasks"][index][1] = "in-progress";
        }
        else if (argv[1] == "mark-done") {
            std::string index(argv[2]);
            data["tasks"][index][1] = "done";
        }
    }
};

int main(int argc, char* argv[])
{
    Tasks obj;
    argv[1] = const_cast<char*>("add");
    argv[2] = const_cast<char*>("groceries");
    
    //argv[1] = const_cast<char*>("list");
    //argc--;

    //argv[1] = const_cast<char*>("delete");
    //argv[2] = const_cast<char*>("1");
    //std::cout << "what a fuck" << std::endl;
    obj.order(argc, argv);
    
    return 0;
}