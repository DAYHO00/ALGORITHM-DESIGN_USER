#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int single = 0, LT = 150, LT_AND_RT = 300, RT = 450;

void LPS_CALCULATE(const int len, const string& str, int& LPS_length, string& LPS_string) {

    vector<vector<int>> Len_Table(len, vector<int>(len, 0)); // LPS 길이를 저장하는 테이블
    vector<vector<int>> Pal_Table(len, vector<int>(len, 0)); // 회문 추적을 위한 상태를 저장하는 테이블

    string left_str; // LPS의 왼쪽 절반 문자열
    string right_str; // LPS의 오른쪽 절반 문자열

    // 길이가 1인 부분 문자열에 대해 초기화
    for (int i = 0; i < len; i++) {

        Len_Table[i][i] = 1;
        Pal_Table[i][i] = single;

    }

    // 길이가 2인 부분 문자열에 대해 초기화
    for (int i = 0; i < len - 1; i++) {

        if (str[i] == str[i + 1]) {
            Len_Table[i][i + 1] = 2;
            Pal_Table[i][i + 1] = LT_AND_RT;
        }
        else {
            Len_Table[i][i + 1] = 1;
            Pal_Table[i][i + 1] = LT;
        }

    }

    // 길이가 3 이상인 부분 문자열에 대해 DP 테이블 채우기
    for (int k = 2; k < len; k++) {
        for (int i = 0; i < len - k; i++) {
            int j = i + k;

            if (str[i] == str[j]) {
                Len_Table[i][j] = Len_Table[i + 1][j - 1] + 2;
                Pal_Table[i][j] = LT_AND_RT;
            }
            else if (Len_Table[i + 1][j] >= Len_Table[i][j - 1]) {
                Len_Table[i][j] = Len_Table[i + 1][j];
                Pal_Table[i][j] = LT;
            }
            else {
                Len_Table[i][j] = Len_Table[i][j - 1];
                Pal_Table[i][j] = RT;
            }
        }
    }


    int left = 0;
    int right = len - 1;

    while (left <= right) {

        switch (Pal_Table[left][right]) {

        case single: // 단일 문자 상태
            left_str += str[left];
            left++;
            break;

        case LT: // 왼쪽 문자 제외 상태
            left++;
            break;

        case RT: // 오른쪽 문자 제외 상태
            right--;
            break;

        case LT_AND_RT: // 양쪽 문자 모두 포함 상태
            left_str += str[left];
            right_str += str[right];
            left++;
            right--;
            break;
        }

    }

    reverse(right_str.begin(), right_str.end());

    LPS_string = left_str + right_str; // LPS 완성 
    LPS_length = LPS_string.length(); // LPS 길이 저장

}

int main() {

    ifstream file_line("LPS_command.txt");
    if (!file_line.is_open()) {
        cout << "WARNING: File Open Error\n";
        return 1;
    }

    int count;
    file_line >> count;


    for (int i = 0; i < count; i++) {

        string inputFile, outputFile;
        file_line >> inputFile >> outputFile;
        ifstream input_line(inputFile);
        ofstream output_line(outputFile);


        if (!input_line.is_open() || !output_line.is_open()) {
            cout << "WARNING: File Open Error\n";
            return 1;
        }

        int num;
        input_line >> num;
        output_line << num << "\n";

        for (int i = 0; i < num; i++) {
            int length;
            string str;

            input_line >> length >> str;

            int LPS_len;
            string LPS_string;

            LPS_CALCULATE(length, str, LPS_len, LPS_string);

            output_line << LPS_len << "\n" << LPS_string << "\n";
        }

        input_line.close();
        output_line.close();
    }

    file_line.close();
    return 0;
}