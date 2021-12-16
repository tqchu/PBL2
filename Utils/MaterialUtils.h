#ifndef MATERIALUTILS_H
#define MATERIALUTILS_H
#include "BaseUtils.h"
class MaterialUtils : public BaseUtils<Material>
{
private:
    // inherited io,list,virtualList

    // Truy cập ds đã xoá
    DeletedMaterialIO dio;
    ArrayList<Material> deletedList;

    // Lấy list NSX
    ManufacturerIO pIO;
    ArrayList<Manufacturer> pList;

    // Lấy list LVT
    CategoryIO cIO;
    ArrayList<Category> cList;

public:
    // inherit manage,display
    MaterialUtils();
    virtual void control();
    virtual void add();
    virtual void update();
    virtual void sort();
    virtual void search();
    void viewManufacturerDetail();
    void remove();
    void filter(string name, string categoryName, string manufacturerName, int quantity, unsigned long minUnitPrice, unsigned long maxUnitPrice);
};
MaterialUtils::MaterialUtils()
{
    // Khởi tạo title
    title += "VAT TU";

    // Khởi tạo io và dio
    io = new MaterialIO();

    // Khởi tạo list và gán virtualList = list
    list = io->getList();

    virtualList = list;

    // Lấy DS Vật tư đã xoá
    deletedList = dio.getList();

    // Lấy DS Category
    cList = cIO.getList();
    // Lấy DS NSX
    pList = pIO.getList();
}

