// C++ program to demonstrate working of regex_search()
// after git edit experimental branch
#include <iostream>
#include <regex>
#include <string.h>
#include <fstream>

int main()
{
    // An object of regex for pattern to be searched
    std::regex r("[a-zA-Z][0-9]+");
    std::string fmt= "0$&";
    std::string result;
    std::string line;
    std::ifstream dotfile;
    std::ofstream outfile;
    outfile.open("outfile.dot", std::ofstream::out);
    dotfile.open("memory_conroller.dot",std::ifstream::in);

    if (dotfile.is_open())
    {
        std::cout<<"dotfile is open for the first."<<std::endl;
        while (getline (dotfile,line))
        {

            //std::cout<<line<<std::endl;
            //std::regex_replace (std::back_inserter(result), line.begin(), line.end(), r, "0$&");
            if (/*line.find("clk") > 10000*/1)
            {
                line = std::regex_replace(line, r, fmt);
                //std::regex_replace (std::back_inserter(result), line.begin(), line.end(), r, "0$&");
                //std::cout<<line<<std::endl;
                outfile<<line<<std::endl;
            }
            else
            {
                outfile<<line<<std::endl;
            }
        }
    }
    return 0;
}
