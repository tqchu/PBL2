#include "Material.h"
#include "Category.h"
#include "Order.h"
#include "OrderDetail.h"
#include "Provider.h"
#include <conio.h>
#include <iomanip>
#define lineLength 119
// in dấu gạch dưới
void printUnderscore(int n);
// in menu
void printMenu();
// chọn chức năng chính
void controlMain();
// in hộp quản lý
void printBox(string title);
// quản lý vật tư
void manageMaterial();
void controlMaterialList(int numberOfRecords, Material *materialList);
Material *filterMaterial(int numberOfRecords, Material *materialList);
void addMaterial(int &numberOfRecords, Material *materialList);
void updateMaterial(int numberOfRecords, Material *materialList);
void displayMaterialList(int numberOfRecords, Material *materialList);
void deleteMaterial(int &numberOfRecords, Material *materialList);
// quản lý nhà sản xuất
void manageProviders();
void controlProviderList(int &numberOfRecords, Provider *providerList);
void addProvider(int &numberOfRecords, Provider *providerList);
void updateProvider(int numberOfRecords, Provider *providerList);
void deleteProvider(int &numberOfRecords, Provider *providerList);
void displayProviderList(int numberOfRecords, Provider *providerList);
// quản lý loại vật tư
void manageCategories();
void controlCategoryList(int &numberOfRecords, Category *categoryList);
void addCategory(int &numberOfRecords, Category *categoryList);
void updateCategory(int numberOfRecords, Category *categoryList);
void deleteCategory(int &numberOfRecords, Category *categoryList);
void displayCategoryList(int numberOfRecords, Category *categoryList);
// quản lý đơn hàng
void manageOrders();
void controlOrderList(int numberOfRecords, Order *orderList);
void displayOrderList(int numberOfRecords, Order *orderList);
void addOrder(int &numberOfRecords, Order *orderList);
void deleteOrderHistory(int numberOfRecords, Order *orderList);
void viewOrderDetail(int numberOfOrderDetail, Order *orderList);
void cancelOrder(int numberOfRecords,Order* orderList);
// cap nhat trang thai giao hang
void updateOrder(int numberOfRecords, Order *orderList);
int main()
{

    controlMain();
}
// quản lý NSX
void manageProviders()
{

    // lấy  danh sách
    Provider *providerList = getProviderList();
    // tính số hàng
    int numberOfRecords;
    for (numberOfRecords = 0; numberOfRecords < maxProviderRecords; numberOfRecords++)
    {
        if (providerList[numberOfRecords].getId() == 0)
            break;
    }
    /*....*/
    controlProviderList(numberOfRecords, providerList);
}
void manageMaterial()
{
    // lấy  danh sách
    Material *materialList = getMaterialList();
    // tính số hàng
    int numberOfRecords = getNumberOfRecords(materialList, maxMaterialRecords);

    /*
        chức năng tìm kiếm (lọc )
    */
    /* string name, categoryName, providerName, status, quantity, minUnitPrice, maxUnitPrice;
    printBox("CHON VAT TU BAN MUON QUAN LY");
    cout << endl;
    cin.ignore();
    cout << "Nhap * de CHON TAT CA !" << endl
         << endl;
    cout << "Chon ten VT : ";
    getline(cin, name);
    cout << "Chon loai VT: ";
    getline(cin, categoryName);
    cout << "Chon NSX: ";
    getline(cin, providerName);
    cout << "Chon so luong ( > ): ";
    getline(cin, quantity);
    cout << "Chon don gia: " << endl;
    cout << "\t"
         << "Thap nhat : ";
    getline(cin, minUnitPrice);
    cout << "\t"
         << "Cao nhat : ";
    getline(cin, maxUnitPrice);

    cout << "Chon trang thai ( con su dung : 1 | ngung su dung : 0 ): ";
    getline(cin, status);
    status = (status == "1" ? "Con su dung" : "Ngung su dung");
    materialList = filterMaterial(numberOfRecords, materialList);
 */

    controlMaterialList(numberOfRecords, materialList);
}
// quản lý LVT
void manageCategories()
{
    // lấy  danh sách
    Category *categoryList = getCategoryList();
    // tính số hàng
    int numberOfRecords;
    for (numberOfRecords = 0; numberOfRecords < maxCategoryRecords; numberOfRecords++)
    {
        if (categoryList[numberOfRecords].getId() == 0)
            break;
    }
    /*....*/
    controlCategoryList(numberOfRecords, categoryList);
}

// quản lý DH
void manageOrders()
{

    // lấy  danh sách
    Order *orderList = getOrderList();
    // tính số hàng
    int numberOfRecords;
    for (numberOfRecords = 0; numberOfRecords < maxOrderRecords; numberOfRecords++)
    {
        if (orderList[numberOfRecords].getId() == 0)
            break;
    }
    /*....*/

        controlOrderList(numberOfRecords, orderList);
}

