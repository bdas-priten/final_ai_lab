#include <bits/stdc++.h>
using namespace std;

bool solved = false;

void solve(vector<char>& letters, vector<int>& values, vector<bool>& visited, vector<string>& words) {
    if (solved) return;  // Stop searching after first solution

    if ((int)values.size() == (int)letters.size()) {
        unordered_map<char, int> map;
        for (int i = 0; i < (int)letters.size(); i++) {
            map[letters[i]] = values[i];
        }

        // Leading letters can't be zero
        if (map[words[0][0]] == 0 || map[words[1][0]] == 0 || map[words[2][0]] == 0)
            return;

        int num1 = 0, num2 = 0, res = 0;
        for (char c : words[0]) num1 = num1 * 10 + map[c];
        for (char c : words[1]) num2 = num2 * 10 + map[c];
        for (char c : words[2]) res = res * 10 + map[c];

        if (num1 + num2 == res) {
            cout << num1 << " + " << num2 << " = " << res << "\t{";
            for (int i = 0; i < (int)letters.size(); i++) {
                cout << letters[i] << "=" << values[i];
                if (i != (int)letters.size() - 1) cout << ", ";
            }
            cout << "}\n";
            solved = true;
        }
        return;
    }

    for (int i = 0; i < 10; i++) {
        if (!visited[i]) {
            visited[i] = true;
            values.push_back(i);
            solve(letters, values, visited, words);
            values.pop_back();
            visited[i] = false;
        }
    }
}

int main() {
    cout << "\nCRYPTARITHMETIC PUZZLE SOLVER\n";
    cout << "WORD1 + WORD2 = RESULT\n";

    string word1, word2, result;
    cout << "Enter WORD1: ";
    cin >> word1;
    cout << "Enter WORD2: ";
    cin >> word2;
    cout << "Enter RESULT: ";
    cin >> result;

    // Convert to uppercase (optional)
    transform(word1.begin(), word1.end(), word1.begin(), ::toupper);
    transform(word2.begin(), word2.end(), word2.begin(), ::toupper);
    transform(result.begin(), result.end(), result.begin(), ::toupper);

    // Validate input: letters only
    auto isAlpha = [](const string& s) {
        for (char c : s)
            if (!isalpha(c)) return false;
        return true;
    };

    if (!isAlpha(word1) || !isAlpha(word2) || !isAlpha(result)) {
        cout << "Only letters allowed.\n";
        return 0;
    }

    if ((int)result.size() > max((int)word1.size(), (int)word2.size()) + 1) {
        cout << "0 solutions!\n";
        return 0;
    }

    set<char> unique_letters;
    for (char c : word1) unique_letters.insert(c);
    for (char c : word2) unique_letters.insert(c);
    for (char c : result) unique_letters.insert(c);

    if ((int)unique_letters.size() > 10) {
        cout << "0 solutions!\n";
        return 0;
    }

    vector<char> letters(unique_letters.begin(), unique_letters.end());

    vector<int> values;
    vector<bool> visited(10, false);
    vector<string> words = {word1, word2, result};

    cout << "\nSolutions:\n";
    solve(letters, values, visited, words);

    if (!solved)
        cout << "0 solutions!\n";

    return 0;
}
