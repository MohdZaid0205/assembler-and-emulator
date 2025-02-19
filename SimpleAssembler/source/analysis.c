#include "analysis.h"

bool syntacticalAnalysis(Line arr[], unsigned int length){
	// To be implimented by shlok and sambhav.
	return true;
}


bool lexicalAnalysis(Line arr[], unsigned int length) {
	
	for (int i = 0; i < length; i++) {
		if (!isLineLexicallyCorrect(arr[i]))
			return false;
	}
	return false;
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


bool isLineLexicallyCorrect(Line line) {
	char lineType = line.lType;
	if (lineType == LABEL) {
		if (!is_valid_label(line.content))
			return false;

		return true;
	}


	else if (lineType == TEXTS) {
		const char* lineContent = line.content;
		char words[10][10];
		char delimiters[] = {' ',','};
		string_splitter(lineContent, words, delimiters);

		if (!is_valid_instruction(words[0]))
			return false;
		
		Instruction instruction1 = instruction_encoding(words[0]);
		const char* instructionType = instruction1.type;

		if (strcmp(instructionType, "R") == 0) {
			bool s1 = is_valid_register(words[1]);
			bool s2 = is_valid_register(words[2]);
			bool s3 = is_valid_register(words[3]);
			if (s1 && s2 && s3 == false) {// To impliment which type of error is raised.
			    return false;
			}
		}
		
		if (strcmp(instructionType, "I") == 0) {
			bool s1 = is_valid_register(words[1]);
			bool s2 = is_valid_register(words[2]);
			bool s3 = is_valid_immediate(words[3], I);

			if (s1 && s2 && s3 == false) {// To impliment which type of error is raised.
				return false;
			}
		}

		if (strcmp(instructionType, "S") == 0) {
			char delimiters2[] = { '(', ')'};
			char words2[10][10];
			string_splitter(words[2], words2, delimiters2);
			bool s1 = is_valid_register(words[1]);
			bool s2 = is_valid_immediate(words2[0], S);
			bool s3 = is_valid_register(words2[1]);
			if (s1 && s2 && s3 == false) {// To impliment which type of error is raised.
				return false;
			}
		}

		if (strcmp(instructionType, "B") == 0) {
			bool s1 = is_valid_register(words[1]);
			bool s2 = is_valid_register(words[2]);
			bool s3 = is_valid_immediate(words[3], B) || is_valid_label(words[3]);
			if (s1 && s2 && s3 == false) {// To impliment which type of error is raised.
				return false;
			}
		}

		if (strcmp(instructionType, "J") == 0) {
			bool s1 = is_valid_register(words[1]);
			bool s2 = is_valid_immediate(words[2], J) || is_valid_label(words[2]);
			if (s1 && s2 == false) {// To impliment which type of error is raised.
				return false;
			}
		}
		
		return true;
	}


}