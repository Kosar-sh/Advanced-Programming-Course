#include <iostream>
#include <string>
#include <vector>

using namespace std;

int up_down[4] = {0, 0, 1, -1};
int left_right[4] = {1, -1, 0, 0};
vector<string> result;

string change_name(int i, int current_row, int current_col);
bool possible_moves(char arr[7][7], int current_row, int current_col);
int more_moves_possibly(char board[7][7]);
int main()
{
    string inputing;
    int num = 0;
    char board[7][7];
    // the board as an input
    while (getline(cin, inputing))
    {
        for (int i = 0; i < 7; i++)
        {
            board[num][i] = inputing[i];
        }
        if (num == 6)
        {
            break;
        }
        num++;
    }
    if (possible_moves(board, 0, 0))
    {
        //printing moves
        for (int i = result.size() - 1; i >= 0; i--)
        {
            cout << result[i];
        }
    }
    else
        cout << "LOSER\n";
}
bool possible_moves(char arr[7][7], int current_row, int current_col)
{
    string made_move;
    char copy[7][7];
    if (36 <= current_col * current_row)
    {
        int now = more_moves_possibly(arr);
        if (arr[3][3] == 'N' && now == 0) // if only one N exist and its in middle
        {
            return true;
        }
        else // this moves wont led to vectory
        {
            return false;
        }
    }

    if (arr[current_row][current_col] == 'N')
    {
        for (int move = 0; move < 4; move++)
        {
            int new_row = current_row + up_down[move];
            int new_col = current_col + left_right[move];

            if (new_row < 0 || new_row > 6 || new_col < 0 || new_col > 6)
                continue; // out of range
            if (arr[new_row][new_col] != 'N')
                continue; // not wanted

            int s_row = new_row + up_down[move];
            int s_col = new_col + left_right[move];

            if (s_row < 0 || s_row > 6 || s_col < 0 || s_col > 6)
                continue; // out of range
            if (arr[s_row][s_col] != 'O')
                continue; // not wanted

            // make copy to save thr pre_board
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 7; j++)
                {
                    copy[i][j] = arr[i][j];
                }
            }
            //change the arrangment
            arr[current_row][current_col] = 'O';
            arr[new_row][new_col] = 'O';
            arr[s_row][s_col] = 'N';
            if (possible_moves(arr, 0, 0))
            {
                made_move = change_name(move, current_row, current_col); // find the home name
                result.push_back(made_move);
                return true;
            }
            else
            {
                //make the copy board the current board
                for (int i = 0; i < 7; i++)
                {
                    for (int j = 0; j < 7; j++)
                    {
                        arr[i][j] = copy[i][j];
                    }
                }
            }
        }
    }
    // if it's O,X then continue foe searching the best move
    if (current_col == 6)
    {
        current_row = current_row + 1;
        current_col = 0;
        if (possible_moves(arr, current_row, current_col))
            return true;
    }
    else
    {
        current_col = current_col + 1;
        if (possible_moves(arr, current_row, current_col))
            return true;
    }

    return false;
}
string change_name(int i, int current_row, int current_col)
{
    string output;
    switch (current_row)
    {
    case 0:
        output = "A";
        break;
    case 1:
        output = "B";
        break;
    case 2:
        output = "C";
        break;
    case 3:
        output = "D";
        break;
    case 4:
        output = "E";
        break;
    case 5:
        output = "F";
        break;
    case 6:
        output = "G";
        break;
    default:
        break;
    }
    // find its number
    output = output + to_string(current_col + 1);
    // find the name of move
    switch (i)
    {
    case 0:
        output = output + " RIGHT\n";
        break;
    case 1:
        output = output + " LEFT\n";
        break;
    case 2:
        output = output + " DOWN\n";
        break;
    case 3:
        output = output + " UP\n";
        break;
    default:
        break;
    }
    return output;
}
int more_moves_possibly(char board[7][7])
{
    int flag = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] == 'N') // any house has N
            {
                flag++;
            }
        }
    }
    if (flag == 1) // the moves were great
    {
        return 0;
    }
    else // need to do again
        return 1;
}