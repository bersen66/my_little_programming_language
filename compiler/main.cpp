#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "profile.h"
#include "token.h"
#include "grammar.h"
#include <boost/program_options.hpp>


namespace opt = boost::program_options;

std::string GetProgramText(std::istream &input) {
    return {std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>()};
}

int main(int argc, char *argv[]) {

    // std::ios_base::sync_with_stdio(false);
    // LOG_DURATION("TOTAL: ")

    opt::options_description desc("All options");

    desc.add_options()
            ("file_path,fp",  opt::value<std::string>(), "path to compile file")
            ("output_path,o", opt::value<std::string>()->default_value("out.rpn"), "path to output file")
            ("lexer_res,l", opt::value<bool>()->default_value(false), "show lexing results")
            ("parser_res,p", opt::value<bool>()->default_value(false), "show parsing results")
            ("help", "produce help message")
   ;

    opt::variables_map vm;

    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }


    std::ifstream input(vm["file_path"].as<std::string>());

    if (!input.is_open()) {
        std::cerr << "No FILE!" << std::endl;
        std::terminate();
    }

    std::string text = GetProgramText(input);
    input.close();
    TokenStream stream(SplitIntoTokens(text));

    if (vm["lexer_res"].as<bool>()) {
        for (auto &token: SplitIntoTokens(text)) {
            std::cout << token.value << " " << token.line_number << std::endl;
        }
    }



    //LOG_DURATION("Parse time: ");
    NontermHolder lang = MakeNonterminal(Nonterminal::Type::LANG);
    lang->ParseFrom(stream);

    std::ofstream output("out.rpn");
    lang->GenerateRPN(output);
    output.close();


    if (vm["parser_res"].as<bool>()) {
        std::cout << lang->ToString();
    }

    return 0;
}
