/*Contains the "physical" appearance of objects as well as drawing methods*/
#ifndef GRAPHICS_H_
#define GRAPHICS_H_

class Graphics {
public:
	Graphics();
	~Graphics();
	void init();

private:
	terrain = glGenLists(1);
};

#endif /* GRAPHICS_H_ */
