#include "rogerber/Gerber.hpp"
#include "rogerber/GerberExecutor.hpp"
#include <iostream>

using namespace rogerber;

int main(int argc, char *argv[]) {
    Gerber gerber;

    std::string str = "G75*\n"
            "G70*\n"
            "%OFA0B0*%\n"
            "%FSLAX24Y24*%\n"
            "%IPPOS*%\n"
            "%LPD*%\n"
            "%AMOC8*\n"
            "5,1,8,0,0,1.08239X$1,22.5*\n"
            "%\n"
            "%ADD10C,0.0000*%\n"
            "D10*\n"
            "X000100Y000200D02*\n"
            "X004100Y000200D01*\n"
            "X004100Y006700D01*\n"
            "X000100Y006700D01*\n"
            "X000100Y000200D01*\n"
            "X004100Y000200D01*\n"
            "M02*\n"
            "%MOMM*%";

    gerber.Parse(str);

    GerberExecutor executor(gerber);


    std::cout << gerber.Dump();

    return 0;
}