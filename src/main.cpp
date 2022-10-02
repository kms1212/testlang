#include <iostream>

#include "scanner.hpp"
#include "parser.hpp"
#include "ast.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(1);
    }

    char* path = argv[1];
    std::cerr << "Reading from file " << path << std::endl;
    FILE *fp = fopen(path, "r");
    if (!fp) {
        std::cerr << "Open failed on '" << path << "'" << std::endl;
        exit(5);
    }
    std::cerr << "Opened " << argv[1] << std::endl;

    ast::ASTNode* root;

    yy::Lexer lexer(fp);
    yy::parser parser(lexer, &root);

    parser.parse();

    std::cout << root->str() << std::endl;
    return 0;
}