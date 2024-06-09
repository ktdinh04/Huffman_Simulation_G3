#include <math.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <unordered_map>
#include <queue>
#include <fstream>


using namespace std;
//Cac ham support
template<typename arr_type>
void in_mang(vector <arr_type> arr) {
  for(int i = 0; i<arr.size(); i++) {
    cout<<arr[i]<<" ";
  }
  cout<<endl;
}

double luong_tin_rieng(double p_xi) {
  return -(log2(p_xi));
}

// Ham kiem tra gia tri dau vao co phai la expression khong
bool include_expression(string dau_vao) {
  for(int i = 0; i<dau_vao.size(); i++) {
    if(dau_vao[i] == '/') {
      return true;
    }
  }
  return false;
}

// Ham tinh toan gia tri dau vao neu no la mot bieu thuc
// Trong ham co su dung ham stod() la chuyen doi tu string sang double
double calc_expression(string dau_vao) {
  if(include_expression(dau_vao)) {
    int operator_index;
    string tu ="";
    string mau= "";

    for(int i = 0; i<dau_vao.size(); i++) {
      if(dau_vao[i] != '/') {
        tu += dau_vao[i];
      }
      else {
        operator_index = i;
        break;
      }
    }

    for(int i = operator_index+1; i<dau_vao.size();i++) {
      mau += dau_vao[i];
    }

    double result = stod(tu)/stod(mau);
    return result;

  }else {
    return stod(dau_vao);
  }
}

double binary_to_decimal(string binary) {
  double sum = 0;
  for(int i = 0; i<binary.size(); i++) {
    if(binary[i] == '1') {
      sum += pow(2,binary.size()-i-1);
    }
  }
  return sum;
}

void binary_sort(vector<string> &mang) {
    for(int i = 0; i<mang.size() - 1; i++) {
      for(int j = i+1; j<mang.size(); j++) {

        bool dk1 = (binary_to_decimal(mang[i]) >binary_to_decimal(mang[j])&&mang[i].size() == mang[j].size());
        bool dk2 = mang[i].size() > mang[j].size();

        if(dk1||dk2) {
          swap(mang[i], mang[j]);
        }
      }
    }
}

template<typename kieu_numeric>
void sort(vector<kieu_numeric> &mang) {
  for(int i =0; i<mang.size()-1; i++) {
    for(int j = i+1; j<mang.size(); j++) {
      if(mang[i] > mang[j]) {
        swap(mang[i],mang[j]);
      }
    }
  }
}

bool isPre(string ma1, string ma2) {
  if(ma1.size() < ma2.size()) {
    string prefix = "";
    for(int i =0; i<ma1.size(); i++) {
      prefix +=ma2[i];
    }
    if(ma1 == prefix) {
      return true;
    }
  }
  if(ma1.size() > ma2.size()) {
    string prefix = "";
    for(int i =0; i<ma2.size(); i++) {
      prefix +=ma1[i];
    }
    if(ma2 == prefix) {
      return true;
    }
  }
  return false;
}

string take_rest(string ma1, string ma2) {
  string rest="";

  if(isPre(ma1,ma2)) {
    if(ma1.size() > ma2.size()) {
      for(int i = ma2.size(); i<ma1.size(); i++) {
        rest +=ma1[i];
      }
    }
    else {
      for(int i = ma1.size(); i<ma2.size(); i++) {
        rest +=ma2[i];
      }
    }
  }

  return rest;
}

bool includes(vector<string> arr, string key) {
  for(int i = 0; i<arr.size(); i++) {
    if(key == arr[i]) {
      return true;
    }
  }
  return false;
}

template <typename kieu_dl>
bool isSame(vector <kieu_dl> arr1, vector<kieu_dl> arr2) {
  if(arr1.size() != arr2.size()) {
    return false;
  }
  for(int i = 0; i<arr1.size(); i++) {
    if(arr1[i] != arr2[i]) {
      return false;
    }
  }
  return true;
}

string tach_extension(string path) {
  string result_path = "";
  int vi_tri_extension;
  for(int i = path.size()-1; i>=0; i--) {
    if(path[i] == '.') {
      vi_tri_extension = i;
      break;
    }
  }

  for(int i = 0; i<vi_tri_extension; i++) {
    result_path += path[i];
  }

  return result_path;
}

