#include "rogerber/Gerber.hpp"
#include "rogerber/GerberProcessor.hpp"
#include <iostream>

using namespace rogerber;

int main(int argc, char *argv[]) {
    Gerber gerber;
/*
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
*/
	std::string str = "G04 Ucamco ex. 1: Twosquare boxes*\n"
			"%FSLAX25Y25*%\n"
			"%MOMM*%\n"
			"%TF.Part,Other,example*%\n"
			"%LPD*%\n"
			"%ADD10C,0.010*%\n"
			"D10*\n"
			"X0Y0D02*\n"
			"G01*\n"
			"X500000Y0D01*\n"
			"Y500000D01*\n"
			"X0D01*\n"
			"Y0D01*\n"
			"X600000D02*\n"
			"X1100000D01*\n"
			"Y500000D01*\n"
			"X600000D01*\n"
			"Y0D01*\n"
			"M02*\n";

	gerber.Load("D:\\msys64\\home\\mroszko\\qieda\\src\\test\\gerbers\\polarties-apertures.gbr");
    //gerber.Parse(str);

	GerberProcessor executor(gerber);


    std::cout << gerber.Dump() << std::flush;

	try
	{
		executor.Execute();
	}
	catch(GerberException e)
	{
		std::cerr << "Parsing error encountered: " << e.what() << std::endl;
	}


    return 0;
}