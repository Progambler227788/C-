#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

void generatePermutations(std::string current, int length, std::vector<std::string>& permutations) {
    if (current.length() == length) {
        permutations.push_back(current);
        return;
    }

    for (char ch = 'a'; ch <= 'z'; ++ch) {
        generatePermutations(current + ch, length, permutations);
    }
}


int main()
{
    string b;
    cout<<"enter a number"<<endl;
    cin >> b;

    std::unordered_set<char> uniqueDigits;
    std::string uniqueNumber = "";

    for (char digit : b) {
        if (uniqueDigits.find(digit) == uniqueDigits.end()) {
            uniqueDigits.insert(digit);
            uniqueNumber += digit;
        }
    }

    int result = std::stoi(uniqueNumber);
    std::cout << "Original number: " << b << std::endl;
    std::cout << "Unique number: " << result << std::endl;

    int length = std::to_string(result).length();

    std::vector<std::string> permutations;
    if (length >= 0 && length <= 9) {
        generatePermutations("", length, permutations);
        std::cout << "possible Permutations : " << permutations.size() << "\n";
    } else {
        std::cout << "Invalid input. Length should be between 0 and 9." << std::endl;
    }
    
    
    string tofind = "red";
    int i = 0;
    
    for (const auto& permutation : permutations) {
        if(permutation == tofind){
            break;
        }
        i++;
    }

    std::cout << "actual result : " << i << "\n";
    
    
    

    return 0;
}