
#ifndef BOX_H
#define BOX_H

struct Box {
	int x, y;
	unsigned short w, h;
};

bool boundingBoxCollision (Box a, Box b);

#endif
