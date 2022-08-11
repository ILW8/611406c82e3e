
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


// read in Windows PE file and determine if file is an SSH client
int main(int argc, char *argv[]) {
    // first command line argument should be file path to a Windows PE file
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


    // first determine if file is Windows PE using its PE signature
    unsigned int pe_signature_offset = 0;
    infile.seekg(0x3c);
    for (int byte = 0; byte < 4; byte++) {
        pe_signature_offset |= infile.get() << byte * 8;
    }

    char win_pe_signature[] = {'P', 'E', '\0', '\0'};
    infile.seekg(pe_signature_offset);
    for (char byte: win_pe_signature) {
        if (infile.get() != byte) {
            cout << "File not a Windows Portable Executable";
            return 1;
        }
    }


    // locate required algorithm names within executable's strings according to rfc4253
    // this method may identify executables that may not be an ssh client but implements an ssh client in some capacity,
    // i.e. PuTTY or ffmpeg
    // this method is also not very memory efficient...
    vector<string> required_algorithms = {"3des-cbc",
                                          "hmac-sha1",
                                          "diffie-hellman-group14-sha1",
                                          "diffie-hellman-group1-sha1",
                                          "ssh-dss"};
    infile.seekg(0, ios_base::end);
    unsigned int file_length = infile.tellg();
    char *buffer = new char[file_length];

    infile.seekg(0, ios_base::beg);
    infile.read(buffer, file_length);
    string executable_data(buffer, file_length);

    for (const string &required_algo: required_algorithms) {
        if (string::npos == executable_data.find(required_algo)) {
            cout << "Missing required algorithm " << "'" << required_algo << "'";
            return 1;
        }
    }

    cout << "File is likely an SSH client or contains an SSH client" << endl;
    return 0;
}