void MaterialUtils::control()
{
    cout << "  ";
    cout << setw(20) << left << "0. Quay lai";
    cout << setw(20) << left << "1. Them VT";
    cout << setw(30) << left << "2. Cap nhat thong tin VT";
    cout << setw(25) << left << "3. Xem chi tiet NSX" << endl;
    cout << "  ";
    cout << setw(20) << left << "4. Xoa VT";
    cout << setw(20) << left << "5. Tim kiem";
    cout << setw(30) << left << "6. Sap xep";
    cout << endl;
    bool isValid = false;
    while (!isValid)
    {
        cout << endl
             << "  Chon chuc nang: ";
        int controlNumber;
        cin >> controlNumber;
        cout << endl;
        cin.ignore();
        switch (controlNumber)
        {
        case 0:
            dio.update(deletedList);
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
            viewManufacturerDetail();
            isValid = true;
            break;
        case 4:
            remove();
            isValid = true;
            break;
        case 5:
            search();
            manage();
            isValid = true;
            break;
        case 6:
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
void MaterialUtils::search()
{
    printBox("TIM KIEM VAT TU");
    // xoá đi virtualList cũ
    virtualList.reset();
    int id;
    string name, categoryName, manufacturerName;
    int quantity;
    unsigned long minUnitPrice, maxUnitPrice;
    string minUnitPriceString, maxUnitPriceString, quantityString;
    cout << "Nhap 0 neu ban muon bo qua!" << endl;
    // * I. Lấy input
    cout << "Nhap ten: ";
    getline(cin, name);
    name = trim(name);
    if (name == "0")
        name = "\0";

    cout << "Nhap ten loai VT: ";
    getline(cin, categoryName);
    categoryName = trim(categoryName);
    if (categoryName == "0")
        categoryName = "\0";

    cout << "Nhap ten NSX: ";
    getline(cin, manufacturerName);
    manufacturerName = trim(manufacturerName);
    if (manufacturerName == "0")
        manufacturerName = "\0";

    cout << "Nhap so luong (it nhat): ";
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

    cout << "Nhap don gia:" << endl;
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
void MaterialUtils::filter(string name, string categoryName, string manufacturerName, int quantity, unsigned long minUnitPrice, unsigned long maxUnitPrice)
{
    Material material;
    for (int i = 0; i < list.size; i++)
    {
        material = list[i];

        if ((toLower(material.getName()).find(toLower(name)) != string::npos) &&
            ((toLower(material.getCategory().getName()).find(toLower(categoryName)) != string::npos)) &&
            (toLower(material.getManufacturer().getName()).find(toLower(manufacturerName)) != string::npos) &&
            (material.getQuantity() >= quantity) &&
            (material.getUnitPrice() >= minUnitPrice) &&
            (material.getUnitPrice() <= maxUnitPrice))
        {
            virtualList.add(material);
        }
    }
}
void MaterialUtils::viewManufacturerDetail()
{
    printBox("XEM CHI TIET NSX");

    Material material;
    string idString;

    int id;
    cout << "Nhap ma vat tu: ";
    
    // Lấy VT từ input người dùng
    material = getElement(virtualList);

    // IN NSX RA
    cout << endl;
    Manufacturer::printTitle();
    cout << endl;
    cout << material.getManufacturer();
    cout << endl;

    // ĐỀ XUẤT
    cout << endl;
    int control;
    cout << "Ban co muon xem chi tiet NSX cua vat tu khac khong? (co: 1 | khong: 0): ";
    cin >> control;
    cin.ignore();
    if (control)
        viewManufacturerDetail();
    // Nếu không thì quay về manage();
    else
        manage();
}

void MaterialUtils::add()
{
    // Khởi tạo properties của Material
    Material newMaterial;

    int id, categoryId, manufacturerId, quantity;
    string name, calculationUnit;
    Category category;
    Manufacturer manufacturer;
    unsigned long unitPrice;

    // Khởi tạo các chuỗi string để đánh giá input
    string quantityString, unitPriceString;

    printBox("THEM VAT TU");

    // Lấy id tiếp theo( từ list hiện tại và list đã xoá)
    int id1 = list.getMaxId() + 1;
    int id2 = deletedList.getMaxId() + 1;
    id = (id1 > id2 ? (id1) : (id2));
    newMaterial.setId(id);

    // Sử dụng isCancel để xác định trạng thái thoát
    bool isCancel = false;

    // Sử dụng vòng lặp cho tới khi nào thoả mãn các điều kiện của 1 Vật tư
    while (true)
    {
        // Tránh lỗi cin phía trước

        // Nhập tên, trim tên
        cout << "Nhap ten: ";
        getline(cin, name);
        name = trim(name);
        newMaterial.setName(name);

        // IN ds LVT và để người dùng chọn mã LVT
        printBox2("DANH SACH LOAI VAT TU");
        Category::printTitle();
        cout << endl;
        cout << cList;
        cout << endl << endl;
        cout << "Nhap ma LVT: ";

        // Lấy LVT từ input người dùng
        category = getElement(cList);
        newMaterial.setCategory(&category);

        // IN ds NSX và để người dùng chọn mã NSX
        printBox2("DANH SACH NSX");
        Manufacturer::printTitle();
        cout << endl;
        cout << pList;
        cout << endl << endl;
        cout << "Nhap ma NSX: ";

        // Lấy NSX từ input người dùng
        manufacturer = getElement(pList);
        newMaterial.setManufacturer(&manufacturer);

        // Đơn vị tính
        cout << "Nhap don vi tinh: ";
        getline(cin, calculationUnit);
        newMaterial.setCalculationUnit(trim(calculationUnit));

        // Số lượng
        cout
            << "Nhap so luong: ";
        while (true)
        {
            getline(cin, quantityString);
            quantityString = trim(quantityString);
            try
            { // chuyển chuỗi thành số
                // throw invalid_input
                quantity = toNumber(quantityString, "So luong");
                newMaterial.setQuantity(quantity);
                break;
            }
            catch (invalid_input &exception)
            {
                cout << exception.get_info();
                cout << " Vui long nhap lai: ";
            }
        }

        // Đơn giá
        cout << "Nhap don gia: ";
        while (true)
        {
            getline(cin, unitPriceString);
            unitPriceString = trim(unitPriceString);
            try
            { // throw invalid_input
                unitPrice = toNumber(unitPriceString, "Don gia");

                // trường hợp đơn giá = 0
                if (unitPrice == 0)
                    throw nonPositive_number("Don gia");
                else
                {
                    newMaterial.setUnitPrice(unitPrice);
                    break;
                }
            }
            catch (custom_exception &exception)
            {
                cout << exception.get_info();
                cout << " Vui long nhap lai: ";
            }
        }

        // Kiểm tra xem VT này đã có trong DS VT chưa
        // Nếu đã có
        if (
            list.contains(newMaterial))
        {
            cout << endl
                 << "Vat tu nay da ton tai!" << endl;
            // Khi tồn tại thì lập tức huỷ việc thêm đơn hàng( nếu không muốn nhập lại)
            isCancel = true;
        }
        else
        { // Gán lại isCancel = false để tránh giá trị đã bị gán true ở lần trước
            isCancel = false;
        }

        // Xác nhận việc huỷ
        int controlNumber;
        cout << "Ban co muon nhap lai? (co: 1 | khong: 0): ";

        cin >> controlNumber;
        cout << endl;
        cin.ignore();
        // Nếu huỷ thì break ra ngoài
        if (controlNumber == 0)
            break;
    }
    // Nếu huỷ thì về manage()
    if (isCancel)
        manage();
    // Nếu thoả mãn các điều kiện
    else
    {
        // Thêm newMaterial vào cả ds thật và ảo
        list.add(newMaterial);
        virtualList.add(newMaterial);
        // Thông báo
        cout << "Da them VT thanh cong!" << endl;
        // Đề xuất
        cout << "Ban co muon tiep tuc them VT?  (co: 1 | khong: 0): ";
        int controlNumber;
        cin >> controlNumber;
        cin.ignore();
        // Nếu không nhập tiếp thì về lại manage
        if (controlNumber == 0)
        {

            manage();
        }
        // Tiếp tục thêm
        else
            add();
    }
}
void MaterialUtils::update()
{
    printBox("CAP NHAT THONG TIN VAT TU");
    int id;
    cout << "Chon ma VT: ";
    Material material;
    // Get material từ id người dùng nhập
    material = getElement(virtualList);

    // số lượng cần thêm
    unsigned long newPrice;
    int addNumber;
    string name;
    string categoryName;
    string manufacturerName;

    cout << "Nhap '0' neu ban muon de thong tin nhu cu!" << endl;
    cout << "Nhap ten moi: ";
    getline(cin, name);
    name = trim(name);
    if (name != "0")
    {
        material.setName(name);
    }

    // LVT
    cout << endl;
    Category::printTitle();
    cout << endl;
    cout << cList;
    Category category;
    string categoryIdString;
    int categoryId;
    cout << endl << endl;
    cout << "Nhap ma loai VT: ";

    while (true)
    {
        // GET chuỗi và trim
        getline(cin, categoryIdString);
        categoryIdString = trim(categoryIdString);
        // Nếu không update thì break;
        if (categoryIdString == "0")
            break;
        try
        { // Chuyển chuỗi thành số
            // throw invalid_input exception
            categoryId = toNumber(categoryIdString, "Ma");

            // Get element từ list, và thoát khỏi vòng lặp
            // throw non_existent_element
            category = cList.get(findById, categoryId);
            material.setCategory(&category);
            break;
        }
        catch (invalid_input &exception)
        {
            cout << exception.get_info();
        }
        catch (non_existent_element &exception)
        {
            cout << "Ma khong ton tai!";
        }
        // Nếu xảy ra 1 trong 2 exception ở trên
        cout << " Vui long nhap lai: ";
    }

    // NSX
    cout << endl;
    Manufacturer::printTitle();
    cout << endl;
    cout << pList;
    Manufacturer manufacturer;
    string manufacturerIdString;
    int manufacturerId;
    cout << endl;
    cout << "Nhap ma NSX: ";
    while (true)
    {
        // GET chuỗi và trim
        getline(cin, manufacturerIdString);
        manufacturerIdString = trim(manufacturerIdString);
        // Nếu không update thì break;
        if (manufacturerIdString == "0")
            break;

        try
        { // Chuyển chuỗi thành số
            // throw invalid_input exception
            manufacturerId = toNumber(manufacturerIdString, "Ma");

            // Get element từ list, và thoát khỏi vòng lặp
            // throw non_existent_element
            manufacturer = pList.get(findById, manufacturerId);
            material.setManufacturer(&manufacturer);
            break;
        }
        catch (invalid_input &exception)
        {
            cout << exception.get_info();
        }
        catch (non_existent_element &exception)
        {
            cout << "Ma khong ton tai!";
        }
        // Nếu xảy ra 1 trong 2 exception ở trên
        cout << " Vui long nhap lai: ";
    }

    string quantityString;
    cout << "Nhap so luong can them: ";
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
    cout << "Nhap don gia moi: ";
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
            }
            break;
        }
        catch (custom_exception &exception)
        {
            cout << exception.get_info();
            cout << " Vui long nhap lai: ";
        }
    }
    // Cập nhật vào 2 ds
    virtualList.update(material);
    list.update(material);
    cout << endl
         << "Da cap nhat VT thanh cong !" << endl;
    cout << "Ban co muon tiep tuc cap nhat VT? (co: 1 | khong: 0): ";
    int controlNumber;
    cin >> controlNumber;
    cin.ignore();

    if (controlNumber == 0)
    {
        manage();
    }
    else
        update();
}
void MaterialUtils::remove()
{
    printBox("XOA VAT TU");
    // nhap ma VT
    int id, i, j;
    bool isCancel = false;
    cout << "Nhap ma VT can xoa: ";

    Material material;

    while (true)
    {
        cin >> id;
        cin.ignore();

        try
        {   
            // Get material từ input
            // throw non_existent element
            material = virtualList.get(findById, id);
            // Số lượng = 0, đủ điều kiện => thoát vòng lặp
            if (material.getQuantity() == 0)
                break;
            else
            {
                cout << "So luong vat tu trong kho van con, khong the xoa! Ban co muon xoa vat tu khac? (co: 1 | khong: 0): ";
                int cancelNumber;
                cin >> cancelNumber;
                cin.ignore();

                isCancel = !(cancelNumber);
                // cancel thì break ra ngoài
                if (isCancel)
                    break;
            }
        }
        catch (non_existent_element &exception)
        {
            cout << "Khong ton tai VT ban vua nhap !";
        }
        // Nhập lại cho trường hợp số lượng > 0 hoặc không tồn tại
        cout << " Vui long nhap lai: ";
    }

    if (isCancel)
        manage();
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
        cin.ignore();

        if (controlNumber == 0)
        { // nếu thoát ra ngoài thì cập nhật file đã xoá
            manage();
        }
        else
            remove();
    }
}

void MaterialUtils::sort()
{
    printBox("SAP XEP VAT TU");
    cout << "Ban muon sap xep theo tieu chi nao ? " << endl
         << endl;
    cout << setw(15) << "1. Ten vat tu" << setw(20) << " 2. Ten loai vat tu" << setw(25) << " 3. Ten nha san xuat" << setw(20) << " 4. So luong"
         << " 5. Don gia " << endl
         << endl;

    int number;

    cout << "Nhap tieu chi: ";

    cin >> number;
    cin.ignore();

    char a;
    cout << "Tang ? Giam ? (t/g): ";
    cin >> a;
    cin.ignore();

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

#endif