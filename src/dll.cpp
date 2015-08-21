#include <Nooskewl_Engine/Nooskewl_Engine.h>

#include "brains.h"
#include "dll.h"
#include "gui.h"
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
	else if (type == "item_drop") {
		std::string inventory_s = options.substr(type.length() + 1);

		Inventory *inventory = new Inventory();
		inventory->from_string(inventory_s);

		return new Item_Drop_Brain(inventory);
	}
	else if (type == "shop") {
		std::string this_options = options.substr(type.length() + 1);
		Tokenizer t(this_options, ',');

		int len = 0;

		std::string caption = t.next();
		len += caption.length() + 1;
		caption = unescape_string(caption);

		std::string yes_option = t.next();
		len += yes_option.length() + 1;
		yes_option = unescape_string(yes_option);

		std::string no_option = t.next();
		len += no_option.length() + 1;
		no_option = unescape_string(no_option);

		std::string inv_size_s = t.next();
		len += inv_size_s.length() + 1;

		int inv_size = atoi(inv_size_s.c_str());

		std::vector<int> costs;

		for (int i = 0; i < inv_size; i++) {
			std::string cost = t.next();
			len += cost.length() + 1;

			costs.push_back(atoi(cost.c_str()));
		}

		std::string inventory_s = this_options.substr(len);

		Inventory *inventory = new Inventory();
		inventory->from_string(inventory_s);

		return new Shop_Brain(caption, yes_option, no_option, inventory, costs);
	}

	return 0;
}

void dll_pause()
{
	Pause_GUI *gui = new Pause_GUI();
	gui->start();
	noo.guis.push_back(gui);
}
