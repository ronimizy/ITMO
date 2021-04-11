//
//  main.cpp
//  Lab3
//
//  Created by Георгий Круглов on 10.02.2021.
//

#include <iostream>
#include <map>
#include <vector>
#include "pugixml.hpp"

struct Node {
    double x, y;
    std::vector<std::string> routes;
    
    Node(std::string crd, std::string str) {
        getRoutesFromString(str);
        getCoordinatesFromString(crd);
    }
    
    friend std::ostream& operator<<(std::ostream &lhs, Node &rhs) {
        
        lhs << "x: " << rhs.x << ", y: " << rhs.y;
        
        return lhs;
    }
    
private:
    void getCoordinatesFromString(std::string str) {
        std::vector<double> one;
        
        int i = 0;
        std::string buffer = "";
        
        while (char c = str[i++]) {
            if (c != ',') {
                buffer += c;
            } else {
                one.push_back(std::stod(buffer));
                buffer = "";
            }
        }
        if (buffer != "") {
            one.push_back(std::stod(buffer));
        }
        
        x = one[0];
        y = one[1];
    }
    void getRoutesFromString(std::string str) {
        int i = 0;
        std::string buffer = "";
        
        while (char c = str[i++]) {
            if (c != '.' && c != ',') {
                buffer += c;
            } else {
                routes.push_back(buffer);
                buffer = "";
            }
        }
        if (buffer != "") {
            routes.push_back(buffer);
        }
    }
};

int main(int argc, const char * argv[]) {
    
    pugi::xml_document document;
    pugi::xml_parse_result result = document.load_file("/Users/george/Documents/ITMO/2_sem/Programming/Lab3/Lab3/data.xml");
    
    
    if (result.status != 0) {
        std::cout << "File not loaded, description: " << result.description() << std::endl;
        exit(0);
    }
    
    
    std::vector<Node> nodes;
    std::map<std::string, std::vector<Node>> streets;
    pugi::xml_node set = document.child("dataset");
    
    for (pugi::xml_node station = set.child("transport_station"); station; station = station.next_sibling()) {
        nodes.emplace_back(station.child("coordinates").first_child().value(),
                           station.child("routes").first_child().value());
        
        std::vector<std::string> s;
        std::string str = station.child("location").first_child().value();
        
        int i = 0;
        std::string buffer;
        while (char c = str[i++]) {
            if (c != ',') {
                buffer += c;
            } else {
                s.push_back(buffer);
                buffer = "";
                i++;
            }
        }
        if (buffer != "") {
            s.push_back(buffer);
        }
        
        for (auto &location : s) {
//            if (streets.count(location)) {
//                
//            }
            streets[location].push_back(nodes.back());
        }
    }
    
    for (std::map<std::string, std::vector<Node>>::iterator it = streets.begin(); it != streets.end(); it++) {
        for (auto i : it->second) {
            std::cout << i << '\n';
        }
    }
    
    
    return 0;
}
