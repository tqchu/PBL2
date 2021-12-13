#ifndef MANUFACTURERUTILS_H
#define MANUFACTURERUTILS_H
#include "D:/PBL2/src/IO/ManufacturerIO.h"
#include "D:/PBL2/src/IO/MaterialIO.h"
#include "BaseUtils.h"
#include "D:/PBL2/src/Comparator.h"
#include "D:/PBL2/src/Find.h"
#include <iomanip>
class ManufacturerUtils : public BaseUtils<Manufacturer>
{
private:
    // inherited io,list,virtualList
public:
    // inherit manage,display
    ManufacturerUtils();
    virtual void control();
    virtual void printTitle();
    virtual void add();
    virtual void update();
    virtual void sort();
    virtual void search();
    virtual void remove();
    void filter(string name, string phoneNumber, Date minDate, Date maxDate, string address);
};
ManufacturerUtils::ManufacturerUtils()
{
    title += "NSX";

    io = new ManufacturerIO();

    io->getList(list);
    // io->getList(virtualList);
    virtualList = list;
}

void ManufacturerUtils::control()
{
    cout << "  ";
    cout << setw(20) << left << "0. Quay lai";
    cout << setw(20) << left << "1. Them NSX";
    cout << setw(34) << left << "2. Cap nhat thong tin NSX";
    cout << setw(19) << "3. Xoa NSX";
    cout << setw(20) << "4. Tim kiem";
    cout << setw(20) << "5. Sap xep";
    cout << endl;
    bool isValid = false;
    while (isValid == false)
    {
        cout << endl
             << "  Chon chuc nang : ";
        int controlNumber;
        cin >> controlNumber;
        cout << endl;
        switch (controlNumber)
        {
        case 0:
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
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void ManufacturerUtils::printTitle()
{
    cout << setw(5) << "";

    cout << setw(10) << left << "Ma NSX";
    cout << setw(32) << left << "Ten NSX";
    cout << setw(16) << left << "SDT";
    cout << setw(16) << left << "Ngay hop tac";
    cout << "Dia chi" << endl
         << endl;
}
void ManufacturerUtils::search()
{
    // xoá đi virtualList cũ
    virtualList.reset();
    int id;
    string name, phoneNumber, minDateString, maxDateString, address;
    Date minDate, maxDate;

    cout << "Nhap 0 neu ban muon bo qua!" << endl;
    // * I. Lấy input
    cin.ignore();
    cout << "Nhap ten: ";
    getline(cin, name);
    name = trim(name);
    if (name == "0")
        name = "\0";
    cout << "Nhap SDT : ";
    while (true)
    {
        getline(cin, phoneNumber);
        phoneNumber = trim(phoneNumber);
        if (phoneNumber == "0")
            break;
        try
        {
            if (!(regex_match(phoneNumber, regex("0{1}[1-9]{1}[0-9]{8}"))))
            {
                throw invalid_input("SDT");
            }
            else
                break;
        }
        catch (invalid_input &exception)
        {
            cout << exception.get_info();
            cout << " (SDT phai co 10 ki tu toan la chu so, bat dau bang so 0).";
            cout << " Vui long nhap lai: ";
        }
    }
    if (phoneNumber == "0")
        phoneNumber = "\0";
    cout << "Nhap ngay hop tac (dd/mm/yyyy):" << endl;
    cout << "\t"
         << setw(15) << right << "tu: ";
    while (true)
    {
        getline(cin, minDateString);
        minDateString = trim(minDateString);
        if (minDateString == "0")
        {
            minDate = Date::toDate("01/01/1111");
            break;
        }
        else
        {
            try
            {
                minDate = Date::toDate(minDateString);
                break;
            }
            catch (custom_exception &exception)
            {
                cout << exception.get_info();
                cout << " Vui long nhap lai: ";
            }
        }
    }

    cout << "\t"
         << setw(15) << right << "den: ";
    while (true)
    {
        getline(cin, maxDateString);
        maxDateString = trim(maxDateString);
        if (maxDateString == "0")
        {
            maxDate = Date::toDate("31/12/9999");
            break;
        }
        else
        {
            try
            {
                maxDate = Date::toDate(maxDateString);
                break;
            }
            catch (custom_exception &exception)
            {
                cout << exception.get_info();
                cout << " Vui long nhap lai: ";
            }
        }
    }
    cout << "Nhap dia chi: ";
    getline(cin, address);
    address = trim(address);
    if (address == "0")
        address = "\0";

    filter(name, phoneNumber, minDate, maxDate, address);
}
void ManufacturerUtils::filter(string name, string phoneNumber, Date minDate, Date maxDate, string address)

{
    Manufacturer manufacturer;
    for (int i = 0; i < list.size; i++)
    {
        manufacturer = list[i];

        Date pDate = manufacturer.getDate();
        if ((toLower(manufacturer.getName()).find(toLower(name)) != string::npos) &&
            ((toLower(manufacturer.getPhoneNumber()).find(toLower(phoneNumber)) != string::npos)) &&
            (toLower(manufacturer.getAddress()).find(toLower(address)) != string::npos) &&
            (pDate >= minDate) &&
            (pDate <= maxDate))
        {
            virtualList.add(manufacturer);
        }
    }
}
void ManufacturerUtils::add()
{
    string name, phoneNumber, address;
    Date date;
    bool isCancel = false;
    printBox("THEM NHA SAN XUAT");
    // mở cổng và getList

    int id = list.getMaxId() + 1;

    // bắt đầu lấy dữ liệu từ người dùng
    // dùng để tránh lỗi do cin phía trước

    cin.ignore();
    int controlNumber;
    cout << "Nhap ten : ";
    while (true)
    {
        getline(cin, name);
        name = trim(name);
        if (list.contains(findByName, name))
        {
            cout << endl
                 << "NSX da ton tai!" << endl;
            cout << "Ban co muon nhap lai(co: 1 | khong: 0): ";
            int control;
            cin >> control;
            cin.ignore();
            if (control)
            {
                isCancel = false;
                cout << "Vui long nhap lai: ";
            }
            else
            {
                isCancel = true;
                break;
            }
        }
        else
        {
            cout << "Nhap SDT : ";
            while (true)
            {
                getline(cin, phoneNumber);
                phoneNumber = trim(phoneNumber);
                try
                {
                    if (!(regex_match(phoneNumber, regex("0{1}[1-9]{1}[0-9]{8}"))))
                    {
                        throw invalid_input("SDT");
                    }
                    else
                        break;
                }
                catch (invalid_input &exception)
                {
                    cout << exception.get_info();
                    cout << " (SDT phai co 10 ki tu toan la chu so, bat dau bang so 0).";
                    cout << " Vui long nhap lai: ";
                }
            }
            cout << "Nhap ngay hop tac (dd/mm/yyyy) : ";
            string dateString;
            while (true)
            {
                getline(cin, dateString);
                dateString = trim(dateString);

                try
                {
                    date = Date::toDate(dateString);
                    break;
                }
                catch (invalid_input &exception)
                {
                    cout << exception.get_info();
                    cout << " Vui long nhap lai: ";
                }
            }
            cout << "Nhap dia chi : ";
            getline(cin, address);
            address = trim(address);

            break;
        }
    }
    if (!isCancel)
    {
        Manufacturer newManufacturer(id, name, phoneNumber, date, address);
        list.add(newManufacturer);

        virtualList.add(newManufacturer);
        // tin nhan thong bao
        cout << "Da them NSX thanh cong !" << endl;
        cout << "Ban co muon tiep tuc them NSX ?  (co : 1 / khong : 0) : ";
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
    {
        cout << "Da break";
        manage();
    }
}
void ManufacturerUtils::update()
{
    printBox("CAP NHAT THONG TIN NSX");
    int id;
    cout << "Chon ma NSX : ";

    while (true)
    {
        cin >> id;
        if (virtualList.contains(findById, id))
            break;
        else
        {
            cout << "Khong ton tai NSX tuong ung voi ma ban vua nhap! Vui long nhap lai: ";
        }
    }

    Manufacturer &virtualManufacturer = virtualList.get(findById, id);
    Manufacturer &manufacturer = list.get(findById, id);
    // số lượng cần thêm
    string name;
    string phoneNumber;
    string address;

    // dùng để tránh lỗi do cin phía trước
    cin.ignore();

    cout << "Nhap '0' neu ban muon de thong tin nhu cu !" << endl;
    cout << "Nhap ten moi : ";
    getline(cin, name);
    name = trim(name);
    if (name != "0")
    {
        manufacturer.setName(name);
        virtualManufacturer.setName(name);
    }
    cout << "Nhap SDT moi : ";
    while (true)
    {
        getline(cin, phoneNumber);
        phoneNumber = trim(phoneNumber);
        if (phoneNumber == "0")
            break;
        try
        {
            if (!(regex_match(phoneNumber, regex("0{1}[1-9]{1}[0-9]{8}"))))
            {
                throw invalid_input("SDT");
            }
            else
                break;
        }
        catch (invalid_input &exception)
        {
            cout << exception.get_info();
            cout << " (SDT phai co 10 ki tu toan la chu so, bat dau bang so 0).";
            cout << " Vui long nhap lai: ";
        }
    }
    if (phoneNumber != "0")
    {
        manufacturer.setPhoneNumber(phoneNumber);
        virtualManufacturer.setPhoneNumber(phoneNumber);
    }
    cout << "Nhap dia chi moi : ";
    getline(cin, address);
    address = trim(address);

    if (address != "0")
    {
        manufacturer.setAddress(address);
        virtualManufacturer.setAddress(address);
    }
    cout << endl
         << "Da cap nhat NSX thanh cong !" << endl;
    cout << "Ban co muon tiep tuc cap nhat NSX ?  (co : 1 / khong : 0) : ";
    int controlNumber;
    cin >> controlNumber;
    if (controlNumber == 0)
    {
        manage();
    }
    else
        update();
}
void ManufacturerUtils::remove()
{
    MaterialIO mIO;
    ArrayList<Material> fullMList;
    mIO.getList(fullMList);

    ArrayList<Material> mList;

    // nhap ma NSX
    int id, i, j;
    bool isValid = false;
    bool isCancel = false;
    cout << "Nhap ma NSX can xoa : ";

    Manufacturer manufacturer;

    while (true)
    {
        cin >> id;

        try
        {
        
            manufacturer = virtualList.get(findById, id);
            mList = fullMList.getGroup(findByManufacturerName, manufacturer.getName());
            if (mList.every(outOfQuantity))
                break;
            else
            {
                cout << "So luong vat tu cua NSX nay trong kho van con, khong the xoa! Ban co muon xoa NSX khac? (co: 1 | khong: 0): ";
                int cancelNumber;
                cin >> cancelNumber;
                isCancel = !(cancelNumber);
                if (isCancel)
                    break;
            }
            
        }
        catch (non_existent_element &exception)
        {
            cout << "Khong ton tai NSX ban vua nhap !";
        }
        cout << " Vui long nhap lai: ";
    }

    if (isCancel)
    {
        manage();
    }
    else
    {

        // xoá tất cả VT liên quan
        for (int i = 0; i < mList.size;i++){
            fullMList.remove(mList[i].getId());
        }
        mIO.update(fullMList);

        list.remove(id);
        virtualList.remove(id);

        cout << endl
             << "Da xoa NSX thanh cong !" << endl;
        cout << "Ban co muon tiep tuc xoa NSX ?  (co : 1 / khong : 0) : ";
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

void ManufacturerUtils::sort()
{

    cout << "Ban muon sap xep theo tieu chi nao ? " << endl
         << endl;
    cout << setw(20) << "1. Ten NSX"
         << "2. Ngay hop tac" << endl
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
            virtualList.sort(sortByDate, ascendingDate);
        else
            virtualList.sort(sortByDate, descendingDate);
        break;
    }
}
/* 
int main()
{
    ManufacturerUtils p;
    p.manage();
} */