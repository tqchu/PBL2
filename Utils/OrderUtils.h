#ifndef ORDERUTILS_H
#define ORDERUTILS_H
#include "BaseUtils.h"
#include "D:/PBL2/src/Comparator.h"
#include "D:/PBL2/src/Find.h"
#include <iomanip>
class OrderUtils : public BaseUtils<Order>
{
private:
    // inherited io,list,virtualList
public:
    // inherit manage,display
    OrderUtils();
    virtual void control();
    virtual void printTitle();
    virtual void add();
    virtual void update();
    virtual void sort();
    virtual void search();
    void cancel();
    void statisticize();
    void filter(string name, string categoryName, string manufacturerName, int quantity, unsigned long minUnitPrice, unsigned long maxUnitPrice);
};
OrderUtils::OrderUtils()
{
    title = "QUAN LY VAT TU";

    io = new OrderIO();
    dio = new DeletedOrderIO();
    io->getList(list);
    virtualList = list;

    dio->getList(deletedList);
}

void OrderUtils::control()
{
    cout << "  ";
    cout << setw(20) << left << "0. Quay lai";
    cout << setw(20) << left << "1. Them VT";
    cout << setw(30) << left << "2. Cap nhat thong tin VT";
    cout << setw(20) << "3. Xoa VT";
    cout << setw(20) << "4. Tim kiem";
    cout << setw(20) << "5. Sap xep";
    cout << endl;
    bool isValid = false;
    while (!isValid)
    {
        cout << endl
             << "  Chon chuc nang : ";
        int controlNumber;
        cin >> controlNumber;
        cout << endl;
        switch (controlNumber)
        {
        case 0:
            dio->update(deletedList);
            io->update(list);
            isValid = true;
            break;
        case 1:
            add();
            isValid = true;
            break;
        case 2:
            update();
            isValid = true;
            break;
        case 3:

            remove();
            isValid = true;
            break;
        case 4:
            search();
            manage();
            isValid = true;
            break;
        case 5:
            sort();
            manage();
            isValid = true;
            break;
        default:
            cout << "Khong co chuc nang da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void OrderUtils::printTitle()
{
    cout << setw(5) << "";
    cout << setw(10) << left << "Ma VT";
    cout << setw(24) << left << "Ten VT";
    cout << setw(16) << left << "Ten loai VT";
    cout << setw(24) << left << "Ten nha san xuat";
    cout << setw(15) << left << "Don vi tinh";
    cout << setw(15) << left << "So luong";
    cout << "Don gia" << endl
         << endl;
}
void OrderUtils::search()
{
    // xoá đi virtualList cũ
    virtualList.reset();
    int id;
    string name, categoryName, manufacturerName;
    int quantity;
    unsigned long minUnitPrice, maxUnitPrice;
    string minUnitPriceString, maxUnitPriceString, quantityString;
    cout << "Nhap 0 neu ban muon bo qua!" << endl;
    // * I. Lấy input
    cin.ignore();
    cout << "Nhap ten : ";
    getline(cin, name);
    name = trim(name);
    if (name == "0")
        name = "\0";

    cout << "Nhap ten loai VT: ";
    getline(cin, categoryName);
    categoryName = trim(categoryName);
    if (categoryName == "0")
        categoryName = "\0";

    cout << "Nhap ten NSX : ";
    getline(cin, manufacturerName);
    manufacturerName = trim(manufacturerName);
    if (manufacturerName == "0")
        manufacturerName = "\0";

    cout << "Nhap so luong( it nhat): ";
    while (true)
    {
        getline(cin, quantityString);
        quantityString = trim(quantityString);
        try
        {
            quantity = toNumber(quantityString, "So luong");
            break;
        }
        catch (custom_exception &exception)
        {
            cout << exception.get_info();
            cout << " Vui long nhap lai: ";
        }
    }

    cout << "Nhap don gia :" << endl;
    cout << "\t"
         << "Thap nhat: ";
    while (true)
    {
        getline(cin, minUnitPriceString);
        minUnitPriceString = trim(minUnitPriceString);
        try
        {
            minUnitPrice = toNumber(minUnitPriceString, "Don gia");
            break;
        }
        catch (custom_exception &exception)
        {
            cout << exception.get_info();
            cout << " Vui long nhap lai: ";
        }
    }
    cout << "\t"
         << "Cao nhat: ";
    while (true)
    {
        getline(cin, maxUnitPriceString);
        maxUnitPriceString = trim(maxUnitPriceString);
        try
        {
            maxUnitPrice = toNumber(maxUnitPriceString, "Don gia");
            break;
        }
        catch (custom_exception &exception)
        {
            cout << exception.get_info();
            cout << " Vui long nhap lai: ";
        }
    }
    if (maxUnitPrice == 0)
        maxUnitPrice = 1000000000;

    filter(name, categoryName, manufacturerName, quantity, minUnitPrice, maxUnitPrice);
}
void OrderUtils::filter(string name, string categoryName, string manufacturerName, int quantity, unsigned long minUnitPrice, unsigned long maxUnitPrice)
{
    Order material;
    for (int i = 0; i < list.size; i++)
    {
        material = list[i];

        if ((toLower(material.getName()).find(toLower(name)) != string::npos) &&
            ((toLower(material.getCategoryName()).find(toLower(categoryName)) != string::npos)) &&
            (toLower(material.getManufacturerName()).find(toLower(manufacturerName)) != string::npos) &&
            (material.getQuantity() >= quantity) &&
            (material.getUnitPrice() >= minUnitPrice) &&
            (material.getUnitPrice() <= maxUnitPrice))
        {
            virtualList.add(material);
        }
    }
}
void OrderUtils::add()
{
    string name, categoryName, manufacturerName, calculationUnit;
    int id, quantity;
    string quantityString, unitPriceString;
    unsigned long unitPrice;
    Order newOrder; // mở cổng và getList
    ManufacturerIO pIO;
    ArrayList<Manufacturer> pList;
    pIO.getList(pList);
    Manufacturer manufacturer;
    CategoryIO cIO;
    ArrayList<Category> cList;
    cIO.getList(cList);
    Category category;

    printBox("THEM VAT TU");

    int id1 = list.getMaxId() + 1;
    int id2 = deletedList.getMaxId() + 1;

    id = (id1 > id2 ? (id1) : (id2));
    // bắt đầu lấy dữ liệu từ người dùng
    // dùng để tránh lỗi do cin phía trước
    bool isCancel = false;
    while (true)
    {
        cin.ignore();
        int controlNumber;
        cout << "Nhap ten : ";
        getline(cin, name);
        name = trim(name);
        bool isValid = false;
        cout << "Nhap ten loai VT : ";
        while (true)
        {

            getline(cin, categoryName);
            categoryName = trim(categoryName);
            try
            {
                category = cList.get(findByName, categoryName);
                categoryName = category.getName();
                break;
            }
            catch (non_existent_element &exception)
            {

                cout << "Ten loai VT khong ton tai  , vui long nhap lai : ";
            }
        }
        // dat lai gia tri false cho NSX
        isValid = false;
        cout << "Nhap ten NSX : ";
        while (!isValid)
        {

            getline(cin, manufacturerName);
            manufacturerName = trim(manufacturerName);
            try
            {
                manufacturer = pList.get(findByName, manufacturerName);
                manufacturerName = manufacturer.getName();
                break;
            }
            catch (non_existent_element &exception)
            {

                cout << "Ten NSX khong ton tai  , vui long nhap lai : ";
            }
        }
        cout << "Nhap don vi tinh : ";
        getline(cin, calculationUnit);
        calculationUnit = trim(calculationUnit);

        // code mau
        cout << "Nhap so luong : ";
        while (true)
        {
            getline(cin, quantityString);
            quantityString = trim(quantityString);
            try
            {
                quantity = toNumber(quantityString, "So luong");
                break;
            }
            catch (custom_exception &exception)
            {
                cout << exception.get_info();
                cout << " Vui long nhap lai: ";
            }
        }
        cout << "Nhap don gia : ";
        while (true)
        {
            getline(cin, unitPriceString);
            unitPriceString = trim(unitPriceString);
            try
            {
                unitPrice = toNumber(unitPriceString, "Don gia");
                if (unitPrice == 0)
                    throw nonPositive_number("Don gia");
                else
                    break;
            }
            catch (custom_exception &exception)
            {
                cout << exception.get_info();
                cout << " Vui long nhap lai: ";
            }
        }
        newOrder = Order(id, name, categoryName, manufacturerName, calculationUnit, quantity, unitPrice);
        if (
            list.contains(newOrder))
        {
            cout << endl
                 << "Vat tu nay da ton tai !" << endl;
            isCancel = true;
        }
        else
        {
            isCancel = false;
        }
        cout << "Ban co muon  nhap lai ? (co : 1 / khong : 0) : ";

        cin >> controlNumber;
        cout << endl;
        if (controlNumber == 0)
            break;
    }
    if (!isCancel)
    {

        list.add(newOrder);

        virtualList.add(newOrder);
        // tin nhan thong bao
        cout << "Da them VT thanh cong !" << endl;
        cout << "Ban co muon tiep tuc them VT ?  (co : 1 / khong : 0) : ";
        int controlNumber;
        cin >> controlNumber;
        if (controlNumber == 0)
        {

            manage();
        }
        else
            add();
    }
    else
        manage();
}
void OrderUtils::update()
{
    printBox("CAP NHAT THONG TIN VAT TU");
    int id;
    cout << "Chon ma VT : ";

    while (true)
    {
        cin >> id;
        if (virtualList.contains(findById, id))
            break;
        else
        {
            cout << "Khong ton tai VT tuong ung voi ma ban vua nhap! Vui long nhap lai: ";
        }
    }

    Order &virtualOrder = virtualList.get(findById, id);
    Order &material = list.get(findById, id);
    // số lượng cần thêm
    unsigned long newPrice;
    int addNumber;
    string name;
    string categoryName;
    string manufacturerName;
    // dùng để tránh lỗi do cin phía trước
    cin.ignore();

    cout << "Nhap '0' neu ban muon de thong tin nhu cu !" << endl;
    cout << "Nhap ten moi : ";
    getline(cin, name);
    name = trim(name);
    if (name != "0")
    {
        material.setName(name);
        virtualOrder.setName(name);
    }
    ManufacturerIO pIO;
    CategoryIO cIO;
    ArrayList<Manufacturer> pList;
    pIO.getList(pList);
    ArrayList<Category> cList;
    cIO.getList(cList);
    cout << "Nhap ten loai VT : ";
    while (true)
    {
        getline(cin, categoryName);
        categoryName = trim(categoryName);
        if (categoryName == "0")
            break;
        else
        {
            try
            {
                Category category = cList.get(findByName, categoryName);
                material.setCategoryName(category.getName());
                virtualOrder.setCategoryName(category.getName());
                break;
            }
            catch (non_existent_element &exception)
            {
                cout << "Loai VT k ton tai , vui long nhap lai: ";
            }
        }
    }
    cout << "Nhap ten NSX : ";
    while (true)
    {
        getline(cin, manufacturerName);
        manufacturerName = trim(manufacturerName);
        if (manufacturerName == "0")
            break;
        else
        {
            try
            {
                Manufacturer manufacturer = pList.get(findByName, manufacturerName);
                material.setManufacturerName(manufacturer.getName());
                virtualOrder.setManufacturerName(manufacturer.getName());
                break;
            }
            catch (non_existent_element &exception)
            {
                cout << "NSX k ton tai , vui long nhap lai: ";
            }
        }
    }
    string quantityString;
    cout << "Nhap so luong can them : ";
    while (true)
    {
        getline(cin, quantityString);
        quantityString = trim(quantityString);
        try
        {
            addNumber = toNumber(quantityString, "So luong them");
            if (addNumber != 0)
            {
                material.setQuantity(material.getQuantity() + addNumber);
                virtualOrder.setQuantity(virtualOrder.getQuantity() + addNumber);
            }
            break;
        }
        catch (custom_exception &exception)
        {
            cout << exception.get_info();
            cout << " Vui long nhap lai: ";
        }
    }
    string priceString;
    cout << "Nhap don gia moi : ";
    while (true)
    {
        getline(cin, priceString);
        priceString = trim(priceString);
        try
        {
            newPrice = toNumber(priceString, "Don gia");
            if (newPrice != 0)
            {
                material.setUnitPrice(newPrice);
                virtualOrder.setUnitPrice(newPrice);
            }
            break;
        }
        catch (custom_exception &exception)
        {
            cout << exception.get_info();
            cout << " Vui long nhap lai: ";
        }
    }
    cout << endl
         << "Da cap nhat VT thanh cong !" << endl;
    cout << "Ban co muon tiep tuc cap nhat VT ?  (co : 1 / khong : 0) : ";
    int controlNumber;
    cin >> controlNumber;
    if (controlNumber == 0)
    {
        manage();
    }
    else
        update();
}
void OrderUtils::remove()
{

    // nhap ma VT
    int id, i, j;
    bool isValid = false;
    bool isCancel = false;
    cout << "Nhap ma VT can xoa : ";

    Order material;

    while (true)
    {
        cin >> id;

        try
        {
            material = virtualList.get(findById, id);
            if (material.getQuantity() == 0)
                break;
            else
            {
                cout << "So luong vat tu trong kho van con, khong the xoa! Ban co muon xoa vat tu khac? (co: 1 | khong: 0): ";
                int cancelNumber;
                cin >> cancelNumber;
                isCancel = !(cancelNumber);
                if (isCancel)
                    break;
            }
        }
        catch (non_existent_element &exception)
        {
            cout << "Khong ton tai VT ban vua nhap !";
        }
        cout << " Vui long nhap lai: ";
    }

    if (isCancel)
    {
        manage();
    }
    else
    {

        // insert vao file da xoa
        deletedList.add(material);

        list.remove(id);
        virtualList.remove(id);

        cout << endl
             << "Da xoa VT thanh cong !" << endl;
        cout << "Ban co muon tiep tuc xoa VT ?  (co : 1 / khong : 0) : ";
        int controlNumber;

        cin >> controlNumber;

        if (controlNumber == 0)
        { // nếu thoát ra ngoài thì cập nhật file đã xoá
            manage();
        }
        else
            remove();
    }
}

void OrderUtils::sort()
{

    cout << "Ban muon sap xep theo tieu chi nao ? " << endl
         << endl;
    cout << setw(20) << "1. Ten vat tu" << setw(20) << " 2. Ten loai VT" << setw(25) << " 3. Ten nha san xuat" << setw(20) << " 4. So luong"
         << " 5. Don gia " << endl
         << endl;

    int number;

    cout << "Nhap tieu chi: ";

    cin >> number;

    char a;
    cout << "Tang ? Giam ? (t/g): ";
    cin >> a;
    switch (number)

    {

    case 1:
        if ((a == 't') || (a == 'T'))
            virtualList.sort(sortByName, ascendingString);
        else
            virtualList.sort(sortByName, descendingString);
        break;

    case 2:
        if ((a == 't') || (a == 'T'))
            virtualList.sort(sortByCategoryName, ascendingString);
        else
            virtualList.sort(sortByCategoryName, descendingString);
        break;

    case 3:
        if ((a == 't') || (a == 'T'))
            virtualList.sort(sortByManufacturerName, ascendingString);
        else
            virtualList.sort(sortByManufacturerName, descendingString);
        break;

    case 4:
        if ((a == 't') || (a == 'T'))
            virtualList.sort(sortByQuantity, ascendingNumber);
        else
            virtualList.sort(sortByQuantity, descendingNumber);
        break;

    case 5:
        if ((a == 't') || (a == 'T'))
            virtualList.sort(sortByUnitPrice, ascendingNumber);
        else
            virtualList.sort(sortByUnitPrice, descendingNumber);
        break;
    }
}