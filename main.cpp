// Created by Arseny Polyubin on 3.10.2020.
#include <cstdio>
#include <iomanip>
#include <iostream>
#include "vector.hpp"



const int DIGIT_NUMBER = 11;
void CountingSort(NMyStd::TVector <NMyStd::TItem> &data, int digit) {
        //vector<vector<item>> firstResult(10, vector<item>);
        //item countArray[10];
        unsigned long long countArray[DIGIT_NUMBER];
        for (unsigned int i = 0; i <= DIGIT_NUMBER; ++i) {
            countArray[i] = 0;
        }
        for (int i = 0; i < data.Size(); ++i) {
            countArray[(int)(data[i].Date[digit] - '0')]++;
        }
        for (unsigned int i = 1; i <= DIGIT_NUMBER; ++i) {
            countArray[i] += countArray[i - 1];
        }
        NMyStd::TItem *first_Result = new NMyStd::TItem[data.Size()];
        for (long long i = data.Size() - 1; i >= 0; --i) {
            first_Result[countArray[(int)(data[i].Date[digit] - '0')] - 1] = data[i];
            --countArray[(int)(data[i].Date[digit] - '0')];
        }
        for (long long i = 0; i < data.Size(); ++i) {
            for (int j = 0; j < DATE_LENGTH; ++j) {
                data[i].Date[j] = first_Result[i].Date[j];
            }
            for (int j = 0; j < VALUE_LENGTH; ++j) {
                data[i].Value[j] = first_Result[i].Value[j];
            }
        }

        delete[] first_Result;
}

void DigwiseSort(NMyStd::TVector<NMyStd::TItem> &data) {
        for (int k = DATE_LENGTH - 1; k >= 0; --k) {
            CountingSort(data, k);
        }
}

int main(){
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    NMyStd::TVector<NMyStd::TItem> data;
    char strKey [KEY_LENGTH];
    NMyStd::TItem curr;

    NMyStd::TVector<char*> ValueData;

    while (std::cin >> strKey >> curr.Value) {//sscanf(myarray, "%d.%d.%d", &first, &second, &third);

        sscanf(strKey, "%d.%d.%d", &curr.Day, &curr.Month, &curr.Year);
        sprintf(curr.Date, "%4d%2d%2d", curr.Year, curr.Month, curr.Day);
        for (int i = 0; i < DATE_LENGTH; ++i) {
            if (curr.Date[i] == ' ') {
                curr.Date[i] = '0';
            }
        }
        printf("%s\n", curr.Date);
        data.PushBack(curr);
    }
    DigwiseSort(data);
    for (int i = 0; i < data.Size(); ++i) {
        for (int j = 0; j < KEY_LENGTH; ++j){
            std::cout << std::hex << std::setw(4) << std::setfill('0') << data[i].Key[j];
        }
        std::cout << " " << *data[i].Value << "\n";
    }
    for (int i = 0; i < ValueData.Size(); ++i){
        delete[] ValueData[i];
    }
    return 0;

}


        
