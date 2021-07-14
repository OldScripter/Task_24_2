#include <iostream>
#include <map>
#include <ctime>
#include <vector>
#include <iomanip>

std::time_t getDate(std::string& input)
{
    std::istringstream ss(input);
    std::time_t birthday = std::time(nullptr);
    std::tm local = *std::localtime(&birthday);
    ss >> std::get_time(&local, "%Y/%m/%d");
    if (ss.fail()) {
        std::cerr << "Date parse is failed!\n";
        return -1;
    } else {
        return birthday;
    }

}

std::string getName()
{
    std::string name;
    std::getline(std::cin, name);
    return name;
}

void printNearestBirthday(std::map<std::time_t, std::vector<std::string>>& birthdays)
{
    std::cout << birthdays.size() << "\n";
    std::cout << "Nearest birthday:\n";
    std::time_t today = std::time(nullptr);
    std::map<std::time_t, std::vector<std::string>>::iterator it;
    for (it = birthdays.begin(); it != birthdays.end(); it++)
    {
        std::tm* local = std::localtime(&it->first);
        std::cout << std::put_time(local, "%Y/%m/%d") << "\n";




//        std::tm* local = std::localtime(&it->first);
//        std::tm* localToday = std::localtime(&today);
//        if (local->tm_mon >= localToday->tm_mon && local->tm_mday >= localToday->tm_mday)
//        {
//            if (local->tm_mon == localToday->tm_mon &&
//                local->tm_mday == localToday->tm_mday)
//            {
//                std::cout << "TODAY!\n";
//                std::cout << std::put_time(local, "%B %d");
//            }
//            else
//            {
//                std::cout << std::put_time(local, "%B %d");
//            }
//            for (std::string name : it->second)
//            {
//                std::cout << name << " ";
//            }
//            std::cout << "\n";
//            break;
//        }

    }
    std::cout << "Print is ended\n";
}

int main() {

    std::map<std::time_t, std::vector<std::string>> birthdays;

    do
    {
        std::cout << "Please enter names of your friend or \'end\' command:\n";
        std::string cmd = getName();
        if (cmd == "end") break;
        else
        {
            std::cout << "Please enter his birthday in format [Name YYYY/MM/DD]:\n";
            std::string dateInput;
            std::getline(std::cin, dateInput);
            std::time_t birthday = getDate(dateInput);
            if (birthday == -1) continue;
            else
            {
                auto i = birthdays.find(birthday);
                if (i != birthdays.end()) i->second.push_back(cmd);
                else
                {
                    auto* v = new std::vector<std::string>{cmd};
                    birthdays.insert(std::make_pair(birthday, *v));
                    delete v;
                }
                std::cout << "Date for " << cmd << " is registered." << "\n";
            }
        }
    } while (true);

    printNearestBirthday(birthdays);



    return 0;
}
