#include "analysis.h"

bool syntacticalAnalysis(Line arr[], unsigned int length) {
	bool status = true;
	for (int i = 0; i < length; i++) {
		if (arr[i].lType == LABEL) {
			if (calculate_label_occurence(arr[i].content, arr, length) > 1)
				trace_sytx_error(arr[i].lNo, arr[i].content, "Label is defined more than once");
				status = false;
		}
		else if (!isLineSyntacticallyCorrect(arr[i])) {
			status = false;
		}
	}
	return status;
}


bool lexicalAnalysis(Line arr[], unsigned int length) {
	bool status = true;
	for (int i = 0; i < length; i++) {
		if (!isLineLexicallyCorrect(arr[i]))
			status = false;
	}
	return status;
}


bool is_valid_label(const char* text) {

	if (is_valid_register(text) || is_valid_instruction(text) || (48 <= (int)text[0] && (int)text[0] <= 57))
		return false;

	for (int i = 0; i < strlen(text); i++) {
		switch (text[i]) {
			// Digits (0-9)
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':

			// Uppercase letters (A-Z)
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
		case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
		case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
		case 'V': case 'W': case 'X': case 'Y': case 'Z':

			// Lowercase letters (a-z)
		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
		case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
		case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
		case 'v': case 'w': case 'x': case 'y': case 'z':

			// Underscore (_)
		case '_':
			continue;  // Valid character

		default:
			return false;  // Invalid character
		}
	
	}
	return true;
}

int calculate_label_occurence(const char* _lab, Line arr[], int length) {
	int occurence = 0;
	for (int i = 0; i < length; i++){
		if (arr[i].lType == LABEL && strcmp(arr[i].content, _lab) == 0)
			occurence++;
	}
	return occurence;
}

const char* calculate_label_rAd(const char* _lab, unsigned int aAd, Line arr[], int length) {
	char* value[20];
	for (int i = 0; i < length; i++) {
		if (arr[i].lType == LABEL && strcmp(arr[i].content, _lab) == 0)
			sprintf(value, "%d", arr[i].aAd - aAd);
	}
	return value;
}


