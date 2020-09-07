#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(string a, string b)
{
    if (a.length() == b.length())
        return a < b;
    return a.length() < b.length();
}
vector<int> solution(vector<string> words, vector<string> queries)
{
    vector<int> answer;
    vector<string> rwords = words;
    int w_size = words.size();
    for (int i = 0; i < w_size; i++)
        reverse(rwords[i].begin(), rwords[i].end());

    sort(words.begin(), words.end(), cmp);
    sort(rwords.begin(), rwords.end(), cmp);
    int idx, len, low, high;
    for (string query : queries)
    {
        len = query.length();
        if (query[0] == '?')
        {
            reverse(query.begin(), query.end());
            idx = query.find_first_of('?');

            for (int i = idx; i < len; i++)
                query[i] = 'a';
            low = lower_bound(rwords.begin(), rwords.end(), query, cmp) - rwords.begin();

            for (int i = idx; i < len; i++)
                query[i] = 'z';
            high = upper_bound(rwords.begin(), rwords.end(), query, cmp) - rwords.begin();
        }
        else
        {
            idx = query.find_first_of('?');

            for (int i = idx; i < len; i++)
                query[i] = 'a';
            low = lower_bound(words.begin(), words.end(), query, cmp) - words.begin();

            for (int i = idx; i < len; i++)
                query[i] = 'z';
            high = upper_bound(words.begin(), words.end(), query, cmp) - words.begin();
        }
        answer.push_back(high - low);
    }
    return answer;
}