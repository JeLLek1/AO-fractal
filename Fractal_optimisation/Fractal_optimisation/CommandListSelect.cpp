#include "CommandListSelect.h"
#include <conio.h>
#include <iostream>

void CommandListSelect::handleInput(char key)
{
	switch (key)
	{
	case 13:
		applySelected_ = true;
		break;
		case 'w':
		{
			size_t prev = currentSelection_ - 1;
			if (prev >= selections_.size())
				prev = selections_.size() - 1;

			currentSelection_ = prev;
			break;
		}
		case 's':
		{
			size_t next = currentSelection_ + 1;
			if (next >= selections_.size())
				next = 0;

			currentSelection_ = next; 
			break;
		}
	}
}

void CommandListSelect::display()
{
	std::cout << title_ << std::endl << std::endl;
	for (size_t i = 0; i < selections_.size(); i++) {
		if (currentSelection_ == i) {
			std::cout << " -> ";
		}
		else {
			std::cout << "    ";
		}
		std::cout << selections_[i] << std::endl;
	}
}

CommandListSelect::CommandListSelect(std::string title, std::vector<std::string>& selections)
{
	title_ = title;
    selections_ = selections;
}

size_t CommandListSelect::run()
{
    while (!applySelected_) {
        system("CLS");
        display();
        handleInput(_getch());
    }
    return currentSelection_;
}
