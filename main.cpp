
#include <bits/stdc++.h>
#include "#2graph2.h"
//book reference and functions provided from hw 
//function to find difference 
bool pathDifference(const std::string& x, const std::string& y) {
    int countingPath = 0;
    for (std::size_t z = 0; z < x.size(); ++z) {
        if (x[z] != y[z]) {
            ++countingPath;
            if (countingPath > 1) {
                return false;
            }
        }
    }
    return countingPath == 1;
}

//vector function
std::vector<std::string> dictKnuth(const std::string& files) {
    std::ifstream file(files);
    std::vector<std::string> pathDictionary;
    std::string element;

    while (file >> element) {
        pathDictionary.push_back(element);
    }

    return pathDictionary;
}

int retriveIndexes(const std::string& element, const std::vector<std::string>& pathDictionary) {
    auto it = std::find(pathDictionary.begin(), pathDictionary.end(), element);
    return (it != pathDictionary.end()) ? std::distance(pathDictionary.begin(), it) : -1;
}


graph graphFormation(const std::vector<std::string>& pathDictionary) {
    graph wordGraph;

    //adding words
    for (std::size_t x = 0; x < pathDictionary.size(); ++x) {
        wordGraph.add_vertex();
    }

   //loop for condition
    for (std::size_t y = 0; y < pathDictionary.size(); ++y) {
        for (std::size_t z = y + 1; z < pathDictionary.size(); ++z) {
            if (pathDifference(pathDictionary[y], pathDictionary[z])) {
                wordGraph.add_edge(y, z);
            }
        }
    }

    return wordGraph;
}

int main() {
    //build dictionary 
    std::vector<std::string> pathDictionary = dictKnuth("dictionary.txt");

    //graph from dictionary 
    graph wordGraph = graphFormation(pathDictionary);

    //vector of words
    std::vector<std::pair<std::string, std::string>> doublets = {
        {"black", "white"}, {"tears", "smile"}, {"small", "giant"},
        {"stone", "money"}, {"angel", "devil"}, {"amino", "right"},
        {"amigo", "signs"}
    };

    //solving
    for (const auto& doubletsPuzzle : doublets) {
        int location = retriveIndexes(doubletsPuzzle.first, pathDictionary);
      //retrive indexes
      //provided in homework 

        int dest = retriveIndexes(doubletsPuzzle.second, pathDictionary);

      //provided in homework 
        if (location == -1 || dest == -1) {
            std::cout << "This " << doubletsPuzzle.first << " nor " << doubletsPuzzle.second << " is found in the puzzle.\n";
            continue;
        }
//provided in homework 
        std::vector<int> find = wordGraph.shortest_path(location, dest);
        if (find.empty()) {
            std::cout << "\nA path between " << doubletsPuzzle.first << " and " << doubletsPuzzle.second << " doesn't exist"<<".\n";
        } else {
            std::cout << "\nA path from " << doubletsPuzzle.first << " to " << doubletsPuzzle.second << " does exist: \n";
            for (std::size_t x = 0; x < find.size(); ++x) {
                std::cout << pathDictionary[find[x]] << (x == find.size() - 1 ? "\n" : " - ");
            }
        }
    }
    return 0;
}