bool isLineSyntacticallyCorrect(Line line) {
	
	char* lineContent = (char*)line.content;
	char words[10][10];
	char delimiters[] = { ' ',',', '\0' };
	lineContent[strcspn(lineContent, "\n")] = '\0';
	string_splitter(lineContent, words, delimiters);
	

	Instruction instruction1 = instruction_encoding(words[0]);
	const char* instructionType = instruction1.type;

	if (strcmp(instructionType, "R") == 0) {
		int commaCount = 0;
		int termCount = 0;
		int termCountStatus = 1;
		for (int i = 0; i < strlen(lineContent); i++) {
			if (lineContent[i] == ',')
				commaCount++;
		}
		for (int i = 0; i < 10; i++){
			if ((words[i][0] != '\0') && (termCountStatus == 1)) {
				termCount++;
				continue;
			}
			termCountStatus = 0;
		}
		bool s1, s2, s3;
		s1 = (commaCount == 2);
		s2 = (termCount == 4);
		s3 = true;
		for (int i = 0; lineContent[i]; i++) {
			if (!isalnum((unsigned char)lineContent[i]) && lineContent[i] != ',' && lineContent[i] != ' ') {
				s3 = false;
				break;
			}
		}
		if ((s1 && s2 && s3) == 0)
			trace_sytx_error(line.lNo, line.content, "Syntax Error in R-Type Instruction");
		return s1 && s2 && s3;
	}

	if (strcmp(instructionType, "S") == 0) {
		int commaCount = 0;
		int termCount = 0;
		int termCountStatus = 1;
		int openParen = 0, closeParen = 0;
		for (int i = 0; i < strlen(lineContent); i++) {
			if (lineContent[i] == ',')
				commaCount++;
			if (lineContent[i] == '(')
				openParen++;
			if (lineContent[i] == ')')
				closeParen++;
		}
		for (int i = 0; i < 10; i++) {
			if ((words[i][0] != '\0') && (termCountStatus == 1)) {
				termCount++;
				continue;
			}
			termCountStatus = 0;
		}
		bool s1 = (commaCount == 1);
		bool s2 = (termCount == 3);
		bool s3 = (openParen == 1 && closeParen == 1);
		bool s4 = true;
		for (int i = 0; lineContent[i]; i++) {
			if (!isalnum((unsigned char)lineContent[i]) && lineContent[i] != ',' &&
				lineContent[i] != '(' && lineContent[i] != ')' && lineContent[i] != '-' && lineContent[i] != ' ') {
				s4 = false;
				break;
			}
		}
		if ((s1 && s2 && s3 && s4) == 0)
			trace_sytx_error(line.lNo, line.content, "Syntax Error in S-Type Instruction");
		return s1 && s2 && s3 && s4;
	
	}

	if (strcmp(instructionType, "I") == 0) {
		int commaCount = 0;
		int termCount = 0;
		int termCountStatus = 1;
		for (int i = 0; i < strlen(lineContent); i++) {
			if (lineContent[i] == ',')
				commaCount++;
		}
		for (int i = 0; i < 10; i++) {
			if ((words[i][0] != '\0') && (termCountStatus == 1)) {
				termCount++;
				continue;
			}
			termCountStatus = 0;
		}
		bool s1 = (commaCount == 2);
		bool s2 = (termCount == 4);
		bool s3 = true;
		for (int i = 0; lineContent[i]; i++) {
			if (!isalnum((unsigned char)lineContent[i]) && lineContent[i] != ',' && lineContent[i] != '-' && lineContent[i] != ' ') {
				s3 = false;
				break;
			}
		}
		bool s4 = (commaCount == 1);
		bool s5 = (termCount == 3);

		if (!((s1 && s2 && s3) || (s4 && s5 && s3 && (strcmp(words[0], "lw") == 0))));
			trace_sytx_error(line.lNo, line.content, "Syntax Error in I-Type Instruction");
		return (s1 && s2 && s3)||(s4 && s5 && s3 && (strcmp(words[0],"lw")==0));
	}


	if (strcmp(instructionType, "B") == 0) {
		int commaCount = 0;
		int termCount = 0;
		int termCountStatus = 1;
		for (int i = 0; i < strlen(lineContent); i++) {
			if (lineContent[i] == ',')
				commaCount++;
		}
		for (int i = 0; i < 10; i++) {
			if ((words[i][0] != '\0') && (termCountStatus == 1)) {
				termCount++;
				continue;
			}
			termCountStatus = 0;
		}
		bool s1 = (commaCount == 2);
		bool s2 = (termCount == 4);
		bool s3 = true;
		for (int i = 0; lineContent[i]; i++) {
			char c = lineContent[i];
			if (!isalnum((unsigned char)c) && c != ',' && c != '_' && c != '-' && c != ' ') {
				s3 = false;
				break;
			}
		}
		if ((s1 && s2 && s3) == 0)
			trace_sytx_error(line.lNo, line.content, "Syntax Error in B-Type Instruction");
		return s1 && s2 && s3;
	}

	if (strcmp(instructionType, "J") == 0) {
		int commaCount = 0;
		int termCount = 0;
		int termCountStatus = 1;
		for (int i = 0; i < strlen(lineContent); i++) {
			if (lineContent[i] == ',')
				commaCount++;
		}
		for (int i = 0; i < 10; i++) {
			if ((words[i][0] != '\0') && (termCountStatus == 1)) {
				termCount++;
				continue;
			}
			termCountStatus = 0;
		}
		bool s1 = (commaCount == 1);
		bool s2 = (termCount == 3);
		bool s3 = true;
		for (int i = 0; lineContent[i]; i++) {
			char c = lineContent[i];
			if (!isalnum((unsigned char)c) && c != ',' && c != '_' && c != '-' && c != ' ') {
				s3 = false;
				break;
			}
		}
		if ((s1 && s2 && s3) == 0)
			trace_sytx_error(line.lNo, line.content, "Syntax Error in J-Type Instruction");
		return s1 && s2 && s3;
	}
	trace_cstm_error("Instruction Type Error", "Instruction Type Not Found");
	return false;
}