void displayMaterialList(int numberOfRecords, Material *materialList)
{

    cout << endl;
    printUnderscore(lineLength);
    // in tiêu đề
    cout << setw(10) << left << "Ma VT";
    cout << setw(24) << left << "Ten VT";

    cout << setw(16) << left << "Ten loai VT";
    cout << setw(24) << left << "Ten nha san xuat";
    cout << setw(12) << left << "Don vi tinh";
    cout << setw(10) << left << "So luong";
    cout << setw(10) << left << "Don gia";
    cout << "Trang thai" << endl
         << endl;
    for (int i = 0; i < numberOfRecords; i++)
    {
        cout << setw(10) << left << materialList[i].getId();
        cout << setw(24) << left << materialList[i].getName();
        cout << setw(16) << left << materialList[i].getCategoryName();
        cout << setw(24) << left << materialList[i].getProviderName();
        cout << setw(12) << left << materialList[i].getCalculationUnit();
        cout << setw(10) << left << materialList[i].getQuantity();
        cout << setw(10) << left << materialList[i].getUnitPrice();
        cout << materialList[i].getStatus() << endl;
    }
    printUnderscore(lineLength);
}
void displayProviderList(int numberOfRecords, Provider *providerList)
{

    cout << endl;
    printUnderscore(lineLength);
    // in tiêu đề
    cout << setw(15) << left << "Ma NSX";
    cout << setw(32) << left << "Ten NSX";
    cout << setw(16) << left << "SDT";
    cout << setw(16) << left << "Ngay hop tac";
    cout << "Dia chi" << endl
         << endl;
    for (int i = 0; i < numberOfRecords; i++)
    {
        cout << setw(15) << left << providerList[i].getId();
        cout << setw(32) << left << providerList[i].getName();
        cout << setw(16) << left << providerList[i].getPhoneNumber();
        cout << setw(16) << left << providerList[i].getDate();
        cout << providerList[i].getAddress() << endl;
    }
    printUnderscore(lineLength);
}
void displayCategoryList(int numberOfRecords, Category *categoryList)
{
    cout << endl;
    printUnderscore(lineLength);
    // in tiêu đề
    cout << setw(20) << "" << setw(35) << left << "Ma LVT";
    cout << setw(35) << left << "Ten LVT" << endl
         << endl;
    for (int i = 0; i < numberOfRecords; i++)
    {
        cout << setw(20) << "" << setw(35) << left << categoryList[i].getId();
        cout << setw(35) << left << categoryList[i].getName() << endl;
    }
    printUnderscore(lineLength);
}
void displayOrderList(int numberOfRecords, Order *orderList)
{
    cout << endl;
    printUnderscore(lineLength);
    // in tiêu đề
    cout << setw(15) << left << "Ma DH";
    cout << setw(15) << left << "Thanh tien";
    cout << setw(20) << left << "Thoi gian dat";
    cout << setw(30) << left << "Dia chi giao hang";
    cout << "Trang thai giao" << endl
         << endl;
    for (int i = 0; i < numberOfRecords; i++)
    {
        cout << setw(15) << left << orderList[i].getId();
        cout << setw(15) << left << orderList[i].getTotalPrice();
        cout << setw(20) << left << orderList[i].getTime();
        cout << setw(30) << left << orderList[i].getShippingAddress();
        cout << orderList[i].getShippingStatus() << endl;
    }
    printUnderscore(lineLength);
}

