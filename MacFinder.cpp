#include <iostream>
#include<string>
#include <vector>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <set>
#include <algorithm>
#include <iterator>

typedef struct //struct for menu output
{
    std::string menu_text;
    int menu_num;    
}MENU;

MENU cl_menu(char cl_command) //menu for open files or exit
{
    cl_command = tolower(cl_command);
    MENU main_menu;    
    switch (cl_command)
    {
    case ('e'):
        main_menu.menu_text = "Goodbye!";
        main_menu.menu_num = 0;
        break;
    case ('o'):
        main_menu.menu_text = "Enter first file name: ";
        main_menu.menu_num = 1;
        break;
    default:
        main_menu.menu_text = "Input error";
        main_menu.menu_num = 2;
        break;
    }
    return main_menu;
}
MENU cl_operation_menu(char cl_operation_command) //menu for file operations
{
    cl_operation_command = tolower(cl_operation_command);
    MENU operation_menu;
    switch (cl_operation_command)
    {
    case ('c'):
        operation_menu.menu_text = "Coincidence result: ";
        operation_menu.menu_num = 0;
        break;
    case ('d'):
        operation_menu.menu_text = "Difference result: ";
        operation_menu.menu_num = 1;
        break;
    default:
        operation_menu.menu_text = "Operation error";
        operation_menu.menu_num = 2;
        break;
    }
    return operation_menu;
}

std::vector<std::string> coincidence(std::vector<std::string> first_file_content, std::vector<std::string>second_file_content)
{    
    std::set<std::string> ff_content(first_file_content.begin(), first_file_content.end());
    std::set<std::string> sf_content(second_file_content.begin(), second_file_content.end());
    std::set<std::string> result_set;
    std::set_intersection(begin(ff_content), end(ff_content), begin(sf_content), end(sf_content), std::inserter(result_set, begin(result_set)));
    std::vector<std::string> result_vector(result_set.begin(), result_set.end());
    return result_vector;
}


std::vector<std::string> open_file(std::string file_path) //open file & translate data to vector
{
    std::ifstream file{};
    std::string line;
    std::vector<std::string> file_content;
    file.open(file_path);
    if (file.is_open())
    {
        while (std::getline(file, line))
            file_content.push_back(line);
        return file_content;
    }
    else
    {
        std::cout << "File open error" << std::endl;
        exit(0);
    }
    
}

int main()
{
    MENU menu_response, operation_menu_response; //create menus
    std::string file_path;
    std::vector<std::string> first_file_content, second_file_content;
menu:
    system("cls");
    std::cout << "[O]pen\t[E]xit" << std::endl;    
    std::cout << "----------------------------------------" << std::endl;
    std::cout << std::endl;

    char cl_command = _getch(); //input menu command 
    menu_response = cl_menu(cl_command); //processing command in menu function
    switch (menu_response.menu_num) 
    {
    case (0):
        exit(0);        
    case (1):
        std::cout << menu_response.menu_text << std::endl;
        std::getline(std::cin, file_path);
        first_file_content = open_file(file_path);
        std::cout << std::endl;
        std::cout << "Enter second file name: " << std::endl;
        std::getline(std::cin, file_path);
        second_file_content = open_file(file_path);
        std::cout << std::endl;        
        break;
    case (2):
        goto menu;
        break;
    default:
        break;
    }

    int min_size, max_size, file_size_index;
    std::string empty_stroke = "-----------------";
    if (first_file_content.size() >= second_file_content.size()) //definition vectors size
    {
        max_size = first_file_content.size();
        min_size = second_file_content.size();
        file_size_index = 0;
    }
    else
    {
        max_size = second_file_content.size();
        min_size = first_file_content.size();
        file_size_index = 1;
    }
    if (file_size_index == 0) // additional recording if vector to short
    {
        if (min_size < 11)
        {
            for (int i = (min_size - 1); i < 11; i++)
                second_file_content.push_back(empty_stroke);
        }
        if (max_size < 11)
        {
            for (int i = (min_size - 1); i < 11; i++)
                first_file_content.push_back(empty_stroke);
        }
    }
    if (file_size_index == 1) // additional recording if vector to short
    {
        if (min_size < 11)
        {
            for (int i = (min_size - 1); i < 11; i++)
                first_file_content.push_back(empty_stroke);
        }
        if (max_size < 11)
        {
            for (int i = (min_size - 1); i < 11; i++)
                second_file_content.push_back(empty_stroke);
        }
    }

    system("cls");
    std::cout << "[C]oincidence\t[D]ifference" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "1st file content:\t\t\t2nd file content:" << std::endl;
    std::cout << std::endl;  


    for (int i = 0; i < 11; i++) //print vectors
    {
        std::cout << first_file_content[i] + "\t\t\t" + second_file_content[i] << std::endl;
    }
    char cl_operation_command = _getch(); //input menu command
    
    std::vector<std::string> result;
    operation_menu_response = cl_operation_menu(cl_operation_command); //processing command in menu function
    switch (operation_menu_response.menu_num)
    {
    case (0):
        result = coincidence(first_file_content, second_file_content);
        system("cls");
        std::cout << "Operation result:" << std::endl;
        std::cout << std::endl;
        for (int i = 0; i < result.size(); i++)
            std::cout << result[i] << std::endl;
        break;
    case (1):        
        break;    
    default:
        std::cout << "Output error";
        break;
    } 


    

    return 0;
}


