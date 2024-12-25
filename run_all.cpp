#include <cstdlib>
#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <unistd.h>
#include <chrono>
#include <cstdio>

namespace fs = std::filesystem;

int main() {
    const std::string buildDir = "build";

    std::vector<std::string> fileNames;

    try {
        for (const auto& entry : fs::directory_iterator(buildDir)) {
            if (entry.is_regular_file()) { // Check if it's a file
                fileNames.push_back(entry.path().filename().string());
            }
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }

    if (chdir(buildDir.c_str()) != 0) {
        std::cerr << "Failed to change directory!" << std::endl;
        return 1;
    }

    int d = 0;
    double totalTime = 0.0;
    std::cout << std::left << std::setw(10) << "Day" 
              << std::setw(20) << "First Star"
              << std::setw(40) << "Second Star"
              << std::setw(5) << "Time (ms)" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    for (const auto &fileName : fileNames) {
        ++d;

        FILE* fp = popen(fileName.c_str(), "r");
        if (fp == nullptr) {
            std::cerr << "Failed to run " << fileName << std::endl;
            continue;
        }

        // Capture the output from the program
        char buffer[128];
        std::string output = "";
        while (fgets(buffer, sizeof(buffer), fp) != nullptr) {
            output += buffer;
        }
        pclose(fp);

        // Parse the output
        std::string firstStar, secondStar, timeStr;
        
        std::stringstream ss(output);
        std::string line;
        while (std::getline(ss, line)) {
            if (line.find("First star :") != std::string::npos) {
                firstStar = line.substr(line.find(":") + 2);
            } else if (line.find("Second star :") != std::string::npos) {
                secondStar = line.substr(line.find(":") + 2);
            } else if (line.find("Time :") != std::string::npos) {
                timeStr = line.substr(line.find(":") + 2, line.find("ms") - (line.find(":") + 2));
                totalTime += stod(timeStr);
            }
        }

        std::cout << std::left << std::setw(10) << d
                  << std::setw(20) << firstStar
                  << std::setw(40) << secondStar
                  << std::setw(5) << timeStr << std::endl;
    }


    std::cout << std::endl << "Total time : " << totalTime << "ms" << std::endl;


    return 0;
}