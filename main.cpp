#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <limits>

struct Restaurant {
    std::string address;
    bool alcohol;
    bool caters;
    bool dogs_allowed;
    bool drive_through;
    bool good_for_dancing;
    bool good_for_kids;
    bool happy_hour;
    bool has_tv;
    std::string noise_level;
    bool open_24_hours;
    bool outdoor_seating;
    bool delivery;
    bool good_for_groups;
    int price_range;
    bool reservation;
    bool wifi;
    std::string business_id;
    std::string categories;
    std::string city;
    std::string hours_friday;
    std::string hours_monday;
    std::string hours_saturday;
    std::string hours_sunday;
    std::string hours_thursday;
    std::string hours_tuesday;
    std::string hours_wednesday;
    double latitude;
    double longitude;
    std::string name;
    int postal_code;
    int review_count;
    double stars;
    std::string state;
};

double haversine_distance(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0;
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    double a = std::sin(dLat / 2) * std::sin(dLat / 2) +
               std::cos(lat1 * M_PI / 180.0) * std::cos(lat2 * M_PI / 180.0) *
               std::sin(dLon / 2) * std::sin(dLon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return R * c;
}

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool str_to_bool(const std::string& s) {
    return s == "True" || s == "true" || s == "1";
}

void read_csv(const std::string& file_name, std::unordered_map<std::string, Restaurant>& hash_table) {
    std::ifstream file(file_name);
    std::string line;

    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::vector<std::string> tokens = split(line, ',');

        Restaurant r;
        r.address = tokens[0];
        r.alcohol = str_to_bool(tokens[1]);
        r.caters = str_to_bool(tokens[2]);
        r.dogs_allowed = str_to_bool(tokens[3]);
        r.drive_through = str_to_bool(tokens[4]);
        r.good_for_dancing = str_to_bool(tokens[5]);
        r.good_for_kids = str_to_bool(tokens[6]);
        r.happy_hour = str_to_bool(tokens[7]);
        r.has_tv = str_to_bool(tokens[8]);
        r.noise_level = tokens[9];
        r.open_24_hours = str_to_bool(tokens[10]);
        r.outdoor_seating = str_to_bool(tokens[11]);
        r.delivery = str_to_bool(tokens[12]);
        r.good_for_groups = str_to_bool(tokens[13]);
        r.price_range = std::stoi(tokens[14]);
        r.reservation = str_to_bool(tokens[15]);
        r.wifi = str_to_bool(tokens[16]);
        r.business_id = tokens[17];
        r.categories = tokens[18];
        r.city = tokens[19];
        r.hours_friday = tokens[20];
        r.hours_monday = tokens[21];
        r.hours_saturday = tokens[22];
        r.hours_sunday = tokens[23];
        r.hours_thursday = tokens[24];
        r.hours_tuesday = tokens[25];
        r.hours_wednesday = tokens[26];
        r.latitude = std::stod(tokens[27]);
        r.longitude = std::stod(tokens[28]);
        r.name = tokens[29];
        r.postal_code = std::stoi(tokens[30]);
        r.review_count = std::stoi(tokens[31]);
        r.stars = std::stod(tokens[32]);
        r.state = tokens[33];

        hash_table[r.business_id] = r;
    }
}

int main() {
    std::unordered_map<std::string, Restaurant> hash_table;
    read_csv("YelpRestaurants.csv", hash_table);

    double user_latitude, user_longitude;
    std::cout << "Enter your latitude: ";
    std::cin >> user_latitude;
    std::cout << "Enter your longitude: ";
    std::cin >> user_longitude;

    const double search_radius = 5.0; // Search radius in km
    Restaurant best_restaurant;
    double min_distance = std::numeric_limits<double>::max();

    for (const auto& kv : hash_table) {
        const Restaurant& r = kv.second;
        double distance = haversine_distance(user_latitude, user_longitude, r.latitude, r.longitude);

        if (distance <= search_radius && distance < min_distance) {
            min_distance = distance;
            best_restaurant = r;
        }
    }

    if (min_distance == std::numeric_limits<double>::max()) {
        std::cout << "No restaurants found within " << search_radius << " km radius." << std::endl;
    } else {
        std::cout << "Best restaurant found: " << best_restaurant.name << std::endl;
        std::cout << "Address: " << best_restaurant.address << std::endl;
        std::cout << "Distance: " << min_distance << " km" << std::endl;
    }

    return 0;
}
