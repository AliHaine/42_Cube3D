# Cub3d - Minecraft : セグメンテーションフォルトのないプログラムは、鋭い剣のように正確に使える。
## Cub3d is a project at the school 42. We work on it in groups of 2 students. The project involves creating a game similar Wolfeinstein 3D (1992), using Raycasting to develop a "Fake" 3d game (2.5D) with a 2D map. We implement it in C and whithout the use of any GameEngine; instead, we had to utilize MLX as the graphic lib (similar to SDL but significantly less powerful).
---
[![Image](https://i.goopics.net/gn5v60.png)](https://goopics.net/i/gn5v60)
[![Image](https://i.goopics.net/km1wsr.png)](https://goopics.net/i/km1wsr)

## Authors and Features
-   [@AliY](https://www.github.com/alihaine)  notably implemented:
    -   DDA (most optimized Raycasting method)
    -   Item system
    -   Block system
    -   World, Biome[...] system
    -   Sound with BASS libs
    -   Animation system
    -   Infinit world..
    -   Energy bar
    -   Multiple Difficulty
    -   Multi-World and Teleportation (between them)
    -   Destroying (block) system
-   [@NathanG](https://www.github.com/drogonj)  notably implemented:
    -   GUI, like crafting interface
    -   Action bar
    -   Inventory managment (picking item, stacking them[...])
    -   Crafting system
    -   Animated texture (nether portal texture[...])
    -   Textured ceil with normal ceiling system or Skybox-type system
    -   Textured floor
    -   Fog system
    -   Dynamic minimap
    -   Sprite  system

## Installation

Can be run only in Mac or Linux.

Clone the Git

```sh
git clone https://github.com/AliHaine/42_Cube3D
```
Inside the cloned folder, use 'make' to create the program, and then run the program
```sh
cd PROJECT
make
./cub3d
```
---
## 0.0 Introduction
This readme is primarily an explanation of how to create a 'Thing' from *'nothing'*. While I will often refer to myself as "I" since this is my part of the project, it's worth noting that my teammate contribution such as: skybox, sprite, crafting, fog and many more have been crucial features for the project. So of course, the part of my teammate are equally significant. **It was a perfect collaboration between us**, and that collaboration allowed us to create a project like this.

*This is not a tutorial or a comprehensive explanation of the entire project or C concepts (such as Enum, Struct..)*

## 0.1 Project starting and idea

From the start, the goal is immediatly defined: creating a **Wolfeinstein MINECRAFT with Raycasting** in 2.5D. We started the project at the begin of may 2023, and finish him at the begin of september 2023, the "normal" part, wanted by the subject was finish in 2 weeks, all the rest of the time we spent in this project is for the fun and pleasure of coding. Of course the project are not really "finished", there is still lot of features to be implement, and lots of ideas in our minds, but the wasted time into this project was to big.. The end had to be sounded. 

we hadn't started yet the projet that we puted **lots of goals and features** to had: world, block, item, chat, enemy, NPC and more.. but of course, **we didn't realize the huge work all our ideas represente..**

---

## 1.0 Creating a thing

To create a game like Minecraft, it's essential to have some basic elements of Minecraft, such as Item, Block, and of course an INFINIT world, and more... I want to reiterate that **we did not have a Game Engine**, everything had to be coded from scratch. Of course, I made many (a lot of) mistakes before reaching this point, and I will talk about them later, but for now, let me explain how I create a concept (like Block, Item..) from scratch, here is my logic and approach:

- Concept definition 
- Declaration of the structur with all necessary elements
- Associate an Enum to the concept
- Desinging a straightforward method to creating the concept object
- Setting up a easy way to acces and use the concept object

**Definition**: What is the concept I want to do ? How will I use it ? Do  I need to allocate memory dynamically, perhaps by using malloc or creating linked list, or any other allocation method ? How many ressources do I need to allocate? At this stage, everything is not really certain; it's purely theoretical. However this work provides me with a global view of the concept.

**Declaration**: What does the concept need to have for work ? In other words, what are all the variables that ce concept (and its structure) needs to have. Each concept has its own structure.

**Enum**: For each concepts, an enum must be defined with values for each of its elements.

**Design**: The concept not only needs to work, but the code associated with it also has to be perfect, easy to understand, and easy to use. With some functions *(involving one or more algorithms)* I need to be able to create an *object-like* of my concept. This point is the MUST important, and you will understand its significance when i go into detail.

**Accessor**: Finally, i implemented the "accessor", which **simplifies the process of accessing and utilizing a concept**. Accessor method are akin to getter and setter methods. In an accessor file *(each concept have his own .c accessor file)*, I declare a global static array variable to store something resembling an instance of the concept. Then, i create various accessor such as: ```get_want_i_want()```. I acknowledge that my accessor system isn't perfect; for example my getters aren't marked as const, and sometimes I do a horrible thing: directly modifiying a value retrived through a getter, like this: ```get_want_i_want().acces_to_a_variable = new_value```. However, in  the 42 school  **_we must adhere to coding standards_**, these standards stipulate constraints such as limiting functions to 25 lines or a file's to 5 functions.. Consequently, in cases where a concept has numerous of attributes, it may not be feasible to create proper getters and setters methods for each one.

---

## 1.1 Example of creating a thing

The essential element of Minecraft is, of course, the Blocks. So, in accordance with what I mentioned previously, here is the concept of Block:

## Enum Block

| Name      |
| :---           |
| 	OBSIDIAN |
|	NETHER_PORTAL |
|	CRACKED_DEEPSLAT_TILES |
|	DEEPSLATE_COAL_ORE |
|	NETHER_WART_BLOCK |
|	GRASS |
| ... |
| BLOCK_NUMBER |

First of all, you can see the Enum below where each Blocks is defined. Initially, we didn't use them, and **managing the Blocks was challenging**, but take a look at the Enum now, you can see the "BLOCK_NUMBER" value, this allow me to do something  like this ```char c[BLOCK_NUMBER]```. it's powerful because instead manually allocating (X + 1) blocks and setting 0 at the end for iteration, we can simply **use BLOCK_NUMBER from everywhere.**

Before and 'Normal':

```
//declaration
t_blocks *blocks_list;
blocks_list = malloc(sizeof(t_blocks *) * 8);   <--- manually change each time I add a block and must be free
blocks_list[7] = 0;                             <--- manually change each time I add a block

//iterator
int i = 0;
while (blocks_list[i]) {
    //do stuff
}

//example of get number
get_blocks_number(void)
{
    int i = 0;
    while (blocks_list[i])
        i++;
}
```
After with Enum:
```
t_blocks blocks_list[BLOCK_NUMBER]; <--- Auto change when I add a Block, no need to free

int i = 0;
while(i < BLOCK_NUMBER) {
    //do stuff
}

//no need to call a function to get number, just call BLOCK_NUMBER from anywhere.
```

It's not all, Enum also provide more clarity, how can you acces, for example, the GRASS block, which is at position 5 in the blocks_list ? Here an example:
```
//whithout enum
get_my_block(5);        <--- You must remember the position of every blocks

//with enum
get_my_blocks(GRASS)    <--- Immediately provide the correct element
```
because you don't want remembre every block, here's what you would have to do (this is what we had before):
```
get_my_block('G') <--- For the example, we considere char 'G' as the unique char value of the block GRASS

return get_my_block(char c)
{
    int i = 0;
    while (blocks_list[i])
    {
        if (blocks_list[i].char == c)
            return (RETURN);
        i++;
    }
}
```

In addition of clarity, there's a significant optimization. You no longer need to iterate multiple times to count the number of blocks or to find the right block when needed, and more..

## Struct Block and Accessor

| attribute      | Description |
| :---           |    :----:   |
|	Block		 |	name        |
|	char	|		block_char |
|	t_item	*|		item |
|	int		|		strength |
|	t_animation	|	animation |
|	mlx_image_t	*|	image |
|	bool	|		is rigid |

The Struct was straightforward to read and understand, the intersting part is the Accessor, I mean, how I acces the wanted element from the Struct. Initially there was a traditional 'Core' Struct that contained everything:
```
Struct Core {
    t_animation *animations_list;
    t_block     *blocks_list;
    t_item      *items_list;
    t_player    player;
    [...]
}
```
Then I passed the wanted elements to the function:
```call_a_function_who_need_a_item(core->items_list);```

The main issues that I encountered is with the 'depth function', imagine that simple (and typical) scenario:
Func1 call Func2, which call Func3, which call Func4 [...]. If only Func4 needs, for example to acces a Block, I had to pass the entire blocks_list through Func1, Func2 and Func3 just for deliver it to Func4.. Not only is this an inneficient coding practice, but it also breaks the encapsulation concept, as I had to send the entire blocks_list for getting a Block though X Func. And it's even worse if I pass the Core Struct directly everywhere..
[![Image](https://i.goopics.net/r0x9jf.png)](https://goopics.net/i/r0x9jf)

To resolve this issue, I used global static variables in an Accessor file (block_accessor.c..), to facilitate acces to the required element from anywhere. These global static variables are specifically used for fundamental concepts that are frequently utilized in various part of the program, such as Blocks or Items. Here are some functions that work with the global static variable of Block in the accessor

```
static t_block	*g_blocks[BLOCK_NUMBER];

t_block	*get_block(Block block)
{
	return (g_blocks[block]);
}

t_block	*get_block_from_char(char block_char)
{
	int	i;

	i = BLOCK_NUMBER;
	while (i-- > 0)
	{
		if (g_blocks[i]->block_char == block_char)
			return (g_blocks[i]);
	}
	return (0);
}

mlx_image_t	*get_block_image(Block block)
{
	return (g_blocks[block]->image);
}
```

