#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

vector<pair<int, int>> edges;
vector<vector<int>> table;

typedef struct _Pt {
    double x;
    double y;
} Pt;

double dist(Pt a, Pt b, int a_Idx, int b_Idx) {
    if (abs(a_Idx - b_Idx) <= 1) {
        return 0;
    }
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
    if (a.first != b.first) {
        return a.first < b.first; 
    }
    return a.second < b.second; 
}


void add_Edges(int a, int b, int n) {
    
    // 첫 번째 분할이 유효한 경우
    if (table[a * n + b][0] > -1 && table[a * n + b][1] > -1) {
        edges.push_back({ table[a * n + b][0], table[a * n + b][0] + table[a * n + b][1] });
        add_Edges(table[a * n + b][0], table[a * n + b][1], n);
    }

    // 두 번째 분할이 유효한 경우
    if (table[a * n + b][2] > -1 && table[a * n + b][3] > -1) {
        edges.push_back({ table[a * n + b][2], table[a * n + b][2] + table[a * n + b][3] });
        add_Edges(table[a * n + b][2], table[a * n + b][3], n);
    }
}

double tri_Cost(int i, int s, int n, Pt* pts, double** dp) {
    
    if (s < 2) {
        return 0;
    }

    if (dp[i][s] != -1) {
        return dp[i][s];
    } //base case

    double result = numeric_limits<double>::max();

    for (int k = 1; s - k >= 1; k++) {
        double tempCost = tri_Cost(i, k, n, pts, dp) + tri_Cost(i + k, s - k, n, pts, dp) + dist(pts[i], pts[i + k], i, i + k) + dist(pts[i + k], pts[i + s], i + k, i + s);
        // 첫 번째 부분 문제 +  두 번째 부분 문제
        if (result > tempCost) {
            result = tempCost;

            // 분할 정보 저장
            table[i * n + s][0] = (k > 1) ? i : -1;  // 첫 번째 부분 문제의 시작 인덱스
            table[i * n + s][1] = (k > 1) ? k : -1;  // 첫 번째 부분 문제의 길이
            table[i * n + s][2] = (s - k > 1) ? (i + k) : -1;  // 두 번째 부분 문제의 시작 인덱스
            table[i * n + s][3] = (s - k > 1) ? (s - k) : -1; // 두 번째 부분 문제의 길이
        }
    }

    dp[i][s] = result;

    return result;
}

double minTriCost(int n, Pt* pts, double** dp) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }

    table.resize(n * n, vector<int>(4, -1));

    return tri_Cost(0, n - 1, n, pts, dp);
}

int main() {
    ifstream file_line("MT_command.txt");

    if (!file_line.is_open()) {
        cout << "WARNING: File Open Error\n";
        return 1;
    }

    int count;

    file_line >> count;

    for (int i = 0; i < count; i++) {
        int n;
        string inputFile, outputFile;
        file_line >> inputFile >> outputFile;
        ifstream input_line(inputFile);
        ofstream output_line(outputFile);

        if (!input_line.is_open() || !output_line.is_open()) {
            cout << "WARNING: File Open Error\n";
            return 1;
        }

        input_line >> n;

        if (n <= 3) {
            output_line << 0 << '\n';
            return 1;
        }

        Pt* pts = new Pt[n];
        for (int i = 0; i < n; i++) {
            input_line >> pts[i].x >> pts[i].y;
        }

        double** dp = new double* [n];
        for (int i = 0; i < n; i++) {
            dp[i] = new double[n];
        }

        double result = minTriCost(n, pts, dp);

        output_line << fixed << setprecision(3) << result << "\n";

        add_Edges(0, n - 1, n);

        sort(edges.begin(), edges.end(), cmp);

        for (const auto& edge : edges) {
            output_line << edge.first << " " << edge.second << "\n";
        }

        for (int i = 0; i < n; i++) {
            delete[] dp[i];
        }
        delete[] dp;
        delete[] pts;

        edges.clear();
    }

    file_line.close();
    return 0;
}
