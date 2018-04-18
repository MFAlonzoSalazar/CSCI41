#include <iostream>
using namespace std;

class Plants {
	public:
	string color = "Green";
	string cell_type = "Eukaryote";
	string kingdom = "Plantae";
	string food_source = "Photosynthesis";
};
class Tree : public Plants {
	string types_of_trees = "In Clovis there are : Populus Fremontii, Plane trees, Platanus Racemosa, Boxelder Maple, Salix Laevigata, Salix Lasiolepis, among others.";
	string tree_lifespan = "Tree life-span can depend on the species, they usually live around 40(for a palm tree) - 5,000 years (for the Bristlecone Pine)";
	string stinky_tree = "Some of the stinkiest trees include : the Maidenhair Tree (vomit/rotten eggs), the Tree of Heaven (that emits a hellish smell), the Chinese Chestnut Tree (only the male flowers stink), the Callery Pear Tree (beautiful, but smells like fish).";
	string pretty_tree = "Among the prettiest trees are : The Royal Poinciana, The Rainbow Eucalyptus, The Rhododendron Tree, The Wisteria Tree, The Cherry Tree, the Flamboyant Tree, The Dragonblood Tree,etc.";
	string worlds_saddest_tree = "Rome's $57,000 Christmas Tree.";

};
class Shrub : public Plants {
	string difference = "Shrub is not another name for a tree. Shrubs have many stems, trees only have one. They are also generally shorter in height.";
	string shrubbery = "A human-created area in gardens, parks, etc. This is where multiple shrubs and other plants grow.";

};
class Grass : public Plants {
	string types_of_grass = "The types of grass are : Kentucky Bluegrass, Zoysia Grass, Tall Fescue, Ryegrass, Bermuda Grass, among others.";
	string bg_state = "Kentucky is the Bluegrass State.";
	string ew = "Ruminants are animals that eat a lot of grass. The world Ruminant comes from the Latin word ruminare which means chew over again. Cows are ruminants. They regurgitate the grass from their first stomach and chew it again.";
	string song = "There is a song about the colors of the grass in Ireland called Forty Shades of Green.";
	string fear = "Hastenburaphobia is the fear of grass.";
	string pollution = "According to the Environmental Protection Agency, as much as 5%% of all polluting exhaust in urban areas is from lawn mowers.";
	string degree = "You can get a degree in lawn maintenance from Penn State University, it's called Turf Grass Science.";
};

/*class Fire {
	public:
};
class Ash : public Fire {
};*/
