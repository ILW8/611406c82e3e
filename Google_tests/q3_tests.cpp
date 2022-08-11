#include "gtest/gtest.h"
#include "../parse_uri.cpp"


TEST(URIParserTestSuite, AuthorityAndPath) {
    std::vector<std::string> parsed = parse_uri("ftp://ftp.is.co.za/rfc/rfc1808.txt");
    std::vector<std::string> expected = {"ftp", "ftp.is.co.za", "/rfc/rfc1808.txt", "", ""};
    EXPECT_EQ(parsed, expected);
}
TEST(URIParserTestSuite, AuthorityAndPath2) {
    std::vector<std::string> parsed = parse_uri("telnet://192.0.2.16:80/");
    std::vector<std::string> expected = {"telnet", "192.0.2.16:80", "/", "", ""};
    EXPECT_EQ(parsed, expected);
}

TEST(URIParserTestSuite, AuthorityOnly) {
    std::vector<std::string> parsed = parse_uri("ftp://ftp.is.co.za");
    std::vector<std::string> expected = {"ftp", "ftp.is.co.za", "", "", ""};
    EXPECT_EQ(parsed, expected);
}

TEST(URIParserTestSuite, PathAbsolute) {
    std::vector<std::string> parsed = parse_uri("something:/someplace/somewhere");
    std::vector<std::string> expected = {"something", "", "/someplace/somewhere", "", ""};
    EXPECT_EQ(parsed, expected);
}

TEST(URIParserTestSuite, PathEmpty) {
    std::vector<std::string> parsed = parse_uri("ftp:");
    std::vector<std::string> expected = {"ftp", "", "", "", ""};
    EXPECT_EQ(parsed, expected);
}
TEST(URIParserTestSuite, PathRootless) {
    std::vector<std::string> parsed = parse_uri("mailto:adam.blake@threatspike.com");
    std::vector<std::string> expected = {"mailto", "", "adam.blake@threatspike.com", "", ""};
    EXPECT_EQ(parsed, expected);
}
TEST(URIParserTestSuite, PathRootless2) {
    std::vector<std::string> parsed = parse_uri("news:comp.infosystems.www.servers.unix");
    std::vector<std::string> expected = {"news", "", "comp.infosystems.www.servers.unix", "", ""};
    EXPECT_EQ(parsed, expected);
}
TEST(URIParserTestSuite, PathRootless3) {
    std::vector<std::string> parsed = parse_uri("tel:+1-816-555-1212");
    std::vector<std::string> expected = {"tel", "", "+1-816-555-1212", "", ""};
    EXPECT_EQ(parsed, expected);
}

TEST(URIParserTestSuite, IPv6Query) {
    std::vector<std::string> parsed = parse_uri("ldap://[2001:db8::7]/c=GB?objectClass?one");
    std::vector<std::string> expected = {"ldap", "[2001:db8::7]", "/c=GB", "objectClass?one", ""};
    EXPECT_EQ(parsed, expected);
}
TEST(URIParserTestSuite, QueryFragment) {
    std::vector<std::string> parsed = parse_uri("http://www.apple.com/store/products?mychoice=macpro#techspecs");
    std::vector<std::string> expected = {"http", "www.apple.com", "/store/products", "mychoice=macpro", "techspecs"};
    EXPECT_EQ(parsed, expected);
}



//TEST(URIParserTestSuite, ExampleDate) {
//    std::vector<std::string> parsed = parse_uri("ftp://ftp.is.co.za/rfc/rfc1808.txt");
//    std::vector<std::string> expected = {"ftp", "ftp.is.co.za", "/rfc/rfc1808.txt", "", ""};
//    EXPECT_EQ(parsed, expected);
//}
//
//TEST(URIParserTestSuite, ExampleDate) {
//    std::vector<std::string> parsed = parse_uri("ftp://ftp.is.co.za/rfc/rfc1808.txt");
//    std::vector<std::string> expected = {"ftp", "ftp.is.co.za", "/rfc/rfc1808.txt", "", ""};
//    EXPECT_EQ(parsed, expected);
//}

