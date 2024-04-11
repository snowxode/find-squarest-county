#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct County {
    string name;
    vector<pair<double, double>> border;
};

double calculate_squareness(const vector<pair<double, double>>& border) {
    double min_lat = border[0].first;
    double max_lat = border[0].first;
    double min_lon = border[0].second;
    double max_lon = border[0].second;
    for (auto& point : border) {
        if (point.first < min_lat) {
            min_lat = point.first;
        }
        if (point.first > max_lat) {
            max_lat = point.first;
        }
        if (point.second < min_lon) {
            min_lon = point.second;
        }
        if (point.second > max_lon) {
            max_lon = point.second;
        }
    }
    double width = max_lon - min_lon;
    double height = max_lat - min_lat;
    double rectangle_area = width * height;
    double polygon_area = 0;
    for (int i = 0; i < border.size(); i++) {
        int j = (i + 1) % border.size();
        polygon_area += border[i].first * border[j].second - border[i].second * border[j].first;
    }
    polygon_area /= 2;
    cout << rectangle_area / polygon_area;
    return rectangle_area / polygon_area;
}

int main() {
    ifstream infile("counties.csv");
    vector<County> counties;
    string line;
    while (getline(infile, line)) {
        County county;
        stringstream ss(line);
        string name;
        ss >> name;
        county.name = name;
        while (ss.good()) {
            double lat, lon;
            ss >> lat >> lon;
            county.border.push_back(make_pair(lat, lon));
        }
        counties.push_back(county);
    }
    double max_squareness = 0;
    County squarest_county;
    for (auto& county : counties) {
        double squareness = calculate_squareness(county.border);
        if (squareness > max_squareness) {
            max_squareness = squareness;
            squarest_county = county;
        }
    }
    cout << "The squarest county is " << squarest_county.name << " with a squareness score of " << max_squareness << endl;
    return 0;
}
