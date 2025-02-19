#include "analysis.h"

bool syntacticalAnalysis(FILE* file) {
	// To be implimented by shlok and sambhav.
	return true;
}

bool lexicalAnalysis(FILE* file) {
	// To be implimented by rishabh.
	return false;
}

bool isLineLexicallyCorrect(Line line) {
	char lineType = line.lType;
	if (lineType == LABEL) {
		
		return true;
	}


	else if (lineType == TEXTS) {
		char lineContent = line.content;
		char words[10][10];
		char delimiters[] = {' ',','};
		string_splitter(lineContent, words, delimiters);

		if (!is_valid_instruction(words[0]))
			return false;
		
		Instruction instruction1 = instruction_encoding(words[0]);
		char instructionType = instruction1.type;

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

		if (strcat(instructionType, "J") == 0) {
			bool s1 = is_valid_register(words[1]);
			bool s2 = is_valid_immediate(words[2], J) || is_valid_label(words[2]);
			if (s1 && s2 == false) {// To impliment which type of error is raised.
				return false;
			}
		}

		
		return true;
	}


}