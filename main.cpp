#include "Utils/BaseUtils.h"
#include "Utils/MaterialUtils.h"
#include "Utils/CategoryUtils.h"
#include "Utils/ManufacturerUtils.h"
#include "Utils/OrderUtils.h"

void control();
int main()
{

    introduce();
    while (true)
    {
        control();
    }
    sayBye();
    return 0;
}
void control()
{

    printMenu();
    int number;
    cout << "  Chon chuc nang: ";
    cin >> number;
    cin.ignore();
    cout << endl;

    switch (number)
    {
    case 0:
        sayBye();
        exit(0);
        break;
    case 1:
    {
        MaterialUtils mUtils;
        mUtils.manage();
        break;
    }
    case 2:
    {
        ManufacturerUtils manuUtils;
        manuUtils.manage();
        break;
    }
    case 3:
    {
        CategoryUtils cUtils;
        cUtils.manage();
    }
    break;
    case 4:
    {
        OrderUtils oUtils;
        oUtils.manage();
    }
    break;
    default:
        cout << "Khong co chuc nhap da nhap! "
             << "Moi ban nhap lai chuc nang: " << endl;
        break;
    }
}
