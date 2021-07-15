#include <iostream>
#include <ctime>
#include <iomanip>
#include <map>
#include <vector>

/**
 * @function Return current year in integer.
 * @return integer [year]
 */
int getCurrentYear()
{
    std::time_t today = time(nullptr);
    std::tm* localToday = localtime(&today);
    return localToday->tm_year;
}

/**
 * @function Return the integer of current month [0-11].
 * @return integer [0-11]
 */
int getCurrentMonth()
{
    std::time_t today = time(nullptr);
    std::tm* localToday = localtime(&today);
    return localToday->tm_mon;
}

/**
 * @function Return integer of current day of a month.
 * @return integer [1-31]
 */
int getCurrentDay()
{
    std::time_t today = time(nullptr);
    std::tm* localToday = localtime(&today);
    return localToday->tm_mday;
}

/**
 * @function Make the time_t from integers of day [1-31], month [0-11] and year.
 * @param [in] day
 * @param [in] month
 * @param [in] year
 * @return time_t
 */
std::time_t makeDate(const int day, const int month, const int year)
{
    std::tm local = {};
    local.tm_year = year;
    local.tm_mon = month;
    local.tm_mday = day;

    std::time_t date = std::mktime(&local);
    return date;
}

/**
 * @function Try parse string in format YYYY/MM/DD into date and changes the year to current year.
 * @param [in] input String
 * @return time_t with current year
 */
std::time_t getDate(std::string& input)
{
    std::tm local = {};
    std::stringstream stream(input);
    stream >> std::get_time(&local, "%Y/%m/%d");
    local.tm_year = getCurrentYear();

    if (stream.fail()) {
        return -1;
    } else {
        std::time_t birthday = std::mktime(&local);
        return birthday;
    }
}

/**
 * @function Print the nearest birthday and names to congratulate.
 * @param [in] birthdays Map
 */
void getNearestBirthday(std::map<std::time_t, std::vector<std::string>>& birthdays)
{
    std::cout << "Nearest birthdays:\n";
    if (birthdays.empty())
    {
        std::cout << "No data.\n";
        return;
    }
    std::time_t today = makeDate(getCurrentDay(), getCurrentMonth(), getCurrentYear());
    for (auto & birthday : birthdays)
    {
        std::tm* checkingDate = localtime(&(birthday.first));

        if (birthday.first >= today)
        {
            if (birthday.first == today) std::cout << "TODAY!!!\n";
            else std::cout << std::put_time(checkingDate, "%B %d") << "\n";

            std::cout << "Don't forget to congratulate:\n";
            for (const std::string& name : birthday.second)
            {
                std::cout << "\t -" << name << "\n";
            }
            break;
        }
    }
}

int main()
{
    std::map<std::time_t, std::vector<std::string>> birthdays;

    do
    {
        std::cout << "Please enter the name of your friend:";
        std::string name;
        std::getline(std::cin, name);
        if (name == "end") break;
        else
        {
            std::cout << "Please enter his birthday (YYYY/MM/DD):";
            std::string input;
            std::getline(std::cin, input);
            std::time_t birthday = getDate(input);
            if (birthday == -1)
            {
                std::cout << "Date is incorrect, please try again.\n";
                continue;
            }
            auto i = birthdays.find(birthday);
            if (i == birthdays.end())
            {
                auto* names = new std::vector<std::string>{name};
                birthdays.insert(std::make_pair(birthday, *names));
                delete names;
            }
            else i->second.push_back(name);
        }
    } while (true);

    getNearestBirthday(birthdays);

    return 0;
}