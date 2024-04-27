#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cctype>
#include <iomanip>
#include <cmath>

using namespace std;

struct TreeNode {
    string value;
    TreeNode *left, *right;
    TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Helper to determine if a string is numeric
bool isNumeric(const string& s) {
    return !s.empty() && s.find_first_not_of("0123456789") == string::npos;
}

TreeNode* constructExpressionTree(const string& expr) {
    stack<TreeNode*> nodes;
    stack<char> ops;

    for (int i = 0; i < expr.length(); i++) {
        if (isspace(expr[i]))
            continue;

        if (expr[i] == '(') {
            ops.push(expr[i]);
        } else if (isdigit(expr[i])) {
            string val = "";
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                val += expr[i++];
            }
            i--;
            nodes.push(new TreeNode(val));
        } else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                TreeNode *right = nodes.top(); nodes.pop();
                TreeNode *left = nodes.top(); nodes.pop();
                char op = ops.top(); ops.pop();
                TreeNode *opNode = new TreeNode(string(1, op));
                opNode->left = left;
                opNode->right = right;
                nodes.push(opNode);
            }
            ops.pop();
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            while (!ops.empty() && ops.top() != '(') {
                TreeNode *right = nodes.top(); nodes.pop();
                TreeNode *left = nodes.top(); nodes.pop();
                char op = ops.top(); ops.pop();
                TreeNode *opNode = new TreeNode(string(1, op));
                opNode->left = left;
                opNode->right = right;
                nodes.push(opNode);
            }
            ops.push(expr[i]);
        }
    }

    return nodes.top();
}

void printTree(TreeNode* root, int space = 0, int height = 10) {
    if (root == nullptr)
        return;

    space += height;
    printTree(root->right, space);

    cout << endl;
    for (int i = height; i < space; i++)
        cout << ' ';
    cout << root->value << "\n";

    printTree(root->left, space);
}

int main() {
    string expression = "((1 + 2) * (3 - 4))";
    TreeNode* root = constructExpressionTree(expression);
    cout << "Visual representation of the constructed expression tree:" << endl;
    printTree(root);

    return 0;
}
