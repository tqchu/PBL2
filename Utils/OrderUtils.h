#ifndef ORDERUTILS_H
#define ORDERUTILS_H
#include "BaseUtils.h"
#include "D:/PBL2/src/Common/Percentage.h"
class OrderUtils : public BaseUtils<Order>
{
private:
    // inherited io,list,virtualList
    void advancedSearch();
    bool isFirstTime;
    // Chi tiết đơn hàng
    OrderDetailIO odIO;
    ArrayList<OrderDetail> fullODList;
    // DS vật tư
    MaterialIO mIO;
    ArrayList<Material> fullMList;

    // Vật tư đã xoá
    DeletedMaterialIO dmIO;
    ArrayList<Material> dmList;

public:
    // inherit manage,display
    OrderUtils();
    void manage();
    virtual void control();
    virtual void add();
    virtual void update();
    virtual void sort();
    virtual void search();
    void cancelOrder();
    void statisticize();
    void filter(const Date &minDate, const Date &maxDate, string address, string status, unsigned long minTotalPrice, unsigned long maxTotalPrice);
    void filter(const Date &minDate, const Date &maxDate);
    void viewOrderDetail();
};
OrderUtils::OrderUtils()
{
    title += "DON HANG";

    io = new OrderIO();
    list = io->getList();

    // Khởi tạo vlist bằng list và lọc lấy 30 ngày gần nhất
    Date thisDate = Date::now();
    Date lastDate = thisDate;
    lastDate.toDateOfLast(0, 1, 0);
    filter(lastDate, thisDate);
    // Khởi tạo isFirstTime để in Title 30 Ngay Gan Nhat
    isFirstTime = true;

    // Khởi tạo OrderDetail List
    fullODList = odIO.getList();
    // Khởi tạo Material List
    fullMList = mIO.getList();
    // Vật tư đã xoá
    dmList = dmIO.getList();
}
/**
 * @Override
 * Thêm vào phần In tiêu đề 30 ngày nếu là lần đầu gọi manage()
 */
