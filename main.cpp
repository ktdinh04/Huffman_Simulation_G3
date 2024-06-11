#include <iostream>
#include <vector>
#include <string.h>
#include <unordered_map>
#include <queue>
#include <fstream>
#include "helper.h"
#include "Nen_File.h"

using namespace std;

struct HuffmanData {
    char ki_tu;
    double xac_suat;
    string tu_ma;
    int do_dai;
};
vector<HuffmanData> danh_sach_ma;



void TuMa(string input_path, vector<string> &huffmanCodesArray, vector<HuffmanData> &danh_sach_ma) {
    string van_ban;

    ifstream MyReadFile(input_path);
    if (!MyReadFile) {
        cout << "Khong tim thay file";
        return;
    }
    getline(MyReadFile, van_ban);

    Huffman cay_ma;
    string output_path = tach_extension(input_path) + "_giainen" + ".txt";

    Node* root = cay_ma.tao_cay_Huffman(van_ban, output_path);

    // Bắt đầu quá trình mã hóa và nén:
    unordered_map<char, string> huffmanCode;
    cay_ma.ma_hoa(root, "", huffmanCode);

    // Lưu tần suất ký tự
    cay_ma.lay_tan_suat_ky_tu();
    vector<pair<char, int>> tan_suat_ky_tu = cay_ma.get_tan_suat_ky_tu();

    // Tính tổng số ký tự
    int tong_ki_tu = van_ban.size();

    // Lưu thông tin mã hóa vào vector
    for (auto pair : tan_suat_ky_tu) {
        char ki_tu = pair.first;
        double xac_suat = double(pair.second) / tong_ki_tu;
        string tu_ma = huffmanCode[ki_tu];
        int do_dai = tu_ma.size();

        HuffmanData data = {ki_tu, xac_suat, tu_ma, do_dai};
        danh_sach_ma.push_back(data);

        huffmanCodesArray.push_back(tu_ma);
    }
}


vector<string> huffmanCodesArray;
void hien_thi_danh_sach_ma(vector<HuffmanData> &danh_sach_ma) {
    printf("+------+------------+-------------------+----------------+\n");
    printf("| %-4s | %-10s | %-17s | %-14s |\n", "Ki tu", "Xac suat", "Tu ma", "Do dai tu ma");
    printf("+------+------------+-------------------+----------------+\n");

    for (const auto &data : danh_sach_ma) {
        printf("| %-4c | %-10f | %-17s | %-14d |\n", data.ki_tu, data.xac_suat, data.tu_ma.c_str(), data.do_dai);
    }

    printf("+------+------------+-------------------+----------------+\n");
}


int main() {
    
 
    ofstream outFile("file.txt");
    string line;
    cout << "Nhap du lieu (An Enter de ket thuc):" << endl;

    while (true) {
        getline(cin, line);

        if (line.empty()) {
            break;
        }

        outFile << line << endl;
    }

    outFile.close();
    vector<string> huffmanCodesArray;
    vector<HuffmanData> danh_sach_ma;
    TuMa("file.txt", huffmanCodesArray, danh_sach_ma);
    hien_thi_danh_sach_ma(danh_sach_ma);
}   
