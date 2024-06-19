#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// Màu ban đầu
// 0 -> red
// 1 -> green
// 2 -> blue

int p1 = 19; // 2 số nguyên tố được lấy bởi bên thứ nhất(prover).
int p2 = 73; // Cố gắng làm cho bên thứ hai (người xác minh) tin rằng bên thứ nhất có 2 số nguyên tố.


bool isPrime(int n)
{
    int flag = 1;
    for(int i=2;i<=sqrt(n);i++)
    {
        if(n%i==0)
        {
            flag = 0;
            break;
        }
    }
    if(flag==0)
    {
        return false;
    }
    else{
        return true;
    }
};


int random(int min, int max) //Để tạo ngẫu nhiên 0 hoặc 1 hoặc 2
{
   static bool first = true;
   if (first)
   {
      srand(time(NULL));
      first = false;
   }
   return min + rand() % ((max+1)-min);
};



/* Sau mỗi chu kỳ, 3 màu của đồ thị được hoán vị ngẫu nhiên, vì vậy,
 ví dụ: nếu người kiểm tra chọn cùng một cạnh giữa 2 đỉnh được kết nối trong một hàng, nó sẽ hiển thị cặp màu khác nhau
trong 2 lần thử,nhưng đồ thị vẫn giữ nguyên 3 màu -có thể tô màu hoặc không thể tô màu 3 màu tùy theo tuyên bố chứng minh 
của người chứng minh là đúng hay sai tương ứng*/
void randomise_color(vector<char>& permu_color)
{
    vector<char> color = {'r','g','b'};

    int x = random(0,2);
    permu_color;
    permu_color.push_back(color[x]);
    vector<char>::iterator it1;
    it1 = color.begin()+x;
    color.erase(it1);

    int y =random(0,1);
    permu_color.push_back(color[y]);
    vector<char>::iterator it2;
    it2 = color.begin()+y;
    color.erase(it2);

    permu_color.push_back(color[0]);
};



// Để in màu đỏ, lục hoặc lam tùy theo 'r', 'g' hay 'b'
void print_col(char c)
{
    if(c=='r')
    {
        cout<<"red";
    }
    else if(c=='g')
    {
        cout<<"green";
    }
    else{
        cout<<"blue";
    }
};



/* Lớp này chứa 2 biểu đồ: 1 biểu đồ 3 màu và biểu đồ không thể tô 3 màu khác và các phương thức khác nhau cho chúng*/
class graph
{
private:
    int g1_v = 10;
    int g1_e = 15;
    int *g1 = nullptr;
    vector<int> g1_col;

    int g2_v = 12;
    int g2_e = 21;
    int *g2 = nullptr;
    vector<int> g2_col;

