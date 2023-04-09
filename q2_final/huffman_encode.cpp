#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>
#include <fstream>
using namespace std;

struct Node {
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = right = nullptr;
    }

    Node(int frequency, Node* left, Node* right) {
        data = '\0';
        this->frequency = frequency;
        this->left = left;
        this->right = right;
    }
};

struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

unordered_map<char, string> codes;

void generateCodes(Node* root, string code) {
    if (root == nullptr) {
        return;
    }
    if (root->data != '\0') {
        codes[root->data] = code;
    }
    generateCodes(root->left, code + "0");
    generateCodes(root->right, code + "1");
}

string encode(string text) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    /*priority_queue is a standard library container in C++ that implements a priority queue data structure. A priority queue is a data structure that allows efficient access to the element with the highest priority. It is typically implemented as a heap data structure.
In the given code, a priority_queue is being declared. The priority_queue is templated on three types: Node*, vector<Node*>, and Compare.
Node* is the type of the elements stored in the priority queue. In this case, the priority queue will store pointers to Node objects.
vector<Node*> is the type of the underlying container used to store the elements. The priority queue will use a vector to store the Node pointers.
Compare is the type of the comparison function used to determine the priority of the elements.
Compare is a custom comparison function that defines the ordering of the elements in the priority queue. It takes two Node* pointers as arguments and returns a bool value. The comparison function should return true if the first argument is of higher priority than the second argument.
So, in summary, the given code declares a priority_queue that stores pointers to Node objects in a vector and orders the elements based on a custom comparison function.*/
    unordered_map<char, int> freq;
    /*unordered_map<char, int> is a C++ Standard Library container that represents an associative array, which allows you to store and access data based on a unique key. In this case, the keys are characters (char) and the values are integers (int).
The name of the map is freq, which suggests that it is being used to store frequency counts. For example, you might use this map to count the number of occurrences of each character in a string.*/
    for (char c : text) {
        freq[c]++;
    }
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }
    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        int sum = left->frequency + right->frequency;
        pq.push(new Node(sum, left, right));
    }
    Node* root = pq.top();
    pq.pop();
    generateCodes(root, "");
    string encoded = "";
    for (char c : text) {
        encoded += codes[c];
        encoded += " ";
    }
    return encoded;
}



int main() {
    FILE* file;
    FILE* file2;
    file = fopen("file3.txt", "r");
    char ch;
    string text;
    while ((ch=getc(file))!=EOF) {
      text=text+ch;
    }

    string encoded = encode(text);

    // Printing of MAP
    cout << "Element  Frequency" << endl;
    for (auto i : codes){
        cout << i.first << " \t\t\t " << i.second << endl;
    }
    ofstream output("code_table3.txt");
    for (auto i : codes){
        output<< i.first << "=" << i.second << endl;
    }
    output.close();

    cout << "Encoded: " << encoded << endl;
    ofstream output2("Encoded3.txt");
    output2<<encoded;
    output2.close();
    return 0;
}
