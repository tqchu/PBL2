#include "Material.h"
#include "Category.h"
#include "Order.h"
#include "OrderDetail.h"
#include "Provider.h"
#include <conio.h>
#include <iomanip>
#define lineWidth 130
// in chào 
void printHello();
// in tạm biệt
void printGoodBye();
// in dấu gạch dưới
void printUnderscore(int n);
// in dấu gạch ngang
void printHyphen(int n);
// in menu
void printMenu();
// chọn chức năng chính
void controlMain();
// in hộp quản lý
void printBox(string title);
void printSmallBox(string title);
// quản lý vật tư
void manageMaterial();
void controlMaterialList(int numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList);

void addMaterial(int &numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList);
void updateMaterialInformation(int numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList);
void displayMaterialList(int numberOfRecords, Material *materialList);
void deleteMaterial(int &numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList);
void searchMaterial(int &numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList);
void filterMaterial(int numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList,
                    string name, string categoryName, string providerName,
                    int quantity,
                    unsigned long minUnitPrice, unsigned long maxUnitPrice);
void sortMaterialList(int numberOfRecords, Material *materialList);
// quản lý nhà sản xuất
void manageProviders();
void controlProviderList(int &numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList);
void addProvider(int &numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList);
void updateProviderInfor(int numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList);
void deleteProvider(int &numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList);
void searchProvider(int &numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList);
void sortProviderList(int numberOfRecords, Provider *providerList);
void displayProviderList(int numberOfRecords, Provider *providerList);

void filterProvider(int numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList, string name, string phoneNumber, string minDate, string maxDate, string address);
// quản lý loại vật tư
void manageCategories();
void controlCategoryList(int &numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList);
void addCategory(int &numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList);
void updateCategoryInfor(int numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList);
void deleteCategory(int &numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList);
void sortCategoryList(int numberOfRecords, Category *categoryList);
void displayCategoryList(int numberOfRecords, Category *categoryList);

void searchCategory(int &numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList);

