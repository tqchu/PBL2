#ifndef CATEGORYUTILS_H
#define CATEGORYUTILS_H
#include "BaseUtils.h"
class CategoryUtils : public BaseUtils<Category>
{
private:
    // inherited io,list,virtualList

    // Truy cập ds đã xoá
    DeletedCategoryIO dio;
    ArrayList<Category> deletedList;

public:
    // inherit manage,display
    CategoryUtils();
    virtual void control();
    virtual void add();
    virtual void update();
    virtual void sort();
    virtual void search();
    void viewMaterialList();
    void remove();
    void filter(string name);
};
CategoryUtils::CategoryUtils()
{
    // Khởi tạo title
    title += "LOAI VAT TU";

    // Khởi tạo io và dio
    io = new CategoryIO();

    // Khởi tạo list và gán virtualList = list
    list = io->getList();

    virtualList = list;

    // Lấy DS Vật tư đã xoá
    deletedList = dio.getList();

}

void CategoryUtils::control()
{
    cout << "  ";
    cout << setw(20) << left << "0. Quay lai";
    cout << setw(20) << left << "1. Them LVT";
    cout << setw(34) << left << "2. Cap nhat thong tin LVT";
    cout << setw(34) << left << "3. Xem danh sach vat tu";
    cout << endl;
    cout << "  ";
    cout << setw(20) << left << "4. Xoa LVT";
    cout << setw(20) << left << "5. Tim kiem";
    cout << setw(20) << "6. Sap xep";
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
            cout << "Khong co chuc nang da nhap! "
                 << "Moi ban nhap lai chuc nang" << endl;
            break;
        }
    }
}
void CategoryUtils::search()
{
    // xoá đi virtualList cũ
    virtualList.reset();
    string name;
    // * I. Lấy input
    cout << "Nhap ten: ";
    getline(cin, name);
    name = trim(name);

    filter(name);
}
void CategoryUtils::filter(string name)
{
    Category category;
    for (int i = 0; i < list.size; i++)
    {
        category = list[i];

        if ((toLower(category.getName()).find(toLower(name)) != string::npos))
        {
            virtualList.add(category);
        }
    }
}
void CategoryUtils::viewMaterialList()
{
    printBox("XEM DANH SACH VAT TU");

    Category category;

    int id;
    cout << "Nhap ma loai vat tu: ";

    // Lấy LVT từ input người dùng
    category = getElement(virtualList);

    // IN DS LVT
    cout << endl;
    Material::printTitle();
    cout << endl;
    cout << category.getMaterialList();

    // ĐỀ XUẤT
    cout << endl << endl;
    int control;
    cout << "Ban co muon xem danh sach vat tu cua LVT khac khong? (co: 1 | khong: 0): ";
    cin >> control;
    cin.ignore();
    if (control)
        viewMaterialList();
    // Nếu không thì quay về manage();
    else
        manage();
}

void CategoryUtils::add()
{
    // Khởi tạo properties của Category
    Category newCategory;
    int id;
    string name;

    printBox("THEM LOAI VAT TU");

    // Lấy id tiếp theo( từ list hiện tại và list đã xoá)
    int id1 = list.getMaxId() + 1;
    int id2 = deletedList.getMaxId() + 1;
    id = (id1 > id2 ? (id1) : (id2));
    newCategory.setId(id);

    // Sử dụng isCancel để xác định trạng thái thoát
    bool isCancel = false;
    cout << "Nhap ten: ";
    // Sử dụng vòng lặp cho tới khi nào thoả mãn các điều kiện của 1 Vật tư
    while (true)
    {
        getline(cin, name);
        name = trim(name);

        newCategory.setName(name);

        // Kiểm tra xem LVT này đã có trong DS LVT chưa
        // Nếu đã có
        if (
            list.contains(newCategory))
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
        // Thêm newCategory vào cả ds thật và ảo
        list.add(newCategory);
        virtualList.add(newCategory);
        // Thông báo
        cout << "Da them LVT thanh cong!" << endl;
        // Đề xuất
        cout << "Ban co muon tiep tuc them LVT? (co: 1 | khong: 0): ";
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
void CategoryUtils::update()
{
    printBox("CAP NHAT THONG TIN VAT TU");
    int id;
    cout << "Chon ma LVT: ";
    Category category;
    // Get category từ id người dùng nhập
    category = getElement(virtualList);

    string name;
    cout << "Nhap ten moi: ";
    getline(cin, name);
    name = trim(name);
    category.setName(name);

   
    // Cập nhật vào 2 ds
    virtualList.update(category);
    list.update(category);
    cout << endl
         << "Da cap nhat LVT thanh cong!" << endl;
    cout << "Ban co muon tiep tuc cap nhat LVT? (co: 1 | khong: 0): ";
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
/** 
 * Điều kiện: Tổng số lượng vật tư của loại VT này đều đã hết
*/
void CategoryUtils::remove()
{

    // nhap ma LVT
    int id, i, j;
    bool isCancel = false;
    cout << "Nhap ma LVT can xoa: ";

    Category category;
    ArrayList<Material> mList;
    while (true)
    {
        cin >> id;
        cin.ignore();

        try
        {
            // Get category từ input
            // throw non_existent element
            category = virtualList.get(findById, id);
            mList = category.getMaterialList();
            // Số lượng = 0, đủ điều kiện => thoát vòng lặp
            if ((mList.isEmpty()) || (mList.every(outOfQuantity)))
                break;
            else
            {
                cout << "So luong vat tu cua loai vat tu nay trong kho van con, khong the xoa! Ban co muon xoa loai vat tu khac? (co: 1 | khong: 0): ";
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
            cout << "Khong ton tai LVT ban vua nhap!";
        }
        // Nhập lại cho trường hợp số lượng > 0 hoặc không tồn tại
        cout << " Vui long nhap lai: ";
    }

    if (isCancel)
        manage();
    else
    {
        // xoá luôn DS VT
        MaterialIO mIO;
        DeletedMaterialIO dmIO;
        ArrayList<Material> fullMList = mIO.getList();
        ArrayList<Material> fullDMList = dmIO.getList();

        // Loop qua DS VT của LVT
        for (int i = 0; i < mList.size;i++){
            // Remove khỏi list thực
            fullMList.remove(mList[i].getId());
            // Thêm vào list đã xoá
                fullDMList.add(mList[i]);
        }
        // Cập nhật vào 2 file
        dmIO.update(fullDMList);
        mIO.update(fullMList);

        // insert vao file da xoa
        deletedList.add(category);
    
        list.remove(id);
        virtualList.remove(id);

        cout << endl
             << "Da xoa LVT thanh cong!" << endl;
        cout << "Ban co muon tiep tuc xoa LVT? (co : 1 | khong : 0): ";
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

void CategoryUtils::sort()
{

    cout << "Danh sach LVT duoc sap xep theo ten!" << endl;
    char a;
    cout << "Tang ? Giam ? (t/g): ";
    cin >> a;
    cin.ignore();

    if (a == 't')
        virtualList.sort(sortByName, ascendingString);
    else
        virtualList.sort(sortByName, descendingString);
}

#endif