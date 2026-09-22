#include <iostream>
using namespace std;
int main() 
{
    int a[3][3][4] = 
    {
        {{0, 1, 0, 0}, {1, 1, 0, 1}, {0, 0, 0, 0}},
        {{1, 0, 1, 0}, {0, 0, 1, 1}, {1, 1, 0, 0}},
        {{0, 1, 1, 1}, {1, 0, 0, 0}, {0, 0, 1, 0}}
    };

    int occ = 0, avail = 0;

    for (int f = 0; f < 3; f++) 
    {
        cout << "Floor " << f + 1 << ":\n";
        int f_occ = 0;
        for (int w = 0; w < 3; w++) 
        {
            cout << "  Ward " << w + 1 << ": ";
            for (int b = 0; b < 4; b++) {
                cout << a[f][w][b] << " ";
                if (a[f][w][b] == 1) 
                {
                    occ++;
                    f_occ++;
                } 
                else 
                {
                    avail++;
                }
            }
            cout << "\n";
        }
        cout << "Occupied beds on Floor " << f + 1 << ": " << f_occ << "\n\n";
    }

    cout << "Total occupied beds: " << occ << "\n";
    cout << "Total available beds: " << avail << "\n\n";

    int f, w, b;
    cout << "Enter floor (1-3), ward (1-3), bed (1-4): ";
    cin >> f >> w >> b;

    f--; w--; b--;

    if (f >= 0 && f < 3 && w >= 0 && w < 3 && b >= 0 && b < 4) 
    {
        if (a[f][w][b] == 1) 
        {
            cout << "The selected bed is Occupied.\n";
        } 
        else 
        {
            cout << "The selected bed is Available.\n";
        }
    } 
    else 
    {
        cout << "Invalid input.\n";
    }

    return 0;
}