#include <iostream>
using namespace std;

class Plant {
	public:
	string get_color() {
		return "Green";
	}
	string get_cell_type() {
		return "Eukaryote";
	}
	string get_kingdom () {
		return "Plantae";
	}
	string get_food (){
		return "Photosynthesis";
	}
};
class Tree : public Plant {
	string types_of_trees = "In Clovis there are : Populus Fremontii, Plane trees, Platanus Racemosa, Boxelder Maple, Salix Laevigata, Salix Lasiolepis, among others.";
	string tree_lifespan = "Tree life-span can depend on the species, they usually live around 40(for a palm tree) - 5,000 years (for the Bristlecone Pine)";
	string stinky_tree = "Some of the stinkiest trees include : the Maidenhair Tree (vomit/rotten eggs), the Tree of Heaven (that emits a hellish smell), the Chinese Chestnut Tree (only the male flowers stink), the Callery Pear Tree (beautiful, but smells like fish).";
	string pretty_tree = "Among the prettiest trees are : The Royal Poinciana, The Rainbow Eucalyptus, The Rhododendron Tree, The Wisteria Tree, The Cherry Tree, the Flamboyant Tree, The Dragonblood Tree,etc.";
	string worlds_saddest_tree = "Rome's $57,000 Christmas Tree.";
	int flammability = 20;
	int burn_time = 20;
	public :
	string get_type() {
		return types_of_trees;
	}
	string get_life() {
		return tree_lifespan;
	}
	string get_stinky() {
		return stinky_tree;
	}
	string get_pretty (){
		return pretty_tree;
	}
	string get_sad () {
		return worlds_saddest_tree;
	}
	int get_flame (){
		return flammability;
	}
	int get_burn() {
		return burn_time;
	}
};
class Bush : public Plant {
	string pretty_for_garden = "Buddliea, Forsynthia Spectabillis, Spirea Arguta, Ceanothus Yakee Point, Weigelia.";
	string used = "Bush and shrub are usually used synonymously.";
	string shrubbery = "A human-created area in gardens, parks, etc. This is where multiple shrubs and other plants grow.";
	int flammability = 50;
	int burn_time = 15 ;
	public:
	string get_pretty() {
		return pretty_for_garden;
	}
	string get_used() {
		return used;
	}
	string get_shrub(){
		return shrubbery;
	}
	int get_flame(){
		return flammability;
	}
	int get_burn() {
		return burn_time;
	}
};
class Grass : public Plant {
	string types_of_grass = "The types of grass are : Kentucky Bluegrass, Zoysia Grass, Tall Fescue, Ryegrass, Bermuda Grass, among others.";
	string bg_state = "Kentucky is the Bluegrass State.";
	string ew = "Ruminants are animals that eat a lot of grass. The world Ruminant comes from the Latin word ruminare which means chew over again. Cows are ruminants. They regurgitate the grass from their first stomach and chew it again.";
	string song = "There is a song about the colors of the grass in Ireland called Forty Shades of Green.";
	string fear = "Hastenburaphobia is the fear of grass.";
	string pollution = "According to the Environmental Protection Agency, as much as 5%% of all polluting exhaust in urban areas is from lawn mowers.";
	string degree = "You can get a degree in lawn maintenance from Penn State University, it's called Turf Grass Science.";
	int flammability = 80;
	int burn_time = 10;
	public:
	string get_grass() {
		return types_of_grass;
	}
	string get_bg() {
		return bg_state;
	}
	string get_ew(){
		return ew;
	}
	string get_song() {
		return song;
	}
	string get_fear() {
		return fear;
	}
	string get_pollution() {
		return pollution;
	}
	string get_degree() {
		return degree;
	}
	int get_flame() {
		return flammability;
	}
	int get_burn() {
		return burn_time;
	}
};