bool isLineLexicallyCorrect(Line line) {
	char lineType = line.lType;
	if (lineType == LABEL) {
		if (!is_valid_label(line.content))
			trace_name_error(line.lNo, line.content, "Label", "Label is not valid");
			return false;

		return true;
	}

	char* lineContent = (char*)line.content;
	char words[10][10];
	char delimiters[] = { ' ',',', '\0' };
	lineContent[strcspn(lineContent, "\n")] = '\0';
	string_splitter(lineContent, words, delimiters);

	if (!is_valid_instruction(words[0])) {
		trace_name_error(line.lNo, line.content, "Instruction", "Instruction is not valid");
		return false;
	}
		
	Instruction instruction1 = instruction_encoding(words[0]);
	const char* instructionType = instruction1.type;
	
	if (strcmp(instructionType, "R") == 0) {
		bool s1 = is_valid_register(words[1]);
		bool s2 = is_valid_register(words[2]);
		bool s3 = is_valid_register(words[3]);
		if (!(s1 && s2 && s3))
			trace_name_error(line.lNo, line.content, "Register", "Register is not valid");
		return s1 && s2 && s3;
	}
		
	if (strcmp(instructionType, "I") == 0) {
		int commaCount = 0;
		int termCount = 0;
		int termCountStatus = 1;
		for (int i = 0; i < strlen(lineContent); i++) {
			if (lineContent[i] == ',')
				commaCount++;
		}
		for (int i = 0; i < 10; i++) {
			if ((words[i][0] != '\0') && (termCountStatus == 1)) {
				termCount++;
				continue;
			}
			termCountStatus = 0;
		}
		bool s1 = (commaCount == 2);
		bool s2 = (termCount == 4);
		bool s3 = true;
		for (int i = 0; lineContent[i]; i++) {
			if (!isalnum((unsigned char)lineContent[i]) && lineContent[i] != ',' && lineContent[i] != '-' && lineContent[i] != ' ') {
				s3 = false;
				break;
			}
		}
		bool s4 = (commaCount == 1);
		bool s5 = (termCount == 3);

		if (((s1 && s2 && s3) || (s4 && s5 && s3)) == 0)
			trace_sytx_error(line.lNo, line.content, "Syntax Error in I-Type Instruction");
		return (s1 && s2 && s3) || (s4 && s5 && s3);
	}

	if (strcmp(instructionType, "S") == 0) {
		char delimiters2[] = { '(', ')', '\0'};
		char words2[10][10];
		words[2][strcspn(words[2], "\n")] = '\0';
		string_splitter(words[2], words2, delimiters2);
		bool s1 = is_valid_register(words[1]);
		bool s2 = is_valid_immediate(words2[0], S);
		bool s3 = is_valid_register(words2[1]);
		if (!(s1 && s2 && s3))
			trace_name_error(line.lNo, line.content, "Register/Immediate", "Either Register or Immediate is not valid");
		return s1 && s2 && s3;

	}

	if (strcmp(instructionType, "B") == 0) {
		int len = 0;
		for (int i = 0; words[i][0] != '\0'; i++) {
			len++;
		}
		bool s1 = is_valid_register(words[1]);
		bool s2 = is_valid_register(words[2]);
		bool s3 = (is_valid_immediate(words[3], B) || is_valid_label(words[3])) ;
		if (!(s1 && s2 && s3 && (len == 4)))
			trace_name_error(line.lNo, line.content, "Register/Immediate/Label", "Either Register or Immediate or Label is not valid");
		return s1 && s2 && s3 && (len == 4);
	}

	if (strcmp(instructionType, "J") == 0) {
		int len = 0;
		for (int i = 0; words[i][0] != '\0'; i++) {
			len++;
		}
		bool s1 = is_valid_register(words[1]);
		bool s2 = is_valid_immediate(words[2], J) || is_valid_label(words[2]);
		if (s1 && s2 && (len == 3))
			trace_name_error(line.lNo, line.content, "Register/Immediate/Label", "Either Register or Immediate or Label is not valid");
		return s1 && s2 && (len == 3);
	}
	return true;
}