    int itr = 1;
public:
    // Đồ thị 3 màu
    void graph1()
    {
        int n = g1_v;
        g1 = (int*)malloc(n*n*sizeof(int));

        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                *(g1+i*n+j) = 0;
            }
        }

        for(int i=0;i<n-n/2;i++)
        {
            int x = (i+2)%5;
            int y = (i+3)%5;
            int z = i+5;

            *(g1+i*n+x) = 1;
            *(g1+i*n+y) = 1;
            *(g1+i*n+z) = 1;
            *(g1+z*n+i) = 1;
        }

        for(int i=5;i<n;i++)
        {
            if(i==5)
            {
                *(g1+i*n+i+1) = 1;
                *(g1+i*n+9) = 1;
            }
            else if(i==9)
            {
                *(g1+i*n+i-1) = 1;
                *(g1+i*n+5) = 1;
            }
            else
            {
                *(g1+i*n+i-1) = 1;
               *(g1+i*n+i+1) = 1;
            }
        }

        int color[n] = {0,1,1,2,0,1,2,0,1,2};
        for(int i=0;i<n;i++)
        {
            g1_col.push_back(color[i]);
        }
    };



    // Đồ thị không màu
    void graph2()
    {
        int n = g2_v;
        g2 = (int*)malloc(n*n*sizeof(int));

         for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                *(g2+i*n+j) = 0;
            }
        }

        for(int i=0;i<n-n/2;i++)
        {
            if(i==0)
            {
                *(g2+i*n+i+1) = 1;
                *(g2+i*n+5) = 1;
                *(g2+i*n+i+6) = 1;
                *(g2+i*n+i+7) = 1;
            }
            else if(i==5)
            {
                *(g2+i*n+i-1) = 1;
                *(g2+i*n+0) = 1;
                *(g2+i*n+i+6) = 1;
                *(g2+i*n+6) = 1;
            }
            else
            {
                *(g2+i*n+i-1) = 1;
                *(g2+i*n+i+1) = 1;
                *(g2+i*n+i+6) = 1;
                *(g2+i*n+i+7) = 1;

            }
        }

        for(int i=6;i<n;i++)
        {
            if(i==6)
            {
                *(g2+i*n+5) = 1;
                *(g2+i*n+0) = 1;
            }
            else
            {
                int x = i-7;
                *(g2+i*n+x) = 1;
                *(g2+i*n+x+1) = 1;
            }
        }

        for(int i=6;i<9;i++)
        {
            *(g2+i*n+i+3) = 1;
            *(g2+(i+3)*n+i) = 1;
        }
        int color[n] = {1,2,1,2,0,0,2,0,0,0,1,1};
        for(int i=0;i<n;i++)
        {
            g2_col.push_back(color[i]);
        }
    };



    // In biểu đồ 1 để chỉ ra mối liên hệ giữa các đỉnh (nếu có)
    void print_graph1()
    {
        int n = g1_v;
        for(int i=0;i<n;i++){
            cout<<"V"<<i<<" -> ";
            for(int j=0;j<n;j++)
            {
                if(*(g1+i*n+j)==1)
                {
                    cout<<"V"<<j<<" ";
                }
            }
            cout<<endl;
        }
        cout<<endl;
    };



    // Để in biểu đồ2 để chỉ ra các kết nối giữa các đỉnh (nếu có)
    void print_graph2()
    {
        int n = g2_v;
        for(int i=0;i<n;i++){
            cout<<"V"<<i<<" -> ";
            for(int j=0;j<n;j++)
            {
                if(*(g2+i*n+j)==1)
                {
                    cout<<"V"<<j<<" ";
                }
            }
            cout<<endl;
        }
        cout<<endl;
    };



    /* Đối với đồ thị-1: Để in màu của 2 đỉnh nối nhau bởi một cạnh (được yêu cầu bởi người xác minh) và cập nhật độ tin cậy
 của người xác minh tương ứng */
    void check_color_g1(int v1,int v2)
    {
        int n = g1_v;
        if(*(g1+v1*n+v2)==1)
        {
            vector<char> tmp;
            randomise_color(tmp);

            if(g1_col[v1]==0)
            {
                cout<<"V"<<v1<<"(";
;                print_col(tmp[0]);
                cout<<")"<<"--------";
            }
            else if(g1_col[v1]==1)
            {
                cout<<"V"<<v1<<"(";
;                print_col(tmp[1]);
                cout<<")"<<"--------";
            }
            else{
                cout<<"V"<<v1<<"(";
;                print_col(tmp[2]);
                cout<<")"<<"--------";
            }


            if(g1_col[v2]==0)
            {
                cout<<"V"<<v2<<"(";
                print_col(tmp[0]);
                cout<<")";
            }
            else if(g1_col[v2]==1)
            {
                cout<<"V"<<v2<<"(";
                print_col(tmp[1]);
                cout<<")";
            }
            else{
                cout<<"V"<<v2<<"(";
                print_col(tmp[2]);
                cout<<")";
            }
            cout<<endl;
            double confidence = (1 - pow((1-1.0/g1_e),itr))*100;
            cout<<"Độ tin cậy của người xác minh: "<<confidence<<"%"<<endl;
            itr++;
        }
        else{
            cout<<"2 đỉnh không được nối với nhau bằng một cạnh"<<endl;
        }
    };



    /* Đối với đồ thị-2: Để in màu của 2 đỉnh nối nhau bởi một cạnh (được yêu cầu bởi người xác minh) và cập nhật độ tin cậy
 của người xác minh tương ứng */
    void check_color_g2(int v1,int v2)
    {
        int n = g2_v;
        if(*(g2+v1*n+v2)==1)
        {
            vector<char> tmp;
            randomise_color(tmp);

            if(g2_col[v1]==0)
            {
                cout<<"V"<<v1<<"(";
;                print_col(tmp[0]);
                cout<<")"<<"--------";
            }
            else if(g2_col[v1]==1)
            {
                cout<<"V"<<v1<<"(";
;                print_col(tmp[1]);
                cout<<")"<<"--------";
            }
            else{
                cout<<"V"<<v1<<"(";
;                print_col(tmp[2]);
                cout<<")"<<"--------";
            }


            if(g2_col[v2]==0)
            {
                cout<<"V"<<v2<<"(";
                print_col(tmp[0]);
                cout<<")";
            }
            else if(g2_col[v2]==1)
            {
                cout<<"V"<<v2<<"(";
                print_col(tmp[1]);
                cout<<")";
            }
            else{
                cout<<"V"<<v2<<"(";
                print_col(tmp[2]);
                cout<<")";
            }
            cout<<endl;
            if(g2_col[v1]==g2_col[v2])
            {
                cout<<"Chúng ta có 2 đỉnh liền kề cùng màu, do đó, đồ thị không thể tô được 3 màu!!!"<<endl;
                cout<<"Do đó, người xác minh hiện có 0 độ tin cậy rằng 2 số mà người chứng minh có là số nguyên tố"<<endl;
                itr = 1;
            }
            else
            {
                double confidence = (1 - pow((1-1.0/g2_e),itr))*100;
                cout<<"Độ tin cậy của người xác minh:"<<confidence<<"%"<<endl;
                itr++;
            }
        }
        else{
            cout<<"2 đỉnh không được nối với nhau bằng một cạnh"<<endl;
        }
    };

};