void viewOrderDetail(int numberOfOrderRecords, Order *orderList)
{
    printBox("CHI TIET DON HANG");
    cout << endl;
    // lấy mã đơn hàng
    int id;
    cout << "Nhap ma don hang : ";
    while (true)
    {
        cin >> id;
        int i;
        for (i = 0; i < numberOfOrderRecords; i++)
        {
            if (orderList[i].getId() == id)
                break;
        }
        if (i < numberOfOrderRecords)
            break;
        else
            cout << "Khong ton tai don hang ban vua nhap , vui long nhap lai : ";
    }
    // lay ds tat ca CTDH
    int numberOfRecords;

    OrderDetail *orderDetailList = getOrderDetailList();

    for (numberOfRecords = 0; numberOfRecords < maxOrderDetailRecords; numberOfRecords++)
    {
        if (orderDetailList[numberOfRecords].getId() == 0)
            break;
    }
    // tao STT de in
    int stt = 1;
    // in tieu de
    printUnderscore(lineLength);
    cout << setw(5) << "STT";
    // in ten VT
    cout << setw(30) << "Ten VT";
    cout << setw(15) << "Don vi tinh";
    cout << setw(10) << "So luong";
    cout << setw(10) << "Don gia";
    cout << "Thanh tien" << endl
         << endl;
    // tìm mã đơn hàng trong CTDH và in
    unsigned long totalWithoutDiscount = 0;
    for (int i = 0; i < numberOfRecords; i++)
    {
        if (orderDetailList[i].getId() == id)
        {

            Material materialById = getMaterialById(orderDetailList[i].getMaterialId());
            cout << setw(5) << stt++;
            // in ten VT
            cout << setw(30) << materialById.getName();
            cout << setw(15) << materialById.getCalculationUnit();
            cout << setw(10) << orderDetailList[i].getQuantity();
            cout << setw(10) << materialById.getUnitPrice();
            unsigned long price = orderDetailList[i].getQuantity() * materialById.getUnitPrice();
            totalWithoutDiscount += price;
            cout << price << endl;
        }
    }
    printUnderscore(lineLength * 3 / 4);
    unsigned long discount = getDiscount(totalWithoutDiscount);
    cout << "Tong tien (chua giam gia) : " << totalWithoutDiscount << endl;
    cout << "Giam gia ( " << discount * 100 / totalWithoutDiscount << "% ) : " << discount << endl;
    cout << "Thanh tien : " << totalWithoutDiscount - discount << endl;
    printUnderscore(lineLength);
}
void addMaterial(int &numberOfRecords, Material *materialList)
{
    string name, categoryName, providerName, calculationUnit;
    int id, quantity;
    unsigned long unitPrice;
    printBox("THEM VAT TU");
    // can be REFACTORED
    // tìm id lớn nhất
    // -> id sẽ bằng maxId + 1
    id = materialList[numberOfRecords - 1].getId() + 1;
    // bắt đầu lấy dữ liệu từ người dùng
    // dùng để tránh lỗi do cin phía trước
    while (true)
    {
        cin.ignore();
        int controlNumber;
        cout << "Nhap ten : ";
        getline(cin, name);
        bool isValid = false;
        cout << "Nhap ten loai VT : ";
        while (!isValid)
        {

            getline(cin, categoryName);
            isValid = checkCategoryByName(categoryName);
            if (!isValid)
                cout << "Ten loai VT khong ton tai  , vui long nhap lai : ";
        }
        // dat lai gia tri false cho NSX
        isValid = false;
        cout << "Nhap ten NSX : ";
        while (!isValid)
        {

            getline(cin, providerName);
            isValid = checkProviderByName(providerName);
            if (!isValid)
                cout << "Ten NSX khong ton tai , vui long nhap lai : ";
        }
        cout << "Nhap don vi tinh : ";
        getline(cin, calculationUnit);
        cout << "Nhap so luong : ";
        cin >> quantity;
        cout << "Nhap don gia : ";
        cin >> unitPrice;
        cout << "Ban co muon  nhap lai ? (co : 1 / khong : 0) : ";

        cin >> controlNumber;
        if (controlNumber == 0)
            break;
    }
    // trang thai khi them se la = " Con su dung"
    Material newMaterial(id, name, categoryName, providerName, calculationUnit, quantity, unitPrice, "Con su dung");
    materialList[numberOfRecords++] = newMaterial;

    // tin nhan thong bao
    cout << endl
         << "Da them VT thanh cong !" << endl;
    cout << "Ban co muon tiep tuc them VT ?  (co : 1 / khong : 0) : ";
    int controlNumber;
    cin >> controlNumber;
    if (controlNumber == 0)
    {
        
        controlMaterialList(numberOfRecords,materialList);
    }
    else
        addMaterial(numberOfRecords, materialList);
}
void addProvider(int &numberOfRecords, Provider *providerList)

