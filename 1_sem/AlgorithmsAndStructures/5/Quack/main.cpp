#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main()
{
    freopen("quack.in", "r", stdin);
    freopen("quack.out", "w", stdout);

    queue<unsigned short> queue;

    vector<unsigned short> registers(26);
    for (int i = 0; i < 26; i++) registers[i] = 0;

    string command;
    int pointer = 0;
    vector<string> commands;
    vector<pair<string, int>> labels;


    while (cin >> command)
    {
        if (command[0] == ':') labels.emplace_back(command.substr(1, command.size() - 1), commands.size());
        commands.push_back(command);
    }


    int a, b;
    string sub;

    while (pointer < commands.size())
    {
        if (commands[pointer].empty()) continue;
        switch (commands[pointer][0])
        {
            case '+':
                a = queue.front(); queue.pop();
                b = queue.front(); queue.pop();
                queue.push(a + b);

                break;
            case '-':
                a = queue.front(); queue.pop();
                b = queue.front(); queue.pop();
                queue.push(a - b);

                break;
            case '*':
                a = queue.front(); queue.pop();
                b = queue.front(); queue.pop();
                queue.push(a * b);

                break;
            case '/':
                a = queue.front(); queue.pop();
                b = queue.front(); queue.pop();
                queue.push(b == 0 ? 0 : a/b);

                break;
            case '%':
                a = queue.front(); queue.pop();
                b = queue.front(); queue.pop();
                queue.push(b == 0 ? 0 : a%b);

                break;
            case '>':
                registers[commands[pointer][1] - 'a'] = queue.front();
                queue.pop();

                break;
            case '<':
                queue.push(registers[commands[pointer][1] - 'a']);

                break;
            case 'P':
                if (commands[pointer].size() == 1)
                {
                    cout << queue.front() << endl;
                    queue.pop();
                }
                else
                {
                    cout << registers[commands[pointer][1] - 'a'] << endl;
                }

                break;
            case 'C':
                if (commands[pointer].size() == 1)
                {
                    cout << (char) queue.front();
                    queue.pop();
                }
                else
                {
                    cout <<  (char) registers[commands[pointer][1] - 'a'];
                }

                break;
            case ':':
                break;
            case 'J':
                sub = commands[pointer].substr(1, commands[pointer].size()-1);
                for (auto & label : labels) if (label.first == sub)
                    {
                        pointer = label.second-1;
                        break;
                    }

                break;
            case 'Z':
                if (registers[commands[pointer][1] - 'a'] == 0)
                {
                    sub = commands[pointer].substr(2, commands[pointer].size()-1);
                    for (auto & label : labels) if (label.first == sub)
                        {
                            pointer = label.second-1;
                            break;
                        }
                }

                break;
            case 'E':
                if (registers[commands[pointer][1] - 'a'] == registers[commands[pointer][2] - 'a'])
                {
                    sub = commands[pointer].substr(3, commands[pointer].size()-1);
                    for (auto & label : labels) if (label.first == sub)
                        {
                            pointer = label.second-1;
                            break;
                        }
                }

                break;
            case 'G':
                if (registers[commands[pointer][1] - 'a'] > registers[commands[pointer][2] - 'a'])
                {
                    sub = commands[pointer].substr(3, commands[pointer].size()-1);
                    for (auto & label : labels) if (label.first == sub)
                        {
                            pointer = label.second-1;
                            break;
                        }
                }

                break;
            case 'Q':
                return 0;
            default:
                queue.push(stoi(commands[pointer]));

                break;
        }
        pointer++;
    }


    return 0;
}