void filterCategory(int numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList, string name);
// quản lý đơn hàng
void manageOrders();
void controlOrderList(int numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList,int flag);
void displayOrderList(int numberOfRecords, Order *orderList);
void addOrder(int &numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList);
void deleteOrderHistory(int numberOfRecords, Order *orderList);
void viewOrderDetail(int numberOfOrderDetail, Order *orderList);
void cancelOrder(int numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList);
void searchOrder(int &numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList);
void filterOrder(int numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList, string minDate, string maxDate, string address, string status, unsigned long minTotalPrice, unsigned long maxTotalPrice);
void ordersStatistics(int numberOfRecords, Order *oderList);
// cap nhat trang thai giao hang
void updateOrder(int numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList);
int main()
{
    // in chào 
    printHello();
    controlMain();
}
// quản lý NSX
void manageProviders()
{

    // lấy  danh sách
    Provider *providerList = getProviderList();
    // tính số hàng
    int numberOfRecords = getNumberOfRecords(providerList, maxProviderRecords);

    Provider *virtualProviderList = getProviderList();
    // tính số hàng
    int numberOfVirtualRecords = numberOfRecords;
    /*....*/
    controlProviderList(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
}
void manageMaterial()
{
    // lấy  danh sách
    Material *materialList = getMaterialList();
    // tính số hàng
    int numberOfRecords = getNumberOfRecords(materialList, maxMaterialRecords);

    // * clone ra mot ds ao uong tu
    Material *virtualMaterialList = getMaterialList();
    // tính số hàng
    int numberOfVirtualRecords = numberOfRecords;

    controlMaterialList(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
}
// quản lý LVT
void manageCategories()
{
    // lấy  danh sách
    Category *categoryList = getCategoryList();
    // tính số hàng
    int numberOfRecords = getNumberOfRecords(categoryList, maxCategoryRecords);

    // * Clone ra 1 ds ao
    Category *virtualCategoryList = getCategoryList();
    // tính số hàng
    int numberOfVirtualRecords = numberOfRecords;

    /*....*/
    controlCategoryList(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
}

// quản lý DH
void manageOrders()
{

    // lấy  danh sách
    Order *orderList = getOrderList();
    // tính số hàng
    int numberOfRecords = getNumberOfRecords(orderList, maxOrderRecords);
    /*....*/

    // * Clone ra 1 ds ao
    // tạo ds ảo bằng ds thực, nhớ dùng getOrderList(), gán = thì sẽ ảnh hưởng ds thực
    Order *virtualOrderList=getOrderList();

    int numberOfVirtualRecords = numberOfRecords;
    // lấy ngày hiện tại
    string thisDate = getCurrentTime("date");
    // đổi tháng thành tháng trươcs
    int lastMonth = stoi(thisDate.substr(3, 5)) - 1;

    string dateOfLastMonth = thisDate;
    // th1 : thang truoc lon hon 10
    if (lastMonth >= 10)
    // sử dụng to_string sau đó dùng [0] để convert từ int sang char
        dateOfLastMonth[4] = (to_string(lastMonth - 10))[0];
    else
    { // truong hop thang nay la thang 1
        // ...

            // truong hop thang nay khac thang 1
            dateOfLastMonth[3] = '0';
        dateOfLastMonth[4] = to_string(lastMonth)[0];
    }
    
    filterOrder(numberOfRecords, orderList, numberOfVirtualRecords, virtualOrderList, dateOfLastMonth, thisDate, "\0", "\0", 0, 4000000000);
    // tính số hàng

    controlOrderList(numberOfRecords, orderList, numberOfVirtualRecords, virtualOrderList,1);
}

void displayMaterialList(int numberOfRecords, Material *materialList)
{
    printHyphen(lineWidth);
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
    printHyphen(lineWidth);
}
void displayProviderList(int numberOfRecords, Provider *providerList)
{
    printHyphen(lineWidth);
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
    printHyphen(lineWidth);
}
void displayCategoryList(int numberOfRecords, Category *categoryList)
{
    printHyphen(lineWidth);
    // in tiêu đề
    cout << setw(20) << left << "Ma LVT";
    cout << "Ten LVT" << endl
         << endl;
    for (int i = 0; i < numberOfRecords; i++)
    {
        cout << setw(20) << left << categoryList[i].getId();
        cout << categoryList[i].getName() << endl;
    }
    printHyphen(lineWidth);
}
void displayOrderList(int numberOfRecords, Order *orderList)
{
    printHyphen(lineWidth);
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
    printHyphen(lineWidth);
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
    printHyphen(lineWidth);
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
    printHyphen(lineWidth * 3 / 4);
    unsigned long discount = getDiscount(totalWithoutDiscount);
    cout << "Tong tien (chua giam gia) : " << totalWithoutDiscount << endl;
    cout << "Giam gia ( " << discount * 100 / totalWithoutDiscount << "% ) : " << discount << endl;
    cout << "Thanh tien : " << totalWithoutDiscount - discount << endl;
    printHyphen(lineWidth);
    delete[] materialList;
    delete[] orderDetailList;
}
void addMaterial(int &numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList)
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

        virtualMaterialList[numberOfVirtualRecords++] = newMaterial;
        // tin nhan thong bao
        cout << "Da them VT thanh cong !" << endl;
        cout << "Ban co muon tiep tuc them VT ?  (co : 1 / khong : 0) : ";
        int controlNumber;
        cin >> controlNumber;
        if (controlNumber == 0)
        {

            controlMaterialList(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
        }
        else
            addMaterial(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
    }
    else
        controlMaterialList(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
}
void addProvider(int &numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList)
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
        virtualProviderList[numberOfVirtualRecords++] = newProvider;

        // tin nhan thong bao
        cout << endl
             << "Da them NSX thanh cong !" << endl;
        cout << "Ban co muon tiep tuc them NSX ?  (co : 1 / khong : 0) : ";
        int controlNumber;
        cin >> controlNumber;
        if (controlNumber == 0)
        {

            controlProviderList(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
        }
        else
            addProvider(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
    }
    else
    {
        controlProviderList(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
    }
}
void addCategory(int &numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList)
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
        virtualCategoryList[numberOfVirtualRecords++] = newCategory;

        // tin nhan thong bao
        cout << endl
             << "Da them LVT thanh cong !" << endl;
        cout << "Ban co muon tiep tuc them LVT ?  (co : 1 / khong : 0) : ";
        int controlNumber;
        cin >> controlNumber;
        if (controlNumber == 0)
        {

            controlCategoryList(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
        }
        else
            addCategory(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
    }
    else
        controlCategoryList(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
}
void addOrder(int &numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList)
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
    OrderDetail *orderDetailList = getOrderDetailList();
    int numberOfODRecords=getNumberOfRecords(orderDetailList,maxOrderDetailRecords);
    
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
            cout << endl;
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
        cout << "Nhap dia chi giao hang : ";

        getline(cin, shippingAddress);
        // tao trang thai mac dinh
        string shippingStatus = "Chua xu ly";
        // in list detail vo CTDH
        Order newOrder(id, totalPrice, time, shippingAddress, shippingStatus);
        orderList[numberOfRecords++] = newOrder;
        virtualOrderList[numberOfVirtualRecords++] = newOrder;

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
                controlOrderList(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList,0);

        }
        else
            addOrder(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList);
    }
    else
            controlOrderList(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList,0);

}
void updateProviderInfor(int numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList)
{

    printBox("CAP NHAT NSX");
    int id;
    // chọn mã vật tư
    cout << "Chon ma NSX : ";
    bool isValid = false;
    while (!isValid)
    {
        cin >> id;
        int i, j;
        for (j = 0; j < numberOfVirtualRecords; j++)
        {
            if (virtualProviderList[j].getId() == id)
                break;
        }
        // vật tư đã có
        if (j < numberOfVirtualRecords)
        { // lấy tên của NSX cần thay đổi
            for (i = 0; i < numberOfRecords; i++)
            {
                if (providerList[i].getId() == id)
                    break;
            }
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
            {
                providerList[i].setName(name);
                virtualProviderList[j].setName(name);
            }
            if (phoneNumber != "0")
            {
                providerList[i].setPhoneNumber(phoneNumber);
                virtualProviderList[j].setPhoneNumber(phoneNumber);
            }
            if (address != "0")
            {
                providerList[i].setAddress(address);
                virtualProviderList[j].setAddress(address);
            }
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

        controlProviderList(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
    }
    else
        updateProviderInfor(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
}
void updateMaterialInformation(int numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList)
{
    printBox("CAP NHAT THONG TIN VAT TU");
    int id;
    // chọn mã vật tư
    cout << "Chon ma VT : ";
    bool isValid = false;
    while (!isValid)
    {
        cin >> id;
        int j;
        for (j = 0; j < numberOfVirtualRecords; j++)
        {
            if (virtualMaterialList[j].getId() == id)
                break;
        }
        // vật tư đã có
        if (j < numberOfVirtualRecords)
        {
            // * Tim vat tu tuong tu trong mang chinhs
            int i = 0;
            for (; i < numberOfRecords; i++)
            {
                if (materialList[i].getId() == id)
                    break;
            }
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
            {
                materialList[i].setName(name);
                virtualMaterialList[j].setName(name);
            }
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
                        virtualMaterialList[j].setCategoryName(categoryName);
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
                        virtualMaterialList[j].setProviderName(providerName);
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
            {

                materialList[i].setQuantity(materialList[i].getQuantity() + addNumber);
                virtualMaterialList[j].setQuantity(materialList[i].getQuantity());
            }
            if (newPrice != 0)
            {
                materialList[i].setUnitPrice(newPrice);
                virtualMaterialList[j].setUnitPrice(newPrice);
            }
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

        controlMaterialList(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
    }
    else
        updateMaterialInformation(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
}

void updateCategoryInfor(int numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList)
{
    printBox("CAP NHAT LVT");
    int id;
    // chọn mã loại vật tư
    cout << "Chon ma LVT : ";
    bool isValid = false;
    while (!isValid)
    {
        cin >> id;
        int i, j;
        for (j = 0; j < numberOfVirtualRecords; j++)
        {
            if (virtualCategoryList[j].getId() == id)
                break;
        }
        // vật tư đã có
        if (j < numberOfVirtualRecords)

        {
            for (i = 0; i < numberOfRecords; i++)
            {
                if (categoryList[i].getId() == id)
                    break;
            }
            // lấy tên của LVT cần thay đổi
            string categoryNameToFind = categoryList[i].getName();

            // tên
            string name;
            // dùng để tránh lỗi do cin phía trước
            cin.ignore();
            cout << "Nhap ten moi : ";
            getline(cin, name);
            categoryList[i].setName(name);
            virtualCategoryList[j].setName(name);

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

        controlCategoryList(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
    }
    else
        updateCategoryInfor(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
}
void updateOrder(int numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList)
{
    // chon dh
    int id;
    printBox("CAP NHAT DON HANG");
    cout << "Nhap ma don hang : ";
    bool isValid = false;
    while (!isValid)
    {
        cin >> id;
        int i,j;
        for (j = 0; j < numberOfVirtualRecords; j++)
        {
            if (virtualOrderList[j].getId() == id)
                break;
        }
        // ton tai don hang
        if (j < numberOfVirtualRecords)
        {
            for (i = 0; i < numberOfRecords; i++)
            {
                if (orderList[i].getId() == id)
                    break;
            }
            // truong hop 1 : don hang da giao
            if (virtualOrderList[j].getShippingStatus() == "Da giao")
            {
                cout << "Co le ban nhap nham ! Don hang nay da duoc giao roi , vui long nhap lai : ";
            }
            else if (virtualOrderList[j].getShippingStatus() == "Da huy")
            {
                cout << "Co le ban nhap nham ! Don hang nay da bi huy , vui long nhap lai : ";
            }
            else if (virtualOrderList[j].getShippingStatus() == "Da van don")
            {
                string shippingStatus;
                shippingStatus = "Da giao";
                // cap nhat order
                orderList[i].setShippingStatus(shippingStatus);
                virtualOrderList[j].setShippingStatus(shippingStatus);
                // thoat vong lap
                isValid = true;
            }
            else if (virtualOrderList[j].getShippingStatus() == "Chua xu ly")
            {
                string shippingStatus;
                shippingStatus = "Da van don";
                // cap nhat order
                orderList[i].setShippingStatus(shippingStatus);
                virtualOrderList[j].setShippingStatus(shippingStatus);
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

            controlOrderList(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList,0);

    }
    else
        updateOrder(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList);
}
void deleteCategory(int &numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList)
{
    // nhap ma loai VT
    int id;
    bool isValid = false;
    cout << "Nhap ma loai VT can xoa : ";
    // vong lap kiem tra loai VT co ton tai hay k
    while (!isValid)
    {
        cin >> id;
        int i, j;
        for (j = 0; j < numberOfVirtualRecords; j++)
        {
            if (virtualCategoryList[j].getId() == id)
                break;
        }
        if (j == numberOfVirtualRecords)
        {
            cout << "Khong ton tai loai VT ban vua nhap ! Vui long nhap lai : ";
        }
        else
        {
            for (i = 0; i < numberOfRecords; i++)
            {
                if (categoryList[i].getId() == id)
                    break;
            }
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
            for (int z = j; z < numberOfVirtualRecords - 1; z++)
            {

                virtualCategoryList[z] = virtualCategoryList[z + 1];
            }
            isValid = true;
            numberOfRecords--;
            numberOfVirtualRecords--;
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

        controlCategoryList(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
    }
    else
        deleteCategory(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
}

void deleteProvider(int &numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList)
{
    // nhap ma NSX
    int id, i, j;
    bool isValid = false;
    cout << "Nhap ma NSX can xoa : ";
    // vong lap kiem tra NSX co ton tai hay k
    while (!isValid)
    {
        cin >> id;
        for (j = 0; j < numberOfVirtualRecords; j++)
        {
            if (virtualProviderList[j].getId() == id)
                break;
        }

        if (j == numberOfVirtualRecords)
        {
            cout << "Khong ton tai NSX ban vua nhap ! Vui long nhap lai : ";
        }
        else
        {
            for (i = 0; i < numberOfRecords; i++)
            {
                if (providerList[i].getId() == id)
                    break;
            }
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
            for (int z = j; z < numberOfVirtualRecords - 1; z++)
            {

                virtualProviderList[z] = virtualProviderList[z + 1];
            }
            isValid = true;
            numberOfRecords--;
            numberOfVirtualRecords--;
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

        controlProviderList(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
    }
    else
        deleteProvider(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
}
void deleteMaterial(int &numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList)
{
    // nhap ma VT
    int id, i, j;
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
        for (j = 0; j < numberOfVirtualRecords; j++)
        {
            if (virtualMaterialList[j].getId() == id)
                break;
        }

        if (j == numberOfVirtualRecords)
        {
            cout << "Khong ton tai VT ban vua nhap ! Vui long nhap lai : ";
        }
        // ton tai
        else
        {
            for (i = 0; i < numberOfRecords; i++)
            {
                if (materialList[i].getId() == id)
                    break;
            }
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

            // xoa element trong mang
            for (int j = i; j < numberOfRecords - 1; j++)
            {
                materialList[j] = materialList[j + 1];
            }

            for (int z = j; z < numberOfVirtualRecords - 1; z++)
            {
                virtualMaterialList[z] = virtualMaterialList[z + 1];
            }
            // dung de thoat vong lap
            isValid = true;
            // giam so luong record
            numberOfRecords--;
            numberOfVirtualRecords--;
            cout << endl
                 << "Da xoa VT thanh cong !" << endl;
        }
    }

    cout << "Ban co muon tiep tuc xoa VT ?  (co : 1 / khong : 0) : ";
    int controlNumber;

    cin >> controlNumber;

    if (controlNumber == 0)
    { // update file

        controlMaterialList(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
    }
    else
        deleteMaterial(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
}
void searchMaterial(int &numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList)
{
    // xoa list cu

    delete[] virtualMaterialList;
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
    virtualMaterialList = new Material[maxMaterialRecords];
    numberOfVirtualRecords = maxMaterialRecords;

    filterMaterial(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList,
                   name, categoryName, providerName,
                   quantity,
                   minUnitPrice, maxUnitPrice);
    // * III. Tra ve quan ly
    controlMaterialList(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
}

void searchProvider(int &numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList)
{
    // xoa list cu

    delete[] virtualProviderList;
    int id;
    string name, phoneNumber, minDate, maxDate, address;
    cout << "Nhap 0 neu ban muon bo qua!" << endl;
    // * I. Lấy input
    cin.ignore();
    cout << "Nhap ten: ";
    getline(cin, name);
    if (name == "0")
        name = "\0";

    cout << "Nhap sdt: ";
    getline(cin, phoneNumber);
    if (phoneNumber == "0")
        phoneNumber = "\0";

    cout << "Nhap ngay hop tac( dd/mm/yyyy):" << endl;
    cout << "\t"
         << setw(15) << right << "tu: ";
    cin >> minDate;
    if (minDate == "0")
        minDate = "01/01/1600";
    cout << "\t"
         << setw(15) << right << "den: ";
    cin >> maxDate;
    if (maxDate == "0")
        maxDate = "31/12/9999";
    cin.ignore();
    cout << "Nhap dia chi: ";
    getline(cin, address);
    if (address == "0")
        address = "\0";
    // * II. Tạo ds mới với những tiêu chí đã lọc ( numberOfRecords đã tự động thay đổi)
    virtualProviderList = new Provider[maxProviderRecords];
    numberOfVirtualRecords = maxProviderRecords;

    filterProvider(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList,
                   name, phoneNumber, minDate, maxDate, address);
    // * III. Tra ve quan ly
    controlProviderList(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
}
void searchCategory(int &numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList)
{
    // xoa list cu

    delete[] virtualCategoryList;
    int id;
    string name;

    // * I. Lấy input
    cout << "Nhap 0 neu muon bo qua!" << endl;
    cin.ignore();
    cout << "Nhap ten : ";
    getline(cin, name);
    if (name == "0")
        name = "\0";
    // * II. Tạo ds mới với những tiêu chí đã lọc ( numberOfRecords đã tự động thay đổi)
    virtualCategoryList = new Category[maxCategoryRecords];
    numberOfVirtualRecords = maxCategoryRecords;

    filterCategory(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList,
                   name);
    // * III. Tra ve quan ly
    controlCategoryList(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
}
void searchOrder(int &numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList)
{
    // xoa list cu

    delete[] virtualOrderList;
    string minDate;
    string maxDate;
    string address;
    string status;
    unsigned long minTotalPrice;
    unsigned long maxTotalPrice;

    // * I. Lấy input
    cout
        << "Nhap 0 neu muon bo qua!" << endl;
    cin.ignore();
    cout << "Nhap thoi gian (dd/mm/yyyy): " << endl;
    cout << "\t"
         << "Tu ngay: ";
    cin >> minDate;
    if (minDate == "0")
        minDate = "01/01/1111";
    cout << "\t"
         << "Den ngay: ";
    cin >> maxDate;
    if (maxDate == "0")
        maxDate = "31/12/9999";
    cin.ignore();
    cout << "Nhap dia chi: ";
    getline(cin, address);
    if (address == "0")
        address = "\0";cout << "Nhap trang thai: ";
    getline(cin, status);
    if (status == "0")
        status = "\0";
    cout << "Nhap thanh tien:" << endl;
    cout << "\t"
         << "Nho nhat: ";
    cin >> minTotalPrice;
    cout << "\t"
         << "Lon nhat: ";
    cin >> maxTotalPrice;

    if (maxTotalPrice==0)
        maxTotalPrice = 4000000000;
    // * II. Tạo ds mới với những tiêu chí đã lọc ( numberOfRecords đã tự động thay đổi)
    virtualOrderList = new Order[maxOrderRecords];
    numberOfVirtualRecords = maxOrderRecords;

    filterOrder(numberOfRecords, orderList, numberOfVirtualRecords, virtualOrderList,minDate,maxDate,address,status,minTotalPrice,maxTotalPrice);
    // * III. Tra ve quan ly
    controlOrderList(numberOfRecords, orderList, numberOfVirtualRecords, virtualOrderList,0);
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
        if ((a == 't') || (a == 'T'))
            sortById(materialList, numberOfRecords, ascending);
        else
            sortById(materialList, numberOfRecords, descending);
        break;

    case 2:
        if ((a == 't') || (a == 'T'))
            sortByName(materialList, numberOfRecords, ascending);
        else
            sortByName(materialList, numberOfRecords, descending);
        break;

    case 3:
        if ((a == 't') || (a == 'T'))
            sortByCateOrProName("categoryName", materialList, numberOfRecords, ascending);
        else
            sortByCateOrProName("categoryName", materialList, numberOfRecords, descending);
        break;

    case 4:
        if ((a == 't') || (a == 'T'))
            sortByCateOrProName("providerName", materialList, numberOfRecords, ascending);
        else
            sortByCateOrProName("providerName", materialList, numberOfRecords, descending);
        break;

    case 5:
        if ((a == 't') || (a == 'T'))
            sortByQuantityOrUnitPrice("quantity", materialList, numberOfRecords, ascending);
        else
            sortByQuantityOrUnitPrice("quantity", materialList, numberOfRecords, descending);
        break;

    case 6:
        if ((a == 't') || (a == 'T'))
            sortByQuantityOrUnitPrice("unitPrice", materialList, numberOfRecords, ascending);
        else
            sortByQuantityOrUnitPrice("unitPrice", materialList, numberOfRecords, descending);
        break;
    }
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
        if ((a == 't') || (a == 'T'))
            sortById(providerList, numberOfRecords, ascending);
        else
            sortById(providerList, numberOfRecords, descending);
        break;

    case 2:
        if ((a == 't') || (a == 'T'))
            sortByName(providerList, numberOfRecords, ascending);
        else
            sortByName(providerList, numberOfRecords, descending);
        break;

    case 3:
        if ((a == 't') || (a == 'T'))
            sortByDate(providerList, numberOfRecords, ascendingDate);
        else
            sortByDate(providerList, numberOfRecords, descendingDate);
        break;
    }
}
void sortCategoryList(int numberOfRecords, Category *categoryList)
{

    cout << "Ban muon sap xep theo tieu chi nao ? " << endl
         << endl;
    cout << setw(20) << "1. Ma loai VT"
         << "2. Ten loai VT" << endl
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
            sortById(categoryList, numberOfRecords, ascending);
        else
            sortById(categoryList, numberOfRecords, descending);
        break;

    case 2:
        if ((a == 't') || (a == 'T'))
            sortByName(categoryList, numberOfRecords, ascending);
        else
            sortByName(categoryList, numberOfRecords, descending);
        break;
    }
}
void ordersStatistics(int numberOfOrderRecords, Order *orderList)

{
    // ... thống kê theo tháng
    printBox("THONG KE DOANH THU");

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
        if ((status != "Da huy") && (status != "Chua xu ly"))
        {

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
    double materialPercentage[numberOfMaterialRecords + 1];
    for (int i = 1; i <= numberOfMaterialRecords; i++)
    {
        materialPercentage[i] = 0;
    }

    // * Luu ten loai VT
    string categoryNames[maxCategoryRecords];
    int categoryCount = 0;
    // * Luu phan tram
    double categoryPercentage[maxCategoryRecords];
    for (int i = 0; i < maxCategoryRecords; i++)
    {
        categoryPercentage[i] = 0;
    }
    // * II. 3 Luu gia tri % cua tung vat va loai VT vao mang

    OrderDetail temp;
    for (int i = 0; i < numberOfODRecords; i++)
    {

        temp = orderDetailList[i];

        // * phai thoa dkien la order phai dc ban
        if (soldOrders[temp.getId()])
        {
            // * 1. Tinh tổng giá của từng ..
            int materialId = temp.getMaterialId();
            Material material = getMaterialById(materialId, materialList);
            unsigned long price = temp.getQuantity() * material.getUnitPrice();

            double percentage = (double)price / originalToTalPrice * 100;
            materialPercentage[materialId] += percentage;

            string categoryName = material.getCategoryName();
            int j = 0;
            // * th1 : neu ten vat tu da ton tai
            for (; j < categoryCount; j++)
            {
                if (categoryNames[j] == categoryName)
                {
                    categoryPercentage[j] += percentage;
                    break;
                }
            }
            // * th2: ten vat tu chua ton tai
            if (j == categoryCount)
            {
                categoryNames[j] = categoryName;
                categoryPercentage[j] = percentage;
                categoryCount++;
            }
        }
    }
    // * III. Sap xep vat tu theo %
    // * II.1 Tao mang luu thu tu

    int rankMaterial[numberOfMaterialRecords + 1];
    for (int i = 1; i <= numberOfMaterialRecords; i++)
    {
        rankMaterial[i] = i;
    }

    // * II.2 Sap xep gia tri cua rank..[i] theo % cua rank[i]

    sortByPercentage(rankMaterial, materialPercentage, numberOfMaterialRecords + 1, descending);

    // * III. In ra bang xep hang theo tieu chi vat tu

    printBox("THONG KE THEO VAT TU");

    printHyphen(lineWidth * 10 / 13);
    cout << setw(18) << "" << setw(10) << "STT" << setw(20) << "Ten vat tu" << setw(25) << ("Ten loai VT") << setw(30) << "Ten NSX"
         << "%" << endl
         << endl;
    int stt = 1;
    for (int i = 1; i < numberOfMaterialRecords + 1; i++)
    {
        int materialId = rankMaterial[i];
        double percentage = materialPercentage[materialId];
        if (percentage != 0)
        {
            Material material = getMaterialById(materialId, materialList);
            cout << setw(18) << "";
            cout << setw(10) << stt++;
            cout << setw(20) << material.getName();
            cout << setw(25) << material.getCategoryName();

            cout << setw(30) << material.getProviderName();
            cout << fixed << setprecision(2) << percentage;
            cout << endl;
        }
    }
    printHyphen(lineWidth * 10 / 13);
    // * IIII.4 Sap xep theo loai VT
    // * IIII.4.1 Tao cac mang luu du lieu

    // * Luu  thu tu cua index
    int categoryOrder[categoryCount];
    for (int i = 0; i < categoryCount; i++)
    {
        categoryOrder[i] = i;
    }
    sortCategoryByPercentage(categoryOrder, categoryPercentage, categoryCount, descending);

    printBox("THONG KE THEO LOAI VAT TU");

    printHyphen(lineWidth * 5 / 13);
    cout << setw(45) << "" << setw(10) << "STT" << setw(25) << "Ten loai VT"
         << "%" << endl
         << endl;
    for (int i = 0; i < categoryCount; i++)
    {
        int index = categoryOrder[i];
        cout << setw(45) << "";
        cout << setw(10) << (i + 1);
        cout << setw(25) << categoryNames[index];
        cout << categoryPercentage[index];
        cout << endl;        
    }
    printHyphen(lineWidth * 5 / 13);
    cout << "An phim bat ky de tiep tuc..." << endl;
    getch();
}
void controlMaterialList(int numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList)
{
    printBox("QUAN LY VAT TU");
    displayMaterialList(numberOfVirtualRecords, virtualMaterialList);

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
            delete[] virtualMaterialList;
            controlMain();
            isValid = true;
            break;
        case 1:
            addMaterial(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
            isValid = true;
            break;
        case 2:
            updateMaterialInformation(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
            isValid = true;
            break;
        case 3:

            deleteMaterial(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
            isValid = true;
            break;
        case 4:
            searchMaterial(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
            isValid = true;
            break;
        case 5:
            sortMaterialList(numberOfVirtualRecords, virtualMaterialList);
            controlMaterialList(numberOfRecords, materialList, numberOfVirtualRecords, virtualMaterialList);
            isValid = true;
            break;
        default:
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void controlProviderList(int &numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList)
{

    printBox("QUAN LY NSX");

    displayProviderList(numberOfVirtualRecords, virtualProviderList);

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
            delete[] virtualProviderList;
            delete[] providerList;
            controlMain();
            isValid = true;
            break;
        case 1:
            addProvider(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
            isValid = true;
            break;
        case 2:
            updateProviderInfor(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
            isValid = true;
            break;
        case 3:
            deleteProvider(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
            isValid = true;
            break;
        case 4:
            searchProvider(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
            isValid = true;
            break;
        case 5:
            sortProviderList(numberOfVirtualRecords, virtualProviderList);
            controlProviderList(numberOfRecords, providerList, numberOfVirtualRecords, virtualProviderList);
            isValid = true;
            break;
        default:
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void controlCategoryList(int &numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList)

{
    printBox("QUAN LY LOAI VT");
    displayCategoryList(numberOfVirtualRecords, virtualCategoryList);

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
        cin >> controlNumber;
        switch (controlNumber)
        {
        case 0:
            updateLVT(numberOfRecords, categoryList);
            delete[] virtualCategoryList;
            delete[] categoryList;
            controlMain();
            isValid = true;
            break;
        case 1:
            addCategory(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
            isValid = true;
            break;
        case 2:
            updateCategoryInfor(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
            isValid = true;
            break;
        case 3:
            deleteCategory(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
            isValid = true;
            break;
        case 4:
            searchCategory(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
            isValid = true;
            break;
        case 5:
            sortCategoryList(numberOfVirtualRecords, virtualCategoryList);
            controlCategoryList(numberOfRecords, categoryList, numberOfVirtualRecords, virtualCategoryList);
            isValid = true;
            break;
        default:
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void controlOrderList(int numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList,int flag)
{
    printBox("QUAN LY DON HANG");
    if (flag!=0)
        printSmallBox("30 NGAY GAN NHAT");
    displayOrderList(numberOfVirtualRecords, virtualOrderList);

    // chọn chức năng

    cout << setw(40) << left << "0. Quay lai";
    cout << setw(30) << left << "1. Them don hang";
    cout << "2. Xem chi tiet don hang" << endl;
    cout << setw(40) << left << "3. Cap nhat trang thai giao hang";
    cout << setw(30) << left << "4. Huy don hang";
    cout <<  "5. Tim kiem don hang"<<endl;

    cout << setw(40)<<"6. Thong ke doanh thu";
    cout << endl;
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
            delete[] virtualOrderList;
            isValid = true;
            controlMain();
            break;
        case 1:
            addOrder(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList);
            isValid = true;
            break;

        case 2:
            viewOrderDetail(numberOfVirtualRecords, virtualOrderList);
            cout << "Nhan phim bat ky de quay lai ! " << endl;
            getch();
                controlOrderList(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList,0);

            break;
        case 3:
            updateOrder(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList);
            isValid = true;
            break;
        case 4:

            cancelOrder(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList);
            isValid = true;
            break;
        case 5:
            searchOrder(numberOfRecords,orderList,numberOfVirtualRecords,virtualOrderList);
            isValid = true;
            break;
        case 6:
            ordersStatistics(numberOfRecords, orderList);
            controlOrderList(numberOfRecords, orderList, numberOfVirtualRecords, virtualOrderList,0);
            isValid = true;
            break;
        default:
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void filterMaterial(int numberOfRecords, Material *materialList, int &numberOfVirtualRecords, Material *virtualMaterialList,
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

        if ((toLower(material.getName()).find(toLower(name)) != string::npos) &&
            ((toLower(material.getCategoryName()).find(toLower(categoryName)) != string::npos)) &&
            (toLower(material.getProviderName()).find(toLower(providerName)) != string::npos) &&
            (material.getQuantity() >= quantity) &&
            (material.getUnitPrice() >= minUnitPrice) &&
            (material.getUnitPrice() <= maxUnitPrice))
        {
            virtualMaterialList[count] = material;
            count++;
        }
    }

    // * II. Tra  ve ds moi
    numberOfVirtualRecords = count;
}
void filterProvider(int numberOfRecords, Provider *providerList, int &numberOfVirtualRecords, Provider *virtualProviderList, string name, string phoneNumber, string minDate, string maxDate, string address)
{
    int count = 0;
    Provider provider;
    // * I. LOC
    for (int i = 0; i < numberOfRecords; i++)
    {
        provider = providerList[i];

        if ((toLower(provider.getName()).find(toLower(name)) != string::npos) &&
            ((toLower(provider.getPhoneNumber()).find(toLower(phoneNumber)) != string::npos)) &&
            (toLower(provider.getAddress()).find(toLower(address)) != string::npos) &&
            (ascendingDate(provider.getDate(), minDate)) &&
            (ascendingDate(maxDate, provider.getDate())))
        {
            virtualProviderList[count] = provider;
            count++;
        }
    }

    // * II. Tra  ve ds moi
    numberOfVirtualRecords = count;
}
void filterCategory(int numberOfRecords, Category *categoryList, int &numberOfVirtualRecords, Category *virtualCategoryList, string name)
{
    int count = 0;
    Category category;
    // * I. LOC
    for (int i = 0; i < numberOfRecords; i++)
    {
        category = categoryList[i];

        if (toLower(category.getName()).find(toLower(name)) != string::npos)
        {
            virtualCategoryList[count] = category;
            count++;
        }
    }

    // * II. Tra  ve ds moi
    numberOfVirtualRecords = count;
}
void filterOrder(int numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList, string minDate, string maxDate, string address, string status, unsigned long minTotalPrice, unsigned long maxTotalPrice){
   
    int count = 0;
    Order order;
    // * I. LOC
    for (int i = 0; i < numberOfRecords; i++)
    {
        order = orderList[i];
        // chuyển đổi orderTime thành Order Date
        string orderDate=order.getTime();
        orderDate = orderDate.substr(6, 15);
        unsigned long totalPrice = order.getTotalPrice();
        if ((toLower(order.getShippingAddress()).find(toLower(address)) != string::npos) &&
            (toLower(order.getShippingStatus()).find(toLower(status)) != string::npos) && 
            (ascendingDate(orderDate, minDate)) &&
            (ascendingDate(maxDate, orderDate))&&
            (minTotalPrice<=totalPrice)&&
            (maxTotalPrice>=totalPrice)
        )
        {
            virtualOrderList[count] = order;
            count++;
        }
    }

    // * II. Tra  ve ds moi
    numberOfVirtualRecords = count;
}
    // ...
void cancelOrder(int numberOfRecords, Order *orderList, int &numberOfVirtualRecords, Order *virtualOrderList)
{
    int orderId;
    printBox("HUY DON HANG");
    cout << "Nhap ma don hang : ";
    bool isCancel = false;
    while (true)
    {
        int i = 0,j=0;
        cin >> orderId;
        for (; j < numberOfVirtualRecords; j++)
        {
            if (virtualOrderList[j].getId() == orderId)
                break;
        }
        if (j < numberOfVirtualRecords)
        {
            for (; i < numberOfRecords; i++)
            {
                if (orderList[i].getId() == orderId)
                    break;
            }
            if (orderList[i].getShippingStatus() == "Chua xu ly")
            {
                Material *materialList = getMaterialList();
                int numberOfMaterialRecords = getNumberOfRecords(materialList, maxMaterialRecords);

                Material *deletedMaterialList = getDeletedMaterialList();
                int numberOfDeletedMaterialRecords = getNumberOfRecords(deletedMaterialList, maxMaterialRecords);

                isCancel = false;
                orderList[i].setShippingStatus("Da huy");
                virtualOrderList[j].setShippingStatus("Da huy");
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
            controlOrderList(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList,0);

    else
    {
        cout << endl
             << "Da huy Don Hang thanh cong !" << endl;
        cout << "Ban co muon tiep tuc huy Don Hang ?  (co : 1 / khong : 0) : ";
        int controlNumber;

        cin >> controlNumber;

        if (controlNumber == 0)
        { // update file

                controlOrderList(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList,0);

        }
        else
            cancelOrder(numberOfRecords, orderList,numberOfVirtualRecords,virtualOrderList);
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
    printHyphen(40);
    cout << endl;
}
void printSmallBox(string title)
{
    int length = title.length();
    int indent = (lineWidth - length) / 2;
    for (int i = 0; i < indent; i++)
    {
        cout << " ";
    }
    cout << title << endl;
    cout << endl;
}
void printUnderscore(int n)
{
    int indent = (lineWidth - n) / 2;
    for (int i = 0; i < indent; i++)
        cout << " ";
    for (int i = 0; i < n; i++)
    {
        cout << "_";
    }
    cout << endl;
}
void printHyphen(int n)
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
    printHyphen(lineWidth);
    cout << "0. Thoat chuong trinh"
         << "\t";
    cout << setw(20) << left << "1. Quan ly VT"

        ;
    cout << "2. Quan ly nha san xuat"
         << "\t";
    cout << "3. Quan ly loai VT"
         << "\t";
    cout << "4. Quan ly hoa don " << endl;
    printHyphen(lineWidth);
    cout << endl;
}
void printHello()
{
    printUnderscore(lineWidth); cout << endl;
    cout << setw(35) << ""; cout << "CHAO MUNG THAY CO DEN VOI DO AN LAP TRINH CO SO LAP TRINH PBL2 " << endl;
    cout << setw(35) << ""; cout << "                  DE TAI : QUAN LY VAT TU                      " << endl;
    cout << setw(35) << ""; cout << "                   SINH VIEN THUC HIEN                         " << endl;
    cout << setw(35) << ""; cout << "                    TRUONG QUANG CHU                           " << endl;
    cout << setw(35) << ""; cout << "                    NGUYEN VAN VUONG                           " << endl;
    printUnderscore(lineWidth); cout << endl;
    cout << setw(35) << ""; cout << "                 HE THONG QUAN LY VAT TU                       " << endl;
}
void printGoodBye()
{
    printUnderscore(lineWidth); cout << endl;
    cout << setw(35) << ""; cout << "                   CHUONG TRINH KET THUC!                      " << endl;
    cout << setw(35) << ""; cout << "            CAM ON THAY CO VA CAC BAN DA THEO DOI              " << endl;
    printUnderscore(lineWidth);
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
        printGoodBye();
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