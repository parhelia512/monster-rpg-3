#include <Nooskewl_Engine/Nooskewl_Engine.h>

#include "brains.h"
#include "dll.h"
#include "ml_start.h"
#include "ml_start_upper.h"

bool dll_start()
{
	noo.window_title = "Monster RPG 3";
	return start_brains();
}

void dll_end()
{
	end_brains();
}

Map_Logic *dll_get_map_logic(std::string map_name)
{
	Map_Logic *ml = NULL;

	if (map_name == "start.map") {
		ml = new ML_start();
	}
	else if (map_name == "start_upper.map") {
		ml = new ML_start_upper();
	}

	return ml;
}

Brain *dll_get_brain(std::string options)
{
	Tokenizer t(options, ',');

	std::string type = t.next();

	if (type == "talk_brain") {
		std::string name = t.next();
		return new Talk_Brain(name);
	}
	else if (type == "animated_brain") {
		std::string name = t.next();
		return new Animated_Brain(name);
	}
	else if (type == "talk_then_animate_brain") {
		std::string name = t.next();
		return new Talk_Then_Animate_Brain(name);
	}
	else if (type == "door_brain") {
		bool open;
		std::string open_s = t.next();
		if (open_s == "open") {
			open = true;
		}
		else {
			open = false;
		}
		return new Door_Brain(open);
	}
	else if (type == "item_brain") {
		std::string this_options = options.substr(type.length() + 1);
		Tokenizer t(this_options, ',');

		std::string opt = t.next();

		Tokenizer t2(opt, '=');

		std::string key = t2.next();
		std::string value = t2.next();

		Tokenizer t3(value, ':');

		std::string quantity = t3.next();
		std::string milestone = t3.next();

		return new Item_Brain(key, atoi(quantity.c_str()), atoi(milestone.c_str()));
	}

	return 0;
}
