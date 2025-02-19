#include "assembler.h"

int main(int argc, char** argv){
    
    // assuming that assembly source file is passed to this assembler as first argument
    // assuming format for input argparse to be:
    //     SimpleAssembler -file source.asm -out source.exe
    const char* argparse_executable = argv[0];
    const char* argparse_file_flags = argv[1];
    const char* argparse_source_nme = argv[2];
    const char* argparse_outs_flags = argv[3];
    const char* argparse_output_nme = argv[4];
    const char* argparse_paths_type = argv[5];

    char _curr_working_directory[1024]; // for file read/write
    char* _cwd_status = get_cwd(_curr_working_directory, 1024);

    char _source_file_path[1024];
    char _output_file_path[1024];
    if (strcmp(argparse_paths_type, "-rel")){
        strcpy(_source_file_path, _curr_working_directory);
        strcpy(_output_file_path, _curr_working_directory);
        strcat(_source_file_path, PATH_SEPERATOR);
        strcat(_output_file_path, PATH_SEPERATOR);
        strcat(_source_file_path, argparse_source_nme);
        strcat(_output_file_path, argparse_source_nme);
    }
    else if (strcmp(argparse_paths_type, "-abs")){
        strcpy(_source_file_path, argparse_source_nme);
        strcpy(_output_file_path, argparse_output_nme);
    }
    

    FILE* SOURCE = fopen(_source_file_path, "r");
    if (SOURCE == NULL){
        trace_cstm_error(_source_file_path, "specified file path not found.");
        return 1;
    }

    char _source_file_line[256];
    unsigned int _all_lines = 1;
    unsigned int _rel_lines = 1;
    Line* _source_all_lines = (Line*)calloc(_all_lines,sizeof(Line));

    while (fgets(_source_file_line, sizeof(_source_file_line), SOURCE) != NULL) {
        _rel_lines += 1;
        if(strcmp(_source_file_line, "\n") == 0)
            continue;
            
        char *colon_pos = strchr(_source_file_line, ':');
        if (colon_pos == NULL){
            _all_lines += 1;
            _source_all_lines = realloc(_source_all_lines, (int)sizeof(Line)*_all_lines);
            Line _current;
            _current.lNo = _rel_lines-1;
            _current.lType = TEXTS;
            _current.content = strdup(_source_file_line);
            _current.aAd = 0;
            _source_all_lines[_all_lines-1] = _current;
        }
        else {
            _all_lines += 2;
            _source_all_lines = realloc(_source_all_lines, (int)sizeof(Line)*_all_lines);
            Line _current;
            _current.lNo = _rel_lines-1;
            _current.lType = TEXTS;
            _current.content = strdup(colon_pos+1);
            _current.aAd = 0;
            _source_all_lines[_all_lines-1] = _current;
            Line _label;
            colon_pos[0] = '\0';
            _label.lNo = _rel_lines-1;
            _label.lType = LABEL;
            _label.content = strdup(_source_file_line);
            _label.aAd = (_rel_lines-1)*4;
            _source_all_lines[_all_lines-2] = _label;
        }
    }
    
    for (int i = 1; i < _all_lines; i++){
        Line line = _source_all_lines[i];
        // printf("%d %d %s\n", line.lNo, line.lType, line.content);
        bool a = isLineSyntacticallyCorrect(line);
        bool b = isLineLexicallyCorrect(line);
        printf("this line is %d %d\n", a, b);
    }


    free(_source_all_lines);
    fclose(SOURCE);
    return 0;
}