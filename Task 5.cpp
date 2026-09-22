#include <iostream>
using namespace std;
int main() 
{
    int a[2][3][5] = 
    {
        {{0, 1, 0, 0, 1}, {1, 0, 0, 1, 0}, {0, 0, 1, 0, 0}},
        {{1, 1, 0, 1, 0}, {0, 0, 0, 0, 1}, {1, 0, 1, 0, 1}}
    };

    int avail = 0, used = 0;

    for (int l = 0; l < 2; l++) 
    {
        cout << "Lab " << l + 1 << ":\n";
        int l_avail = 0;
        for (int r = 0; r < 3; r++) 
        {
            cout << "  Row " << r + 1 << ": ";
            for (int c = 0; c < 5; c++) 
            {
                cout << a[l][r][c] << " ";
                if (a[l][r][c] == 0) 
                {
                    avail++;
                    l_avail++;
                } 
                else 
                {
                    used++;
                }
            }
            cout << "\n";
        }
        cout << "Available computers in Lab " << l + 1 << ": " << l_avail << "\n\n";
    }

    cout << "Total available computers: " << avail << "\n";
    cout << "Total computers in use: " << used << "\n\n";

    int l, r, c;
    cout << "Enter lab (1-2), row (1-3), computer (1-5): ";
    cin >> l >> r >> c;

    l--; r--; c--;

    if (l >= 0 && l < 2 && r >= 0 && r < 3 && c >= 0 && c < 5) {
        if (a[l][r][c] == 0) 
        {
            cout << "The selected computer is Available.\n";
        } 
        else 
        {
            cout << "The selected computer is In Use.\n";
        }
    } 
    else 
    {
        cout << "Invalid input.\n";
    }

    return 0;
}