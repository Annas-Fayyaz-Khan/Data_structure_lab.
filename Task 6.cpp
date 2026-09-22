#include <iostream>
using namespace std;
int main() 
{
    int a[2][2][2] = 
    {
        {{10, 20}, {30, 40}},
        {{50, 60}, {70, 80}}
    };

    cout << "3D Array:\n\n";

    for (int i = 0; i < 2; i++) 
    {
        cout << "Layer " << i + 1 << ":\n";
        for (int j = 0; j < 2; j++) 
        {
            for (int k = 0; k < 2; k++) 
            {
                cout << a[i][j][k] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    int target = 70;
    cout << "Searching for: " << target << "\n\n";

    bool found = false;
    for (int i = 0; i < 2; i++) 
    {
        for (int j = 0; j < 2; j++) 
        {
            for (int k = 0; k < 2; k++) 
            {
                if (a[i][j][k] == target) 
                {
                    cout << "Element found!\n";
                    cout << "Layer: " << i + 1 << "\n";
                    cout << "Row: " << j + 1 << "\n";
                    cout << "Column: " << k + 1 << "\n";
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (found) break;
    }

    return 0;
}