{
    int id;
    string name, phoneNumber, date, address;
    printBox("THEM NHA SAN XUAT");
    // can be REFACTORED
    // tìm id lớn nhất
    id = providerList[numberOfRecords - 1].getId() + 1;
    // bắt đầu lấy dữ liệu từ người dùng
    // dùng để tránh lỗi do cin phía trước
    while (true)
    {
        cin.ignore();
        int controlNumber;
        bool isValid = true;
        cout << "Nhap ten : ";
        while (isValid)
        {
            getline(cin, name);
            isValid = checkProviderByName(name);
            if (isValid)
                cout << "Ten NSX da ton tai  , vui long nhap lai : ";
        }
        cout << "Nhap SDT : ";
        getline(cin, phoneNumber);
        cout << "Nhap ngay hop tac (dd/mm/yyyy ) : ";
        getline(cin, date);
        cout << "Nhap dia chi : ";
        getline(cin, address);

        cout << "Ban co muon nhap lai ? (co : 1 / khong : 0) : ";
        cin >> controlNumber;
        if (controlNumber == 0)
            break;
    }
    Provider newProvider(id, name, phoneNumber, date, address);
    providerList[numberOfRecords++] = newProvider;

    // tin nhan thong bao
    cout << endl
         << "Da them NSX thanh cong !" << endl;
    cout << "Ban co muon tiep tuc them NSX ?  (co : 1 / khong : 0) : ";
    int controlNumber;
    cin >> controlNumber;
    if (controlNumber == 0)
    {
        
        controlProviderList(numberOfRecords, providerList);
    }
    else
        addProvider(numberOfRecords, providerList);
}
void addCategory(int &numberOfRecords, Category *categoryList)
{
    int id;
    string name;
    printBox("THEM LOAI VAT TU");
    // can be REFACTORED
    // tìm id lớn nhất

    id = categoryList[numberOfRecords - 1].getId() + 1;
    // bắt đầu lấy dữ liệu từ người dùng
    // dùng để tránh lỗi do cin phía trước
    while (true)
    {
        cin.ignore();
        int controlNumber;
        bool isValid = true;
        cout << "Nhap ten : ";
        while (isValid)
        {
            getline(cin, name);
            isValid = checkCategoryByName(name);
            if (isValid)
                cout << "Ten LVT da ton tai  , vui long nhap lai : ";
        } 
    cout << "Ban co muon nhap lai ? (co : 1 / khong : 0) : ";
    cin >> controlNumber;
    if (controlNumber == 0)
        break;
    }
    Category newCategory(id, name);
    categoryList[numberOfRecords++] = newCategory;

    // tin nhan thong bao
    cout << endl
         << "Da them LVT thanh cong !" << endl;
    cout << "Ban co muon tiep tuc them LVT ?  (co : 1 / khong : 0) : ";
    int controlNumber;
    cin >> controlNumber;
    if (controlNumber == 0)
    {
        
        controlCategoryList(numberOfRecords, categoryList);
    }
    else
        addCategory(numberOfRecords, categoryList);
}
void addOrder(int &numberOfRecords, Order *orderList)
{
    printBox("THEM DON HANG");
    // hiển thị vật tư đang có
    Material *materialList = getMaterialList();
    int numberOfMaterialRecords = getNumberOfRecords(materialList, maxMaterialRecords);
    displayMaterialList(numberOfMaterialRecords, materialList);
    // vong lap
    // ma VT
    // so luong
    unsigned long totalWithoutDiscount = 0;
    bool isValid = true;
    int controlNumber;
    bool cancel;
    // tao id cho don hang
    // tu dong tao ma DH

    int id = orderList[numberOfRecords - 1].getId() + 1;
    //
    // lay DS CTDH tu file
    int numberOfODRecords;
    OrderDetail *orderDetailList = getOrderDetailList();
    for (numberOfODRecords = 0; numberOfODRecords < maxOrderDetailRecords; numberOfODRecords++)
    {
        if (orderDetailList[numberOfODRecords].getId() == 0)
            break;
    }
    // CAP nhat VT
    // Material *materialList = getMaterialList();
    // int numberOfMaterialRecords = getNumberOfRecords(materialList, maxMaterialRecords);
    //
    //  lay  DS detail
    while (isValid)
    {
        int materialId, quantity;
        bool quantityFlag = false;
        Material material;
        while (!quantityFlag)
        {
            cout << "Nhap ma VT : ";
            cin >> materialId;
            cout << "Nhap so luong : ";
            cin >> quantity;
            // tru di so luong vat tu
            material = updateMaterialById(materialId, quantity, materialList, numberOfMaterialRecords);
            // thoa dieu kien
            if (material.getId() > 0)
            {
                quantityFlag = true;
            }
            // khong ton tai
            else if (material.getId() == -1)
            {
                // do nothing
            }
            else
            {
                int quantityControl;
                cout << "Ban co muon nhap lai vat tu/ so luong khac khong, neu khong viec them don hang nay se bi huy ? (co : 1 / khong : 0 ) : ";
                cin >> quantityControl;
                // neu khong nhap lai, thoat vong lap nay
                if (!quantityControl)
                {
                    quantityFlag = true;
                    isValid = false;
                    cancel = 1;
                }
            }
        }
        // cong them tien vo tong gia
        if (cancel)
            break;

        totalWithoutDiscount += material.getUnitPrice() * quantity;

        // tao ctdh moi
        OrderDetail newOrderDeTail(id, materialId, quantity);
        // tang so luong record cua CTDH
        orderDetailList[numberOfODRecords++] = newOrderDeTail;
        // hoi them
        cout << "Ban co muon nhap tiep ? (co :1 /khong :0) : ";
        cin >> controlNumber;
        isValid = controlNumber;
    }
    if (!cancel)
    {
        // cap nhat file VT
        // in lai DS VT
        updateVT(numberOfMaterialRecords, materialList);
        delete[] materialList;

        // tinh thanh tien
        unsigned long totalPrice = totalWithoutDiscount - getDiscount(totalWithoutDiscount);
        // lay thoi gian dat
        string time = getCurrentTime("time");
        // lay dia chi giao
        string shippingAddress;
        cin.ignore();
        cout << endl
             << "Nhap dia chi giao hang : ";

        getline(cin, shippingAddress);
        // tao trang thai mac dinh
        string shippingStatus = "Chua xu ly";
        // in list detail vo CTDH
        Order newOrder(id, totalPrice, time, shippingAddress, shippingStatus);
        orderList[numberOfRecords++] = newOrder;

        updateCTDH(numberOfODRecords, orderDetailList);
        delete[] orderDetailList;

        // tin nhan thong bao
        cout << endl
             << "Da them don hang thanh cong !" << endl;
        cout << "Ban co muon tiep tuc them don hang ?  (co : 1 / khong : 0) : ";
        int controlFunction;
        cin >> controlFunction;

        if (controlFunction == 0)
        {
            controlOrderList(numberOfRecords, orderList);
        }
        else
            addOrder(numberOfRecords, orderList);
    }
    else
        controlOrderList(numberOfRecords, orderList);
}
void updateProvider(int numberOfRecords, Provider *providerList)
{

    printBox("CAP NHAT NSX");
    int id;
    // chọn mã vật tư
    cout << "Chon ma NSX : ";
    bool isValid = false;
    while (!isValid)
    {
        cin >> id;
        int i;
        for (i = 0; i < numberOfRecords; i++)
        {
            if (providerList[i].getId() == id)
                break;
        }
        // vật tư đã có
        if (i < numberOfRecords)
        { // lấy tên của NSX cần thay đổi
            string providerNameToFind = providerList[i].getName();

            // tên
            string name;
            // sdt
            string phoneNumber;
            // địa chỉ
            string address;
            // dùng để tránh lỗi do cin phía trước
            cin.ignore();
            cout << "Nhap '0' neu ban muon de thong tin nhu cu !" << endl;
            cout << "Nhap ten moi : ";
            getline(cin, name);
            cout << "Nhap SDT moi : ";
            getline(cin, phoneNumber);
            cout << "Nhap dia chi moi : ";
            getline(cin, address);
            if (name != "0")
                providerList[i].setName(name);
            if (phoneNumber != "0")
                providerList[i].setPhoneNumber(phoneNumber);
            if (address != "0")
                providerList[i].setAddress(address);

            // xác minh là tên mới có khác tên cũ không
            if (name != providerNameToFind)
            {
                // sửa toàn bộ thông tin NSX của vật tư liên quan
                // updateMaterialByProvider();

                Material *materialList = getMaterialList();
                int numberOfRecords = getNumberOfRecords(materialList, maxMaterialRecords);
                for (int i = 0; i < numberOfRecords; i++)
                {
                    if (materialList[i].getProviderName() == providerNameToFind)
                    {
                        materialList[i].setProviderName(name);
                    }
                }
                updateVT(numberOfRecords, materialList);
                delete[] materialList;
            }
            isValid = true;
        }
        else
        {
            cout << "Ma NSX khong ton tai , vui long nhap lai : ";
        }
    }
    cout << endl
         << "Da cap nhat NSX thanh cong !" << endl;
    cout << "Ban co muon tiep tuc cap nhat NSX ?  (co : 1 / khong : 0) : ";
    int controlNumber;

    cin >> controlNumber;

    if (controlNumber == 0)
    {
        
        controlProviderList(numberOfRecords, providerList);
    }
    else
        updateProvider(numberOfRecords, providerList);
}
void updateMaterial(int numberOfRecords, Material *materialList)
{
    printBox("CAP NHAT VAT TU");
    int id;
    // chọn mã vật tư
    cout << "Chon ma VT : ";
    bool isValid = false;
    while (!isValid)
    {
        cin >> id;
        int i;
        for (i = 0; i < numberOfRecords; i++)
        {
            if (materialList[i].getId() == id)
                break;
        }
        // vật tư đã có
        if (i < numberOfRecords)
        {
            // số lượng cần thêm
            unsigned long newPrice;
            int addNumber;
            string name;
            // dùng để tránh lỗi do cin phía trước
            cin.ignore();
            cout << "Nhap '0' neu ban muon de thong tin nhu cu !" << endl;
            cout << "Nhap ten moi : ";
            getline(cin, name);
            cout << "Nhap so luong can them : ";
            while (true)
            {
                cin >> addNumber;
                if (addNumber < 0)
                    cout << "So luong them khong the la so am ! Vui long nhap lai : ";
                else
                    break;
            }

            cout << "Nhap don gia moi : ";
            while (true)
            {
                cin >> newPrice;
                if (newPrice < 0)
                    cout << "Don gia khong the la so am ! Vui long nhap lai : ";
                else
                    break;
            }

            if (name != "0")
                materialList[i].setName(name);
            if (addNumber != 0)
                materialList[i].setQuantity(materialList[i].getQuantity() + addNumber);
            if (newPrice != 0)
                materialList[i].setUnitPrice(newPrice);

            isValid = true;
        }
        else
        {
            cout << "Ma VT khong ton tai , vui long nhap lai : ";
        }
    }
    cout << endl
         << "Da cap nhat VT thanh cong !" << endl;
    cout << "Ban co muon tiep tuc cap nhat VT ?  (co : 1 / khong : 0) : ";
    int controlNumber;
    cin >> controlNumber;
    if (controlNumber == 0)
    {
        

        controlMaterialList(numberOfRecords,materialList);
    }
    else
        updateMaterial(numberOfRecords, materialList);
}
void updateCategory(int numberOfRecords, Category *categoryList)
{
    printBox("CAP NHAT LVT");
    int id;
    // chọn mã loại vật tư
    cout << "Chon ma LVT : ";
    bool isValid = false;
    while (!isValid)
    {
        cin >> id;
        int i;
        for (i = 0; i < numberOfRecords; i++)
        {
            if (categoryList[i].getId() == id)
                break;
        }
        // vật tư đã có
        if (i < numberOfRecords)
        { // lấy tên của LVT cần thay đổi
            string categoryNameToFind = categoryList[i].getName();

            // tên
            string name;
            // dùng để tránh lỗi do cin phía trước
            cin.ignore();
            cout << "Nhap ten moi : ";
            getline(cin, name);
            categoryList[i].setName(name);

            // xác minh là tên mới có khác tên cũ không
            if (name != categoryNameToFind)
            {
                // sửa toàn bộ thông tin LVT của vật tư liên quan
                // updateMaterialByCategory();

                Material *materialList = getMaterialList();
                int numberOfRecords = getNumberOfRecords(materialList, maxMaterialRecords);
                for (int i = 0; i < numberOfRecords; i++)
                {
                    if (materialList[i].getCategoryName() == categoryNameToFind)
                    {
                        materialList[i].setCategoryName(name);
                    }
                }
                updateVT(numberOfRecords, materialList);
                delete[] materialList;
            }
            isValid = true;
        }
        else
        {
            cout << "Ma LVT khong ton tai , vui long nhap lai : ";
        }
    }
    cout << endl
         << "Da cap nhat LVT thanh cong !" << endl;
    cout << "Ban co muon tiep tuc cap nhat LVT ?  (co : 1 / khong : 0) : ";
    int controlNumber;

    cin >> controlNumber;

    if (controlNumber == 0)
    {
        
        controlCategoryList(numberOfRecords, categoryList);
    }
    else
        updateCategory(numberOfRecords, categoryList);
}
void updateOrder(int numberOfRecords, Order *orderList)
{
    // chon dh
    int id;
    printBox("CAP NHAT DON HANG");
    cout << "Nhap ma don hang : ";
    bool isValid = false;
    while (!isValid)
    {
        cin >> id;
        int i;
        for (i = 0; i < numberOfRecords; i++)
        {
            if (orderList[i].getId() == id)
                break;
        }
        // ton tai don hang
        if (i < numberOfRecords)
        {
            // truong hop 1 : don hang da giao
            if (orderList[i].getShippingStatus() == "Da giao")
            {
                cout << "Co le ban nhap nham ! Don hang nay da duoc giao roi , vui long nhap lai : ";
            }
            else
            {
                string shippingStatus;
                // dùng để tránh lỗi do cin phía trước
                cin.ignore();
                cout << "Nhap trang thai giao hang moi : ";
                getline(cin, shippingStatus);
                // cap nhat order
                orderList[i].setShippingStatus(shippingStatus);

                // thoat vong lap
                isValid = true;
            }
        }
        else
        {
            cout << "Ma don hang khong ton tai , vui long nhap lai : ";
        }
    }
    cout << endl
         << "Da cap nhat don hang thanh cong !" << endl;
    cout << "Ban co muon tiep tuc cap nhat don hang ?  (co : 1 / khong : 0) : ";
    int controlNumber;

    cin >> controlNumber;

    if (controlNumber == 0)
    { // in lai DS order vao file
        
        controlOrderList(numberOfRecords, orderList);
    }
    else
        updateOrder(numberOfRecords, orderList);
}
void deleteCategory(int &numberOfRecords, Category *categoryList)
{
    // nhap ma loai VT
    int id;
    bool isValid = false;
    cout << "Nhap ma loai VT can xoa : ";
    // vong lap kiem tra loai VT co ton tai hay k
    while (!isValid)
    {
        cin >> id;
        int i;
        for (i = 0; i < numberOfRecords; i++)
        {
            if (categoryList[i].getId() == id)
                break;
        }
        if (i == numberOfRecords)
        {
            cout << "Khong ton tai loai VT ban vua nhap ! Vui long nhap lai : ";
        }
        else
        {
            // khong du dieu kien
            if (!checkMaterialQuantityByCategoryName(categoryList[i].getName()))
            {
                cout << "So luong vat tu cua loai VT nay trong kho van con, khong the xoa loai VT!" << endl;
                break;
            }
            // du dieu kien
            for (int j = i; j < numberOfRecords - 1; j++)
            {

                categoryList[j] = categoryList[j + 1];
            }
            isValid = true;
            numberOfRecords--;
            // xoa toan bo VT du thua

            cout << endl
                 << "Da xoa loai VT thanh cong !" << endl;
        }
    }

    cout << "Ban co muon tiep tuc xoa loai VT ?  (co : 1 / khong : 0) : ";
    int controlNumber;

    cin >> controlNumber;

    if (controlNumber == 0)
    { // update file
        
        controlCategoryList(numberOfRecords, categoryList);
    }
    else
        deleteCategory(numberOfRecords, categoryList);
}

