#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>

#define CMAX 1000000000 

using namespace std;

struct matrix1D {
    long maxSubSum;
    int top_left;
    int bottom_right;
};

void Algorithm_3(vector<vector<int>>& arr, int n, long& max_sum, int& max_k, int& max_i, int& max_l, int& max_j, int avg) {
    vector<vector<long>> T(n, vector<long>(n, 0));
    T[0][0] = arr[0][0] - avg;

    for (int j = 1; j < n; j++) {
        T[0][j] = T[0][j - 1] + arr[0][j] - avg;
    }

    for (int i = 1; i < n; i++) {
        T[i][0] = T[i - 1][0] + arr[i][0] - avg;
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            T[i][j] = arr[i][j] - avg + T[i - 1][j] + T[i][j - 1] - T[i - 1][j - 1];
        }
    }

    max_sum = LONG_MIN;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int l = k; l < n; l++) {
                for (int j = i; j < n; j++) {
                    long sum = T[l][j];
                    if (k > 0) sum -= T[k - 1][j];
                    if (i > 0) sum -= T[l][i - 1];
                    if (k > 0 && i > 0) sum += T[k - 1][i - 1];

                    if (sum > max_sum) {
                        max_sum = sum;
                        max_k = k;
                        max_i = i;
                        max_j = j;
                        max_l = l;
                    }
                }
            }
        }
    }
}

matrix1D DivideAndConquer(const vector<int>& A, int left, int right) {
    if (left == right) {
        return { A[left], left, right };
    }
    int middle = (left + right) / 2;

    matrix1D leftResult = DivideAndConquer(A, left, middle);
    matrix1D rightResult = DivideAndConquer(A, middle + 1, right);

    long leftMaxBorderSum = LONG_MIN, rightMaxBorderSum = LONG_MIN;
    long sum = 0;
    int maxLeft = middle, maxRight = middle + 1;

    for (int i = middle; i >= left; --i) {
        sum += A[i];
        if (sum > leftMaxBorderSum) {
            leftMaxBorderSum = sum;
            maxLeft = i;
        }
    }

    sum = 0;
    for (int j = middle + 1; j <= right; j++) {
        sum += A[j];
        if (sum > rightMaxBorderSum) {
            rightMaxBorderSum = sum;
            maxRight = j;
        }
    }

    matrix1D middleResult = { leftMaxBorderSum + rightMaxBorderSum, maxLeft, maxRight };
    if (leftResult.maxSubSum >= rightResult.maxSubSum && leftResult.maxSubSum >= middleResult.maxSubSum)
        return leftResult;
    else if (rightResult.maxSubSum >= leftResult.maxSubSum && rightResult.maxSubSum >= middleResult.maxSubSum)
        return rightResult;
    else
        return middleResult;
}

void Algorithm_4(vector<vector<int>>& arr, int n, long& max_sum, int& max_k, int& max_i, int& max_l, int& max_j, int avg) {
    max_sum = LONG_MIN;

    for (int left_Col = 0; left_Col < n; left_Col++) {
        vector<int> temp(n, 0);
        for (int right_Col = left_Col; right_Col < n; right_Col++) {
            for (int row = 0; row < n; row++) {
                temp[row] += arr[row][right_Col] - avg;
            }
            matrix1D result = DivideAndConquer(temp, 0, n - 1);
            if (result.maxSubSum > max_sum) {
                max_sum = result.maxSubSum;
                max_k = result.top_left;
                max_l = result.bottom_right;
                max_i = left_Col;
                max_j = right_Col;
            }
        }
    }
}

matrix1D Kadane(const vector<int>& A, int n) {
    long maxSum = LONG_MIN, thisSum = 0;
    int cur_start = 0, start = 0, finish = -1;

    for (int i = 0; i < n; i++) {
        thisSum += A[i];
        if (thisSum < 0) {
            thisSum = 0;
            cur_start = i + 1;
        }
        else if (thisSum > maxSum) {
            maxSum = thisSum;
            start = cur_start;
            finish = i;
        }
    }

    if (finish == -1) {
        maxSum = A[0];
        start = finish = 0;
        for (int i = 1; i < n; i++) {
            if (A[i] > maxSum) {
                maxSum = A[i];
                start = finish = i;
            }
        }
    }

    return { maxSum, start, finish };
}

void Algorithm_5(vector<vector<int>>& arr, int n, long& max_sum, int& max_k, int& max_i, int& max_l, int& max_j, int avg) {
    max_sum = LONG_MIN;

    for (int left_Col = 0; left_Col < n; left_Col++) {
        vector<int> temp(n, 0);

        for (int right_Col = left_Col; right_Col < n; right_Col++) {
            for (int row = 0; row < n; row++) {
                temp[row] += arr[row][right_Col] - avg;
            }

            matrix1D result = Kadane(temp, n);
            if (result.maxSubSum > max_sum) {
                max_sum = result.maxSubSum;
                max_k = result.top_left;
                max_l = result.bottom_right;
                max_i = left_Col;
                max_j = right_Col;
            }
        }
    }
}

bool read_PGM(const string& name, vector<vector<int>>& arr, int& size) {
    ifstream file(name);
    if (!file.is_open()) {
        return false;
    }

    string line;
    getline(file, line);

    getline(file, line);
    istringstream format(line);
    int w, h;
    format >> w >> h;
    size = w;

    getline(file, line);

    arr.resize(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            file >> arr[i][j];
        }
    }
    return true;
}

bool read_Average(const string& name, int& avg) {
    ifstream file(name);
    file >> avg;
    return true;
}

void write_Output(const string& name, long max_sum, int max_k, int max_i, int max_l, int max_j) {
    ofstream outfile(name);
    outfile << max_sum << " " << max_k << " " << max_i << " " << max_l << " " << max_j << endl;
}

int main() {
    ifstream config_File("./Data/HW1_config.txt");
    if (!config_File.is_open()) {
        cerr << "OPEN ERROR" << endl;
        return 1;
    }

    string line;

    while (getline(config_File, line)) {
        istringstream format(line);

        int number;
        string pgm_File, avg_File, result_File;

        format >> number >> pgm_File >> avg_File >> result_File;

        vector<vector<int>> arr;
        int n;
        if (!read_PGM("./Data/" + pgm_File, arr, n)) {
            continue;
        }
        int avg;
        if (!read_Average("./Data/" + avg_File, avg)) {
            continue;
        }

        long max_sum = LONG_MIN;
        int max_i = 0, max_j = 0, max_k = 0, max_l = 0;

        if (number == 3) {
            Algorithm_3(arr, n, max_sum, max_k, max_i, max_l, max_j, avg);
        }
        else if (number == 4) {
            Algorithm_4(arr, n, max_sum, max_k, max_i, max_l, max_j, avg);
        }
        else if (number == 5) {
            Algorithm_5(arr, n, max_sum, max_k, max_i, max_l, max_j, avg);
        }

        write_Output("./Data/" + result_File, max_sum, max_k, max_i, max_l, max_j);
    }
    config_File.close();
    return 0;
}
