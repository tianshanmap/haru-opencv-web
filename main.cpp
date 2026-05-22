#include "include/httplib.hpp"
#include <string>
#include "modules/photo_handler.h"

using namespace haru;
int main()
{
    // webMain();
    // std::string source = "/Users/developer/T9/travels/2026-01-14_2026-03-25/2026-01-16-2026-01-23-singapore-maleka";
    // std::string destination = "/Users/developer/T9/travels/processed";
    // process_filesystem(source, destination);
    std::string destination = "/Users/developer/T9/travels/processed/2026-01-16-2026-01-23-singapore-maleka/jpeg";
    std::string output = "/Users/developer/T9/travels/processed/2026-01-16-2026-01-23-singapore-maleka/export/malaka.mp4";
    process_photoes(destination,output);
}//
// Created by developer on 2026-05-19.
//
