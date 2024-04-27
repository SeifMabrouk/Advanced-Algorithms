#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

vector<string> wrapText(const string& text, int lineWidth) {
    istringstream words(text);
    string word;
    string currentLine;
    vector<string> wrappedText;

    while (words >> word) {
        if (currentLine.length() + word.length() + (currentLine.empty() ? 0 : 1) <= lineWidth) {
            if (!currentLine.empty()) currentLine += " ";
            currentLine += word;
        } else {
            if (!currentLine.empty()) wrappedText.push_back(currentLine);
            currentLine = word;
        }
    }
    if (!currentLine.empty()) wrappedText.push_back(currentLine);

    return wrappedText;
}

int main() {
    string text = "Mary loves to sing and perform tapdancing.";
    int lineWidth = 10;
    vector<string> outputLines = wrapText(text, lineWidth);

    for (int i = 0; i < outputLines.size(); ++i) {
        cout << "line " << i + 1 << ": " << outputLines[i] << endl;
    }

    return 0;
}

