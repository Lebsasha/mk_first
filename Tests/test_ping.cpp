#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
int main(int argc, char** argv)
{
    int time = 0;
    std::ofstream dev("/dev/ttyACM0"); //TODO Add uint32_t
    std::ifstream read_dev("/dev/ttyACM0");
    if(!dev)
    {
        std::cout<<"Error opening file"<<std::endl;
        return 1;
    }
    std::vector<size_t> sizes;
    std::ofstream log("res_new_2.csv", std::ios_base::out | std::ios_base::app);
    if (argc > 1)
    {
        for (size_t i = 1; i < argc; ++i)
        {
            sizes.push_back(strtol(argv[i], nullptr, 10));
            if (errno == ERANGE)
                return 1;
        }
    }
    const char* s =
            "01234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123012345678901234567890123456789012345678901234567890123456789012301234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123012345678901234567890123456789012345678901234567890123456789012301234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123012345678901234567890123456789012345678901234567890123456789012301234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123012345678901234567890123456789012345678901234567890123456789012301234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123012345678901234567890123456789012345678901234567890123456789012301234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123012345678901234567890123456789012345678901234567890123456789012301234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123012345678901234567890123456789012345678901234567890123456789012301234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123012345678901234567890123456789012345678901234567890123456789012301234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123012345678901234567890123456789012345678901234567890123456789012301234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123012345678901234567890123456789012345678901234567890123456789012301234567890123456789012345678901234567890123456789012345678901230123456789012345678901234567890123456789012345678901234567890123";
    char read_s[2049] = {0};
    std::string cmd = "213 ";
    for(int j =0; j < 10; ++j)
        for(size_t size_of_packet: sizes)
        {
            cout<<"Begin "<<size_of_packet<<endl;
            dev.write((cmd+to_string(size_of_packet)+' ').c_str(), cmd.length());
            dev.flush();
            dev.write(s, size_of_packet);
            dev.flush();
            read_dev.read(read_s, size_of_packet);
            if(!strcmp(s, read_s))
            {
                read_dev.read(reinterpret_cast<char*>(&time), sizeof(int));
                log << size_of_packet << ", " << static_cast<double>(size_of_packet) * 100'000 / time << ", "
                    << static_cast<double>(time) / 100'000<< std::endl;
            }
        }
}

