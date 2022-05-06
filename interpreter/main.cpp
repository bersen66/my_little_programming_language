#include <iostream>

#include "virtual_machine.h"
#include "instructions.h"
#include "profile.h"


#include <boost/program_options.hpp>


namespace opt = boost::program_options;

int main(int argc, char* argv[]) {

    opt::options_description desc("All options");

    desc.add_options()
            ("filepath,fp", opt::value<std::string>(), "path to file with code")
            ("help,h", "produce help message")
    ;

    opt::variables_map vm;

    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    std::ifstream code(vm["filepath"].as<std::string>());
    VirtualMachine virtual_machine;
    {
        LOG_DURATION("TOTAL:" );
        ProcessInstructions(ReadInstructions(code), virtual_machine);
    }
    code.close();

    for (auto& [key, val] : virtual_machine.GetResults()) {
        std::cout << key << " - " << val->ToString() << std::endl;
    }



    return 0;

}

