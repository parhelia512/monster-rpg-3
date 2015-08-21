#ifndef M3_GUI_H
#define M3_GUI_H

#include <Nooskewl_Engine/Nooskewl_Engine.h>

using namespace Nooskewl_Engine;

class Buy_Sell_GUI : public GUI {
public:
	static void add_item(Inventory *inventory, std::vector<int> &costs, std::string name, int cost, int quantity);
	static void confirm_callback(void *data);
	static void get_number_callback(void *data);

	Buy_Sell_GUI(Inventory *seller_inventory, std::vector<int> &seller_costs);
	virtual ~Buy_Sell_GUI();

	void handle_event(TGUI_Event *event);
	bool update();

private:
	static bool cancel;
	static bool getting_number;
	static bool got_number;
	static int number;

	void set_labels();
	void set_list(Widget_List *list, Inventory *inventory, bool is_your_inventory);
	void set_lists();
	Item *remove_item(int index, bool buying);
	void add_item(Item *item, bool buying);
	void swap_item(int index, bool buying);
	void return_items();
	int get_cost(bool player);
	void clear_hilights();
	void set_hilights();
	void merge(Inventory *inventory, int count);
	void move_original(Inventory *inventory, int count, std::vector<Item *> &move_from, std::vector<Item *> &move_to);

	Widget_Label *your_gold_label;
	Widget_List *your_list;
	Widget_Label *their_gold_label;
	Widget_List *their_list;

	Widget_Text_Button *accept_button;
	Widget_Text_Button *done_button;

	Widget_Label *cost_label;
	Widget_Label *weight_label;
	Widget_Label *value_label;
	Widget_Label *condition_label;
	Widget_Label *properties_label;

	Stats *stats;

	Inventory *seller_inventory;
	std::vector<int> &seller_costs;

	std::map<Item *, int> costs; // cost of everything, buyer and seller

	std::vector<Item *> your_original_inventory;
	std::vector<Item *> their_original_inventory;

	int sell_count;
	int buy_count;
	std::vector<int> swapped_out_costs;

	MML *cha_ching;

	bool getting_for_your_inventory;
	int getting_for;

	bool exit_menu;
};

class Multiple_Choice_GUI : public GUI {
public:
	Multiple_Choice_GUI(std::string caption, std::vector<std::string> choices, Callback callback);

	bool update();

private:
	Widget_Label *caption_label;
	Widget_List *list;

	Callback callback;
};

#endif // M3_GUI_H