//Ma hoa Huffman algorithm
struct Node {
  char ki_tu;
  int tan_so;
  Node *left, *right;
};

Node* tao_Node(char ki_tu, int tan_so, Node *left, Node *right) {

  Node* new_node= new Node();

  new_node->ki_tu = ki_tu;
  new_node->tan_so = tan_so;
  new_node->left = left;
  new_node->right = right;

  return new_node;
}


// Định nghĩa compare function dùng trong priority queue
struct comp {
  bool operator()(Node* left, Node* right){
    // Định nghĩa toán tử so sánh để set cho priority queue có phần tử với tần số thấp nhất sẽ ở độ ưu tiên cao nhất.
    return left->tan_so > right->tan_so;
  }
};

class Huffman {
  unordered_map<char, int> bang_tan_so;
  public:
    void ma_hoa(Node* root, string danh_so, unordered_map<char, string> &huffManCode);
    void giai_ma(Node* root, int &index, string encoded_str);
    Node* tao_cay_Huffman(string van_ban, string output_path);
    Node* tao_cay_Huffman(priority_queue<Node*, vector<Node*>, comp> container);
    double ty_so_nen(unordered_map<char, string> huffmanCode);
};


void Huffman::ma_hoa(Node* root, string ma, unordered_map<char, string> &huffManCode) {
  
  // Kiểm tra nếu như không còn nút để duyệt
  // thì dừng lại quá trình duyệt và mã hóa
  if(root == nullptr) return;

  // Nếu chạm đến nút lá
  // Thì gán mã hóa cho kí tự trong danh sách mã huffManCode
  if(!root->left && !root->right) {
    huffManCode[root->ki_tu] = ma;
  }

  // Dùng hồi quy để duyệt cây mã huffMan
  ma_hoa(root->left, ma + "0", huffManCode);
  ma_hoa(root->right, ma + "1", huffManCode);

}

void Huffman::giai_ma(Node* root, int &index, string encoded_str) {

  if(root == nullptr) {
    return ;
  }

  // Nếu chạm tới nút kí tự
  if (!root->left && !root->right)
	{
		cout << root->ki_tu;
		return;
	}

	index++;

	if (encoded_str[index] =='0')
		giai_ma(root->left, index, encoded_str);
	else
		giai_ma(root->right, index, encoded_str);
}

Node* Huffman::tao_cay_Huffman(string van_ban, string output_path) {

  // Bảng đếm tần số xuất hiện của các kí tự
  // unordered_map<char, int> bang_tan_so;
  for(char ch: van_ban) {
    bang_tan_so[ch]++;
  }
  // Ghi lại key để giải mã file được nén
  ofstream OutputFile(output_path);
  OutputFile<<bang_tan_so.size()<<endl;
  for (auto pair: bang_tan_so) {
    char ki_tu;
    ki_tu = pair.first;
    if(ki_tu == ' ') {
      ki_tu = '_';
    }
    OutputFile<<ki_tu<<" "<<pair.second<<" ";
  }
  // Tạo container để lưu trữ tần số các kí tự
  // Sao cho các kí tự có tần số nhỏ nhất
  // Luôn luôn được ưu tiên lấy ra đầu
  priority_queue<Node*, vector<Node*>, comp> container;

  // Tạo các nút lá chứa kí tự cần mã hóa
  // Và thêm chúng vào container
  for(auto pair: bang_tan_so) {
    container.push(tao_Node(pair.first, pair.second, nullptr, nullptr));
  }


  // Tiến hành xây dựng cây mã
  while(container.size() !=1) {
    
    // lấy ra 2 nút có tần số nhỏ nhất
    // sau đó khởi tạo nút mới
    // Có tông tần số = tần số 2 nút lấy ra
    // Lưu lại vào container.
    Node *left = container.top(); container.pop();
    Node *right = container.top(); container.pop();

    int sum = left->tan_so + right->tan_so;
    container.push(tao_Node('\0', sum, left, right));
  }

  

  // Lấy ra root của cây mã
  Node* root = container.top();

  return root;
}


