//для ревью

#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <sstream>

class Reader {
public:
    Reader() : page_count_(1001, 0), total_users_(0) {}

    void AddUser(int user, int page) {
        if (user_base_.count(user)) {
            // Уменьшаем счётчик на старой странице пользователя
            int old_page = user_base_[user];
            if (old_page != page) { // Обновляем только если страница изменилась
                --page_count_[old_page];
                user_base_[user] = page;
                ++page_count_[page];
            }
        }
        else {
            user_base_[user] = page;
            ++page_count_[page];
            ++total_users_;
        }
    }

    double GetStatistic(int user) const {
        double result = 0.0;
        if (user_base_.count(user) != 0) {
            if (user_base_.size() == 1) {
                result = 1;
            }
            else {
                int user_page = user_base_.at(user);
                int users_with_less_pages = 0;

                // Считаем пользователей с меньшим количеством прочитанных страниц
                for (int i = 0; i < user_page; ++i) {
                    users_with_less_pages += page_count_[i];
                }
                result = static_cast<double>(users_with_less_pages) / (total_users_ - 1);

            }
        }
        // Возвращаем долю пользователей с меньшим количеством страниц
        return result;

    }

private:
    std::unordered_map<int, int> user_base_;  // База данных пользователей и страниц
    std::vector<int> page_count_;             // Количество пользователей на каждой странице
    int total_users_;                         // Общее количество пользователей
};

int main() {
    int q;
    std::cin >> q;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line;
    Reader reader;

    for (int i = 0; i < q; ++i) {
        std::getline(std::cin, line);
        std::istringstream line_stream(line);
        std::string command;
        line_stream >> command;

        if (command == "CHEER") {
            int user;
            line_stream >> user;
            std::cout << std::setprecision(6) << reader.GetStatistic(user) << std::endl;
        }
        else if (command == "READ") {
            int user, page;
            line_stream >> user >> page;
            reader.AddUser(user, page);
        }
        else {
            throw std::runtime_error("неверная команда");
        }
    }

    return 0;
}
