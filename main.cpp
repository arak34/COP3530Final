#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
struct Restaurant {
    string bID, name, address, city, state, postal_code;
    double latitude, longitude, rating;
    int review_count, price_range;
    bool alcohol, bike, bitcoin, credit, parking, caters, dogs, drive_thru, dancing, kids, groups, tv, twenty_four, outdoor, delivery, reservations, table_service, take_out, wifi;
    string categories;
    string mon, tue, wed, thu, fri, sat, sun;
    Restaurant() {
        bID = name = address = city = state = postal_code = "";
        latitude = longitude = rating = 0.0;
        review_count = 0;
        alcohol = bike = bitcoin = credit = parking = caters = dogs = drive_thru = dancing = kids = groups = tv = twenty_four = outdoor = delivery = reservations = table_service = take_out = wifi = false;
    }
    bool operator<(const Restaurant& other) {
        return latitude < other.latitude;
    }
};
struct RestaurantsList {
    vector<string> business_ids;
    vector<Restaurant> restaurants;
    void insert(string bID, Restaurant obj) {
        bool exists = false;
        for (int i = 0; i < restaurants.size(); i++) {
            if (restaurants[i].bID == bID) {
                exists = true;
            }
        }
        if (!exists) {
            restaurants.push_back(obj);
            business_ids.push_back(bID);
        }
        else {
            cout << "error - duplicate business IDs" << endl;
        }
        vectorsort();
    }
    void vectorsort() {
        sort(restaurants.begin(), restaurants.end());
        for (int i = 0; i < business_ids.size(); i++) {
            business_ids[i] = restaurants[i].bID;
        }
    }
    bool compareLat(const Restaurant& a, const Restaurant& b) {
        return a.latitude < b.latitude;
    }
    Restaurant getRestaurant(string bID) {
        long index = 0;
        auto it = find(business_ids.begin(), business_ids.end(), bID);
        if (it != business_ids.end()) {
            index = it - business_ids.begin();
        }
        else {
            cout << "Could not find restaurant" << endl;
        }
        return restaurants[index];
    }
    double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
        lat1 = 3.14 / 180 * lat1;
        lon1 = 3.14 / 180 * lon1;
        lat2 = 3.14 / 180 * lat2;
        lon2 = 3.14 / 180 * lon2;
        double dlon = lon2 - lon1;
        double dlat = lat2 - lat1;
        double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
        double c = 2 * asin(sqrt(a));
        double r = 3956;
        return(c * r);
    }
};


