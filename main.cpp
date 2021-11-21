#include "Material.h"
#include "Category.h"
#include "Order.h"
#include "OrderDetail.h"
#include "Provider.h"
#include <conio.h>
#include <iomanip>
#define lineWidth 130
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

void addMaterial(int &numberOfRecords, Material *materialList);
void updateMaterialInformation(int numberOfRecords, Material *materialList);
void displayMaterialList(int numberOfRecords, Material *materialList);
void deleteMaterial(int &numberOfRecords, Material *materialList);
void searchMaterial(int &numberOfRecords, Material *materialList);
Material *filterMaterial(int &numberOfRecords, Material *materialList,
                         string name, string categoryName, string providerName,
                         int quantity,
                         unsigned long minUnitPrice, unsigned long maxUnitPrice);
void sortMaterialList(int numberOfRecords, Material *materialList);
// quản lý nhà sản xuất
void manageProviders();
void controlProviderList(int &numberOfRecords, Provider *providerList);
void addProvider(int &numberOfRecords, Provider *providerList);
void updateProviderInfor(int numberOfRecords, Provider *providerList);
void deleteProvider(int &numberOfRecords, Provider *providerList);
void sortProviderList(int numberOfRecords, Provider *providerList);
void displayProviderList(int numberOfRecords, Provider *providerList);
// quản lý loại vật tư
void manageCategories();
void controlCategoryList(int &numberOfRecords, Category *categoryList);
void addCategory(int &numberOfRecords, Category *categoryList);
void updateCategoryInfor(int numberOfRecords, Category *categoryList);
void deleteCategory(int &numberOfRecords, Category *categoryList);
void sortCategoryList(int numberOfRecords, Category *categoryList);
void displayCategoryList(int numberOfRecords, Category *categoryList);
// quản lý đơn hàng
void manageOrders();
void controlOrderList(int numberOfRecords, Order *orderList);
void displayOrderList(int numberOfRecords, Order *orderList);
void addOrder(int &numberOfRecords, Order *orderList);
void deleteOrderHistory(int numberOfRecords, Order *orderList);
void viewOrderDetail(int numberOfOrderDetail, Order *orderList);
void cancelOrder(int numberOfRecords, Order *orderList);
void ordersStatistics(int numberOfRecords, Order *oderList);
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
    /* string name, categoryName, providerName, quantity, minUnitPrice, maxUnitPrice;
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
    printUnderscore(lineWidth);
    // in tiêu đề
    cout << setw(10) << left << "Ma VT";
    cout << setw(24) << left << "Ten VT";
    cout << setw(16) << left << "Ten loai VT";
    cout << setw(24) << left << "Ten nha san xuat";
    cout << setw(15) << left << "Don vi tinh";
    cout << setw(15) << left << "So luong";
    cout << "Don gia" << endl
         << endl;
    for (int i = 0; i < numberOfRecords; i++)
    {
        cout << setw(10) << left << materialList[i].getId();
        cout << setw(24) << left << materialList[i].getName();
        cout << setw(16) << left << materialList[i].getCategoryName();
        cout << setw(24) << left << materialList[i].getProviderName();
        cout << setw(15) << left << materialList[i].getCalculationUnit();
        cout << setw(15) << left << materialList[i].getQuantity();
        cout << materialList[i].getUnitPrice() << endl;
    }
    printUnderscore(lineWidth);
}
void displayProviderList(int numberOfRecords, Provider *providerList)
{

    cout << endl;
    printUnderscore(lineWidth);
    // in tiêu đề
    cout << setw(10) << left << "Ma NSX";
    cout << setw(32) << left << "Ten NSX";
    cout << setw(16) << left << "SDT";
    cout << setw(16) << left << "Ngay hop tac";
    cout << "Dia chi" << endl
         << endl;

    for (int i = 0; i < numberOfRecords; i++)
    {
        cout << setw(10) << left << providerList[i].getId();
        cout << setw(32) << left << providerList[i].getName();
        cout << setw(16) << left << providerList[i].getPhoneNumber();
        cout << setw(16) << left << providerList[i].getDate();
        cout << providerList[i].getAddress() << endl;
    }
    printUnderscore(lineWidth);
}
void displayCategoryList(int numberOfRecords, Category *categoryList)
{
    cout << endl;
    printUnderscore(lineWidth);
    // in tiêu đề
    cout << setw(20) << left << "Ma LVT";
    cout << "Ten LVT" << endl
         << endl;
    for (int i = 0; i < numberOfRecords; i++)
    {
        cout << setw(20) << left << categoryList[i].getId();
        cout << categoryList[i].getName() << endl;
    }
    printUnderscore(lineWidth);
}
void displayOrderList(int numberOfRecords, Order *orderList)
{
    cout << endl;
    printUnderscore(lineWidth);
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
    printUnderscore(lineWidth);
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
    printUnderscore(lineWidth);
    cout << setw(5) << "STT";

    // in ten VT
    cout << setw(25) << "Ten VT";
    cout << setw(10) << "Loai VT";
    cout << setw(25) << "NSX";
    cout << setw(20) << "Don vi tinh";
    cout << setw(10) << "So luong";
    cout << setw(10) << "Don gia";
    cout << "Thanh tien" << endl
         << endl;
    // lay ds VT con va da xoa
    Material *materialList = getMaterialList();
    int numberOfMaterialRecords = getNumberOfRecords(materialList, maxMaterialRecords);
    Material *deletedMaterialList = getDeletedMaterialList();
    int numberOfDeletedMaterialRecords = getNumberOfRecords(deletedMaterialList, maxMaterialRecords);
    // 8, 4
    for (int i = numberOfMaterialRecords; i < numberOfMaterialRecords + numberOfDeletedMaterialRecords; i++)
    {
        materialList[i] = deletedMaterialList[i - numberOfMaterialRecords];
    }
    numberOfMaterialRecords += numberOfDeletedMaterialRecords;

    // tìm mã đơn hàng trong CTDH và in
    unsigned long totalWithoutDiscount = 0;
    for (int i = 0; i < numberOfRecords; i++)
    {
        if (orderDetailList[i].getId() == id)
        {

            Material materialById = getMaterialById(orderDetailList[i].getMaterialId(), materialList);
            cout << setw(5) << stt++;

            // in ten VT
            cout << setw(25) << materialById.getName();

            cout << setw(10) << materialById.getCategoryName();
            cout << setw(25) << materialById.getProviderName();
            cout << setw(20) << materialById.getCalculationUnit();
            cout << setw(10) << orderDetailList[i].getQuantity();
            cout << setw(10) << materialById.getUnitPrice();

            unsigned long price = orderDetailList[i].getQuantity() * materialById.getUnitPrice();
            totalWithoutDiscount += price;
            cout << price << endl;
        }
    }
    printUnderscore(lineWidth * 3 / 4);
    unsigned long discount = getDiscount(totalWithoutDiscount);
    cout << "Tong tien (chua giam gia) : " << totalWithoutDiscount << endl;
    cout << "Giam gia ( " << discount * 100 / totalWithoutDiscount << "% ) : " << discount << endl;
    cout << "Thanh tien : " << totalWithoutDiscount - discount << endl;
    printUnderscore(lineWidth);
    delete[] materialList;
    delete[] orderDetailList;
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
    Material *deletedMaterialList = getDeletedMaterialList();
    int numberOfDeletedMaterialRecords = getNumberOfRecords(deletedMaterialList, maxMaterialRecords);

    int id1 = getNextId(materialList, numberOfRecords);
    int id2 = getNextId(deletedMaterialList, numberOfDeletedMaterialRecords);
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

        int number = findMaterialByName(name);
        if ((number >= 0) && (materialList[number].getProviderName() == providerName) && (materialList[number].getUnitPrice() == unitPrice))
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
        Material newMaterial(id, name, categoryName, providerName, calculationUnit, quantity, unitPrice);
        materialList[numberOfRecords++] = newMaterial;

        // tin nhan thong bao
        cout << endl
             << "Da them VT thanh cong !" << endl;
        cout << "Ban co muon tiep tuc them VT ?  (co : 1 / khong : 0) : ";
        int controlNumber;
        cin >> controlNumber;
        if (controlNumber == 0)
        {

            controlMaterialList(numberOfRecords, materialList);
        }
        else
            addMaterial(numberOfRecords, materialList);
    }
    else
        controlMaterialList(numberOfRecords, materialList);
}
void addProvider(int &numberOfRecords, Provider *providerList)

{
    int id;
    string name, phoneNumber, date, address;
    printBox("THEM NHA SAN XUAT");
    // can be REFACTORED
    // tìm id lớn nhất
    id = getNextId(providerList, numberOfRecords);
    // bắt đầu lấy dữ liệu từ người dùng
    // dùng để tránh lỗi do cin phía trước
    bool isCancel = false;
    while (true)
    {
        cin.ignore();
        int controlNumber;
        bool isValid = true;
        cout << "Nhap ten : ";
        getline(cin, name);
        if (checkProviderByName(name))
        {
            cout << endl
                 << "NSX da ton tai !" << endl;
            isCancel = true;
        }
        else
        {
            isCancel = false;
            cout << "Nhap SDT : ";
            getline(cin, phoneNumber);
            cout << "Nhap ngay hop tac (dd/mm/yyyy ) : ";
            getline(cin, date);
            cout << "Nhap dia chi : ";
            getline(cin, address);
        }

        cout << "Ban co muon nhap lai ? (co : 1 / khong : 0) : ";
        cin >> controlNumber;
        cout << endl;
        if (controlNumber == 0)
            break;
    }
    if (!isCancel)
    {
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
    else
    {
        controlProviderList(numberOfRecords, providerList);
    }
}
void addCategory(int &numberOfRecords, Category *categoryList)
{
    int id;
    string name;
    printBox("THEM LOAI VAT TU");
    // can be REFACTORED
    // tìm id lớn nhất

    id = getNextId(categoryList, numberOfRecords);
    // bắt đầu lấy dữ liệu từ người dùng
    // dùng để tránh lỗi do cin phía trước
    bool isCancel = false;
    while (true)
    {
        cin.ignore();
        int controlNumber;
        bool isValid = true;
        cout << "Nhap ten : ";
        getline(cin, name);
        if (checkCategoryByName(name))
        {
            cout << endl
                 << "LVT da ton tai!" << endl;

            isCancel = true;
        }
        else
        {
            isCancel = false;
        }
        cout << "Ban co muon nhap lai ? (co : 1 / khong : 0) : ";
        cin >> controlNumber;
        cout << endl;
        if (controlNumber == 0)
            break;
    }
    if (!isCancel)
    {
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
    else
        controlCategoryList(numberOfRecords, categoryList);
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

    int id = getNextId(orderList, numberOfRecords);
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
            while (true)
            {
                cin >> quantity;
                if (quantity <= 0)
                    cout << "So luong phai lon hon 0, vui long nhap lai: ";
                else
                    break;
            }

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
        cout << endl
             << "Ban co muon nhap tiep ? (co :1 /khong :0) : ";
        cin >> controlNumber;
        cout << endl;
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
void updateProviderInfor(int numberOfRecords, Provider *providerList)
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
                // lay list va so record của tồn tại và deleted

                Material *materialList = getMaterialList();
                int numberOfMaterialRecords = getNumberOfRecords(materialList, maxMaterialRecords);

                Material *deletedMaterialList = getDeletedMaterialList();
                int numberOfDeletedMaterialRecords = getNumberOfRecords(deletedMaterialList, maxMaterialRecords);

                // het doan lay thong tin
                for (int i = 0; i < numberOfMaterialRecords; i++)
                {
                    if (materialList[i].getProviderName() == providerNameToFind)
                    {
                        materialList[i].setProviderName(name);
                    }
                }
                for (int i = 0; i < numberOfDeletedMaterialRecords; i++)
                {
                    if (deletedMaterialList[i].getProviderName() == providerNameToFind)
                    {
                        deletedMaterialList[i].setProviderName(name);
                    }
                }
                updateVT(numberOfMaterialRecords, materialList);
                updateDeletedVT(numberOfDeletedMaterialRecords, deletedMaterialList);
                delete[] materialList;
                delete[] deletedMaterialList;
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
        updateProviderInfor(numberOfRecords, providerList);
}
void updateMaterialInformation(int numberOfRecords, Material *materialList)
{
    printBox("CAP NHAT THONG TIN VAT TU");
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
            string categoryName;
            string providerName;
            // dùng để tránh lỗi do cin phía trước
            cin.ignore();
            cout << "Nhap '0' neu ban muon de thong tin nhu cu !" << endl;
            cout << "Nhap ten moi : ";
            getline(cin, name);
            if (name != "0")
                materialList[i].setName(name);
            cout << "Nhap ten loai VT : ";
            while (true)
            {
                getline(cin, categoryName);
                if (categoryName == "0")
                    break;
                else
                {
                    if (checkCategoryByName(categoryName))
                    {
                        materialList[i].setCategoryName(categoryName);
                        break;
                    }
                    else
                        cout << "Loai VT k ton tai , vui long nhap lai: ";
                }
            }
            cout << "Nhap ten NSX : ";
            while (true)
            {
                getline(cin, providerName);
                if (providerName == "0")
                    break;
                else
                {
                    if (checkProviderByName(providerName))
                    {
                        materialList[i].setProviderName(providerName);
                        break;
                    }
                    else
                        cout << "NSX k ton tai , vui long nhap lai: ";
                }
            }

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

            //.... loi k ton tai ten loai VT
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

        controlMaterialList(numberOfRecords, materialList);
    }
    else
        updateMaterialInformation(numberOfRecords, materialList);
}
void updateCategoryInfor(int numberOfRecords, Category *categoryList)
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
                int numberOfMaterialRecords = getNumberOfRecords(materialList, maxMaterialRecords);

                Material *deletedMaterialList = getDeletedMaterialList();
                int numberOfDeletedMaterialRecords = getNumberOfRecords(deletedMaterialList, maxMaterialRecords);

                // het doan lay thong tin
                for (int i = 0; i < numberOfMaterialRecords; i++)
                {
                    if (materialList[i].getCategoryName() == categoryNameToFind)
                    {
                        materialList[i].setCategoryName(name);
                    }
                }
                for (int i = 0; i < numberOfDeletedMaterialRecords; i++)
                {
                    if (deletedMaterialList[i].getCategoryName() == categoryNameToFind)
                    {
                        deletedMaterialList[i].setCategoryName(name);
                    }
                }
                updateVT(numberOfMaterialRecords, materialList);
                updateDeletedVT(numberOfDeletedMaterialRecords, deletedMaterialList);
                delete[] materialList;
                delete[] deletedMaterialList;
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
        updateCategoryInfor(numberOfRecords, categoryList);
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
            // insert vao file da xoa
            Material *deletedMaterialList = getDeletedMaterialList();
            ofstream deletedOut(DeletedVT, ios::out | ios::app);
            insertDeletedMaterial(materialList[i], deletedOut);
            delete[] deletedMaterialList;
            deletedOut.close();
            // ham them vo , insert
            //  ham lay ra, de doc order , get
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

        controlMaterialList(numberOfRecords, materialList);
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
            else
            {
                cout << "Don hang chua hoan thanh , khong the xoa lich su !" << endl;
                controlOrderList(numberOfRecords, orderList);
            }
            isValid = true;
        }
    }
}
void searchMaterial(int &numberOfRecords, Material *materialList)
{
    int id;
    string name, categoryName, providerName;
    int quantity;
    unsigned long minUnitPrice, maxUnitPrice;
    cout << "Nhap 0 neu ban muon bo qua!" << endl;
    // * I. Lấy input
    cin.ignore();
    cout << "Nhap ten : ";
    getline(cin, name);
    if (name == "0")
        name = "\0";

    cout << "Nhap ten loai VT: ";
    getline(cin, categoryName);
    if (categoryName == "0")
        categoryName = "\0";

    cout << "Nhap ten NSX : ";
    getline(cin, providerName);
    if (providerName == "0")
        providerName = "\0";

    cout << "Nhap so luong( it nhat): ";
    cin >> quantity;

    cout << "Nhap don gia :" << endl;
    cout << "\t"
         << "Thap nhat: ";
    cin >> minUnitPrice;
    cout << "\t"
         << "Cao nhat: ";
    cin >> maxUnitPrice;
    if (maxUnitPrice == 0)
        maxUnitPrice = 1000000000;

    // * II. Tạo ds mới với những tiêu chí đã lọc ( numberOfRecords đã tự động thay đổi)

    materialList = filterMaterial(numberOfRecords, materialList,
                                  name, categoryName, providerName,
                                  quantity,
                                  minUnitPrice, maxUnitPrice);
    // * III. Tra ve quan ly
    controlMaterialList(numberOfRecords, materialList);
}
void sortMaterialList(int numberOfRecords, Material *materialList)
{
    cout << "Ban muon sap xep theo tieu chi nao ? " << endl
         << endl;
    cout << setw(15) << "1. Ma VT" << setw(20) << " 2. Ten vat tu" << setw(20) << " 3. Ten loai VT" << setw(25) << " 4. Ten nha san xuat" << setw(20) << " 5. So luong"
         << " 6. Don gia " << endl
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
        if (a == 't')
            sortById(materialList, numberOfRecords, ascending);
        else
            sortById(materialList, numberOfRecords, descending);
        break;

    case 2:
        if (a == 't')
            sortByName(materialList, numberOfRecords, ascending);
        else
            sortByName(materialList, numberOfRecords, descending);
        break;

    case 3:
        if (a == 't')
            sortByCateOrProName("categoryName", materialList, numberOfRecords, ascending);
        else
            sortByCateOrProName("categoryName", materialList, numberOfRecords, descending);
        break;

    case 4:
        if (a == 't')
            sortByCateOrProName("providerName", materialList, numberOfRecords, ascending);
        else
            sortByCateOrProName("providerName", materialList, numberOfRecords, descending);
        break;

    case 5:
        if (a == 't')
            sortByQuantityOrUnitPrice("quantity", materialList, numberOfRecords, ascending);
        else
            sortByQuantityOrUnitPrice("quantity", materialList, numberOfRecords, descending);
        break;

    case 6:
        if (a == 't')
            sortByQuantityOrUnitPrice("unitPrice", materialList, numberOfRecords, ascending);
        else
            sortByQuantityOrUnitPrice("unitPrice", materialList, numberOfRecords, descending);
        break;
    }
    controlMaterialList(numberOfRecords, materialList);
}
void sortProviderList(int numberOfRecords, Provider *providerList)
{

    cout << "Ban muon sap xep theo tieu chi nao ? " << endl
         << endl;
    cout << setw(20) << "1. Ma NSX" << setw(20) << "2. Ten NSX"
         << "3. Ngay hop tac" << endl
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
        if (a == 't')
            sortById(providerList, numberOfRecords, ascending);
        else
            sortById(providerList, numberOfRecords, descending);
        break;

    case 2:
        if (a == 't')
            sortByName(providerList, numberOfRecords, ascending);
        else
            sortByName(providerList, numberOfRecords, descending);
        break;

    case 3:
        if (a == 't')
            sortByDate(providerList, numberOfRecords, ascendingDate);
        else
            sortByDate(providerList, numberOfRecords, descendingDate);
        break;
    }
    controlProviderList(numberOfRecords, providerList);
}
void sortCategoryList(int numberOfRecords, Category *categoryList)
{

    cout << "Ban muon sap xep theo tieu chi nao ? " << endl
         << endl;
    cout << setw(20) << "1. Ma loai VT"
         << "2. 2.  loai VT" << endl
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
        if (a == 't')
            sortById(categoryList, numberOfRecords, ascending);
        else
            sortById(categoryList, numberOfRecords, descending);
        break;

    case 2:
        if (a == 't')
            sortByName(categoryList, numberOfRecords, ascending);
        else
            sortByName(categoryList, numberOfRecords, descending);
        break;
    }
    controlCategoryList(numberOfRecords, categoryList);
}
void ordersStatistics(int numberOfRecords, Order *oderList)

{
    // ... thống kê theo tháng
    printBox("THONG KE DOANH THU");

    Order *orderList = getOrderList();

    int numberOfOrderRecords = getNumberOfRecords(orderList, maxOrderRecords);

    // * I. Tinh cac du lieu can thiet
    // * I.1 Doanh thu  2. Tong don hang   3. Tong gia goc   4. Cac don hang duoc ban

    // * Doanh thu
    unsigned long totalPrice = 0;
    // * Tong don hang duoc ban
    int numberOfOrders = 0;
    // * Tong gia goc
    unsigned long originalToTalPrice = 0;
    // * Mang chua cac don hang duoc ban, khoi tao mang bang 0, neu thoa thi cho bang 1
    int maxSize = getNextId(orderList, numberOfOrderRecords);
    bool soldOrders[maxSize];
    for (int i = 0; i < maxSize; i++)
    {
        soldOrders[i] = 0;
    }

    // * I.2 Bat dau duyet orderList va tinh cac gia tri
    for (int i = 0; i < numberOfOrderRecords; i++)

    {
        Order temp = orderList[i];
        string status = temp.getShippingStatus();
        // * neu thoa dieu kien
        if ((status!= "Da huy") && (status!= "Chua xu ly")){

            totalPrice += temp.getTotalPrice();

            numberOfOrders++;

            originalToTalPrice += getOriginalPrice(temp.getTotalPrice());
            soldOrders[temp.getId()] = 1;
        }
    }

    cout << "Tong so don hang da ban la: " << numberOfOrders << endl;
    cout << "Tong doanh thu la: " << totalPrice << endl;



    // * II. Thong ke theo loai VT
    // * II.1. Lay orderDetailList

    OrderDetail *orderDetailList = getOrderDetailList();
    int numberOfODRecords = getNumberOfRecords(orderDetailList, maxOrderDetailRecords);

    // * II.2 Lay ds Vat tu cung doanh thu
    Material *materialList = getMaterialList();
    int numberOfMaterialRecords = getNumberOfRecords(materialList, maxMaterialRecords);
    Material *deletedMaterialList = getDeletedMaterialList();
    int numberOfDeletedMaterialRecords = getNumberOfRecords(deletedMaterialList, maxMaterialRecords);

    for (int i = numberOfMaterialRecords; i < numberOfMaterialRecords + numberOfDeletedMaterialRecords; i++)
    {
        materialList[i] = deletedMaterialList[i - numberOfMaterialRecords];
    }
    numberOfMaterialRecords += numberOfDeletedMaterialRecords;

    //  * khởi tạo mảng lưu giá trị % của từng VT, khởi đầu =0
    double materialPercentage[numberOfMaterialRecords+1];
    for (int i = 1; i <= numberOfMaterialRecords; i++)
    {
        materialPercentage[i] = 0;
    }

    // * Luu ten loai VT
    string categoryNames[maxCategoryRecords];
    int categoryCount = 0;
    // * Luu phan tram
    double categoryPercentage[maxCategoryRecords];
    for (int i = 0; i < maxCategoryRecords;i++){
        categoryPercentage[i] = 0;
    }
        // * II. 3 Luu gia tri % cua tung vat va loai VT vao mang

        OrderDetail temp;
    for (int i = 0; i < numberOfODRecords; i++)
    {
        
        
        temp = orderDetailList[i];

        // * phai thoa dkien la order phai dc ban
        if (soldOrders[temp.getId()]){
            // * 1. Tinh tổng giá của từng ..
            int materialId = temp.getMaterialId();
            Material material = getMaterialById(materialId, materialList);
            unsigned long price = temp.getQuantity() *material.getUnitPrice();

            double percentage = (double)price / originalToTalPrice * 100;
            materialPercentage[materialId] += percentage;

            string categoryName=material.getCategoryName();
            int j = 0;
            // * th1 : neu ten vat tu da ton tai
            for (; j < categoryCount; j++)
            {
                if (categoryNames[j]==categoryName){
                    categoryPercentage[j] += percentage;
                    break;
                }
            }
            // * th2: ten vat tu chua ton tai
            if (j==categoryCount){
                categoryNames[j]=categoryName;
                categoryPercentage[j] = percentage;
                categoryCount++;
            }


        }

        
    }
    // * III. Sap xep vat tu theo %
    // * II.1 Tao mang luu thu tu

    int rankMaterial[numberOfMaterialRecords+1];
    for(int i=1;i<=numberOfMaterialRecords;i++){
        rankMaterial[i] = i;
    }

    // * II.2 Sap xep gia tri cua rank..[i] theo % cua rank[i]

    sortByPercentage(rankMaterial, materialPercentage, numberOfMaterialRecords + 1, descending);

    // * III. In ra bang xep hang theo tieu chi vat tu

    printBox("THONG KE THEO VAT TU");

    printUnderscore(lineWidth*10/13);
    cout << setw(18)<<""<<setw(10) << "STT" << setw(20) << "Ten vat tu" << setw(25) << ("Ten loai VT") << setw(30) << "Ten NSX"
         << "%" << endl<<endl;
    int stt = 1;
    for (int i = 1; i < numberOfMaterialRecords + 1;i++){
        int materialId = rankMaterial[i];
        double percentage=materialPercentage[materialId];
        if (percentage!=0){
            Material material = getMaterialById(materialId, materialList);
            cout << setw(18) << "";
            cout << setw(10) << stt++;
            cout << setw(20) << material.getName();
            cout << setw(25) << material.getCategoryName();
            
                cout << setw(30) << material.getProviderName();
            cout << fixed<<setprecision(2)<<percentage;
            cout << endl;
        }
    }
    printUnderscore(lineWidth * 10 / 13);
    // * IIII.4 Sap xep theo loai VT
    // * IIII.4.1 Tao cac mang luu du lieu
    
    // * Luu  thu tu cua index
    int categoryOrder[categoryCount];
    for (int i = 0;i<categoryCount;i++){
        categoryOrder[i] = i;
    }
    sortCategoryByPercentage(categoryOrder,categoryPercentage,categoryCount,descending);


    printBox("THONG KE THEO LOAI VAT TU");

    printUnderscore(lineWidth*5/13);
    cout << setw(45) << "" <<setw(10) << "STT" << setw(25) << "Ten loai VT"
         << "%" << endl
         << endl;
    for (int i = 0; i < categoryCount; i++)
    {
        int index = categoryOrder[i];
        cout << setw(45) << "";
        cout <<setw(10)<< (i + 1);
        cout<<setw(25)<<categoryNames[index];
        cout<<categoryPercentage[index];
        cout << endl;
    }
    printUnderscore(lineWidth * 5 / 13);
    cout << "An phim bat ky de tiep tuc..." << endl;
    getch();
    controlOrderList(numberOfOrderRecords, orderList);
}
void controlMaterialList(int numberOfRecords, Material *materialList)
{
    printBox("QUAN LY VAT TU");
    displayMaterialList(numberOfRecords, materialList);

    // chọn chức năng

    cout << setw(20) << left << "0. Quay lai";
    cout << setw(20) << left << "1. Them VT";
    cout << setw(30) << left << "2. Cap nhat thong tin VT";
    cout << setw(20) << "3. Xoa VT";
    cout << setw(20) << "4. Tim kiem";
    cout << setw(20) << "5. Sap xep";
    cout << endl;
    bool isValid = false;
    while (isValid == false)
    {
        cout << endl
             << "Chon chuc nang : ";
        int controlNumber;
        cin >> controlNumber;
        cout << endl;
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
            updateMaterialInformation(numberOfRecords, materialList);
            isValid = true;
            break;
        case 3:

            deleteMaterial(numberOfRecords, materialList);
            isValid = true;
            break;
        case 4:
            searchMaterial(numberOfRecords, materialList);
            isValid = true;
            break;
        case 5:
            sortMaterialList(numberOfRecords, materialList);
            isValid = true;
            break;
        default:
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void controlProviderList(int &numberOfRecords, Provider *providerList)
{

    printBox("QUAN LY NSX");

    displayProviderList(numberOfRecords, providerList);

    // chọn chức năng

    cout << setw(20) << left << "0. Quay lai";
    cout << setw(20) << left << "1. Them NSX";
    cout << setw(35) << left << "2. Cap nhat thong tin NSX";
    cout << setw(20) << "3. Xoa NSX";

    cout << setw(20) << "4. Tim kiem";
    cout << setw(20) << "5. Sap xep";
    cout << endl;
    bool isValid = false;
    while (isValid == false)
    {
        cout << endl
             << "Chon chuc nang : ";
        int controlNumber;
        cin >> controlNumber;
        cout << endl;
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
            updateProviderInfor(numberOfRecords, providerList);
            isValid = true;
            break;
        case 3:
            deleteProvider(numberOfRecords, providerList);
            isValid = true;
            break;
        case 4:

            isValid = true;
            break;
        case 5:
            sortProviderList(numberOfRecords, providerList);
            isValid = true;
            break;
        default:
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void controlCategoryList(int &numberOfRecords, Category *categoryList)
{
    printBox("QUAN LY LOAI VT");
    displayCategoryList(numberOfRecords, categoryList);

    // chọn chức năng

    cout << setw(20) << left << "0. Quay lai";
    cout << setw(20) << left << "1. Them LVT";
    cout << setw(35) << left << "2. Cap nhat thong tin LVT";
    cout << setw(20) << "3. Xoa LVT";
    cout << setw(20) << "4. Tim kiem";
    cout << setw(20) << "5. Sap xep";
    cout << endl;
    bool isValid = false;
    while (isValid == false)
    {
        cout << endl
             << "Chon chuc nang : ";
        int controlNumber;
        cout << endl;
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
            updateCategoryInfor(numberOfRecords, categoryList);
            isValid = true;
            break;
        case 3:
            deleteCategory(numberOfRecords, categoryList);
            isValid = true;
            break;
        case 4:

            isValid = true;
            break;
        case 5:
            sortCategoryList(numberOfRecords, categoryList);
            isValid = true;
            break;
        default:
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void controlOrderList(int numberOfRecords, Order *orderList)
{
    printBox("QUAN LY DON HANG");
    displayOrderList(numberOfRecords, orderList);

    // chọn chức năng

    cout << setw(40) << left << "0. Quay lai";
    cout << setw(30) << left << "1. Them don hang";
    cout << "2. Xem chi tiet don hang" << endl;
    cout << setw(40) << left << "3. Cap nhat trang thai giao hang";
    cout << setw(30) << left << "4. Huy don hang";
    cout << "5. Thong ke doanh thu";
    cout << endl;
    bool isValid = false;
    while (isValid == false)
    {
        cout << endl
             << "Chon chuc nang : ";
        int controlNumber;
        cout << endl;
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
            controlOrderList(numberOfRecords, orderList);
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
            ordersStatistics(numberOfRecords, orderList);
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
Material *filterMaterial(int &numberOfRecords, Material *materialList,
                         string name, string categoryName, string providerName,
                         int quantity,
                         unsigned long minUnitPrice, unsigned long maxUnitPrice)
{
    int count = 0;
    Material material;
    // * I. LOC
    for (int i = 0; i < numberOfRecords; i++)
    {
        material = materialList[i];

        if ((toLower(material.getName()).find(name) != string::npos) &&
            ((toLower(material.getCategoryName()).find(categoryName) != string::npos)) &&
            (toLower(material.getProviderName()).find(providerName) != string::npos) &&
            (material.getQuantity() >= quantity) &&
            (material.getUnitPrice() >= minUnitPrice) &&
            (material.getUnitPrice() <= maxUnitPrice))
        {
            materialList[count] = material;
            cout << material.getName() << endl;
            count++;
        }
    }

    // * II. Tra  ve ds moi
    numberOfRecords = count;
    return materialList;
}
// ...
void cancelOrder(int numberOfRecords, Order *orderList)
{
    int orderId;
    printBox("HUY DON HANG");
    cout << "Nhap ma don hang : ";
    bool isCancel = false;
    while (true)
    {
        int i = 0;
        cin >> orderId;
        for (; i < numberOfRecords; i++)
        {
            if (orderList[i].getId() == orderId)
                break;
        }
        if (i < numberOfRecords)
        {
            if (orderList[i].getShippingStatus() == "Chua xu ly")
            {
                Material *materialList = getMaterialList();
                int numberOfMaterialRecords = getNumberOfRecords(materialList, maxMaterialRecords);

                Material *deletedMaterialList = getDeletedMaterialList();
                int numberOfDeletedMaterialRecords = getNumberOfRecords(deletedMaterialList, maxMaterialRecords);

                isCancel = false;
                orderList[i].setShippingStatus("Da huy");
                // doan code phuc hoi so luong vat tu
                OrderDetail *orderDetailList = getOrderDetailList();
                int numberOfODRecords = getNumberOfRecords(orderDetailList, maxOrderDetailRecords);
                for (int i = 0; i < numberOfODRecords; i++)
                {
                    int tempId = orderDetailList[i].getId();
                    // * tới chỗ có mã đơn hàng cần tìm
                    if (tempId == orderId)
                    {

                        // phuc hoi so luong cua vat tu nay
                        restoreMaterial(orderDetailList[i].getMaterialId(), orderDetailList[i].getQuantity(), materialList, numberOfMaterialRecords, deletedMaterialList, numberOfDeletedMaterialRecords);
                    }
                    else if (tempId > orderId)
                        break;
                }
                delete[] orderDetailList;
                updateVT(numberOfMaterialRecords, materialList);
                delete[] materialList;
                updateDeletedVT(numberOfDeletedMaterialRecords, deletedMaterialList);
                delete[] deletedMaterialList;
                break;
            }
            else
            {
                cout << "Don hang nay khong the huy, ban co muon nhap lai (1 : co | khong : 0): ";
                int controlNumber;
                cin >> controlNumber;
                if (controlNumber == 0)
                {
                    isCancel = true;
                    break;
                }
            }
        }
        else
        {
            cout << "Vat tu khong ton tai, vui long nhap lai: ";
        }
    }
    if (isCancel)
        controlOrderList(numberOfRecords, orderList);
    else
    {
        cout << endl
             << "Da huy Don Hang thanh cong !" << endl;
        cout << "Ban co muon tiep tuc huy Don Hang ?  (co : 1 / khong : 0) : ";
        int controlNumber;

        cin >> controlNumber;

        if (controlNumber == 0)
        { // update file

            controlOrderList(numberOfRecords, orderList);
        }
        else
            cancelOrder(numberOfRecords, orderList);
    }
}

void printBox(string title)
{
    printUnderscore(lineWidth);
    cout << endl;
    int length = title.length();
    int indent = (lineWidth - length) / 2;
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
    int indent = (lineWidth - n) / 2;
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
    printUnderscore(lineWidth);
    cout << "0. Thoat chuong trinh"
         << "\t";
    cout << setw(20) << left << "1. Quan ly VT"

        ;
    cout << "2. Quan ly nha san xuat"
         << "\t";
    cout << "3. Quan ly loai VT"
         << "\t";
    cout << "4. Quan ly hoa don " << endl;
    printUnderscore(lineWidth);
    cout << endl;
}
void controlMain()
{
    printMenu();
    int number;
    cout << "Chon chuc nang: ";
    cin >> number;
    cout << endl;

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
