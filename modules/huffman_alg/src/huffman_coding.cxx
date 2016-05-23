// Copyright 2016 Sergey Shumihin

#include <string>
#include "include/huffman_coding.h"

HuffmanCoding::HuffmanCoding() : _message("") {}

string HuffmanCoding::operator()(int argc, const char ** argv) {
    if (argc == 1) {
        help(argv[0]);
        return _message;
    } else if (argc == 2) {
        _operation = argv[1];
        if (_operation == "-h" || _operation == "-help")
            help(argv[0]);
        else
            _message = "Should be 3 or more arguments.\n Use -h for help";
        return _message;
    }

    _operation = argv[1];
    if (_operation == "-c") {
        if (argc == 3) {
            Huff huf;
            FreqMap map;
            map = huf.readString(argv[2]);
            huf.coding(map);
            _message = huf.printTable();
        } else {
            _message = "Encode must have 2 arguments.\n";
        }
    } else if (_operation == "-d") {
        if (argc >= 5) {
            try {
                Huff huf;
                TableMap table;
                string toParse("");
                string toDecode(argv[2]);
                for (int i = 3; i < argc; i++)
                    toParse += (argv[i] + string(" "));
                table = huf.fillTable(toParse);
                _message = huf.decoding(table, toDecode);
            }
            catch (string str) {
                _message = str;
            }
        } else {
            _message = "Decode must have 4 or more arguments.\n";
        }
    } else {
        _message = "Wrong argument.\n Use -h for help.";
    }
    return _message;
}

void HuffmanCoding::help(const char * appname) {
    _message = std::string("")
        + "This application work with Huffman coding.\n" +
        "To work with it specify what action should be performed in format:\n"
        + "# " + appname + " <operation> " + " <string> \n\n"

        + "<operator> must be one of:\n"
        + "-c \tIf you want to encode some string.\n"
        + "For example:\t -c test\n"
        + "This command will code word \"test\" using huffman code\n\n"

        + "-d \tIf you want to decode some code.\n"
        + "After -d argument, you must enter, code to decode\n"
        + "and code for all using symbol.\n"
        + "Using format: \t -d <code_to_decode> <code> <symbol> ...\n"
        + "For example:\t -d 010110 10 a 11 b 0 c\n"
        + "This command will decode \"010110\" into"
        + "\"cabñc\" using huffman code\n\n";
}
