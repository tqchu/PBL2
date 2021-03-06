#ifndef MANUFACTURERUTILS_H
#define MANUFACTURERUTILS_H
#include "BaseUtils.h"
class ManufacturerUtils : public BaseUtils<Manufacturer>
{
private:
    // inherited io,list,virtualList
    DeletedManufacturerIO dio;
    ArrayList<Manufacturer> deletedList;

public:
    // inherit manage,display
    ManufacturerUtils();
    virtual void control();
    virtual void add();
    virtual void update();
    virtual void sort();
    virtual void search();
    void remove();
    void viewMaterialList();
    void filter(string name, string phoneNumber, Date minDate, Date maxDate, string address);
};
ManufacturerUtils::ManufacturerUtils()
{
    title += "NSX";

    io = new ManufacturerIO();

    list = io->getList();
    virtualList = list;

    deletedList = dio.getList();
}

void ManufacturerUtils::control()
{
    cout << "  ";
    cout << setw(20) << left << "0. Quay lai";
    cout << setw(20) << left << "1. Them NSX";
    cout << setw(35) << left << "2. Cap nhat thong tin NSX";
    cout << setw(35) << left << "3. Xem danh sach vat tu";
    cout << endl;
    cout << "  ";
    cout << setw(20) << left << "4. Xoa NSX";
    cout << setw(20) << left << "5. Tim kiem";
    cout << setw(35) << left << "6. Sap xep";
    cout << endl;
    bool isValid = false;
    while (isValid == false)
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
            io->update(list);
            dio.update(deletedList);
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
            viewMaterialList();
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
            cout << "Khong co chuc nhap da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}

void ManufacturerUtils::viewMaterialList()
{
    printBox("XEM DANH SACH VAT TU");

    Manufacturer manufacturer;

    int id;
    cout << "Nhap ma NSX: ";

    // L???y NSX t??? input ng?????i d??ng
    manufacturer = getElement(virtualList);

    // IN DS NSX
    cout << endl;
    Material::printTitle();
    cout << endl;
    cout << manufacturer.getMaterialList();

    // ????? XU???T
    int control;
    cout << endl << endl;
    cout << "Ban co muon xem DS Vat tu cua NSX khac khong? (co: 1 | khong: 0): ";
    cin >> control;
    cin.ignore();
    if (control)
        viewMaterialList();
    // N???u kh??ng th?? quay v??? manage();
    else
        manage();
}
void ManufacturerUtils::search()
{
    printBox("TIM KIEM NHA SAN XUAT");
    // xo?? ??i virtualList c??
    virtualList.reset();
    int id;
    string name, phoneNumber, minDateString, maxDateString, address;
    Date minDate, maxDate;

    cout << "Nhap 0 neu ban muon bo qua!" << endl;
    // * I. L???y input
    cout << "Nhap ten: ";
    getline(cin, name);
    name = trim(name);
    if (name == "0")
        name = "\0";
    cout << "Nhap SDT: ";
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
    Manufacturer newManufacturer;
    int id;
    string name, phoneNumber, address;
    Date date;
    bool isCancel = false;
    printBox("THEM NHA SAN XUAT");

    // L???y id ti???p theo( t??? list hi???n t???i v?? list ???? xo??)
    int id1 = list.getMaxId() + 1;
    int id2 = deletedList.getMaxId() + 1;
    id = (id1 > id2 ? (id1) : (id2));
    newManufacturer.setId(id);

    // b???t ?????u l???y d??? li???u t??? ng?????i d??ng
    // d??ng ????? tr??nh l???i do cin ph??a tr?????c

    int controlNumber;
    cout << "Nhap ten: ";
    while (true)
    {

        getline(cin, name);
        name = trim(name);
        newManufacturer.setName(name);

        // SDT
        cout << "Nhap SDT: ";
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
                {
                    newManufacturer.setPhoneNumber(phoneNumber);
                    break;
                }
            }
            catch (invalid_input &exception)
            {
                cout << exception.get_info();
                cout << " (SDT phai co 10 ki tu toan la chu so, bat dau bang so 0).";
                cout << " Vui long nhap lai: ";
            }
        }
        cout << "Nhap ngay hop tac (dd/mm/yyyy): ";
        string dateString;
        while (true)
        {
            getline(cin, dateString);
            dateString = trim(dateString);

            try
            {
                date = Date::toDate(dateString);
                newManufacturer.setDate(date);
                break;
            }
            catch (invalid_input &exception)
            {
                cout << exception.get_info();
                cout << " Vui long nhap lai: ";
            }
        }
        cout << "Nhap dia chi: ";
        getline(cin, address);
        address = trim(address);
        newManufacturer.setAddress(address);

        if (
            list.contains(newManufacturer))
        {
            cout << endl
                 << "NSX nay da ton tai!" << endl;
            // Khi t???n t???i th?? l???p t???c hu??? vi???c th??m ????n h??ng( n???u kh??ng mu???n nh???p l???i)
            isCancel = true;
        }
        else
        { // G??n l???i isCancel = false ????? tr??nh gi?? tr??? ???? b??? g??n true ??? l???n tr?????c
            isCancel = false;
        }

        // X??c nh???n vi???c hu???
        int controlNumber;
        cout << "Ban co muon  nhap lai? (co: 1 | khong: 0) : ";

        cin >> controlNumber;
        cout << endl;
        cin.ignore();
        // N???u hu??? th?? break ra ngo??i
        if (controlNumber == 0)
            break;

        break;
    }
    if (!isCancel)
    {
        list.add(newManufacturer);

        virtualList.add(newManufacturer);
        // tin nhan thong bao
        cout << "Da them NSX thanh cong!" << endl;
        cout << "Ban co muon tiep tuc them NSX?  (co: 1 | khong: 0): ";
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
        manage();
    }
}
void ManufacturerUtils::update()
{
    Manufacturer manufacturer;
    printBox("CAP NHAT THONG TIN NSX");
    int id;
    cout << "Chon ma NSX: ";
    manufacturer = getElement(virtualList);

    // s??? l?????ng c???n th??m
    string name;
    string phoneNumber;
    string address;


    cout << "Nhap '0' neu ban muon de thong tin nhu cu!" << endl;
    cout << "Nhap ten moi: ";
    getline(cin, name);
    name = trim(name);
    if (name != "0")
    {
        manufacturer.setName(name);
    }
    cout << "Nhap SDT moi: ";
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
            else{
                manufacturer.setPhoneNumber(phoneNumber);
                break;
            }
        }
        catch (invalid_input &exception)
        {
            cout << exception.get_info();
            cout << " (SDT phai co 10 ki tu toan la chu so, bat dau bang so 0)";
            cout << " Vui long nhap lai: ";
        }
    }
    cout << "Nhap dia chi moi: ";
    getline(cin, address);
    address = trim(address);

    if (address != "0")
    {
        manufacturer.setAddress(address);
    }

    list.update(manufacturer);
    virtualList.update(manufacturer);
    cout << endl
         << "Da cap nhat NSX thanh cong!" << endl;
    cout << "Ban co muon tiep tuc cap nhat NSX?  (co: 1 | khong: 0): ";
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
    printBox("XOA NHA SAN XUAT");
    // nhap ma NSX
    int id, i, j;
    bool isCancel = false;
    cout << "Nhap ma NSX can xoa: ";

    Manufacturer manufacturer;
    ArrayList<Material> mList;
    while (true)
    {
        cin >> id;
        cin.ignore();

        try
        {
            // Get manufacturer t??? input
            // throw non_existent element
            manufacturer = virtualList.get(findById, id);
            mList = manufacturer.getMaterialList();
            // S??? l?????ng = 0, ????? ??i???u ki???n => tho??t v??ng l???p
            if ((mList.isEmpty())||(mList.every(outOfQuantity)))
                break;
            else
            {
                cout << "So luong vat tu cua NSX nay trong kho van con, khong the xoa! Ban co muon xoa NSX khac? (co: 1 | khong: 0): ";
                int cancelNumber;
                cin >> cancelNumber;
                cin.ignore();

                isCancel = !(cancelNumber);
                // cancel th?? break ra ngo??i
                if (isCancel)
                    break;
            }
        }
        catch (non_existent_element &exception)
        {
            cout << "Khong ton tai NSX ban vua nhap!";
        }
        // Nh???p l???i cho tr?????ng h???p s??? l?????ng > 0 ho???c kh??ng t???n t???i
        cout << " Vui long nhap lai: ";
    }

    if (isCancel)
        manage();
    else
    {
        // xo?? lu??n DS VT
        MaterialIO mIO;
        DeletedMaterialIO dmIO;
        ArrayList<Material> fullMList = mIO.getList();
        ArrayList<Material> fullDMList = dmIO.getList();

        // Loop qua DS VT c???a NSX
        for (int i = 0; i < mList.size; i++)
        {
            // Remove kh???i list th???c
            fullMList.remove(mList[i].getId());
            // Th??m v??o list ???? xo??
            fullDMList.add(mList[i]);
        }
        // C???p nh???t v??o 2 file
        dmIO.update(fullDMList);
        mIO.update(fullMList);

        // insert vao file da xoa
        deletedList.add(manufacturer);

        list.remove(id);
        virtualList.remove(id);

        cout << endl
             << "Da xoa NSX thanh cong!" << endl;
        cout << "Ban co muon tiep tuc xoa NSX?  (co: 1 | khong: 0): ";
        int controlNumber;

        cin >> controlNumber;
        cin.ignore();

        if (controlNumber == 0)
        { // n???u tho??t ra ngo??i th?? c???p nh???t file ???? xo??
            manage();
        }
        else
            remove();
    }
}

void ManufacturerUtils::sort()
{
    printBox("SAP XEP NHA SAN XUAT");
    cout << "Ban muon sap xep theo tieu chi nao? " << endl
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
#endif