/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-05-09 17:39:11
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-05-09 18:17:26
 * @FilePath: /WordsFrequency/word_frequency.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
// файл wordstat.cpp

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include "log_duration.h"
#include <unordered_map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

vector<pair<string, int>> GetSortedWordCounts(vector<string> words) {
    unordered_map<string, int> counts_map;

    {
        LOG_DURATION("Filling"s);
        for (auto& word : words) {
            ++counts_map[move(word)];
     }
    }

    {
        LOG_DURATION("Moving & sorting"s);


        vector<pair<string, int>> counts_vector(move_iterator(counts_map.begin()), move_iterator(counts_map.end()));
        sort(counts_vector.begin(), counts_vector.end(), [](const auto& l, const auto& r) {
            return l.second > r.second;
        });

        return counts_vector;
    }

    
}

int main() {
    vector<string> words;
    string word;
    
    ifstream text_file ("canterbury.txt");
    ofstream myfile ("words.txt");
    if (text_file.is_open())
    {
        while (text_file >> word) {
         words.push_back(word);
        }

        auto counts_vector = GetSortedWordCounts(move(words));

        cout << "Слово - Количество упоминаний в тексте"s << endl;
        // выводим первые 10 слов
        for (auto [iter, i] = tuple(counts_vector.begin(), 0); i < 10 && iter != counts_vector.end(); ++i, ++iter) {
            cout << iter->first << " - "s << iter->second << endl;
        }
        for (auto [iter, i] = tuple(counts_vector.begin(), 0); iter != counts_vector.end(); ++i, ++iter) {
            if(iter->first.size() == 5){
                myfile << iter->first << " - "s << iter->second << endl;
            }
        }
    }else{
        cout << "Unable to open file"; 
    }
}