void deleteProvider(int &numberOfRecords, Provider *providerList)
{
    // nhap ma NSX
    int id, i;
    bool isValid = false;
    cout << "Nhap ma NSX can xoa : ";
    // vong lap kiem tra NSX co ton tai hay k
    while (!isValid)
    {
        cin >> id;
        for (i = 0; i < numberOfRecords; i++)
        {
            if (providerList[i].getId() == id)
                break;
        }

        if (i == numberOfRecords)
        {
            cout << "Khong ton tai NSX ban vua nhap ! Vui long nhap lai : ";
        }
        else
        {
            i = i;
            // khong du dieu kien
            if (!checkMaterialQuantityByProviderName(providerList[i].getName()))
            {
                cout << "So luong vat tu cua NSX nay trong kho van con, khong the xoa NSX!" << endl;
                break;
            }
            // du dieu kien
            for (int j = i; j < numberOfRecords - 1; j++)
            {

                providerList[j] = providerList[j + 1];
            }
            isValid = true;
            numberOfRecords--;
            // xoa toan bo VT du thua

            cout << endl
                 << "Da xoa NSX thanh cong !" << endl;
        }
    }

    cout << "Ban co muon tiep tuc xoa NSX ?  (co : 1 / khong : 0) : ";
    int controlNumber;

    cin >> controlNumber;

    if (controlNumber == 0)
    { // update file
        
        controlProviderList(numberOfRecords, providerList);
    }
    else
        deleteProvider(numberOfRecords, providerList);
}
void deleteMaterial(int &numberOfRecords, Material *materialList)
{
    // nhap ma VT
    int id, i;
    bool isValid = false;
    cout << "Nhap ma VT can xoa : ";
    // vong lap kiem tra VT co ton tai hay k

    /*
        Kiem tra so luong VT con lai la 0
        Neu khong thoa dieu kien thi buoc phai nhap lai, hoac lua chon thoat , tro ve QL VT
    */
    // isValid de kiem tra ma VT co ton tai khong
    while (!isValid)
    {
        cin >> id;
        // khoong ton tai
        for (i = 0; i < numberOfRecords; i++)
        {
            if (materialList[i].getId() == id)
                break;
        }

        if (i == numberOfRecords)
        {
            cout << "Khong ton tai VT ban vua nhap ! Vui long nhap lai : ";
        }
        // ton tai
        else
        {

            if (materialList[i].getQuantity() > 0)
            {
                // mot la tiep tuc nhap lai , hai la thoat , k xoa
                cout << "So luong vat tu trong kho van con, khong the xoa VT !" << endl;
                break;
            }
            // thoa dk
            for (int j = i; j < numberOfRecords - 1; j++)
            {
                materialList[j] = materialList[j + 1];
            }
            // dung de thoat vong lap
            isValid = true;
            // giam so luong record
            numberOfRecords--;
            cout << endl
                 << "Da xoa VT thanh cong !" << endl;
        }
    }

    cout << "Ban co muon tiep tuc xoa VT ?  (co : 1 / khong : 0) : ";
    int controlNumber;

    cin >> controlNumber;

    if (controlNumber == 0)
    { // update file
        
        controlMaterialList(numberOfRecords,materialList);
    }
    else
        deleteMaterial(numberOfRecords, materialList);
}
void deleteOrderHistory(int numberOfRecords, Order *orderList)
{
    // nhap ma Don Hang
    int id, i;
    bool isValid = false;
    cout << "Nhap ma Don Hang can xoa : ";
    // vong lap kiem tra Don Hang co ton tai hay k

    /*
        Kiem tra so luong Don Hang con lai la 0
        Neu khong thoa dieu kien thi buoc phai nhap lai, hoac lua chon thoat , tro ve QL Don Hang
    */
    // isValid de kiem tra ma Don Hang co ton tai khong
    while (!isValid)
    {
        cin >> id;
        // khoong ton tai
        for (i = 0; i < numberOfRecords; i++)
        {
            if (orderList[i].getId() == id)
                break;
        }

        if (i == numberOfRecords)
        {
            cout << "Khong ton tai Don Hang ban vua nhap ! Vui long nhap lai : ";
        }
        // ton tai
        else
        {
            if (orderList[i].getShippingStatus() == "Da giao")
            {
                for (int j = i; j < numberOfRecords - 1; j++)
                {
                    orderList[j] = orderList[j + 1];
                }
                // xoa CTDH theo DH
                deleteOrderDetailByOrderId(id);
                // dung de thoat vong lap
                
                // giam so luong record
                numberOfRecords--;
                cout << endl
                     << "Da xoa Don Hang thanh cong !" << endl;
                cout << "Ban co muon tiep tuc xoa Don Hang ?  (co : 1 / khong : 0) : ";
                int controlNumber;

                cin >> controlNumber;

                if (controlNumber == 0)
                { // update file
                    
                    controlOrderList(numberOfRecords, orderList);
                }
                else
                    deleteOrderHistory(numberOfRecords, orderList);
            }
            else {
                cout << "Don hang chua hoan thanh , khong the xoa lich su !" << endl;
                controlOrderList(numberOfRecords, orderList);
            }
            isValid = true;
        }
    }

    
}
void controlMaterialList(int numberOfRecords, Material *materialList){
    printBox("QUAN LY VAT TU");
    displayMaterialList(numberOfRecords, materialList);

    // chọn chức năng

    cout << setw(30) << left << "0. Quay lai";
    cout << setw(30) << left << "1. Them VT";
    cout << setw(30) << left << "2. Cap nhat thong tin VT";
    cout << "3. Cap nhat trang thai VT ( chua code )" << endl;
    bool isValid = false;
    while (isValid == false)
    {
        cout << endl
             << "Chon chuc nang : ";
        int controlNumber;
        cin >> controlNumber;
        switch (controlNumber)
        {
        case 0:
            updateVT(numberOfRecords, materialList);
            delete[] materialList;
            controlMain();
            isValid = true;
            break;
        case 1:
            addMaterial(numberOfRecords, materialList);
            isValid = true;
            break;
        case 2:
            updateMaterial(numberOfRecords, materialList);
            isValid = true;
            break;
        case 3:
            // ...
            cout << "Ban da chon chuc nang cap nhat trang thai vat tu " << endl;
            isValid = true;
            break;
        default:
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void controlProviderList(int &numberOfRecords, Provider *providerList){

    printBox("QUAN LY NSX");

    displayProviderList(numberOfRecords, providerList);

    // chọn chức năng

    cout << setw(20) << left << "0. Quay lai";
    cout << setw(20) << left << "1. Them NSX";
    cout << setw(35) << left << "2. Cap nhat thong tin NSX";
    cout << "3. Xoa NSX ( chua biet nen lam gi )" << endl;
    bool isValid = false;
    while (isValid == false)
    {
        cout << endl
             << "Chon chuc nang : ";
        int controlNumber;
        cin >> controlNumber;
        switch (controlNumber)
        {
        case 0:
            updateNSX(numberOfRecords, providerList);
            delete[] providerList;
            controlMain();
            isValid = true;
            break;
        case 1:
            addProvider(numberOfRecords, providerList);
            isValid = true;
            break;
        case 2:
            updateProvider(numberOfRecords, providerList);
            isValid = true;
            break;
        case 3:
            deleteProvider(numberOfRecords, providerList);
            break;
        default:
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void controlCategoryList(int &numberOfRecords, Category *categoryList){
    printBox("QUAN LY LOAI VT");
    displayCategoryList(numberOfRecords, categoryList);

    // chọn chức năng

    cout << setw(20) << left << "0. Quay lai";
    cout << setw(20) << left << "1. Them LVT";
    cout << setw(35) << left << "2. Cap nhat thong tin LVT";
    cout << "3. Xoa LVT (chua biet nen lam gi )" << endl;
    bool isValid = false;
    while (isValid == false)
    {
        cout << endl
             << "Chon chuc nang : ";
        int controlNumber;
        cin >> controlNumber;
        switch (controlNumber)
        {
        case 0:
            updateLVT(numberOfRecords, categoryList);
            delete[] categoryList;
            controlMain();
            isValid = true;
            break;
        case 1:
            addCategory(numberOfRecords, categoryList);
            isValid = true;
            break;
        case 2:
            updateCategory(numberOfRecords, categoryList);
            isValid = true;
            break;
        case 3:
            deleteCategory(numberOfRecords, categoryList);
            isValid = true;
            break;
        default:
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void controlOrderList(int numberOfRecords, Order *orderList){
    printBox("QUAN LY DON HANG");
    displayOrderList(numberOfRecords, orderList);

    // chọn chức năng

    cout << setw(40) << left << "0. Quay lai";
    cout << setw(30) << left << "1. Them don hang";
    cout << "2. Xem chi tiet don hang" << endl;
    cout << setw(40) << left << "3. Cap nhat trang thai giao hang";
    cout << setw(30) << left << "4. Huy don hang ( chua code)";
    cout << "5. Xoa lich su don hang" << endl;
    bool isValid = false;
    while (isValid == false)
    {
        cout << endl
             << "Chon chuc nang : ";
        int controlNumber;
        cin >> controlNumber;
        switch (controlNumber)
        {
        case 0:
            updateDH(numberOfRecords, orderList);
            delete[] orderList;
            controlMain();
            isValid = true;
            break;
        case 1:
            addOrder(numberOfRecords, orderList);
            isValid = true;
            break;

        case 2:
            viewOrderDetail(numberOfRecords, orderList);
            cout << "Nhan phim bat ky de quay lai ! " << endl;
            getch();
            manageOrders();
            break;
        case 3:
            updateOrder(numberOfRecords, orderList);
            isValid = true;
            break;
        case 4:

            cancelOrder(numberOfRecords, orderList);
            isValid = true;
            break;
        case 5:
            deleteOrderHistory(numberOfRecords, orderList);
            isValid = true;
            break;
        default:
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
// chưa viết
Material *filterMaterial(int numberOfRecords, Material *materialList)
{
    return NULL;
}
// ...
void cancelOrder(int numberOfRecords, Order *orderList){
    manageOrders();
}

    void printBox(string title)
{
    printUnderscore(lineLength);
    cout << endl;
    int length = title.length();
    int indent = (lineLength - length) / 2;
    for (int i = 0; i < indent; i++)
    {
        cout << " ";
    }
    cout << title << endl;
    printUnderscore(40);
    cout << endl;
}
void printUnderscore(int n)
{
    int indent = (lineLength - n) / 2;
    for (int i = 0; i < indent; i++)
        cout << " ";
    for (int i = 0; i < n; i++)
    {
        cout << "-";
    }
    cout << endl;
}
void printMenu()
{
    printBox("CHON CHUC NANG");
    printUnderscore(lineLength);
    cout << "0. Thoat chuong trinh"
         << "\t";
    cout <<setw(20)<<left<< "1. Quan ly VT"

         ;
    cout << "2. Quan ly nha san xuat"
         << "\t";
    cout << "3. Quan ly loai VT"
         << "\t";
    cout << "4. Quan ly hoa don " << endl;
    printUnderscore(lineLength);
    cout << endl;
}
void controlMain()
{
    printMenu();
    int number;
    cout << "Chon chuc nang: ";
    cin >> number;
    switch (number)
    {
    case 0:
        // them chao tam biet
        exit(0);
        break;
    case 1:
        manageMaterial();
        break;
    case 2:
        manageProviders();
        break;
    case 3:
        manageCategories();
        break;
    case 4:
        manageOrders();
        break;
    default:
        cout << "Khong co chuc nhap da nhap! "
             << "Moi ban nhap lai chuc nang" << endl;
        controlMain();
        break;
    }
}
