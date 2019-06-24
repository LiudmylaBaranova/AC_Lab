#include <limits>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


int n = 0;

void CountSizeFromFile() {
    ifstream file("list.txt");
    if (!file) {
        cout << "Wrong filename." << endl;
        exit(1);
    }
    
    
    string Name;
    double Price;
    double Freq;
    
    while (file >> Name ) {
        file >> Price >> Freq;
        n++;
    }
}

class BST {
public:
    BST();
    BST(int size);
    void initDataFromFile();
    void showData();
    void printOBST(int i, int j);

    void f(){
        optBST(n);
        cout << endl <<"Optimal tree of cost " << cost[1][n] << " is: ";
        printOBST(1, n);
        
        cout << endl << endl;
        
        cout << "\n Matrix of cost: \n";
        for (int i = 1; i < cost.size() - 1; i++)
        {
            for (int j = 1; j <cost.size() - 1; j++)
            {
                if (i > j) cout << " \t";
                else cout << cost[i][j] << "\t";
            }
            cout << endl;
        }
        
        cout << "\n Matrix of root: \n";
        for (int i = 1; i < root.size(); i++)
        {
            for (int j = 1; j < root.size(); j++)
            {
                if (i > j) cout << " \t";
                else cout << root[i][j] << " \t";
            }
            cout << endl;
        }
        
    }

private:
    struct Goods {
        string name;
        double price;
    };

    void optBST(int n);

    int m_size;
    vector<pair<Goods, double>> vec;
    vector<vector<int>> cost;
    vector<vector<int>> root;
};

BST::BST() {
    root.resize(n+1);
    cost.resize(n+2);

    for (int i = 0; i < n+1; i++) {
        root[i].resize(n+1);
    }
    
    for (int i = 0; i < n+2; i++) {
        cost[i].resize(n+2);
    }
}

BST::BST(int size) {
    m_size = size;
    root.resize(n+1);
    cost.resize(n+2);

    for (int i = 0; i < n+1; i++) {
        root[i].resize(n+1);
    }
    
    for (int i = 0; i < n+2; i++) {
        cost[i].resize(n+2);
    }
}

void BST::initDataFromFile() {
    ifstream file("list.txt");
    if (!file) {
        cout << "Wrong filename." << endl;
        exit(1);
    }


    string Name;
    double Price;
    double Freq;
    
    vec.push_back({{"", 0}, 0});

    while (file >> Name ) {
        file >> Price >> Freq;
        vec.push_back({{Name, Price}, Freq});
       //n++;
    }
}

void BST::showData(){
    cout << "[" << "name" << " " << "price" << "]    : " << "frequancy" << endl;
    for (int i = 1; i < vec.size(); i++) {
        cout << "[\t" << vec[i].first.name << "\t " << vec[i].first.price << "]\t: " << vec[i].second << endl;
    }
}

void BST::optBST(int n){
    int i,j,r,t;

    for (i = 1; i <= n ; i++)
        for (j = i+1; j <= n+1; j++)
            cost[i][j] = INT_MAX;

    for (i = 1; i <= n+1; i++)
        cost[i][i-1] = 0;

    for (i = 1; i <= n; i++){
        cost[i][i] = vec[i].second;
        root[i][i] = i;
    }

        for (j = 1; j <= n-1; j++)
            for (i = 1; i <= n-j; i++){
            for (r = i; r <= i+j; r++){
                t = cost[i][r-1] + cost[r+1][i+j];
                if (t < cost[i][i+j]){
                    cost[i][i+j] = t;
                    root[i][i+j] = r;
                }
            }
            for (int k = i; k <= i+j; cost[i][i+j] += vec[k++].second)
                ;
        }
}

void BST::printOBST(int i, int j){
    if (j < i) return;

    cout << "(";
    printOBST(i,root[i][j]-1);
    cout << vec[root[i][j]].first.name;
    printOBST(root[i][j]+1,j);
    cout << ")";
}

int main() {
    CountSizeFromFile();
    BST a;
    a.initDataFromFile();
    a.showData();

    a.f();
    return 0;
}



