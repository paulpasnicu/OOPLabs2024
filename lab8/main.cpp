#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
#include <cctype>

// convertim sirul la minuscule
std::string toLowerCase(const std::string &str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// separam sirul folosind separatorii
std::vector<std::string> split(const std::string &str, const std::string &separators) {
    std::vector<std::string> words;
    size_t start = str.find_first_not_of(separators), end = start;

    while (start != std::string::npos) {
        end = str.find_first_of(separators, start);
        words.push_back(str.substr(start, end - start));
        start = str.find_first_not_of(separators, end);
    }

    return words;
}

// comparatie pentru coada cu prioritati
struct cmp {
    bool operator()(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) const {
        if (a.second == b.second) {
            return a.first > b.first;
        }
        return a.second < b.second;
    }
};

int main() {
    // citire din fisier
    std::ifstream file("input.txt");
    if (!file) {
        std::cout << "File does not exist" << std::endl;
        return 1;
    }

    std::ostringstream oss;
    oss << file.rdbuf();  // citeste intreg fisierul intr-un string
    std::string phrase = oss.str();
    file.close();

    // definim operatorii
    std::string separators = " ,?!.\n\t";

    // separam fraza in cuvinte
    std::vector<std::string> words = split(phrase, separators);

    // numaram frecventa cuvintelor
    std::map<std::string, int> wordCount;
    for (std::vector<std::string>::iterator it = words.begin(); it != words.end(); ++it) {
        if (!it->empty()) {
            std::string lowerWord = toLowerCase(*it);
            wordCount[lowerWord]++;
        }
    }

    // definim coada cu prioritati cu separatorii definiti
    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int> >, cmp> pq;

    // inseram frecventa cuvintelor in coada cu prioritati
    for (std::map<std::string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it) {
        pq.push(*it);
    }

    // afisam cuvintele sortate dupa frecventa
    while (!pq.empty()) {
        std::cout << pq.top().first << " => " << pq.top().second << std::endl;
        pq.pop();
    }

    return 0;
}
