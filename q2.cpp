#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int main(int argc, char *argv[]) {
    // first command line argument should be file path
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " FILE_PATH" << endl;
        cout << "Expected 1 argument, got " << argc - 1 << endl;
    }


    ifstream infile;
    try {
        infile.open(argv[1], ios::binary);
        if (infile.fail()) {
            cout << "Could not open '" << argv[1] << "'";
            return -1;
        }
    }
    catch (const ifstream::failure &e) {
        cout << "Could not open '" << argv[1] << "'";
        return -1;
    }

    // check if file matches against known magic number
    // pair: offset, signature bytes
    vector<pair<int, vector<int>>> magic_numbers = {
            {0, {0x54, 0x44, 0x45, 0x46}},  // encrypted telegram desktop file
            {0, {0x65, 0x6E, 0x63, 0x72, 0x63, 0x64, 0x73, 0x61}}  // Macintosh encrypted Disk image (v2)
    };

    for (pair magic_num: magic_numbers) {
        bool sig_matched = true;
        int signature_length = static_cast<int>(magic_num.second.size());
        infile.seekg(magic_num.first + signature_length);
        if (infile.eof()) {
            continue;
        }

        infile.seekg(magic_num.first);
        for (int i = 0; i < signature_length; i++) {
            if (magic_num.second[i] < 0) {
                infile.get();
                continue;  // negative int in signature indicates any byte may be present
            }

            if (infile.get() != magic_num.second[i]) {
                sig_matched = false;
                break;
            }
        }

        if (sig_matched) {
            cout << "File matched a known magic number of an encrypted file format.";
            return 0;
        }

    }

    // measure file entropy
//    vector<int> buckets(255, 0);
//
//    infile.seekg(0, ios_base::end);
//    unsigned int file_length = infile.tellg();
//    infile.seekg(0, ios_base::beg);
//
//    int current = infile.get();
//    while (!infile.eof()){
//        buckets[current]++;
//        current = infile.get();
//    }
//
//    double entropy = 0.;
//    for (int byte_count:buckets){
//        if(byte_count){
//            entropy -= static_cast<double>(byte_count)/file_length * log2(static_cast<double>(byte_count)/file_length);
//        }
//    }
//    entropy /= 8;
//    cout << "File entropy: " << entropy << endl;

    return 0;

}
