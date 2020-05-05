//
// Created by Igor Frank on 30.04.20.
//

#include "Args.h"
void Args::parseArgs(int argc, char **argv) {
  runPath = std::string(argv[0]);
  for (auto i = 1; i < argc; ++i) {
    std::string tmp = argv[i];
    if (tmp == "-h" || tmp == "--h") {
      help = true;
      break;
    }
    if (tmp == "-in") {
      if (inputFile.has_value())
        throw std::invalid_argument("Duplicate \"-in\" argument!");
      inputFile = argv[++i];
    } else if (tmp == "-out") {
      if (outputFile.has_value())
        throw std::invalid_argument("Duplicate \"-out\" argument!");
      outputFile = argv[++i];
    } else if (tmp == "-m=SIMPLE") {
      if (method.has_value())
        throw std::invalid_argument("Duplicate \"-m=XXX\" argument!");
      method = MethodType::SIMPLE;
    } else if (tmp == "-m=REGULAR") {
      if (method.has_value())
        throw std::invalid_argument("Duplicate \"-m=XXX\" argument!");
      method = MethodType::REGULAR;
    } else if (tmp == "-v") {
      visualize = true;
    } else if (tmp == "-go") {
      origin.x = std::stof(argv[++i]);
      origin.y = std::stof(argv[++i]);
      origin.z = std::stof(argv[++i]);
    } else if (tmp == "-gs") {
      size.x = std::stof(argv[++i]);
      size.y = std::stof(argv[++i]);
      size.z = std::stof(argv[++i]);
    } else if (tmp == "-t") {
      if (threshold.has_value())
        throw std::invalid_argument("Duplicate \"-t\" argument!");
      threshold = std::stof(argv[++i]);
    } else {
      throw std::invalid_argument("Unknown argument " + std::string(argv[i]) + " !");
    }
  }
}
std::string Args::getHelp() {
  std::string help("Demo app for extracting surface from volumetric data.\n"
                   "Usage:\n"
                   "\t-in [input_file_path] (.vox or JSON)\n"
                   "\t-out [input_file_path] (.obj file)\n"
                   "\t-v toggle visualization\n"
                   "\t-m=[REGULAR/SIMPLE] chooses which method to use (REGULAR is deafult)\n"
                   "\t-t [float] threshold for QEF solver in REGUALR method\n"
                   "\t-go [float float float] grid origin for DC compute\n"
                   "\t-gs [float float float] size of grid for DC compute\n");
  return help;
}
