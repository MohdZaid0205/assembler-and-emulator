#include "assembler.h"


BYTECODE Instruction_to_ByteCode(Line line, Line arr[], int length) {
    char* lineContent = (char*)line.content;
    char words[10][10];
    char delimiters[] = { ' ',',', '\0' };
    lineContent[strcspn(lineContent, "\n")] = '\0';
    string_splitter(lineContent, words, delimiters);
    Instruction instruction1 = instruction_encoding(words[0]);
    const char* instructionType = instruction1.type;
    
    if (strcmp(instructionType, "R") == 0) {
        return translateRType(words[0], words[2], words[3], words[1]);
    }
	if (strcmp(instructionType, "I") == 0) {
        if (strcmp(words[0], "lw") == 0) {
            char delimiters2[] = { '(', ')', '\0' };
            char words2[10][10];
            words[2][strcspn(words[2], "\n")] = '\0';
            string_splitter(words[2], words2, delimiters2);
			return translateIType(words[0], words2[1], words2[0], words[1]);
        }
		return translateIType(words[0], words[2], words[3], words[1]);
	}
	if (strcmp(instructionType, "S") == 0) {
        char delimiters2[] = { '(', ')', '\0' };
        char words2[10][10];
        words[2][strcspn(words[2], "\n")] = '\0';
        string_splitter(words[2], words2, delimiters2); 
        return translateSType(words[0], words2[1], words[1], words2[0]);
	}
	if (strcmp(instructionType, "B") == 0) {
        char* imm;
        if (!is_valid_immediate(words[3], B))
            imm = calculate_label_rAd(words[3], line.aAd, arr, length);
		else
			imm = words[3];
		return translateBType(words[0], words[1], words[2], imm);// words[3] is the label value/ immediate
	}
	if (strcmp(instructionType, "J") == 0) {
        char* imm;
        if (!is_valid_immediate(words[2], J)) {
            imm = calculate_label_rAd(words[2], line.aAd, arr, length);
        }
        else {
            imm = words[2];
        }
		return translateJType(words[0], imm, words[1]); // words[2] is the label value/ immediate
	}
}


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

    //const char* argparse_source_nme = "../temp/example.txt";
    //const char* argparse_output_nme = "../temp/output.txt";
    //const char* argparse_paths_type = "-rel";

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
            _current.aAd = (_rel_lines - 1) * 4;
            _source_all_lines[_all_lines-1] = _current;
        }
        else {
            _all_lines += 2;
            _source_all_lines = realloc(_source_all_lines, (int)sizeof(Line)*_all_lines);
            Line _label;
            colon_pos[0] = '\0';
            _label.lNo = _rel_lines-1;
            _label.lType = LABEL;
            _label.content = strdup(_source_file_line);
            _label.aAd = (_rel_lines-1)*4;
            _source_all_lines[_all_lines-2] = _label;
            Line _current;
            _current.lNo = _rel_lines-1;
            _current.lType = TEXTS;
            _current.content = strdup(colon_pos+1);
            _current.aAd = (_rel_lines - 1) * 4;
            _source_all_lines[_all_lines-1] = _current;
        }
    }
    
    bool syn= syntacticalAnalysis(_source_all_lines + 1, _all_lines - 1);
    bool lex= lexicalAnalysis(_source_all_lines + 1, _all_lines - 1);

    if (syn && lex)
    {
	    FILE* OUTPUT = fopen(_output_file_path, "w");
		if (OUTPUT == NULL) {
			trace_cstm_error(_output_file_path, "specified file path not found.");
			return 1;
		}
        for (int i = 1; i < _all_lines; i++){
            BYTECODE generated = Instruction_to_ByteCode(_source_all_lines[i], _source_all_lines + 1, _all_lines - 1);
		    char binary[33];
		    intToBinaryString(generated, binary);
		    fprintf(OUTPUT, "%s\n", binary);
        }
    }

     //   BYTECODE St = translateSType("sw", "s8", "s2", "38");
     //   char binary[33];
     //   intToBinaryString(St, binary);
     //   printf("%s\n", binary);

    free(_source_all_lines);
    fclose(SOURCE);
    return 0;
}