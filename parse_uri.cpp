#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <string> parse_uri(string uri) {
    string scheme;
    string authority;
    string path;
    string query;
    string fragment;
    unsigned long search_index;

    // parse scheme
    search_index = uri.find(':');
    if (search_index == string::npos || search_index == 0) {
        uri = "";
    }
    if (!isalpha(uri[0])) {
        uri = "";  // scheme didn't start with ALPHA
    }
    for (char c: uri.substr(1, search_index - 1)) {
        if (!isalpha(c) && !isdigit(c) && c != '+' && c != '-' && c != '.') {
            uri = "";
        }
    }
    scheme = uri.substr(0, search_index);
    uri = uri.substr(search_index + 1);


    // get fragment (if any)
    search_index = uri.find('#');
    if (search_index != string::npos) {
        fragment = uri.substr(search_index + 1);
    }
    uri = uri.substr(0, min(uri.size(), search_index));

    // get query (if any)
    search_index = uri.find('?');
    if (search_index != string::npos) {
        query = uri.substr(search_index + 1);
    }
    uri = uri.substr(0, min(uri.size(), search_index));


    // parse hier-part
    search_index = uri.find('/');
    if (search_index == 0 && uri[search_index + 1] == '/') {  // "//" authority path-abempty
        uri = uri.substr(search_index + 2);
        search_index = uri.find('/');
        authority = string::npos == search_index ? uri : uri.substr(0, search_index);
        if (string::npos != search_index) {  // has path
            uri = uri.substr(search_index);
            path = uri;
        }
    } else if (search_index == 0) {  // path-absolute
        path = uri.substr(search_index);
    } else {  // path-rootless or path-empty
        path = uri;
    }


    cout << "Scheme: '" << scheme << "'" << endl;
    cout << "Authority: '" << authority << "'" << endl;
    cout << "Path: '" << path << "'" << endl;
    cout << "Query: '" << query << "'" << endl;
    cout << "Fragment: '" << fragment << "'" << endl;

    return vector<string>{scheme, authority, path, query, fragment};
}