void OrderUtils::manage()
{
    printBox(title);
    // Nếu là lần đầu gọi manage()
    if (isFirstTime)
    {
        printTitle("30 NGAY GAN NHAT");
        isFirstTime = false;
    }
    display();
    control();
}
void OrderUtils::control()
{
    cout << "  ";
    cout << setw(40) << left << "0. Quay lai";
    cout << setw(30) << left << "1. Them don hang";
    cout << "2. Xem chi tiet don hang" << endl;

    cout << "  ";
    cout << setw(40) << left << "3. Cap nhat trang thai giao hang";
    cout << setw(30) << left << "4. Huy don hang";
    cout << "5. Tim kiem don hang" << endl;

    cout << "  ";
    cout << setw(40) << "6. Sap xep";
    cout << setw(30) << "7. Thong ke doanh thu";
    cout << endl;
    bool isValid = false;
    while (!isValid)
    {
        cout << endl
             << "  Chon chuc nang : ";
        int controlNumber;
        cin >> controlNumber;
        cin.ignore();

        cout << endl;
        switch (controlNumber)
        {
        case 0:
            io->update(list);
            odIO.update(fullODList);
            mIO.update(fullMList);
            dmIO.update(dmList);
            isValid = true;
            break;
        case 1:
            add();
            isValid = true;
            break;
        case 2:
            viewOrderDetail();
            manage();
            isValid = true;
            break;
        case 3:
            update();
            isValid = true;
            break;
        case 4:
            cancelOrder();
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
        case 7:
            statisticize();
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
void OrderUtils::search()
{
    // xoá đi virtualList cũ
    virtualList.reset();

    // Lấy ngày hiện tại
    Date thisDate = Date::now();
    // Gán bằng ngày hiện tại, sau đó trừ lùi
    Date lastDate = thisDate;

    // * 1. Chọn tiêu chí
    int controlNumber;
    cout << "Chon tieu chi tim kiem !" << endl;
    cout << setw(30) << "0. Tat ca";
    cout << setw(30) << "1. 7 ngay";
    cout << setw(30) << "2. 1 thang";
    cout << setw(30) << "3. 3 thang" << endl;
    cout << setw(30) << "4. 6 thang";
    cout << setw(30) << "5. 1 nam";
    cout << "6. Tim kiem nang cao";
    cout << endl
         << endl;
    cout << "Chon: ";
    cin >> controlNumber;
    cin.ignore();
    switch (controlNumber)
    {
    case 0:
        lastDate = Date::minDate();
        break;
    case 1:
        lastDate.toDateOfLast(7, 0, 0);
        break;
    case 2:
        lastDate.toDateOfLast(0, 1, 0);
        break;
    case 3:
        lastDate.toDateOfLast(0, 3, 0);
        break;
    case 4:
        lastDate.toDateOfLast(0, 6, 0);
        break;
    case 5:
        lastDate.toDateOfLast(0, 0, 1);
        break;
    case 6:
        advancedSearch();
        break;
    }
    // Case từ 1-5 , lười viết lại =)))
    if (controlNumber < 6)
    {
        filter(lastDate, thisDate);
    }
}
void OrderUtils::cancelOrder()
{
    printBox("HUY DON HANG");

    Order order;
    bool isCancel = false;
    cout << "Nhap ma don hang: ";
    while (true)
    {
        order = getElement(virtualList);
        if (order.getShippingStatus() != "Chua xu ly")
        {
            cout << "Don hang nay da duoc xu ly! Khong the huy!" << endl;
            cout << "Ban co muon nhap lai(co : 1 / khong : 0): ";
            int control;
            cin >> control;
            cin.ignore();
            if (!control)
            {
                isCancel = true;
                break;
            }
            else
                cout << " Vui long nhap lai: ";
        }
        else
            break;
    }
    if (!isCancel)
    {
        CategoryIO cIO;
        ArrayList<Category> cList = cIO.getList();
        DeletedCategoryIO dcIO;
        ArrayList<Category> dcList = dcIO.getList();

        ManufacturerIO manIO;
        ArrayList<Manufacturer> manList = manIO.getList();
        DeletedManufacturerIO dmanIO;
        ArrayList<Manufacturer> dmanList = dmanIO.getList();

        order.setShippingStatus("Da huy");
        // Phục hồi số lượng vật tư

        ArrayList<OrderDetail> odList = order.getOrderDetailList();
        Material dM;
        // loop qua từng ctdh
        for (int i = 0; i < odList.size; i++)
        {

            int id = odList[i].getMaterial().getId();

            // Nếu chứa trong list hiện tại thì cộng số lượng
            try
            {
                dM = fullMList.get(findById, id);
                dM.setQuantity(dM.getQuantity() + odList[i].getQuantity());
                fullMList.update(dM);
            }

            // Nếu vật tư đã bi xoá, thì phục hồi và xoá khỏi ds đã xoá
            catch (non_existent_element &e)
            {

                dM = dmList.get(findById, id);
                dM.setQuantity(odList[i].getQuantity());
                fullMList.add(dM);
                dmList.remove(id);
                // Nếu NSX và loại VT của VT đã xoá cũng đã bị xoá thì ta khôi phục luôn

                // KHÔI PHỤC LOẠI VẬT TƯ
                // Lấy mã Loại vật tư
                Category category = dM.getCategory();
                int cateId = category.getId();
                // Nếu ds Cate hiện tại không chứa thì ta khôi phục và xoá từ list đã xoá
                if (!cList.contains(category))
                {
                    cList.add(category);
                    dcList.remove(cateId);
                }

                // KHÔI PHỤC NSX
                //  Lấy mã NSX

                Manufacturer manufacturer = dM.getManufacturer();
                int manId = manufacturer.getId();
                if (!manList.contains(manufacturer))
                {
                    manList.add(manufacturer);
                    dmanList.remove(manId);
                }
            }
        }
        cIO.update(cList);
        dcIO.update(dcList);
        dmanIO.update(dmanList);
        manIO.update(manList);

        virtualList.update(order);
        list.update(order);
        // ĐỀ XUÂT
        cout << endl
             << "Da huy Don Hang thanh cong !" << endl;
        cout << "Ban co muon tiep tuc huy Don Hang ?  (co : 1 / khong : 0) : ";
        int controlNumber;

        cin >> controlNumber;
        cin.ignore();

        if (controlNumber == 0)
        { // nếu thoát ra ngoài thì cập nhật file đã xoá
            manage();
        }
        else
            cancelOrder();
    }
    else
        manage();
}
void OrderUtils::statisticize()
{
    printBox("THONG KE DOANH THU");

    // * I. Lấy DS các đơn hàng được tính vào doanh thu, tính luôn các giá trị cần thiết
    ArrayList<Order> oList;

    Order tempOrder;
    string shippingStatus;
    int numberOfOrders = 0;
    unsigned long originalPrice = 0;
    unsigned long totalPrice = 0;
    // * Loop qua từng đơn hàng và thêm vào ds
    // * Tính luôn Tổng số đơn hàng, Tổng giá gốc
    for (int i = 0; i < virtualList.size; i++)
    {
        tempOrder = virtualList[i];
        shippingStatus = tempOrder.getShippingStatus();
        // Nếu thoả điều kiện : Đã vận đơn / Đã huỷ
        if ((shippingStatus == ("Da van don")) || (shippingStatus == "Da giao"))
        {
            oList.add(tempOrder);
            numberOfOrders++;
            originalPrice += getOriginalPrice(tempOrder.getTotalPrice());
            totalPrice += tempOrder.getTotalPrice();
        }
    }
    // * II. Khởi tạo các mảng chứa DS Vật tư và Loại Vật tư
    ArrayList<Percentage<Material>> materialPercentageList;
    ArrayList<Percentage<Category>> categoryPercentageList;
    Percentage<Material> materialPercentage;
    Percentage<Category> categoryPercentage;

    ArrayList<OrderDetail> orderDetailList;
    OrderDetail orderDetail;
    unsigned long tempTotalPrice;
    double tempPercentage;
    Material tempMaterial;
    Category tempCategory;
    // * II. 1. Loop qua DS Order
    for (int i = 0; i < oList.size; i++)
    {
        orderDetailList = oList[i].getOrderDetailList();
        // * Loop qua từng orderDetail
        for (int j = 0; j < orderDetailList.size; j++)
        {

            // * Tính phần trăm
            orderDetail = orderDetailList[j];

            tempTotalPrice = orderDetail.getQuantity() * orderDetail.getUnitPrice();

            tempPercentage = (double)tempTotalPrice * 100 / originalPrice;
            // * lấy vật tư và loại vật tư
            tempMaterial = orderDetail.getMaterial();
            tempCategory = tempMaterial.getCategory();
            // * thêm vật tư vào ds vật tư
            // check xem vật tư đã có chưa

            try
            {
                materialPercentage = materialPercentageList.get(findByMaterial, tempMaterial);
                materialPercentage.setPercentage(tempPercentage + materialPercentage.getPercentage());
                materialPercentageList.update(materialPercentage);
            }
            catch (non_existent_element &e)
            {
                materialPercentage.setT(tempMaterial);
                materialPercentage.setPercentage(tempPercentage);
                materialPercentageList.add(materialPercentage);
            }

            // * thêm  loai vật tư vào ds  loai vật tư
            // check xem loai vật tư đã có chưa
            try
            {
                categoryPercentage = categoryPercentageList.get(findByCategory, tempCategory);
                categoryPercentage.setPercentage(tempPercentage + categoryPercentage.getPercentage());
                categoryPercentageList.update(categoryPercentage);
            }
            catch (non_existent_element &e)
            {
                categoryPercentage.setT(tempCategory);
                categoryPercentage.setPercentage(tempPercentage);
                categoryPercentageList.add(categoryPercentage);
            }
        }
    }

    // sort danh sach
    materialPercentageList.sort(sortByPercentage, descendingDouble);
    categoryPercentageList.sort(sortByPercentage, descendingDouble);

    cout << "TONG SO DON HANG: " << numberOfOrders << endl;
    cout << "TONG DOANH THU: " << totalPrice << endl;

    printBox("THONG KE THEO VAT TU");

    Percentage<Material>::printTitle();
    cout << materialPercentageList;

    printBox("THONG KE THEO LOAI VAT TU");
    Percentage<Category>::printTitle();
    cout << categoryPercentageList;
}
void OrderUtils::advancedSearch()
{

    string minDateString;
    string maxDateString;
    Date minDate, maxDate;
    string address;
    string status;
    unsigned long minTotalPrice;
    unsigned long maxTotalPrice;
    string minTotalPriceString, maxTotalPriceString;
    cout
        << "Nhap 0 neu muon bo qua!" << endl;
    cin.ignore();
    cout << "Nhap thoi gian (dd/mm/yyyy): " << endl;
    cout << "\t"
         << "Tu ngay: ";
    while (true)
    {
        getline(cin, minDateString);
        minDateString = trim(minDateString);
        if (minDateString == "0")
        {
            minDate = Date::minDate();
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
         << "Den ngay: ";
    while (true)
    {
        getline(cin, maxDateString);
        maxDateString = trim(maxDateString);
        if (maxDateString == "0")
        {
            maxDate = Date::maxDate();
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
    cout << "Nhap trang thai: ";
    getline(cin, status);
    status = trim(status);
    if (status == "0")
        status = "\0";
    cout << "Nhap thanh tien:" << endl;
    cout << "\t"
         << "Nho nhat: ";
    while (true)
    {
        getline(cin, minTotalPriceString);
        minTotalPriceString = trim(minTotalPriceString);
        try
        {
            minTotalPrice = toNumber(minTotalPriceString, "Thanh tien");
            if (minTotalPrice == 0)
                throw nonPositive_number("Thanh tien");
            else
                break;
        }
        catch (custom_exception &exception)
        {
            cout << exception.get_info();
            cout << " Vui long nhap lai: ";
        }
    }
    cout << "\t"
         << "Lon nhat: ";
    while (true)
    {
        getline(cin, maxTotalPriceString);
        maxTotalPriceString = trim(maxTotalPriceString);
        try
        {
            maxTotalPrice = toNumber(maxTotalPriceString, "Thanh tien");
            if (maxTotalPrice == 0)
                throw nonPositive_number("Thanh tien");
            else
                break;
        }
        catch (custom_exception &exception)
        {
            cout << exception.get_info();
            cout << " Vui long nhap lai: ";
        }
    }
    if (maxTotalPrice == 0)
        maxTotalPrice = 4000000000;
    filter(minDate, maxDate, address, status, minTotalPrice, maxTotalPrice);
}
void OrderUtils::filter(const Date &minDate, const Date &maxDate, string address, string status, unsigned long minTotalPrice, unsigned long maxTotalPrice)
{
    Order order;
    Date orderDate;
    unsigned long totalPrice;
    for (int i = 0; i < list.size; i++)
    {
        order = list[i];
        totalPrice = order.getTotalPrice();
        orderDate = order.getTime().getDate();
        if ((toLower(order.getShippingAddress()).find(toLower(address)) != string::npos) &&
            (toLower(order.getShippingStatus()).find(toLower(status)) != string::npos) &&
            (orderDate >= minDate) &&
            (orderDate <= maxDate) &&
            (minTotalPrice <= totalPrice) &&
            (maxTotalPrice >= totalPrice))
        {
            virtualList.add(list[i]);
        }
    }
}
void OrderUtils::filter(const Date &minDate, const Date &maxDate)
{
    Order order;
    Date orderDate;
    for (int i = 0; i < list.size; i++)
    {
        order = list[i];
        orderDate = order.getTime().getDate();
        if ((orderDate >= minDate) && (orderDate <= maxDate))
        {
            virtualList.add(list[i]);
        }
    }
}
void OrderUtils::viewOrderDetail()
{
    printBox("XEM CHI TIET DON HANG");
    Order order;
    cout << "Nhap ma don hang: ";
    order = getElement(virtualList);

    // IN DS
    OrderDetail::printTitle();
    cout << order.getOrderDetailList();

    unsigned long totalPrice = order.getTotalPrice();
    unsigned long originalPrice = getOriginalPrice(totalPrice);
    unsigned long discount = originalPrice - totalPrice;
    printHyphen(lineWidth);
    cout << setw(10) << ""
         << setw(40) << "Tong tien (chua giam gia)"
         << ": " << setw(15) << right << originalPrice << endl;
    cout << setw(10) << ""
         << setw(40) << "Giam gia ( " << discount * 100 / originalPrice << "% )"
         << ": " << setw(15) << right << discount << endl;
    cout << setw(10) << ""<< setw(40) << "Thanh tien"
         << ": " << setw(15) << right << totalPrice << endl;
    printHyphen(lineWidth);

    // ĐỀ XUẤT
    int controlNumber;
    cout << endl
         << "Ban co muon xem chi tiet don hang khac?(co: 1 | khong: 0): ";
    cin >> controlNumber;
    cin.ignore();
    if (controlNumber)
        viewOrderDetail();
}
void OrderUtils::add()
{

    printBox("THEM DON HANG");

    // Khởi tạo
    Order newOrder;
    ArrayList<OrderDetail> odList;
    OrderDetail od;
    Material material;
    unsigned long quantity;
    unsigned long totalWithoutDiscount = 0;
    unsigned long discount = 0;
    int id = list.getMaxId() + 1;
    newOrder.setId(id);
    bool isCancel = false;
    // Điều kiện thoát vòng lặp nhập vật tư
    bool flag = true;
    bool quantityCondition = true;
    while (flag)
    {
        // IN DS Vật tư
        Material::printTitle();
        cout << fullMList;

        // Lấy Vật tư
        while (true)
        {

            cout << "Nhap ma VT: ";
            material = getElement(fullMList);
            cout << "Nhap so luong: ";
            cin >> quantity;
            cin.ignore();

            // Đủ số lượng
            if (material.getQuantity() >= quantity)
            {
                quantityCondition = true;
                break;
            }
            // Không đủ số lượng
            else
            {
                quantityCondition = false;
                cout << "So luong vat tu nay trong kho khong du de ban!" << endl;
                cout << "Neu khong, don hang nay se bi huy!" << endl;
                // ĐỀ XUẤT
                cout << "Ban co muon nhap lai? (co: 1 | khong: 0): ";
                int control;
                cin >> control;
                cin.ignore();
                if (!control)
                {
                    flag = false;
                    isCancel = true;
                    break;
                }
            }
        }

        // ĐỦ ĐIỀU KIỆN
        if (quantityCondition)
        {
            // Thêm vào tổng tiền
            totalWithoutDiscount += quantity * material.getUnitPrice();

            // Trừ số lượng vật tư
            material.setQuantity(material.getQuantity() - quantity);
            fullMList.update(material);

            // Thêm vào OrderDetailList
            od = OrderDetail(id, material, quantity);
            od.setUnitPrice(material.getUnitPrice());

            odList.add(od);

            cout << "Ban co muon nhap tiep?(co: 1 | khong: 0): ";
            int control;
            cin >> control;
            cin.ignore();
            if (!control)
                flag = false;
        }
    }
    if (isCancel)
        manage();
    else
    {

        string shippingAddress;
        cout << "Nhap dia chi giao hang : ";

        getline(cin, shippingAddress);
        shippingAddress = trim(shippingAddress);
        newOrder.setShippingAddress(shippingAddress);
        // Tạo trạng thái giao hàng mặc định
        string shippingStatus = "Chua xu ly";
        newOrder.setShippingStatus(shippingStatus);
        // Set OrderDetailList
        newOrder.setOrderDetailList(odList);
        // Set time
        Time time = Time::now();
        newOrder.setTime(time);
        // Set TotalPrice
        discount = getDiscount(totalWithoutDiscount);
        newOrder.setTotalPrice(totalWithoutDiscount - discount);

        // Thêm DS CTDH vào list
        fullODList.add(odList);
        virtualList.add(newOrder);
        list.add(newOrder);
        // tin nhan thong bao
        cout << "Da them Don Hang thanh cong !" << endl;
        cout << "Ban co muon tiep tuc them Don Hang ?  (co : 1 / khong : 0) : ";
        int controlNumber;
        cin >> controlNumber;

        cin.ignore();

        if (controlNumber == 0)
        {
            manage();
        }
        else
            add();
    }
}
void OrderUtils::update()
{
    printBox("CAP NHAT TRANG THAI GIAO HANG");

    cout << "Nhap ma don hang: ";
    Order order;
    string status;
    bool isCancel = false;
    while (true)
    {
        order = getElement(virtualList);
        status = order.getShippingStatus();
        if ((status == "Da giao") || (status == "Da huy"))
        {

            cout << "Don hang nay " + status + "! Khong the cap nhat!" << endl;
            cout << "Ban co muon nhap lai?(co: 1 | khong: 0): ";
            int control;
            cin >> control;
            cin.ignore();
            if (!control)
            {
                isCancel = true;
                break;
            }
            else
                cout << "Vui long nhap lai: ";
        }
        else if (status == "Chua xu ly")
        {
            status = "Da van don";
            break;
        }
        else if (status == "Da van don")
        {
            status = "Da giao";
            break;
        }
    }
    if (!isCancel)
    {
        order.setShippingStatus(status);
        virtualList.update(order);
        list.update(order);
        // tin nhan thong bao
        cout << "Ban co muon tiep tuc cap nhat don hang?(co : 1 / khong : 0) : ";
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
    else
        manage();
}

void OrderUtils::sort()
{

    cout << "Ban muon sap xep theo tieu chi nao ? " << endl
         << endl;
    cout << setw(20)
         << "1. Thoi gian dat"
         << "2. Thanh tien" << endl
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
            virtualList.sort(sortByTime, ascendingTime);

        else
            virtualList.sort(sortByTime, descendingTime);

        break;
    case 2:

        if ((a == 't') || (a == 'T'))
            virtualList.sort(sortByTotalPrice, ascendingNumber);
        else
            virtualList.sort(sortByTotalPrice, descendingNumber);
        break;
    }
}
#endif