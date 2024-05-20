#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

// ############################### PROBLEM 1: Balanced Number [lvl 1] #############################################
//  A balanced number is a number where the sum of digits to the left of the middle digit(s)
//  and the sum of digits to the right of the middle digit(s) are equal.
//  If the number has an odd number of digits,
//  then there is only one middle digit. (For example, 92645 has one middle digit, 6.)
//  Otherwise, there are two middle digits. (For example, the middle digits of 1301 are 3 and 0.)
//  The middle digit(s) should not be considered when determining whether
//  a number is balanced or not, e.g. 413023 is a balanced number because the left sum and right sum are both 5.
//  Given a number, find if it is balanced, and return the string "Balanced" or "Not Balanced" accordingly.
//  The passed number will always be positive.

//  Examples
//  7 ==> return "Balanced"
//  Explanation:
//  middle digit(s): 7
//  sum of all digits to the left of the middle digit(s) -> 0
//  sum of all digits to the right of the middle digit(s) -> 0
//  0 and 0 are equal, so it's balanced.
//  295591 ==> return "Not Balanced"
//  Explanation:
//  middle digit(s): 55
//  sum of all digits to the left of the middle digit(s) -> 11
//  sum of all digits to the right of the middle digit(s) -> 10
//  11 and 10 are not equal, so it's not balanced.
//  959 ==> return "Balanced"
//  Explanation:
//  middle digit(s): 5
//  sum of all digits to the left of the middle digit(s) -> 9
//  sum of all digits to the right of the middle digit(s) -> 9
//  9 and 9 are equal, so it's balanced.
//  27102983 ==> return "Not Balanced"
//  Explanation:
//  middle digit(s): 02
//  sum of all digits to the left of the middle digit(s) -> 10
//  sum of all digits to the right of the middle digit(s) -> 20
//  10 and 20 are not equal, so it's not balanced.

std::string balancedNum(unsigned long long int number) {
    auto number_str = std::to_string(number);

    int left_sum = 0;
    int right_sum = 0;

    int middle_idx = number_str.size() / 2;
    for (int ii = 0; number_str.size() % 2 ? ii <= middle_idx : ii < middle_idx; ++ii) {
        left_sum += number_str[ii] - '0';
    }
    for (int ii = middle_idx; ii < number_str.size(); ++ii) {
        right_sum += number_str[ii] - '0';
    }
    return left_sum == right_sum ? "Balanced" : "Not Balanced";
}

// ********************************************************************************************************


// ############################### PROBLEM 2: Isograms [lvl 1] #############################################
// An isogram is a word that has no repeating letters, consecutive or non-consecutive. Implement a function 
//that determines whether a string that contains only letters is an isogram. Assume the empty string is an isogram. Ignore letter case.
// Example: (Input --> Output)
// "Dermatoglyphics" --> true
// "aba" --> false
// "moOse" --> false (ignore letter case)

bool is_isogram(std::string str) {
    std::unordered_set<char> used_chars;

    for (char cc: str) {
        char lower_cc = std::tolower(cc);
        if (used_chars.find(lower_cc) != used_chars.end()) {
            return false;
        }
        used_chars.insert(cc);
    }

    return true;
}

// ********************************************************************************************************

// ############################### PROBLEM 3: All or Nothing [lvl 1] #############################################
// Suppose a student can earn 100% on an exam by getting the answers all correct or all incorrect. 
// Given a potentially incomplete answer key and the student's answers, 
// write a function that determines whether a student can still score 100%.
// Incomplete questions are marked with an underscore, "_".

// ["A", "_", "C", "_", "B"]   # answer key
// ["A", "D", "C", "E", "B"]   # student's solution

// ➞ True

// # Possible for student to get all questions correct.

// ["B", "_", "B"]   # answer key
// ["B", "D", "C"]   # student's solution

// ➞ False

// # First question is correct but third is wrong, so not possible to score 100%.

// ["T", "_", "F", "F", "F"]   # answer key
// ["F", "F", "T", "T", "T"]   # student's solution

// ➞ True

// # Possible for student to get all questions incorrect.

// Examples
// (["B", "A", "_", "_"], ["B", "A", "C", "C"]) ➞ True
// (["A", "B", "A", "_"], ["B", "A", "C", "C"]) ➞ True
// (["A", "B", "C", "_"], ["B", "A", "C", "C"]) ➞ False
// (["B", "_"], ["C", "A"]) ➞ True
// (["B", "A"], ["C", "A"]) ➞ False
// (["B"], ["B"]) ➞ True
// (["_"], ["B"]) ➞ True


// Notes:
// Test has at least one question.
// len(key) == len(answers)

bool possibly_perfect(const std::vector<char> &key, const std::vector<char> &answers) {
    bool is_first_time = true;
    bool should_all_be_right;

    if (key.size() != answers.size()) {
        return false;
    }

    for (int ii = 0; ii < key.size(); ++ii) {
        char kk = key.at(ii);
        if (kk == '_') {
            continue;
        }
        char aa = answers.at(ii);
        if (is_first_time) {
            should_all_be_right = kk == aa;
        } else {
            if (should_all_be_right && kk != aa || !should_all_be_right && kk == aa) {
                return false;
            }
        }
    }
    return true;
}