double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    lat1 = 3.14 / 180 * lat1;
    lon1 = 3.14  / 180 * lon1;
    lat2 = 3.14 / 180 * lat2;
    lon2 = 3.14 / 180 * lon2;
    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;
    double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
    double c = 2 * asin(sqrt(a));
    double r = 3956;
    return(c * r);
}
int main() {
    ifstream file("YelpRestaurants.csv");
    if (!file.is_open()) {
        cout << "Unable to open file"  << endl;
        return 1;
    }
    string line = "";
    getline(file, line); 
    unordered_map<string, Restaurant> restaurants;
    RestaurantsList list;
    while (getline(file, line)) {
        istringstream ss(line);
        Restaurant restaurant;
        getline(ss, restaurant.bID, ',');
        getline(ss, restaurant.name, ',');
        getline(ss, restaurant.address, ',');
        getline(ss, restaurant.city, ',');
        getline(ss, restaurant.state, ',');
        getline(ss, restaurant.postal_code, ',');
        string temp;
        getline(ss, temp, ',');
        restaurant.latitude = stod(temp);
        getline(ss, temp, ',');
        restaurant.longitude = stod(temp);
        getline(ss, temp, ',');
        restaurant.rating = stod(temp);
        getline(ss, temp, ',');
        restaurant.review_count = stoi(temp);
        getline(ss, temp, ',');
        restaurant.price_range = stoi(temp);
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.alcohol = true;
        }
        else {
            restaurant.alcohol = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.bike = true;
        }
        else {
            restaurant.bike = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.bitcoin = true;
        }
        else {
            restaurant.bitcoin = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.credit = true;
        }
        else {
            restaurant.credit = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.parking = true;
        }
        else {
            restaurant.parking = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.caters = true;
        }
        else {
            restaurant.caters = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.dogs = true;
        }
        else {
            restaurant.dogs = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.drive_thru = true;
        }
        else {
            restaurant.drive_thru = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.dancing = true;
        }
        else {
            restaurant.dancing = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.kids = true;
        }
        else {
            restaurant.kids = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.groups = true;
        }
        else {
            restaurant.groups = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.tv = true;
        }
        else {
            restaurant.tv = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.twenty_four = true;
        }
        else {
            restaurant.twenty_four = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.outdoor = true;
        }
        else {
            restaurant.outdoor = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.delivery = true;
        }
        else {
            restaurant.delivery = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.reservations = true;
        }
        else {
            restaurant.reservations = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.table_service = true;
        }
        else {
            restaurant.table_service = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.take_out = true;
        }
        else {
            restaurant.take_out = false;
        }
        getline(ss, temp, ',');
        if (temp == "TRUE") {
            restaurant.wifi = true;
        }
        else {
            restaurant.wifi = false;
        }
        getline(ss, restaurant.categories, ',');
        getline(ss, restaurant.mon, ',');
        getline(ss, restaurant.tue, ',');
        getline(ss, restaurant.wed, ',');
        getline(ss, restaurant.thu, ',');
        getline(ss, restaurant.fri, ',');
        getline(ss, restaurant.sat, ',');
        getline(ss, restaurant.sun);
        restaurants[restaurant.bID] = restaurant;
        list.business_ids.push_back(restaurant.bID);
        list.restaurants.push_back(restaurant);
    }
    file.close();
    double userLatitude, userLongitude;
    double desiredDistance;
    cout << "Enter your latitude: ";
    cin >> userLatitude;
    cout << "Enter your longitude: ";
    cin >> userLongitude;
    cout << "Enter the maximum distance (in miles) you consider as 'close': ";
    cin >> desiredDistance;
    Restaurant closestRestaurant;
    bool isRestaurantFound = false;
    int countVar = 0;
    int left = 0;
    int right = restaurants.size() - 1;
    int closestIndex = -1;
    while (left <= right) {
        countVar++;
        int mid = left + (right - left) / 2;
        double distance = calculateDistance(userLatitude, userLongitude, list.restaurants[mid].latitude, list.restaurants[mid].longitude);
        if (distance <= desiredDistance) {
            closestIndex = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    if (closestIndex != -1) {
        closestRestaurant = list.restaurants[closestIndex];
        isRestaurantFound = true;
    }
    cout << endl;
    cout << "************************************************************************************************" << endl;
    cout << endl;
    if (isRestaurantFound) {
        cout << "The amount of iterations is " << countVar << endl;
        cout << "Closest restaurant to your location is: " << closestRestaurant.name << endl;
        cout << "Address: " << closestRestaurant.address << ", " << closestRestaurant.city << ", " << closestRestaurant.state << " " << closestRestaurant.postal_code << endl;
        cout << "Latitude, Longitude: " << closestRestaurant.latitude << ", " << closestRestaurant.longitude << endl;
        cout << "Rating, Review Count: " << closestRestaurant.rating << ", " << closestRestaurant.review_count << endl;
        cout << "Alcohol, Caters, Open 24 Hours, Outdoor Seating: " << (closestRestaurant.alcohol ? "Yes" : "No") << ", " << (closestRestaurant.caters ? "Yes" : "No") << ", " << (closestRestaurant.twenty_four ? "Yes" : "No") << ", " << (closestRestaurant.outdoor ? "Yes" : "No") << endl;
        cout << "Bike parking, Parking: " << (closestRestaurant.bike ? "Yes" : "No") << ", " << (closestRestaurant.parking ? "Yes" : "No") << endl;
        cout << "Accepts Bitcoin, Accepts Credit Cards: " << (closestRestaurant.bitcoin ? "Yes" : "No") << ", " << (closestRestaurant.credit ? "Yes" : "No") << endl;
        cout << "Dog-friendly, Good for Kids, Good for Groups: " << (closestRestaurant.dogs ? "Yes" : "No") << ", " << (closestRestaurant.kids ? "Yes" : "No") << (closestRestaurant.groups ? "Yes" : "No") << endl;
        cout << "Has TV, Wifi: " << (closestRestaurant.tv ? "Yes" : "No") << ", " << (closestRestaurant.wifi ? "Yes" : "No") << endl;
        cout << "Delivery, Reservations, Table Service, Take Out: " << (closestRestaurant.delivery ? "Yes" : "No") << (closestRestaurant.reservations ? "Yes" : "No") << (closestRestaurant.table_service ? "Yes" : "No") << ", " << (closestRestaurant.take_out ? "Yes" : "No") << endl;
        cout << "Categories: " << closestRestaurant.categories << endl;
        cout << "Hours (Mon): " << closestRestaurant.mon << endl;
        cout << "Hours (Tue): " << closestRestaurant.tue << endl;
        cout << "Hours (Wed): " << closestRestaurant.wed << endl;
        cout << "Hours (Thu): " << closestRestaurant.thu << endl;
        cout << "Hours (Fri): " << closestRestaurant.fri << endl;
        cout << "Hours (Sat): " << closestRestaurant.sat << endl;
        cout << "Hours (Sun): " << closestRestaurant.sun << endl;
    }
    else {
        cout << "No restaurants found within your specified distance.\n";
    }
    Restaurant closestRestaurant2;
    bool isRestaurantFound2 = false;
    int countVar2 = 0;
    cout << endl;
    cout << "************************************************************************************************" << endl;
    cout << endl;
    for(auto const& pair: restaurants) {
        countVar2++;
        Restaurant restaurant = pair.second;
        double distance = calculateDistance(userLatitude, userLongitude, restaurant.latitude, restaurant.longitude);
        if (distance <= desiredDistance) {
            closestRestaurant2 = restaurant;
            isRestaurantFound2 = true;
        }
    }
    if (isRestaurantFound2) {
        cout << "The amount of iterations is " << countVar2 << endl;
        cout << "Closest restaurant to your location is: " << closestRestaurant.name << endl;
        cout << "Address: " << closestRestaurant.address << ", " << closestRestaurant.city << ", " << closestRestaurant.state << " " << closestRestaurant.postal_code << endl;
        cout << "Latitude, Longitude: " << closestRestaurant.latitude << ", " << closestRestaurant.longitude << endl;
        cout << "Rating, Review Count: " << closestRestaurant.rating << ", " << closestRestaurant.review_count << endl;
        cout << "Alcohol, Caters, Open 24 Hours, Outdoor Seating: " << (closestRestaurant.alcohol ? "Yes" : "No") << ", " << (closestRestaurant.caters ? "Yes" : "No") << ", " << (closestRestaurant.twenty_four ? "Yes" : "No") << ", " << (closestRestaurant.outdoor ? "Yes" : "No") << endl;
        cout << "Bike parking, Parking: " << (closestRestaurant.bike ? "Yes" : "No") << ", " << (closestRestaurant.parking ? "Yes" : "No") << endl;
        cout << "Accepts Bitcoin, Accepts Credit Cards: " << (closestRestaurant.bitcoin ? "Yes" : "No") << ", " << (closestRestaurant.credit ? "Yes" : "No") << endl;
        cout << "Dog-friendly, Good for Kids, Good for Groups: " << (closestRestaurant.dogs ? "Yes" : "No") << ", " << (closestRestaurant.kids ? "Yes" : "No") << (closestRestaurant.groups ? "Yes" : "No") << endl;
        cout << "Has TV, Wifi: " << (closestRestaurant.tv ? "Yes" : "No") << ", " << (closestRestaurant.wifi ? "Yes" : "No") << endl;
        cout << "Delivery, Reservations, Table Service, Take Out: " << (closestRestaurant.delivery ? "Yes" : "No") << (closestRestaurant.reservations ? "Yes" : "No") << (closestRestaurant.table_service ? "Yes" : "No") << ", " << (closestRestaurant.take_out ? "Yes" : "No") << endl;
        cout << "Categories: " << closestRestaurant.categories << endl;
        cout << "Hours (Mon): " << closestRestaurant.mon << endl;
        cout << "Hours (Tue): " << closestRestaurant.tue << endl;
        cout << "Hours (Wed): " << closestRestaurant.wed << endl;
        cout << "Hours (Thu): " << closestRestaurant.thu << endl;
        cout << "Hours (Fri): " << closestRestaurant.fri << endl;
        cout << "Hours (Sat): " << closestRestaurant.sat << endl;
        cout << "Hours (Sun): " << closestRestaurant.sun << endl;
    } else {
        cout << "No restaurants found within your specified distance.\n";
    }
    return 0;
}