int main()
{
    int n;

    graph g;
    g.graph1();
    g.graph2();

    cout<<"Xin chào Người xác minh!!!"<<endl;
    cout<<endl;
    cout<<"Người chứng minh khẳng định có 2 số nguyên tố"<<endl;
    cout<<endl;
    cout<<"Và để chứng minh tính đúng đắn của nhận định này ";
    cout<<"người chứng minh đã chuyển câu nói rằng ông ta có 2 số nguyên tố thành ";
    cout<<"Bản đồ 3 màu và đưa cho bạn (người xác minh) mà không cần thực hiện ";
    cout<<"bất kỳ thay đổi tiếp theo nào trong cách sắp xếp của biểu đồ ngoài màu sắc của các đỉnh"<<endl;
    cout<<endl;
    cout<<"Để kiểm tra tính đúng đắn của tuyên bố, bạn (người xác minh)";
    cout<<"chọn các đỉnh liền kề xem chúng có màu khác nhau hay không và xác minh thông tin"<<endl;
    cout<<endl;
    cout<<"Nếu tại bất kỳ điểm nào 2 cạnh liền kề có cùng màu thì điều này có nghĩa là bản đồ không thể có 3 màu,";
    cout<<"do đó khẳng định của người chứng minh là sai"<<endl;
    cout<<endl;


    /* Đây là một ứng dụng nhỏ của chứng minh không có kiến ​​thức trong đó thông qua các biểu đồ màu, người chứng minh cố gắng tăng
 độ tin cậy của người xác minh mà không thực sự cho người xác minh biết 2 số nguyên tố đó là gì.*/

    /* Có vẻ mơ hồ về cách chúng ta có thể tạo ra mối quan hệ một-một giữa tuyên bố chứng minh (trong trường hợp này là
 khẳng định rằng người chứng minh phải có số nguyên tố) và đồ thị 3 màu. Nhưng người ta biết rằng bất kỳ bằng chứng nào
 đúng có thể được chuyển đổi thành biểu đồ 3 màu hợp lệ nhưng bằng chứng sai thì không thể.*/

    /* Ở đây mà không thực sự sử dụng các bước chính xác để tìm mối quan hệ một-một giữa câu lệnh và biểu đồ có thể tô màu của nó
 (điều này thực sự khó thực hiện), tôi đã trực tiếp đặt mối quan hệ khó khăn giữa đó để đơn giản cho việc chứng minh*/

    /*LƯU Ý: Hiện tại cả hai số đều là số nguyên tố, để kiểm tra xem điều gì xảy ra khi có ít nhất 1 số không phải là số nguyên tố, chỉ cần thay đổi chúng
 và chọn một số cặp đỉnh và sau một số lựa chọn, hãy chọn V4---v5 và xem điều gì sẽ xảy ra*/

    cout<<"1. Để tiếp tục hỏi màu các đỉnh liền kề của đồ thị"<<endl;
    cout<<"bạn có thể chọn các đỉnh theo danh sách các kết nối đỉnh được đưa ra bên dưới"<<endl;
    cout<<endl;
    cout<<"2. Thoát"<<endl;

    do
    {
        if(isPrime(p1) && isPrime(p2))
        {
            int a,b;
            g.print_graph1();
            cout<<"Nhập 2 số đỉnh để xem màu của chúng: ";
            cin>>a>>b;
            g.check_color_g1(a,b);
        }
        else
        {
            int a,b;
            g.print_graph2();
            cout<<"Nhập 2 đỉnh để xem màu của chúng:";
            cin>>a>>b;
            g.check_color_g2(a,b);
        }
        cout<<"Nhấn phím 1. Để tiếp tục ; 2. Để thoát"<<endl;
        cin>>n;
        cout<<endl;
    }while(n!=2);



    return 0;
}