// ********************************************************************************************************


// ############################### PROBLEM 4: Find the odd int [lvl 2] #############################################
//  Given an array of integers, find the one that appears an odd number of times.
//  There will always be only one integer that appears an odd number of times.
//  Examples
//  [7] should return 7, because it occurs 1 time (which is odd).
//  [0] should return 0, because it occurs 1 time (which is odd).
//  [1,1,2] should return 2, because it occurs 1 time (which is odd).
//  [0,1,0,1,0] should return 0, because it occurs 3 times (which is odd).
//  [1,2,2,3,3,3,4,3,3,3,2,2,1] should return 4, because it appears 1 time (which is odd).

int findOdd(const std::vector<int> &numbers) {
    std::unordered_map<int, bool> odd_count;

    for (int num: numbers) {
        if (odd_count.find(num) != odd_count.end()) {
            odd_count[num] = !odd_count.at(num);
        } else {
            odd_count[num] = true;
        }
    }

    for (auto it = odd_count.begin(); it != odd_count.end(); ++it) {
        if (it->second) return it->first;
    }

    return -1;
}

// ********************************************************************************************************



// ############################### PROBLEM 5: The Vowel Code [lvl 2] #############################################
// Step 1: Create a function called encode() to replace all the lowercase vowels in 
// a given string with numbers according to the following pattern:
// a -> 1
// e -> 2
// i -> 3
// o -> 4
// u -> 5
// For example, encode("hello") would return "h2ll4". There is no need to worry about uppercase vowels in this exercise.
// Step 2: Now create a function called decode() to turn the numbers back into vowels according to the same pattern shown above.
// For example, decode("h3 th2r2") would return "hi there".
// For the sake of simplicity, you can assume that any numbers passed into the function will correspond to vowels.

std::string encode(const std::string &str) {
    std::unordered_map<char, char> vowel_encoding = {
            {'a', '1'},
            {'e', '2'},
            {'i', '3'},
            {'o', '4'},
            {'u', '5'}
    };
    std::string encoded_str;
    for (const char &c: str) {
        encoded_str += vowel_encoding.find(c) == vowel_encoding.end() ? c : vowel_encoding[c];
    }
    return encoded_str;
}

std::string decode(const std::string &str) {
    std::unordered_map<char, char> vowel_decoding = {
            {'1', 'a'},
            {'2', 'e'},
            {'3', 'i'},
            {'4', 'o'},
            {'5', 'u'}
    };
    std::string decoded_str;
    for (const char &c: str) {
        decoded_str += vowel_decoding.find(c) == vowel_decoding.end() ? c : vowel_decoding[c];
    }
    return decoded_str;
}

// ********************************************************************************************************



// ############################### PROBLEM 6: Bananas [lvl 3] #############################################
// > "What is your name" said Tim.
// "My name" said the mouse "Is Dinglemouse".
// > "What were you before the witch turned you into a mouse" said Rose.
// "I was a banana" said Dingle the mouse, "So be careful. If you see her, run away!".
// - Badjelly the Witch (12:32), Spike Milligan

// Given a string of letters a, b, n how many different ways can you make the word "banana" 
// by crossing out various letters and then reading left-to-right?
// (Use - to indicate a crossed-out letter)

// Example:

// Input
// bbananana

// Output
// b-anana--
// b-anan--a
// b-ana--na
// b-an--ana
// b-a--nana
// b---anana
// -banana--
// -banan--a
// -bana--na
// -ban--ana
// -ba--nana
// -b--anana

// Notes
// You must return all possible bananas, but the order does not matter
// The example output above is formatted for readability. Please refer to the example tests for expected format of your result.

void find_matching(const std::string ref, const std::string test, int ref_idx, int test_idx, std::string temp_str,
                   std::unordered_set <std::string> matching) {
    // if "banana" has been detected, replace the rest of the tested string with '-' and save the string
    if (ref_idx == ref.size()) {
        for (int i = 0; i < test.size(); ++i) {
            temp_str += "-";
        }
        matching.insert(temp_str);
        return;
    }

    // otherwise keep searching for the rest of "banana" given the ref_idx (the letter you're searching for)
    //  starting from a certain point test_idx in the given string to test
    for (int i = test_idx; i < test.size(); ++i) {
        if (test[test_idx] == ref[ref_idx]) {
            find_matching(ref, test, ref_idx + 1, test_idx + 1, temp_str + test[i], matching);
        }
        temp_str += "-";
    }
}

std::unordered_set <std::string> bananas(const std::string &s) {
    std::unordered_set <std::string> bananas;

    find_matching("banana", s, 0, 0, "", bananas);
}



// ********************************************************************************************************