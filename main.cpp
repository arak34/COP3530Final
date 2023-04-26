#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iterator>

struct Restaurant {
    std::string address;
    std::string city;
    std::string state;
    std::string postal_code;
    std::string business_id;
    std::string categories;
    int review_count;
    float stars;
    int is_open;
    float latitude;
    float longitude;
    std::string name;
};

int main() {
    std::string csv_file = "YelpRestaurants.csv";
    std::ifstream file(csv_file);

    if (!file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    std::string line;
    std::getline(file, line); // Skip header line

    std::map<std::string, Restaurant> restaurants;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string token;

        Restaurant restaurant;

        std::getline(ss, restaurant.address, ',');
        for (int i = 0; i < 42; ++i) {
            std::getline(ss, token, ','); // Skip unnecessary columns
        }
        std::getline(ss, restaurant.business_id, ',');
        std::getline(ss, restaurant.categories, ',');
        std::getline(ss, restaurant.city, ',');
        for (int i = 0; i < 6; ++i) {
            std::getline(ss, token, ','); // Skip unnecessary columns
        }
        std::getline(ss, token, ',');
        restaurant.is_open = std::stoi(token);
        std::getline(ss, token, ',');
        restaurant.latitude = std::stof(token);
        std::getline(ss, token, ',');
        restaurant.longitude = std::stof(token);
        std::getline(ss, restaurant.name, ',');
        std::getline(ss, restaurant.postal_code, ',');
        std::getline(ss, token, ',');
        restaurant.review_count = std::stoi(token);
        std::getline(ss, token, ',');
        restaurant.stars = std::stof(token);
        std::getline(ss, restaurant.state, ',');

        restaurants[restaurant.name] = restaurant;
    }

    file.close();

    // Example: print all restaurant names
    for (const auto& restaurant_pair : restaurants) {
        std::cout << "Name: " << restaurant_pair.first << std::endl;
    }

    return 0;
}