Node* Huffman::tao_cay_Huffman(priority_queue<Node*, vector<Node*>, comp> container) {

  // Tạo các nút lá chứa kí tự cần mã hóa
  // Và thêm chúng vào container

  // Tiến hành xây dựng cây mã
  while(container.size() !=1) {
    
    // lấy ra 2 nút có tần số nhỏ nhất
    // sau đó khởi tạo nút mới
    // Có tông tần số = tần số 2 nút lấy ra
    // Lưu lại vào container.
    Node *left = container.top(); container.pop();
    Node *right = container.top(); container.pop();

    int sum = left->tan_so + right->tan_so;
    container.push(tao_Node('\0', sum, left, right));
  }

  // Lấy ra root của cây mã
  Node* root = container.top();

  return root;
}

double Huffman::ty_so_nen(unordered_map<char, string> huffmanCode) {
  int tong_ki_tu = 0;
  for(auto pair:bang_tan_so) {
    tong_ki_tu += pair.second;
  }
  
  // Tính toán entropy
  double Hx = 0;
  for(auto pair:bang_tan_so) {
    double p_xi = double(pair.second)/tong_ki_tu;
    Hx += p_xi*(luong_tin_rieng(p_xi));
  }

  // Tính toán độ dài trung bình từ mã
  double l_tb = 0;
  for(auto pair: huffmanCode) {
    double p_xi = double(bang_tan_so[pair.first])/tong_ki_tu;
    l_tb += p_xi*((pair.second).size());
  }

  
  return Hx/l_tb;
}

//Nen file, tinh ti so nen, giai nen
void nen_file(string input_path) {
  string van_ban;

  ifstream MyReadFile(input_path);
  if(!MyReadFile) {
    cout<<"Khong tim thay file";
    return;
  }
  getline(MyReadFile, van_ban);

  Huffman cay_ma;
  string output_path = tach_extension(input_path) + "_giainen" +".txt";

  Node* root = cay_ma.tao_cay_Huffman(van_ban, output_path);

  // Bắt đầu quá trình mã hóa và nén:
  unordered_map<char, string> huffmanCode;
  cay_ma.ma_hoa(root, "", huffmanCode);

  cout<<"Bang ma Huffman: \n"<<'\n';
  for(auto pair: huffmanCode) {
    cout<<pair.first<<" "<<pair.second<<'\n';
  }

  // Tính toán tỷ số nén:
  cout<<"\nTy so nen: "<<cay_ma.ty_so_nen(huffmanCode);
  

  // Mã hóa văn bản với bảng mã đã lập
  string vb_da_ma_hoa = "";
  for(char ki_tu: van_ban) {
    vb_da_ma_hoa += huffmanCode[ki_tu];
  }

  // Ghi đoạn văn sau khi đã được mã hóa ra file
  ofstream OuputFile(output_path,fstream::app);

  OuputFile<<vb_da_ma_hoa;
  OuputFile.close();

}


void giai_nen(string input_path) {

  // Mở file cần giải nen và lấy ra key
  ifstream InputFile(input_path);
  if(!InputFile) {
    cout<<"Khong tim thay file!";
    return;
  }
  char ki_tu;
  int freq;
  int num_key;

  InputFile>>num_key;

  unordered_map<char, int> bang_tan_so;
  priority_queue<Node*, vector<Node*>, comp> container;
  for(int i = 0; i<num_key; i++) {

    InputFile>>ki_tu;
    if(ki_tu == '_') {
      ki_tu = ' ';
    }
    InputFile>>freq;
   
    container.push(tao_Node(ki_tu, freq, nullptr, nullptr));
  }

  // Lấy ra đoạn văn đã được mã hóa để giải mã
  string doan_ma_hoa;
  getline(InputFile,doan_ma_hoa);

  // Loại bỏ dấu cách bị thừa ở đầu 
  // đoạn văn trong quá trình mã hóa
  string doan_ma_hoa_moi = "";
  for(int i =1; i<doan_ma_hoa.size(); i++) {
    doan_ma_hoa_moi += doan_ma_hoa[i];
  }
 
  Huffman cay_ma;
  Node * root = cay_ma.tao_cay_Huffman(container);

  // Thực hiện giải mã
  int index = -1;
	cout << "\n Noi dung cua file da duoc giai nen: \n";
	while (index < (int)doan_ma_hoa.size() - 2) {
		cay_ma.giai_ma(root, index, doan_ma_hoa_moi);
	}
}

int main() { 
    nen_file("test.txt");
    giai_nen("D:/HUST/2023.2/LTTT/Infomation-Theory-Small-Project-master/Infomation-Theory-Small-Project-master/test_giainen.txt");
    
}


