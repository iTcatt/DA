#include <iostream>
#include <unistd.h>
#include <string>
#include <sstream>

// -c, -d, -k, -l, -r, -t, -1, -9.
struct Flags {
    bool output = false; // -c
    bool decompress = false; // -d
    bool info = false; // -l выводит информацию сколько бит в
    bool keep = false; // -k не удаляет заархивированный файл
    bool recursive = false; // -r рекурсивно сжимает все файлы в директории и в поддирикториях
    bool test = false; // -t проверка, что содержимое архива не повреждено
    bool help = false; // -h инструкция по работе с программой
    bool fast = false; // -1 high speed low effective
    bool best = false; // -9 low speed high effective
};

std::string helpMessage = R"(
Usage: yazip [OPTION]... [FILE]...
Compress or uncompress FILEs (by default, compress FILES in-place).

Mandatory arguments to long options are mandatory for short options too.

-c, --stdout      write on standard output, keep original files unchanged
-d, --decompress  decompress
-f, --force       force overwrite of output file and compress links
-S, --suffix=SUF  use suffix SUF on compressed files
--synchronous synchronous output (safer if system crashes, but slower)
-t, --test        test compressed file integrity

-1, --fast        compress faster
-9, --best        compress better

With no FILE, or when FILE is -, read standard input.

)";

std::string errorMessage(int flag) {
    std::stringstream msg;
    msg << "yazip: invalid option --";
    msg << "'" << flag << "'";
    return msg.str();
}

int main(int argc, char* argv[]) {
    int opt;
    Flags config;

    while ((opt = getopt(argc, argv, "cdklrt19")) != -1) {
        switch (opt) {
            case 'c':
                config.output = true;
                break;
            case 'd':
                config.decompress = true;
                break;
            case 'k':
                std::cout << "Don't know" << std::endl;
                break;
            case 'r':
                config.recursive = true;
                break;
            case 1:
                config.fast = true;
                break;
            case 9:
                config.best = true;
                break;
            default:
                std::cerr << errorMessage(opt) << std::endl;
                return 1;
        }
    }
    return 0;
}
