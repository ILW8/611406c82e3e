#include <iostream>
#include <string>
#include <vector>
#include "parse_uri.h"

using namespace std;


int main(int argc, char *argv[]) {
    string uri;
    switch (argc) {
        case 1:
            // read from stdin
            cout << "URI to parse: ";
            getline(cin, uri);
            break;
        case 2:
            // use 2nd argument
            uri = argv[1];
            break;
        default:
            // print usage statement
            cout << "Usage: " << argv[0] << " [URI]" << endl;
            cout << "Expected 0 or 1 argument, got " << argc - 1 << endl;
            return -1;
    }

    if (uri.empty()) {
        return 0;
    }

    /*       some URI examples:
     *       ftp://ftp.is.co.za/rfc/rfc1808.txt
     *       http://www.ietf.org/rfc/rfc2396.txt
     *       ldap://[2001:db8::7]/c=GB?objectClass?one

     *       news:comp.infosystems.www.servers.unix
     *       tel:+1-816-555-1212
     *       telnet://192.0.2.16:80/
     *       urn:oasis:names:specification:docbook:dtd:xml:4.1.2
     *       http://www.apple.com/store/products?mychoice=macpro#techspecs
     *       mailto:adam.blake@threatspike.com
     */

    parse_uri(uri);
    return 0;
}
